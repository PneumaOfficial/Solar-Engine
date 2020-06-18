#include <iostream>
#include "Game.hpp"
#include "DEFINTIONS.hpp"
namespace Solar 
{
    Enums Enum;
}

int main(){
    
    Solar::Game(Solar::Enum.Window.SCREEN_WIDTH, Solar::Enum.Window.SCREEN_HEIGHT, "Solar Engine Testing");
    return EXIT_SUCCESS;
}