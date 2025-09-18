#ifndef FILE_UTILS_H
#define FILE_UTILS_H

#include <fstream>
#include <iostream>
#include <string>

template <typename FileStream>
bool checkFileOpen(FileStream &file, const std::string &filename)
{
    if (!file.is_open())
    {
        std::cout << "Ошибка открытия файла: " << filename << std::endl;
        return false;
    }
    return true;
}

void initializeFiles(std::ifstream &infile, std::ofstream &outfile,
                     const int &argc, char *argv[]);

#endif