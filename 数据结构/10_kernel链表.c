#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<stdbool.h>
#include"Kernel_List.h"

typedef struct Students
{
    char name[32];
    int age;

} DataType;

typedef struct Node
{
    DataType data;
    
    struct list_head ptr_domain;//这里用的是内核链表的小结构体，里面存了两个指针

}Node;

typedef struct list_head Head;

/********************链表操作列表函数***********************
 * 1.初始化链表
 * 2.创建结点
 * 3.获取数据
 * 4.头插入链表
 * 5.尾插入链表
 * 6.遍历链表
 * 7.销毁链表
 * 
 * 
 * 
***********************************************************/

//====================函数列表========================
Node * Creat_Node(DataType * newdata);//初始化链表头
DataType * Get_DataType(void);//获取数据
bool Judge_loop(void);//判断循环是否继续
void Display_List(Head * head,void (* handle)(Node * ptr));//遍历显示链表(要用钩子函数)
void displayInformation(Node * data);//显示当前成员函数,被遍历显示调用
bool Judge_age(Node * Src,Node * Tag);//判断年龄是否相等

//===================================================

int main()
{
    //1.初始化链表头
    LIST_HEAD(HEAD);//创建了一个小结构体
    struct list_head * head = &HEAD;

    //2.头插创建链表
    while(Judge_loop())
    {
        Node * ptr_newnode=NULL;
        DataType * NewData=Get_DataType();
        ptr_newnode=Creat_Node(NewData);
        list_add(&ptr_newnode->ptr_domain,head);
        free(NewData);
    }

    //6.遍历链表(这里要进行指针转换来访问数据)
    Display_List(head,displayInformation);


    return 0;
}


Node * Creat_Node(DataType * newdata)
{
    Node * ptr=(Node *)calloc(1,sizeof(Node));

    //初始化数据域
    if(newdata)
    {
        memcpy(&ptr->data,newdata,sizeof(DataType));
    }

    //初始化指针域
    INIT_LIST_HEAD(&ptr->ptr_domain);

    return ptr;

}

DataType * Get_DataType(void)
{
    DataType * num=(DataType *)calloc(1,sizeof(DataType));

    //录入名字
    printf("请输入姓名:\n");
    fgets(num->name,sizeof(num->name),stdin);
    num->name[strlen(num->name)-1]='\0';

    //录入年龄
    printf("请输入年龄:\n");
    scanf("%d",&num->age);
    while(getchar()!='\n');

    return num;
}

bool Judge_loop(void)
{
    int judge=0;
    printf("是否要继续(0结束循环)\n");
    scanf("%d",&judge);
    while(getchar()!='\n');
    return judge;
}

void Display_List(Head * head, void (* handle)(Node * ptr))
{
    if(head->next==head)
    {
        printf("链表为空...\n");
        return;
    }

    Node * tmp=NULL;
    list_for_each_entry(tmp,head,ptr_domain)//这里用list_for_each_entry是将小结构体指针转化为大结构体指针
    {                                      //，每次小结构体偏移后，转化并用大结构体进行操作,member是大结构体的指针域
        displayInformation(tmp);
    }

    return ;
}

void displayInformation(Node * data)
{
    printf("===========================\n");
    printf("姓名:%s\n",data->data.name);
    printf("年龄:%d\n",data->data.age);
    printf("===========================\n");
    return;
}

bool Judge_age(Node * Src,Node * Tag)
{
    return (Src->data.age>=Tag->data.age);
}