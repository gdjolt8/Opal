#ifndef OPAL_DATA_TYPE_H
#define OPAL_DATA_TYPE_H

typedef enum
{
  DATA_TYPE_INT = 3,
  DATA_TYPE_UNSIGNED_INT,
  DATA_TYPE_FLOAT,
  DATA_TYPE_STRING,
  DATA_TYPE_CHAR,
  DATA_TYPE_BOOLEAN,
  DATA_TYPE_VOID,
  DATA_TYPE_CLASS,
  DATA_TYPE_ARRAY,
  DATA_TYPE_UNKNOWN
} Op_DataType;

typedef struct STRUCT_OP_DATATYPE {
  Op_DataType type;
  struct STRUCT_OP_DATATYPE *array_type;

} Opal_DataType;

Opal_DataType *init_opal_data_type(Op_DataType type);
Opal_DataType * opal_data_type_from_string(char* type_name);
#endif