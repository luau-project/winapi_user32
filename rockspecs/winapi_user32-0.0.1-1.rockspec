package = "winapi_user32"
version = "0.0.1-1"
source = {
   url = "git://github.com/luau-project/winapi_user32",
   tag = "v0.0.1-1",
}
description = {
   summary = "Windows API User32.lib binding for Lua",
   detailed = [[
       winapi_user32 is a library to allow the Lua programmer
       to interface with the underlying WINAPI User32.lib
   ]],
   license = "MIT/X11",
}
dependencies = {
   "lua >= 5.1"
}
build = {
   type = "builtin",
   modules = {
      winapi_user32 = {
          sources = { "src/winapi_user32.c" },
          incdirs = { "src/" },
          libraries = { "user32" }
      }
   }
}