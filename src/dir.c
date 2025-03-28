#include <unistd.h>
#include <pwd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <dir.h>
#include <fat_string.h>


string current_dir(void) {
    char cwd[1024];

    if (getcwd(cwd, sizeof(cwd)) == NULL) {
        perror("getcwd failed");
        return mk_string("");
    }

    struct passwd *pw = getpwuid(getuid());
    if (!pw || !pw->pw_dir) {
        return mk_string(cwd);
    }


    if (strcmp(cwd, pw->pw_dir) == 0) {
        return mk_string("~");
    }

    string result = mk_string(cwd);
    string replaced = replace(result, pw->pw_dir, "~");

    return replaced;
}

