#ifndef OPAL_AST_H
#define OPAL_AST_H

#include "../opal_list.h"
#include "opal_data_type.h"
typedef enum ENUM_OPAL_AST_TYPE {
  OPAL_AST_BLOCK,
  OPAL_AST_FUNCTION_CALL,
  OPAL_AST_FUNCTION_DEFINITION,
  OPAL_AST_ASSIGNMENT,
  OPAL_AST_TYPE_DEFINITION,
  OPAL_AST_VARIABLE,
  OPAL_AST_VARIABLE_DEFINITION,
  OPAL_AST_RETURN_STATEMENT,
  OPAL_AST_IF_STATEMENT,
  OPAL_AST_WHILE_STATEMENT,
  OPAL_AST_FOR_STATEMENT,
  OPAL_AST_ARRAY,
  OPAL_AST_TYPE,
  OPAL_AST_INTEGER,
  OPAL_AST_FLOAT,
  OPAL_AST_BOOLEAN,
  OPAL_AST_CHAR,
  OPAL_AST_STRING,
  OPAL_AST_BINOP,
  OPAL_AST_UNOP,
  OPAL_AST_VOID
} OpalAst_Type;

typedef struct OPAL_AST_STRUCT {
  OpalAst_Type opal_ast_type;
  OpalList_T *opal_block_children;

  struct OPAL_AST_STRUCT *opal_function_call_ident;
  OpalList_T *opal_function_call_arguments;
  struct OPAL_AST_STRUCT *function_definition_name;
  Opal_DataType *function_definition_type;
  OpalList_T *function_definition_params;
  struct OPAL_AST_STRUCT *function_definition_block;
  struct OPAL_AST_STRUCT *assignment_left_op;
  struct OPAL_AST_STRUCT *assignment_right_op;
  struct OPAL_AST_STRUCT *type_definition_name;
  struct OPAL_AST_STRUCT *type_definition_type;
  struct OPAL_AST_STRUCT *type_definition_block;
  struct OPAL_AST_STRUCT *variable_name;

  struct OPAL_AST_STRUCT *variable_definition_name;
  Opal_DataType *variable_definition_type;
  struct OPAL_AST_STRUCT *variable_definition_value;

  struct OPAL_AST_STRUCT *return_value;

  struct OPAL_AST_STRUCT *if_statement_condition;
  struct OPAL_AST_STRUCT *if_statement_body;

  struct OPAL_AST_STRUCT *while_statement_condition;
  struct OPAL_AST_STRUCT *while_statement_body;

  struct OPAL_AST_STRUCT *for_statement_definition; // i: int = 0
  struct OPAL_AST_STRUCT *for_statement_condition;  // i < 5
  struct OPAL_AST_STRUCT *for_statement_loop;       // i += 1
  struct OPAL_AST_STRUCT *for_statement_body;       // { i ... }

  OpalList_T *array_object_children;

  long long int_literal_value;
  long double float_literal_value;
  bool boolean_literal_value;
  char char_literal_value;
  char *string_literal_value;

  struct OPAL_AST_STRUCT *binop_left;
  int binop_op;
  struct OPAL_AST_STRUCT *binop_right;

  int unop_op;
  struct OPAL_AST_STRUCT *unop_right;
} OpalAST_T;

OpalAST_T *init_opal_ast(OpalAst_Type type);
#endif