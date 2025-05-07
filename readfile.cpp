#include <iostream>
#include <fstream>

using namespace std;


int main(void)
{
    ofstream testFile("testfile.txt");

    testFile<< "We are seeing if we can write to a file";

    testFile.close();

    return 0;
}