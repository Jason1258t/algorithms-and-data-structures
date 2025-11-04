#include <fstream>
#include <iostream>
#include "operator_factory.hpp"
#include "tokenizer.hpp"
#include "logger.hpp"

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
  std::ifstream file;
  try
  {
    file = openFile(argc, argv);
  }
  catch (const std::exception &ex)
  {
    std::cerr << ex.what() << '\n';
    return 1;
  }

  OperatorFactory factory;
  Logger logger(std::cout, LoggerMode::normal);
  Tokenizer tokenizer(factory, logger);

  std::string line;
  int lineNumber = 0;

  try
  {
    while (std::getline(file, line))
    {
      ++lineNumber;
      tokenizer.processLine(line, lineNumber);
    }

    if (tokenizer.hasUnclosedOperators())
    {
      Operator top = tokenizer.getTopUnclosedOperator();
      throw ParserError("missing closing token '" + top.closeToken +
                        "' for '" + top.startToken + "' (opened at line " +
                        std::to_string(top.line) + ")");
    }

    file.close();
    std::cout << "Syntax nesting is correct.\n";
    return 0;
  }
  catch (const ParserError &e)
  {
    std::cerr << "Error: " << e.what() << std::endl;
    file.close();
    return e.getExitCode();
  }
  catch (const std::exception &e)
  {
    std::cerr << "Unexpected error: " << e.what() << std::endl;
    file.close();
    return 1;
  }
}