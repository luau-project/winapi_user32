# Overview

*winapi_user32* is a library to allow the Lua programmer to interface with the underlying WINAPI User32.lib. Also, this library has been tested with Lua 5.1.5, 5.2.4 and 5.3.3.

**Note**: Due the huge amount of functions available in the User32.lib, this is going to take a considerable time of work to bind them all, which is going to happen in a lot of releases.

# Functions

- [EnumWindows](#enumwindows)
- [FindWindowA](#findwindowa)
- [FlashWindow](#flashwindow)
- [GetClassNameA](#getclassnamea)
- [GetForegroundWindow](#getforegroundwindow)
- [GetWindowTextA](#getwindowtexta)
- [GetWindowTextLengthA](#getwindowtextlengtha)
- [GetWindowThreadProcessId](#getwindowthreadprocessid)
- [MessageBoxA](#messageboxa)
- [SetForegroundWindow](#setforegroundwindow)

## EnumWindows

```lua
local user32 = require("winapi_user32")

-- BOOL
local result = user32.EnumWindows(
    -- EnumWindowsProc
    function(hWnd)
        -- true : continue enumeration
        -- false: stop enumeration
        return true
    end
)
```

## FindWindowA

```lua
local user32 = require("winapi_user32")

-- HWND
local hWnd = user32.FindWindowA(
    "Notepad", -- (optional) LPCTSTR lpClassName
    "Hello World" -- (optional) LPCTSTR lpClassName
)
```

## FlashWindow

```lua
local user32 = require("winapi_user32")

local hWnd = -- previously acquired HWND

-- BOOL
local result = user32.FlashWindow(
    hWnd, -- HWND hWnd
    false -- BOOL bInvert
)
```

## GetClassNameA

```lua
local user32 = require("winapi_user32")

local hWnd = -- previously acquired HWND

-- int, string
local result, className = user32.GetClassNameA(
    hWnd, -- HWND hWnd
    1024 -- int nMaxCount
)

if (result) then
    print(className)
end
```

## GetForegroundWindow

```lua
local user32 = require("winapi_user32")

-- HWND
local result = user32.GetForegroundWindow()
```

## GetWindowTextA

```lua
local user32 = require("winapi_user32")

local hWnd = -- previously acquired HWND

-- int, string
local result, text = user32.GetWindowTextA(
    hWnd, -- HWND hWnd
    1024 -- int nMaxCount
)

if (result) then
    print(text)
end
```

## GetWindowTextLengthA

```lua
local user32 = require("winapi_user32")

local hWnd = -- previously acquired HWND

-- int
local length = user32.GetWindowTextLengthA(
    hWnd -- HWND hWnd
)
```

## GetWindowThreadProcessId

```lua
local user32 = require("winapi_user32")

local hWnd = -- previously acquired HWND

-- DWORD, DWORD
local threadId, processId = user32.GetWindowThreadProcessId(
    hWnd -- HWND hWnd
)
```

## MessageBoxA

```lua
local user32 = require("winapi_user32")

local hWnd = -- previously acquired HWND

-- int
local result = user32.MessageBoxA(
    hWnd, -- HWND hWnd
    "This is a message", -- LPCTSTR lpText
    "This is the title", -- LPCTSTR lpCaption
    0 -- UINT uType
)
```

## SetForegroundWindow

```lua
local user32 = require("winapi_user32")

local hWnd = -- previously acquired HWND

-- BOOL
local result = user32.SetForegroundWindow(
    hWnd -- HWND hWnd
)
```
