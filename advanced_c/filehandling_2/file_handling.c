#include <stdio.h>
int main()
{
    FILE *fp;

    fp=fopen("myfile","w+");
    fputs("Hi My name is Sunil\n",fp);
    long fpos=ftell(fp);
    printf("fpos=%ld\n",fpos);

    fseek(fp,14,SEEK_SET);
    fputs("Sunil Kumar Sahu\n",fp);
    fpos=ftell(fp);
    printf("fpos=%ld\n",fpos);
    fclose(fp);

    return 0;
}
