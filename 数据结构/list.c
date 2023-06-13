#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#define MaxLength 30

//将要存入的数据取一个别名，便于修改
typedef struct{
    char name[20];
    char class[20];
    int grade;

}DataType;

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

//显示顺序表函数,还要判断顺序表是否为空
void Display(Data *p)
{
    if(p->lastSubscript==-1)
    {
        printf("顺序表为空....\n");
        return ;
    }
    for(int i=0;i<=p->lastSubscript;i++)
    {
        printf("=================\n");
        printf("第%d个学生:\n",i+1);
        // printf("姓名:%s\n",(p->ptr+i)->name);
        // printf("班级:%s\n",(p->ptr+i)->class);
        printf("成绩:%d\n",(p->ptr+i)->grade);
        printf("=================\n");
    }
    printf("显示结束.....\n");

}

//显示对应下标成员,传入管理结构体指针以及对应下标
void Displaymember(Data*p,int i)
{
    printf("=================\n");
    printf("第%d个学生:\n",i+1);
    // printf("姓名:%s\n",(p->ptr+i)->name);
    // printf("班级:%s\n",(p->ptr+i)->class);
    printf("成绩:%d\n",(p->ptr+i)->grade);
    printf("=================\n");

}

//右移左移函数,接收三个参数，一个是管理结构体指针，一个是判断左移右移模式，还有是需要移位的下标
void MOVE(Data *p,char r_or_l,int index)
{
    if(r_or_l=='r')
    {
        for(int i=p->lastSubscript;i>=index;i--)
        {
            // p->ptr[i+1]=p->ptr[i];
            memcpy(p->ptr+i+1,p->ptr+i,sizeof(DataType));
        }
        printf("右移结束....\n");

    }else if(r_or_l=='l')
    {
        for(int i=index;i<=p->lastSubscript;i++)
        {
            // p->ptr[i]=p->ptr[i+1];
            memcpy(p->ptr+i,p->ptr+i+1,sizeof(DataType));
        }
        printf("左移结束....\n");

    }else{
        printf("左移右移出错....\n");
        return;
    }
}

//排序函数,传入管理结构体指针以及当前录入的下标,便录入数据边排序
//依照成绩进行排序
void DataSort(Data *p,int index)
{
    DataType *m=(DataType*)calloc(1,sizeof(DataType));
    memcpy(m,p->ptr+index,sizeof(DataType));
    for(int i=0;i<=p->lastSubscript;i++)
    {
        if(((p->ptr+i)->grade)>((p->ptr+index)->grade))
        {
            MOVE(p,'r',i);
            memcpy(p->ptr+i,m,sizeof(DataType));
        }
    }
    free(m);
    return ;
}

//删除函数,传入管理结构体指针,以及所要删除的节点数据，删除后所有数据自动前移
void DelData(Data*p,int index)
{
    index--;//这里传入的数据是经过偏移的
    //判断t是否超出范围
    if(index<0||index>p->lastSubscript)
    {
        printf("输入的下标超出范围......\n");
        return;
    }
    MOVE(p,'l',index);
    p->lastSubscript--;//这里删除了一位，需要减去一位
}

//二分查找数据函数,传入所需要查找的成绩，管理结构体指针，返回一个下标，返回-1表示失败
int FIND(Data*p,int g)
{
    //用于接收查找的范围
    int a=0;//下限
    int b=p->lastSubscript;//上限

    int count=0;
    int i=0;
    for(i=(p->lastSubscript)/2;g!=(p->ptr+i)->grade&&count<p->lastSubscript;i=(a+b)/2)
    {
        if(g>(p->ptr+i)->grade)
        {
            a=i+1;
        }else if(g<(p->ptr+i)->grade)
        {
            b=i-1;
        }
        count++;
    }

    //判断是否查找到
    if(count<p->lastSubscript)
    {
        printf("查找成功\n");
        return i;
    }else{
        printf("查找失败\n");
        return -1;
    }

}

//录入数据函数,返还录入成功或失败
int inputData(Data *p)
{
    if(p->lastSubscript+1>=p->maxlength)
    {
        printf("顺序表存储已满...\n");
        return -1;//满了就返还一个-1表示录入失败
    }

    int i=0;
    int isprime=0;
    DataType *member=(DataType*)calloc(1,sizeof(DataType));//用于接收输入的学生信息
    for(i=p->lastSubscript+1;i<p->maxlength;i++)
    {
        // scanf("%d",(p->ptr+i));
        // while(getchar()!='\n');//清除缓冲区


        //// 输入名字，班级以及成绩后统一复制粘贴到数据中
        // printf("请输入名字:\n");
        // fgets(member->name,20,stdin);
        // member->name[strlen(member->name)-1]='\0';

        // printf("请输入班级:\n");
        // fgets(member->class,20,stdin);
        // member->class[strlen(member->class)-1]='\0';

        printf("请输入成绩:\n");
        scanf("%d",&member->grade);
        while (getchar()!='\n');

        memcpy(p->ptr+i,member,sizeof(DataType));
        printf("已录入%d个数据\n",i+1);
        
        //调用排序函数以及显示所有信息
        DataSort(p,i);
        p->lastSubscript++;
        // Display(p);

        //判断是否要继续录入
        printf("是否要继续录入(-1结束录入)\n");
        scanf("%d",&isprime);
        while(getchar()!='\n');
        if(isprime==-1)
        {
            printf("录入结束....\n");
            break;
        }
    }
    return 0;//0表示成功
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
    char a=0;//用于判断循环退出条件
    while(1)
    {
        printf("请按顺序录入数据(结束请录入-1):\n");
        inputData(p);//录入数据函数
        Display(p);//显示所有数据函数
        printf("n键结束录入");
        scanf("%c",&a);
        while(getchar()!='\n');
        if(a=='n')
        {
            printf("结束录入....\n");
            break;
        }
    }

    //删除数据
    int t=-2;//接收节点序号
    printf("请输入所要删除的目标节点序号:\n");
    for(int i=0;;i++)
    {
        if(i==0)
        {
            scanf("%d",&t);
            while(getchar()!='\n');
        }else{
            printf("是否需要继续?(-1结束)\n");
            scanf("%d",&t);
            while(getchar()!='\n');
            if(t==-1)
            {
                break;
            }
        }
        //调用删除函数
        DelData(p,t);
        Display(p);
    }

    //调用二分查找函数
    while(1)
    {   
        int g=0;
        int num=-1;
        printf("请输入想要查找的成绩:\n");
        scanf("%d",&g);
        while(getchar()!='\n');
        num=FIND(p,g);
        if(num==-1)
        {
            continue;
        }
        Displaymember(p,num);
    }

    //显示录入的顺序表数据
    Display(p);

    //销毁掉顺序表
    free(p->ptr);
    free(p);

    return 0;
}