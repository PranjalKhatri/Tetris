#ifndef __UTILS_HPP_
#define __UTILS_HPP_

#include<stdlib.h>
#include<time.h>

class Random
{
private:
public:
    Random();
    int GetRandomNumber(int lb,int ub);
    int GetRandomNumber(int range);
};

#endif