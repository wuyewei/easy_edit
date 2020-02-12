/*********************ͷ�ļ�***********************/
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
/*******************�ṹ�嶨��***********************/
typedef struct{
	char * ch;                                  //����ַ���
	int length;                                 //����ַ�������
} HString;                                      //����һ���Ѵ�

typedef struct LNode{
	HString S;
	struct LNode * next;                        //ָ����һ��ָ��
	int listlines;                              //��ʾ���ַ�������
}LNode, * LinkList;                             //��������洢�ַ���
/********************ȫ�ֱ���***********************/
LinkList head=(LinkList)malloc(sizeof(LNode));  //����һ����ͷָ��
int lines=80;                                   //�����ַ��洢�����ֵ
char filename[20];                              //����һ���ַ����������ļ���
FILE *fp;                                       //����һ���ļ�ָ��
int setcolor=7;                                 //���ڿ���������ɫ
/*******************���漰�˵�����***********************/
void menuMain();                                //����������
void menuFile();                                //�ļ��˵�����
void menuEdit();                                //�༭�˵�����
void menuStyle();                               //��ʽ�˵�����
void menuCheck();                               //�鿴�˵�����
void menuHelp();                                //�����˵�����
void choiceFile();                              //�ļ��������ܲ˵�
void choiceEdit();                              //�༭�������ܲ˵�
void choiceStyle();                             //��ʽ�������ܲ˵�
void choiceCheck();                             //�鿴�������ܲ˵�
void choiceHelp();                              //�����������ܲ˵�
/*********************���ܺ���***********************/
int color(int i);                               //����������ɫ
void createNewFile();                           //�½�һ���ļ�
void openFile();                                //��һ���ļ��������ļ��е����ݵ��������
void initList(LinkList * L);                    //��ʼ������
int StrAssign();                                //�����ַ�����������ʱ����Ϊ�գ�
int StrAppend();                                //׷���ַ���������
int StrIndex(LinkList P, HString T);            //�ҵ�Ҫɾ�����Ӵ��ڸô��е�λ��
int StrDelete(LinkList P, int pos, int len);    //�ڵ�ǰ����ɾ��ָ�����Ӵ�������ɾ����Ľ��ǰ��
void writedata();                               //�������е����ݱ��浽�ļ���
void ReadData();                                //���ļ��е����ݶ�ȡ��������
void count();                                   //ͳ����ĸ�������������ո������������ַ���
int StrCount(LinkList P, HString T);            //ͳ��ָ���Ӵ��ڵ�ǰ���еĳ��ִ���
/*********************������***********************/
int main()
{
	head->next=NULL;                            //�������ÿ�                            
	system("color 07");                         //���ñ���ɫ
	SetConsoleTitle("���б༭��");            //���ô��ڱ���
	system("mode con cols=72 lines=35");        //���ô��ڿ��
	char choice;
	while(1)
	{
		system("cls");
		menuMain();
		choice=getch();
		switch(choice)
		{
		case 'f':
			choiceFile();                        //�ļ����ܲ˵�             
			getch();
			break;
		case 'e':
			choiceEdit();                        //�༭���ܲ˵�
			getch();
			break;
		case 'o':
			choiceStyle();                       //��ʽ���ܲ˵�
			getch();
			break;
		case 'v':
			choiceCheck();                       //�鿴���ܲ˵�
			getch();
			break;
		case 'h':
			choiceHelp();                        //�������ܲ˵�
			getch();
			break;
		}
	}	
	return 0;
}
/********************************************************/
void menuMain()
{ //������
	printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	printf("  �ļ�(F)    �༭(E)    ��ʽ(O)    �鿴(V)    ����(H)");
	printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
}

void menuFile()
{ //�ļ�����
	printf("  �½�(N)\n\n  ��(O)\n\n  ����(S)\n\n  �˳�(X)\n\n");
}
void menuEdit()
{ //�༭����
	printf("\t     д��(R)\n\n\t     ɾ��(D)\n\n");
}
void menuStyle()
{ //��ʽ����
	printf("\t\t\t������ɫ(C)\n\n");
}

void menuCheck()
{ //�鿴����
	printf("\t\t\t\t   ���(V)\n\n\t\t\t\t   ͳ��(C)\n\n");
}
void menuHelp()
{ //��������
	system("cls");
}

