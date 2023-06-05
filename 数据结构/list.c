#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#define MaxLength 30

//将要存入的数据取一个别名，便于修改
typedef int DataType;

//管理结构体的声明
typedef struct Data
{
    int maxlength;//表示顺序表的最大长度
    int lastSubscript;//表示顺序表的有效数据的末尾下标
    DataType * ptr;//一个指向存入数据类型的指针，要指向所申请的内存地址入口
}Data;

//初始化一个堆空间，给管理结构体以及所要存储的顺序表申请一块堆内存空间，返还一个管理结构体的入口地址
//（这里也可以将管理结构体直接定义在主函数的栈空间）
Data *InitList()
{
    //申请一块管理结构体的堆内存
    Data *p=(Data*)calloc(1,sizeof(Data));
    if(p==NULL)
    {
        printf("管理结构体堆内存申请失败.....\n");
        return NULL;
    }

    //初始化结构体的前两个成员变量
    p->maxlength=MaxLength;
    p->lastSubscript=-1;//这里用-1表示是因为下标是从0开始计数的

    //给顺序表申请一块堆内存空间，让管理结构体的ptr接收
    p->ptr=(DataType*)calloc(p->maxlength,sizeof(DataType));
    if(p->ptr==NULL)
    {
        printf("顺序表堆内存空间申请失败...\n");
        return NULL;
    }

    return p;

}

//录入数据函数,返还一个末尾下标
int inputData(Data *p)
{
    if(p->lastSubscript+1>=p->maxlength)
    {
        printf("顺序表存储已满...\n");
        return -2;//满了就返还一个-2表示录入失败
    }

    int i=0;
    for(i=p->lastSubscript;i<p->maxlength;i++)
    {
        scanf("%d",(p->ptr+i));
        while(getchar()!='\n');//清除缓冲区
        printf("已录入%d个数据\n",i+1);
        if(p->ptr[i]==-1)
        {
            printf("录入结束....\n");
            p->ptr[i]=0;//清理一下这个-1
            break;
        }
    }
    p->lastSubscript=i;
    return 0;
}

//排序函数,传入管理结构体指针,便录入数据边排序



//显示顺序表函数,还要判断顺序表是否为空
void Display(Data *p)
{
    if(p->lastSubscript==-1)
    {
        printf("顺序表为空....\n");
        return ;
    }
    for(int i=0;i<p->lastSubscript;i++)
    {
        printf("第%d个数据:%d\n",i+1,p->ptr[i]);
    }

    printf("显示结束.....\n");

}

int main()
{
    //初始化管理结构体以及顺序表
    Data *p=InitList();
    if(p==NULL)
    {
        printf("申请堆空间失败....\n");
        return -1;
    }


    //存入数据
    while(1)
    {
        printf("请按顺序录入数据(结束请录入-1):\n");
        inputData(p);
        Display(p);
    }

    //显示录入的顺序表数据
    Display(p);

    //排序函数



    return 0;
}