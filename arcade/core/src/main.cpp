#include <iostream>
#include "core/Core.hpp"

int main(int argc, char **argv)
{
  if (argc != 2)
  {
    std::cerr << "Usage:" << std::endl << " " << argv[0] << " lib" << std::endl;
    return (EXIT_FAILURE);
  }
  arcade::Core core(argv[1]);
  core.gameLoop();
  std::cout << "loading libraries..." << std::endl;
  return (EXIT_SUCCESS);
}