void menuColor()
{ //��ɫ����
	printf("    �������ı�������ɫ��\n\n");
	printf("\t0.��ɫ\t\t8.��ɫ\n\n\t1.����ɫ\t9.����ɫ\n\n\t2.����ɫ\t10.����ɫ\n\n");
	printf("\t3.������ɫ\t11.������ɫ\n\n\t4.���ɫ\t12.��ɫ\n\n\t5.��ɫ\t\t13.��ɫ\n\n");
	printf("\t6.����ɫ\t14.��ɫ\n\n\t7.��ɫ\t\t15.����ɫ\n\n");
	printf("    ��������������ɫ��ţ� ");	
	fflush(stdin);
	scanf("%d", &setcolor);
	color(setcolor);	
	Sleep(500);
	printf("\n\t���óɹ���\n");
	color(7);
}

/*�ļ����ܲ˵�*/
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
		createNewFile();                            //�½�һ���ļ�
		head->next=NULL;                            //�������ÿ�
		break;
	case 'o':
		openFile();
		break;
	case 's':
		if(fp==NULL && head->next!=NULL)            //�ļ�δ�򿪣�����Ϊ�գ��򱣴����ָ�����ļ���
		{
			printf("    ��������Ҫ������ļ�����");
			scanf("%s",filename);
			fp=fopen(filename, "w+");
			writedata();
		}
		if(fp!=NULL && head->next!=NULL)            //�ļ��򿪣�����Ϊ�գ��򱣴���Ѵ򿪵��ļ���
		{
			writedata();
		}
		if((fp==NULL && head->next==NULL)||(fp!=NULL && head->next==NULL))
		{                                           //�ļ��򿪣�����Ϊ�ջ����ļ�δ�򿪣�����Ϊ�գ����޷�����
			printf("\n    ���ļ�δ�򿪻����ڱ༭�ĵ����޷����棡\n");
			break;
		}
		printf("\n    ��ɹ����棡\n");
		head->next=NULL;                            //�������ļ��������ÿ�
		break;
	case 'x':
		exit(0);
		break;
	}
}

/*�༭���ܲ˵�*/
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
		printf("����������������׷���ı����ݣ�˫���س����˳��༭��\n");
		color(setcolor);
		if(head->next==NULL)
		{
			StrAssign();               //����Ϊ������������
		}
		else
		{
			StrAppend();               //����Ϊ����׷��������
		}
		color(7);
		printf("\n    ��д��ɹ���\n");
		break;
	case 'd':
		if(fp==NULL && head->next==NULL || fp!=NULL && head->next==NULL)
		{
			printf("\n    �����ĵ����ݿ�ɾ����");
			break;
		}
		printf("    ��������Ҫɾ�����ַ�����");
		scanf("%s", T.ch);
		T.length=strlen(T.ch);	
		while(P->next!=NULL)
		{	
			P=P->next;
			pos=StrIndex(P, T);	                //��pos��ȡ�Ӵ�λ��
			StrDelete(P, pos, strlen(T.ch));    //����posλ�û����Ӵ�����ɾ���Ӵ�
		}
		printf("\n    ��ɾ���ɹ���\n");
		break;
	}

}

/*��ʽ���ܲ˵�*/
void choiceStyle()
{
	char choice;                   //���ڻ�ȡ��ɫ��
	menuStyle();
	choice=getch();	
	if(choice=='c')
	{
		system("cls");
		menuMain();
		menuColor();
	}
}

/*�鿴���ܲ˵�*/
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
			printf("\n    ���ļ�δ�򿪻������ĵ����ݣ�\n");
			break;
		}
		color(7);
		printf("����Ϊ�ı����ݣ�\n");
		color(setcolor);
		LinkList V;
		V=head;
		while(V->next!=NULL)                   //��ʾ�����е����м�¼
		{
			V=V->next;
			printf("%s\n",V->S.ch);
		}
		color(7);
		count();		
		break;
	case 'c':
		sum=0;
		printf("\n    �������������ѯ���Ӵ���");
		scanf("%s",T.ch);
		T.length=strlen(T.ch);
		while(P->next!=NULL)                    
		{	
			P=P->next;
			sum=sum+StrCount(P, T);                  //ͳ���ı����Ӵ����ֵĴ���
		}
		printf("\n    ����Ӵ����ı��г��ִ���Ϊ��%d\n",sum);
		break;
	}
	
}

/*�������ܲ˵�*/
void choiceHelp()
{
	char ch;
	system("cls");
	fp=fopen("help.txt","r");                  //��ֻ����ʽ�򿪸��ļ�
	if(fp==NULL)
		printf("\n\n    ����ļ������ڣ�\n");
	else
	{		
		while((ch=fgetc(fp))!=EOF)             //��ȡ�ı��ļ��е����ݵ���ʾ����
			fputc(ch,stdout);
		printf("\n") ;
	}
	fclose(fp);
	fp=NULL;
}

