#include "../../include/opal_string.h"

#define MIN(a,b) a > b ? b : a
char* str_format(char* instr) {
  char* newstr = opal_malloc(1, sizeof(char));
  unsigned int len = strlen(instr);

  unsigned int i = 0;
  while (instr[i] != '\0' && i < len)
  {
    newstr = opal_realloc(newstr, (strlen(newstr) + 2) * sizeof(char));

    if (instr[i] == '\\')
    {
      char escape = str_to_escape_seq((char[]){ instr[i], instr[MIN(i+1, len)], 0 });
      strcat(newstr, (char[]){escape, 0});
      i += 2;
    }
    else
    {
      strcat(newstr, (char[]){instr[i], 0});
      i += 1;
    }
  }

  return newstr;
}

char str_to_escape_seq(const char* instr)
{
  if (strlen(instr) <= 1) return 0;
  if (instr[0] != '\\') return 0;
  char in_c = instr[1];

  switch (in_c)
  {
    case 'n': return '\n';
    case 't': return '\t';
    case 'r': return '\r';
    case '\\': return in_c;
    default: return in_c;
  }

  return in_c;
}