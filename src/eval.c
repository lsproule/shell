#include <stdlib.h>
#include <stdio.h>

#include <eval.h>
#include <read.h>
#include <fat_string.h> 





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
    return mk_string("");
}



string Eval(str_arr cmd){
    if (cmd.length == 0){
        return mk_string("");
    }
    handle_command(cmd);
    return mk_string("");
} 
