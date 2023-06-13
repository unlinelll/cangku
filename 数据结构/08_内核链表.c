//先定义DATATYPE的数据类型
#define DATATYPE struct Student\
        {\
            char name [32];\
            int age; \
        }\

#include "corelist.h"

//===================函数列表====================
bool Judge_data(datatype * p1 ,datatype * p2);//判断年龄是否相等
void Read_data(datatype * data);//读取信息函数
datatype * Get_data(); //录入结点数据信息,涉及内存申请，注意要释放
bool Judge();//判断循环是否继续
//==============================================

int main()
{
    //  初始化链表
    Node * head=InitList();

    // 头插输入数据，先录入数据,再创建结点，最后用头插法插入
    while(Judge())
    {
        datatype * new_data=Get_data();
        Node * new_node=_newNode(new_data);
        // printf("名字:%s\n",new_node->data.name);
        free(new_data);
        listadd_head(head,new_node);
        // ergodic(head,Read_data);
    }

    //遍历链表
    ergodic(head,Read_data);

    //查找数据
    printf("请输入需要查找的数据\n");
    int newdata;
    scanf("%d",&newdata);
    while(getchar()!='\n');
    datatype data={0};
    data.age=newdata;

    Node * ptr=list_find(head,&data,Judge_data);
    if(ptr==head)
    {
        printf("没找到...\n");
    }else{
        printf("找到了...\n");
        Read_data(&ptr->data);
    }

    //销毁链表
    Destory_list(head);
    free(head);
}

bool Judge_data(datatype * p1 ,datatype * p2)
{
    return (p1->age==p2->age);
}

void Read_data(datatype * data)
{
    printf("学生姓名:%s\n",data->name);
    printf("年龄:%d\n",data->age);
    return;
}

datatype * Get_data()
{
    //申请一块内存
    datatype * ptr=(datatype *)calloc(1,sizeof(datatype));
    if(ptr==NULL)
    {
        perror("data apply error...\n");
        return NULL;
    }

    //录入数据
    printf("请输入姓名:\n");
    fgets(ptr->name,sizeof(ptr->name),stdin);
    ptr->name[strlen(ptr->name)-1]='\0';

    //录入年龄
    printf("请输入年龄:\n");
    scanf("%d",&ptr->age);
    while(getchar()!='\n');

    return ptr;

}


bool Judge()
{
    int judge=-1;
    printf("是否继续(0键结束)\n");
    scanf("%d",&judge);
    while(getchar()!='\n');

    if(judge==0)
    {
        return 0;
    }else{
        return 1;
    }

}