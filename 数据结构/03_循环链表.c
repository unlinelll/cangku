#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include <string.h>

#define TRUE 1
#define FALSE 0

typedef struct student
{
    char name[32];
    int age;

}DataType;

typedef struct Node
{
    DataType data;
    struct Node * Next;
    struct Node * Prior;
}Node;

//======================函数列表===========================
Node * CreatNode(DataType * NewData);//初始化创建新结点,传入一个新数据的指针，返还一个指向新结点的指针，传入空则不写入数据
void InsertList(Node * Prior,Node * Next ,Node *NewData);//（单纯插入）双向链表插入,传入三个参数,前后结点指针以及新的数据结点指针,不返还
DataType getData();//得到新数据函数，返还一个录入的DataType的值
DataType * getData1();//得到新数据函数，返还一个DataType类型的数据地址，失败返还空，注意需要释放内存
int Judge();//用于判断循环是否继续的函数，返还TRUE或FALSE
void Add_Head(Node * head);//头插法创建链表,传入一个头结点指针
int Traversal(Node * head);//遍历链表的函数,传入头结点指针,返还链表长度,不包括头结点
void MOVE(Node * target,Node *Prior);//移动位置的函数,传入需要移动结点指针，再输入需要移动的前目标位置,无返还
Node *DelData(Node *del);//结点删除,输入要删除的指针位,返还被删除掉的结点指针
Node *Find(Node *head,DataType *data);//查找位置的函数，输入头结点指针，以及需要查找的数据指针，返还找到的位置,失败返回头结点指针
void DestroyList(Node *head);//销毁链表,传入头结点指针
void Editlist(DataType * NewData,Node * Edit);//修改数据的函数，传入一个数据指针，以及需要修改的位置指针，不返还
void Add_Order(Node * head,DataType * NewData);//有序插入
// void DestroyList1(Node *head);//递归销毁——有点问题

//========================================================

int main()
{
//====================创建链表头节点========================
    Node * head = CreatNode(NULL);
    if(head==NULL)
    {
        printf("创建链表失败...\n");
        return -1;
    }
//=========================================================


//=================头插法创建新的链表=======================
    // Add_Head(head);
    // Traversal(head);
//=========================================================

//===================有序插入==============================
    while(Judge())
    {
        DataType *newnum=getData1();

        Add_Order(head,newnum);
        Traversal(head);

        free(newnum);
    }
//=========================================================

//================查找，并移动函数==========================
// printf("===================================\n");
//     printf("需要移动的数:\n");
//     DataType *num1=getData1();
//     printf("需要移动到的数（前）:\n");
//     DataType *num2=getData1();
//     Node * ptr1=Find(head,num1);
//     Node * ptr2=Find(head,num2);

//     MOVE(ptr1,ptr2);
//     Traversal(head);
// printf("===================================\n");
//=========================================================


//======================删除操作===========================
// printf("===================================\n");
//     printf("输入需要删除的数据\n");
//     DataType *num3=getData1();
//     Node*ptr3=Find(head,num3);
//     DelData(ptr3);
//     Traversal(head);
//     free(ptr3);
// printf("===================================\n");
//=========================================================


//=====================修改链表值===========================
// printf("===================================\n");
//     printf("输入需要匹配修改的数据:\n");
//     DataType *num_edit=getData1();//需要被修改的数据
//     DataType *num_edit1=getData1();//需要修改的数据
//     Node *ptr_edit=Find(head,num_edit);
//     Editlist(num_edit1,ptr_edit);
//     Traversal(head);
// printf("===================================\n");
//=========================================================


//======================销毁链表============================

    DestroyList(head);

//=========================================================
    return 0;
}

int Traversal(Node * head)//正序
{
    //工作指针
    Node *tmp =head;
    int j=0;//计数器，不包含头结点情况

    //开始遍历，出口条件为p->next指向head
    for(tmp=head->Next;tmp!=head;tmp=tmp->Next)
    {
        printf("==============================\n");
        printf("第%d位",j+1);
        printf("学生姓名:%s\n",tmp->data.name);
        printf("学生年龄:%d\n",tmp->data.age);
        printf("==============================\n");
        j++;
    }
    if(j==0)
    {
        printf("链表为空...\n");
        return 0;
    }
    return j;
}

