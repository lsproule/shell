#pragma once
#include <fat_string.h>


string current_dir(void);
string expand_tilde(string path);
string expand_env(string path);
