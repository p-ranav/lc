#include <lc/count_lines.hpp>

int main(int argc, char * argv[])
{
  auto path = argv[1];
  std::cout << lc::count_lines(path) << " " << path << "\n";
}
