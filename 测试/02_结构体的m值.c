#include<stdio.h>


typedef struct L
{
    char a;
    int b __attribute__((aligned(4)));
    char c;

} __attribute__((packed)) L;//可能有冲突，与上面的强制转换m值
// }L;

typedef struct node
{
    char d;
    char name[32];
    char e;

}node;

int main()
{
    L st={0};
    printf("结构体大小为:%d\n",sizeof(node));
    return 0;
}

// environment---->env环境变量命令