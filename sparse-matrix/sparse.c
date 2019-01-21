#include <stdlib.h>
#include <memory.h>

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

int sm_get_offset(sparse_matrix_t *ptr, int l, int c) {
  for (int i = 0; i < ptr->elements_count; i++) {
    if (ptr->elements[i].col == c && ptr->elements[i].line == l) {
      return i;
    }
  }

  return -1;
}

void sm_set(sparse_matrix_t *ptr, int l, int c, int v) {
  int index = sm_get_offset(ptr, l, c);
  if (index != -1 && v == 0) {
    sm_delete(ptr, l, c);
    return;
  }
  if (index != -1) {
    ptr->elements[index].value = v;
    return;
  }

  if (ptr->elements_count == 0) {
    ptr->elements = malloc(++ptr->elements_count * sizeof(elem_t));
  } else {
    ptr->elements = realloc(ptr->elements,
                            ++ptr->elements_count * sizeof(elem_t));
  }

  ptr->elements[ptr->elements_count - 1].line = l;
  ptr->elements[ptr->elements_count - 1].col = c;
  ptr->elements[ptr->elements_count - 1].value = v;
}

int sm_get(sparse_matrix_t *ptr, int l, int c) {
  int index = sm_get_offset(ptr, l, c);
  return index == -1 ? 0 : ptr->elements[index].value;
}

void sm_delete(sparse_matrix_t *ptr, int l, int c) {
  int index = sm_get_offset(ptr, l, c);
  if (index == -1) {
    return;
  }

  memmove(ptr->elements + index,
          ptr->elements + index + 1,
          (--ptr->elements_count - index) * sizeof(elem_t));

  ptr->elements = realloc(ptr->elements, ptr->elements_count * sizeof(elem_t));
}
