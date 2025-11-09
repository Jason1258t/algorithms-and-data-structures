#include <iostream>
#include <fstream>
#include <string>
#include "parser.hpp"
#include "print.hpp"
#include "path_finder.hpp"

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

void printMenu()
{
    std::cout << "\n=== Меню ===" << std::endl;
    std::cout << "1. Найти пути из столицы" << std::endl;
    std::cout << "2. Сменить столицу" << std::endl;
    std::cout << "3. Выход" << std::endl;
    std::cout << "Выберите опцию: ";
}

int main(int argc, char *argv[])
{
    std::string placesFilename;
    std::string roadsFilename;
    int start;

    if (argc == 4)
    {
        start = std::stoi(argv[1]);
        placesFilename = argv[2];
        roadsFilename = argv[3];
    }
    else
    {
        std::cout << "Enter place filename: ";
        std::cin >> placesFilename;

        std::cout << "Enter roads filename: ";
        std::cin >> roadsFilename;

        std::cout << "Enter start place id: ";
        std::cin >> start;
    }

    std::cout << "Загрузка данных..." << std::endl;
    std::unordered_map<int, Place> graph = Parser::parse(placesFilename, roadsFilename);
    std::cout << "Данные успешно загружены!" << std::endl;

    bool running = true;
    while (running)
    {
        printMenu();

        int choice;
        std::cin >> choice;

        switch (choice)
        {
        case 1:
        {
            std::unordered_map<int, Way> ways = PathFinder::findWays(graph, start);
            printDetailedWays(ways, graph);
            break;
        }
        case 2:
        {
            std::cout << "Введите новый ID столицы: ";
            std::cin >> start;
            std::cout << "Столица изменена на город с ID: " << start << std::endl;
            break;
        }
        case 3:
        {
            // Выход
            running = false;
            std::cout << "Выход из программы..." << std::endl;
            break;
        }
        default:
        {
            std::cout << "Неверный выбор. Попробуйте снова." << std::endl;
            break;
        }
        }
    }

    return 0;
}