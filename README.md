# linecount

This project provides a fast multi-threaded line counter. 

```console
$ lc large_file.csv
20973777 large_file.csv
```

## Build & Install

```console
$ mkdir build && cd build
$ cmake .. && make && sudo make install


$ lc some_large_file
20973777 some_large_file
```

## Performance Benchmark

* This performance benchmark was run on an [NVIDIA DGX-1](https://docs.nvidia.com/dgx/dgx1-user-guide/introduction-to-dgx1.html#topic_hardware-specs) system.
* Use `utils/make_large_file.py` to create files of desired size, filled with random data.
* For large files, this line counter can be 5-10 times faster than `wc -l` depending on compute resources.

| File size | Lines     | `wc -l <file>` | `./lc <file>` |
|----------:|----------:|---------------:|--------------:|
| 500 MB    | 2047277   | 116.8 ms       | 34.5 ms       |
| 1 GB      | 4192675   | 243.0 ms       | 60.9 ms       |
| 5 GB      | 20969987  | 1.160 s        | 200.5 ms      |
| 25 GB     | 104839424 | 6.162 s        | 738.8 ms      |
| 51 GB     | 209706969 | 13.117 s       | 1.461 s       | 
| 100 GB    | 209706969 | 27.279 s       | 3.597 s       | 
