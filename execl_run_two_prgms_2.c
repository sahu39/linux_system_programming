#include<stdio.h>
#include<unistd.h>
#include<string.h>
int main(int argc,char *argv[0])
{

    int pid,err,num_times;
    char num_str[5];
    if(argc==1)
    {
        printf("Taken loop maximum times 10\n");
        num_times = 10;
        sprintf(num_str,"%d",num_times);
    }
    else
    {
        strcpy(num_str,argv[1]);
        printf("num_time_str is %s\n",num_str); 
    //    pid = fork();
    }
    pid = fork();


//    pid=fork();
    /* child process*/
    if(pid==0)
    {
        printf("Child process is running hello_world process.\n");
        err = execl("./hello_world","./hello_world",(char *)0);
        printf("error %d\n",err);
        perror("execl error:");
        printf("This would not print\n");
    }
    else
    {
        sleep(3);
        printf("Parent process is running while_loop process.\n");
        execl("./while_loop_2","./while_loop_2",(char *)num_str,(char *)0);
        printf("This would not print\n");
    }
    return 0;
}
