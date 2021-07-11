# linecount

This project provides a fast multi-threaded line counter. 

```console
$ ./lc large_file.csv
20973777 large_file.csv
```

## Getting Started

1. Create a large file of desired size using `make_large_file.py`

```console
$ python3 make_large_file.py
$ du -sh large_file
5.1G    large_file
```

2. Build linecount and run on large file

```console
$ make
$ ./lc large_file
20973777 large_file
```

## Performance

For large files, this line counter can be 5-6 times faster than `wc -l` depending on compute resources
