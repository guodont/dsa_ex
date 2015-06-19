/*-----单链表的基本操作-----*/
#include<stdio.h>
#include<stdlib.h>
typedef int Elemtype;
typedef int Status;

typedef struct node//定义存储节点
{
	int data;//数据域
	struct node *next;//结构体指针
} *linklist,node;//结构体变量，结构体名称
linklist creat (int n)//创建单链表
{
	linklist head,p;//定义头指针head,p指针
	int x,i;
	head=(node *)malloc(sizeof(node));//生成头结点
	head->next=NULL;
	printf("输入数字:\n");
	for(i=n;i>0;i--)//for 循环用于生成第一个节点并读入数据
	{
		scanf("%d",&x);
		p=(node *)malloc(sizeof(node));
		p->data=x;//读入第一个节点的数据
		p->next=head->next;//把第一个节点连在头结点的后面
		head->next=p;//循环以便于生成第二个节点
	}
return head;//返回头指针

}
void output (linklist head)//输出链表
{
	linklist p;
	p=head->next;
	do
	{
		printf("%3d",p->data);
		p=p->next;

	}
	while(p);
	printf("\n");


}

 Status GetElem(linklist l,int i,Elemtype &e )//查找操作
 {
	 linklist p;
	 int j;
	 p=l->next;
	 j=1;
	 while(p && j<i)
	 {
		 p=p->next;
		 ++j;
	 }
	 if(!p || j>i)
		 printf("无法查找");
	 e=p->data;
	 return e;


 }


Status insert ( linklist &l,int i, Elemtype e)//插入操作
{
	int j=0;
linklist p=l,s;
	while(j<i-1 && p)
	{
		p=p->next;
		++j;
	}
	if(!p || j>i-1)
			printf("无法插入");
	else
	{
		s=(node *)malloc(sizeof(node));
		s->data=e;
		s->next=p->next;
		p->next=s;
		return 1;
	}
}
Status delect ( linklist &l,int i, Elemtype &e)//删除操作
{
	int j=0;
	linklist p=l,q;
	while(j<i-1 && p->next)
	{
		p=p->next;
			++j;
	}

	if(!p->next || j>i-1)
			printf("无法删除");
	else
	{
		q=p->next;
		p->next=q->next;
		e=q->data;
		free(q);
		return 1;
	}
}

void main()
{
	linklist la;
	int n;
	int i,j;
	Elemtype e;
	char cmd;
	printf("输入链表元素的个数:\n");
	scanf("%d",&n);
	la=creat(n);
	printf("输出链表:\n");
	output(la);
	
	do
		{
			printf("g,G...查找\n");
			printf("i,I...插入\n");
			printf("d,D...删除\n");
			printf("q,Q...退出\n");
			do
			{
				scanf("%c",&cmd);
			}
			while((cmd!='g')&&(cmd!='G')&&(cmd!='d')&&(cmd!='D')&&(cmd!='q')&&(cmd!='Q')&&(cmd!='i')&&(cmd!='I'));
			switch(cmd)
			{
			case 'g':
			case'G':
				printf("请输入要查找元素的位置:\n");
				scanf("%d",&i);
				j=GetElem(la,i,e);
				printf("所要查找的元素是%d\n",j);
				break;
			case 'i':
			case'I':
				printf("请输入你要插入的数据：");
				scanf("%d",&e);
				printf("请输入你要插入的位置：");
				scanf("%d",&i);
				insert(la,i,e);
				printf("插入后的链表:\n");
				output(la);
				break;
			case'd':
			case'D':
				printf("请输入要删除的位置:\n");
				scanf("%d",&i);
				delect(la,i,e);
				printf("删除的那个元素是:%d\n",e);
				printf("输出删除后的顺序表:\n");
				output(la);
				break;
			}
		}
		while((cmd!='q')&&(cmd!='Q'));
}

