#include "../../include/opal/opal_scanner.h"
#include "../../include/opal_strops.h"
#include <ctype.h>

OpalScanner_T* init_opal_scanner(char* source, const char *directory)
{
  OpalScanner_T* l = (OpalScanner_T *)opal_malloc(1, sizeof(OpalScanner_T));
  l->source = source;
  l->directory = directory;
  l->current_char = source[0];
  l->charOffset = 0;
  l->colOffset = 0;
  l->lineOffset = 0;
  l->error_list = init_list_type();
    if (l->current_char == '\n') {
        l->lineOffset++;
        l->colOffset = 0;
    }
  return l;
}

void opal_scanner_add_error(OpalScanner_T* l, const char* msg) {
    OpalError_T* err = opal_malloc(1, sizeof(OpalError_T));
    err->err_msg = (char *)msg;
    err->directory = l->directory;
    err->pos = init_opal_position(l->lineOffset, l->colOffset);
    err->err_type = OPAL_ERR_TYPE_ERROR;
    err->err_level = OPAL_ERR_SYNTAX;
    opal_add_error(err, l->error_list);
}
void opal_scanner_read_next_char(OpalScanner_T* l)
{
  l->charOffset++;
  l->colOffset++;
  if (l->charOffset >= 
      strlen(l->source)) {
    l->current_char = '\0';
    return;
  }
  l->current_char = l->source[l->charOffset];
if (l->current_char == '\n') {
        l->lineOffset++;
        l->colOffset = 0;
}
}
char opal_scanner_peek(OpalScanner_T* l, int offset) {
  if (l->charOffset + offset >= strlen(l->source)) {
    return '\0';
  }
  return l->source[l->charOffset + offset];
}
void opal_scanner_scan_whitespace(OpalScanner_T* l) {
    while (l->current_char == ' ' || l->current_char == '\t' || l->current_char == '\r' || l->current_char == '\n')
    {
      opal_scanner_read_next_char(l);
    }
}
void opal_scanner_scan_comment(OpalScanner_T* l) {
    if (l->current_char == '/' && opal_scanner_peek(l, 1) == '/') {
        while (!(l->current_char == '\n' || l->current_char == '\0'))
        {
            opal_scanner_read_next_char(l);
        }
    } else if (l->current_char == '/' && opal_scanner_peek(l, 1) == '*')
    {
        while (1) {
            if(l->current_char == '\0')
            {
                opal_scanner_add_error(l, "unterminated long comment");
                throw_opal_error(l->error_list->items[l->error_list->size-1]);
                break;
            }
            if (l->current_char == '*' && opal_scanner_peek(l, 1) == '/') {
                opal_scanner_read_next_char(l);
                opal_scanner_read_next_char(l);
                break;
            }
            opal_scanner_read_next_char(l);
        }
    }
    opal_scanner_scan_whitespace(l);
}

OpalToken_T* init_opal_token_advance(OpalScanner_T* l, OpalToken_T* t) {
    if (!t->pos){
        t->pos = init_opal_position(l->lineOffset, l->colOffset);
    }
    for(int i = 0; i < strlen(t->value); i++) opal_scanner_read_next_char(l);
    return t;
}
OpalToken_T* opal_scanner_scan_next_token(OpalScanner_T* l)  {
      opal_scanner_scan_whitespace(l);
      opal_scanner_scan_comment(l);

      if (isalpha(l->current_char))
      {
          return opal_scanner_scan_next_identifier(l);
      }
      if (isdigit(l->current_char)) {
          return opal_scanner_read_number_token(l);
      }

      if (l->current_char == '\"') {
          return opal_scanner_scan_next_string(l);
      }

      if (l->current_char == '\'') {
          return opal_scanner_scan_next_character(l);
      }

      OpalToken_T *token = init_opal_token((char[]){l->current_char, '\0'}, ILLEGAL);
        token->pos = init_opal_position(l->lineOffset, l->colOffset);
      switch (l->current_char)
      {
          case '+': {
              if (opal_scanner_peek(l, 1) == '='){
                  return init_opal_token_advance(l, init_opal_token("+=", PLUSEQ));
              }
              return init_opal_token_advance(l, init_opal_token("+", PLUS));
          }
          case '-': {
              if (opal_scanner_peek(l, 1) == '='){
                  return init_opal_token_advance(l, init_opal_token("-=", MINUSEQ));
              }
              return init_opal_token_advance(l, init_opal_token("-", MINUS));
          }
          case '*': {
              if (opal_scanner_peek(l, 1) == '='){
                  return init_opal_token_advance(l, init_opal_token("*=", STAREQ));
              }
              return init_opal_token_advance(l, init_opal_token("*", STAR));
          }
          case '/': {
              if (opal_scanner_peek(l, 1) == '='){
                  return init_opal_token_advance(l, init_opal_token("/=", SLASHEQ));
              }
              return init_opal_token_advance(l, init_opal_token("/", SLASH));
          }

          case '&': {
              if (opal_scanner_peek(l, 1) == '&'){
                  return init_opal_token_advance(l, init_opal_token("&&", ANDAND));
              }
              return init_opal_token_advance(l, init_opal_token("&", AMPERSAND));
          }
          case '|': {
              if (opal_scanner_peek(l, 1) == '|'){
                  return init_opal_token_advance(l, init_opal_token("||", OROR));
              }
              return init_opal_token_advance(l, init_opal_token("|", OR));
          }
          case '=': {
              if (opal_scanner_peek(l, 1) == '='){
                  return init_opal_token_advance(l, init_opal_token("==", EQEQ));
              }
              return init_opal_token_advance(l, init_opal_token("=", EQ));
          }
          case '!': {
              if (opal_scanner_peek(l, 1) == '='){
                  return init_opal_token_advance(l, init_opal_token("!=", NOTEQ));
              }
              return init_opal_token_advance(l, init_opal_token("!", NOT));
          }
          case '>': {
              if (opal_scanner_peek(l, 1) == '='){
                  return init_opal_token_advance(l, init_opal_token(">=", GREATEREQ));
              }
              return init_opal_token_advance(l, init_opal_token(">", GREATER));
          }
          case '<': {
              if (opal_scanner_peek(l, 1) == '='){
                  return init_opal_token_advance(l, init_opal_token("<=", LESSEQ));
              }
              return init_opal_token_advance(l, init_opal_token("<", LESS));
          }
          case '(': return init_opal_token_advance(l, init_opal_token("(", LPAREN));
          case ')': return init_opal_token_advance(l, init_opal_token(")", RPAREN));
          case '{': return init_opal_token_advance(l, init_opal_token("{", LBRACE));
          case '}': return init_opal_token_advance(l, init_opal_token("}", RBRACE));
          case '[': return init_opal_token_advance(l, init_opal_token("[", LSQB));
          case ']': return init_opal_token_advance(l, init_opal_token("]", RSQB));
          case ',': return init_opal_token_advance(l, init_opal_token(",", COMMA));
          case ';': return init_opal_token_advance(l, init_opal_token(";", SEMI));
          case ':': return init_opal_token_advance(l, init_opal_token(":", COLON));
          case '.': return init_opal_token_advance(l, init_opal_token(".", DOT));
          case 0: return init_opal_token("<EOF>", EOF);
      }

      if (token && token->type == ILLEGAL) {
          char* buf = opal_malloc(8192, sizeof(char));
          sprintf(buf, "%p (%c)", (size_t)l->current_char, l->current_char);
          OpalError_T* err = init_opal_error(buf, token->pos, l->directory, OPAL_ERR_TYPE_ERROR, OPAL_ERR_SYNTAX);
          add_element_list(err, l->error_list);
      }
      return token;
  }
