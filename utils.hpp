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

template <class T>
class Vector2
{
private:
    T x;
    T y;
public:
    Vector2() = default;
    void set(T x,T y);
    ~Vector2() = default;
};


#endif