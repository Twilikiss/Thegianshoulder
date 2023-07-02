#ifndef AI_SMALL_H
#define AI_SMALL_H

#include"widget.h"
#include"Situation1.h"
#include"situation.h"
#include <string>
#include"ThreadForAI.h"
#include <QWidget>
#include <QPainter>
#include<QPoint>
#include"point.h"
#include"checks.h"
#include <QFrame>
#include <QThread>
#include <QMap>
#include"situation.h"
#include"Situation1.h"
#include<QJsonArray>
#include<QJsonObject>
#include<QJsonDocument>
#include<QJsonValue>
using namespace  std;
extern string path ;
//最终版本
class AI_small
{
public:
    AI_small();

    //缩减版AI
    int singlechain = 0;
    int doublechain = 0;
    int fanshuagnjiao = 0;
    int Searched[6][6];
    chu trifree;

    void mutualoccupy1(Situation Square[6][6], int x, int y, int k);
    int SingleChain(Situation Square[6][6], int x, int y);
    int DoubleChain(Situation Square[6][6], int x, int y);
    int Count_AntDoublecorse(Situation Square[6][6]);
    bool Dead(Situation Square[6][6]);
    int Triple_Freedom(Situation Square[6][6], int x, int y);
    void copy1(Situation  from[6][6], Situation  to[6][6]);
    int heixiazi1(Situation Square[6][6],chu *move, int len);
    int heixiazi2(Situation Square[6][6],chu *move, int len);
    int three_count(Situation Square[6][6], int *Num2_2);

};

#endif // AI_SMALL_H
