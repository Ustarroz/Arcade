#include <iostream>
#include "Core.hpp"

int main(int argc, char **argv)
{
  if (argc != 2)
  {
    std::cerr << "Usage:" << std::endl << " " << argv[0] << " lib" << std::endl;
    return (EXIT_FAILURE);
  }
  arcade::Core core(argv[1]);
  if (core.loadLibraries())
  {
    std::cerr << core.getError() << std::endl;
    return (EXIT_FAILURE);
  }
  core.gameLoop();
  return (EXIT_SUCCESS);
}
