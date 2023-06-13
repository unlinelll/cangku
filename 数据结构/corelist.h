#ifndef _CORELIST_
#define _CORELIST_

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<stdbool.h>

/***********************************************
 *          带头结点的通用性链表
 * 1.在使用include包括该头文件时需要先定义DATATYPE的
 * 类型
 * 2.
 * 
 * 
 * 
************************************************/

#ifndef DATATYPE
#define DATATYPE int  // 这里是如果未定义数据类型则将数据类型定义为默认的int类型数据
#endif

typedef DATATYPE datatype;

typedef struct Node
{
    datatype data;
    struct Node * Prev;
    struct Node * Next;
}Node;

//================函数列表(这里需要用静态修饰符来限定函数作用范围)========================
static Node * InitList();//1.链表的初始化
static Node * _newNode(datatype * NewData);//2.创建新结点
static void listadd_head(Node * head, Node * newdata);//3.结点的插入(头插法)
static void listadd_tail(Node * head, Node * newdata);//3.结点的插入(尾插法)
static Node * delNode(Node * deldata);//4.结点的删除
static Node * list_find(Node * head , datatype * find_data , bool (* equal)(datatype * p1,datatype * p2));//5.查找结点（要回调判断数据相等的函数）
static int ergodic(Node * head,void (* interview)(datatype *));//6.遍历链表（回调访问函数）
static bool isEmpty(Node * node);//7.判断链表是否为空
static void Destory_list(Node * head);//8.销毁链表
//=====================================================================================

//1.初始化链表
static Node * InitList()
{
    //申请一块内存
    Node * ptr =(Node *)calloc(1,sizeof(Node));
    if(ptr!=NULL)
    {
        //初始化链表头结点数据
        ptr->Next=ptr->Prev=ptr;
    }
   
    return ptr;
}

//2.创建新结点
static Node * _newNode(datatype * NewData)
{
    //申请内存
    Node * tmp = (Node *)calloc(1,sizeof(Node));
    if(tmp!=NULL)
    {
        //初始化结点
        tmp->Next=tmp;
        tmp->Prev=tmp;

        //拷贝数据
        memcpy(&(tmp->data),NewData,sizeof(datatype));

    }
    return tmp;

}

//3.结点头插入
static void listadd_head(Node * head, Node * newdata)
{
    //先动新结点前后指针，再动前后指针
    newdata->Next=head->Next;
    newdata->Prev=head;

    head->Next->Prev=newdata;
    head->Next=newdata;

    return;
}

//3.结点尾插入
static void listadd_tail(Node * head, Node * newdata)
{
    //先动新结点前后指针，再动前后指针
    newdata->Next=head;
    newdata->Prev=head->Prev;

    head->Prev->Next=newdata;
    head->Prev=newdata;

    return;
}

//4.结点的删除,返还一个指针指向被拆出的结点,需要外面手动释放
static Node * delNode(Node * deldata)
{
    //先要判断是否为空链表,这里只需要传一个指针
    if(deldata==NULL||isEmpty(deldata))
    {
        return NULL;
    }

    Node * ptr=deldata;

    deldata->Prev->Next=deldata->Next;
    deldata->Next->Prev=deldata->Prev;

    deldata->Next=deldata;
    deldata->Prev=deldata;

    return ptr;
}

//5.查找结点,要传入一个可以判断数据是否相等的函数指针(这里可以不需要完全匹配的)
static Node * list_find(Node * head , datatype * find_data , bool (* equal)(datatype * p1,datatype * p2))
{
    //查找函数
    Node * tmp=head->Next;
    while(tmp!=head)
    {
        if(equal(&tmp->data,find_data))
        {
            break;
        }
        tmp=tmp->Next;
    }

    return tmp;
}

//6.遍历输出链表,返还链表长度,调用一个访问数据函数
static int ergodic(Node * head,void (* interview)(datatype *))
{
    //判断链表是否为空
    if(isEmpty(head))
    {
        return 0;
    }

    int j=0;
    Node * tmp =NULL;
    //遍历输出链表
    for(tmp=head->Next;tmp!=head;tmp=tmp->Next)
    {
        // printf("读取了一次...\n");
        interview(&tmp->data);
        j++;
    }

    return j;
}

//7.判断链表是否为空,用是否指向自己判断
static bool isEmpty(Node * node)
{

    return (node->Next==node);
    
}

//8.销毁链表
static void Destory_list(Node * head)
{
    //先删除再释放,不会释放头结点
    Node * tmp=NULL;
    Node * ptr=NULL;
    for(tmp=head->Next;tmp!=head;tmp=ptr)
    {
        ptr=tmp->Next;
        free(delNode(tmp));                
    }
    return ;
}


#endif