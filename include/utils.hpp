#ifndef __UTILS_HPP_
#define __UTILS_HPP_

#include<stdlib.h>
#include<time.h>
#include <fstream>
#include <iostream>
#include <vector>
class Random
{
private:
public:
    Random();
    int GetRandomNumber(int lb, int ub);
    int GetRandomNumber(int range);
};

class FileOps
{
private:
    /// @brief name of the file
    std::string f_name;

public:
    /// @brief Initialises the class and set the file name
    /// @param name name of file to use
    FileOps(std::string name);
    ~FileOps() = default;
    /// @brief Writes the given string to the file in append mode
    /// @param message message to write
    void Write(std::string message);
    /// @brief reads the lines from the file
    /// @return a vector of strings each corresponding to a different line in order
    std::vector<std::string> read();
    /// @brief Clears the content of the file
    void clear();
};

#endif