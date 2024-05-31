#include "../include/opal.h"
#include "../include/opal/opal_scanner.h"
#include "../include/opal/opal_fs.h"

#define OPAL_DEBUG 0
void opal_main(int argc, char **argv)
{
  if (argc < 2 && !OPAL_DEBUG)
  {
      fprintf(stderr, "Opal is a language focusing on efficiency.\nTo compile a program, rerun with \n\t[opal *.op]\n");
      return;
  }
  const char* dir = OPAL_DEBUG ? "src/tests/main.op" : argv[1];
  OpalScanner_T* s = init_opal_scanner(read_file_fs(dir), dir);
  OpalToken_T* t = opal_scanner_scan_next_token(s);
    if(s->error_list->size > 0)
    {
        return;
    }
  while(t->type != EOF) {
        if(s->error_list->size > 0)
        {
            printf("%s\n", opal_error_to_string(s->error_list->items[0]));
            return;
        }
      printf("%s\n", opal_token_to_string(t));
      t = opal_scanner_scan_next_token(s);
  }
}