/*����������ɫ*/
int color(int c)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c);  
	return 0;
}

/*����һ�����ļ�*/
void createNewFile()
{
	printf("\n    ���������ļ�����");
	scanf("%s", filename);
	fp=fopen(filename,"w+");                     //���½���ʽ�򿪿ɶ�д�ļ�               
	if(fp==NULL)
	{
		printf("\n\n\t���޷��������ļ���\n\n");
		exit(0);
	}
	else
	{
		Sleep(500);
		printf("\n    ���½��ɹ���\n\n");
	}
}

/*�ļ��򿪵�ͬʱ����ȡ�ļ����ݽ�����*/
void openFile()
{
	printf("\n    ���������ļ�����");
	scanf("%s", filename);
	fp=fopen(filename,"r+");                   //�Զ�д��ʽ���Ѵ��ڵ��ļ�
	if(fp==NULL)
	{
		Sleep(500);
		printf("\n    ����ļ������ڣ�\n\n");
	}
	else
	{
		Sleep(500);
		printf("\n    ��ɹ��򿪸��ļ���\n\n");
	}
	head->next=NULL;                           //�������ÿ�
	ReadData();                                //��ȡ�ļ����ݽ�����
}

void initList(LinkList * L)
{
	* L = (LinkList)malloc(sizeof(LNode));
	(*L)->S.ch=(char *)malloc(lines);
	(*L)->listlines=0;                       
	(*L)->next=NULL;
}

/*�����ַ���������*/
int StrAssign()
{
	int i=1;
	LinkList P;LinkList Q;
	initList(&P);
	head->next=P;
	while(1)
	{
		fflush(stdin);
		gets(P->S.ch);                                //��ȡ�ַ���
		P->S.length=strlen(P->S.ch);                  //��������ֵ��length
		P->listlines=i++;                             //��������ֵ��listlines
		if(!P->S.length)                              //���������ַ�������Ϊ0����ֹͣ����
			break;
		Q=P; 
		initList(&P);
		Q->next=P;                                    //�ṹ��ָ��Q���ڽ��ַ�������Ĵ洢�ռ��ν�����
	}	
	Q->next=NULL;                                     
	return  1;
}

/*׷���ַ���������*/
int StrAppend()
{
	int i;
	LinkList P, Q;
	P=head;
	initList(&Q);
	while(P->next!=NULL)                              //���ڽṹ��ָ��ָ���βΪ�յ�������¼
	{
		P=P->next;
	}
	i=P->listlines+1;                                 //���ڵ�������
	while(1)
	{			
		fflush(stdin);
		gets(Q->S.ch);                                //��ȡ�ַ���
		Q->S.length=strlen(Q->S.ch);                  //��������ֵ��length
		Q->listlines=i++;	                          //��������ֵ��listlines
		if(!Q->S.length)                              //���������ַ�������Ϊ0����ֹͣ����
			break;			
		P->next=Q;		
		initList(&Q);
		P=P->next;                               //�ṹ��ָ��P���ڽ��ַ�������Ĵ洢�ռ��ν�����
	}	
	P->next=NULL;
	return 1;
}

/*�������¼д���ļ���*/
void writedata()
{
	LinkList p;
	p=head;
	if(fp!=NULL)
		fclose(fp);
	fp=fopen(filename,"w+");                             //���½���ʽ�򿪿ɶ�д�ļ�
	while(p->next!=NULL)
	{
		p=p->next;
		if (fwrite(p->S.ch,strlen(p->S.ch),1,fp)!=1)     //��������¼д���ļ���
         {
              printf("д���ļ�����!\n");
			  exit(0);
         }
		fputc('\n',fp);		                             //ʹд���ı����ַ������Ի�����ʾ
	}
	fclose(fp);
	fp=NULL;
}

/*���ı��е��ַ������ݶ���������*/
void ReadData()
{
	LinkList p1;
	LinkList p2;	
	initList(&p1);
	head->next=p2=p1; 
	char *find;
	int i=1;
	while(fgets(p1->S.ch,lines,fp) != NULL)              //���н������е��ַ�����������
	{
		find=strchr(p1->S.ch,'\n');                      //ȥ���ı��еĻ��з�
		if(find)
			*find='\0';
		p1->S.length=strlen(p1->S.ch);                   //���ַ����Ĵ�С����length
		p1->listlines=i++;                               //��������
		p2->next=p1;                                     //p2�ṹ��ָ�������ν���������
		p2=p1;
		initList(&p1);
	}
	p2->next=NULL;
}

