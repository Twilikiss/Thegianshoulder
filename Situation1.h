#ifndef SITUATION1_H
#define SITUATION1_H
#include"situation.h"

class Situation1
{
public:

    Situation cheer[6][6];

    Situation1() ;
    Situation1 *son[60];
    Situation1 *parent;
    int childNum = 0;
    bool occupy = false;
    double count  = 0;                 //访问次数
    double winCount = 0;               //胜利次数
    double ucb = 0.0;
    bool end = false;

};
class MaybeChain
{
public:
    int x=-1;
    int y=-1;
};

#endif // SITUATION1_H
