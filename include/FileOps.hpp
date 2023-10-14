#ifndef __FILEOPS_HPP__
#define __FILEOPS_HPP__
#include <iostream>
#include <fstream>
class FileOps
{
private:
    std::string f_name;
public:
    FileOps(std::string name);
    ~FileOps() = default;
    void Write(std::string message);
};

FileOps::FileOps(std::string name)
{
    f_name = name;
}

void FileOps::Write(std::string message)
{
    std::fstream f(f_name, std::ios_base::app | std::ios_base::in);
    f << message;
    f.close();
}
#endif