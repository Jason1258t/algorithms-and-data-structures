#include <iostream>
#include <fstream>
#include <string>

// Домогацкий Иван ПС-22

// Среда выполнения:
// Apple clang version 16.0.0 (clang-1600.0.26.3)
// Target: arm64-apple-darwin24.6.0
// Thread model: posix


// 26. Имеется сеть автомобильных дорог. По  некоторым дорогам
// можно  проехать  только  в одном  направлении. Известна  длина 
// каждой дороги, причем она может быть разной в  зависимости  от 
// направления. Один  из  городов  является  столицей.  Требуется
// вывести список длин вторых по минимальности путей из столицы в 
// другие города. Допускается присутствие циклических путей (12).

std::ifstream openFile(int argc, char *argv[])
{
    std::string filename;

    if (argc > 1)
    {
        filename = argv[1];
    }
    else
    {
        std::cout << "Enter filename: ";
        std::getline(std::cin, filename);
    }

    if (filename.empty())
    {
        throw std::runtime_error("Error: Filename cannot be empty!");
    }

    std::ifstream file(filename);
    if (!file.is_open())
    {
        throw std::runtime_error("Error: Cannot open file '" + filename + "'!");
    }

    std::cout << "File '" << filename << "' opened successfully!" << std::endl;
    return file;
}

int main(int argc, char *argv[])
{

}