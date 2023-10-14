#include "..\include\utils.hpp"

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
