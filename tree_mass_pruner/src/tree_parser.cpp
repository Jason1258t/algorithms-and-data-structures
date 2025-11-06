#include "tree_parser.hpp"
#include <fstream>
#include <sstream>
#include <stack>
#include <stdexcept>

std::unique_ptr<TreeNode> TextTreeParser::parse(std::ifstream &file)
{
    std::string line;
    std::stack<std::pair<TreeNode *, int>> stack; // узел и его глубина
    std::unique_ptr<TreeNode> root = nullptr;

    while (std::getline(file, line))
    {
        if (line.empty())
            continue;

        // Определяем глубину по количеству точек
        int depth = 0;
        size_t pos = 0;
        while (pos < line.length() && line[pos] == '.')
        {
            depth++;
            pos++;
        }

        // Парсим оставшуюся часть строки
        std::string rest = line.substr(pos);
        std::istringstream iss(rest);

        char typeChar;
        std::string name;
        int weight;

        if (!(iss >> typeChar >> name >> weight))
        {
            throw std::runtime_error("Invalid line format: " + line);
        }

        // Определяем тип узла
        NodeType type;
        if (typeChar == 'a' || typeChar == 'A')
        {
            type = NodeType::AND;
        }
        else if (typeChar == 'o' || typeChar == 'O')
        {
            type = NodeType::OR;
        }
        else
        {
            throw std::runtime_error("Unknown node type: " + std::string(1, typeChar));
        }

        // Создаем узел
        auto node = std::make_unique<TreeNode>(type, weight, name);

        // Обрабатываем глубину
        if (depth == 0)
        {
            // Корневой узел
            root = std::move(node);
            stack.push({root.get(), 0});
        }
        else
        {
            // Находим родителя
            while (!stack.empty() && stack.top().second >= depth)
            {
                stack.pop();
            }

            if (stack.empty())
            {
                throw std::runtime_error("Invalid depth in line: " + line);
            }

            // Добавляем как ребенка
            TreeNode *parent = stack.top().first;
            parent->addChild(std::move(node));

            // Добавляем в стек новый узел
            TreeNode *newNode = parent->getChildren().back().get();
            stack.push({newNode, depth});
        }
    }

    if (!root)
    {
        throw std::runtime_error("Empty tree file");
    }

    return root;
}