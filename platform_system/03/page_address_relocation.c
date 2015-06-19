#define pagesize  1024
#define pagetablelength  64

/*系统页表*/
const int pagetable[pagetablelength]={0,42,29,15,45,31,44,43,
                               41,28,1,30,12,24,6,32,
	                           14,27,13,46,7,33,10,22,
				               40,2,51,11,39,23,49,50,
				               26,16,25,4,47,17,3,48,
				               52,36,58,35,57,34,21,63,
				               5,37,18,8,62,56,20,54,
				               60,19,38,9,61,55,59,53};
#include<iostream.h>
#include<iomanip.h>

void main()
{
	int logicaladdress=0;
	int pagenum=0;
	int w=0;
	cout<<"系统页号对应块号情况（页号——>块号）：\n";
	for(int i=0;i<64;i++)
	{		
		cout<<setw(2)<<i<<"-->"<<setw(2)<<pagetable[i]<<"  ";
		if(i%8==7)
			cout<<endl;
	}
	cout<<endl<<"请输入逻辑地址（十进制）：\n";
	cin>>logicaladdress;
	pagenum=logicaladdress/pagesize;    //求页号
	w=logicaladdress%pagesize;          //求页内偏移地址
    if(pagenum>pagetablelength)         //判断是否跃界
	{
		cout<<"本次访问的地址已超出进程的地址空间，系统将产生越界中断！\n";
		return;
	}
	cout<<"对应的物理地址为（十进制）：\n"<<pagetable[pagenum]*pagesize+w<<endl;
}

