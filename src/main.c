#include <stdbool.h>
#include <stdio.h>

#include <read.h>
#include <eval.h>
#include <constants.h>
#include <fat_string.h>







int main(void){
    char buffer[BUFF_SIZE];
    bool quit = false;
    read_init();

    while (!quit){
        string buff = Read(buffer);
        trim(&buff);
        str_arr cmd = split(buff, " ");
        string output = Eval(cmd);
        printf("%s\n", output.data);
    }
    read_save();
    return 0;
}
