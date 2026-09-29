#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>

int main()
{
    int fd[2];
    pid_t p1, p2;

    pipe(fd);

    /* Producer-Consumer */
    p1 = fork();

    if (p1 == 0)
    {
        char data[] = "Hello from Parent";
        close(fd[0]);

        write(fd[1], data, sizeof(data));
        close(fd[1]);

        exit(0);
    }

    else
    {
        char buffer[100];

        close(fd[1]);

        read(fd[0], buffer, sizeof(buffer));
        printf("Consumer received: %s\n", buffer);

        close(fd[0]);
        waitpid(p1, NULL, 0);
    }

    /* ls -l | grep ".c" */
    pipe(fd);

    p2 = fork();

    if (p2 == 0)
    {
        close(fd[0]);
        dup2(fd[1], STDOUT_FILENO);
        close(fd[1]);

        execlp("ls", "ls", "-l", NULL);
        exit(1);
    }

    else
    {
        pid_t grep_pid = fork();

        if (grep_pid == 0)
        {
            close(fd[1]);
            dup2(fd[0], STDIN_FILENO);
            close(fd[0]);

            execlp("grep", "grep", ".c", NULL);
            exit(1);
        }

        close(fd[0]);
        close(fd[1]);

        waitpid(p2, NULL, 0);
        waitpid(grep_pid, NULL, 0);
    }

    return 0;
}#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>

int main()
{
    int fd[2];
    pid_t p1, p2;

    pipe(fd);

    /* Producer-Consumer */
    p1 = fork();

    if (p1 == 0)
    {
        char data[] = "Hello from Parent";
        close(fd[0]);

        write(fd[1], data, sizeof(data));
        close(fd[1]);

        exit(0);
    }

    else
    {
        char buffer[100];

        close(fd[1]);

        read(fd[0], buffer, sizeof(buffer));
        printf("Consumer received: %s\n", buffer);

        close(fd[0]);
        waitpid(p1, NULL, 0);
    }

    /* ls -l | grep ".c" */
    pipe(fd);

    p2 = fork();

    if (p2 == 0)
    {
        close(fd[0]);
        dup2(fd[1], STDOUT_FILENO);
        close(fd[1]);

        execlp("ls", "ls", "-l", NULL);
        exit(1);
    }

    else
    {
        pid_t grep_pid = fork();

        if (grep_pid == 0)
        {
            close(fd[1]);
            dup2(fd[0], STDIN_FILENO);
            close(fd[0]);

            execlp("grep", "grep", ".c", NULL);
            exit(1);
        }

        close(fd[0]);
        close(fd[1]);

        waitpid(p2, NULL, 0);
        waitpid(grep_pid, NULL, 0);
    }

    return 0;
}
