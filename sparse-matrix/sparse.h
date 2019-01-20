#ifndef SPARSE_H
#define SPARSE_H

typedef struct {
  int line;
  int col;
  int value;
} elem_t;

typedef struct {
  int width;
  int height;
  int elements_count;
  elem_t *elements;
} sparse_matrix_t;

// Allocate a sparse matrix on the heap.
sparse_matrix_t* sm_alloc(int width, int height);

// Release the memory of a sparse matrix.
void sm_free(sparse_matrix_t *matrix);

// Checks whether the given coordinates exist in the sparse matrix.
int sm_has(sparse_matrix_t *matrix, int l, int c);

// Add or modify an element to the sparse matrix.
void sm_set(sparse_matrix_t *matrix, int l, int c, int v);

// Get an element from the sparse matrix.
int sm_get(sparse_matrix_t *matrix, int l, int c);

// Delete an element from the sparse matrix.
void sm_delete(sparse_matrix_t *matrix, int l, int c);

#endif /* end of include guard: SPARSE_H */
