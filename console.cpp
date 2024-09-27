#include "console.h"

void Console::disableBuffering()
{
    // Disable buffering
    setvbuf(stdout, NULL, _IONBF, 0);
}

void Console::fastwrite(const wchar_t *text, Color color)
{
    // Convert to UTF-8
    std::wstring wstr(text);
    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
    std::string utf8Str = converter.to_bytes(wstr);

    // Set the color
    char colorCode[8];
    snprintf(colorCode, sizeof(colorCode), "%s%d%s", "\033[", color, "m");
    write(STDOUT_FILENO, colorCode, sizeof(colorCode));

    // Write
    write(STDOUT_FILENO, utf8Str.c_str(), utf8Str.size());

    // Reset the color
    const char* resetColor = "\033[0m";
    write(STDOUT_FILENO, resetColor, sizeof(resetColor));
}

void Console::clear()
{
    // Clear the console
    const char *clearScreen = "\033[2J\033[H";
    write(STDOUT_FILENO, clearScreen, 7);
}

void Console::hideCursor() {
    // Hide the cursor
    const char *hideCursor = "\033[?25l";
    write(STDOUT_FILENO, hideCursor, 6);
}
