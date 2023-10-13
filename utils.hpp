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

int Random::GetRandomNumber(int range){
    return ((rand()%range));
}
int Random::GetRandomNumber(int ub, int lb){
    int rd = lb + (rand() % (ub - lb + 1));
    return rd;
}
Random::Random()
{
    srand(time(NULL));
}

#endif