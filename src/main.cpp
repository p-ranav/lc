#include "lc/argparse.hpp"
#include "lc/count_lines.hpp"
#include <stdlib.h>

int main(int argc, char *argv[]) {

  argparse::ArgumentParser program("lc");
  program.add_argument("FILE")
    .action([](const std::string& value) { return value; });

  try {
    program.parse_args(argc, argv);
  }
  catch (const std::runtime_error& err) {
    std::cout << err.what() << std::endl;
    std::cout << program;
    return EXIT_FAILURE;
  }  
  
  auto path = program.get<std::string>("FILE");
  std::cout << lc::count_lines(path) << " " << path << "\n";
  return EXIT_SUCCESS;
}
