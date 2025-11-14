#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(int argc, char* argv[]) {
    // TODO: Complete and document

    if (argc != 2) {
        printf("USAGE: partc FILEIN\n");
        return 1;
    }

    char *filename = argv[1];
    int pipefd[2];

    if (pipe(pipefd) < 0)
        return 2;

    pid_t pid = fork();
    if (pid < 0)
        return 3;

    if (pid == 0) {
        close(pipefd[0]);
        if (dup2(pipefd[1], STDOUT_FILENO) < 0)
            return 4;
        close(pipefd[1]);
        char *args[] = {"parta", filename, NULL};
        execv("./parta", args);
        return 5;
    }

    close(pipefd[1]);

    if (dup2(pipefd[0], STDIN_FILENO) < 0)
        return 6;
    close(pipefd[0]);

    char *sort_args[] = {"sort", "-t,", "-k2", "-n", NULL};
    execvp("sort", sort_args);

    return 7;
}
