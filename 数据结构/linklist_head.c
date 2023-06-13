#include<stdio.h>
#include<stdlib.h>
#include<time.h>
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

//头结点结构体
typedef struct 
{
    int MAXlength;
    Node * start;
}Head;

//**************函数列表***************

Head * InitList(Head * L);//初始化头结点
int CreatList_Head(Head *L,int n);//随机数创建n个结点（头插）
int Traversal(Head * L);//遍历显示链表数据
int CreatList_Head2(Head*L,int i);//录入数据式头插
int ListInsert(Head *L,int i,DataType NewData);//按位插入
Node* DelData(Head * L , int i );//删除数据
void recursiveDeletion(Head * L);//双指针销毁链表
Node* FIND(Head *L,DataType data);//按内容查找
int MOVE(Head*L,int i,int j);//移动函数
DataType middlelist(Node*L);//返回中间值
int getlength(Node*L);
Node * list_flip(Head * head,Node * tmp);//翻转
void list_flip_pointer(Head * head);//翻转，但是是指针版


//************************************

/*************************************

这里我们用正常逻辑，计数从1开始计数

*************************************/
int main()
{
    //创建空链表
    Head *Linklist;
    Linklist=InitList(Linklist);
    if(Linklist==NULL)
    {
        printf("链表头结点创建有误....\n");
        return -1;
    }

/*****************链表的整表创建(随机数创建长度为n的链表)********************

    //链表的整表创建(随机数创建长度为n的链表)
    int n=0;
    // int judge2=1;//做判断是否成功
    // printf("输入要创建的链表长度:\n");
    // scanf("%d",&n);
    // while(getchar()!='\n');
    // judge2=CreatList_Head(&Linklist,n);//头插方式
    // if(judge2==0)
    // {
    //     printf("创建链表有误...\n");
    //     return -1;
    // }else{
    //     Linklist.MAXlength=judge2;//更新链表长度
    //     // printf("长度为%d\n",Linklist.MAXlength);
    // }
    // Traversal(&Linklist);

****************************************************************************/


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
        k=CreatList_Head2(Linklist,k);
        Linklist->MAXlength=k;
        printf("当前链表长度为:%d\n",Linklist->MAXlength);
        Traversal(Linklist);
    }
    printf("链表长度为%d\n",Linklist->MAXlength);

    Traversal(Linklist);

//****************************************************************************

    // //链表的遍历
    // int num=0;
    // num=Traversal(&Linklist);
    // printf("链表的长度为%d\n",num);

//*****************************链表的插入***************************************
    //
    // int i=0;
    // DataType new=0;
    // printf("请输入想要插入的位置:\n");
    // scanf("%d",&i);
    // while (getchar()!='\n');
    // printf("请输入想要插入的数据:\n");
    // scanf("%d",&new);
    // while(getchar()!='\n');
    // // printf("i:%d new:%d",i,new);
    // ListInsert(Linklist,i,new);
    // Traversal(Linklist);
    // printf("链表长度为%d\n",Linklist->MAXlength);

//****************************************************************************

//**************************删除链表结点**************************************
    
    // int m=0;
    // Node *q=NULL;
    // printf("请输入需要删除的结点序号:\n");
    // scanf("%d",&m);
    // while(getchar()!='\n');
    // q=DelData(Linklist,m);
    // free(q);
    // Traversal(Linklist);
    // printf("length=%d\n",Linklist->MAXlength);

//****************************************************************************

//****************************查找函数**********************************

    // int n;
    // n=FIND(Linklist,5);
    // printf("第%d位\n",n);

//****************************************************************************

//******************************移动函数****************************************

    // int y;
    // int z;
    // printf("请输入需要移动的成员序号以及要插入的位置\n");
    // scanf("%d %d",&y,&z);
    // while(getchar()!='\n');
    // MOVE(Linklist,y,z-1);


//****************************************************************************

//******************************翻转链表**************************************
    Traversal(Linklist);
    // list_flip(Linklist,Linklist->start);
    list_flip_pointer(Linklist);
    Traversal(Linklist);

//****************************************************************************

//*******************************返回中间结点********************************
    DataType num=0;
    num=middlelist(Linklist->start);
    printf("中间值为:%d\n",num);
    Traversal(Linklist);
//**************************************************************************

