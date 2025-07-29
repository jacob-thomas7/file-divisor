#include <windows.h>
#include <tchar.h>

#include "config.h"

using namespace file_divisor;

int WINAPI WinMain(HINSTANCE h_instance, HINSTANCE h_prev_instance, LPSTR args, int cmd_show){
    MessageBox(NULL, _T("Opening File Divisor GUI!"), _T("File Divisor"), NULL);
}