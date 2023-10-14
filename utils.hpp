#ifndef __UTILS_HPP_
#define __UTILS_HPP_

#include<stdlib.h>
#include<time.h>
#include<fstream>
#include <iostream>
class Random
{
private:
public:
    Random();
    int GetRandomNumber(int lb,int ub);
    int GetRandomNumber(int range);
};

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
    std::fstream f(f_name,std::ios_base::app | std::ios_base::in);
    f<<message;
    f.close();
}




#endif