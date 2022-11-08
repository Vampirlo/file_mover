#include <iostream>
#include <string>
#include <fstream>
#include <filesystem>
#include <windows.h> // перед WinBase нужно включить виндовс, иначе очень страшно становится 
#include <WinBase.h>

using namespace std;

int main()
{
    string gtaPath;
    string dll_Asi_PAth;
    string disabledModsPath;
    string oldPath;
    string newPath;
    int action;
    char* dll_Asi_Name = new char[1024];

    // считываем путь к игре
    ifstream in;
    in.open("path.dat", ios::out); // окрываем файл для чтения
    if (in.is_open())
    {
        in >> gtaPath;
        in.close();
    }
    // проверка(создание) существования директории, куда/откуда будут перемещены файлы
    cout << "creating disabledMods directory" << endl;

    disabledModsPath = gtaPath + "\\disabledMods";
    auto cdResult = std::filesystem::create_directory(disabledModsPath);
    if (cdResult)
        cout << "directory successfully created" << endl;
    else
    {
        cout << "directory already exists" << endl;
    }
    // EOF в компьютерной терминологии является индикатором операционной системы, означающим, что данные в источнике закончились.
    cout << gtaPath << endl << disabledModsPath << endl;
    // считываю название dll/asi, конкатанирую строку с путём игры, movefile
    ifstream _in;
    _in.open("DLLASIname.dat", ios::out);

wrong_action:

    cout << "1 - to disabledMods" << endl << "2 - from disabledMods" << endl;
    cin >> action;

    if (action == 1)
    {
        goto to_disabledMods;
    }
    else if (action == 2)
    {
        goto from_disabledMods;
    }
    else
    {
        cout << "wrong action, enter right number" << endl;
        goto wrong_action;
    }

to_disabledMods:

    while (!_in.eof())
    {
        _in.getline(dll_Asi_Name, 1024, '\n');                                           // считываем файл

        oldPath = gtaPath + "\\" + dll_Asi_Name;                                         // текущий путь файла
        newPath = disabledModsPath + "\\" + dll_Asi_Name;                                // новый путь файла

        wstring wstroldPath(oldPath.begin(), oldPath.end());                    // преобразовываем строку в wstring
        wstring wstrnewPath(newPath.begin(), newPath.end());                    //
        bool mfResult = MoveFile(wstroldPath.c_str(), wstrnewPath.c_str());     // перемещаем файл
        cout << "File: " << dll_Asi_Name << " was moved" << endl;
    }
    _in.close();
    return 0;

from_disabledMods:

    while (!_in.eof())
    {
        _in.getline(dll_Asi_Name, 1024, '\n');

        oldPath = gtaPath + "\\" + dll_Asi_Name;
        newPath = disabledModsPath + "\\" + dll_Asi_Name;

        wstring wstroldPath(oldPath.begin(), oldPath.end());                    // преобразовываем строку в wstring
        wstring wstrnewPath(newPath.begin(), newPath.end());                    //
        bool mfResult = MoveFile(wstrnewPath.c_str(), wstroldPath.c_str());     // перемещаем файл
        cout << "File: " << dll_Asi_Name << " was moved" << endl;
    }
    _in.close();
    return 0;
}