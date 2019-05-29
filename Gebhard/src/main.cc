///////////////////////////////////////////////////////
//
//		Copyright � 1994 Jens Gebhard
//
//      DATEI:	MAIN.CPP
//
//		ZWECK:  Hauproutine
//
///////////////////////////////////////////////////////

#include <new>
#include "Permutationstest.h"

int main(int argc, char **argv)
{
  std::set_new_handler(0);
  PermutationTestApp Test(argc, argv);
  Test.Run();
  return 0;
}
