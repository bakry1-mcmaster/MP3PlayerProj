#include <iostream>
#include <filesystem>
#include <windows.h>
#include <mmsystem.h>
#include <string>
#include "conio.h"


#pragma comment(lib, "Winmm.lib")

//Use this to compile: g++ mp3file.cpp -o mp3file.exe -lwinmm


namespace file = std::filesystem;

int main(void)
{
    file::path currentPath = "C:/Personal Coding Projects/FilePractice/Songs";

    bool exit = false;

    while(!exit)
    {
        for(const auto& dirEntry : file::directory_iterator(currentPath)){

            if(dirEntry.is_regular_file())
            {
                //std::cout<<"Playing test music\n";
                //std::cout<<dirEntry.path()<<std::endl;


                std::string directoryPath = dirEntry.path().string();
                std::string filename = dirEntry.path().filename().string();
                std::cout<<"Playing: "<<filename<<std::endl;
                PlaySoundA(directoryPath.c_str(), NULL, SND_FILENAME|SND_ASYNC);

                bool skip = false;

                while(!skip)
                {
                    if(_kbhit())
                    {
                        char inputted = getch();
                        if(inputted == 32)
                        {
                            PlaySoundA(NULL, 0, 0);
                            std::cout<<"Going to next song lets gooo"<<std::endl;
                            skip = true;
                        }

                        else if(inputted == 'a')
                        {
                            exit = true;
                            skip = true;
                            std::cout<<"Goodbye";
                            break;
                        }
                    }
                    Sleep(100); //Apparently we need this to prevent too much cpu usage for micro
                }
            }

            if(exit)
                break;
        }
    }
    return 0;
}
