#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <dir.h>

 

// my imports
#include <fat_string.h>
#include <constants.h>

void read_init(void){
    read_history(".history");
    using_history();
}


void read_save(void){
    write_history(".history");
}

string Read(char* buffer){
    string pmpt = string_cat(current_dir(), mk_string(" "));
    buffer = readline(c_str(pmpt));
    add_history(buffer);
    return mk_string(buffer);
}
