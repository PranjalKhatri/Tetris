#include "..\include\utils.hpp"


FileOps::FileOps(std::string name)
{
    f_name = name;
}

void FileOps::Write(std::string message)
{
    std::fstream f(f_name, std::ios_base::app);
    if (f.is_open()) {
        f << message;
    }
    else {
        std::cout << "Unable to open the file\n";
    }
    f.close();
}

std::vector<std::string> FileOps::read() {
    std::fstream f(f_name, std::ios_base::in);
    while (!f.eof())
    {
        std::string s;
        std::getline(f, s);
        lines.push_back(s);
    }
    f.close();
    return lines;
}

void FileOps::clear() {
    std::fstream f(f_name, std::ios_base::out | std::ios_base::trunc);

    f.close();
}
