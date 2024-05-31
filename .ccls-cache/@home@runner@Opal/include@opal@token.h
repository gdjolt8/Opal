#ifndef OP_OPAL_TOKEN_H
#define OP_OPAL_TOKEN_H

typedef struct
{
  char *value;
  enum {

    EOF = 0,
    INTEGER_LITERAL,
    FLOAT_LITERAL,
    STRING_LITERAL,
    CHAR_LITERAL,
    BOOLEAN_LITERAL,

    LBRACE, RBRACE, LPAREN, RPAREN, LSQB, RSQB,
    COMMA, DOT, SEMICOLON,
    PLUS, MINUS, STAR, SLASH,

    AND, OR, NOT,
    EQUAL, NOT_EQUAL, EQ_EQ,
    LESS, GREATER, LESS_EQUAL, GREATER_EQUAL,
    PLUS_EQUAL, MINUS_EQUAL, STAR_EQUAL, SLASH_EQUAL,
    ANDAND, OROR,
  } type;
} OpalToken_T;

OpalToken_T *init_token (char *value, int type);
char *token_to_string(OpalToken_T *t);
#endif