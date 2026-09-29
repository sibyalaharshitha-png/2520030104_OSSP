#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    int fd[2];
    pid_t pid;

    /* Part 1: Producer-Consumer */
    pipe(fd);

    pid = fork();

    if (pid < 0)
    {
        perror("fork");
        return 1;
    }

    if (pid == 0)
    {
        char buffer[100];

        close(fd[1]);

        read(fd[0], buffer, sizeof(buffer));

        printf("Child received: %s\n", buffer);

        close(fd[0]);
        return 0;
    }
    else
    {
        char message[] = "Hello from Parent";

        close(fd[0]);

        write(fd[1], message, sizeof(message));

        close(fd[1]);

        wait(NULL);
    }

    /* Part 2: ls -l | grep ".c" */

    pipe(fd);

    pid = fork();

    if (pid == 0)
    {
        close(fd[0]);

        dup2(fd[1], STDOUT_FILENO);

        close(fd[1]);

        execlp("ls", "ls", "-l", NULL);

        perror("ls");
        exit(1);
    }

    pid_t grep_pid = fork();

    if (grep_pid == 0)
    {
        close(fd[1]);

        dup2(fd[0], STDIN_FILENO);

        close(fd[0]);

        execlp("grep", "grep", ".c", NULL);

        perror("grep");
        exit(1);
    }

    close(fd[0]);
    close(fd[1]);

    waitpid(pid, NULL, 0);
    waitpid(grep_pid, NULL, 0);

    return 0;
}
