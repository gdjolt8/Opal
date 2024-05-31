#include "../../include/opal/opal_scanner.h"
#include "../../include/opal_strops.h"
#include <ctype.h>

OpalScanner_T* init_opal_scanner(char* source)
{
  OpalScanner_T* l = (OpalScanner_T *)opal_malloc(1, sizeof(OpalScanner_T));
  l->source = source;
  l->current_char = source[0];
  l->offset = 0;
  l->colOffset = 0;
  l->lineOffset = 0;
  l->errorCount = 0;

  return l;
}
void opal_lexer_read_next_char(OpalScanner_T* l)
{
  l->offset++;
  l->colOffset++;
  if (l->offset >= 
      strlen(l->source)) {
    l->current_char = '\0';
    return;
  }
  l->current_char = l->source[l->offset];
  if (l->current_char == '\n') {
    l->lineOffset++;
    l->colOffset = 0;
  }
}
char opal_lexer_peek(OpalScanner_T* l, int offset) {
  if (l->offset + offset >= strlen(l->source)) {
    return '\0';
  }
  return l->source[l->offset + offset];
}
void opal_lexer_scan_whitespace(OpalScanner_T* l) {
    while (l->current_char == ' ' || l->current_char == '\t' || l->current_char == '\r' || l->current_char == '\n')
    {
      opal_lexer_read_next_char(l);
    }
}
void opal_lexer_scan_comment(OpalScanner_T* l) {
    if (l->current_char == '/' && opal_lexer_peek(l, 1) == '/') {
        while (!(l->current_char == '\n'))
        {
            opal_lexer_read_next_char(l);
        }
    } else if (l->current_char == '/' && opal_lexer_peek(l, 1) == '*')
    {
        while (1) {
            if (l->current_char == '*' && opal_lexer_peek(l, 1) == '/') {
                opal_lexer_read_next_char(l);
                  opal_lexer_read_next_char(l);
                break;
            }
              opal_lexer_read_next_char(l);
        }
    }
    opal_lexer_scan_whitespace(l);
}

