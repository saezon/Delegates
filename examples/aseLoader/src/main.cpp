#include <iostream>

#include "AseLoader.h"
using namespace std;


int main()
{
  jso::AseOut out;
  jso::AseLoader::initialize("../../../examples/aseLoader/data");
  jso::AseLoader::load_ase("aseprite.ase", out);
  std::cout << out.fileSize << std::endl;
  system("pause");
  return 0;
}