DataType * getData1()//返还指针获取数据，用于结构体类型的数据，要释放内存
{
    DataType * num=(DataType*)calloc(1,sizeof(DataType));//申请内存
    if(num==NULL)
    {
        printf("获取数据失败...\n");
        return NULL;
    }

    //录入数据
    printf("请输入姓名:\n");
    fgets(num->name,32,stdin);
    num->name[strlen(num->name)-1]='\0';

    printf("请输入年龄:\n");
    scanf("%d",&num->age);
    while(getchar()!='\n');

    return num;

}

// DataType getData()//获取单个int型数据
// {
//     printf("请输入数据:\n");
//     DataType data=0;
//     scanf("%d",&data);
//     while(getchar()!='\n');
//     return data;
// }


Node * CreatNode(DataType * NewData)
{
    //申请内存
    Node * p=(Node *)calloc(1,sizeof(Node));
    if(p==NULL)
    {
        printf("申请内存失败...\n");
        return NULL;
    }

    //初始化数据域
    if(NewData!=NULL)
    {
        memcpy(p,NewData,sizeof(Node));
    }

    //初始化指针域
    p->Next=p;
    p->Prior=p;

    return p;

}

void InsertList(Node * Prior,Node * Next ,Node *NewData)
{
    //修改四个指针,传入三个指针不需要考虑顺序
    NewData->Next=Next;
    NewData->Prior=Prior;

    Prior->Next=NewData;
    Next->Prior=NewData;

    return;
}


void Add_Head(Node * head)//需要考虑只有头结点的情况
{
    //先获取数据，再创建新节点，再插入
    while(Judge())
    {
        DataType * newdata=getData1();
        Node *p=CreatNode(newdata);
        free(newdata);//释放掉申请的内存
        InsertList(head,head->Next,p);
        // InsertList(head->Prior,head,p);//改一下就变成了尾插
    }
    return;
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

void MOVE(Node * target,Node *Prior)
{
    if(target==Prior||target==NULL||Prior==NULL)//判断是否为同一个结点
    {
        printf("移动失败...\n");
        return;
    }
   
    Node*p=DelData(target);//取出该目标
    if(p==NULL||p->Next==p)
    {
        printf("移动失败...\n");
        return ;
    }

    InsertList(Prior,Prior->Next,p);
    return ;
}

Node *Find(Node *head,DataType *data)
{
    Node*p=head->Next;
    
    //对比数据内容
    for(;p!=head;p=p->Next)
    {
        if(!memcmp(&(p->data),data,sizeof(DataType)))
        {   
            printf("匹配成功...\n");
            return p;
        }
    }
    printf("匹配失败...\n");
    return NULL;
    
}

Node *DelData(Node *del)
{
    Node*p=del;
    if(del==NULL||del->Next==del)
    {
        printf("删除失败...\n");
        return NULL;
    }
    p->Prior->Next=p->Next;
    p->Next->Prior=p->Prior;

    p->Next=p->Prior=NULL;
    return p;

}

void DestroyList(Node *head)//双指针销毁数据,头结点没销毁
{
    if(head->Next==NULL)
    {
        printf("释放头结点...\n");
        free(head);
        return ;
    }
    Node*p=head->Next;
    Node*q=head->Next->Next;

    for(;p!=head;q=q->Next)
    {
        free(p);
        printf("销毁了一次\n");
        p=q;
    }
    free(head);
    return ;

}

void Editlist(DataType * NewData,Node * Edit)
{
    Node *p=Edit;
    if(p==NULL||p->Next==p)//判断头结点或空指针
    {
        printf("修改失败...\n");
        return;
    }
    memcpy(&p->data,NewData,sizeof(DataType));
    return;
}   

void Add_Order(Node * head,DataType * NewData)//有序插入,按照年龄从小到大排序，传入新数据以及头结点指针
{
    //遍历找到比该数据大的年龄
    Node * tmp=NULL;
    for(tmp=head->Next;tmp!=head;tmp=tmp->Next)
    {
        if((tmp->data.age)>(NewData->age))
        {
            break;
        }
    }

    //插入
    Node * New=CreatNode(NewData);
    InsertList(tmp->Prior,tmp,New);

    return;

}

// void DestroyList1(Node *head)//递归删除
// {
//     Node*p=head->Next;
//     if(p==head)
//     {
//         free(p);
//         return;
//     }
//     DestroyList1(p->Next);
//     free(p);
//     return;
// }