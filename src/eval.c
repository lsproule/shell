#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include <eval.h>
#include <read.h>
#include <fat_string.h> 
#include <path.h>





string handle_command(str_arr cmd){
    string cmd_name = str_arr_shift(&cmd);
    if (string_cmp(cmd_name, mk_string("exit"))){
        read_save();
        if (cmd.length == 0){
            exit(0);
        }
        int status = atoi(cmd.arr[1].data);
        exit(status);
    }
    if (string_cmp(cmd_name, mk_string("cd"))){
        if (cmd.length == 0){
            return mk_string("");
        }
        string path = cmd.arr[0];
        chdir(path.data);
        return mk_string("");
    }


    string path_var = mk_string(getenv("MY_PATH"));

    str_arr path = split_path(path_var);
    string bin_path = exec_path(path, cmd_name); 

    if (bin_path.length == 0){
        return mk_string("Command not found");
    }
    printf("Executing %s\n", bin_path.data);
    execute_with_output(c_str(bin_path), carr(cmd));
    return mk_string("");
}



string Eval(str_arr cmd){
    if (cmd.length == 0){
        return mk_string("");
    }
    handle_command(cmd);
    return mk_string("");
} 

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void execute_with_output(char *bin_path, char **cmd) {
    int pipefd[2];  // Pipe for stdout and stderr
    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    pid_t pid = fork();
    if (pid < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {  // Child process
        close(pipefd[0]);  // Close read end of the pipe

        // Redirect stdout and stderr to the write end of the pipe
        dup2(pipefd[1], STDOUT_FILENO);
        dup2(pipefd[1], STDERR_FILENO);
        close(pipefd[1]);  // Close original file descriptor

        execv(bin_path, cmd);
        perror("execv");  // execv only returns on error
        exit(EXIT_FAILURE);
    } else {  // Parent process
        close(pipefd[1]);  // Close write end of the pipe

        char buffer[1024];
        ssize_t n;
        while ((n = read(pipefd[0], buffer, sizeof(buffer) - 1)) > 0) {
            buffer[n] = '\0';  // Null-terminate output
            printf("%s", buffer);
        }
        close(pipefd[0]);

        // Wait for child process to finish
        int status;
        waitpid(pid, &status, 0);
        if (WIFEXITED(status)) {
            printf("\nProcess exited with status: %d\n", WEXITSTATUS(status));
        } else {
            printf("\nProcess terminated abnormally\n");
        }
    }
}

