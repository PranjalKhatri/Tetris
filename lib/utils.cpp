#include "..\include\utils.hpp"

int Random::GetRandomNumber(int range) {
    return ((rand() % range));
}
int Random::GetRandomNumber(int ub, int lb) {
    int rd = lb + (rand() % (ub - lb + 1));
    return rd;
}
Random::Random()
{
    srand(time(NULL));
}

FileOps::FileOps(std::string name)
{
    f_name = name;
}

void FileOps::Write(std::string message)
{
    std::string msg = message;
    std::fstream f(f_name, std::ios_base::app);
    if (f.is_open()) {
        f << message;
        f << std::endl;
    }
    else {
        std::cout << "Unable to open the file\n";
    }
    // f << std::endl;
    f.close();
}

std::vector<std::string> FileOps::read() {
    /// @brief individual lines of the file
    std::vector<std::string> lines;
    std::string str;
    std::ifstream f(f_name);
    if (!f.is_open()) {
        std::cout << "Failed to open file.. ERROR 1598\n";
        return std::vector<std::string>();
    }
    while (!f.eof())
    {
        std::getline(f, str);
        lines.push_back(str);
    }
    f.close();
    // std::cout << lines.size();
    return lines;
}

void FileOps::clear() {
    std::fstream f(f_name, std::ios_base::out | std::ios_base::trunc);

    f.close();
}
