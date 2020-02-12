/*********************头文件***********************/
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
/*******************结构体定义***********************/
typedef struct{
	char * ch;                                  //存放字符串
	int length;                                 //存放字符串长度
} HString;                                      //定义一个堆串

typedef struct LNode{
	HString S;
	struct LNode * next;                        //指向下一个指针
	int listlines;                              //标示该字符串行数
}LNode, * LinkList;                             //定义链表存储字符串
/********************全局变量***********************/
LinkList head=(LinkList)malloc(sizeof(LNode));  //定义一个表头指针
int lines=80;                                   //单行字符存储的最大值
char filename[20];                              //定义一个字符型数组存放文件名
FILE *fp;                                       //定义一个文件指针
int setcolor=7;                                 //用于控制字体颜色
/*******************界面及菜单函数***********************/
void menuMain();                                //主函数界面
void menuFile();                                //文件菜单界面
void menuEdit();                                //编辑菜单界面
void menuStyle();                               //格式菜单界面
void menuCheck();                               //查看菜单界面
void menuHelp();                                //帮助菜单界面
void choiceFile();                              //文件操作功能菜单
void choiceEdit();                              //编辑操作功能菜单
void choiceStyle();                             //格式操作功能菜单
void choiceCheck();                             //查看操作功能菜单
void choiceHelp();                              //帮助操作功能菜单
/*********************功能函数***********************/
int color(int i);                               //设置字体颜色
void createNewFile();                           //新建一个文件
void openFile();                                //打开一个文件，并将文件中的数据导入进链表
void initList(LinkList * L);                    //初始化链表
int StrAssign();                                //新增字符串进链表（此时链表为空）
int StrAppend();                                //追加字符串进链表
int StrIndex(LinkList P, HString T);            //找到要删除的子串在该串中的位置
int StrDelete(LinkList P, int pos, int len);    //在当前串中删除指定的子串，并将删除后的结果前移
void writedata();                               //将链表中的数据保存到文件中
void ReadData();                                //将文件中的数据读取到链表中
void count();                                   //统计字母数、数字数、空格数、文章总字符数
int StrCount(LinkList P, HString T);            //统计指定子串在当前串中的出现次数
/*********************主函数***********************/
int main()
{
	head->next=NULL;                            //将链表置空                            
	system("color 07");                         //设置背景色
	SetConsoleTitle("简单行编辑器");            //设置窗口标题
	system("mode con cols=72 lines=35");        //设置窗口宽高
	char choice;
	while(1)
	{
		system("cls");
		menuMain();
		choice=getch();
		switch(choice)
		{
		case 'f':
			choiceFile();                        //文件功能菜单             
			getch();
			break;
		case 'e':
			choiceEdit();                        //编辑功能菜单
			getch();
			break;
		case 'o':
			choiceStyle();                       //格式功能菜单
			getch();
			break;
		case 'v':
			choiceCheck();                       //查看功能菜单
			getch();
			break;
		case 'h':
			choiceHelp();                        //帮助功能菜单
			getch();
			break;
		}
	}	
	return 0;
}
/********************************************************/
void menuMain()
{ //主界面
	printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	printf("  文件(F)    编辑(E)    格式(O)    查看(V)    帮助(H)");
	printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
}

void menuFile()
{ //文件界面
	printf("  新建(N)\n\n  打开(O)\n\n  保存(S)\n\n  退出(X)\n\n");
}
void menuEdit()
{ //编辑界面
	printf("\t     写入(R)\n\n\t     删除(D)\n\n");
}
void menuStyle()
{ //格式界面
	printf("\t\t\t字体颜色(C)\n\n");
}

void menuCheck()
{ //查看界面
	printf("\t\t\t\t   浏览(V)\n\n\t\t\t\t   统计(C)\n\n");
}
void menuHelp()
{ //帮助界面
	system("cls");
}

