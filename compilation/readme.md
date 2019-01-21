# Compilation

This is a small example that takes an input catalog file in the following
format:

```
<filename> <start-line> <end-line>
...
```

The program reads the catalog file and creates a *compilation file* containing
the chunks defined in the catalog (i.e. line `start-line` to `end-line`from
`filename`).

The program can be executed using the following format:

```
$ ./compile <catalog-filename>
```

The example can be compiled using:

```
gcc -o compile -Wall -Wextra -std=c99 compilation.c
```
