# Binary Files Access

This small demo is about reading and writing from and to a binary file.
I imagined a small *database* of products with the following fields:
 - `code` integer
 - `price` integer
 - `name` a dynamically allocated string that **can** contain spaces

By running `make` you will get two executables: `readdb` and `writedb`.

## Writing the database

To write the database you need to run `writedb` and add input data. The
following example will generate a database with three products:

```
$ ./writedb products.bin
3
1 599 Cheap Phone
2 2799 MacBook Pro
3 999 MacBook Air
```

## Reading the database

To read the database you need to run the `readdb` executable with the database
filename as first argument:

```
$ ./readdb products.bin
```