void menuColor()
{ //颜色界面
	printf("    ◎设置文本字体颜色：\n\n");
	printf("\t0.黑色\t\t8.灰色\n\n\t1.深蓝色\t9.亮蓝色\n\n\t2.深绿色\t10.亮绿色\n\n");
	printf("\t3.深蓝绿色\t11.亮蓝绿色\n\n\t4.深红色\t12.红色\n\n\t5.紫色\t\t13.粉色\n\n");
	printf("\t6.暗黄色\t14.黄色\n\n\t7.白色\t\t15.亮白色\n\n");
	printf("    ◎请输入字体颜色序号： ");	
	fflush(stdin);
	scanf("%d", &setcolor);
	color(setcolor);	
	Sleep(500);
	printf("\n\t设置成功！\n");
	color(7);
}

/*文件功能菜单*/
void choiceFile()
{
	char choice;
	menuFile();
	choice=getch();	
	system("cls");
	menuMain();
	switch(choice)
	{
	case 'n':
		createNewFile();                            //新建一个文件
		head->next=NULL;                            //将链表置空
		break;
	case 'o':
		openFile();
		break;
	case 's':
		if(fp==NULL && head->next!=NULL)            //文件未打开，链表不为空，则保存进新指定的文件中
		{
			printf("    ◎请输入要保存的文件名：");
			scanf("%s",filename);
			fp=fopen(filename, "w+");
			writedata();
		}
		if(fp!=NULL && head->next!=NULL)            //文件打开，链表不为空，则保存进已打开的文件中
		{
			writedata();
		}
		if((fp==NULL && head->next==NULL)||(fp!=NULL && head->next==NULL))
		{                                           //文件打开，链表为空或者文件未打开，链表为空，则无法保存
			printf("\n    ◎文件未打开或无在编辑文档，无法保存！\n");
			break;
		}
		printf("\n    ◎成功保存！\n");
		head->next=NULL;                            //保存完文件后将链表置空
		break;
	case 'x':
		exit(0);
		break;
	}
}

/*编辑功能菜单*/
void choiceEdit()
{
	char choice;
	int pos;
	HString T;
	LinkList P=head;
	T.ch=(char *)malloc(lines);
	menuEdit();
	choice=getch();
	system("cls");
	menuMain();
	switch(choice)
	{
	case 'r':
		color(7);
		printf("◎请在下面新增或追加文本内容（双击回车键退出编辑）\n");
		color(setcolor);
		if(head->next==NULL)
		{
			StrAssign();               //链表为空则新增内容
		}
		else
		{
			StrAppend();               //链表不为空则追加新内容
		}
		color(7);
		printf("\n    ◎写入成功！\n");
		break;
	case 'd':
		if(fp==NULL && head->next==NULL || fp!=NULL && head->next==NULL)
		{
			printf("\n    ◎无文档内容可删除！");
			break;
		}
		printf("    ◎请输入要删除的字符串：");
		scanf("%s", T.ch);
		T.length=strlen(T.ch);	
		while(P->next!=NULL)
		{	
			P=P->next;
			pos=StrIndex(P, T);	                //用pos获取子串位置
			StrDelete(P, pos, strlen(T.ch));    //根据pos位置还有子串长度删除子串
		}
		printf("\n    ◎删除成功！\n");
		break;
	}

}

/*格式功能菜单*/
void choiceStyle()
{
	char choice;                   //用于获取颜色数
	menuStyle();
	choice=getch();	
	if(choice=='c')
	{
		system("cls");
		menuMain();
		menuColor();
	}
}

/*查看功能菜单*/
void choiceCheck()
{
	char choice;
	int sum;
	LinkList P=head;
	HString T;
	T.ch=(char *)malloc(lines);
	menuCheck();
	choice=getch();	
	system("cls");
	menuMain();
	switch(choice)
	{
	case 'v':
		if(head->next==NULL)
		{
			printf("\n    ◎文件未打开或是无文档内容！\n");
			break;
		}
		color(7);
		printf("以下为文本内容：\n");
		color(setcolor);
		LinkList V;
		V=head;
		while(V->next!=NULL)                   //显示链表中的所有记录
		{
			V=V->next;
			printf("%s\n",V->S.ch);
		}
		color(7);
		count();		
		break;
	case 'c':
		sum=0;
		printf("\n    ◎请输入你想查询的子串：");
		scanf("%s",T.ch);
		T.length=strlen(T.ch);
		while(P->next!=NULL)                    
		{	
			P=P->next;
			sum=sum+StrCount(P, T);                  //统计文本中子串出现的次数
		}
		printf("\n    ◎该子串在文本中出现次数为：%d\n",sum);
		break;
	}
	
}

