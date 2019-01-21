#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

typedef struct {
  char filename[128];
  int start_line, end_line;
} include_def_t;

typedef struct {
  int line;
  int col;
  int pos;
} pos_t;

typedef struct {
  include_def_t *defs;
  int defs_count;
} catalog_t;

void process_include_def(include_def_t*, char[]);

int main(int argc, char **argv) {
  if (argc < 2) {
    fprintf(stderr, "Filename is required.\n");
    return -1;
  }

  FILE *fp = fopen(argv[1], "r");
  if (!fp) {
    fprintf(stderr, "File could not be opened.\n");
    return -1;
  }

  printf("Reading file \"%s\".\n", argv[1]);

  catalog_t catalog = {NULL, 0};
  include_def_t t;

  while (fscanf(fp, "%s%d%d", t.filename, &t.start_line, &t.end_line) == 3) {
    if (catalog.defs_count == 0) {
      catalog.defs = malloc(++catalog.defs_count * sizeof(include_def_t));
      catalog.defs[0] = t;
    } else {
      catalog.defs = realloc(catalog.defs,
                             ++catalog.defs_count * sizeof(include_def_t));
      catalog.defs[catalog.defs_count - 1] = t;
    }
  }

  fclose(fp);

  char compilation_filename[128];
  snprintf(compilation_filename, 128, "%s.cpl", argv[1]);
  fp = fopen(compilation_filename, "w");

  for (int i = 0; i < catalog.defs_count; i++) {
    char buf[1024] = {0};
    process_include_def(&catalog.defs[i], buf);

    fprintf(fp, "%s", buf);

    memset(buf, 0, sizeof(buf));
  }

  free(catalog.defs);
  fclose(fp);

  return 0;
}

void process_include_def(include_def_t *def, char buf[]) {
  FILE *fp = fopen(def->filename, "r");
  fseek(fp, 0, SEEK_SET);

  int line = 0;

  do {
    char line_buf[1024] = {0};
    fgets(line_buf, sizeof(line_buf), fp);
    line++;
  } while (line < def->start_line - 1);

  do {
    char line_buf[1024] = {0};
    fgets(line_buf, sizeof(line_buf), fp);
    memcpy(buf + strlen(buf), line_buf, strlen(line_buf));
    line++;
  } while (line < def->end_line);

  fclose(fp);
}
