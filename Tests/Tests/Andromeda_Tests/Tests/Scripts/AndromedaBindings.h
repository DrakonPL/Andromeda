#pragma once

extern "C"
{
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}

// This is the only header we need to include for LuaBind to work
#include "luabind/luabind.hpp"

class AndromedaBindings
{
private:

	lua_State* _luaState;

private:

	void BindGraphics();

public:

	AndromedaBindings(lua_State* state);
	~AndromedaBindings();

	void Bind();
};