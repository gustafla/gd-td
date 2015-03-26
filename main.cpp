//Le alibaba game

#include <iostream>
#include <SDL/SDL.h>
#include "cleanup.hpp"

//using namespace std;
//Let's not use std all the time, use std::* instead
//std::cout << "stuff\n"; for example

int main(int argc, char* argv[])
{
    atexit(cleanup);
    return 0;
}
