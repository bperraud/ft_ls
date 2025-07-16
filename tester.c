#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int start(int, char**);

#define MAX_CMD_LEN 1024
#define MAX_OUTPUT_LEN 8192
#define MAX_CAPTURED 8192

char *ls(int argc, char *argv[]) {
    char cmd[MAX_CMD_LEN] = "ls";
    char buffer[256];

    // Allocate output buffer on heap
    char *result = malloc(MAX_OUTPUT_LEN);
    if (!result) {
        perror("malloc failed");
        return NULL;
    }
    result[0] = '\0';  // Make sure it's null-terminated

    // Build the command string with arguments
    for (int i = 1; i < argc; i++) {
        strncat(cmd, " ", MAX_CMD_LEN - ft_strlen(cmd) - 1);
        strncat(cmd, argv[i], MAX_CMD_LEN - ft_strlen(cmd) - 1);
    }
    ft_strncat(cmd, " -C", MAX_CMD_LEN - ft_strlen(cmd) - 1);

    FILE *pipe = popen(cmd, "r");
    if (!pipe) {
        perror("popen failed");
        free(result);
        return NULL;
    }

    while (fgets(buffer, sizeof(buffer), pipe) != NULL) {
        ft_strncat(result, buffer, MAX_OUTPUT_LEN - ft_strlen(result) - 1);
    }

    pclose(pipe);
    return result;
}


int main(int argc, char **argv) {
    int pipefd[2];
    char buffer[MAX_CAPTURED] = {0};

    // Step 1: Create a pipe
    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(1);
    }

    // Step 2: Backup original stdout and stderr
    int saved_stdout = dup(fileno(stdout));
    int saved_stderr = dup(fileno(stderr));
    if (saved_stdout == -1 || saved_stderr == -1) {
        perror("dup");
        exit(1);
    }

    // Step 3: Redirect both stdout and stderr to the pipe's write end
    dup2(pipefd[1], fileno(stdout));
    dup2(pipefd[1], fileno(stderr));
    close(pipefd[1]); // Close write end in parent

    // Step 4: Emit some test output to both stdout and stderr
    start(argc, argv);

    fflush(stdout);
    fflush(stderr);

    // Step 5: Restore original stdout and stderr
    dup2(saved_stdout, fileno(stdout));
    dup2(saved_stderr, fileno(stderr));
    close(saved_stdout);
    close(saved_stderr);

    // Step 6: Read from the pipe
    ssize_t len = read(pipefd[0], buffer, sizeof(buffer) - 1);
    close(pipefd[0]); // Close read end
    //

    char * ls_result = ls(argc, argv);

    if (len > 0) {
        buffer[len] = '\0'; // Null-terminate
        printf("%s", ls_result);
        printf("---------------\n%s", buffer);
    } else {
        printf("Nothing captured.\n");
    }

    free(ls_result);

    return 0;
}

