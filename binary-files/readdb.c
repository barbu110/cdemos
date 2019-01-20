#include <stdio.h>
#include <stdlib.h>

#include "product.h"

int read_product(product_t *p, FILE *fp) {
  if (fread(&p->code, sizeof(int), 1, fp) == 0) {
    return 0;
  }

  fread(&p->price, sizeof(int), 1, fp);
  fread(&p->name_size, sizeof(int), 1, fp);
  p->name = malloc(p->name_size * sizeof(char));
  fread(p->name, sizeof(char), p->name_size, fp);

  return 1;
}

int main(int argc, char *argv[]) {
  if (argc < 2) {
    fprintf(stderr, "Filename is required.\n");
    return -1;
  }

  FILE *fp = fopen(argv[1], "rb");
  if (fp == NULL) {
    fprintf(stderr, "Database cannot be read.\n");
    return -1;
  }

  product_t p;
  printf("Code\tPrice\tName\n");
  while (read_product(&p, fp) != 0) {
    printf("%4d\t%4d\t%s\n", p.code, p.price, p.name);

    free(p.name);
  }

  fclose(fp);

  return 0;
}
