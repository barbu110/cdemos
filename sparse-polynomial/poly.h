#ifndef POLY_H
#define POLY_H

typedef struct {
  int c;
  int exp;
} term_t;

typedef struct {
  int degree;
  int terms_count;
  term_t *terms;
} poly_t;

poly_t *p_alloc();

void p_free(poly_t*);

void p_add_term(poly_t*, term_t);

void p_print(poly_t *p);

#endif /* end of include guard: POLY_H */