OpalToken_T* init_opal_token_advance(OpalScanner_T* l, OpalToken_T* t) {
    for(int i = 0; i < strlen(t->value); i++) opal_lexer_read_next_char(l);
    return t;
}
OpalToken_T* opal_lexer_scan_next_token(OpalScanner_T* l)  {
      opal_lexer_scan_whitespace(l);
      opal_lexer_scan_comment(l);

      if (isalpha(l->current_char))
      {
          return opal_lexer_scan_next_identifier(l);
      }
      if (isdigit(l->current_char)) {
          return opal_lexer_read_number_token(l);
      }

      if (l->current_char == '\"') {
          return opal_lexer_scan_next_string(l);
      }

      if (l->current_char == '\'') {
          return opal_lexer_scan_next_character(l);
      }

      OpalToken_T *token = NULL;

      switch (l->current_char)
      {
          case '+': {
              if (opal_lexer_peek(l, 1) == '='){
                  return init_opal_token_advance(l, init_opal_token("+=", PLUSEQ));
              }
              return init_opal_token_advance(l, init_opal_token("+", PLUS));
          }
          case '-': {
              if (opal_lexer_peek(l, 1) == '='){
                  return init_opal_token_advance(l, init_opal_token("-=", MINUSEQ));
              }
              return init_opal_token_advance(l, init_opal_token("-", MINUS));
          }
          case '*': {
              if (opal_lexer_peek(l, 1) == '='){
                  return init_opal_token_advance(l, init_opal_token("*=", STAREQ));
              }
              return init_opal_token_advance(l, init_opal_token("*", STAR));
          }
          case '/': {
              if (opal_lexer_peek(l, 1) == '='){
                  return init_opal_token_advance(l, init_opal_token("/=", SLASHEQ));
              }
              return init_opal_token_advance(l, init_opal_token("/", SLASH));
          }

          case '&': {
              if (opal_lexer_peek(l, 1) == '&'){
                  return init_opal_token_advance(l, init_opal_token("&&", ANDAND));
              }
              return init_opal_token_advance(l, init_opal_token("&", AMPERSAND));
          }
          case '|': {
              if (opal_lexer_peek(l, 1) == '|'){
                  return init_opal_token_advance(l, init_opal_token("||", OROR));
              }
              return init_opal_token_advance(l, init_opal_token("|", OR));
          }
          case '=': {
              if (opal_lexer_peek(l, 1) == '='){
                  return init_opal_token_advance(l, init_opal_token("==", EQEQ));
              }
              return init_opal_token_advance(l, init_opal_token("=", EQ));
          }
          case '!': {
              if (opal_lexer_peek(l, 1) == '='){
                  return init_opal_token_advance(l, init_opal_token("!=", NOTEQ));
              }
              return init_opal_token_advance(l, init_opal_token("!", NOT));
          }
          case '>': {
              if (opal_lexer_peek(l, 1) == '='){
                  return init_opal_token_advance(l, init_opal_token(">=", GREATEREQ));
              }
              return init_opal_token_advance(l, init_opal_token(">", GREATER));
          }
          case '<': {
              if (opal_lexer_peek(l, 1) == '='){
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

      fprintf(stderr, "Invalid character: (%c): (%d)", l->current_char, (int)l->current_char);
      exit(1);
  }
OpalToken_T* opal_lexer_scan_next_identifier(OpalScanner_T* l) {
      char* value = opal_malloc(1, sizeof(char));
      while (isalnum(l->current_char)) {
          value = opal_realloc(value, (strlen(value) + 2) * sizeof(char));
          strcat(value, (char[]){l->current_char, 0});
          opal_lexer_read_next_char(l); 
      }
      return init_opal_token(value, opal_token_ident_lookup(value));
  }
OpalToken_T* opal_lexer_scan_next_integer(OpalScanner_T* l) {
      char* value = opal_malloc(1, sizeof(char));

      while (isdigit(l->current_char))
      {
          value = opal_realloc(value, (strlen(value) + 2) * sizeof(char));
          strcat(value, (char[]){l->current_char, 0});
          opal_lexer_read_next_char(l);
      }

      return init_opal_token(value, INT_LITERAL);

  }
OpalToken_T* opal_lexer_scan_next_string(OpalScanner_T* l) {
      char* value = opal_malloc(1, sizeof(char));
      opal_lexer_read_next_char(l);

      while (l->current_char != '"') {
          value = opal_realloc(value, (strlen(value) + 2) * sizeof(char));
          strcat(value, (char[]){l->current_char, 0});
          opal_lexer_read_next_char(l);
      }

      opal_lexer_read_next_char(l);
      char* fmt = str_format(value);
      free(value);

      return init_opal_token(fmt, STRING_LITERAL);
  }
OpalToken_T* opal_lexer_scan_next_character(OpalScanner_T* l) {
        char* value = opal_malloc(1, sizeof(char));
        opal_lexer_read_next_char(l);

        while (l->current_char != '\'') {

            if (strlen(value) > 1)
            {
                fprintf(stderr, "Character too long\n");
                exit(1);
            }

            value = opal_realloc(value, (strlen(value) + 2) * sizeof(char));
            strcat(value, (char[]){l->current_char, 0});
            opal_lexer_read_next_char(l);
        }
        opal_lexer_read_next_char(l);
        char* fmt = str_format(value);
        free(value);

        return init_opal_token(fmt, CHAR_LITERAL);
    }
OpalToken_T* opal_lexer_read_number_token(OpalScanner_T* l) {
    OpalToken_T* int_l = opal_lexer_scan_next_integer(l);
    if (l->current_char != '.') return int_l;
    // Float literal
    opal_lexer_read_next_char(l);
    if (!isdigit(l->current_char)) {
        fprintf(stderr, "Expected integer value, got %c\n", l->current_char);
        exit(1);
    }   

    OpalToken_T* frac = opal_lexer_scan_next_integer(l);

    char* fmt = opal_malloc(strlen(int_l->value) + strlen(frac->value) + 2, sizeof(char));
    sprintf(fmt, "%s.%s", int_l->value, frac->value);
    return init_opal_token(fmt, FLOAT_LITERAL);
}
