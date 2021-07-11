#include <lc/count_lines.hpp>

namespace lc {

  namespace detail {

    // Thread function - for each chunk
    void LineCounter::count_lines_in_chunk(std::size_t chunk_index,
					   std::size_t chunk_start,
					   std::size_t chunk_end) {
      std::size_t lines_in_chunk = 0;
    
      std::size_t index;
      for (index = chunk_start; index < chunk_end; ++index) {
	if (file_mmap[index] == '\n') {
	  lines_in_chunk += 1;
	}
      }
      result += lines_in_chunk;
    }    
  
    LineCounter::LineCounter(const char * path) {
      file_mmap = mio::make_mmap_source(path, error);
      file_size = file_mmap.size();
      num_chunks = std::thread::hardware_concurrency();
      size_per_chunk = file_size / num_chunks;
    }

    std::size_t LineCounter::count() {
      if (error) {
	return result;
      }
    
      // schedule line counter for each chunk
      for (std::size_t i = 0; i < num_chunks; ++i) {
	std::size_t chunk_start = i * size_per_chunk;
	std::size_t chunk_end = chunk_start + size_per_chunk;
      
	if (chunk_end > file_size || (i == num_chunks - 1)) {
	  chunk_end = file_size;
	
	  // check if last character is not a newline
	  if (file_mmap[chunk_end - 1] != '\n') {
	    result += 1;
	  }
	}
      
	threads.push_back(std::thread(std::bind(&LineCounter::count_lines_in_chunk, this,
						i, chunk_start, chunk_end)));
      }
    
      for (auto& t: threads) {
	t.join();
      }    
    
      return result;
    }
  
  }

  std::size_t count_lines(const char * path) {
    auto counter = detail::LineCounter(path);
    return counter.count();
  }

}
