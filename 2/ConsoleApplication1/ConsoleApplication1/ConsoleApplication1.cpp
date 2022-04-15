#include <Windows.h>
#include <ctype.h>
#include <iostream>
#include <stdio.h>
#include <string>

using namespace std;

int main()
{
    setlocale(LC_ALL, "ru");
    HANDLE myFile = CreateFile(L"myfile.txt", GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, 0);
    cout << "> Дескриптор " << myFile << "\n";
    DWORD myFileSize = GetFileSize(myFile, NULL);
    cout << "> Размер файла  = " << myFileSize << "\n";
    HANDLE myFileMapping = CreateFileMapping(myFile, NULL, PAGE_READWRITE, 0, 0, (LPCWSTR)"myFileMapping");
    cout << "> Дескриптор файлового отображения = " << myFileMapping << "\n";
    LPVOID myFileMapView = MapViewOfFile(myFileMapping, FILE_MAP_WRITE, 0, 0, 0);
    cout << "> Отображённая область памяти = " << MapViewOfFile << "\n\n";
    cout << "Отзеркаливаем содержимое файла..." << "\n\n";
    char* myFileMemory = new char[myFileSize];
    char* myNewFileMemory = new char[myFileSize];
    CopyMemory(myFileMemory, myFileMapView, myFileSize);
    int global_i = 0;
    for (int i = 0; i < myFileSize; i++) {
        char* buff = new char[myFileSize];
        for (int ii = 0; i < myFileSize+1; ii++,i++) {
            char c = myFileMemory[i];
            if ((c == '\n')||(i==myFileSize)|| (c == '\r')) {
                for (int j = i-global_i; j!=0; j--, global_i++) {
                    myNewFileMemory[global_i] = buff[j-1];
                }
                myNewFileMemory[global_i] = '\n';
                global_i++;
                break;
            }
            else {
                buff[ii] = c;
            }
        }
        delete[] buff;
    }
    cout << "\n";
    CopyMemory(myFileMapView, myNewFileMemory, myFileSize);
    cout << "\nT H E   E N D\n";
    if (!UnmapViewOfFile(myFileMapView))
        cout << "\n! Ошибка: не удалось осваободить память!";
    else
        cout << "\n> Отображённая память освободилась успешно.";
    if (!CloseHandle(myFileMapping))
        cout << "\n! Ошибка: не удалось закрытиь файловое сообщение";
    else
        cout << "\n> Файловое отображение успешно закрыто.";
    if (!CloseHandle(myFile))
        cout << "\n! Ошибка: не удалось закрыть файл!";
    else
        cout << "\n> Файл успешно закрыт.";
    cout << "\n\n";
    delete[] myFileMemory;
    
    system("pause");
    //delete[] myNewFileMemory;
    return 0;
}

