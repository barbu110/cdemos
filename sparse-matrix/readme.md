# Sparse Matrix Implementation

This is a basic implementation of a sparse matrix using the Coordinates List
storage method (read about it [here](https://en.wikipedia.org/wiki/Sparse_matrix#Coordinate_list_(COO))).

The API for the `sparse_matrix_t` features the following functions:

```c
sparse_matrix_t *sm_alloc(int width, int height);
void sm_free(sparse_matrix_t *matrix);
int sm_get_offset(sparse_matrix_t *matrix, int l, int c);
void sm_set(sparse_matrix_t *matrix, int l, int c, int v);
int sm_get(sparse_matrix_t *matrix, int l, int c);
void sm_delete(sparse_matrix_t *matrix, int l, int c);
```

To test the library, I implemented a small utility program that can either
populate the sparse matrix from keyboard input or by reading a binary file.

The utility can be run using the following signatures:

```
./populate <matrix-size>
./populate <matrix-width> <matrix-height>
./populate <matrix-width> <matrix-height> <input-file>
```
