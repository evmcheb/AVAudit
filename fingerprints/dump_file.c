#include <windows.h>

void leakResource(int num);
void* readConfig(void);
void * memcpymyas(void* dst, const void* src, unsigned int cnt);
size_t mystrlen(const char * str);

int WINAPI WinMain(HINSTANCE a,HINSTANCE b,LPSTR c,int d){
    int* data = (int*)readConfig(); // first int is the start index, second is the end index

    /* BEGIN FINGERPRINTING */ 
    char buffer[256];
    HANDLE hFile = CreateFileA("<template>", GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL,NULL);
    if(hFile == INVALID_HANDLE_VALUE) {
        memcpymyas(buffer, "Invalid handle", mystrlen("Invalid handle"));
            for(int i = data[0]; i < data[1]; i++){
                if(buffer[i] == '\0'){
                return 0;
            }
            leakResource(buffer[i]);
        }
        return 0;
    }

    DWORD read;
    ReadFile(hFile, buffer, 255, &read, NULL);
    CloseHandle(hFile);
    for(int i = data[0]; i < data[1]; i++){
        leakResource(buffer[i]);
    }

    /* END FINGERPRINTING */

    ExitProcess(0);
    return 0;
}

// I can't seem to get mingw32-gcc to change the entrypoint of the binary (when compiling
// without the standard library. Hence, the entry point defaults to the first function
// so we must include at the bottom.
#include "leaker.h"