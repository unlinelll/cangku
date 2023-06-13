#include<stdlib.h>

char * init(void);

int main()
{
    char *q=init();
    free(q);

    return 0;
}

char * init()
{
    char *p=(char* )calloc(1,sizeof(char));
    return p;

}