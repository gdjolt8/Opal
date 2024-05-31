#ifndef OPAL_SCANNER_H
#define OPAL_SCANNER_H

#include <stdio.h>
#include "opal_token.h"
#include "../opal.h"
typedef struct OPAL_SCANNER_T {
    char* source;
    const char *directory; 

    int current_char;
    size_t charOffset;
    size_t colOffset;
    size_t lineOffset;
    OpalList_T *error_list;
} OpalScanner_T;

OpalScanner_T* init_opal_scanner(char* source, const char *directory);
void opal_scanner_read_next_char(OpalScanner_T* l);
char opal_scanner_peek(OpalScanner_T* l, int offset);
void opal_scanner_scan_whitespace(OpalScanner_T* l);
void opal_scanner_scan_comment(OpalScanner_T* l);
OpalToken_T* opal_scanner_scan_next_token(OpalScanner_T* l);
OpalToken_T* opal_scanner_scan_next_identifier(OpalScanner_T* l);
OpalToken_T* opal_scanner_scan_next_integer(OpalScanner_T* l);
OpalToken_T* opal_scanner_scan_next_string(OpalScanner_T* l);
OpalToken_T* opal_scanner_scan_next_character(OpalScanner_T* l);
OpalToken_T* opal_scanner_read_number_token(OpalScanner_T* l);

#endif