#include <atomic>
#include <iostream>
#include <lc/mio.hpp>
#include <thread>
#include <unordered_map>

namespace lc {

namespace detail {
struct LineCounter {
  std::error_code error;
  mio::mmap_source file_mmap;
  std::size_t file_size;
  std::size_t num_chunks;
  std::size_t size_per_chunk;
  std::atomic_size_t result{0};
  std::vector<std::thread> threads;

  // Thread function - for each chunk
  void count_lines_in_chunk(std::size_t chunk_start, std::size_t chunk_end);

  // Constructor
  // Memory map the file
  LineCounter(const char *path);

  // Main function that counts the lines
  // Spawns threads (N = num_chunks)
  std::size_t count();
};
} // namespace detail

std::size_t count_lines(const char *path);

} // namespace lc