OpalToken_T* opal_scanner_scan_next_identifier(OpalScanner_T* l) {
      char* value = opal_malloc(1, sizeof(char));
      while (isalnum(l->current_char)) {
          value = opal_realloc(value, (strlen(value) + 2) * sizeof(char));
          strcat(value, (char[]){l->current_char, 0});
          opal_scanner_read_next_char(l); 
      }
      return init_opal_token(value, opal_token_ident_lookup(value));
  }
OpalToken_T* opal_scanner_scan_next_integer(OpalScanner_T* l) {
      char* value = opal_malloc(1, sizeof(char));

      while (isdigit(l->current_char))
      {
          value = opal_realloc(value, (strlen(value) + 2) * sizeof(char));
          strcat(value, (char[]){l->current_char, 0});
          opal_scanner_read_next_char(l);
      }

      return init_opal_token(value, INT_LITERAL);

  }
OpalToken_T* opal_scanner_scan_next_string(OpalScanner_T* l) {
      char* value = opal_malloc(1, sizeof(char));
      opal_scanner_read_next_char(l);

      while (l->current_char != '"') {
          value = opal_realloc(value, (strlen(value) + 2) * sizeof(char));
          strcat(value, (char[]){l->current_char, 0});
          opal_scanner_read_next_char(l);
      }

      opal_scanner_read_next_char(l);
      char* fmt = str_format(value);

      return init_opal_token(fmt, STRING_LITERAL);
  }
OpalToken_T* opal_scanner_scan_next_character(OpalScanner_T* l) {
        char* value = opal_malloc(1, sizeof(char));
        opal_scanner_read_next_char(l);

        while (l->current_char != '\'') {

            if (strlen(value) > 1)
            {
                fprintf(stderr, "Character too long\n");
                exit(1);
            }

            value = opal_realloc(value, (strlen(value) + 2) * sizeof(char));
            strcat(value, (char[]){l->current_char, 0});
            opal_scanner_read_next_char(l);
        }
        opal_scanner_read_next_char(l);
        char* fmt = str_format(value);

        return init_opal_token(fmt, CHAR_LITERAL);
    }
OpalToken_T* opal_scanner_read_number_token(OpalScanner_T* l) {
    OpalToken_T* int_l = opal_scanner_scan_next_integer(l);
    if (l->current_char != '.') return int_l;
    // Float literal
    opal_scanner_read_next_char(l);
    if (!isdigit(l->current_char)) {
        fprintf(stderr, "Expected integer value, got %c\n", l->current_char);
        exit(1);
    }   

    OpalToken_T* frac = opal_scanner_scan_next_integer(l);

    char* fmt = opal_malloc(strlen(int_l->value) + strlen(frac->value) + 2, sizeof(char));
    sprintf(fmt, "%s.%s", int_l->value, frac->value);
    return init_opal_token(fmt, FLOAT_LITERAL);
}
