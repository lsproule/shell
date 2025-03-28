#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>

#include <fat_string.h>


str_arr split(string s, char* delim) {
  str_arr result;
  result.length = 0;
  result.capacity = 10;
  
  result.arr = (string*)malloc(sizeof(string) * result.capacity);

  char* token = "";

  token = strtok(s.data, delim);

  if (token == NULL) {
    return result;
  }

  result.arr[result.length] = (string){token, strlen(token)};
  result.length = result.length + 1;

  while (token != NULL) {
    if (result.length == result.capacity) {
      result.arr = (string*)realloc(result.arr, sizeof(string) * result.capacity * 2);
      result.capacity = result.capacity * 2;
    }

    token = strtok(NULL, delim);

    if (token != NULL) {
      result.arr[result.length] = (string){token, strlen(token)};
      result.length = result.length + 1;
    }
  }
  return result;
}

void str_arr_free(str_arr* arr){
  free(arr->arr);
  arr->capacity = 0;
  arr->length = 0; 
}

void trimLeft(string* str){
  while (str->length > 0 && isspace(str->data[0])){
    str->data = str->data + 1;
    str->length = str->length - 1;
  } 
}

void trimRight(string* str){
  while (str->length > 0 && isspace(str->data[str->length - 1])){
    str->data[str->length - 1] = '\0';
    str->length = str->length - 1;
  }
}

void trim(string* str){
  trimLeft(str);
  trimRight(str);
}

char pop(string* str){
  char c = str->data[str->length - 1];
  str->data[str->length - 1] = '\0';
  str->length = str->length - 1;
  return c;
}
string string_cat(string a, string b){
  char* new_data = (char*)malloc(a.length + b.length + 1);
  if (!new_data){
    return mk_string("");
  }
  memcpy(new_data, a.data, a.length);
  memcpy(new_data + a.length, b.data, b.length);
  new_data[a.length + b.length] = '\0';
  return (string){new_data, a.length + b.length};
}

string replace(string str, const char *old, const char *new) {
    if (!str.data || !old || !new || strlen(old) == 0) {
        return mk_string(str.data);
    }

    size_t old_len = strlen(old);
    size_t new_len = strlen(new);

    size_t count = 0;
    char *pos = str.data;
    while ((pos = strstr(pos, old)) != NULL) {
        count++;
        pos += old_len;
    }

    if (count == 0) {
        return mk_string(str.data);
    }

    size_t new_length = str.length + (new_len - old_len) * count;
    char *new_data = (char *)malloc(new_length + 1);
    if (!new_data) {
        return mk_string("");
    }

    char *src = str.data;
    char *dest = new_data;
    while ((pos = strstr(src, old)) != NULL) {
        size_t prefix_len = pos - src;
        memcpy(dest, src, prefix_len);
        dest += prefix_len;
        memcpy(dest, new, new_len);
        dest += new_len;
        src = pos + old_len;
    }
    strcpy(dest, src);  

    return (string){new_data, new_length};
}





string str_arr_shift( str_arr *  arr){
  if (arr->length == 0){
    return (string){NULL, 0};
  };
  string result = arr->arr[0]; 
  if (arr->length == 1){
    arr->length = 0;
    return result;
  }

  for (size_t i = 0; i < arr->length - 1; i++){
    arr->arr[i] = arr->arr[i + 1];
  }
  arr->length = arr->length - 1;

  return result;
}


char* c_str(string s){
  return s.data;
}

bool string_cmp(string a, string b){
  if (a.length != b.length){
    return false;
  }
  for (size_t i = 0; i < a.length; i++){
    if (a.data[i] != b.data[i]){
      return false;
    }
  }
  return true;
}

string mk_string(const char* data){
  return (string){(char*)data, strlen(data)};
}

  

string str_arr_pop(str_arr * arr){
  if (arr->length == 0){
    return (string){NULL, 0};
  }
  string result = arr->arr[arr->length - 1];
  arr->length = arr->length - 1;
  return result; 
}

