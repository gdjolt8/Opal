#include "../../include/opal/opal_data_type.h"
#include "../../include/opal.h"
Opal_DataType *init_opal_data_type(Op_DataType type) {
  Opal_DataType *data_type = opal_malloc(1, sizeof(Opal_DataType));
  data_type->type = type;
  return data_type;
}
Opal_DataType * opal_data_type_name_to_enum(char* type_name)
{
  Opal_DataType *data_type = 
}