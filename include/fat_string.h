#pragma once
#include <ctype.h>
#include <stdbool.h>

typedef struct string {
  char *data;
  size_t length;
} string;

typedef struct str_arr{
  string* arr;
  size_t length; 
  size_t capacity;

} str_arr;

string mk_string(const char* data);
void trimLeft(string*); 
void trimRight(string*); 
void trim(string*); 
char pop(string*); 
bool string_cmp(string, string);  
string string_cat(string, string);  
char* c_str(string);
char** carr(str_arr);
string replace(string, const char*, const char*);
str_arr split(string, char* delim);
string str_arr_shift(str_arr*);
string str_arr_pop(str_arr*);

