#include <winapi_user32.h>

#include <Windows.h>

#include <lualib.h>
#include <luaconf.h>
#include <lauxlib.h>

#ifndef LUA_WINAPI_USER32_VERSION
#define LUA_WINAPI_USER32_VERSION "0.0.1-0"
#endif

#if LUA_VERSION_NUM < 502
#define luaL_newlib(L,l) (lua_newtable(L), luaL_register(L,NULL,l))
#define luaL_checkinteger(L, n) (luaL_checkint(L, (n)))
#endif

typedef struct LuaReference LuaReference;

struct LuaReference {
	lua_State *L;
	int index;
};

static int lua_FindWindowA(lua_State *L)
{
    const char *className = luaL_optstring(L, 1, NULL);
    const char *titleName = luaL_optstring(L, 2, NULL);
    
    HWND hwnd = FindWindowA(className, titleName);
    void *userdata = lua_newuserdata(L, sizeof(HWND));
    *((HWND *)userdata) = hwnd;
    
    return 1;
}

static int lua_GetWindowTextLengthA(lua_State *L)
{
    void *userdata = lua_touserdata(L, 1);
    HWND *hwnd = (HWND *)userdata;
    lua_pushinteger(L, GetWindowTextLengthA(*hwnd));
    return 1;
}

static int lua_GetWindowTextA(lua_State *L)
{
    void *userdata = lua_touserdata(L, 1);
    HWND *hwnd = (HWND *)userdata;
    lua_Integer length = luaL_checkinteger(L, 2);

    int bufferLength = (int)length + 1;

    char *buffer = (char *)(malloc(bufferLength));
    lua_pushinteger(L, GetWindowTextA(*hwnd, buffer, bufferLength));
    lua_pushstring(L, buffer);
    free((void *)buffer);
    return 2;
}

static int lua_GetWindowThreadProcessId(lua_State *L)
{
    void *userdata = lua_touserdata(L, 1);
    HWND *hwnd = (HWND *)userdata;
    DWORD dwProcessId;
    lua_pushinteger(L, GetWindowThreadProcessId(*hwnd, &dwProcessId));
    lua_pushinteger(L, dwProcessId);
    return 2;
}

static int lua_GetClassNameA(lua_State *L)
{
    void *userdata = lua_touserdata(L, 1);
    HWND *hwnd = (HWND *)userdata;
    lua_Integer length = luaL_checkinteger(L, 2);

    int bufferLength = (int)length + 1;

    char *buffer = (char *)(malloc(bufferLength));
    lua_pushinteger(L, GetClassNameA(*hwnd, buffer, bufferLength));
    lua_pushstring(L, buffer);
    free((void *)buffer);
    return 2;
}

static BOOL CALLBACK EnumWindowsCallback(
    __in  HWND hWnd,
    __in  LPARAM lParam
)
{
    BOOL result = FALSE;

    LuaReference *ref = (LuaReference *)lParam;
    lua_rawgeti(ref->L, LUA_REGISTRYINDEX, ref->index);

    void *userdata = lua_newuserdata(ref->L, sizeof(HWND));
    *((HWND *)userdata) = hWnd;
    
    if (lua_pcall(ref->L, 1, 1, 0) == 0) {
        result = lua_toboolean(ref->L, -1);
        lua_pop(ref->L, 1);
    }
    else {
        luaL_error(ref->L, "Failed to execute callback function");
    }

    return result;
}

static int lua_EnumWindows(lua_State *L)
{
    if (lua_isfunction(L, 1)) {

        lua_settop(L, 1);

        LuaReference ref;
        ref.L = L;
        ref.index = luaL_ref(L, LUA_REGISTRYINDEX);

        BOOL enumerationResult = EnumWindows(EnumWindowsCallback, (LPARAM)&ref);

        luaL_unref(L, LUA_REGISTRYINDEX, ref.index);

        lua_pushboolean(L, enumerationResult);
    }
    else {
        luaL_argerror(L, 1, "Function expected");
    }

    return 1;
}

static int lua_MessageBoxA(lua_State *L)
{
    HWND *hwnd = NULL;
    if (!lua_isnil(L, 1))
    {
        void *userdata = lua_touserdata(L, 1);
        hwnd = (HWND *)userdata;
    }
    const char *lpText = luaL_optstring(L, 2, NULL);
    const char *lpCaption = luaL_optstring(L, 3, NULL);
    UINT uType = (UINT)(luaL_checkinteger(L, 4));
    lua_pushinteger(L, MessageBoxA(*hwnd, lpText, lpCaption, uType));
    return 1;
}

static int lua_GetForegroundWindow(lua_State *L)
{
    void *userdata = lua_newuserdata(L, sizeof(HWND));
    *(HWND *)userdata = GetForegroundWindow();
    return 1;
}

static int lua_SetForegroundWindow(lua_State *L)
{
    void *userdata = lua_touserdata(L, 1);
    HWND *hwnd = (HWND *)userdata;
    lua_pushboolean(L, SetForegroundWindow(*hwnd));
    return 1;
}

static int lua_FlashWindow(lua_State *L)
{
    void *userdata = lua_touserdata(L, 1);
    HWND *hwnd = (HWND *)userdata;
    BOOL bInvert = lua_toboolean(L, 2);
    lua_pushboolean(L, FlashWindow(*hwnd, bInvert));
    return 1;
}

static const struct luaL_Reg winapi_user32_f[] = {
    {"FindWindowA", lua_FindWindowA},
    {"GetWindowTextLengthA", lua_GetWindowTextLengthA},
    {"GetWindowTextA", lua_GetWindowTextA},
    {"GetWindowThreadProcessId", lua_GetWindowThreadProcessId},
    {"GetClassNameA", lua_GetClassNameA},
    {"EnumWindows", lua_EnumWindows},
    {"MessageBoxA", lua_MessageBoxA},
    {"GetForegroundWindow", lua_GetForegroundWindow},
    {"SetForegroundWindow", lua_SetForegroundWindow},
    {"FlashWindow", lua_FlashWindow},
    {NULL, NULL}
};

LUA_WINAPI_USER32 int luaopen_winapi_user32(lua_State *L)
{
    luaL_newlib(L, winapi_user32_f);

    lua_pushstring(L, "_VERSION");
    lua_pushstring(L, LUA_WINAPI_USER32_VERSION);
    lua_settable(L, -3);

    return 1;
}