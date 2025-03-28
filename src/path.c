#include <path.h>
#include <dirent.h>
#include <stdio.h>

#define NULL 0

str_arr split_path(string path){
  return split(path, ":");
}

string exec_path(str_arr path, string command){
  string res = mk_string("");
  for (size_t i = 0; i < path.length; i++){
    string dir = path.arr[i];
    DIR *d = opendir(dir.data);
    if (d){
      struct dirent *entry;

      while((entry = readdir(d))!= NULL){
        string file = mk_string(entry->d_name);
        if (string_cmp(file, command)){
          res = string_cat(string_cat(dir, mk_string("/")), file);
          closedir(d);
          return res;
        }
      }
      closedir(d);
      break;
    }
  }
  return res;
}

