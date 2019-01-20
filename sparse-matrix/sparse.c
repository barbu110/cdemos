#include <stdlib.h>

#include "sparse.h"

sparse_matrix_t* sm_alloc(int width, int height) {
  sparse_matrix_t *ptr = malloc(sizeof(sparse_matrix_t));

  ptr->width = width;
  ptr->height = height;
  ptr->elements_count = 0;
  ptr->elements = NULL;

  return ptr;
}

void sm_free(sparse_matrix_t *ptr) {
  free(ptr->elements);
  free(ptr);
}

int sm_has(sparse_matrix_t *ptr, int l, int c) {
  for (int i = 0; i < ptr->elements_count; i++) {
    if (ptr->elements[i].col == c && ptr->elements[i].line == l) {
      return 1;
    }
  }

  return 0;
}

void sm_set(sparse_matrix_t *ptr, int l, int c, int v) {

}
