#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include <string.h>

#define TRUE 1
#define FALSE 0
#define LENGTH 10

typedef int Datatype;

typedef struct Queue
{
    Datatype * data;//顺序表地址
    int QueueSize;//尺寸
    int front;//队头，出队
    int rear;//队尾，入队
}Queue;

//=========================函数列表===========================
Queue * InitQueue();//初始化循环队列,返还管理结构体地址
void enQueue(Queue * Q,Datatype * NewData);//入队
Datatype getNewData();//获得新数据,返还新数据，注意要释放，只能录入int型
int Judge_Full(Queue *Q);//判断是否队列已满，传入管理结构体指针,返还是否正确
int Judge_Empty(Queue *Q);//判断是否为空
int Judge();//判断循环是否继续
int outQueue(Queue * Q);//出队
//销毁
//遍历
//============================================================


int main()
{
    //初始化循环队列
    Queue * Q=InitQueue();

    //入队操作
    while(Judge())
    {
        Datatype new=getNewData();
        enQueue(Q,&new);
        // free(num);
    }

    //出队操作
    while(!Judge_Empty(Q))
    {
        Datatype num=outQueue(Q);
        printf("成员数据为:%d\n",num);
    }

    free(Q->data);
    free(Q);

    return 0;
}

Queue * InitQueue()
{
    //申请一块内存
    Queue * ptr=(Queue*)calloc(1,sizeof(Queue));
    if(ptr==NULL)
    {
        perror("Queue error...\n");
        return NULL;
    }

    //初始化管理结构体
    ptr->data=(Datatype*)calloc(LENGTH,sizeof(Datatype));
    ptr->front=ptr->rear=0;
    ptr->QueueSize=LENGTH;

    return ptr;

}

void enQueue(Queue * Q,Datatype * NewData)
{
    //先判断队列是否已满
    if(Judge_Full(Q))
    {
        printf("队列已满...\n");
        return ;
    }

    //执行队列插入操作
    memcpy(Q->data+Q->rear,NewData,sizeof(Datatype));

    //队尾下标偏移
    Q->rear=((Q->rear+1)%(Q->QueueSize));

    return;

}

Datatype outQueue(Queue * Q)
{
    //判断队列是否为空
    if(Judge_Empty(Q))
    {
        printf("队列为空...\n");
        return -1;
    }

    //数据给录入并返还
    Datatype tmp=*(Q->data+Q->front);

    //队头偏移
    Q->front=((Q->front+1)%(Q->QueueSize));

    return tmp;

}

int Judge()
{
    int judge=-2;
    printf("是否要继续(0退出)\n");
    scanf("%d",&judge);
    while(getchar()!='\n');
    if(judge==0)
    {
        return FALSE;
    }else{
        return TRUE;
    }
}

Datatype getNewData()
{
    Datatype num=0;
    printf("请输入需要录入的数据:\n");
    scanf("%d",&num);
    while(getchar()!='\n');
    return num;
}

int Judge_Empty(Queue*Q)
{
    return (Q->front==Q->rear);
}

int Judge_Full(Queue *Q)
{
    return (((Q->rear+1)%(Q->QueueSize))==Q->front);
}