/*帮助功能菜单*/
void choiceHelp()
{
	char ch;
	system("cls");
	fp=fopen("help.txt","r");                  //以只读方式打开该文件
	if(fp==NULL)
		printf("\n\n    ◎该文件不存在！\n");
	else
	{		
		while((ch=fgetc(fp))!=EOF)             //读取文本文件中的内容到显示屏上
			fputc(ch,stdout);
		printf("\n") ;
	}
	fclose(fp);
	fp=NULL;
}

/*控制字体颜色*/
int color(int c)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c);  
	return 0;
}

/*创建一个新文件*/
void createNewFile()
{
	printf("\n    ◎请输入文件名：");
	scanf("%s", filename);
	fp=fopen(filename,"w+");                     //以新建方式打开可读写文件               
	if(fp==NULL)
	{
		printf("\n\n\t◎无法创建该文件！\n\n");
		exit(0);
	}
	else
	{
		Sleep(500);
		printf("\n    ◎新建成功！\n\n");
	}
}

/*文件打开的同时，读取文件数据进链表*/
void openFile()
{
	printf("\n    ◎请输入文件名：");
	scanf("%s", filename);
	fp=fopen(filename,"r+");                   //以读写方式打开已存在的文件
	if(fp==NULL)
	{
		Sleep(500);
		printf("\n    ◎该文件不存在！\n\n");
	}
	else
	{
		Sleep(500);
		printf("\n    ◎成功打开该文件！\n\n");
	}
	head->next=NULL;                           //将链表置空
	ReadData();                                //读取文件数据进链表
}

void initList(LinkList * L)
{
	* L = (LinkList)malloc(sizeof(LNode));
	(*L)->S.ch=(char *)malloc(lines);
	(*L)->listlines=0;                       
	(*L)->next=NULL;
}

/*新增字符串进链表*/
int StrAssign()
{
	int i=1;
	LinkList P;LinkList Q;
	initList(&P);
	head->next=P;
	while(1)
	{
		fflush(stdin);
		gets(P->S.ch);                                //获取字符串
		P->S.length=strlen(P->S.ch);                  //将串长赋值给length
		P->listlines=i++;                             //将行数赋值给listlines
		if(!P->S.length)                              //如果输入的字符串长度为0，则停止输入
			break;
		Q=P; 
		initList(&P);
		Q->next=P;                                    //结构体指针Q用于将字符串链表的存储空间衔接起来
	}	
	Q->next=NULL;                                     
	return  1;
}

/*追加字符串进链表*/
int StrAppend()
{
	int i;
	LinkList P, Q;
	P=head;
	initList(&Q);
	while(P->next!=NULL)                              //用于结构体指针指向表尾为空的那条记录
	{
		P=P->next;
	}
	i=P->listlines+1;                                 //用于调整行数
	while(1)
	{			
		fflush(stdin);
		gets(Q->S.ch);                                //获取字符串
		Q->S.length=strlen(Q->S.ch);                  //将串长赋值给length
		Q->listlines=i++;	                          //将行数赋值给listlines
		if(!Q->S.length)                              //如果输入的字符串长度为0，则停止输入
			break;			
		P->next=Q;		
		initList(&Q);
		P=P->next;                               //结构体指针P用于将字符串链表的存储空间衔接起来
	}	
	P->next=NULL;
	return 1;
}

/*将链表记录写入文件中*/
void writedata()
{
	LinkList p;
	p=head;
	if(fp!=NULL)
		fclose(fp);
	fp=fopen(filename,"w+");                             //以新建方式打开可读写文件
	while(p->next!=NULL)
	{
		p=p->next;
		if (fwrite(p->S.ch,strlen(p->S.ch),1,fp)!=1)     //逐条将记录写入文件中
         {
              printf("写入文件错误!\n");
			  exit(0);
         }
		fputc('\n',fp);		                             //使写进文本的字符串可以换行显示
	}
	fclose(fp);
	fp=NULL;
}

