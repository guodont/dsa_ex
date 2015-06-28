#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//动态分配数组存储霍夫曼树
typedef struct{
	int weight;					//字符的权值
	int parent,lchild,rchild;			//字符的双亲及左右孩子
}HTNode,*HuffmanTree;        
 

typedef char* *HuffmanCode;   //动态分配数组存储霍夫曼编码
 
//选择k个结点中权值最小的两个结点
void Select(HuffmanTree &HT,int k,int &s1,int &s2)
{    int i;
     i=1;
     while(i<=k && HT[i].parent!=0)i++;
     //下面选出权值最小的结点，用s1指向其序号
     s1=i;    
     for(i=1;i<=k;i++)
     {       
         if(HT[i].parent==0&&HT[i].weight<HT[s1].weight)s1=i;
     }
     //下面选出权值次小的结点，用s2指向其序号
     for(i=1;i<=k;i++)
     {
         if(HT[i].parent==0&&i!=s1)break;
     }
     s2=i;  
     for(i=1;i<=k;i++)
     {
     if(HT[i].parent==0&&i!=s1&&HT[i].weight<HT[s2].weight)s2=i;
     }
}

//构造Huffman树，求出n个字符的编码
void HuffmanCoding(HuffmanTree &HT,HuffmanCode &HC,int *w,int n)
{   
     int m,c,f,s1,s2,i,start;
     char *cd;
     if(n<=1)return;
     m=2*n-1;        //n个叶子结点，n-1个非叶子结点
	 HT=(HuffmanTree)malloc((m+1)*sizeof(HTNode));  //预分配m+1个单元，0号单元未用
     HuffmanTree p=HT+1; 
     w++;   //w的0号单元也没有值，所以从1号单元开始
     for(i=1;i<=n;i++,p++,w++)	//对n个叶子结点赋初值
     {
         p->weight=*w;
         p->parent=p->rchild=p->lchild=0;
     }
     for(;i<=m;++i,++p)			//对另外n-1个叶子结点赋初值
     {
         p->weight=p->parent=p->rchild=p->lchild=0;
     }
 
     for(i=n+1;i<=m;i++)
     {
		 Select(HT,i-1,s1,s2);   //选出当前权值最小的两个结点s1和s2
         HT[s1].parent=i;		 //修改结点s1的双亲值
         HT[s2].parent=i;		 //修改结点s2的双亲值
         HT[i].lchild=s1;		 //修改双亲结点的左孩子结点
         HT[i].rchild=s2;		 //修改双亲结点的右孩子结点
         HT[i].weight=HT[s1].weight+HT[s2].weight;  //修改双亲结点的权值
     }
   //从叶子到根逆向求每个字符的霍夫曼编码
     HC=(HuffmanCode)malloc((n+1)*sizeof(char*)); //分配n个字符编码的头指针变量
     cd=(char*)malloc(n*sizeof(char));   //分配求编码的工作空间
     cd[n-1]='\0';//编码结束符
     for(i=1;i<=n;i++)   //逐个字符求霍夫曼编码
     {   
         start=n-1;            //编码结束符位置
         for(c=i,f=HT[i].parent;f!=0;c=f,f=HT[f].parent)    //从叶子到根逆向求编码
         {   
              if(HT[f].lchild==c) cd[--start]='0';
              else
                   cd[--start]='1';
         }
     HC[i]=(char*)malloc((n-start)*sizeof(char)); //为第i个字符编码分配空间
     strcpy(HC[i],&cd[start]);//从cd复制编码到HC
     }
  free(cd);   //释放工作空间
}

int main()
{   
	 int n,i;
     int* w;    //记录权值
     char* ch;  //记录字符
     HuffmanTree HT;
     HuffmanCode HC;
     //cout<<"请输入待编码的字符个数n=";
	 printf("请输入待编码的字符个数n=");
     //cin>>n;
	 scanf("%d",&n);
     w=(int*)malloc((n+1)*sizeof(int));  //记录权值，0号单元未用
     ch=(char*)malloc((n+1)*sizeof(char));//记录字符，0号单元未用
     //cout<<"依次输入待编码的字符data及其权值weight"<<endl;
     printf("依次输入待编码的字符data及其权值weight\n");
	 for(i=1;i<=n;i++)
     {
         printf("data[%d]=",i);
		 scanf("%s",&ch[i]);
		 printf("weight[%d]=",i);
		 scanf("%d",&w[i]);
     }
     HuffmanCoding(HT,HC,w,n);
     //输出字符及其编码
     for(i=1;i<=n;i++)
		printf("%c:%s\n",ch[i],HC[i]);
	return 0;
}
