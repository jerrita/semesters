#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void signal_handler(int sig)
{
    switch (sig)
    {
    case SIGINT:
        printf("\nGet a signal:SIGINT. You pressed ctrl+c.\n");
        break;
    case SIGQUIT:
        printf("\nGet a signal:SIGQUIT. You pressed ctrl+\\.\n");
        break;
    case SIGTSTP: //请同学们自行补充代码。
        printf("\nGet a signal:SIGTSTP. You pressed ctrl+z.\n");
        break;
    }
    exit(0);
}

int main()
{
    printf("Current process ID is %d\n", getpid());
    signal(SIGINT, signal_handler);
    signal(SIGQUIT, signal_handler);
    signal(SIGTSTP, signal_handler); //请同学们自行补充代码。
    for (;;)
        ;
}
