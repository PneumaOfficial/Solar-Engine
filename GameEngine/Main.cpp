#include <iostream>
#include "Game.hpp"
#include "DEFINTIONS.hpp"
namespace Solar 
{
    Enums Enum;
}
#ifndef __LUA_INC_H__
#define __LUA_INC_H__
extern "C"
{
#include "Lua535/include/lauxlib.h"
#include "Lua535/include/lua.h"
#include "Lua535/include/lualib.h"
}
#endif // __LUA_INC_H__
int main(){
    std::string command = "a = 7 + 11";
    lua_State* L = luaL_newstate();
    int r = luaL_dostring(L, command.c_str());

    if (r == LUA_OK)
    {

        lua_getglobal(L, "a");
        if (lua_isnumber(L, -1))
        {
            float a_in_cpp = (float)lua_tonumber(L,-1);
            std::cout << a_in_cpp << std::endl;
        }
    }
    else
    {
        std::string errmsg = lua_tostring(L, -1);
        std::cout << errmsg << std::endl;
    }

    system("pause");
    lua_close(L);
    //Solar::Game(Solar::Enum.Window.SCREEN_WIDTH, Solar::Enum.Window.SCREEN_HEIGHT, "Solar Engine Testing");
    return EXIT_SUCCESS;
}