/*将文本中的字符串数据读入链表中*/
void ReadData()
{
	LinkList p1;
	LinkList p2;	
	initList(&p1);
	head->next=p2=p1; 
	char *find;
	int i=1;
	while(fgets(p1->S.ch,lines,fp) != NULL)              //逐行将文字中的字符串读入链表
	{
		find=strchr(p1->S.ch,'\n');                      //去掉文本中的换行符
		if(find)
			*find='\0';
		p1->S.length=strlen(p1->S.ch);                   //将字符串的大小赋给length
		p1->listlines=i++;                               //保存行数
		p2->next=p1;                                     //p2结构体指针用于衔接链表数据
		p2=p1;
		initList(&p1);
	}
	p2->next=NULL;
}

/*子串位置检索*/
int StrIndex(LinkList P, HString T)
{
	int i=0, j=0;
	if(T.length==0 || T.length>P->S.length) return -1;
	while(i<P->S.length && j<T.length)
		if(P->S.ch[i]==T.ch[j])                          //判断两个子串是否相同                 
		{
			i++;
			j++;
		}
		else
		{
			i=i-j+1;                                     //不相同则将i置为原子串首地址大一的位置
			j=0;                                         //将j置为指定子串的首地址
		}
	if(j>=T.length) return (i-j);                        //如果找到子串，则返回子串的首地址
	else 
		return -1;
}

/*删除字符串中的pos位置开始的指定子串*/
int StrDelete(LinkList P, int pos, int len)
{
	int i;
	char *temp;
	if(pos<0||pos>(P->S.length - len))                     //如果下标位置不对，则不进行删除操作
		return 0;
	temp = (char *)malloc(P->S.length - len);              //用于存放删除指定子串后的字符串
	if(temp==NULL) return 0;
	for(i=0;i<pos;i++)                                     
		temp[i]=P->S.ch[i];                                //将指定子串位置前的子串赋给temp
	for(i=pos;i<P->S.length - len;i++)
		temp[i]=P->S.ch[i+len];                            //将指定子串位置后的子串赋给temp
	temp[i]='\0';                                          //以‘\0’为结束符代表新串的结束
	P->S.length=P->S.length - len;
	free(P->S.ch);                                         //释放原字符串的存储空间
	P->S.ch=temp;                                          //结构体指针P指向新字符串的存储空间
	return 1;
}

/*统计文本中的字母数、数字数等*/
void count()
{
	LinkList P=head;
	int Letters=0,Number=0,Spaces=0,TotalNumber=0;
	int i;
	if(head->next==NULL)
	{
		printf("\n    ◎无数据可统计！\n");
		return;
	}
	while(P->next!=NULL)
	{
		P=P->next;
		for(i=0;i<P->S.length;i++)
		{
			if(P->S.ch[i]>=65&&P->S.ch[i]<=90 ||P->S.ch[i]>=97 && P->S.ch[i]<=122)
				Letters++;                                //统计字母个数
			if(P->S.ch[i]==32)
				Spaces++;                                 //统计空格个数
			if(P->S.ch[i]>=48 && P->S.ch[i]<=57)
				Number++;			                      //统计数字个数
		}
		TotalNumber=TotalNumber+P->S.length;              //统计文章总字数
	}
	printf("\n\n\t\t\t\t共%d行\n",P->listlines);
	printf("______________________________________________________________________\n");
	printf("\n统计信息：\n");
	printf("\n    全部字母数：%d\n",Letters);
	printf("\n    数字个数：%d\n",Number);
	printf("\n    空格个数：%d\n",Spaces);
	printf("\n    文章总字数：%d\n",TotalNumber-Spaces);
}

/*统计字符串中有相同指定子串的个数*/
int StrCount(LinkList P, HString T)
{
	int i=0, j=0, sum=0, check;                          //sum用来存放相同子串个数；check用来判别两个子串是否相同
	if(T.length==0 || T.length>P->S.length) return 0;
	for(i=0;i<P->S.length;i++)
	{
		check=1;
		for(j=0;j+i<P->S.length && j<T.length;j++)
		{
			if(P->S.ch[i+j]!=T.ch[j])                    //用于判断i开始长度为T.length的子串是否与T.ch子串相同
			{
				check=0;                                 //不同则跳出内循环，换个i值重新比较
				break;
			}
		}
		if(check==1)                                     //如果相同则sum自加1
		{
			sum++;
		}
	}
	return sum;
}


