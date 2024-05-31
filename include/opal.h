#ifndef OPAL_H
#define OPAL_H

#ifndef NULL
  #define NULL (void*)0
#endif
#define EOF -1

  
#define OPAL_PI 3.141592653589793238462643383279502884197169399375105820
#define OPAL_E 2.71828182845904523536028747135266249775724709369995957
#define OPAL_TAU 6.2831853071795864769252867665590057683943387987502116
  
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <values.h>
#include <limits.h>
#include <assert.h>
#include <errno.h>
#include <time.h>
#include <ctype.h>
  
#include "opal_malloc.h"
#include "opal_list.h"
#include "./lib/opal_datetime.h"
#include "./objects/opal_int.h"
#include "./objects/opal_string.h"
#include "opal_io.h"
#include "./opal/opal_position.h"
#include "./opal/opal_fs.h"
#include "./opal/opal_error.h"
void opal_main(int argc, char**argv);
#endif