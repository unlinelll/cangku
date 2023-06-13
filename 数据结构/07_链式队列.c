#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include <string.h>

#define TRUE 1
#define FALSE 0

typedef int DataType;

typedef struct Queue
{
    DataType data;
    struct Queue * Next;
}Queue;

typedef struct 
{
    Queue *front;//队头就是头结点这里
    Queue *rear;
}Manage;

/**************************************************

                   说明
    这里单向不循环链表注意必须是链表尾部为队尾，
    链表头是队头，队头出，队尾入。这里用尾指针是为了

***************************************************/
//=================函数列表======================
Manage* InitMange();//初始化创建管理结构体,返还一个管理体指针
Queue * CreatNode(DataType * NewData);//建立新结点
void Add_Head(Manage * Q,Queue * Que);//尾插法插入数据,不返还数据
DataType * GetData();//获得数据
int Judge();//判断循环是否继续
void enQueue(Manage * Q);//入队,尾插
void outQueue(Manage * Q);//出队,头出列

//===============================================

int main()
{
    //初始化管理结构体
    Manage * man_Queue=InitMange();

    //开始入队
    enQueue(man_Queue);

    //出队操作,顺便释放内存
    outQueue(man_Queue);


    //释放管理结构体
    free(man_Queue);
}

Manage* InitMange()
{
    //申请一块内存
    Manage * ptr=(Manage *)calloc(1,sizeof(Manage));
    if(ptr==NULL)
    {
        perror("manage error...\n");
        return NULL;
    }

    //初始化管理结构体
    ptr->front=NULL;
    ptr->rear=NULL;

    return ptr;
}

Queue * CreatNode(DataType * NewData)
{
    //申请内存
    Queue * ptr=(Queue * )calloc(1,sizeof(Queue));
    
    //内存拷贝
    memcpy(&ptr->data,NewData,sizeof(DataType));
    ptr->Next=NULL;

    return ptr;
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

DataType * GetData()//只能录入int 型数据
{
    //申请一个内存
    DataType *new=(DataType * )calloc(1,sizeof(DataType));
    if(new==NULL)
    {   
        perror("newdata error...\n");
        return NULL;
    }

    //录入数据
    printf("请输入数据:\n");
    scanf("%d",new);
    while(getchar()!='\n');

    //返还
    return new;
}

void enQueue(Manage * Q)
{
    //判断管理结构体里队列是否是空,为空则创建一个新结点
    Queue * ptr=NULL;
    DataType * NewData=NULL;
    while(Judge())
    {
        if(Q->rear==NULL)
        {
            printf("队列为空...\n");
            NewData=GetData();
            ptr=CreatNode(NewData);
            Q->rear=ptr;
            Q->front=ptr;
            free(NewData);
            continue;
        }

        //开始创建
        NewData=GetData();
        ptr=CreatNode(NewData);
        Add_Head(Q,ptr);//尾插插入数据

        //释放Newdata
        free(NewData);
    }

    return;
}

void outQueue(Manage * Q)
{
    //判断队尾是否指向空，即队列是否为空
    Queue * ptr=NULL;
    while(1)
    {
        if(Q->front==NULL)
        {
            printf("队列为空...\n");
            Q->rear=NULL;
            break;
        }

        //直接指向后一位，并释放
        ptr=Q->front;
        printf("成员为:%d\n",ptr->data);
        Q->front=Q->front->Next;
        free(ptr);
    }
    return ;
}

void Add_Head(Manage * Q,Queue * Que)
{
    //将已有的新节点插入到队尾
    Q->rear->Next=Que;
    Q->rear=Que;

    return ;

}