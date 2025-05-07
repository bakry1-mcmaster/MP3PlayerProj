#include <iostream>
#include <windows.h>
#include <mmsystem.h>

#pragma comment(lib, "Winmm.lib")

using namespace std;

int main(void)
{
    cout<<"Playing test music\n";
    PlaySound(TEXT("megalovania.wav"), NULL, SND_FILENAME);
    cout<<"Music Over\n";


    return 0;
}

//g++ mp3file.cpp -o mp3file.exe -lwinmm