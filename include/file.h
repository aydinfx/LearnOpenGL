#pragma once

#include <cstdio>
#include <fstream>
#include <sstream>
#include <optional>

namespace File
{
    /// @brief Reads the contents of a file.
    /// @param path The path to the file.
    /// @return The file contents if the file was successfully read, std::nullopt otherwise.
    inline std::optional<std::string> read(const std::string &path)
    {
        std::ifstream file(path);

        if (!file.is_open())
        {
            fprintf(stderr, "failed to open file for reading: %s\n", path);
            return std::nullopt;
        }

        std::ostringstream buffer;
        buffer << file.rdbuf();

        return buffer.str();
    }

    /// @brief Writes content to a file, replacing any existing content.
    /// @param path The path to the file.
    /// @param content The content to write to the file.
    /// @return true if the content was successfully written, false otherwise.
    inline bool write(const std::string &path, const std::string &content)
    {
        std::ofstream file(path);

        if (!file.is_open())
        {
            fprintf(stderr, "failed to open file for writing: %s\n", path);
            return false;
        }

        file << content;

        if (!file.fail())
        {
            fprintf(stderr, "failed to write to file: %s\n", path);
            return false;
        }

        return true;
    }

    /// @brief Appends content to the end of a file.
    /// @param path The path to the file.
    /// @param content The content to append to the file.
    /// @return true if the content was successfully appended, false otherwise.
    inline bool append(const std::string &path, const std::string &content)
    {
        std::ofstream file(path, std::ios::app);

        if (!file.is_open())
        {
            fprintf(stderr, "failed to open file for appending: %s\n", path);
            return false;
        }

        file << content;

        if (!file.fail())
        {
            fprintf(stderr, "failed to append to file: %s\n", path);
            return false;
        }

        return true;
    }
}
