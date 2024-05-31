#ifndef OPAL_IO_H
#define OPAL_IO_H

#include "../opal.h"
char* read_file_fs(const char* path_name);
size_t len_file_fs(const char* path_name);
void write_file_fs(const char* path_name, char* contents);
void shell_cmd_fs(const char* cmd);

#endif