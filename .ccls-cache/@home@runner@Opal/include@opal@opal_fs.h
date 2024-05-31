#ifndef OPAL_FS_H
#define OPAL_FS_H

#include "../opal.h"

/*typedef struct STRUCT_OPAL_FILE
{
  FILE *fp;
  char *text;
} OpFile_T;*/
char* read_file_fs(const char* path_name);
size_t len_file_fs(const char* path_name);
void write_file_fs(const char* path_name, char* contents);
void shell_cmd_fs(const char* cmd);

#endif