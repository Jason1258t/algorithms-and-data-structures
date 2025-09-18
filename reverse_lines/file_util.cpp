#include "file_util.h"
#include <iostream>
#include <stdexcept>

void initializeFiles(std::ifstream &infile, std::ofstream &outfile,
                     const int &argc, char *argv[])
{
    std::string inputFilename;
    std::string outputFilename;

    if (argc == 3)
    {
        inputFilename = argv[1];
        outputFilename = argv[2];
    }
    else
    {
        std::cout << "Введите имя входного файла: ";
        std::getline(std::cin, inputFilename);

        std::cout << "Введите имя выходного файла: ";
        std::getline(std::cin, outputFilename);
    }

    if (inputFilename.empty() || outputFilename.empty())
    {
        std::cout << "Имена файлов не могут быть пустыми!" << std::endl;
        throw std::invalid_argument("file names must be provided");
    }

    infile.open(inputFilename, std::ios::binary);
    outfile.open(outputFilename, std::ios::binary);

    if (!checkFileOpen(infile, inputFilename) ||
        !checkFileOpen(outfile, outputFilename))
    {
        throw std::runtime_error("provided files cannot be opened");
    }

    std::cout << "Файлы успешно открыты!" << std::endl;
    std::cout << "Входной файл: " << inputFilename << std::endl;
    std::cout << "Выходной файл: " << outputFilename << std::endl;
}