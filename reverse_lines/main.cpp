#include <iostream>
#include <fstream>
#include <string>
#include "file_util.h"
#include "string_utils.h"

const int BLOCK_SIZE = 8192;      // Размер блока для чтения, равен 8кб как оптимальный для работы с OS
const int MAX_LINES_BUFFER = 100; // Максимальное количество строк в буфере, подобрано как что-то среднее между экномией памяти и скоростью

struct Line
{
    char data[256];
    int length;

    Line(const char *str, int size)
    {
        stringCopy(data, str);
        length = size;
    }
};

int getReadBlockSize(const int currentPos)
{
    int blockToRead = (currentPos >= BLOCK_SIZE) ? BLOCK_SIZE : (int)currentPos;
    return blockToRead;
}

void writeBufferToFile(std::ofstream &outputFile, std::vector<Line> &lineBuffer)
{
    for (int i = 0; i < lineBuffer.size(); i++)
    {
        outputFile.write(lineBuffer[i].data, lineBuffer[i].length);
        outputFile.put('\n');
    }
    lineBuffer.clear();
}

int main(int argc, char *argv[])
{
    std::ifstream inputFile;
    std::ofstream outputFile;

    try
    {
        initializeFiles(inputFile, outputFile, argc, argv);
    }
    catch (std::exception e)
    {
        std::cout << "Exception: " << e.what() << std::endl;
    }

    inputFile.seekg(0, std::ios::end);
    std::streampos fileSize = inputFile.tellg();

    std::vector<Line> lineBuffer;
    lineBuffer.reserve(MAX_LINES_BUFFER);

    char block[BLOCK_SIZE];
    char currentLine[256];
    int linePos = 0;

    std::streampos currentPos = fileSize;

    while (currentPos > 0)
    {
        const int blockSize = getReadBlockSize(currentPos);
        currentPos -= blockSize;

        inputFile.seekg(currentPos);
        inputFile.read(block, blockSize);

        for (int i = blockSize - 1; i >= 0; i--)
        {
            char ch = block[i];

            if (isLineEnding(ch))
            {
                currentLine[linePos] = '\0';
                Line line = Line(currentLine, linePos);
                reverseString(line.data);

                lineBuffer.push_back(line);
                if (lineBuffer.size() >= MAX_LINES_BUFFER)
                {
                    writeBufferToFile(outputFile, lineBuffer);
                }

                linePos = 0;
            }
            else
            {
                currentLine[linePos++] = ch;
            }
        }
    }

    if (linePos > 0)
    {
        reverseString(currentLine);
        Line line = Line(currentLine, linePos);
        if (lineBuffer.size() >= MAX_LINES_BUFFER)
        {
            writeBufferToFile(outputFile, lineBuffer);
        }
        lineBuffer.push_back(line);

        writeBufferToFile(outputFile, lineBuffer);
    }

    inputFile.close();
    outputFile.close();
    return 0;
}