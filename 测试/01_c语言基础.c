#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>

/***************************
 * 这里用于测试scanf的输入缓冲
 * 测试，scanf在遇到不符合格式的
 * 数据时会读取失败然后将输入的
 * 数据留在输入缓冲区，不会清除
 * 可能会导致下一次的错误读取
*****************************/


// int main()
// {
//     int num=0;
//     char zimu='1';
//     printf("请输入数字与字母 :\n");
//     int judge =scanf("%d %c",&num ,&zimu);

//     printf("数字与字母:%d\t%c\n",num,zimu);
//     printf("scanf成功输入%d次\n",judge);

//     printf("请输入字母:\n");
//     char zimu2='1';
//     judge=scanf("%c",&zimu2);
//     printf("字母为:%c\n",zimu2);
//     printf("scanf成功输入%d次\n",judge);

//     return 0;
// }


/*********************************
 * 用于测试printf的输出的行缓冲模式
 * 在遇到死循环时，若printf中没有换行符
 * 则可能会导致内容无法输出，输出缓冲
 * 会在进程结束，遇到换行符或者缓冲区满
 * 才会输出
 * 
***********************************/


int main ()
{

    while(1)
    {
        usleep(5000);
        printf("sleep");
    }

    return 0;

}