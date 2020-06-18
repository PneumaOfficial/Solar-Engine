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

bool CheckLua(lua_State* L, int r)
{
    if (r != LUA_OK)
    {
        std::string errmsg = lua_tostring(L, -1);
        std::cout << errmsg << std::endl;
        return false;
    }
}

int main(){
    std::string command = "a = 7 + 11";
    lua_State* L = luaL_newstate();
    luaL_openlibs(L);
    
    if(CheckLua(L, luaL_dofile(L, "Resources/Testing Scripts/Testing.lua")))
    {
        lua_getglobal(L, "player");
        if (lua_istable(L, -1))
        {
            
        }
    }

    system("pause");
    lua_close(L);
    //Solar::Game(Solar::Enum.Window.SCREEN_WIDTH, Solar::Enum.Window.SCREEN_HEIGHT, "Solar Engine Testing");
    return EXIT_SUCCESS;
}