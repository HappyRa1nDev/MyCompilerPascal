#include "PascalCompiler.h"
#include <iostream>

using namespace std;

int main()
{
    PascalCompiler myCompiler("programm.txt");
    myCompiler.compile();
}
