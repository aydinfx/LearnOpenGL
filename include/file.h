#pragma once

#include <fstream>
#include <sstream>
#include <iostream>
#include <optional>

std::optional<std::string> readFile(const std::string &filePath)
{
    std::ifstream file(filePath);

    if (!file)
    {
        std::cerr << "Failed to open file: " << filePath << '\n';
        return std::nullopt;
    }

    std::stringstream buffer;
    buffer << file.rdbuf();

    return buffer.str();
}
