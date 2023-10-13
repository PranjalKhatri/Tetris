#include "utils.hpp"

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

template <class T>
void Vector2<T>::set(T x,T y){
    this->x = x;
    this->y  =y;
}