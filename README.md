<p align="center">
  <img height="100" src="https://user-images.githubusercontent.com/8450091/125217019-50429280-e285-11eb-9bee-ecc72b949c03.png"/>  
</p>

`lc` is a fast multi-threaded line counter.

## Getting Started

Build and install `lc`

```bash
mkdir build
cd build
cmake ..
make
sudo make install
```

Basic usage:

```console
$ lc some_large_file
20973777 some_large_file
```

## Performance Benchmark

* This performance benchmark was run on an [NVIDIA DGX-1](https://docs.nvidia.com/dgx/dgx1-user-guide/introduction-to-dgx1.html#topic_hardware-specs) system.
* Use `utils/make_large_file.py` to create files of desired size.
* Benchmark using the [hyperfine](https://github.com/sharkdp/hyperfine) command-line benchmarking tool.
* For large files, this line counter can be 2-10 times faster than `wc -l` depending on compute resources.

| File size | Lines     | `wc -l <file>` | `./lc <file>` |
|----------:|----------:|---------------:|--------------:|
| 500 MB    | 2047277   | 116.8 ms       | 34.5 ms       |
| 1 GB      | 4192675   | 243.0 ms       | 60.9 ms       |
| 5 GB      | 20969987  | 1.160 s        | 200.5 ms      |
| 25 GB     | 104839424 | 6.162 s        | 738.8 ms      |
| 51 GB     | 209706969 | 13.117 s       | 1.461 s       | 
| 100 GB    | 209706969 | 27.279 s       | 3.597 s       | 