/*�Ӵ�λ�ü���*/
int StrIndex(LinkList P, HString T)
{
	int i=0, j=0;
	if(T.length==0 || T.length>P->S.length) return -1;
	while(i<P->S.length && j<T.length)
		if(P->S.ch[i]==T.ch[j])                          //�ж������Ӵ��Ƿ���ͬ                 
		{
			i++;
			j++;
		}
		else
		{
			i=i-j+1;                                     //����ͬ��i��Ϊԭ�Ӵ��׵�ַ��һ��λ��
			j=0;                                         //��j��Ϊָ���Ӵ����׵�ַ
		}
	if(j>=T.length) return (i-j);                        //����ҵ��Ӵ����򷵻��Ӵ����׵�ַ
	else 
		return -1;
}

/*ɾ���ַ����е�posλ�ÿ�ʼ��ָ���Ӵ�*/
int StrDelete(LinkList P, int pos, int len)
{
	int i;
	char *temp;
	if(pos<0||pos>(P->S.length - len))                     //����±�λ�ò��ԣ��򲻽���ɾ������
		return 0;
	temp = (char *)malloc(P->S.length - len);              //���ڴ��ɾ��ָ���Ӵ�����ַ���
	if(temp==NULL) return 0;
	for(i=0;i<pos;i++)                                     
		temp[i]=P->S.ch[i];                                //��ָ���Ӵ�λ��ǰ���Ӵ�����temp
	for(i=pos;i<P->S.length - len;i++)
		temp[i]=P->S.ch[i+len];                            //��ָ���Ӵ�λ�ú���Ӵ�����temp
	temp[i]='\0';                                          //�ԡ�\0��Ϊ�����������´��Ľ���
	P->S.length=P->S.length - len;
	free(P->S.ch);                                         //�ͷ�ԭ�ַ����Ĵ洢�ռ�
	P->S.ch=temp;                                          //�ṹ��ָ��Pָ�����ַ����Ĵ洢�ռ�
	return 1;
}

/*ͳ���ı��е���ĸ������������*/
void count()
{
	LinkList P=head;
	int Letters=0,Number=0,Spaces=0,TotalNumber=0;
	int i;
	if(head->next==NULL)
	{
		printf("\n    �������ݿ�ͳ�ƣ�\n");
		return;
	}
	while(P->next!=NULL)
	{
		P=P->next;
		for(i=0;i<P->S.length;i++)
		{
			if(P->S.ch[i]>=65&&P->S.ch[i]<=90 ||P->S.ch[i]>=97 && P->S.ch[i]<=122)
				Letters++;                                //ͳ����ĸ����
			if(P->S.ch[i]==32)
				Spaces++;                                 //ͳ�ƿո����
			if(P->S.ch[i]>=48 && P->S.ch[i]<=57)
				Number++;			                      //ͳ�����ָ���
		}
		TotalNumber=TotalNumber+P->S.length;              //ͳ������������
	}
	printf("\n\n\t\t\t\t��%d��\n",P->listlines);
	printf("______________________________________________________________________\n");
	printf("\nͳ����Ϣ��\n");
	printf("\n    ȫ����ĸ����%d\n",Letters);
	printf("\n    ���ָ�����%d\n",Number);
	printf("\n    �ո������%d\n",Spaces);
	printf("\n    ������������%d\n",TotalNumber-Spaces);
}

/*ͳ���ַ���������ָͬ���Ӵ��ĸ���*/
int StrCount(LinkList P, HString T)
{
	int i=0, j=0, sum=0, check;                          //sum���������ͬ�Ӵ�������check�����б������Ӵ��Ƿ���ͬ
	if(T.length==0 || T.length>P->S.length) return 0;
	for(i=0;i<P->S.length;i++)
	{
		check=1;
		for(j=0;j+i<P->S.length && j<T.length;j++)
		{
			if(P->S.ch[i+j]!=T.ch[j])                    //�����ж�i��ʼ����ΪT.length���Ӵ��Ƿ���T.ch�Ӵ���ͬ
			{
				check=0;                                 //��ͬ��������ѭ��������iֵ���±Ƚ�
				break;
			}
		}
		if(check==1)                                     //�����ͬ��sum�Լ�1
		{
			sum++;
		}
	}
	return sum;
}


