#include <fstream>
#include <iostream>
#include <operator.hpp>
#include <string>

// Домогацкий Иван ПС-22

// Среда выполнения:
// Apple clang version 16.0.0 (clang-1600.0.26.3)
// Target: arm64-apple-darwin24.6.0
// Thread model: posix

// 25. Программа  на ПАСКАЛЕ включает такие сочетания ключевых
// слов, как  REPEAT..UNTIL, RECORD..END, CASE..END и BEGIN..END.
// Некоторые части программы могут быть  закомментированы, другие
// части текста могут представлять собой  константы в апострофах.
// Требуется проверить правильность вложенности этих  конструкций
// с  учетом  допустимости  взаимных  вложений.  В случае  ошибок
// указать номер первой некорректной строки (11).

bool isWordDelimiter(char c) {
  if (std::isalnum(static_cast<unsigned char>(c)) || c == '_') {
    return false;
  }

  return true;
}

int main(int argc, char *argv[]) {
  std::string filename;

  if (argc > 1) {
    filename = argv[1];
  } else {
    std::cout << "Enter filename: ";
    std::getline(std::cin, filename);
  }

  if (filename.empty()) {
    std::cerr << "Error: Filename cannot be empty!" << std::endl;
    return 1;
  }

  std::ifstream file(filename);
  if (!file.is_open()) {
    std::cerr << "Error: Cannot open file '" << filename << "'!" << std::endl;
    return 1;
  }

  std::cout << "File '" << filename << "' opened successfully!" << std::endl;

  std::stack<Operator> operatorsStack;

  file.close();
}