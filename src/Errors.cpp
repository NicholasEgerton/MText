#include "Errors.h"
#ifdef _WIN32
#include <Windows.h>
#endif

void Errors::ShowError(const std::string& errorMessage)
{
#ifdef _WIN32
    std::wstring temp = std::wstring(errorMessage.begin(), errorMessage.end());
    LPCWSTR wideString = temp.c_str();
    MessageBoxW(NULL, wideString, L"Error", MB_OK | MB_ICONERROR | MB_TOPMOST);
#else
    //If not windows just output to the console.
    //This in the future could be improved to include more platform support.
    std::cerr << "Error: " << errorMessage << std::endl;
#endif
}
