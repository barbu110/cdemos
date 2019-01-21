#include <stdio.h>
#include <stdlib.h>

#include "sparse.h"

void sm_print(sparse_matrix_t *ptr);
void sm_read_from_keyboard(sparse_matrix_t *ptr) {
  int line, col, value;

  do {
    scanf("%d%d%d", &line, &col, &value);

    sm_set(ptr, line, col, value);
  } while (line != -1);
}
int sm_read_from_binary_file(sparse_matrix_t *ptr, char *filename) {
  FILE *fp = fopen(filename, "rb");
  if (!fp) {
    fprintf(stderr, "File cannot be opened.\n");
    return -1;
  }

  elem_t elem;
  while (fread(&elem, sizeof(elem_t), 1, fp) != 0) {
    sm_set(ptr, elem.line, elem.col, elem.value);
  }

  return 0;
}

int main(int argc, char **argv) {
  if (argc < 2) {
    fprintf(stderr, "Size of the matrix is required.\n");
    return -1;
  }

  int width;
  int height;
  char *filename = NULL;

  if (argc == 2) {
    width = atoi(argv[1]);
    height = width;
  }
  if (argc >= 3) {
    width = atoi(argv[1]);
    height = atoi(argv[2]);
  }
  if (argc >= 4) {
    filename = argv[3];
  }

  printf("Matrix size is: %dx%d.\n", width, height);
  printf("Data format is: (line, col, value)\n");
  printf("Finish input by adding -1 as line.\n\n");

  if (filename != NULL) {
    printf("Reading matrix from binary file.\n\n");
  }

  sparse_matrix_t *m = sm_alloc(width, height);

  if (filename == NULL) {
    sm_read_from_keyboard(m);
  } else {
    int status = sm_read_from_binary_file(m, filename);

    if (status != 0) {
      sm_free(m);
      return status;
    }
  }

  sm_print(m);

  printf("\n");
  printf("SparseMatrix size: %d bytes.\n",
         sizeof(sparse_matrix_t) + m->elements_count * sizeof(elem_t));
  printf("Traditional matrix size: %d bytes.\n",
         width * height * sizeof(int) + 2 * sizeof(int));

  sm_free(m);

  return 0;
}

void sm_print(sparse_matrix_t *ptr) {
  for (int i = 0; i < ptr->height; i++) {
    for (int j = 0; j < ptr->width; j++) {
      printf("%2d ", sm_get(ptr, i, j));
    }
    printf("\n");
  }
}
