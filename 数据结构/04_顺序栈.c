#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include <string.h>

#define TRUE 1
#define FALSE 0
#define SIZE 20

typedef char DataType;

typedef struct Stack
{
    DataType * Data;
    int size;
    int top;
}Stack;

//====================函数列表========================

Stack * InitStack();//初始化栈
void Pop(Stack * stack,DataType * NewData);//入栈,传入管理结构体指针，与要传入DataType类型数据指针，不返回值
// DataType * Push(Stack *stack);//出栈,返还栈顶的数据
DataType * Top(Stack * stack);//取得栈顶元素，返还栈顶的数据指针
// void DestoryStack(Stack * stack);//销毁栈
DataType GetData();//得到新数据，返还一个int数据，但传完值后要销毁,只能录入单个int型数据
int Judge_Full(Stack * S);//判断是否继续，输入的指针判断是否栈满，1为真，0为假
int Judge_Empty(Stack * S);//同上，但判断栈是否为空
DataType Top_Judge(Stack * stack);//判断数字与非数字，输入char型，用ascii码来判断，返还弹出的值,传入管理栈结构体指针
DataType Get_Data_char();//获得新数据，char类型的，返还一个char类型数据
int Judge(void);//判断循环是否继续

//====================================================

int main()
{
    //初始化栈
    Stack * stack_sequence=InitStack();

    //入栈操作
    while(Judge_Full(stack_sequence))
    {   
        DataType newdata=GetData();
        Pop(stack_sequence,&newdata);
        printf("入栈元素:%c\n",*(stack_sequence->Data+stack_sequence->top));
    }

    //进行数据压入操作，弹出非数字
    Top_Judge(stack_sequence);

    // //显示一下栈顶数据
    // DataType * num=Top(stack_sequence);
    // if(num==NULL)
    // {
    //     printf("显示栈失败...\n");
    // }else{
    //     printf("栈顶为:%d\n",*num);
    // }

    //出栈操作,顺便输出内容
    while(Judge_Empty(stack_sequence))
    {
        Top(stack_sequence);
        stack_sequence->top--;
    }


    //释放内存
    free(stack_sequence->Data);
    free(stack_sequence);

    return 0;
}


Stack * InitStack()
{
    //创建栈的管理结构体
    Stack * ptr=(Stack*)calloc(1,sizeof(Stack));
    if(ptr==NULL)
    {
        perror("stack error...\n");
        return NULL;
    }

    //初始化管理结构体的各个参数
    ptr->size=SIZE;
    ptr->top=-1;
    ptr->Data=(DataType*)calloc(SIZE,sizeof(DataType));
    if(ptr->Data==NULL)
    {
        perror("Data error...\n");
        return NULL;
    }

    return ptr;
}

void Pop(Stack * stack,DataType * NewData)
{
    //判断空间是否已满
    if(stack->top+1>=stack->size)
    {
        printf("栈已满...\n");
        return;
    }

    //top先自加
    stack->top++;

    //新内存拷贝
    memcpy(stack->Data+stack->top,NewData,sizeof(DataType));

    return;

}

DataType GetData()
{
    DataType data=0;
    printf("请输入数据:\n");
    scanf("%c",&data);
    while(getchar()!='\n');

    return data;

}

int Judge_Full(Stack * S)
{
    if(S->top+1==S->size)
    {
        printf("栈已满...\n");
        return FALSE;
    }
    
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

int Judge_Empty(Stack * S)
{
    if(S->top==-1)
    {
        // printf("栈已空...\n");
        return FALSE;
    }
    return TRUE;
}

DataType * Top(Stack * stack)
{
    if(stack->top==-1)
    {
        printf("栈已空...\n");
        return NULL;
    }
    //显示栈顶数据
    DataType * tmp = stack->Data+stack->top;
    printf("成员数据为:%c\n",*tmp);

    return tmp;
}

DataType Top_Judge(Stack * stack)//先录入再判断是否要弹出
{
    //压入操作
    while(Judge())
    {
        DataType NewData=GetData();
        Pop(stack,&NewData);
        printf("入栈元素:%c\n",*(stack->Data+stack->top));

        //判断是否为非数字
        // if(*Top(stack)<'0'||*Top(stack)>'9')
        if(*(stack->Data+stack->top)<'0'||*(stack->Data+stack->top)>'9')
        {
            printf("已弹出非数字%c\n",*(stack->Data+stack->top));
            stack->top--;
        }
    }

    return 0;

}

// DataType Get_Data_char()
// {

// }

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