#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    pid_t p1, p2;

    printf("Parent PID: %d\n", getpid());

    // Create Child 1
    p1 = fork();

    if (p1 == 0)
    {
        printf("Child 1 PID: %d\n", getpid());
        sleep(2);
        exit(0);
    }

    // Create Child 2
    p2 = fork();

    if (p2 == 0)
    {
        printf("Child 2 PID: %d\n", getpid());
        sleep(3);
        exit(0);
    }

    // wait() - waits for any child
    wait(NULL);
    printf("wait(): One child completed\n");

    // waitpid() - waits for specific child
    waitpid(p2, NULL, 0);
    printf("waitpid(): Child 2 completed\n");

    printf("No zombie process remains.\n");

    return 0;
}
