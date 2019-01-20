#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "product.h"

int main(int argc, char *argv[]) {
  if (argc < 2) {
    fprintf(stderr, "Filename is required.\n");
    return -1;
  }

  FILE *fp = fopen(argv[1], "wb");

  int n;
  scanf("%d", &n);

  for (int i = 0; i < n; i++) {
    product_t p;
    char buf[128] = {0};
    scanf("%d%d", &p.code, &p.price);

    fgets(buf, sizeof(buf), stdin);
    buf[strlen(buf) - 1] = 0;

    p.name_size = strlen(buf) + 1;
    p.name = malloc(p.name_size * sizeof(char));
    snprintf(p.name, p.name_size * sizeof(char), "%s", buf);

    fwrite(&p.code, sizeof(int), 1, fp);
    fwrite(&p.price, sizeof(int), 1, fp);
    fwrite(&p.name_size, sizeof(int), 1, fp);
    fwrite(p.name, sizeof(char), p.name_size, fp);

    free(p.name);
  }

  fclose(fp);

  return 0;
}
