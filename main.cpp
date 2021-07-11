#include "mio.hpp"
#include <atomic>
#include <iostream>
#include <thread>
#include <unordered_map>

class LineCounter {
  std::error_code error;
  mio::mmap_source file_mmap;
  std::size_t file_size;
  std::size_t num_chunks;
  std::size_t size_per_chunk;
  std::atomic_size_t __lines__{0};
  std::vector<std::thread> threads;

  void count_lines_in_chunk(std::size_t chunk_index, std::size_t chunk_start, std::size_t chunk_end) {
    std::size_t lines = 0;
    
    std::size_t index;
    std::size_t last_newline_index;
    for (index = chunk_start; index < chunk_end; ++index) {
      if (file_mmap[index] == '\n') {
	lines += 1;
	last_newline_index = index;
      }
    }
    __lines__ += lines;
  }

public:
  LineCounter(const char * path) {
    file_mmap = mio::make_mmap_source(path, error);
    file_size = file_mmap.size();
    num_chunks = std::thread::hardware_concurrency();
    size_per_chunk = file_size / num_chunks;
  }

  std::size_t count() {
    if (error) {
      return __lines__;
    }
    
    // schedule line counter for each chunk
    for (std::size_t i = 0; i < num_chunks; ++i) {
      std::size_t chunk_start = i * size_per_chunk;
      std::size_t chunk_end = chunk_start + size_per_chunk;

      if (chunk_end > file_size || (i == num_chunks - 1)) {
	chunk_end = file_size;

	// check if last character is not a newline
	if (file_mmap[chunk_end - 1] != '\n') {
	  __lines__ += 1;
	}
      }

      threads.push_back(std::thread(std::bind(&LineCounter::count_lines_in_chunk, this,
					      i, chunk_start, chunk_end)));
    }

    for (auto& t: threads) {
      t.join();
    }    

    return __lines__;
  }
  
};

int main(int argc, char * argv[])
{
  auto counter = LineCounter(argv[1]);
  std::cout << counter.count() << " " << argv[1] << "\n";
}

