#include <iostream>
#include <filesystem>
#include <windows.h>
#include <string>
#include "conio.h"

// Use this to compile: g++ mp3file.cpp -o mp3file.exe -lwinmm

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
                std::string directoryPath = dirEntry.path().string();
                std::string filename = dirEntry.path().filename().string();
                std::cout << "Playing: " << filename << std::endl;

                // Use mciSendString to play the WAV file
                std::string commandline = "open \"" + directoryPath + "\" type mpegvideo alias song";
                mciSendString(commandline.c_str(), NULL, 0, NULL);
                mciSendString("play song", NULL, 0, NULL);

                bool skip = false;
                bool pause = false;

                while(!skip)
                {
                    if(_kbhit())
                    {
                        char inputted = getch();
                        if(inputted == 32)
                        {
                            std::cout << "Going to next song lets gooo" << std::endl;
                            skip = true;
                            mciSendString("stop song", NULL, 0, NULL); 
                            mciSendString("close song", NULL, 0, NULL);  // Stop the current song
                        }

                        else if(inputted == 'a')
                        {
                            exit = true;
                            skip = true;
                            std::cout << "Goodbye" << std::endl;
                            mciSendString("stop song", NULL, 0, NULL); 
                            mciSendString("close song", NULL, 0, NULL);  // Stop the current song
                            break;
                        }

                        else if(inputted == 'p')
                        {
                            if(pause == true)
                            {
                                pause = false;
                                mciSendString("resume song", NULL, 0, NULL);
                            }
                            else if(pause == false)
                            {
                                mciSendString("pause song", NULL, 0, NULL);
                                pause = true;
                            }  

                        }
                    }
                    Sleep(100); // Prevent excessive CPU usage
                }
            }

            if(exit)
                break;
        }
    }
    return 0;
}
