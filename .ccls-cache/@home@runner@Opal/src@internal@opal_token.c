#include "../../include/opal/opal_token.h"

OpalToken_T tokens[] = {{ILLEGAL, "ILLEGAL"},
                        {EOF, "EOF"},
                        {IDENT, "IDENT"},
                        {INT_LITERAL, "INTEGER"},
                        {FLOAT_LITERAL, "FLOAT"},
                        {STRING_LITERAL, "STRING"},
                        {CHAR_LITERAL, "CHAR"},

                        {PLUS, "+"},
                        {MINUS, "-"},
                        {STAR, "*"},
                        {SLASH, "/"},
                        {LPAREN, "("},
                        {RPAREN, ")"},
                        {LSQB, "["},
                        {RSQB, "]"},
                        {LBRACE, "{"},
                        {RBRACE, "}"},
                        {AMPERSAND, "&"},
                        {NOT, "!"},
                        {OR, "|"},
                        {COMMA, ","},
                        {DOT, "."},
                        {COLON, ":"},
                        {ANDAND, "&&"},
                        {OROR, "||"},

                        {PLUSEQ, "+="},
                        {MINUSEQ, "-="},
                        {STAREQ, "*="},
                        {SLASHEQ, "/="},

                        {EQEQ, "=="},
                        {NOTEQ, "!="},
                        {EQ, "="},
                        {SEMI, ";"},
                        {GREATER, ">"},
                        {GREATEREQ, ">="},
                        {LESS, "<"},
                        {LESSEQ, "<"},

                        {KW_BREAK, "break"},
                        {KW_CONST, "const"},
                        {KW_CONTINUE, "continue"},
                        {KW_ELSE, "else"},
                        {KW_FOR, "for"},
                        {KW_FUNC, "func"},
                        {KW_IF, "if"},
                        {KW_MAP, "map"},
                        {KW_RETURN, "return"},
                        {KW_TYPE, "type"},
                        {KW_WHILE, "while"}};

OpalToken_T keywords[] = {
    {KW_BREAK, "break"},
    {KW_CONST, "const"},
    {KW_CONTINUE, "continue"},
    {KW_ELSE, "else"},
    {KW_FOR, "for"},
    {KW_FUNC, "func"},
    {KW_IF, "if"},
    {KW_MAP, "map"},
    {KW_RETURN, "return"},
    {KW_TYPE, "type"},
    {KW_WHILE, "while"}
};

OpalToken_T *init_opal_token(char *value, int type) {
  OpalToken_T *t = (OpalToken_T *)opal_malloc(1, sizeof(OpalToken_T));
  t->value = value;
  t->type = type;
  return t;
}
char *opal_token_to_string(OpalToken_T *t) {
  char *s = "";
  if (0 <= t->type && t->type < sizeof(tokens) / sizeof(OpalToken_T)) {
    for (size_t i = 0; i < sizeof(tokens) / sizeof(OpalToken_T); i++) {
      if (tokens[i].type == t->type) {
        s = opal_malloc(strlen(t->value) + strlen(tokens[i].value) + 20,
                        sizeof(char));
        sprintf(s, "token(%s, %s [%d])", t->value, tokens[i].value, t->type);
      }
    }
  }
  if (strcmp(s, "") == 0) {
    char *s = opal_malloc(strlen(tokens[t->type].value) + 1, sizeof(char));
    sprintf(s, "token(%d)", (t->type));
  }
  return s;
}
int opal_precedence(OpalToken_T *t) {
  switch (t->type) {
  case OR:
    return 1;
  case ANDAND:
    return 2;
  case EQEQ:
  case NOTEQ:
  case LESS:
  case LESSEQ:
  case GREATER:
  case GREATEREQ:
    return 3;
  case PLUS:
  case MINUS:
  case OROR:
    return 4;
  case STAR:
  case SLASH:
  case AMPERSAND:
    return 5;
  default:
    return 0;
  }
}

int opal_token_ident_lookup(char *t) {
    for (size_t i = 0; i < sizeof(keywords)/sizeof(OpalToken_T); i++)
    {   
        if (strcmp(keywords[i].value, t) == 0) { 
            return keywords[i].type;
        }
    }
    return IDENT;
}
bool opal_token_IsLiteral(OpalToken_T *t){
    return literal_beg < t->type && t->type < literal_end;
}
bool opal_token_IsOperator(OpalToken_T *t) {
    return (operator_beg < t->type && t->type < operator_end);
}
bool opal_token_IsKeyword(OpalToken_T *t) {
    return keyword_beg < t->type && t->type < keyword_end;
}
bool opal_token_IsIdentifier(OpalToken_T *t) {
    if (strcmp(t->value, "") == 0 || opal_token_IsKeyword(t)) {
        return false;
    }
    for(int i = 0; i < strlen(t->value); i++) {
        if (!isalpha(t->value[i]) && t->value[i] != '_' && (i == 0 || isdigit(t->value[i]))) {
            return false;
        }
    }
    return true;
}