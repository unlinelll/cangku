#include<stdio.h>
#include<stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0

typedef int DataType;

//结点结构体
typedef struct Node
{
    DataType data;
    struct Node * next;//指向一个结构体的指针,这里不要用别名，会无法识别    
}Node;

//**************函数列表***************

Node * InitList();//初始化头指针，并建立第一个结点
// int CreatList_Head(Node *L,int n);//随机数创建n个结点（头插）
int Traversal(Node * L);//遍历显示链表数据
Node* CreatList_Head2(Node*L);//录入数据式头插,这里注意传入的L不会改变实值的大小，也就是不会影响头指针的值，需要返回接收
Node * ListInsert(Node *L,Node*data,DataType NewData);//按位插入
// int DelData(Node * L , int i );//删除数据
Node* recursiveDeletion(Node * L);//递归销毁
// int FIND(Node *L,DataType data);//按内容查找
// int MOVE(Node*L,int i,int j);//移动函数


//************************************


int main()
{
//*************************创建头指针******************************
    Node * L=NULL;
    // L=InitList();//会创建首个结点
    // printf("初始化成功\n");

//****************************************************************

//*****************创建链表(以输入方式创建)**********************************

    int k=0;//用于统计长度
    int isprime=0;//用于退出循环条件
    while(1)
    {
        printf("是否要继续(-1退出)\n");
        scanf("%d",&isprime);
        while(getchar()!='\n');
        if(isprime==-1)
        {
            printf("录入结束\n");
            break;
        }
        L=CreatList_Head2(L);
        Traversal(L);
    }

//****************************************************************************


// //*****************************链表的插入***************************************
    
//     int i=0;
//     DataType new=0;
//     printf("请输入想要插入的位置:\n");
//     scanf("%d",&i);
//     while (getchar()!='\n');
//     printf("请输入想要插入的数据:\n");
//     scanf("%d",&new);
//     while(getchar()!='\n');
//     // printf("i:%d new:%d",i,new);
//     L=ListInsert(L,L->next,new);
//     k=Traversal(L);
//     printf("链表长度%d",k);

// //****************************************************************************


//***************销毁内存,先释放后面的，再释放前面的，用双指针的方式***************

    recursiveDeletion(L);
    // free(L);

//****************************************************************************


    return 0;
}


Node * InitList()
{
    Node*p=(Node*)calloc(1,sizeof(Node));
    if(p==NULL)
    {
        printf("初始化失败...\n");
        return FALSE;
    }
    p->next=NULL;

    return p;

}

int Traversal(Node * L)
{
    Node *p=L;//指向第一个结点
    if(p==NULL)
    {
        printf("遍历链表失败.....\n");
        return FALSE;
    }
    int length=1;
    while(1)
    {
        
        printf("第%d个值是:%d\n",length,p->data);
        p=p->next;
        if(p==NULL)
        {
            printf("遍历结束....\n");
            break;
        }
        length++;
    }
    return length;
}

Node* CreatList_Head2(Node*L)//注意传入的是参数而不是实值，这里改变无法改变其值
{
    Node *tmp;
    int data=0;

    //首先判断链表是否只有一个结点
    if(L==NULL)
    {
        L=(Node *)calloc(1,sizeof(Node));
        tmp=L;
        printf("录入最后一个数据:\n");
        scanf("%d",&(tmp->data));
        while(getchar()!='\n');
    }else{
        printf("链表长度不为0\n");
        tmp=L;
    }

    //头部插入
    while(1)
    {
        printf("请录入(0退出):\n");
        scanf("%d",&data);
        while(getchar()!='\n');
        if(data==FALSE)
        {
            printf("已退出....\n");
            break;
        }

        //插入操作
        tmp=(Node*)calloc(1,sizeof(Node));
        tmp->next=L;//先将插入结点的指针指向第一个结点
        L=tmp;//再将该结点地址赋给L的指针域指针
        tmp->data=data;
        printf("创建了结点...\n");
        Traversal(L);
    }
    return L;
}

Node * ListInsert(Node *L,Node * data,DataType NewData)
{
    //利用工作指针遍历查找数据的指针，传入要查找的结构体指针
    Node *p =L;
    while(1)
    {
        if(p==data)
        {
            printf("位置已找到...\n");
            break;
        }
        if(p->next==NULL)
        {
            printf("位置未找到...\n");
            break;
        }
        p=p->next;
    }
    
    // for(p=L;p->next!=NULL;p=p->next);

    //找到之后创建一个新的结点，先让新连后面那个，再让前一个指向新的
    Node *tmp=(Node*)calloc(1,sizeof(Node));
    if(p==L)//处理第一个结点情况
    {
        tmp->next=L;
        L=tmp;
    }else{
        tmp->next=p->next;
        p->next=tmp;
    }
    // tmp->data=NewData;
    memcpy(&(tmp->data),&NewData,sizeof(DataType));
    return L;
}

// //单链表的删除,传入头结点的地址,以及要删除的结点序号,成功返还TRUE，失败返还FALSE
// int DelData(Head * L , int i )
// {
//     Node*p=L->start;
//     Node * q;//用于释放空间
//     int j=1;

//     //先找到需要找的结点，p同样和插入一样需要对直接前驱结点进行操作，需要加个continue跳过语句
//     while(p!=NULL&&j<i)
//     {
//         j++;
//         if(j==i)
//         {
//             continue;
//         }
//         p=p->next;
//     }

//     //删除数据,需要考虑第一位数据,不需要考虑最后一位
//     if(j==1)//此时p指向第一位(j=2时也是指向第一位)
//     {
//         q=L->start;
//         L->start=p->next;
//         free(q);
//     }else{
//         q=p->next;
//         p->next=p->next->next;
//         free(q);
//     }
//     L->MAXlength--;
//     return TRUE;
    
// }


//递归释放内存
Node* recursiveDeletion(Node * L)
{
    if(L==NULL)
    {
        return NULL;
    }

    recursiveDeletion(L->next);
    printf("成员值为:%d\n",L->data);
    free(L);

    return NULL;

}