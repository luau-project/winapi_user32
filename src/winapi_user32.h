#ifndef WINAPI_USER32_H
#define WINAPI_USER32_H

#ifdef __cplusplus
extern "C" {
#endif

#define LUA_WINAPI_USER32 __declspec(dllexport)

#include <lua.h>

LUA_WINAPI_USER32 int luaopen_winapi_user32(lua_State *L);

#ifdef __cplusplus
}
#endif

#endif