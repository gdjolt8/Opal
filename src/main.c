#include "../include/opal.h"

int main(int argc, char**argv) {
  atexit(opal_gc_free_all);
  opal_main(argc, argv);

}