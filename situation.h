#ifndef SITUATION_H
#define SITUATION_H
#include"Box.h"

struct chains {
    Box a[15];
    int count;
};

struct Situation {
    //public:
    char ower;    //拥有者
    char edge[4]; //四条边
    int degree;   //自由度
                  //int count;

};

struct  zhSituation1 {
    int a;
    int b;
    int c;
    int check;
};
struct chu
{

    int k;                      //边所在格子方位
    int x;			//格子行号
    int y;			//格子列号
    int lose_box;

};

#endif // SITUATION_H
