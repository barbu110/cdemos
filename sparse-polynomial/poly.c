#include <stdlib.h>
#include <memory.h>
#include <stdio.h>

#include "poly.h"

poly_t *p_alloc() {
  poly_t *ptr = malloc(sizeof(poly_t));

  ptr->degree = 0;
  ptr->terms_count = 0;
  ptr->terms = NULL;

  return ptr;
}

void p_free(poly_t *ptr) {
  free(ptr->terms);
  free(ptr);
}

void p_add_term(poly_t *p, term_t term) {
  if (p->terms_count == 0) {
    p->terms = malloc(++p->terms_count * sizeof(term_t));
  } else {
    p->terms = realloc(p->terms, ++p->terms_count * sizeof(term_t));
  }

  p->terms[p->terms_count - 1] = term;
}

void p_print(poly_t *p) {
  for (int i = 0; i < p->terms_count; i++) {
    if (p->terms[i].c != 1) {
      printf("%d", p->terms[i].c);
    }

    if (p->terms[i].exp != 0 && p->terms[i].c != 1) {
      printf(" * ");
    }

    if (p->terms[i].exp != 0) {
      printf("x");

      if (p->terms[i].exp != 1) {
        printf(" ^ %d", p->terms[i].exp);
      }
    }

    if (i < p->terms_count - 1) {
      printf(" + ");
    }
  }
  printf("\n");
}