//***************销毁内存,先释放后面的，再释放前面的，用双指针的方式***************

    recursiveDeletion(Linklist);
    printf("-------------\n");
    free(Linklist);


//****************************************************************************
    return 0;
}

//初始化头结点,返还一个头结点地址,传入一个头结点指针
Head * InitList(Head * L)
{
    Head *p=(Head*)calloc(1,sizeof(Head));
    if(p==NULL)
    {
        return FALSE;
    }
    p->start=NULL;//注意链表末尾要指向空
    p->MAXlength=0;//初始化为0，表示空链表
    return p;
}

//头插法创建一个具有n个元素的随机值的结点，成功返还长度,失败返还FALSE
int CreatList_Head(Head *L,int n)
{
    //先判断输入的是否合法
    if(n<1)
    {
        printf("您输入的长度不合法....\n");
        return FALSE;
    }

    Node *p;//创建工作指针,用于接收新创建的结点指针
    srand(time(0));
    //先创建首个元素
    L->start=(Node*)calloc(1,sizeof(Node));
    L->start->next=NULL;
    L->start->data=rand()%100+1;
    p=L->start;//这里避免p为野指针

    int j=1;
    for(j=1;j<n;j++)
    {
        //创建一个空的结点
        p=(Node*)calloc(1,sizeof(Node));
        p->next=L->start;//先将插入结点的指针指向第一个结点
        L->start=p;//再将该结点地址赋给L的指针域指针
        p->data=rand()%100+1;//随机生成100以内的数据
        // printf("创建了结点...\n");
    }
    return j;
}

