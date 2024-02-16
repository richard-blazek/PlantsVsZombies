#pragma once

#include <string>
#include <windows.h>
#include <cstdlib>

namespace console
{
    inline void SetColor(int background, int foreground)
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (background<<4)+foreground);
    }
    inline void Clear()
    {
        system("cls");
    }
    inline void SetTitle(std::string txt)
	{
		SetConsoleTitleA(txt.c_str());
	}
	inline void SetTitle(std::wstring txt)
	{
		SetConsoleTitleW(txt.c_str());
	}
	inline void Hide()
	{
		HWND wind;
		AllocConsole();
		wind=FindWindowA("ConsoleWindowclass", nullptr);
		ShowWindow(wind, 0);
	}
	inline void Show()
	{
		HWND wind;
		AllocConsole();
		wind=FindWindowA("ConsoleWindowclass", nullptr);
		ShowWindow(wind, 1);
	}
}

namespace cursor
{
	inline void Show()
    {
        CONSOLE_CURSOR_INFO info{100, true};
        SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
    }
    inline void Hide()
    {
        CONSOLE_CURSOR_INFO info{100, false};
        SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
    }
    inline void Move(int x, int y)
    {
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {x, y} );
    }
}