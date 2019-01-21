#include <stdio.h>

#include "poly.h"

poly_t *p_read_binary(FILE *fp) {
  int terms_count;
  if (fread(&terms_count, sizeof(int), 1, fp) == 0) {
    return NULL;
  }

  poly_t *p = p_alloc();
  fread(&p->degree, sizeof(int), 1, fp);

  for (int i = 0; i < terms_count; ++i) {
    term_t temp;
    fread(&temp, sizeof(term_t), 1, fp);

    p_add_term(p, temp);
  }

  return p;
}

int main(int argc, char **argv) {
  if (argc < 2) {
    fprintf(stderr, "Filename is required.\n");
    return -1;
  }

  FILE *f = fopen(argv[1], "rb");
  if (!f) {
    fprintf(stderr, "Cannot open file.\n");
    return -1;
  }



  fclose(f);
  return 0;
}