//遍历一个链表,传入链表的头结点地址，返还FALSE表示遍历失败，成功返回长度
int Traversal(Head * L)
{
    Node *p=L->start;//指向第一个结点
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

//自带数据录入的头插法,传入头节点地址,以及已经插入的长度，返还当前的长度
int CreatList_Head2(Head*L,int i)
{
    Node *tmp;
    int j=i; 
    int data=0;

    //首先判断链表是否为空链表
    if(L->start==NULL)
    {
        printf("链表为空...\n");
        L->start=(Node *)calloc(1,sizeof(Node));
        tmp=L->start;
        tmp->next=NULL;
        printf("录入最后一个数据:\n");
        scanf("%d",&data);
        while(getchar()!='\n');
        tmp->data=data;
        j++;
    }else{
        printf("链表不为空...\n");
        tmp=L->start;
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
        tmp->next=L->start;//先将插入结点的指针指向第一个结点
        L->start=tmp;//再将该结点地址赋给L的指针域指针
        tmp->data=data;
        j++;
        // printf("创建了结点...\n");
        Traversal(L);
    }
    return j;
}

//链表的插入,传入头结点地址，传入要插入的位置(原该位置移动),还有一个新的数据,失败返还FALSE,成功返还TRUE
int ListInsert(Head *L,int i,DataType NewData)
{
    if(i<1||i>L->MAXlength)
    {
        printf("输入的长度不合法...\n");
        // printf("i=%d,L->MAX=%d",i,L->MAXlength);
        return FALSE;
    }

    //利用工作指针遍历查找第i个位置
    Node *p =L->start;
    int j=1;
    while(p!=NULL&&j<i)
    {
        j++;
        if(j==i)//这里让p指向要移动的前驱结点
        {
            continue;
        }
        p=p->next;
    }

    //找到之后创建一个新的结点，先让新连后面那个，再让前一个指向新的
    Node *tmp=(Node*)calloc(1,sizeof(Node));
    if(j==1)//处理第一个结点情况
    {
        tmp->next=L->start;
        L->start=tmp;
    }else{
        tmp->next=p->next;
        p->next=tmp;
    }
    // tmp->data=NewData;
    memcpy(&(tmp->data),&NewData,sizeof(DataType));
    L->MAXlength++;
    return TRUE;
}

//单链表的删除,传入头结点的地址,以及要删除的结点序号,成功返还TRUE，失败返还FALSE
Node* DelData(Head * L , int i )
{
    Node*p=L->start;
    Node * q;//用于释放空间
    int j=1;

    //先找到需要找的结点，p同样和插入一样需要对直接前驱结点进行操作，需要加个continue跳过语句
    while(p!=NULL&&j<i)
    {
        j++;
        if(j==i)
        {
            continue;
        }
        p=p->next;
    }

    //删除数据,需要考虑第一位数据,不需要考虑最后一位
    if(j==1)//此时p指向第一位(j=2时也是指向第一位)
    {
        q=L->start;
        L->start=p->next;
    }else{
        q=p->next;
        p->next=p->next->next;
    }
    L->MAXlength--;
    return q;
}

//递归删除整个链表,传入一个头结点
//从头开始删除，需要用到两个指针，一前一后，前面删除，后一个再给前一个地址，然后后面的指向下一个依次删除
void recursiveDeletion(Head * L)
{
    //判断是否链表为空
    if(L->start==NULL)
    {   
        printf("链表为空，无需销毁\n");
        return;
    }

    Node *p=L->start;//前指针
    Node *q=p->next;//后指针

    //开始删除释放
    while(1)
    {
        printf("释放了一次\n");
        free(p);
        p=q;
        if(p==NULL)
        {
            break;
        }
        q=q->next;
    }
    printf("释放完毕.....\n");
    return ;
}

//依照内容查找,传入头结点指针,需要查找的内容，返回查找的指针,失败则返回NULL
Node * FIND(Head *L,DataType data)
{
    Node *p=L->start;
    int j=1;

    //查找内容
    while(1)
    {
        if(p->data==data)
        {
            printf("数据匹配:第%d位,值为:%d",j,p->data);
            return p;
        }
        j++;
        p=p->next;
    }
    return NULL;
}

//移动函数，传入头结点，以及需要移动的数据序号还有需要插入的位置，返还一个移动后的结点序号，失败返回FALSE
int MOVE(Head*L,int i,int j)
{
    Node *p=(Node*)calloc(1,sizeof(Node));
    Node*q=L->start;//该指针指向第一位，后面进行遍历查找第i位
    int cnt=1;

    if(i>L->MAXlength||i<1)
    {
        printf("查找失败....\n");
        return FALSE;
    }

    //查找第i位数
    while(1)
    {
        if(cnt==i)
        {
            break;
        }
        q=q->next;
        cnt++;
    }

    //将数据复制保存到内存中
    memcpy(p,q,sizeof(Node));

    //调用删除与插入函数
    DelData(L,cnt);
    ListInsert(L,j,p->data);

    //显示一下
    Traversal(L);

    return j;
}

//单向不循环链表输出中间项,传入第一个元素,用双指针进行计数，快指针走两步，慢指针走一步
DataType middlelist(Node*L)
{
    //判断是否为空链表
    if(L==NULL)
    {
        printf("链表空的，读取中间值失败...\n");
        return -1;
    }

    Node * P_fast=L;
    Node * P_slow=L;
    int j=1;//计数器

    for(;P_fast!=NULL;j++)
    {
        P_fast=P_fast->next;
        if(j%2==0)
        {
            P_slow=P_slow->next;
        }
    }

    return P_slow->data;

}
//得到链表长度
int getlength(Node*L)
{
    Node*p=L;
    static int cnt=0;//计数器
    
    if(p==NULL)
    {
        return cnt;
    }

    getlength(p->next);
    cnt++;
    return cnt;

}

//单向不循环链表翻转函数（递归法）
Node * list_flip(Head * head,Node * tmp)
{
    //判断链表长度是否为1或者为0
    if(head->start==NULL||tmp->next==NULL)
    {
        return NULL;
    }

    Node * ptr=tmp;
    //退出条件
    if(ptr->next->next==NULL)
    {
        ptr->next->next=ptr;
        printf("翻转了一次...\n");
        head->start=ptr->next;
        ptr->next=NULL;
        return NULL;
    }

    //递归调用函数
    list_flip(head,ptr->next);
    printf("翻转了一次...\n");
    ptr->next->next=ptr;
    ptr->next=NULL;
    return ptr;

}


void list_flip_pointer(Head * head)//用三个指针进行链表的翻转，从头开始进行翻转操作
{
    //判断链表长度是否足够
    if(head->start==NULL||head->start->next==NULL)
    {
        printf("链表无需翻转...\n");
        return ;
    }

    Node * p1= head->start;
    Node * p2=p1->next;
    Node * p3=p2->next;

    if(p1==head->start)
    {
        p1->next=NULL;
    }


    while(p3!=NULL)
    {
        //指针翻转
        p2->next=p1;

        //指针移位
        p1=p2;
        p2=p3;
        p3=p3->next;

    }

    p2->next=p1;
    head->start=p2;

    return;
}