#ifndef OP_OPAL_TOKEN_H
#define OP_OPAL_TOKEN_H

#include "../opal.h"

enum Opal_TokenType {
  t_beg,
  ILLEGAL = 1,

  // Literals

  literal_beg,
  IDENT,
  INT_LITERAL,
  FLOAT_LITERAL,
  STRING_LITERAL,
  CHAR_LITERAL,
  literal_end,
  // Grammar
  operator_beg,
  LPAREN, RPAREN,  LSQB, RSQB, COMMA, SEMI, PLUS, MINUS, STAR, SLASH,
  PLUSEQ, MINUSEQ, STAREQ, SLASHEQ,
  AMPERSAND, OR, NOT, LESS, GREATER, LESSEQ, GREATEREQ, EQ, DOT,
  ANDAND, OROR, COLON,
  LBRACE, RBRACE, EQEQ, NOTEQ, GREATEREQUAL,
  operator_end,

  keyword_beg,
  KW_AS,
  KW_BREAK,
  KW_CONST,
  KW_CONTINUE,

  KW_ELSE,
  KW_FOR,
  KW_FUNC,
  KW_IF,

  KW_MAP,
  KW_OPERATOR,
  KW_PUBLIC,
  KW_PRIVATE,
  KW_RETURN,
  KW_TYPE,
  KW_WHILE,
  keyword_end,

  t_end
};
typedef struct 
{
  int type;
  char* value;
} OpalToken_Lit;
typedef struct
{
int type;
char *value;
OpalPosition_T* pos;
} OpalToken_T;

OpalToken_T *init_opal_token (char *value, int type);
char *opal_token_to_string(OpalToken_T *t);
int opal_precedence(OpalToken_T* t);

int opal_token_ident_lookup(char* t);
bool opal_token_IsLiteral(OpalToken_T* t);
bool opal_token_IsOperator(OpalToken_T* t);
bool opal_token_IsKeyword(OpalToken_T* t);
bool opal_token_IsIdentifier(OpalToken_T* t);
#endif