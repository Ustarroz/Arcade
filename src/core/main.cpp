#include <iostream>
#include "core/core.hpp"

int main(int argc, char **argv)
{
  if (argc != 2)
  {
    std::cerr << "Usage:" << std::endl << " " << argv[0] << " lib" << std::endl;
    return (EXIT_FAILURE);
  }
  std::cout << "loading libraries..." << std::endl;
  return (EXIT_SUCCESS);
}
