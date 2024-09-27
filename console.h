#pragma once

#include <string>
#include <unistd.h>
#include <codecvt>
#include <locale>

enum Color : int {
    Black = 30,
    Red = 31,
    Green = 32,
    Yellow = 33,
    Blue = 34,
    Magenta = 35,
    Cyan = 36,
    White = 37
};

class Console
{
public:
    static void disableBuffering();
    static void fastwrite(const wchar_t *text, Color color = Color::White);
    static void clear();
    static void hideCursor();
};