#include<stdio.h>
int main(int argc,char *argv[])
{
    int start_value = 1;
    int end_value;
    if (argc==1)
        end_value = 10;
    else
        end_value = atoi(argv[1]);
    while(start_value <= end_value)
    {
        printf("%d\t",start_value);
        start_value++;
    }
    printf("\n");
    return 0;
}
