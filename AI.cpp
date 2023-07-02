#include "AI.h"
#include"Situation1.h"

#include"widget.h"
#include<QMessageBox>
#include<QTimer>
#include<QDebug>
#include"Ai_uct.h"
#include<qDebug>

#include<QTimerEvent>
#include<sstream>
//---------------------------------
#include <iostream>
#include<algorithm>
#include <fstream>
#include <iostream>
#include<cmath>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include <sstream>
#include<vector>
#include <ctime>
#include <fstream>
#include<Qfile>
#include<QString>
#include<QJsonArray>
#include<QJsonDocument>
#include<QJsonObject>
#include<QJsonParseError>
#include<QJsonValue>
#include<QStringList>
#include<QDateTime>
#define random(x)(rand()%x)
#define Max_deep	8				//模糊搜索最大深度
#define Max_len		25				//精确深度最大深度
using namespace std;

int chainNum = 0;
int longestChainLength = 0;
int free1 = 0;
int free2 = 0;
int free3 = 0;
int free4 = 0;
int circlenum = 0;
int guaidian = 0;


int flag;
Situation first[6][6];
MaybeChain maybeChain[25];
MaybeChain maybeCircle[25];
chu trifree;
AI::AI()
{

    chi=0;
    text = 0;
    chaincount = 60;
    mycount = 0;
    hecount = 0;
    factcheer[0][0].degree = 60;
    timeblack=0;
    timewhite=0;

    myturn=1;
    turn = myturn;
    //信号关联
    connect(&ai_thread1, SIGNAL(finished()), this, SLOT(Threadfinish()));

}



void AI::Initial_All(){

}

AI::~AI()
{
    ai_thread1.wait();  //等待线程执行完毕
}

//线程所用
void AI::Threadfinish()
{
    qDebug()<<"子线程已完成------------!!!";


}


//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------

void AI::copy(Situation1  from, Situation1  to)
{
    for (int i = 1; i < 6; i++)
        for (int j = 1; j < 6; j++)

        {
            to.cheer[i][j].ower = from.cheer[i][j].ower;
            to.cheer[i][j].degree = from.cheer[i][j].degree;
            to.cheer[i][j].edge[0] = from.cheer[i][j].edge[0];
            to.cheer[i][j].edge[1] = from.cheer[i][j].edge[1];
            to.cheer[i][j].edge[2] = from.cheer[i][j].edge[2];
            to.cheer[i][j].edge[3] = from.cheer[i][j].edge[3];
        }


}

void AI::copy1(Situation  from[6][6], Situation  to[6][6])
{
    for (int i = 0; i < 6; i++)
        for (int j = 0; j < 6; j++)

        {
            to[i][j].ower = from[i][j].ower;
            to[i][j].degree = from[i][j].degree;
            to[i][j].edge[0] = from[i][j].edge[0];
            to[i][j].edge[1] = from[i][j].edge[1];
            to[i][j].edge[2] = from[i][j].edge[2];
            to[i][j].edge[3] = from[i][j].edge[3];
        }
}
//下棋函数，输入函数，占领格子，减去自由度
void AI::putcheer(Situation Square[6][6], int x, int y, int k, int turn)
{

    if (turn == 1)
    {
        Square[x][y].edge[k] = '*';
        Square[x][y].degree--;
        mutualoccupy1(Square, x, y, k);

    }
    else
    {
        Square[x][y].edge[k] = '#';
        Square[x][y].degree--;
        mutualoccupy1(Square, x, y, k);

    }


}//敌方轮， 是否占领格子
int AI::Dead2(Situation  Square[6][6])                         //判断是否占领格子，并占领，成功turn
{

    for (int x = 1; x<6; x++)
        for (int y = 1; y < 6; y++)
        {
            if (Square[x][y].degree == 0 && Square[x][y].ower == ' ')
            {
                Square[x][y].ower = 'B';
                hecount++;
                if(x==5&&y==5)
                return 1;
            }
        }

    return 0;

}
//判断占格
void AI::opc(Situation Square[6][6], int turn) {

    qDebug()<<"吃格子的人:"<<turn;
    for (int i = 1; i < 6; i++)
        for (int j = 1; j < 6; j++)
            if (Square[i][j].degree == 0 && Square[i][j].ower != 'A'&& Square[i][j].ower != 'B')
                if (turn == 1)
                {
                    Square[i][j].ower = 'A';

                    mycount++;
                }
                else
                {
                    Square[i][j].ower = 'B';


                    hecount++;
                }


}
int AI::move1(Situation Square[6][6], chu move[61]) ///////存储可下边
{


    int s = 0;
    for (int x = 1; x < 6; x++)
        for (int y = 1; y < 6; y++)
            for (int k = 0; k < 4; k++)
            {

                if (Square[x][y].edge[k] == '1') {
                    if(x!=5&&y!=5&&(k==0||k==1)){
                        move[s].k = k;
                        move[s].x = x;
                        move[s].y = y;
                        s++;
                    }else if (x!=5&&y==5&&k!=3) {
                        move[s].k = k;
                        move[s].x = x;
                        move[s].y = y;
                        s++;
                    }else if (x==5&&y!=5&&k!=2) {
                        move[s].k = k;
                        move[s].x = x;
                        move[s].y = y;
                        s++;
                    }else if (x==5&&y==5) {
                        move[s].k = k;
                        move[s].x = x;
                        move[s].y = y;
                        s++;
                    }

                }
            }


    return s;

}

int AI::move(Situation Square[6][6], chu *move) ///////存储可下边
{



    int s = 0;
    for (int x = 1; x < 6; x++)
        for (int y = 1; y < 6; y++)
            for (int k = 0; k < 4; k++)
            {

                if (Square[x][y].edge[k] == '1') {

                    if ((x > 1 && x < 5) && (y > 1 && y < 5))
                    {
                        if (Square[x][y].degree <= 2) { continue; }
                        else if (k == 0 && Square[x][y - 1].degree <= 2) { continue; }
                        else if (k == 1 && Square[x - 1][y].degree <= 2) { continue; }
                        else if (k == 2 && Square[x][y + 1].degree <= 2) { continue; }
                        else if (k == 3 && Square[x + 1][y].degree <= 2) { continue; }
                        else
                        {
                            if(k==0||k==1){
                                move[s].k = k;
                                move[s].x = x;
                                move[s].y = y;
                                s++;
                            }

                        }

                    }
                    else if (x == 1 && y > 1 && y < 5)
                    {
                        if (Square[x][y].degree <= 2) { continue; }
                        else if (k == 0 && Square[x][y - 1].degree <= 2) { continue; }
                        else if (k == 2 && Square[x][y + 1].degree <= 2) { continue; }
                        else if (k == 3 && Square[x + 1][y].degree <= 2) { continue; }
                        else
                        {
                            if(k==0||k==1){
                                move[s].k = k;
                                move[s].x = x;
                                move[s].y = y;
                                s++;
                            }
                        }

                    }//上3

                    else if (x == 5 && y > 1 && y < 5)
                    {
                        if (Square[x][y].degree <= 2) { continue; }
                        else if (k == 0 && Square[x][y - 1].degree <= 2) { continue; }
                        else if (k == 2 && Square[x][y + 1].degree <= 2) { continue; }
                        else if (k == 1 && Square[x - 1][y].degree <= 2) { continue; }
                        else
                        {
                            if(k==0||k==1||k==3){
                                move[s].k = k;
                                move[s].x = x;
                                move[s].y = y;
                                s++;
                            }
                        }


                    }//下3
                    else if (y == 1 && x > 1 && x < 5)
                    {
                        if (Square[x][y].degree <= 2) { continue; }
                        else if (k == 3 && Square[x + 1][y].degree <= 2) { continue; }
                        else if (k == 2 && Square[x][y + 1].degree <= 2) { continue; }
                        else if (k == 1 && Square[x - 1][y].degree <= 2) { continue; }
                        else
                        {
                            if(k==0||k==1){
                                move[s].k = k;
                                move[s].x = x;
                                move[s].y = y;
                                s++;
                            }
                        }


                    }//左3
                    else if (y == 5 && x > 1 && x < 5)
                    {
                        if (Square[x][y].degree <= 2) { continue; }
                        else if (k == 3 && Square[x + 1][y].degree <= 2) { continue; }
                        else if (k == 0 && Square[x][y - 1].degree <= 2) { continue; }
                        else if (k == 1 && Square[x - 1][y].degree <= 2) { continue; }
                        else
                        {
                            if(k==0||k==1||k==2){
                                move[s].k = k;
                                move[s].x = x;
                                move[s].y = y;
                                s++;
                            }
                        }


                    }//右3

                    else if (x == 1 && y == 1)
                    {
                        if (Square[x][y].degree <= 2) { continue; }
                        else if (k == 3 && Square[x + 1][y].degree <= 2) { continue; }
                        else if (k == 2 && Square[x][y + 1].degree <= 2) { continue; }
                        else
                        {
                            if(k==0||k==1){
                                move[s].k = k;
                                move[s].x = x;
                                move[s].y = y;
                                s++;
                            }
                        }



                    }//左上点
                    else if (x == 5 && y == 1)
                    {
                        if (Square[x][y].degree <= 2) { continue; }
                        else if (k == 2 && Square[x][y + 1].degree <= 2) { continue; }
                        else if (k == 1 && Square[x - 1][y].degree <= 2) { continue; }
                        else
                        {
                            if(k==0||k==1||k==3){
                                move[s].k = k;
                                move[s].x = x;
                                move[s].y = y;
                                s++;
                            }
                        }


                    }//左下点
                    else if (x == 1 && y == 5)
                    {
                        if (Square[x][y].degree <= 2) { continue; }
                        else if (k == 3 && Square[x + 1][y].degree <= 2) { continue; }
                        else if (k == 0 && Square[x][y - 1].degree <= 2) { continue; }
                        else
                        {
                            if(k==0||k==1||k==2){
                                move[s].k = k;
                                move[s].x = x;
                                move[s].y = y;
                                s++;
                            }
                        }



                    }//右上点
                    else
                    {
                        if (Square[x][y].degree <= 2) { continue; }
                        else if (k == 1 && Square[x - 1][y].degree <= 2) { continue; }
                        else if (k == 0 && Square[x][y - 1].degree <= 2) { continue; }
                        else
                        {
                            move[s].k = k;
                            move[s].x = x;
                            move[s].y = y;
                            s++;
                        }


                    }//右下点

                }
            }

    return s;
}

int AI::SingleChain(Situation Square[6][6], int x, int y)
{

    if (x == 1 && y == 1)            //左上
    {
        if (Square[x][y].edge[2] != '1' && Square[x][y].edge[3] != '1' && Square[x][y].degree == 2)
        {
            Searched[x][y] = 1;
            return 1;
        }
    }
    if (x == 1 && y == 5)            //右上
    {
        if (Square[x][y].edge[0] != '1'   && Square[x][y].edge[3] != '1' && Square[x][y].degree == 2)
        {
            Searched[x][y] = 1;
            return 1;
        }
    }
    if (x == 5 && y == 1)            //左下
    {
        if (Square[x][y].edge[1] != '1'  && Square[x][y].edge[2] != '1'  && Square[x][y].degree == 2)
        {
            Searched[x][y] = 1;
            return 1;
        }
    }
    if (x == 5 && y == 5)            //左下
    {
        if (Square[x][y].edge[0] != '1' && Square[x][y].edge[1] != '1'  && Square[x][y].degree == 2)
        {
            Searched[x][y] = 1;
            return 1;
        }
    }
    return 0;


}


int AI::DoubleChain(Situation Square[6][6], int x, int y)     //判断双链的情况
{

    if (x == 1 && y >= 1 && y <= 4)											//上边
    {
        if (Square[x][y].edge[1] == '1'  && Square[x][y].edge[2] == '1' && Square[x][y].degree == 2)
        {
            if (Square[x][y + 1].edge[1] == '1' && Square[x][y + 1].degree == 2)
            {
                Searched[x][y] = 1;
                Searched[x][y + 1] = 1;
                return 1;
            }
        }
    }
    if (x == 5 && y >= 1 && y <= 4)											//下边
    {
        if (Square[x][y].edge[3] == '1' && Square[x][y].edge[2] == '1' && Square[x][y].degree == 2)
        {
            if (Square[x][y + 1].edge[3] == '1' && Square[x][y + 1].degree == 2)
            {
                Searched[x][y] = 1;
                Searched[x][y + 1] = 1;
                return 1;
            }
        }
    }
    if (y == 1 && x >= 1 && x <= 4)											//左边
    {
        if (Square[x][y].edge[0] == '1' && Square[x][y].edge[3] == '1' && Square[x][y].degree == 2)
        {
            if (Square[x + 1][y].edge[0] == '1' && Square[x + 1][y].degree == 2)
            {
                Searched[x][y] = 1;
                Searched[x + 1][y] = 1;
                return 1;
            }
        }
    }
    if (y == 5 && x >= 1 && x <= 4)											//右边
    {
        if (Square[x][y].edge[2] == '1' && Square[x][y].edge[3] == '1' && Square[x][y].degree == 2)
        {
            if (Square[x + 1][y].edge[2] == '1' && Square[x + 1][y].degree == 2)
            {
                Searched[x][y] = 1;
                Searched[x + 1][y] = 1;
                return 1;
            }
        }
    }


    if (x == 1 && y == 1)                                                   //左上角
    {
        if (Square[1][1].edge[1] == '1' && Square[1][1].edge[3] == '1' && Square[1][1].degree == 2)
        {
            if (Square[2][1].edge[0] == '1' && Square[2][1].degree == 2)
            {
                Searched[2][1] = 1;
                Searched[x][y] = 1;
                return 1;
            }
        }
        if (Square[1][1].edge[0] == '1'&& Square[1][1].edge[2] == '1' && Square[1][1].degree == 2)
        {
            if (Square[1][2].edge[1] == '1' && Square[1][2].degree == 2)
            {
                Searched[1][2] = 1;
                Searched[x][y] = 1;
                return 1;
            }
        }
    }

    if (x == 1 && y == 5)                                                   //右上角
    {
        if (Square[1][5].edge[2] == '1' && Square[1][5].edge[0] == '1' && Square[1][5].degree == 2)
        {
            if (Square[1][4].edge[1] == '1' && Square[1][4].degree == 2)
            {
                Searched[1][4] = 1;
                Searched[x][y] = 1;
                return 1;
            }
        }
        if (Square[1][5].edge[1] == '1' && Square[1][5].edge[3] == '1' && Square[1][5].degree == 2)
        {
            if (Square[2][5].edge[2] == '1' && Square[2][5].degree == 2)
            {
                Searched[2][5] = 1;
                Searched[x][y] = 1;
                return 1;
            }
        }
    }

    if (x == 5 && y == 1)                                                   //左下角
    {
        if (Square[5][1].edge[3] == '1' && Square[5][1].edge[1] == '1' && Square[5][1].degree == 2)
        {
            if (Square[4][1].edge[0] == '1' && Square[4][1].degree == 2)
            {
                Searched[4][1] = 1;
                Searched[x][y] = 1;
                return 1;
            }
        }
        if (Square[5][1].edge[0] == '1' && Square[5][1].edge[2] == '1' && Square[5][1].degree == 2)
        {
            if (Square[5][2].edge[3] == '1' && Square[5][2].degree == 2)
            {
                Searched[5][2] = 1;
                Searched[x][y] = 1;
                return 1;
            }
        }
    }

    if (x == 5 && y == 5)                                                   //右下角
    {
        if (Square[5][5].edge[1] == '1' && Square[5][5].edge[3] == '1' && Square[5][5].degree == 2)
        {
            if (Square[4][5].edge[2] == '1' && Square[4][5].degree == 2)
            {
                Searched[4][5] = 1;
                Searched[x][y] = 1;
                return 1;
            }
        }
        if (Square[5][5].edge[0] == '1' && Square[5][5].edge[2] == '1' && Square[5][5].degree == 2)
        {
            if (Square[5][4].edge[3] == '1' && Square[5][4].degree == 2)
            {
                Searched[5][4] = 1;
                Searched[x][y] = 1;
                return 1;
            }
        }
    }
    return 0;
}

int AI::Triple_Freedom1(Situation Square[6][6], int x, int y)                //判断某三自由度格的情况
{
//    qDebug()<<"iiiiiiiiiiiiiiiiiii"<<x;
//    qDebug()<<"iiiiiiiiiiiiiiiiiii"<<y;
    if (Square[x][y].degree == 3)									//找到此三自由度格子
    {
        if (Square[x][y].edge[0] == '1')						//找到此自由个字的无边方向 若为左边
        {
            if (Square[x][y - 1].degree == 2 && y - 1>0 && !Searched[x][y - 1])						//临近三个格子自由度都为二 则不是反双交
            {
                if (Square[x][y - 1].edge[0] == '1')
                {
                    if ((Square[x][y - 2].degree == 3 || Square[x][y - 2].degree == 4) && y - 2>0 && !Searched[x][y - 2])
                    {

//                            qDebug()<<"2222222222222 1";

                        trifree.x = x;trifree.y = y;
                        Searched[x][y] = 1;
                        Searched[x][y - 1] = 1;
                        Searched[x][y - 2] = 1;
                        return 1;
                    }
                    if (Square[x][y - 2].degree == 2 && y - 2>0 && !Searched[x][y - 2])
                    {
                        if (Square[x][y - 2].edge[0] == '1')
                        {
                            if (Square[x][y - 3].degree == 3 || Square[x][y - 3].degree == 4)
                            {

//                                    qDebug()<<"2222222222222 2";

                                trifree.x = x;trifree.y = y;
                                Searched[x][y] = 1;
                                Searched[x][y - 1] = 1;
                                Searched[x][y - 2] = 1;
                                Searched[x][y - 3] = 1;
                                return 1;
                            }
                        }
                        if (Square[x][y - 2].edge[1] == '1')
                        {
                            if (Square[x - 1][y - 2].degree == 3 || Square[x - 1][y - 2].degree == 4)
                            {

//                                    qDebug()<<"2222222222222 3";

                                trifree.x = x;trifree.y = y;
                                Searched[x][y] = 1;
                                Searched[x][y - 1] = 1;
                                Searched[x][y - 2] = 1;
                                Searched[x - 1][y - 2] = 1;
                                return 1;
                            }
                        }
                        if (Square[x][y - 2].edge[3] == '1')
                        {
                            if (Square[x + 1][y - 2].degree == 3 || Square[x + 1][y - 2].degree == 4)
                            {
//                                    qDebug()<<"2222222222222 3";

                                trifree.x = x;trifree.y = y;
                                Searched[x][y] = 1;
                                Searched[x][y - 1] = 1;
                                Searched[x][y - 2] = 1;
                                Searched[x + 1][y - 2] = 1;
                                return 1;
                            }
                        }
                    }
                }
                if (Square[x][y - 1].edge[1] == '1')
                {
                    if ((Square[x - 1][y - 1].degree == 3 || Square[x - 1][y - 1].degree == 4) && x - 1>0 && !Searched[x - 1][y - 1])
                    {
//                            qDebug()<<"2222222222222 4";

                        trifree.x = x;trifree.y = y;
                        Searched[x][y] = 1;
                        Searched[x][y - 1] = 1;
                        Searched[x - 1][y - 1] = 1;
                        return 1;
                    }
                    if (Square[x - 1][y - 1].degree == 2 && x - 1>0 && !Searched[x - 1][y - 1])
                    {
                        if (Square[x - 1][y - 1].edge[0] == '1')
                        {
                            if (Square[x - 1][y - 2].degree == 3 || Square[x - 1][y - 2].degree == 4)
                            {
//                                    qDebug()<<"2222222222222 5";

                                trifree.x = x;trifree.y = y;
                                Searched[x][y] = 1;
                                Searched[x][y - 1] = 1;
                                Searched[x - 1][y - 1] = 1;
                                Searched[x - 1][y - 2] = 1;
                                return 1;
                            }
                        }
                        if (Square[x - 1][y - 1].edge[1] == '1')
                        {
                            if (Square[x - 2][y - 1].degree == 3 || Square[x - 2][y - 1].degree == 4)
                            {
//                                    qDebug()<<"2222222222222 6";

                                trifree.x = x;trifree.y = y;
                                Searched[x][y] = 1;
                                Searched[x][y - 1] = 1;
                                Searched[x - 1][y - 1] = 1;
                                Searched[x - 2][y - 1] = 1;
                                return 1;
                            }
                        }
                        if (Square[x - 1][y - 1].edge[2] == '1')
                        {
                            if (Square[x - 1][y].degree == 3 || Square[x - 1][y].degree == 4)
                            {
//                                    qDebug()<<"2222222222222 7";

                                trifree.x = x;trifree.y = y;
                                Searched[x][y] = 1;
                                Searched[x][y - 1] = 1;
                                Searched[x - 1][y - 1] = 1;
                                Searched[x - 1][y] = 1;
                                return 1;
                            }
                        }
                    }
                }
                if (Square[x][y - 1].edge[3] == '1')
                {
                    if ((Square[x + 1][y - 1].degree == 3 || Square[x + 1][y - 1].degree == 4) && x + 1<6 && !Searched[x + 1][y - 1])
                    {
//                            qDebug()<<"2222222222222 7";

                        trifree.x = x;trifree.y = y;
                        Searched[x][y] = 1;
                        Searched[x][y - 1] = 1;
                        Searched[x + 1][y - 1] = 1;
                        return 1;
                    }
                    if (Square[x + 1][y - 1].degree == 2 && x + 1<6 && !Searched[x + 1][y - 1])
                    {
                        if (Square[x + 1][y - 1].edge[0] == '1')
                        {
                            if (Square[x + 1][y - 2].degree == 3 || Square[x + 1][y - 2].degree == 4)
                            {
//                                    qDebug()<<"2222222222222 8";

                                trifree.x = x;trifree.y = y;
                                Searched[x][y] = 1;
                                Searched[x][y - 1] = 1;
                                Searched[x + 1][y - 1] = 1;
                                Searched[x + 1][y - 2] = 1;
                                return 1;
                            }
                        }
                        if (Square[x + 1][y - 1].edge[2] == '1')
                        {
                            if (Square[x + 1][y].degree == 3 || Square[x + 1][y].degree == 4)
                            {
//                                    qDebug()<<"2222222222222 9";

                                trifree.x = x;trifree.y = y;
                                Searched[x][y] = 1;
                                Searched[x][y - 1] = 1;
                                Searched[x + 1][y - 1] = 1;
                                Searched[x + 1][y] = 1;
                                return 1;
                            }
                        }
                        if (Square[x + 1][y - 1].edge[3] == '1')
                        {
                            if (Square[x + 2][y - 1].degree == 3 || Square[x + 2][y - 1].degree == 4)
                            {
//                                    qDebug()<<"2222222222222 10";

                                trifree.x = x;trifree.y = y;
                                Searched[x][y] = 1;
                                Searched[x][y - 1] = 1;
                                Searched[x + 1][y - 1] = 1;
                                Searched[x + 2][y - 1] = 1;
                                return 1;
                            }
                        }
                    }
                }
            }
        }
        if (Square[x][y].edge[1] == '1')						//找到此自由个字的无边方向 若为上边
        {
            if (Square[x - 1][y].degree == 2 && x - 1>0 && !Searched[x - 1][y])						//临近三个格子自由度都为二 则不是反双交
            {
                if (Square[x - 1][y].edge[0] == '1')
                {
                    if ((Square[x - 1][y - 1].degree == 3 || Square[x - 1][y - 2].degree == 4) && y - 1>0 && !Searched[x - 1][y - 1])
                    {
//                            qDebug()<<"2222222222222 11";

                        trifree.x = x;trifree.y = y;
                        Searched[x][y] = 1;
                        Searched[x - 1][y] = 1;
                        Searched[x - 1][y - 1] = 1;
                        return 1;
                    }
                    if (Square[x - 1][y - 1].degree == 2 && y - 1>0 && !Searched[x - 1][y - 1])
                    {
                        if (Square[x - 1][y - 1].edge[0] == '1')                        //hhkjhkjlhlkjhfaksdjhlasd
                        {
                            if (Square[x - 1][y - 2].degree == 3 || Square[x - 1][y - 2].degree == 4)
                            {
//                                    qDebug()<<"2222222222222 12";

                                trifree.x = x;trifree.y = y;
                                Searched[x][y] = 1;
                                Searched[x - 1][y] = 1;
                                Searched[x - 1][y - 1] = 1;
                                Searched[x - 1][y - 2] = 1;
                                return 1;
                            }
                        }
                        if (Square[x - 1][y - 1].edge[1] == '1')
                        {
                            if (Square[x - 2][y - 1].degree == 3 || Square[x - 2][y - 1].degree == 4)
                            {
//                                    qDebug()<<"2222222222222 13";

                                trifree.x = x;trifree.y = y;
                                Searched[x][y] = 1;
                                Searched[x - 1][y] = 1;
                                Searched[x - 1][y - 1] = 1;
                                Searched[x - 2][y - 1] = 1;
                                return 1;
                            }
                        }
                        if (Square[x - 1][y - 1].edge[3] == '1')
                        {
                            if (Square[x][y - 1].degree == 3 || Square[x][y - 1].degree == 4)
                            {
//                                    qDebug()<<"2222222222222 14";

                                trifree.x = x;trifree.y = y;
                                Searched[x][y] = 1;
                                Searched[x - 1][y] = 1;
                                Searched[x - 1][y - 1] = 1;
                                Searched[x][y - 1] = 1;
                                return 1;
                            }
                        }
                    }
                }
                if (Square[x - 1][y].edge[1] == '1')
                {
                    if ((Square[x - 2][y].degree == 3 || Square[x - 2][y].degree == 4) && x - 2>0 && !Searched[x - 2][y])
                    {
//                            qDebug()<<"2222222222222 15";

                        trifree.x = x;trifree.y = y;
                        Searched[x][y] = 1;
                        Searched[x - 1][y] = 1;
                        Searched[x - 2][y] = 1;
                        return 1;
                    }
                    if (Square[x - 2][y].degree == 2 && x - 2>0 && !Searched[x - 2][y])
                    {
                        if (Square[x - 2][y].edge[0] == '1')
                        {
                            if (Square[x - 2][y - 1].degree == 3 || Square[x - 2][y - 1].degree == 4){

//                                    qDebug()<<"2222222222222 16";

                                trifree.x = x;trifree.y = y;
                                Searched[x][y] = 1;
                                Searched[x - 1][y] = 1;
                                Searched[x - 2][y] = 1;
                                Searched[x - 2][y - 1] = 1;
                                return 1;
                            }
                        }
                        if (Square[x - 2][y].edge[1] == '1')
                        {
                            if (Square[x - 3][y].degree == 3 || Square[x - 3][y].degree == 4)
                            {
//                                    qDebug()<<"2222222222222 17";

                                trifree.x = x;trifree.y = y;
                                Searched[x][y] = 1;
                                Searched[x - 1][y] = 1;
                                Searched[x - 2][y] = 1;
                                Searched[x - 3][y] = 1;
                                return 1;
                            }
                        }
                        if (Square[x - 2][y].edge[2] == '1')
                        {
                            if (Square[x - 2][y + 1].degree == 3 || Square[x - 2][y + 1].degree == 4)
                            {
//                                    qDebug()<<"2222222222222 18";

                                trifree.x = x;trifree.y = y;
                                Searched[x][y] = 1;
                                Searched[x - 1][y] = 1;
                                Searched[x - 2][y] = 1;
                                Searched[x - 2][y + 1] = 1;
                                return 1;
                            }
                        }
                    }
                }
                if (Square[x - 1][y].edge[2] == '1')
                {
                    if ((Square[x - 1][y + 1].degree == 3 || Square[x - 1][y + 1].degree == 4) && y + 1<6 && !Searched[x - 1][y + 1])
                    {
//                            qDebug()<<"2222222222222 19";

                        trifree.x = x;trifree.y = y;
                        Searched[x][y] = 1;
                        Searched[x - 1][y] = 1;
                        Searched[x - 1][y + 1] = 1;
                        return 1;
                    }
                    if (Square[x - 1][y + 1].degree == 2 && y + 1<6 && !Searched[x - 1][y + 1])
                    {
                        if (Square[x - 1][y + 1].edge[3] == '1')
                        {
                            if (Square[x][y + 1].degree == 3 || Square[x][y + 1].degree == 4)
                            {
//                                    qDebug()<<"2222222222222 20";

                                trifree.x = x;trifree.y = y;
                                Searched[x][y] = 1;
                                Searched[x - 1][y] = 1;
                                Searched[x - 1][y + 1] = 1;
                                Searched[x][y + 1] = 1;
                                return 1;
                            }
                        }
                        if (Square[x - 1][y + 1].edge[1] == '1')
                        {
                            if (Square[x - 2][y + 1].degree == 3 || Square[x - 2][y + 1].degree == 4)
                            {
//                                    qDebug()<<"2222222222222 21";

                                trifree.x = x;trifree.y = y;
                                Searched[x][y] = 1;
                                Searched[x - 1][y] = 1;
                                Searched[x - 1][y + 1] = 1;
                                Searched[x - 2][y + 1] = 1;
                                return 1;
                            }
                        }
                        if (Square[x - 1][y + 1].edge[2] == '1')
                        {
                            if (Square[x - 1][y + 2].degree == 3 || Square[x - 1][y + 2].degree == 4)
                            {
//                                    qDebug()<<"2222222222222 22";

                                trifree.x = x;trifree.y = y;
                                Searched[x][y] = 1;
                                Searched[x - 1][y] = 1;
                                Searched[x - 1][y + 1] = 1;
                                Searched[x - 1][y + 2] = 1;
                                return 1;
                            }
                        }
                    }
                }
            }
        }
        if (Square[x][y].edge[2] == '1')						//找到此自由个字的无边方向 若为右边
        {
            if (Square[x][y + 1].degree == 2 && y + 1<6 && !Searched[x][y + 1])						//临近三个格子自由度都为二 则不是反双交
            {
                if (Square[x][y + 1].edge[1] == '1')
                {
                    if ((Square[x - 1][y + 1].degree == 3 || Square[x - 1][y + 1].degree == 4) && x - 1>0 && !Searched[x - 1][y + 1])
                    {
//                            qDebug()<<"2222222222222 23";

                        trifree.x = x;trifree.y = y;
                        Searched[x][y] = 1;
                        Searched[x][y + 1] = 1;
                        Searched[x - 1][y + 1] = 1;
                        return 1;
                    }
                    if (Square[x - 1][y + 1].degree == 2 && x - 1>0 && !Searched[x - 1][y + 1])
                    {
                        if (Square[x - 1][y + 1].edge[1] == '1')
                        {
                            if (Square[x - 2][y + 1].degree == 3 || Square[x - 2][y + 1].degree == 4)
                            {
//                                    qDebug()<<"2222222222222 24";

                                trifree.x = x;trifree.y = y;
                                Searched[x][y] = 1;
                                Searched[x][y + 1] = 1;
                                Searched[x - 1][y + 1] = 1;
                                Searched[x - 2][y + 1] = 1;
                                return 1;
                            }
                        }
                        if (Square[x - 1][y + 1].edge[2] == '1')
                        {
                            if (Square[x - 1][y + 2].degree == 3 || Square[x - 1][y + 2].degree == 4)
                            {
//                                    qDebug()<<"2222222222222 25";

                                trifree.x = x;trifree.y = y;
                                Searched[x][y] = 1;
                                Searched[x][y + 1] = 1;
                                Searched[x - 1][y + 1] = 1;
                                Searched[x - 1][y + 2] = 1;
                                return 1;
                            }
                        }
                        if (Square[x - 1][y + 1].edge[0] == '1')
                        {
                            if (Square[x - 1][y].degree == 3 || Square[x - 1][y].degree == 4)
                            {
//                                    qDebug()<<"2222222222222 26";

                                trifree.x = x;trifree.y = y;
                                Searched[x][y] = 1;
                                Searched[x][y + 1] = 1;
                                Searched[x - 1][y + 1] = 1;
                                Searched[x - 1][y] = 1;
                                return 1;
                            }
                        }
                    }
                }
                if (Square[x][y + 1].edge[2] == '1')
                {
                    if ((Square[x][y + 2].degree == 3 || Square[x][y + 2].degree == 4) && y + 2<6 && !Searched[x][y + 2])
                    {
//                            qDebug()<<"2222222222222 27";

                        trifree.x = x;trifree.y = y;
                        Searched[x][y] = 1;
                        Searched[x][y + 1] = 1;
                        Searched[x][y + 2] = 1;
                        return 1;
                    }
                    if (Square[x][y + 2].degree == 2 && y + 2<6 && !Searched[x][y + 2])
                    {
                        if (Square[x][y + 2].edge[1] == '1')
                        {
                            if (Square[x - 1][y + 2].degree == 3 || Square[x - 1][y + 2].degree == 4)
                            {
//                                    qDebug()<<"2222222222222 28";

                                trifree.x = x;trifree.y = y;
                                Searched[x][y] = 1;
                                Searched[x][y + 1] = 1;
                                Searched[x][y + 2] = 1;
                                Searched[x - 1][y + 2] = 1;
                                return 1;
                            }
                        }
                        if (Square[x][y + 2].edge[2] == '1')
                        {
                            if (Square[x][y + 3].degree == 3 || Square[x][y + 3].degree == 4)
                            {
//                                    qDebug()<<"2222222222222 29";

                                trifree.x = x;trifree.y = y;
                                Searched[x][y] = 1;
                                Searched[x][y + 1] = 1;
                                Searched[x][y + 2] = 1;
                                Searched[x][y + 3] = 1;
                                return 1;
                            }
                        }
                        if (Square[x][y + 2].edge[3] == '1')
                        {
                            if (Square[x + 1][y + 2].degree == 3 || Square[x + 1][y + 2].degree == 4)
                            {
//                                    qDebug()<<"2222222222222 30";

                                trifree.x = x;trifree.y = y;
                                Searched[x][y] = 1;
                                Searched[x][y + 1] = 1;
                                Searched[x][y + 2] = 1;
                                Searched[x + 1][y + 2] = 1;
                                return 1;
                            }
                        }
                    }
                }
                if (Square[x][y + 1].edge[3] == '1')
                {
                    if ((Square[x + 1][y + 1].degree == 3 || Square[x + 1][y + 1].degree == 4) && x + 1<6 && !Searched[x + 1][y + 1])
                    {
//                            qDebug()<<"2222222222222 31";

                        trifree.x = x;trifree.y = y;
                        Searched[x][y] = 1;
                        Searched[x][y + 1] = 1;
                        Searched[x + 1][y + 1] = 1;
                        return 1;
                    }
                    if (Square[x + 1][y + 1].degree == 2 && x + 1<6 && !Searched[x + 1][y + 1])
                    {
                        if (Square[x + 1][y + 1].edge[0] == '1')
                        {
                            if (Square[x + 1][y].degree == 3 || Square[x + 1][y].degree == 4)
                            {
//                                    qDebug()<<"2222222222222 32";

                                trifree.x = x;trifree.y = y;
                                Searched[x][y] = 1;
                                Searched[x][y + 1] = 1;
                                Searched[x + 1][y + 1] = 1;
                                Searched[x + 1][y] = 1;
                                return 1;
                            }
                        }
                        if (Square[x + 1][y + 1].edge[2] == '1')
                        {
                            if (Square[x + 1][y + 2].degree == 3 || Square[x + 1][y + 2].degree == 4)
                            {
//                                    qDebug()<<"2222222222222 33";

                                trifree.x = x;trifree.y = y;
                                Searched[x][y] = 1;
                                Searched[x][y + 1] = 1;
                                Searched[x + 1][y + 1] = 1;
                                Searched[x + 1][y + 2] = 1;
                                return 1;
                            }
                        }
                        if (Square[x + 1][y + 1].edge[3] == '1')
                        {
                            if (Square[x + 2][y + 1].degree == 3 || Square[x + 2][y + 1].degree == 4)
                            {
//                                    qDebug()<<"2222222222222 34";

                                trifree.x = x;trifree.y = y;
                                Searched[x][y] = 1;
                                Searched[x][y + 1] = 1;
                                Searched[x + 1][y + 1] = 1;
                                Searched[x + 2][y + 1] = 1;
                                return 1;
                            }
                        }
                    }
                }
            }
        }
        if (Square[x][y].edge[3] == '1')						//找到此自由个字的无边方向 若为下边
        {
            if (Square[x + 1][y].degree == 2 && x + 1<6 && !Searched[x + 1][y])						//临近三个格子自由度都为二 则不是反双交
            {
                if (Square[x + 1][y].edge[0] == '1')
                {
                    if ((Square[x + 1][y - 1].degree == 3 || Square[x + 1][y - 1].degree == 4) && y - 1>0 && !Searched[x + 1][y - 1])
                    {
//                            qDebug()<<"2222222222222 35";

                        trifree.x = x;trifree.y = y;
                        Searched[x][y] = 1;
                        Searched[x + 1][y] = 1;
                        Searched[x + 1][y - 1] = 1;
                        return 1;
                    }
                    if (Square[x + 1][y - 1].degree == 2 && y - 1>0 && !Searched[x + 1][y - 1])
                    {
                        if (Square[x + 1][y - 1].edge[0] == '1')
                        {
                            if (Square[x + 1][y - 2].degree == 3 || Square[x + 1][y - 2].degree == 4)
                            {
//                                    qDebug()<<"2222222222222 36";

                                trifree.x = x;trifree.y = y;
                                Searched[x][y] = 1;
                                Searched[x + 1][y] = 1;
                                Searched[x + 1][y - 1] = 1;
                                Searched[x + 1][y - 2] = 1;
                                return 1;
                            }
                        }
                        if (Square[x + 1][y - 1].edge[1] == '1')
                        {
                            if (Square[x][y - 1].degree == 3 || Square[x][y - 1].degree == 4)
                            {
//                                    qDebug()<<"2222222222222 37";

                                trifree.x = x;trifree.y = y;
                                Searched[x][y] = 1;
                                Searched[x + 1][y] = 1;
                                Searched[x + 1][y - 1] = 1;
                                Searched[x][y - 1] = 1;
                                return 1;
                            }
                        }
                        if (Square[x + 1][y - 1].edge[3] == '1')
                        {
                            if (Square[x + 2][y - 1].degree == 3 || Square[x + 2][y - 1].degree == 4)
                            {
//                                    qDebug()<<"2222222222222 38";

                                trifree.x = x;trifree.y = y;
                                Searched[x][y] = 1;
                                Searched[x + 1][y] = 1;
                                Searched[x + 1][y - 1] = 1;
                                Searched[x + 2][y - 1] = 1;
                                return 1;
                            }
                        }
                    }
                }
                if (Square[x + 1][y].edge[2] == '1')
                {
                    if ((Square[x + 1][y + 1].degree == 3 || Square[x + 1][y + 1].degree == 4) && y + 1<6 && !Searched[x + 1][y + 1])
                    {
//                            qDebug()<<"2222222222222 39";

                        trifree.x = x;trifree.y = y;
                        Searched[x][y] = 1;
                        Searched[x + 1][y] = 1;
                        Searched[x + 1][y + 1] = 1;
                        return 1;
                    }
                    if (Square[x + 1][y + 1].degree == 2 && y + 1<6 && !Searched[x + 1][y + 1])
                    {
                        if (Square[x + 1][y + 1].edge[1] == '1')
                        {
                            if (Square[x][y + 1].degree == 3 || Square[x][y + 1].degree == 4)
                            {
//                                    qDebug()<<"2222222222222 40";

                                trifree.x = x;trifree.y = y;
                                Searched[x][y] = 1;
                                Searched[x + 1][y] = 1;
                                Searched[x + 1][y + 1] = 1;
                                Searched[x][y + 1] = 1;
                                return 1;
                            }
                        }
                        {
                            if (Square[x + 1][y + 2].degree == 3 || Square[x + 1][y + 2].degree == 4)
                            {
//                                    qDebug()<<"2222222222222 41";

                                trifree.x = x;trifree.y = y;
                                Searched[x][y] = 1;
                                Searched[x + 1][y] = 1;
                                Searched[x + 1][y + 1] = 1;
                                Searched[x + 1][y + 2] = 1;
                                return 1;
                            }
                        }
                        if (Square[x + 1][y + 1].edge[3] == '1')
                        {
                            if (Square[x + 2][y + 1].degree == 3 || Square[x + 2][y + 1].degree == 4)
                            {
//                                    qDebug()<<"2222222222222 42";

                                trifree.x = x;trifree.y = y;
                                Searched[x][y] = 1;
                                Searched[x + 1][y] = 1;
                                Searched[x + 1][y + 1] = 1;
                                Searched[x + 2][y + 1] = 1;
                                return 1;
                            }
                        }
                    }
                }
                if (Square[x + 1][y].edge[3] == '1')
                {
                    if ((Square[x + 2][y].degree == 3 || Square[x + 2][y].degree == 4) && x + 2<6 && !Searched[x + 2][y])
                    {
//                            qDebug()<<"2222222222222 43";

                        trifree.x = x;trifree.y = y;
                        Searched[x][y] = 1;
                        Searched[x + 1][y] = 1;
                        Searched[x + 2][y] = 1;
                        return 1;
                    }
                    if (Square[x + 2][y].degree == 2 && x + 2<6 && !Searched[x + 2][y])
                    {
                        if (Square[x + 2][y].edge[0] == '1')
                        {
                            if (Square[x + 2][y - 1].degree == 3 || Square[x + 2][y - 1].degree == 4)
                            {
//                                    qDebug()<<"2222222222222 44";

                                trifree.x = x;trifree.y = y;
                                Searched[x][y] = 1;
                                Searched[x + 1][y] = 1;
                                Searched[x + 2][y] = 1;
                                Searched[x + 2][y - 1] = 1;
                                return 1;
                            }
                        }
                        if (Square[x + 2][y].edge[2] == '1')
                        {
                            if (Square[x + 2][y + 1].degree == 3 || Square[x + 2][y + 1].degree == 4)
                            {
//                                    qDebug()<<"2222222222222 45";

                                trifree.x = x;trifree.y = y;
                                Searched[x][y] = 1;
                                Searched[x + 1][y] = 1;
                                Searched[x + 2][y] = 1;
                                Searched[x + 2][y + 1] = 1;
                                return 1;
                            }
                        }
                        if (Square[x + 2][y].edge[3] == '1')
                        {
                            if (Square[x + 3][y].degree == 3 || Square[x + 3][y].degree == 4)
                            {
//                                    qDebug()<<"2222222222222 46";

                                trifree.x = x;trifree.y = y;
                                Searched[x][y] = 1;
                                Searched[x + 1][y] = 1;
                                Searched[x + 2][y] = 1;
                                Searched[x + 3][y] = 1;
                                return 1;
                            }
                        }
                    }
                }
            }
        }
    }
    return 0;
}

int AI::Triple_Freedom(Situation Square[6][6], int x, int y)                //判断某三自由度格的情况
{

    if (Square[x][y].degree == 3)									//找到此三自由度格子
    {
        if (Square[x][y].edge[0] == '1')						//找到此自由个字的无边方向 若为左边
        {
            if (Square[x][y - 1].degree == 2 && y - 1>0 && !Searched[x][y - 1])						//临近三个格子自由度都为二 则不是反双交
            {
                if (Square[x][y - 1].edge[0] == '1')
                {
                    if ((Square[x][y - 2].degree == 3 || Square[x][y - 2].degree == 4) && y - 2>0 && !Searched[x][y - 2])
                    {
                        trifree.x = x;trifree.y = y;
                        Searched[x][y] = 1;
                        Searched[x][y - 1] = 1;
                        Searched[x][y - 2] = 1;
                        return 1;
                    }
                    if (Square[x][y - 2].degree == 2 && y - 2>0 && !Searched[x][y - 2])
                    {
                        if (Square[x][y - 2].edge[0] == '1')
                        {
                            if (Square[x][y - 3].degree == 3 || Square[x][y - 3].degree == 4)
                            {
                                trifree.x = x;trifree.y = y;
                                Searched[x][y] = 1;
                                Searched[x][y - 1] = 1;
                                Searched[x][y - 2] = 1;
                                Searched[x][y - 3] = 1;
                                return 1;
                            }
                        }
                        if (Square[x][y - 2].edge[1] == '1')
                        {
                            if (Square[x - 1][y - 2].degree == 3 || Square[x - 1][y - 2].degree == 4)
                            {
                                trifree.x = x;trifree.y = y;
                                Searched[x][y] = 1;
                                Searched[x][y - 1] = 1;
                                Searched[x][y - 2] = 1;
                                Searched[x - 1][y - 2] = 1;
                                return 1;
                            }
                        }
                        if (Square[x][y - 2].edge[3] == '1')
                        {
                            if (Square[x + 1][y - 2].degree == 3 || Square[x + 1][y - 2].degree == 4)
                            {
                                trifree.x = x;trifree.y = y;
                                Searched[x][y] = 1;
                                Searched[x][y - 1] = 1;
                                Searched[x][y - 2] = 1;
                                Searched[x + 1][y - 2] = 1;
                                return 1;
                            }
                        }
                    }
                }
                if (Square[x][y - 1].edge[1] == '1')
                {
                    if ((Square[x - 1][y - 1].degree == 3 || Square[x - 1][y - 1].degree == 4) && x - 1>0 && !Searched[x - 1][y - 1])
                    {
                        trifree.x = x;trifree.y = y;
                        Searched[x][y] = 1;
                        Searched[x][y - 1] = 1;
                        Searched[x - 1][y - 1] = 1;
                        return 1;
                    }
                    if (Square[x - 1][y - 1].degree == 2 && x - 1>0 && !Searched[x - 1][y - 1])
                    {
                        if (Square[x - 1][y - 1].edge[0] == '1')
                        {
                            if (Square[x - 1][y - 2].degree == 3 || Square[x - 1][y - 2].degree == 4)
                            {
                                trifree.x = x;trifree.y = y;
                                Searched[x][y] = 1;
                                Searched[x][y - 1] = 1;
                                Searched[x - 1][y - 1] = 1;
                                Searched[x - 1][y - 2] = 1;
                                return 1;
                            }
                        }
                        if (Square[x - 1][y - 1].edge[1] == '1')
                        {
                            if (Square[x - 2][y - 1].degree == 3 || Square[x - 2][y - 1].degree == 4)
                            {
                                trifree.x = x;trifree.y = y;
                                Searched[x][y] = 1;
                                Searched[x][y - 1] = 1;
                                Searched[x - 1][y - 1] = 1;
                                Searched[x - 2][y - 1] = 1;
                                return 1;
                            }
                        }
                        if (Square[x - 1][y - 1].edge[2] == '1')
                        {
                            if (Square[x - 1][y].degree == 3 || Square[x - 1][y].degree == 4)
                            {
                                trifree.x = x;trifree.y = y;
                                Searched[x][y] = 1;
                                Searched[x][y - 1] = 1;
                                Searched[x - 1][y - 1] = 1;
                                Searched[x - 1][y] = 1;
                                return 1;
                            }
                        }
                    }
                }
                if (Square[x][y - 1].edge[3] == '1')
                {
                    if ((Square[x + 1][y - 1].degree == 3 || Square[x + 1][y - 1].degree == 4) && x + 1<6 && !Searched[x + 1][y - 1])
                    {
                        trifree.x = x;trifree.y = y;
                        Searched[x][y] = 1;
                        Searched[x][y - 1] = 1;
                        Searched[x + 1][y - 1] = 1;
                        return 1;
                    }
                    if (Square[x + 1][y - 1].degree == 2 && x + 1<6 && !Searched[x + 1][y - 1])
                    {
                        if (Square[x + 1][y - 1].edge[0] == '1')
                        {
                            if (Square[x + 1][y - 2].degree == 3 || Square[x + 1][y - 2].degree == 4)
                            {
                                trifree.x = x;trifree.y = y;
                                Searched[x][y] = 1;
                                Searched[x][y - 1] = 1;
                                Searched[x + 1][y - 1] = 1;
                                Searched[x + 1][y - 2] = 1;
                                return 1;
                            }
                        }
                        if (Square[x + 1][y - 1].edge[2] == '1')
                        {
                            if (Square[x + 1][y].degree == 3 || Square[x + 1][y].degree == 4)
                            {
                                trifree.x = x;trifree.y = y;
                                Searched[x][y] = 1;
                                Searched[x][y - 1] = 1;
                                Searched[x + 1][y - 1] = 1;
                                Searched[x + 1][y] = 1;
                                return 1;
                            }
                        }
                        if (Square[x + 1][y - 1].edge[3] == '1')
                        {
                            if (Square[x + 2][y - 1].degree == 3 || Square[x + 2][y - 1].degree == 4)
                            {
                                trifree.x = x;trifree.y = y;
                                Searched[x][y] = 1;
                                Searched[x][y - 1] = 1;
                                Searched[x + 1][y - 1] = 1;
                                Searched[x + 2][y - 1] = 1;
                                return 1;
                            }
                        }
                    }
                }
            }
        }
        if (Square[x][y].edge[1] == '1')						//找到此自由个字的无边方向 若为上边
        {
            if (Square[x - 1][y].degree == 2 && x - 1>0 && !Searched[x - 1][y])						//临近三个格子自由度都为二 则不是反双交
            {
                if (Square[x - 1][y].edge[0] == '1')
                {
                    if ((Square[x - 1][y - 1].degree == 3 || Square[x - 1][y - 2].degree == 4) && y - 1>0 && !Searched[x - 1][y - 1])
                    {
                        trifree.x = x;trifree.y = y;
                        Searched[x][y] = 1;
                        Searched[x - 1][y] = 1;
                        Searched[x - 1][y - 1] = 1;
                        return 1;
                    }
                    if (Square[x - 1][y - 1].degree == 2 && y - 1>0 && !Searched[x - 1][y - 1])
                    {
                        if (Square[x - 1][y - 1].edge[0] == '1')                        //hhkjhkjlhlkjhfaksdjhlasd
                        {
                            if (Square[x - 1][y - 2].degree == 3 || Square[x - 1][y - 2].degree == 4)
                            {
                                trifree.x = x;trifree.y = y;
                                Searched[x][y] = 1;
                                Searched[x - 1][y] = 1;
                                Searched[x - 1][y - 1] = 1;
                                Searched[x - 1][y - 2] = 1;
                                return 1;
                            }
                        }
                        if (Square[x - 1][y - 1].edge[1] == '1')
                        {
                            if (Square[x - 2][y - 1].degree == 3 || Square[x - 2][y - 1].degree == 4)
                            {
                                trifree.x = x;trifree.y = y;
                                Searched[x][y] = 1;
                                Searched[x - 1][y] = 1;
                                Searched[x - 1][y - 1] = 1;
                                Searched[x - 2][y - 1] = 1;
                                return 1;
                            }
                        }
                        if (Square[x - 1][y - 1].edge[3] == '1')
                        {
                            if (Square[x][y - 1].degree == 3 || Square[x][y - 1].degree == 4)
                            {
                                trifree.x = x;trifree.y = y;
                                Searched[x][y] = 1;
                                Searched[x - 1][y] = 1;
                                Searched[x - 1][y - 1] = 1;
                                Searched[x][y - 1] = 1;
                                return 1;
                            }
                        }
                    }
                }
                if (Square[x - 1][y].edge[1] == '1')
                {
                    if ((Square[x - 2][y].degree == 3 || Square[x - 2][y].degree == 4) && x - 2>0 && !Searched[x - 2][y])
                    {
                        trifree.x = x;trifree.y = y;
                        Searched[x][y] = 1;
                        Searched[x - 1][y] = 1;
                        Searched[x - 2][y] = 1;
                        return 1;
                    }
                    if (Square[x - 2][y].degree == 2 && x - 2>0 && !Searched[x - 2][y])
                    {
                        if (Square[x - 2][y].edge[0] == '1')
                        {
                            if (Square[x - 2][y - 1].degree == 3 || Square[x - 2][y - 1].degree == 4)
                            {
                                trifree.x = x;trifree.y = y;
                                Searched[x][y] = 1;
                                Searched[x - 1][y] = 1;
                                Searched[x - 2][y] = 1;
                                Searched[x - 2][y - 1] = 1;
                                return 1;
                            }
                        }
                        if (Square[x - 2][y].edge[1] == '1')
                        {
                            if (Square[x - 3][y].degree == 3 || Square[x - 3][y].degree == 4)
                            {
                                trifree.x = x;trifree.y = y;
                                Searched[x][y] = 1;
                                Searched[x - 1][y] = 1;
                                Searched[x - 2][y] = 1;
                                Searched[x - 3][y] = 1;
                                return 1;
                            }
                        }
                        if (Square[x - 2][y].edge[2] == '1')
                        {
                            if (Square[x - 2][y + 1].degree == 3 || Square[x - 2][y + 1].degree == 4)
                            {
                                trifree.x = x;trifree.y = y;
                                Searched[x][y] = 1;
                                Searched[x - 1][y] = 1;
                                Searched[x - 2][y] = 1;
                                Searched[x - 2][y + 1] = 1;
                                return 1;
                            }
                        }
                    }
                }
                if (Square[x - 1][y].edge[2] == '1')
                {
                    if ((Square[x - 1][y + 1].degree == 3 || Square[x - 1][y + 1].degree == 4) && y + 1<6 && !Searched[x - 1][y + 1])
                    {
                        trifree.x = x;trifree.y = y;
                        Searched[x][y] = 1;
                        Searched[x - 1][y] = 1;
                        Searched[x - 1][y + 1] = 1;
                        return 1;
                    }
                    if (Square[x - 1][y + 1].degree == 2 && y + 1<6 && !Searched[x - 1][y + 1])
                    {
                        if (Square[x - 1][y + 1].edge[3] == '1')
                        {
                            if (Square[x][y + 1].degree == 3 || Square[x][y + 1].degree == 4)
                            {
                                trifree.x = x;trifree.y = y;
                                Searched[x][y] = 1;
                                Searched[x - 1][y] = 1;
                                Searched[x - 1][y + 1] = 1;
                                Searched[x][y + 1] = 1;
                                return 1;
                            }
                        }
                        if (Square[x - 1][y + 1].edge[1] == '1')
                        {
                            if (Square[x - 2][y + 1].degree == 3 || Square[x - 2][y + 1].degree == 4)
                            {
                                trifree.x = x;trifree.y = y;
                                Searched[x][y] = 1;
                                Searched[x - 1][y] = 1;
                                Searched[x - 1][y + 1] = 1;
                                Searched[x - 2][y + 1] = 1;
                                return 1;
                            }
                        }
                        if (Square[x - 1][y + 1].edge[2] == '1')
                        {
                            if (Square[x - 1][y + 2].degree == 3 || Square[x - 1][y + 2].degree == 4)
                            {
                                trifree.x = x;trifree.y = y;
                                Searched[x][y] = 1;
                                Searched[x - 1][y] = 1;
                                Searched[x - 1][y + 1] = 1;
                                Searched[x - 1][y + 2] = 1;
                                return 1;
                            }
                        }
                    }
                }
            }
        }
        if (Square[x][y].edge[2] == '1')						//找到此自由个字的无边方向 若为右边
        {
            if (Square[x][y + 1].degree == 2 && y + 1<6 && !Searched[x][y + 1])						//临近三个格子自由度都为二 则不是反双交
            {
                if (Square[x][y + 1].edge[1] == '1')
                {
                    if ((Square[x - 1][y + 1].degree == 3 || Square[x - 1][y + 1].degree == 4) && x - 1>0 && !Searched[x - 1][y + 1])
                    {
                        trifree.x = x;trifree.y = y;
                        Searched[x][y] = 1;
                        Searched[x][y + 1] = 1;
                        Searched[x - 1][y + 1] = 1;
                        return 1;
                    }
                    if (Square[x - 1][y + 1].degree == 2 && x - 1>0 && !Searched[x - 1][y + 1])
                    {
                        if (Square[x - 1][y + 1].edge[1] == '1')
                        {
                            if (Square[x - 2][y + 1].degree == 3 || Square[x - 2][y + 1].degree == 4)
                            {
                                trifree.x = x;trifree.y = y;
                                Searched[x][y] = 1;
                                Searched[x][y + 1] = 1;
                                Searched[x - 1][y + 1] = 1;
                                Searched[x - 2][y + 1] = 1;
                                return 1;
                            }
                        }
                        if (Square[x - 1][y + 1].edge[2] == '1')
                        {
                            if (Square[x - 1][y + 2].degree == 3 || Square[x - 1][y + 2].degree == 4)
                            {
                                trifree.x = x;trifree.y = y;
                                Searched[x][y] = 1;
                                Searched[x][y + 1] = 1;
                                Searched[x - 1][y + 1] = 1;
                                Searched[x - 1][y + 2] = 1;
                                return 1;
                            }
                        }
                        if (Square[x - 1][y + 1].edge[0] == '1')
                        {
                            if (Square[x - 1][y].degree == 3 || Square[x - 1][y].degree == 4)
                            {
                                trifree.x = x;trifree.y = y;
                                Searched[x][y] = 1;
                                Searched[x][y + 1] = 1;
                                Searched[x - 1][y + 1] = 1;
                                Searched[x - 1][y] = 1;
                                return 1;
                            }
                        }
                    }
                }
                if (Square[x][y + 1].edge[2] == '1')
                {
                    if ((Square[x][y + 2].degree == 3 || Square[x][y + 2].degree == 4) && y + 2<6 && !Searched[x][y + 2])
                    {
                        trifree.x = x;trifree.y = y;
                        Searched[x][y] = 1;
                        Searched[x][y + 1] = 1;
                        Searched[x][y + 2] = 1;
                        return 1;
                    }
                    if (Square[x][y + 2].degree == 2 && y + 2<6 && !Searched[x][y + 2])
                    {
                        if (Square[x][y + 2].edge[1] == '1')
                        {
                            if (Square[x - 1][y + 2].degree == 3 || Square[x - 1][y + 2].degree == 4)
                            {
                                trifree.x = x;trifree.y = y;
                                Searched[x][y] = 1;
                                Searched[x][y + 1] = 1;
                                Searched[x][y + 2] = 1;
                                Searched[x - 1][y + 2] = 1;
                                return 1;
                            }
                        }
                        if (Square[x][y + 2].edge[2] == '1')
                        {
                            if (Square[x][y + 3].degree == 3 || Square[x][y + 3].degree == 4)
                            {
                                trifree.x = x;trifree.y = y;
                                Searched[x][y] = 1;
                                Searched[x][y + 1] = 1;
                                Searched[x][y + 2] = 1;
                                Searched[x][y + 3] = 1;
                                return 1;
                            }
                        }
                        if (Square[x][y + 2].edge[3] == '1')
                        {
                            if (Square[x + 1][y + 2].degree == 3 || Square[x + 1][y + 2].degree == 4)
                            {
                                trifree.x = x;trifree.y = y;
                                Searched[x][y] = 1;
                                Searched[x][y + 1] = 1;
                                Searched[x][y + 2] = 1;
                                Searched[x + 1][y + 2] = 1;
                                return 1;
                            }
                        }
                    }
                }
                if (Square[x][y + 1].edge[3] == '1')
                {
                    if ((Square[x + 1][y + 1].degree == 3 || Square[x + 1][y + 1].degree == 4) && x + 1<6 && !Searched[x + 1][y + 1])
                    {
                        trifree.x = x;trifree.y = y;
                        Searched[x][y] = 1;
                        Searched[x][y + 1] = 1;
                        Searched[x + 1][y + 1] = 1;
                        return 1;
                    }
                    if (Square[x + 1][y + 1].degree == 2 && x + 1<6 && !Searched[x + 1][y + 1])
                    {
                        if (Square[x + 1][y + 1].edge[0] == '1')
                        {
                            if (Square[x + 1][y].degree == 3 || Square[x + 1][y].degree == 4)
                            {
                                trifree.x = x;trifree.y = y;
                                Searched[x][y] = 1;
                                Searched[x][y + 1] = 1;
                                Searched[x + 1][y + 1] = 1;
                                Searched[x + 1][y] = 1;
                                return 1;
                            }
                        }
                        if (Square[x + 1][y + 1].edge[2] == '1')
                        {
                            if (Square[x + 1][y + 2].degree == 3 || Square[x + 1][y + 2].degree == 4)
                            {
                                trifree.x = x;trifree.y = y;
                                Searched[x][y] = 1;
                                Searched[x][y + 1] = 1;
                                Searched[x + 1][y + 1] = 1;
                                Searched[x + 1][y + 2] = 1;
                                return 1;
                            }
                        }
                        if (Square[x + 1][y + 1].edge[3] == '1')
                        {
                            if (Square[x + 2][y + 1].degree == 3 || Square[x + 2][y + 1].degree == 4)
                            {
                                trifree.x = x;trifree.y = y;
                                Searched[x][y] = 1;
                                Searched[x][y + 1] = 1;
                                Searched[x + 1][y + 1] = 1;
                                Searched[x + 2][y + 1] = 1;
                                return 1;
                            }
                        }
                    }
                }
            }
        }
        if (Square[x][y].edge[3] == '1')						//找到此自由个字的无边方向 若为下边
        {
            if (Square[x + 1][y].degree == 2 && x + 1<6 && !Searched[x + 1][y])						//临近三个格子自由度都为二 则不是反双交
            {
                if (Square[x + 1][y].edge[0] == '1')
                {
                    if ((Square[x + 1][y - 1].degree == 3 || Square[x + 1][y - 1].degree == 4) && y - 1>0 && !Searched[x + 1][y - 1])
                    {
                        trifree.x = x;trifree.y = y;
                        Searched[x][y] = 1;
                        Searched[x + 1][y] = 1;
                        Searched[x + 1][y - 1] = 1;
                        return 1;
                    }
                    if (Square[x + 1][y - 1].degree == 2 && y - 1>0 && !Searched[x + 1][y - 1])
                    {
                        if (Square[x + 1][y - 1].edge[0] == '1')
                        {
                            if (Square[x + 1][y - 2].degree == 3 || Square[x + 1][y - 2].degree == 4)
                            {
                                trifree.x = x;trifree.y = y;
                                Searched[x][y] = 1;
                                Searched[x + 1][y] = 1;
                                Searched[x + 1][y - 1] = 1;
                                Searched[x + 1][y - 2] = 1;
                                return 1;
                            }
                        }
                        if (Square[x + 1][y - 1].edge[1] == '1')
                        {
                            if (Square[x][y - 1].degree == 3 || Square[x][y - 1].degree == 4)
                            {
                                trifree.x = x;trifree.y = y;
                                Searched[x][y] = 1;
                                Searched[x + 1][y] = 1;
                                Searched[x + 1][y - 1] = 1;
                                Searched[x][y - 1] = 1;
                                return 1;
                            }
                        }
                        if (Square[x + 1][y - 1].edge[3] == '1')
                        {
                            if (Square[x + 2][y - 1].degree == 3 || Square[x + 2][y - 1].degree == 4)
                            {
                                trifree.x = x;trifree.y = y;
                                Searched[x][y] = 1;
                                Searched[x + 1][y] = 1;
                                Searched[x + 1][y - 1] = 1;
                                Searched[x + 2][y - 1] = 1;
                                return 1;
                            }
                        }
                    }
                }
                if (Square[x + 1][y].edge[2] == '1')
                {
                    if ((Square[x + 1][y + 1].degree == 3 || Square[x + 1][y + 1].degree == 4) && y + 1<6 && !Searched[x + 1][y + 1])
                    {
                        trifree.x = x;trifree.y = y;
                        Searched[x][y] = 1;
                        Searched[x + 1][y] = 1;
                        Searched[x + 1][y + 1] = 1;
                        return 1;
                    }
                    if (Square[x + 1][y + 1].degree == 2 && y + 1<6 && !Searched[x + 1][y + 1])
                    {
                        if (Square[x + 1][y + 1].edge[1] == '1')
                        {
                            if (Square[x][y + 1].degree == 3 || Square[x][y + 1].degree == 4)
                            {
                                trifree.x = x;trifree.y = y;
                                Searched[x][y] = 1;
                                Searched[x + 1][y] = 1;
                                Searched[x + 1][y + 1] = 1;
                                Searched[x][y + 1] = 1;
                                return 1;
                            }
                        }
                        {
                            if (Square[x + 1][y + 2].degree == 3 || Square[x + 1][y + 2].degree == 4)
                            {
                                trifree.x = x;trifree.y = y;
                                Searched[x][y] = 1;
                                Searched[x + 1][y] = 1;
                                Searched[x + 1][y + 1] = 1;
                                Searched[x + 1][y + 2] = 1;
                                return 1;
                            }
                        }
                        if (Square[x + 1][y + 1].edge[3] == '1')
                        {
                            if (Square[x + 2][y + 1].degree == 3 || Square[x + 2][y + 1].degree == 4)
                            {
                                trifree.x = x;trifree.y = y;
                                Searched[x][y] = 1;
                                Searched[x + 1][y] = 1;
                                Searched[x + 1][y + 1] = 1;
                                Searched[x + 2][y + 1] = 1;
                                return 1;
                            }
                        }
                    }
                }
                if (Square[x + 1][y].edge[3] == '1')
                {
                    if ((Square[x + 2][y].degree == 3 || Square[x + 2][y].degree == 4) && x + 2<6 && !Searched[x + 2][y])
                    {
                        trifree.x = x;trifree.y = y;
                        Searched[x][y] = 1;
                        Searched[x + 1][y] = 1;
                        Searched[x + 2][y] = 1;
                        return 1;
                    }
                    if (Square[x + 2][y].degree == 2 && x + 2<6 && !Searched[x + 2][y])
                    {
                        if (Square[x + 2][y].edge[0] == '1')
                        {
                            if (Square[x + 2][y - 1].degree == 3 || Square[x + 2][y - 1].degree == 4)
                            {
                                trifree.x = x;trifree.y = y;
                                Searched[x][y] = 1;
                                Searched[x + 1][y] = 1;
                                Searched[x + 2][y] = 1;
                                Searched[x + 2][y - 1] = 1;
                                return 1;
                            }
                        }
                        if (Square[x + 2][y].edge[2] == '1')
                        {
                            if (Square[x + 2][y + 1].degree == 3 || Square[x + 2][y + 1].degree == 4)
                            {
                                trifree.x = x;trifree.y = y;
                                Searched[x][y] = 1;
                                Searched[x + 1][y] = 1;
                                Searched[x + 2][y] = 1;
                                Searched[x + 2][y + 1] = 1;
                                return 1;
                            }
                        }
                        if (Square[x + 2][y].edge[3] == '1')
                        {
                            if (Square[x + 3][y].degree == 3 || Square[x + 3][y].degree == 4)
                            {
                                trifree.x = x;trifree.y = y;
                                Searched[x][y] = 1;
                                Searched[x + 1][y] = 1;
                                Searched[x + 2][y] = 1;
                                Searched[x + 3][y] = 1;
                                return 1;
                            }
                        }
                    }
                }
            }
        }
    }
    return 0;
}


int AI::Count_AntDoublecorse(Situation Square[6][6])    //查找反双交的个数
{
    //记录单链个数
    singlechain = 0;
    //记录双链的个数
    doublechain = 0;
    //记录反双交的个数
    fanshuagnjiao = 0;

    int i, j, num = 0;
    memset(Searched, 0, sizeof(Searched));
    for (i = 1; i <6; i++)
    {
        for (j = 1; j < 6; j++)
        {
            if (Searched[i][j]) continue;						//说明已经查找过了
            if (SingleChain(Square, i, j)) { singlechain++;num++;	continue; }					//SingleChain 单链必为反双交
            if (DoubleChain(Square, i, j)) { doublechain++;num++; continue; }						//DoubleChain 双链可能成为反双交
            if (Square[i][j].degree==3) {

                Searched[i][j] = 1;
                chu BeforeDead[3];
                Situation to[6][6];
                int count = 0;
                for(int k=0;k<4;k++){
                    if(Square[i][j].edge[k]=='1'){
                    BeforeDead[count].x = i;
                    BeforeDead[count].y = j;
                    BeforeDead[count].k = k;
                    count++;
                    }
                }

                for(int x=0;x<3;x++){

                    copy1(Square,to);
                    for(int x=1;x<6;x++)
                        for(int y=1;y<6;y++){
                            if(to[x][y].degree==1){
                                for(int k=0;k<4;k++){
                                    if(to[x][y].edge[k]=='1'&&k==0){
                                        if(to[x][y-1].degree!=3){
                                            to[x][y].degree=0;
                                        }
                                    }else if(to[x][y].edge[k]=='1'&&k==1){
                                        if(to[x-1][y].degree!=3){
                                            to[x][y].degree=0;
                                        }
                                    }else if(to[x][y].edge[k]=='1'&&k==2){
                                        if(to[x][y+1].degree!=3){
                                            to[x][y].degree=0;
                                        }
                                    }else if(to[x][y].edge[k]=='1'&&k==3){
                                        if(to[x+1][y].degree!=3){
                                            to[x][y].degree=0;
                                        }
                                    }
                                }
                            }
                        }

                    to[BeforeDead[x].x][BeforeDead[x].y].edge[BeforeDead[x].k]='*';
                    to[BeforeDead[x].x][BeforeDead[x].y].degree--;
                    mutualoccupy1(to, BeforeDead[x].x,BeforeDead[x].y,BeforeDead[x].k);

                    int count =0;
                    int eat = 0;
                    int zero_count=0;
                    while(eat==0||eat>count){
                        count = eat;
                        for(int x=1;x<6;x++)
                            for(int y=1;y<6;y++){
                                if(to[x][y].degree==1){
                                    for(int k=0;k<4;k++){
                                        if(to[x][y].edge[k]=='1'){
                                            to[x][y].edge[k]='*';
                                            to[x][y].degree--;
                                            mutualoccupy1(to, x,y,k);
                                            eat++;
                                        }
                                    }
                                }
                            }
                        if(eat==0)  zero_count++;
                        if(zero_count>20)   break;   //防止死循环
                    }
                    BeforeDead[x].lose_box = eat;
                }
                int sum =0;
                for(int x=0;x<3;x++){
                    if(BeforeDead[x].lose_box<=2){
                        sum++;
                    }
                }
                 if(sum>=1){
                    fanshuagnjiao++;
                    num++;
                }
                continue;
            }					//Triple_freedem 某三自由度带来交叉的可能为反双交


            if(Square[i][j].degree==4){
                Searched[i][j] = 1;
                chu BeforeDead[4];
                Situation to[6][6];

                for(int k=0;k<4;k++){
                    BeforeDead[k].x = i;
                    BeforeDead[k].y = j;
                    BeforeDead[k].k = k;

                }

                for(int x=0;x<4;x++){
                    copy1(Square,to);
                    for(int x=1;x<6;x++)
                        for(int y=1;y<6;y++){
                            if(to[x][y].degree==1){
                                for(int k=0;k<4;k++){
                                    if(to[x][y].edge[k]=='1'&&k==0){
                                        if(to[x][y-1].degree!=3){
                                            to[x][y].degree=0;
                                        }
                                    }else if(to[x][y].edge[k]=='1'&&k==1){
                                        if(to[x-1][y].degree!=3){
                                            to[x][y].degree=0;
                                        }
                                    }else if(to[x][y].edge[k]=='1'&&k==2){
                                        if(to[x][y+1].degree!=3){
                                            to[x][y].degree=0;
                                        }
                                    }else if(to[x][y].edge[k]=='1'&&k==3){
                                        if(to[x+1][y].degree!=3){
                                            to[x][y].degree=0;
                                        }
                                    }
                                }
                            }
                        }
                    to[BeforeDead[x].x][BeforeDead[x].y].edge[BeforeDead[x].k]='*';
                    to[BeforeDead[x].x][BeforeDead[x].y].degree--;
                    mutualoccupy1(to, BeforeDead[x].x,BeforeDead[x].y,BeforeDead[x].k);
                    int count =0;
                    int eat = 0;
                    int zero_count = 0;
                    while(eat==0||eat>count){
                        count = eat;
                        for(int x=1;x<6;x++)
                            for(int y=1;y<6;y++){
                                if(to[x][y].degree==1){
                                    for(int k=0;k<4;k++){
                                        if(to[x][y].edge[k]=='1'){
                                            to[x][y].edge[k]='*';
                                            to[x][y].degree--;
                                            mutualoccupy1(to, x,y,k);
                                            eat++;
                                        }
                                    }
                                }
                            }
                        if(eat==0)  zero_count++;
                        if(zero_count>20)   break;   //防止死循环
                    }

                    BeforeDead[x].lose_box = eat;
                }
                int count =0;
                for(int x=0;x<4;x++){
                    if(BeforeDead[x].lose_box<=2){
                        count++;
                    }
                }

                if(count == 1){
                    num++;
                }else if(count>=2){
                    num=num+2;
                }
                continue;
            }




        }
    }


    return num;
}

int AI::UCT_Count_AntDoublecorse(Situation Square[6][6])    //查找反双交的个数
{
    //记录单链个数
    singlechain = 0;
    //记录双链的个数
    doublechain = 0;
    //记录反双交的个数
    guaidian = 0;

    int i, j, num = 0;
    memset(Searched, 0, sizeof(Searched));
    for (i = 1; i <6; i++)
    {
        for (j = 1; j < 6; j++)
        {
            if (Searched[i][j]) continue;						//说明已经查找过了
            if (SingleChain(Square, i, j)) { singlechain++;num++;	continue; }					//SingleChain 单链必为反双交
            if (DoubleChain(Square, i, j)) { doublechain++;num++; continue; }						//DoubleChain 双链可能成为反双交
            if (Square[i][j].degree>=3) { guaidian++;num++;continue;}					//Triple_freedem 某三自由度带来交叉的可能为反双交
            //
        }
    }


    return num;
}

int AI::Evaluation(Situation Square[6][6], int Turn)				//评估函数，评估某步棋下过之后的局面 返回股指
{
    int Value = 0;
    int Num = 0;

    if (Turn == myturn)
    {
        Num = Count_AntDoublecorse(Square);

        if (!Dead(Square))
        {



            if (Num % 2 == 1)
            {
                Value = Value + 20;
            }
            else
            {
                Value = Value - 20;
            }
        }
        else
        {
            if (Num % 2 == 0)
            {
                Value = Value + 50;
            }
            else
            {
                Value = Value - 50;
            }
        }
    }


    if (Turn != myturn)
    {

        Num = Count_AntDoublecorse(Square);

        if (!Dead(Square))
        {
            if (Num % 2 == 0)
            {
                Value = Value + 20;
            }
            else
            {
                Value = Value - 20;
            }
        }
        else
        {
            if (Num % 2 == 1)
            {
                Value = Value + 50;
            }
            else
            {
                Value = Value - 50;
            }
        }
    }
    return Value;
}

int AI::Evaluation_I(Situation Square[6][6], int Turn)				//评估函数，评估某步棋下过之后的局面 返回股指
{
    qDebug()<<"进入残局评估";
    int Num = 0;
    Num = Count_AntDoublecorse(Square);
    if (Turn == 1)
    {
        if (Num % 2 == 0)
        {
            qDebug()<<"退出残局评估";
            return 1;
        }
        else
        {
            qDebug()<<"退出残局评估";
            return 0;
        }
    }

    if (Turn != 1)
    {
        if (Num % 2 == 1)
        {
            qDebug()<<"退出残局评估";
            return 1;
        }
        else
        {
            qDebug()<<"退出残局评估";
            return 0;
        }
    }
}

int AI::randmove(Situation Square[6][6], int turn)  //随机函数
{

    int k, x, y;    //etpye为 边的类型0为横13， x,y为坐标

    srand((unsigned)time(NULL));//随机函数rand() % 4;
    while (true)
    {

    shuiji:
        k = rand() % 4;  //随机边
        x = rand() % 5;//随机格子位置
        x++;
        y = rand() % 5;
        y++;


        if (Square[x][y].edge[k] != '1')
        {
            goto shuiji;

        }
        else if ((x > 1 && x < 5) && (y > 1 && y < 5))
        {
            if (Square[x][y].degree <= 2 || Square[x + 1][y].degree <= 2 || Square[x - 1][y].degree <= 2 || Square[x][y + 1].degree <= 2 || Square[x][y - 1].degree <= 2)
            {

                goto shuiji;
            }
            else
                break;
        }
        else if (x == 1 && y>1 && y<5)
        {
            if (Square[x][y].degree <= 2) { goto shuiji; }
            else if (k == 0 && Square[x][y - 1].degree <= 2) { goto shuiji; }
            else if (k == 2 && Square[x][y + 1].degree <= 2) { goto shuiji; }
            else if (k == 3 && Square[x + 1][y].degree <= 2) { goto shuiji; }
            else
                break;
        }//上3
        else if (x == 5 && y>1 && y<5)
        {
            if (Square[x][y].degree <= 2) {  goto shuiji; }
            else if (k == 0 && Square[x][y - 1].degree <= 2) {  goto shuiji; }
            else if (k == 2 && Square[x][y + 1].degree <= 2) {  goto shuiji; }
            else if (k == 1 && Square[x - 1][y].degree <= 2) {  goto shuiji; }
            else
                break;
        }//下3
        else if (y == 1 && x>1 && x<5)
        {
            if (Square[x][y].degree <= 2) {  goto shuiji; }
            else if (k == 3 && Square[x + 1][y].degree <= 2) {  goto shuiji; }
            else if (k == 2 && Square[x][y + 1].degree <= 2) {  goto shuiji; }
            else if (k == 1 && Square[x - 1][y].degree <= 2) {  goto shuiji; }
            else
                break;
        }//左3
        else if (y == 5 && x>1 && x<5)
        {
            if (Square[x][y].degree <= 2) {  goto shuiji; }
            else if (k == 3 && Square[x + 1][y].degree <= 2) {  goto shuiji; }
            else if (k == 0 && Square[x][y - 1].degree <= 2) {  goto shuiji; }
            else if (k == 1 && Square[x - 1][y].degree <= 2) {  goto shuiji; }
            else
                break;
        }//右3

        else if (x == 1 && y == 1)
        {
            if (Square[x][y].degree <= 2) { goto shuiji; }
            else if (k == 3 && Square[x + 1][y].degree <= 2) {  goto shuiji; }
            else if (k == 2 && Square[x][y + 1].degree <= 2) {  goto shuiji; }
            else
                break;
        }//左上点
        else if (x == 5 && y == 1)
        {
            if (Square[x][y].degree <= 2) {  goto shuiji; }
            else if (k == 2 && Square[x][y + 1].degree <= 2) {  goto shuiji; }
            else if (k == 1 && Square[x - 1][y].degree <= 2) {  goto shuiji; }
            else
                break;
        }//左下点
        else if (x == 1 && y == 5)
        {
            if (Square[x][y].degree <= 2) {  goto shuiji; }
            else if (k == 3 && Square[x + 1][y].degree <= 2) {  goto shuiji; }
            else if (k == 0 && Square[x][y - 1].degree <= 2) {  goto shuiji; }
            else
                break;
        }//右上点
        else if (x == 5 && y == 5)
        {
            if (Square[x][y].degree <= 2) {  goto shuiji; }
            else if (k == 1 && Square[x - 1][y].degree <= 2) {  goto shuiji; }
            else if (k == 0 && Square[x][y - 1].degree <= 2) {  goto shuiji; }
            else
                break;
        }//右下点



        else
            break;

    }

    if (turn == 1)
    {
        putcheer(Square, x, y, k, turn);

        getchecksline(x,y,k);
    }

    return  0;
}
//残局后判断函数
void AI::Put_chessboard(Situation Square[6][6], int etype, int i, int j,int turn)								//打印棋盘（边的横竖，坐标）
{
    if (etype == 0)													//为横边
    {
        if (i + 1 != 6)

        {
            if (turn == 1) {
                if(Square[i + 1][j + 1].edge[1]!='1'||i<0||j<0){


                    qDebug()<<"00000000000000000000000000000000000 "<<i + 1;
                    qDebug()<<"00000000000000000000000000000000000 "<<j + 1;
                    qDebug()<<"00000000000000000000000000000000000 "<<1;
                }
                Square[i + 1][j + 1].edge[1] = '*';


                Square[i + 1][j + 1].degree--;
                mutualoccupy1(Square, i + 1, j + 1, 1);
                getchecksline(i+1,j+1,1);

                chaincount--;

                opc(Square, 1);

            }

        }

        else
        {
            if (turn == 1)
            {
                if(Square[i][j + 1].edge[3]!='1'||i<0||j<0){

                    qDebug()<<"00000000000000000000000000000000000 "<<i ;
                    qDebug()<<"00000000000000000000000000000000000 "<<j + 1;
                    qDebug()<<"00000000000000000000000000000000000 "<<3;
                }
                Square[i][j + 1].edge[3] = '*';

                Square[i][j + 1].degree--;
                mutualoccupy1(Square, i, j + 1, 3);
                getchecksline(i,j+1,3);
                chaincount--;
                opc(Square, 1);
            }

        }

    }
    else															//为纵边
    {
        if (j + 1 != 6)
        {
            if (turn == 1)
            {
                if(Square[i + 1][j + 1].edge[0]!='1'||i<0||j<0){
                    qDebug()<<"00000000000000000000000000000000000 "<<i + 1 ;
                    qDebug()<<"00000000000000000000000000000000000 "<<j + 1;
                    qDebug()<<"00000000000000000000000000000000000 "<<0;
                }
            Square[i + 1][j + 1].edge[0] = '*';

            Square[i + 1][j + 1].degree--;
            mutualoccupy1(Square, i + 1, j + 1, 0);
            getchecksline(i+1,j+1,0);
            chaincount--;
            opc(Square, 1);
            }
        }
        else
        {
            if (turn == 1)
            {
                if(Square[i+ 1][j ].edge[2]!='1'||i<0||j<0){
                    qDebug()<<"00000000000000000000000000000000000 "<<i + 1 ;
                    qDebug()<<"00000000000000000000000000000000000 "<<j ;
                    qDebug()<<"00000000000000000000000000000000000 "<<2;
                }
                Square[i+ 1][j ].edge[2] = '*';

                Square[i + 1][j].degree--;
                mutualoccupy1(Square, i+ 1, j , 2);
                getchecksline(i+1,j,2);
                chaincount--;
                opc(Square, 1);


            }

        }
    }

}

void AI::bianli(Situation Square[6][6]) {

    char a[11][11];
    int ii = 1;
    int i, j;
    for (i = 0; i < 11; i++)
        for (j = 0; j < 11; j++)

            a[i][j] = '0';

    for (i = 1; i < 6; i++)
    {
        for (j = 1; j < 6; j++)
        {
            if (a[i * 2 - 1][j * 2 - 1] == '0')  a[i * 2 - 1][j * 2 - 1] = Square[i][j].ower;
            if (a[i * 2 - 1][j * 2 - 2] == '0')    a[i * 2 - 1][j * 2 - 2] = Square[i][j].edge[0];
            if (a[i * 2 - 2][j * 2 - 1] == '0')   a[i * 2 - 2][j * 2 - 1] = Square[i][j].edge[1];
            if (a[i * 2 - 1][j * 2] == '0')     a[i * 2 - 1][j * 2] = Square[i][j].edge[2];
            if (a[i * 2][j * 2 - 1] == '0')    a[i * 2][j * 2 - 1] = Square[i][j].edge[3];

        }

    }
    for (i = 0; i < 11; i++)
        for (j = 0; j < 11; j++)
        {

           std::cout << a[i][j] << "   ";
            ii++;
            if (ii > 11) {
                ii = 1;
                std::cout  << endl;
            }

        }
     std::cout  << endl;

}

int AI::Give_Boxes_Oven(Situation Square[6][6], int turn)
{
    int i, j, x, y;
    for (i = 1; i <= 5; i++)
    {
        for (j = 1; j <= 5; j++)
        {
            if (DoubleChain(Square, i, j))
            {
                if (Square[i][j].edge[0] == '1'&& Square[i][j - 1].degree == 2&&j!=1)
                {
                    if (Square[i][j - 1].edge[0] == '1')
                    {
                        copy1(Square,first);
                        Put_chessboard(Square, 1, i - 1, j - 2,turn);
                        if(Equal(Square,first)){
                            qDebug()<<"000000000000000 1";
                            qDebug()<<"x="<<x;
                            qDebug()<<"y="<<y;
                            for(int i = 1;i<6;i++)
                                for(int j=1;j<6;j++)
                                    qDebug()<<Square[i][j].degree;
                            bianli(Square);
                            exit(0);
                        }
                        return 1;
                    }
                    if (Square[i][j - 1].edge[1] == '1')
                    {
                        copy1(Square,first);
                        Put_chessboard(Square, 0, i - 1, j - 2, turn);
                        if(Equal(Square,first)){
                             qDebug()<<"000000000000000 2";
                             qDebug()<<"x="<<x;
                             qDebug()<<"y="<<y;
                             for(int i = 1;i<6;i++)
                                 for(int j=1;j<6;j++)
                                     qDebug()<<Square[i][j].degree;
                             bianli(Square);
                             exit(0);
                         }
                        return 1;
                    }
                    if (Square[i][j - 1].edge[3] == '1')
                    {
                        copy1(Square,first);
                        Put_chessboard(Square, 0, i, j - 2, turn);
                        if(Equal(Square,first)){
                                                     qDebug()<<"000000000000000 3";
                                                     qDebug()<<"x="<<x;
                                                     qDebug()<<"y="<<y;
                                                     for(int i = 1;i<6;i++)
                                                         for(int j=1;j<6;j++)
                                                             qDebug()<<Square[i][j].degree;
                                                     bianli(Square);
                                                     exit(0);
                                                 }
                        return 1;
                    }
                }
                if (Square[i][j].edge[1] == '1' && Square[i - 1][j].degree == 2)
                {
                    if (Square[i - 1][j].edge[0] == '1')
                    {
                        copy1(Square,first);
                        Put_chessboard(Square, 1, i - 2, j - 1, turn);
                        if(Equal(Square,first)){
                                                     qDebug()<<"000000000000000 4";
                                                     qDebug()<<"x="<<x;
                                                     qDebug()<<"y="<<y;
                                                     for(int i = 1;i<6;i++)
                                                         for(int j=1;j<6;j++)
                                                             qDebug()<<Square[i][j].degree;
                                                     bianli(Square);
                                                     exit(0);
                                                 }
                        return 1;
                    }
                    if (Square[i - 1][j].edge[1] == '1')
                    {
                        copy1(Square,first);
                        qDebug()<<"x="<<x;
                        qDebug()<<"y="<<y;
                        Put_chessboard(Square, 0, i - 2, j - 1, turn);
                        if(Equal(Square,first)){
                                                     qDebug()<<"000000000000000 5";
                                                     qDebug()<<"x="<<x;
                                                     qDebug()<<"y="<<y;
                                                     for(int i = 1;i<6;i++)
                                                         for(int j=1;j<6;j++)
                                                             qDebug()<<Square[i][j].degree;
                                                     bianli(Square);
                                                     exit(0);
                                                 }
                        return 1;
                    }
                    if (Square[i - 1][j].edge[2] == '1')
                    {
                        copy1(Square,first);
                        Put_chessboard(Square, 1, i - 2, j, turn);
                        if(Equal(Square,first)){
                                                     qDebug()<<"000000000000000 6";
                                                     qDebug()<<"x="<<x;
                                                     qDebug()<<"y="<<y;
                                                     for(int i = 1;i<6;i++)
                                                         for(int j=1;j<6;j++)
                                                             qDebug()<<Square[i][j].degree;
                                                     bianli(Square);
                                                     exit(0);
                                                 }
                        return 1;
                    }
                }
                if (Square[i][j].edge[2] == '1' && Square[i][j + 1].degree == 2)
                {
                    if (Square[i][j + 1].edge[1] == '1')
                    {
                        copy1(Square,first);
                        Put_chessboard(Square, 0, i - 1, j, turn);
                        if(Equal(Square,first)){
                                                     qDebug()<<"000000000000000 7";
                                                     qDebug()<<"x="<<x;
                                                     qDebug()<<"y="<<y;
                                                     for(int i = 1;i<6;i++)
                                                         for(int j=1;j<6;j++)
                                                             qDebug()<<Square[i][j].degree;
                                                     bianli(Square);
                                                     exit(0);
                                                 }
                        return 1;
                    }
                    if (Square[i][j + 1].edge[2] == '1')
                    {
                        copy1(Square,first);
                        Put_chessboard(Square, 1, i - 1, j + 1, turn);
                        if(Equal(Square,first)){
                                                     qDebug()<<"000000000000000 8";
                                                     qDebug()<<"x="<<x;
                                                     qDebug()<<"y="<<y;
                                                     for(int i = 1;i<6;i++)
                                                         for(int j=1;j<6;j++)
                                                             qDebug()<<Square[i][j].degree;
                                                     bianli(Square);
                                                     exit(0);
                                                 }
                        return 1;
                    }
                    if (Square[i][j + 1].edge[3] == '1')
                    {
                        copy1(Square,first);
                        Put_chessboard(Square, 0, i, j, turn);
                        if(Equal(Square,first)){
                                                     qDebug()<<"000000000000000 9";
                                                     qDebug()<<"x="<<x;
                                                     qDebug()<<"y="<<y;
                                                     for(int i = 1;i<6;i++)
                                                         for(int j=1;j<6;j++)
                                                             qDebug()<<Square[i][j].degree;
                                                     bianli(Square);
                                                     exit(0);
                                                 }
                        return 1;
                    }
                }
                if (Square[i][j].edge[3] == '1' && Square[i + 1][j].degree == 2)
                {
                    if (Square[i + 1][j].edge[0] == '1')
                    {
                        copy1(Square,first);
                        Put_chessboard(Square, 1, i, j - 1, turn);
                        if(Equal(Square,first)){
                                                     qDebug()<<"000000000000000 10";
                                                     qDebug()<<"x="<<x;
                                                     qDebug()<<"y="<<y;
                                                     for(int i = 1;i<6;i++)
                                                         for(int j=1;j<6;j++)
                                                             qDebug()<<Square[i][j].degree;
                                                     bianli(Square);
                                                     exit(0);
                                                 }
                        return 1;
                    }
                    if (Square[i + 1][j].edge[2] == '1')
                    {
                        copy1(Square,first);
                        Put_chessboard(Square, 1, i, j, turn);
                        if(Equal(Square,first)){
                                                     qDebug()<<"000000000000000 11";
                                                     qDebug()<<"x="<<x;
                                                     qDebug()<<"y="<<y;
                                                     for(int i = 1;i<6;i++)
                                                         for(int j=1;j<6;j++)
                                                             qDebug()<<Square[i][j].degree;
                                                     bianli(Square);
                                                     exit(0);
                                                 }
                        return 1;
                    }
                    if (Square[i + 1][j].edge[3] == '1')
                    {
                        copy1(Square,first);
                        Put_chessboard(Square, 0, i + 1, j - 1, turn);
                        if(Equal(Square,first)){
                                                     qDebug()<<"000000000000000 12";
                                                     qDebug()<<"x="<<x;
                                                     qDebug()<<"y="<<y;
                                                     for(int i = 1;i<6;i++)
                                                         for(int j=1;j<6;j++)
                                                             qDebug()<<Square[i][j].degree;
                                                     bianli(Square);
                                                     exit(0);
                                                 }
                        return 1;
                    }
                }
            }
        }
    }
    for (i = 1; i <= 5; i++)
    {
        for (j = 1; j <= 5; j++)
        {
            if (SingleChain(Square, i, j))								//先给单链                      此处可优化
            {
                if (Square[i][j].edge[0] == '1')
                {
                    copy1(Square,first);
                    Put_chessboard(Square, 1, i - 1, j - 1, turn);
                    if(Equal(Square,first)){
                                                 qDebug()<<"000000000000000 13";
                                                 qDebug()<<"x="<<x;
                                                 qDebug()<<"y="<<y;
                                                 for(int i = 1;i<6;i++)
                                                     for(int j=1;j<6;j++)
                                                         qDebug()<<Square[i][j].degree;
                                                 bianli(Square);
                                                 exit(0);
                                             }
                    return 1;
                }
                if (Square[i][j].edge[1] == '1')
                {
                    copy1(Square,first);
                    Put_chessboard(Square, 0, i - 1, j - 1, turn);
                    if(Equal(Square,first)){
                                                 qDebug()<<"000000000000000 14";
                                                 qDebug()<<"x="<<x;
                                                 qDebug()<<"y="<<y;
                                                 for(int i = 1;i<6;i++)
                                                     for(int j=1;j<6;j++)
                                                         qDebug()<<Square[i][j].degree;
                                                 bianli(Square);
                                                 exit(0);
                                             }
                    return 1;
                }
                if (Square[i][j].edge[2] == '1')
                {
                    copy1(Square,first);
                    Put_chessboard(Square, 1, i - 1, j, turn);
                    if(Equal(Square,first)){
                                                 qDebug()<<"000000000000000 15";
                                                 qDebug()<<"x="<<x;
                                                 qDebug()<<"y="<<y;
                                                 for(int i = 1;i<6;i++)
                                                     for(int j=1;j<6;j++)
                                                         qDebug()<<Square[i][j].degree;
                                                 bianli(Square);
                                                 exit(0);
                                             }
                    return 1;
                }
                if (Square[i][j].edge[3] == '1')
                {
                    copy1(Square,first);
                    Put_chessboard(Square, 0, i, j - 1, turn);
                    if(Equal(Square,first)){
                                                 qDebug()<<"000000000000000 16";
                                                 qDebug()<<"x="<<x;
                                                 qDebug()<<"y="<<y;
                                                 for(int i = 1;i<6;i++)
                                                     for(int j=1;j<6;j++)
                                                         qDebug()<<Square[i][j].degree;
                                                 bianli(Square);
                                                 exit(0);
                                             }
                    return 1;
                }
            }
        }
    }
    for (i = 1; i <= 5; i++)
    {
        for (j = 1; j <= 5; j++)
        {
            x = i;
            y = j;
            if (Square[x][y].degree >= 3)									//找到此三自由度格子
            {
                if (Square[x][y].edge[0] == '1')						//找到此自由个字的无边方向 若为左边
                {
                    if (Square[x][y - 1].degree == 2&&y>1)						//临近三个格子自由度都为二 则不是反双交
                    {
                        if (Square[x][y - 1].edge[0] == '1')
                        {
                            if (Square[x][y - 2].degree >= 3&&y>2)
                            {
                                copy1(Square,first);
                                Put_chessboard(Square, 1, x - 1, y - 1, turn);
                                if(Equal(Square,first)){
                                                             qDebug()<<"000000000000000 17";
                                                             qDebug()<<"x="<<x;
                                                             qDebug()<<"y="<<y;
                                                             for(int i = 1;i<6;i++)
                                                                 for(int j=1;j<6;j++)
                                                                     qDebug()<<Square[i][j].degree;
                                                             bianli(Square);
                                                             exit(0);
                                                         }
                                return 1;
                            }
                            if (Square[x][y - 2].degree == 2&&y>2)
                            {
                                if (Square[x][y - 2].edge[0] == '1'&&y>3)
                                {
                                    if (Square[x][y - 3].degree >= 3)
                                    {
                                        copy1(Square,first);
                                        Put_chessboard(Square, 1, x - 1, y - 2, turn);
                                        if(Equal(Square,first)){
                                                                     qDebug()<<"000000000000000 18";
                                                                     qDebug()<<"x="<<x;
                                                                     qDebug()<<"y="<<y;
                                                                     for(int i = 1;i<6;i++)
                                                                         for(int j=1;j<6;j++)
                                                                             qDebug()<<Square[i][j].degree;
                                                                     bianli(Square);
                                                                     exit(0);
                                                                 }
                                        return 1;
                                    }
                                }
                                if (Square[x][y - 2].edge[1] == '1'&&y>2)
                                {
                                    if (Square[x - 1][y - 2].degree >= 3&&y>2&&x>1)
                                    {
                                        copy1(Square,first);
                                        Put_chessboard(Square, 1, x - 1, y - 2, turn);
                                        if(Equal(Square,first)){
                                                                     qDebug()<<"000000000000000 19";
                                                                     qDebug()<<"x="<<x;
                                                                     qDebug()<<"y="<<y;
                                                                     for(int i = 1;i<6;i++)
                                                                         for(int j=1;j<6;j++)
                                                                             qDebug()<<Square[i][j].degree;
                                                                     bianli(Square);
                                                                     exit(0);
                                                                 }
                                        return 1;
                                    }
                                }
                                if (Square[x][y - 2].edge[3] == '1'&&y>2)
                                {
                                    if (Square[x + 1][y - 2].degree >= 3&&y>2&&x<5)
                                    {
                                        copy1(Square,first);
                                        Put_chessboard(Square, 1, x - 1, y - 2, turn);
                                        if(Equal(Square,first)){
                                                                     qDebug()<<"000000000000000 20";
                                                                     qDebug()<<"x="<<x;
                                                                     qDebug()<<"y="<<y;
                                                                     for(int i = 1;i<6;i++)
                                                                         for(int j=1;j<6;j++)
                                                                             qDebug()<<Square[i][j].degree;
                                                                     bianli(Square);
                                                                     exit(0);
                                                                 }
                                        return 1;
                                    }
                                }
                            }
                        }
                        if (Square[x][y - 1].edge[1] == '1'&&y>1)
                        {
                            if (Square[x - 1][y - 1].degree >= 3&&x>1)
                            {
                                copy1(Square,first);
                                Put_chessboard(Square, 1, x - 1, y - 1, turn);
                                if(Equal(Square,first)){
                                                             qDebug()<<"000000000000000 21";
                                                             qDebug()<<"x="<<x;
                                                             qDebug()<<"y="<<y;
                                                             for(int i = 1;i<6;i++)
                                                                 for(int j=1;j<6;j++)
                                                                     qDebug()<<Square[i][j].degree;
                                                             bianli(Square);
                                                             exit(0);
                                                         }
                                return 1;
                            }
                            if (Square[x - 1][y - 1].degree == 2&&x>1)
                            {
                                if (Square[x - 1][y - 1].edge[0] == '1'&&x>1)
                                {
                                    if (Square[x - 1][y - 2].degree >= 3&&x>1&&y>2)
                                    {
                                        copy1(Square,first);
                                        Put_chessboard(Square, 0, x - 1, y - 2, turn);
                                        if(Equal(Square,first)){
                                                                     qDebug()<<"000000000000000 22";
                                                                     qDebug()<<"x="<<x;
                                                                     qDebug()<<"y="<<y;
                                                                     for(int i = 1;i<6;i++)
                                                                         for(int j=1;j<6;j++)
                                                                             qDebug()<<Square[i][j].degree;
                                                                     bianli(Square);
                                                                     exit(0);
                                                                 }
                                        return 1;
                                    }
                                }
                                if (Square[x - 1][y - 1].edge[1] == '1'&&x>1&&y>1)
                                {
                                    if (Square[x - 2][y - 1].degree >= 3&&x>2&&y>1)
                                    {
                                        copy1(Square,first);
                                        Put_chessboard(Square, 0, x - 1, y - 2, turn);
                                        if(Equal(Square,first)){
                                                                     qDebug()<<"000000000000000 23";
                                                                     qDebug()<<"x="<<x;
                                                                     qDebug()<<"y="<<y;
                                                                     for(int i = 1;i<6;i++)
                                                                         for(int j=1;j<6;j++)
                                                                             qDebug()<<Square[i][j].degree;
                                                                     bianli(Square);
                                                                     exit(0);
                                                                 }
                                        return 1;
                                    }
                                }
                                if (Square[x - 1][y - 1].edge[2] == '1'&&x>1&&y>1)
                                {
                                    if (Square[x - 1][y].degree >= 3)
                                    {
                                        copy1(Square,first);
                                        Put_chessboard(Square, 0, x - 1, y - 2, turn);
                                        if(Equal(Square,first)){
                                                                     qDebug()<<"000000000000000 24";
                                                                     qDebug()<<"x="<<x;
                                                                     qDebug()<<"y="<<y;
                                                                     for(int i = 1;i<6;i++)
                                                                         for(int j=1;j<6;j++)
                                                                             qDebug()<<Square[i][j].degree;
                                                                     bianli(Square);
                                                                     exit(0);
                                                                 }
                                        return 1;
                                    }
                                }
                            }
                        }
                        if (Square[x][y - 1].edge[3] == '1'&&y>1)
                        {
                            if (Square[x + 1][y - 1].degree >= 3&&x<5)
                            {
                                copy1(Square,first);
                                Put_chessboard(Square, 1, x - 1, y - 1, turn);
                                if(Equal(Square,first)){
                                     qDebug()<<"000000000000000 25";
                                     qDebug()<<"x="<<x;
                                     qDebug()<<"y="<<y;
                                     for(int i = 1;i<6;i++)
                                         for(int j=1;j<6;j++)
                                             qDebug()<<Square[i][j].degree;
                                     bianli(Square);
                                     exit(0);
                                 }
                                return 1;
                            }
                            if (Square[x + 1][y - 1].degree == 2&&x<5)
                            {
                                if (Square[x + 1][y - 1].edge[0] == '1'&&x<5&&y>1)
                                {
                                    if (Square[x + 1][y - 2].degree >= 3&&x<5&&y>2)
                                    {
                                        copy1(Square,first);
                                        Put_chessboard(Square, 0, x, y - 2, turn);
                                        if(Equal(Square,first)){
                                             qDebug()<<"000000000000000 26";
                                             qDebug()<<"x="<<x;
                                             qDebug()<<"y="<<y;
                                             for(int i = 1;i<6;i++)
                                                 for(int j=1;j<6;j++)
                                                     qDebug()<<Square[i][j].degree;
                                             bianli(Square);
                                             exit(0);
                                         }
                                        return 1;
                                    }
                                }
                                if (Square[x + 1][y - 1].edge[2] == '1'&&x<5&&y>1)
                                {
                                    if (Square[x + 1][y].degree >= 3)
                                    {
                                        copy1(Square,first);
                                        Put_chessboard(Square, 0, x, y - 2, turn);
                                        if(Equal(Square,first)){
                                             qDebug()<<"000000000000000 27";
                                             qDebug()<<"x="<<x;
                                             qDebug()<<"y="<<y;
                                             for(int i = 1;i<6;i++)
                                                 for(int j=1;j<6;j++)
                                                     qDebug()<<Square[i][j].degree;
                                             bianli(Square);
                                             exit(0);
                                         }
                                        return 1;
                                    }
                                }
                                if (Square[x + 1][y - 1].edge[3] == '1'&&x<5&&y>1)
                                {
                                    if (Square[x + 2][y - 1].degree >= 3&&x<4)
                                    {
                                        copy1(Square,first);
                                        Put_chessboard(Square, 0, x, y - 2, turn);
                                        if(Equal(Square,first)){
                                             qDebug()<<"000000000000000 28";
                                             qDebug()<<"x="<<x;
                                             qDebug()<<"y="<<y;
                                             for(int i = 1;i<6;i++)
                                                 for(int j=1;j<6;j++)
                                                     qDebug()<<Square[i][j].degree;
                                             bianli(Square);
                                             exit(0);
                                         }
                                        return 1;
                                    }
                                }
                            }
                        }
                    }
                }
                if (Square[x][y].edge[1] == '1')						//找到此自由个字的无边方向 若为上边
                {
                    if (Square[x - 1][y].degree == 2&&x>1)						//临近三个格子自由度都为二 则不是反双交
                    {
                        if (Square[x - 1][y].edge[0] == '1')
                        {
                            if (Square[x - 1][y - 1].degree >= 3&&y>1)
                            {
                                copy1(Square,first);
                                Put_chessboard(Square, 0, x - 1, y - 1, turn);
                                if(Equal(Square,first)){
                                     qDebug()<<"000000000000000 29";
                                     qDebug()<<"x="<<x;
                                     qDebug()<<"y="<<y;
                                     for(int i = 1;i<6;i++)
                                         for(int j=1;j<6;j++)
                                             qDebug()<<Square[i][j].degree;
                                     bianli(Square);
                                     exit(0);
                                 }
                                return 1;
                            }
                            if (Square[x - 1][y - 1].degree == 2&&y>1)
                            {
                                if (Square[x - 1][y - 1].edge[0] == '1')
                                {
                                    if (Square[x - 1][y - 2].degree >= 3&&y>2)
                                    {
                                        copy1(Square,first);
                                        Put_chessboard(Square, 1, x - 2, y - 1, turn);
                                        if(Equal(Square,first)){
                                             qDebug()<<"000000000000000 30";
                                             qDebug()<<"x="<<x;
                                             qDebug()<<"y="<<y;
                                             for(int i = 1;i<6;i++)
                                                 for(int j=1;j<6;j++)
                                                     qDebug()<<Square[i][j].degree;
                                             bianli(Square);
                                             exit(0);
                                         }
                                        return 1;
                                    }
                                }
                                if (Square[x - 1][y - 1].edge[1] == '1')
                                {
                                    if (Square[x - 2][y - 1].degree >= 3&&x>2)
                                    {
                                        copy1(Square,first);
                                        Put_chessboard(Square, 1, x - 2, y - 1, turn);
                                        if(Equal(Square,first)){
                                             qDebug()<<"000000000000000 31";
                                             qDebug()<<"x="<<x;
                                             qDebug()<<"y="<<y;
                                             for(int i = 1;i<6;i++)
                                                 for(int j=1;j<6;j++)
                                                     qDebug()<<Square[i][j].degree;
                                             bianli(Square);
                                             exit(0);
                                         }
                                        return 1;
                                    }
                                }
                                if (Square[x - 1][y - 1].edge[3] == '1')
                                {
                                    if (Square[x][y - 1].degree >= 3)
                                    {
                                        copy1(Square,first);
                                        Put_chessboard(Square, 1, x - 2, y - 1, turn);
                                        if(Equal(Square,first)){
                                             qDebug()<<"000000000000000 32";
                                             qDebug()<<"x="<<x;
                                             qDebug()<<"y="<<y;
                                             for(int i = 1;i<6;i++)
                                                 for(int j=1;j<6;j++)
                                                     qDebug()<<Square[i][j].degree;
                                             bianli(Square);
                                             exit(0);
                                         }
                                        return 1;
                                    }
                                }
                            }
                        }
                        if (Square[x - 1][y].edge[1] == '1'&&x>1)
                        {
                            if (Square[x - 2][y].degree >= 3&&x>2)
                            {
                                copy1(Square,first);
                                Put_chessboard(Square, 0, x - 1, y - 1, turn);
                                if(Equal(Square,first)){
                                     qDebug()<<"000000000000000 33";
                                     qDebug()<<"x="<<x;
                                     qDebug()<<"y="<<y;
                                     for(int i = 1;i<6;i++)
                                         for(int j=1;j<6;j++)
                                             qDebug()<<Square[i][j].degree;
                                     bianli(Square);
                                     exit(0);
                                 }
                                return 1;
                            }
                            if (Square[x - 2][y].degree == 2&&x>2)
                            {
                                if (Square[x - 2][y].edge[0] == '1'&&x>2)
                                {
                                    if (Square[x - 2][y - 1].degree >= 3&&x>2&&y>1)
                                    {
                                        copy1(Square,first);
                                        Put_chessboard(Square, 0, x - 2, y - 1, turn);
                                        if(Equal(Square,first)){
                                             qDebug()<<"000000000000000 34";
                                             qDebug()<<"x="<<x;
                                             qDebug()<<"y="<<y;
                                             for(int i = 1;i<6;i++)
                                                 for(int j=1;j<6;j++)
                                                     qDebug()<<Square[i][j].degree;
                                             bianli(Square);
                                             exit(0);
                                         }
                                        return 1;
                                    }
                                }
                                if (Square[x - 2][y].edge[1] == '1'&&x>2)
                                {
                                    if (Square[x - 3][y].degree >= 3&&x>3)
                                    {
                                        copy1(Square,first);
                                        Put_chessboard(Square, 0, x - 2, y - 1, turn);
                                        if(Equal(Square,first)){
                                             qDebug()<<"000000000000000 35";
                                             qDebug()<<"x="<<x;
                                             qDebug()<<"y="<<y;
                                             for(int i = 1;i<6;i++)
                                                 for(int j=1;j<6;j++)
                                                     qDebug()<<Square[i][j].degree;
                                             bianli(Square);
                                             exit(0);
                                         }
                                        return 1;
                                    }
                                }
                                if (Square[x - 2][y].edge[2] == '1'&&x>2)
                                {
                                    if (Square[x - 2][y + 1].degree >= 3&&x>2&&y<5)
                                    {
                                        copy1(Square,first);
                                        Put_chessboard(Square, 0, x - 2, y - 1, turn);
                                        if(Equal(Square,first)){
                                             qDebug()<<"000000000000000 36";
                                             qDebug()<<"x="<<x;
                                             qDebug()<<"y="<<y;
                                             for(int i = 1;i<6;i++)
                                                 for(int j=1;j<6;j++)
                                                     qDebug()<<Square[i][j].degree;
                                             bianli(Square);
                                             exit(0);
                                         }
                                        return 1;
                                    }
                                }
                            }
                        }
                        if (Square[x - 1][y].edge[2] == '1'&&x>1)
                        {
                            if (Square[x - 1][y + 1].degree >= 3&&x>1&&y<5)
                            {
                                copy1(Square,first);
                                Put_chessboard(Square, 0, x - 1, y - 1, turn);
                                if(Equal(Square,first)){
                                     qDebug()<<"000000000000000 37";
                                     qDebug()<<"x="<<x;
                                     qDebug()<<"y="<<y;
                                     for(int i = 1;i<6;i++)
                                         for(int j=1;j<6;j++)
                                             qDebug()<<Square[i][j].degree;
                                     bianli(Square);
                                     exit(0);
                                 }
                                return 1;
                            }
                            if (Square[x - 1][y + 1].degree == 2&&x>1&&y<5)
                            {
                                if (Square[x - 1][y + 1].edge[1] == '1')
                                {
                                    if (Square[x - 2][y + 1].degree >= 3&&x>2&&y<5)
                                    {
                                        copy1(Square,first);
                                        Put_chessboard(Square, 1, x - 2, y, turn);
                                        if(Equal(Square,first)){
                                             qDebug()<<"000000000000000 38";
                                             qDebug()<<"x="<<x;
                                             qDebug()<<"y="<<y;
                                             for(int i = 1;i<6;i++)
                                                 for(int j=1;j<6;j++)
                                                     qDebug()<<Square[i][j].degree;
                                             bianli(Square);
                                             exit(0);
                                         }
                                        return 1;
                                    }
                                }
                                if (Square[x - 1][y + 1].edge[2] == '1')
                                {
                                    if (Square[x - 1][y + 2].degree >= 3&&x>1&&y<4)
                                    {
                                        copy1(Square,first);
                                        Put_chessboard(Square, 1, x - 2, y, turn);
                                        if(Equal(Square,first)){
                                             qDebug()<<"000000000000000 39";
                                             qDebug()<<"x="<<x;
                                             qDebug()<<"y="<<y;
                                             for(int i = 1;i<6;i++)
                                                 for(int j=1;j<6;j++)
                                                     qDebug()<<Square[i][j].degree;
                                             bianli(Square);
                                             exit(0);
                                         }
                                        return 1;
                                    }
                                }
                                if (Square[x - 1][y + 1].edge[3] == '1')
                                {
                                    if (Square[x][y + 1].degree >= 3&&y<5)
                                    {
                                        copy1(Square,first);
                                        Put_chessboard(Square, 1, x - 2, y, turn);
                                        if(Equal(Square,first)){
                                             qDebug()<<"000000000000000 40";
                                             qDebug()<<"x="<<x;
                                             qDebug()<<"y="<<y;
                                             for(int i = 1;i<6;i++)
                                                 for(int j=1;j<6;j++)
                                                     qDebug()<<Square[i][j].degree;
                                             bianli(Square);
                                             exit(0);
                                         }
                                        return 1;
                                    }
                                }
                            }
                        }
                    }
                }
                if (Square[x][y].edge[2] == '1')						//找到此自由个字的无边方向 若为右边
                {
                    if (Square[x][y + 1].degree == 2)						//临近三个格子自由度都为二 则不是反双交
                    {
                        if (Square[x][y + 1].edge[1] == '1')
                        {
                            if (Square[x - 1][y + 1].degree >= 3&&x>1&&y<5)
                            {
                                copy1(Square,first);
                                Put_chessboard(Square, 1, x - 1, y, turn);
                                if(Equal(Square,first)){
                                     qDebug()<<"000000000000000 41";
                                     qDebug()<<"x="<<x;
                                     qDebug()<<"y="<<y;
                                     for(int i = 1;i<6;i++)
                                         for(int j=1;j<6;j++)
                                             qDebug()<<Square[i][j].degree;
                                     bianli(Square);
                                     exit(0);
                                 }
                                return 1;
                            }
                            if (Square[x - 1][y + 1].degree == 2)
                            {
                                if (Square[x - 1][y + 1].edge[0] == '1')
                                {
                                    if (Square[x - 1][y].degree >= 3&&x>1)
                                    {
                                        copy1(Square,first);
                                        Put_chessboard(Square, 0, x - 1, y, turn);
                                        if(Equal(Square,first)){
                                             qDebug()<<"000000000000000 42";
                                             qDebug()<<"x="<<x;
                                             qDebug()<<"y="<<y;
                                             for(int i = 1;i<6;i++)
                                                 for(int j=1;j<6;j++)
                                                     qDebug()<<Square[i][j].degree;
                                             bianli(Square);
                                             exit(0);
                                         }
                                        return 1;
                                    }
                                }
                                if (Square[x - 1][y + 1].edge[1] == '1')
                                {
                                    if (Square[x - 2][y + 1].degree >= 3&&x>2&&y<5)
                                    {
                                        copy1(Square,first);
                                        Put_chessboard(Square, 0, x - 1, y, turn);
                                        if(Equal(Square,first)){
                                             qDebug()<<"000000000000000 43";
                                             qDebug()<<"x="<<x;
                                             qDebug()<<"y="<<y;
                                             for(int i = 1;i<6;i++)
                                                 for(int j=1;j<6;j++)
                                                     qDebug()<<Square[i][j].degree;
                                             bianli(Square);
                                             exit(0);
                                         }
                                        return 1;
                                    }
                                }
                                if (Square[x - 1][y + 1].edge[2] == '1')
                                {
                                    if (Square[x - 1][y + 2].degree >= 3&&x>1&&y<4)
                                    {
                                        copy1(Square,first);
                                        Put_chessboard(Square, 0, x - 1, y, turn);
                                        if(Equal(Square,first)){
                                             qDebug()<<"000000000000000 44";
                                             qDebug()<<"x="<<x;
                                             qDebug()<<"y="<<y;
                                             for(int i = 1;i<6;i++)
                                                 for(int j=1;j<6;j++)
                                                     qDebug()<<Square[i][j].degree;
                                             bianli(Square);
                                             exit(0);
                                         }
                                        return 1;
                                    }
                                }
                            }
                        }
                        if (Square[x][y + 1].edge[2] == '1')
                        {
                            if (Square[x][y + 2].degree >= 3&&y<4)
                            {
                                copy1(Square,first);
                                Put_chessboard(Square, 1, x - 1, y, turn);
                                if(Equal(Square,first)){
                                     qDebug()<<"000000000000000 45";
                                     qDebug()<<"x="<<x;
                                     qDebug()<<"y="<<y;
                                     for(int i = 1;i<6;i++)
                                         for(int j=1;j<6;j++)
                                             qDebug()<<Square[i][j].degree;
                                     bianli(Square);
                                     exit(0);
                                 }
                                return 1;
                            }
                            if (Square[x][y + 2].degree == 2)
                            {
                                if (Square[x][y + 2].edge[1] == '1')
                                {
                                    if (Square[x - 1][y + 2].degree >= 3&&x>1&&y<4)
                                    {
                                        copy1(Square,first);
                                        Put_chessboard(Square, 1, x - 1, y + 1, turn);
                                        if(Equal(Square,first)){
                                             qDebug()<<"000000000000000 46";
                                             qDebug()<<"x="<<x;
                                             qDebug()<<"y="<<y;
                                             for(int i = 1;i<6;i++)
                                                 for(int j=1;j<6;j++)
                                                     qDebug()<<Square[i][j].degree;
                                             bianli(Square);
                                             exit(0);
                                         }
                                        return 1;
                                    }
                                }
                                if (Square[x][y + 2].edge[2] == '1')
                                {
                                    if (Square[x][y + 3].degree >= 3&&y<3)
                                    {
                                        copy1(Square,first);
                                        Put_chessboard(Square, 1, x - 1, y + 1, turn);
                                        if(Equal(Square,first)){
                                             qDebug()<<"000000000000000 47";
                                             qDebug()<<"x="<<x;
                                             qDebug()<<"y="<<y;
                                             for(int i = 1;i<6;i++)
                                                 for(int j=1;j<6;j++)
                                                     qDebug()<<Square[i][j].degree;
                                             bianli(Square);
                                             exit(0);
                                         }
                                        return 1;
                                    }
                                }
                                if (Square[x][y + 2].edge[3] == '1')
                                {
                                    if (Square[x + 1][y + 2].degree >= 3&&x<5&&y<4)
                                    {
                                        copy1(Square,first);
                                        Put_chessboard(Square, 1, x - 1, y + 1, turn);
                                        if(Equal(Square,first)){
                                             qDebug()<<"000000000000000 48";
                                             qDebug()<<"x="<<x;
                                             qDebug()<<"y="<<y;
                                             for(int i = 1;i<6;i++)
                                                 for(int j=1;j<6;j++)
                                                     qDebug()<<Square[i][j].degree;
                                             bianli(Square);
                                             exit(0);
                                         }
                                        return 1;
                                    }
                                }
                            }
                        }
                        if (Square[x][y + 1].edge[3] == '1')
                        {
                            if (Square[x + 1][y + 1].degree >= 3&&x<5&&y<5)
                            {
                                copy1(Square,first);
                                Put_chessboard(Square, 1, x - 1, y, turn);
                                if(Equal(Square,first)){
                                     qDebug()<<"000000000000000 49";
                                     qDebug()<<"x="<<x;
                                     qDebug()<<"y="<<y;
                                     for(int i = 1;i<6;i++)
                                         for(int j=1;j<6;j++)
                                             qDebug()<<Square[i][j].degree;
                                     bianli(Square);
                                     exit(0);
                                 }
                                return 1;
                            }
                            if (Square[x + 1][y + 1].degree == 2)
                            {
                                if (Square[x + 1][y + 1].edge[0] == '1')
                                {
                                    if (Square[x + 1][y].degree >= 3&&x<5)
                                    {
                                        copy1(Square,first);
                                        Put_chessboard(Square, 0, x, y, turn);
                                        if(Equal(Square,first)){
                                             qDebug()<<"000000000000000 50";
                                             qDebug()<<"x="<<x;
                                             qDebug()<<"y="<<y;
                                             for(int i = 1;i<6;i++)
                                                 for(int j=1;j<6;j++)
                                                     qDebug()<<Square[i][j].degree;
                                             bianli(Square);
                                             exit(0);
                                         }
                                        return 1;
                                    }
                                }
                                if (Square[x + 1][y + 1].edge[2] == '1')
                                {
                                    if (Square[x + 1][y + 2].degree >= 3&&x<5&&y<4)
                                    {
                                        copy1(Square,first);
                                        Put_chessboard(Square, 0, x, y, turn);
                                        if(Equal(Square,first)){
                                             qDebug()<<"000000000000000 51";
                                             qDebug()<<"x="<<x;
                                             qDebug()<<"y="<<y;
                                             for(int i = 1;i<6;i++)
                                                 for(int j=1;j<6;j++)
                                                     qDebug()<<Square[i][j].degree;
                                             bianli(Square);
                                             exit(0);
                                         }
                                        return 1;
                                    }
                                }
                                if (Square[x + 1][y + 1].edge[3] == '1')
                                {
                                    if (Square[x + 2][y + 1].degree >= 3&&x<4&&y<5)
                                    {
                                        copy1(Square,first);
                                        Put_chessboard(Square, 0, x, y, turn);
                                        if(Equal(Square,first)){
                                             qDebug()<<"000000000000000 52";
                                             qDebug()<<"x="<<x;
                                             qDebug()<<"y="<<y;
                                             for(int i = 1;i<6;i++)
                                                 for(int j=1;j<6;j++)
                                                     qDebug()<<Square[i][j].degree;
                                             bianli(Square);
                                             exit(0);
                                         }
                                        return 1;
                                    }
                                }
                            }
                        }
                    }
                }
                if (Square[x][y].edge[3] == '1')						//找到此自由个字的无边方向 若为下边
                {
                    if (Square[x + 1][y].degree == 2)						//临近三个格子自由度都为二 则不是反双交
                    {
                        if (Square[x + 1][y].edge[0] == '1')
                        {
                            if (Square[x + 1][y - 1].degree >= 3&&x<5&&y>1)
                            {
                                copy1(Square,first);
                                Put_chessboard(Square, 0, x, y - 1, turn);
                                if(Equal(Square,first)){
                                     qDebug()<<"000000000000000 53";
                                     qDebug()<<"x="<<x;
                                     qDebug()<<"y="<<y;
                                     for(int i = 1;i<6;i++)
                                         for(int j=1;j<6;j++)
                                             qDebug()<<Square[i][j].degree;
                                     bianli(Square);
                                     exit(0);
                                 }
                                return 1;
                            }
                            if (Square[x + 1][y - 1].degree == 2)
                            {
                                if (Square[x + 1][y - 1].edge[0] == '1')
                                {
                                    if (Square[x + 1][y - 2].degree >= 3&&x<5&&y>2)
                                    {
                                        copy1(Square,first);
                                        Put_chessboard(Square, 1, x, y - 1, turn);
                                        if(Equal(Square,first)){
                                             qDebug()<<"000000000000000 54";
                                             qDebug()<<"x="<<x;
                                             qDebug()<<"y="<<y;
                                             for(int i = 1;i<6;i++)
                                                 for(int j=1;j<6;j++)
                                                     qDebug()<<Square[i][j].degree;
                                             bianli(Square);
                                             exit(0);
                                         }
                                        return 1;
                                    }
                                }
                                if (Square[x + 1][y - 1].edge[1] == '1')
                                {
                                    if (Square[x][y - 1].degree >= 3&&y>1)
                                    {
                                        copy1(Square,first);
                                        Put_chessboard(Square, 1, x, y - 1, turn);
                                        if(Equal(Square,first)){
                                             qDebug()<<"000000000000000 55";
                                             qDebug()<<"x="<<x;
                                             qDebug()<<"y="<<y;
                                             for(int i = 1;i<6;i++)
                                                 for(int j=1;j<6;j++)
                                                     qDebug()<<Square[i][j].degree;
                                             bianli(Square);
                                             exit(0);
                                         }
                                        return 1;
                                    }
                                }
                                if (Square[x + 1][y - 1].edge[3] == '1')
                                {
                                    if (Square[x + 2][y - 1].degree >= 3&&x<4&&y>1)
                                    {
                                        copy1(Square,first);
                                        Put_chessboard(Square, 1, x, y - 1, turn);
                                        if(Equal(Square,first)){
                                             qDebug()<<"000000000000000 56";
                                             qDebug()<<"x="<<x;
                                             qDebug()<<"y="<<y;
                                             for(int i = 1;i<6;i++)
                                                 for(int j=1;j<6;j++)
                                                     qDebug()<<Square[i][j].degree;
                                             bianli(Square);
                                             exit(0);
                                         }
                                        return 1;
                                    }
                                }
                            }
                        }
                        if (Square[x + 1][y].edge[2] == '1')
                        {
                            if (Square[x + 1][y + 1].degree >= 3&&x<5&&y<5)
                            {
                                copy1(Square,first);
                                Put_chessboard(Square, 0, x, y - 1, turn);
                                if(Equal(Square,first)){
                                     qDebug()<<"000000000000000 57";
                                     qDebug()<<"x="<<x;
                                     qDebug()<<"y="<<y;
                                     for(int i = 1;i<6;i++)
                                         for(int j=1;j<6;j++)
                                             qDebug()<<Square[i][j].degree;
                                     bianli(Square);
                                     exit(0);
                                 }
                                return 1;
                            }
                            if (Square[x + 1][y + 1].degree == 2)
                            {
                                if (Square[x + 1][y + 1].edge[1] == '1')
                                {
                                    if (Square[x][y + 1].degree >= 3&&y<5)
                                    {
                                        copy1(Square,first);
                                        Put_chessboard(Square, 1, x, y, turn);
                                        if(Equal(Square,first)){
                                             qDebug()<<"000000000000000 58";
                                             qDebug()<<"x="<<x;
                                             qDebug()<<"y="<<y;
                                             for(int i = 1;i<6;i++)
                                                 for(int j=1;j<6;j++)
                                                     qDebug()<<Square[i][j].degree;
                                             bianli(Square);
                                             exit(0);
                                         }
                                        return 1;
                                    }
                                }
                                if (Square[x + 1][y + 1].edge[2] == '1')
                                {
                                    if (Square[x + 1][y + 2].degree >= 3&&x<5&&y<4)
                                    {
                                        copy1(Square,first);
                                        Put_chessboard(Square, 1, x, y, turn);
                                        if(Equal(Square,first)){
                                             qDebug()<<"000000000000000 59";
                                             qDebug()<<"x="<<x;
                                             qDebug()<<"y="<<y;
                                             for(int i = 1;i<6;i++)
                                                 for(int j=1;j<6;j++)
                                                     qDebug()<<Square[i][j].degree;
                                             bianli(Square);
                                             exit(0);
                                         }
                                        return 1;
                                    }
                                }
                                if (Square[x + 1][y + 1].edge[3] == '1')
                                {
                                    if (Square[x + 2][y + 1].degree >= 3&&x<4&&y<5)
                                    {
                                        copy1(Square,first);
                                        Put_chessboard(Square, 1, x, y, turn);
                                        qDebug()<<"x="<<x;
                                        qDebug()<<"y="<<y;
                                        if(Equal(Square,first)){
                                             qDebug()<<"000000000000000 60";
                                             for(int i = 1;i<6;i++)
                                                 for(int j=1;j<6;j++)
                                                     qDebug()<<Square[i][j].degree;
                                             bianli(Square);
                                             exit(0);
                                         }
                                        return 1;
                                    }
                                }
                            }
                        }
                        if (Square[x + 1][y].edge[3] == '1')
                        {
                            if (Square[x + 2][y].degree >= 3&&x<4)
                            {
                                copy1(Square,first);
                                Put_chessboard(Square, 0, x, y - 1, turn);
                                if(Equal(Square,first)){
                                     qDebug()<<"000000000000000 61";
                                     qDebug()<<"x="<<x;
                                     qDebug()<<"y="<<y;
                                     for(int i = 1;i<6;i++)
                                         for(int j=1;j<6;j++)
                                             qDebug()<<Square[i][j].degree;
                                     bianli(Square);
                                     exit(0);
                                 }
                                return 1;
                            }
                            if (Square[x + 2][y].degree == 2)
                            {
                                if (Square[x + 2][y].edge[0] == '1')
                                {
                                    if (Square[x + 2][y - 1].degree >= 3&&x<4&&y>1)
                                    {
                                        copy1(Square,first);
                                        Put_chessboard(Square, 1, x + 1, y - 1, turn);
                                        if(Equal(Square,first)){
                                             qDebug()<<"000000000000000 62";
                                             qDebug()<<"x="<<x;
                                             qDebug()<<"y="<<y;
                                             for(int i = 1;i<6;i++)
                                                 for(int j=1;j<6;j++)
                                                     qDebug()<<Square[i][j].degree;
                                             bianli(Square);
                                             exit(0);
                                         }
                                        return 1;
                                    }
                                }
                                if (Square[x + 2][y].edge[2] == '1')
                                {
                                    if (Square[x + 2][y + 1].degree >= 3&&x<4&&y<5)
                                    {
                                        copy1(Square,first);
                                        Put_chessboard(Square, 1, x + 1, y , turn);
                                        if(Equal(Square,first)){
                                             qDebug()<<"000000000000000 63";
                                             qDebug()<<"x="<<x;
                                             qDebug()<<"y="<<y;
                                             for(int i = 1;i<6;i++)
                                                 for(int j=1;j<6;j++)
                                                     qDebug()<<Square[i][j].degree;
                                             bianli(Square);
                                             exit(0);
                                         }
                                        return 1;
                                    }
                                }
                                if (Square[x + 2][y].edge[3] == '1')
                                {
                                    if (Square[x + 3][y].degree >= 3&&x<3)
                                    {
                                        copy1(Square,first);
                                        Put_chessboard(Square, 0, x + 2, y - 1, turn);
                                        if(Equal(Square,first)){
                                             qDebug()<<"000000000000000 64";
                                             qDebug()<<"x="<<x;
                                             qDebug()<<"y="<<y;
                                             for(int i = 1;i<6;i++)
                                                 for(int j=1;j<6;j++)
                                                     qDebug()<<Square[i][j].degree;
                                             bianli(Square);
                                             exit(0);
                                         }
                                        return 1;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return 1;
}

int AI::Give_Boxes_Odd(Situation Square[6][6], int turn)											//反双交个数为奇数时的让格,此处返回值无意义
{

    int i, j, x, y;
    for (i = 1; i <= 5; i++)
    {
        for (j = 1; j <= 5; j++)
        {
            if (SingleChain(Square, i, j))								//先给单链                      此处可优化
            {
                if (Square[i][j].edge[0] == '1')
                {
                    copy1(Square,first);
                    Put_chessboard(Square, 1, i - 1, j - 1, turn);
                    if(Equal(Square,first)){
                         qDebug()<<"000000000000000 65";
                         qDebug()<<"x="<<x;
                         qDebug()<<"y="<<y;
                         for(int i = 1;i<6;i++)
                             for(int j=1;j<6;j++)
                                 qDebug()<<Square[i][j].degree;
                         bianli(Square);
                         exit(0);
                     }
                    return 1;
                }
                if (Square[i][j].edge[1] == '1')
                {
                    copy1(Square,first);
                    Put_chessboard(Square, 0, i - 1, j - 1, turn);
                    if(Equal(Square,first)){
                         qDebug()<<"000000000000000 66";
                         qDebug()<<"x="<<x;
                         qDebug()<<"y="<<y;
                         for(int i = 1;i<6;i++)
                             for(int j=1;j<6;j++)
                                 qDebug()<<Square[i][j].degree;
                         bianli(Square);
                         exit(0);
                     }
                    return 1;
                }
                if (Square[i][j].edge[2] == '1')
                {
                    copy1(Square,first);
                    Put_chessboard(Square, 1, i - 1, j, turn);
                    if(Equal(Square,first)){
                         qDebug()<<"000000000000000 67";
                         qDebug()<<"x="<<x;
                         qDebug()<<"y="<<y;
                         for(int i = 1;i<6;i++)
                             for(int j=1;j<6;j++)
                                 qDebug()<<Square[i][j].degree;
                         bianli(Square);
                         exit(0);
                     }
                    return 1;
                }
                if (Square[i][j].edge[3] == '1')
                {
                    copy1(Square,first);
                    Put_chessboard(Square, 0, i, j - 1, turn);
                    if(Equal(Square,first)){
                         qDebug()<<"000000000000000 68";
                         qDebug()<<"x="<<x;
                         qDebug()<<"y="<<y;
                         for(int i = 1;i<6;i++)
                             for(int j=1;j<6;j++)
                                 qDebug()<<Square[i][j].degree;
                         bianli(Square);
                         exit(0);
                     }
                    return 1;
                }
            }
        }
    }

    for (i = 1; i <= 5; i++)
    {
        for (j = 1; j <= 5; j++)
        {
            x = i;
            y = j;
            if (Square[x][y].degree == 3)									//找到此三自由度格子
            {
                if (Square[x][y].edge[0] == '1')						//找到此自由个字的无边方向 若为左边
                {
                    if (Square[x][y - 1].degree == 2)						//临近三个格子自由度都为二 则不是反双交
                    {
                        if(j==2&&i==1){
                            Put_chessboard(Square, 1, x-1 , y-1 , turn);
                        }
                        if (Square[x][y - 1].edge[0] == '1')
                        {
                            if (Square[x][y - 2].degree >= 3&&y>2&&x>1)
                            {
                                copy1(Square,first);
                                Put_chessboard(Square, 1, x - 1, y - 1, turn);
                                if(Equal(Square,first)){
                                     qDebug()<<"000000000000000 69";
                                     qDebug()<<"x="<<x;
                                     qDebug()<<"y="<<y;
                                     for(int i = 1;i<6;i++)
                                         for(int j=1;j<6;j++)
                                             qDebug()<<Square[i][j].degree;
                                     bianli(Square);
                                     exit(0);
                                 }
                                return 1;
                            }
                            if (Square[x][y - 2].degree == 2)
                            {
                                if (Square[x][y - 2].edge[0] == '1')
                                {
                                    if (Square[x][y - 3].degree >= 3&&x>1&&y>3)
                                    {
                                        copy1(Square,first);
                                        Put_chessboard(Square, 1, x - 1, y - 2, turn);
                                        if(Equal(Square,first)){
                                             qDebug()<<"000000000000000 70";
                                             qDebug()<<"x="<<x;
                                             qDebug()<<"y="<<y;
                                             for(int i = 1;i<6;i++)
                                                 for(int j=1;j<6;j++)
                                                     qDebug()<<Square[i][j].degree;
                                             bianli(Square);
                                             exit(0);
                                         }
                                        return 1;
                                    }
                                }
                                if (Square[x][y - 2].edge[1] == '1')
                                {
                                    if (Square[x - 1][y - 2].degree >=3&&x>1&&y>2)
                                    {
                                        copy1(Square,first);
                                        Put_chessboard(Square, 1, x - 1, y - 2, turn);
                                        if(Equal(Square,first)){
                                             qDebug()<<"000000000000000 71";
                                             qDebug()<<"x="<<x;
                                             qDebug()<<"y="<<y;
                                             for(int i = 1;i<6;i++)
                                                 for(int j=1;j<6;j++)
                                                     qDebug()<<Square[i][j].degree;
                                             bianli(Square);
                                             exit(0);
                                         }
                                        return 1;
                                    }
                                }
                                if (Square[x][y - 2].edge[3] == '1')
                                {
                                    if (Square[x + 1][y - 2].degree >=3&&x<5&&y>2)
                                    {
                                        copy1(Square,first);
                                        Put_chessboard(Square, 0, x , y - 3, turn);
                                        if(Equal(Square,first)){
                                             qDebug()<<"000000000000000 72";
                                             qDebug()<<"x="<<x;
                                             qDebug()<<"y="<<y;
                                             for(int i = 1;i<6;i++)
                                                 for(int j=1;j<6;j++)
                                                     qDebug()<<Square[i][j].degree;
                                             bianli(Square);
                                             exit(0);
                                         }
                                        return 1;
                                    }
                                }
                            }
                        }
                        if (Square[x][y - 1].edge[1] == '1')
                        {
                            if (Square[x - 1][y - 1].degree >=3&&x>1&&y>1)
                            {
                                copy1(Square,first);
                                Put_chessboard(Square, 1, x - 1, y - 1, turn);
                                if(Equal(Square,first)){
                                     qDebug()<<"000000000000000 73";
                                     qDebug()<<"x="<<x;
                                     qDebug()<<"y="<<y;
                                     for(int i = 1;i<6;i++)
                                         for(int j=1;j<6;j++)
                                             qDebug()<<Square[i][j].degree;
                                     bianli(Square);
                                     exit(0);
                                 }
                                return 1;
                            }
                            if (Square[x - 1][y - 1].degree == 2)
                            {
                                if (Square[x - 1][y - 1].edge[0] == '1')
                                {
                                    if (Square[x - 1][y - 2].degree >=3&&x>1&&y>2)
                                    {
                                        copy1(Square,first);
                                        Put_chessboard(Square, 0, x - 1, y - 2, turn);
                                        if(Equal(Square,first)){
                                             qDebug()<<"000000000000000 74";
                                             qDebug()<<"x="<<x;
                                             qDebug()<<"y="<<y;
                                             for(int i = 1;i<6;i++)
                                                 for(int j=1;j<6;j++)
                                                     qDebug()<<Square[i][j].degree;
                                             bianli(Square);
                                             exit(0);
                                         }
                                        return 1;
                                    }
                                }
                                if (Square[x - 1][y - 1].edge[1] == '1')
                                {
                                    if (Square[x - 2][y - 1].degree >=3&&x>2&&y>2)
                                    {
                                        copy1(Square,first);
                                        Put_chessboard(Square, 0, x - 1, y - 2, turn);
                                        if(Equal(Square,first)){
                                             qDebug()<<"000000000000000 75";
                                             qDebug()<<"x="<<x;
                                             qDebug()<<"y="<<y;
                                             for(int i = 1;i<6;i++)
                                                 for(int j=1;j<6;j++)
                                                     qDebug()<<Square[i][j].degree;
                                             bianli(Square);
                                             exit(0);
                                         }
                                        return 1;
                                    }
                                }
                                if (Square[x - 1][y - 1].edge[2] == '1')
                                {
                                    if (Square[x - 1][y].degree >=3 &&x>1&&y>=2)
                                    {
                                        copy1(Square,first);
                                        Put_chessboard(Square, 0, x - 1, y - 2, turn);
                                        if(Equal(Square,first)){
                                             qDebug()<<"000000000000000 76";
                                             qDebug()<<"x="<<x;
                                             qDebug()<<"y="<<y;
                                             for(int i = 1;i<6;i++)
                                                 for(int j=1;j<6;j++)
                                                     qDebug()<<Square[i][j].degree;
                                             bianli(Square);
                                             exit(0);
                                         }
                                        return 1;
                                    }
                                }
                            }
                        }
                        if (Square[x][y - 1].edge[3] == '1')
                        {
                            if (Square[x + 1][y - 1].degree >=3&&x>1&&x<5&&y<5)
                            {
                                copy1(Square,first);
                                Put_chessboard(Square, 1, x - 1, y - 1, turn);
                                if(Equal(Square,first)){
                                     qDebug()<<"000000000000000 77";
                                     qDebug()<<"x="<<x;
                                     qDebug()<<"y="<<y;
                                     for(int i = 1;i<6;i++)
                                         for(int j=1;j<6;j++)
                                             qDebug()<<Square[i][j].degree;
                                     bianli(Square);
                                     exit(0);
                                 }
                                return 1;
                            }
                            if (Square[x + 1][y - 1].degree == 2)
                            {
                                if (Square[x + 1][y - 1].edge[0] == '1')
                                {
                                    if (Square[x + 1][y - 2].degree >=3&&x<5&&y>2)
                                    {
                                        copy1(Square,first);
                                        Put_chessboard(Square, 0, x, y - 2, turn);
                                        if(Equal(Square,first)){
                                             qDebug()<<"000000000000000 78";
                                             qDebug()<<"x="<<x;
                                             qDebug()<<"y="<<y;
                                             for(int i = 1;i<6;i++)
                                                 for(int j=1;j<6;j++)
                                                     qDebug()<<Square[i][j].degree;
                                             bianli(Square);
                                             exit(0);
                                         }
                                        return 1;
                                    }
                                }
                                if (Square[x + 1][y - 1].edge[2] == '1')
                                {
                                    if (Square[x + 1][y].degree >=3&&x<5&&y>2)
                                    {
                                        copy1(Square,first);
                                        Put_chessboard(Square, 0, x, y - 2, turn);
                                        if(Equal(Square,first)){
                                             qDebug()<<"000000000000000 79";
                                             qDebug()<<"x="<<x;
                                             qDebug()<<"y="<<y;
                                             for(int i = 1;i<6;i++)
                                                 for(int j=1;j<6;j++)
                                                     qDebug()<<Square[i][j].degree;
                                             bianli(Square);
                                             exit(0);
                                         }
                                        return 1;
                                    }
                                }
                                if (Square[x + 1][y - 1].edge[3] == '1')
                                {
                                    if (Square[x + 2][y - 1].degree >=3&&x<4&&y>1)
                                    {
                                        copy1(Square,first);
                                        Put_chessboard(Square, 0, x + 1, y - 2, turn);
                                        if(Equal(Square,first)){
                                             qDebug()<<"000000000000000 80";
                                             qDebug()<<"x="<<x;
                                             qDebug()<<"y="<<y;
                                             for(int i = 1;i<6;i++)
                                                 for(int j=1;j<6;j++)
                                                     qDebug()<<Square[i][j].degree;
                                             bianli(Square);
                                             exit(0);
                                         }
                                        return 1;
                                    }
                                }
                            }
                        }
                    }
                }
                if (Square[x][y].edge[1] == '1')						//找到此自由个字的无边方向 若为上边
                {
                    if (Square[x - 1][y].degree == 2)						//临近三个格子自由度都为二 则不是反双交
                    {
                        if (Square[x - 1][y].edge[0] == '1')
                        {
                            if (Square[x - 1][y - 1].degree >=3&&x>1&&y>1)
                            {
                                copy1(Square,first);
                                Put_chessboard(Square, 0, x - 1, y - 1, turn);
                                if(Equal(Square,first)){
                                     qDebug()<<"000000000000000 81";
                                     qDebug()<<"x="<<x;
                                     qDebug()<<"y="<<y;
                                     for(int i = 1;i<6;i++)
                                         for(int j=1;j<6;j++)
                                             qDebug()<<Square[i][j].degree;
                                     bianli(Square);
                                     exit(0);
                                 }
                                return 1;
                            }
                            if (Square[x - 1][y - 1].degree == 2)
                            {
                                if (Square[x - 1][y - 1].edge[0] == '1')
                                {
                                    if (Square[x - 1][y - 2].degree >=3&&x>2&&y>2)
                                    {
                                        copy1(Square,first);
                                        Put_chessboard(Square, 1, x - 2, y - 1, turn);
                                        if(Equal(Square,first)){
                                             qDebug()<<"000000000000000 82";
                                             qDebug()<<"x="<<x;
                                             qDebug()<<"y="<<y;
                                             for(int i = 1;i<6;i++)
                                                 for(int j=1;j<6;j++)
                                                     qDebug()<<Square[i][j].degree;
                                             bianli(Square);
                                             exit(0);
                                         }
                                        return 1;
                                    }
                                }
                                if (Square[x - 1][y - 1].edge[1] == '1')
                                {
                                    if (Square[x - 2][y - 1].degree >=3&&x>2&&y>1)
                                    {
                                        copy1(Square,first);
                                        Put_chessboard(Square, 1, x - 2, y - 1, turn);
                                        if(Equal(Square,first)){
                                             qDebug()<<"000000000000000 83";
                                             qDebug()<<"x="<<x;
                                             qDebug()<<"y="<<y;
                                             for(int i = 1;i<6;i++)
                                                 for(int j=1;j<6;j++)
                                                     qDebug()<<Square[i][j].degree;
                                             bianli(Square);
                                             exit(0);
                                         }
                                        return 1;
                                    }
                                }
                                if (Square[x - 1][y - 1].edge[3] == '1')
                                {
                                    if (Square[x][y - 1].degree >=3&&x>2&&y>1)
                                    {
                                        copy1(Square,first);
                                        Put_chessboard(Square, 1, x - 2, y - 1, turn);
                                        if(Equal(Square,first)){
                                             qDebug()<<"000000000000000 84";
                                             qDebug()<<"x="<<x;
                                             qDebug()<<"y="<<y;
                                             for(int i = 1;i<6;i++)
                                                 for(int j=1;j<6;j++)
                                                     qDebug()<<Square[i][j].degree;
                                             bianli(Square);
                                             exit(0);
                                         }
                                        return 1;
                                    }
                                }
                            }
                        }
                        if (Square[x - 1][y].edge[1] == '1')
                        {
                            if (Square[x - 2][y].degree >=3&&x>2&&y>1)
                            {
                                copy1(Square,first);
                                Put_chessboard(Square, 0, x - 1, y - 1, turn);
                                if(Equal(Square,first)){
                                     qDebug()<<"000000000000000 85";
                                     qDebug()<<"x="<<x;
                                     qDebug()<<"y="<<y;
                                     for(int i = 1;i<6;i++)
                                         for(int j=1;j<6;j++)
                                             qDebug()<<Square[i][j].degree;
                                     bianli(Square);
                                     exit(0);
                                 }
                                return 1;
                            }
                            if (Square[x - 2][y].degree == 2)
                            {
                                if (Square[x - 2][y].edge[0] == '1')
                                {
                                    if (Square[x - 2][y - 1].degree >=3&&x>2&&y>1)
                                    {
                                        copy1(Square,first);
                                        Put_chessboard(Square, 0, x - 2, y - 1, turn);
                                        if(Equal(Square,first)){
                                             qDebug()<<"000000000000000 86";
                                             qDebug()<<"x="<<x;
                                             qDebug()<<"y="<<y;
                                             for(int i = 1;i<6;i++)
                                                 for(int j=1;j<6;j++)
                                                     qDebug()<<Square[i][j].degree;
                                             bianli(Square);
                                             exit(0);
                                         }
                                        return 1;
                                    }
                                }
                                if (Square[x - 2][y].edge[1] == '1')
                                {
                                    if (Square[x - 3][y].degree >=3 &&x>3&&y>1)
                                    {
                                        copy1(Square,first);
                                        Put_chessboard(Square, 0, x - 2, y - 1, turn);
                                        if(Equal(Square,first)){
                                             qDebug()<<"000000000000000 87";
                                             qDebug()<<"x="<<x;
                                             qDebug()<<"y="<<y;
                                             for(int i = 1;i<6;i++)
                                                 for(int j=1;j<6;j++)
                                                     qDebug()<<Square[i][j].degree;
                                             bianli(Square);
                                             exit(0);
                                         }
                                        return 1;
                                    }
                                }
                                if (Square[x - 2][y].edge[2] == '1')
                                {
                                    if (Square[x - 2][y + 1].degree >=3&&x>2&&y<5)
                                    {
                                        copy1(Square,first);
                                        Put_chessboard(Square, 1, x - 3, y , turn);
                                        if(Equal(Square,first)){
                                             qDebug()<<"000000000000000 88";
                                             qDebug()<<"x="<<x;
                                             qDebug()<<"y="<<y;
                                             for(int i = 1;i<6;i++)
                                                 for(int j=1;j<6;j++)
                                                     qDebug()<<Square[i][j].degree;
                                             bianli(Square);
                                             exit(0);
                                         }
                                        return 1;
                                    }
                                }
                            }
                        }
                        if (Square[x - 1][y].edge[2] == '1')
                        {
                            if (Square[x - 1][y + 1].degree >=3&&x>1&&y>1&&y<5)
                            {
                                copy1(Square,first);
                                Put_chessboard(Square, 0, x - 1, y - 1, turn);
                                if(Equal(Square,first)){
                                     qDebug()<<"000000000000000 89";
                                     qDebug()<<"x="<<x;
                                     qDebug()<<"y="<<y;
                                     for(int i = 1;i<6;i++)
                                         for(int j=1;j<6;j++)
                                             qDebug()<<Square[i][j].degree;
                                     bianli(Square);
                                     exit(0);
                                 }
                                return 1;
                            }
                            if (Square[x - 1][y + 1].degree == 2)
                            {
                                if (Square[x - 1][y + 1].edge[1] == '1')
                                {
                                    if (Square[x - 2][y + 1].degree >=3&&x>2&&y<5)
                                    {
                                        copy1(Square,first);
                                        Put_chessboard(Square, 1, x - 2, y, turn);
                                        if(Equal(Square,first)){
                                             qDebug()<<"000000000000000 90";
                                             qDebug()<<"x="<<x;
                                             qDebug()<<"y="<<y;
                                             for(int i = 1;i<6;i++)
                                                 for(int j=1;j<6;j++)
                                                     qDebug()<<Square[i][j].degree;
                                             bianli(Square);
                                             exit(0);
                                         }
                                        return 1;
                                    }
                                }
                                if (Square[x - 1][y + 1].edge[2] == '1')
                                {
                                    if (Square[x - 1][y + 2].degree >=3&&x>2&&y<4)
                                    {
                                        copy1(Square,first);
                                        Put_chessboard(Square, 1, x - 2, y, turn);
                                        if(Equal(Square,first)){
                                             qDebug()<<"000000000000000 91";
                                             qDebug()<<"x="<<x;
                                             qDebug()<<"y="<<y;
                                             for(int i = 1;i<6;i++)
                                                 for(int j=1;j<6;j++)
                                                     qDebug()<<Square[i][j].degree;
                                             bianli(Square);
                                             exit(0);
                                         }
                                        return 1;
                                    }
                                }
                                if (Square[x - 1][y + 1].edge[3] == '1')
                                {
                                    if (Square[x][y + 1].degree >=3&&y<5)
                                    {
                                        copy1(Square,first);
                                        Put_chessboard(Square, 0, x - 1, y, turn);
                                        if(Equal(Square,first)){
                                             qDebug()<<"000000000000000 92";
                                             qDebug()<<"x="<<x;
                                             qDebug()<<"y="<<y;
                                             for(int i = 1;i<6;i++)
                                                 for(int j=1;j<6;j++)
                                                     qDebug()<<Square[i][j].degree;
                                             bianli(Square);
                                             exit(0);
                                         }
                                        return 1;
                                    }
                                }
                            }
                        }
                    }
                }
                if (Square[x][y].edge[2] == '1')						//找到此自由个字的无边方向 若为右边
                {
                    if (Square[x][y + 1].degree == 2)						//临近三个格子自由度都为二 则不是反双交
                    {
                        if (Square[x][y + 1].edge[1] == '1')
                        {
                            if (Square[x - 1][y + 1].degree >=3&&x>1&&y<5)
                            {
                                copy1(Square,first);
                                Put_chessboard(Square, 1, x - 1, y, turn);
                                if(Equal(Square,first)){
                                     qDebug()<<"000000000000000 93";
                                     qDebug()<<"x="<<x;
                                     qDebug()<<"y="<<y;
                                     for(int i = 1;i<6;i++)
                                         for(int j=1;j<6;j++)
                                             qDebug()<<Square[i][j].degree;
                                     bianli(Square);
                                     exit(0);
                                 }
                                return 1;
                            }
                            if (Square[x - 1][y + 1].degree == 2)
                            {
                                if (Square[x - 1][y + 1].edge[0] == '1')
                                {
                                    if (Square[x - 1][y].degree >=3&&x>1)
                                    {
                                        copy1(Square,first);
                                        Put_chessboard(Square, 0, x - 1, y, turn);
                                        if(Equal(Square,first)){
                                             qDebug()<<"000000000000000 94";
                                             qDebug()<<"x="<<x;
                                             qDebug()<<"y="<<y;
                                             for(int i = 1;i<6;i++)
                                                 for(int j=1;j<6;j++)
                                                     qDebug()<<Square[i][j].degree;
                                             bianli(Square);
                                             exit(0);
                                         }
                                        return 1;
                                    }
                                }
                                if (Square[x - 1][y + 1].edge[1] == '1')
                                {
                                    if (Square[x - 2][y + 1].degree >=3&&x>2&&y<5)
                                    {
                                        copy1(Square,first);
                                        Put_chessboard(Square, 0, x - 1, y, turn);
                                        if(Equal(Square,first)){
                                             qDebug()<<"000000000000000 95";
                                             qDebug()<<"x="<<x;
                                             qDebug()<<"y="<<y;
                                             for(int i = 1;i<6;i++)
                                                 for(int j=1;j<6;j++)
                                                     qDebug()<<Square[i][j].degree;
                                             bianli(Square);
                                             exit(0);
                                         }
                                        return 1;
                                    }
                                }
                                if (Square[x - 1][y + 1].edge[2] == '1')
                                {
                                    if (Square[x - 1][y + 2].degree >=3&&x>1&&y<4)
                                    {
                                        copy1(Square,first);
                                        Put_chessboard(Square, 0, x - 1, y, turn);
                                        if(Equal(Square,first)){
                                             qDebug()<<"000000000000000 96";
                                             qDebug()<<"x="<<x;
                                             qDebug()<<"y="<<y;
                                             for(int i = 1;i<6;i++)
                                                 for(int j=1;j<6;j++)
                                                     qDebug()<<Square[i][j].degree;
                                             bianli(Square);
                                             exit(0);
                                         }
                                        return 1;
                                    }
                                }
                            }
                        }
                        if (Square[x][y + 1].edge[2] == '1')
                        {
                            if (Square[x][y + 2].degree >=3&&x>1&&y<4)
                            {
                                copy1(Square,first);
                                Put_chessboard(Square, 1, x - 1, y, turn);
                                if(Equal(Square,first)){
                                     qDebug()<<"000000000000000 97";
                                     qDebug()<<"x="<<x;
                                     qDebug()<<"y="<<y;
                                     for(int i = 1;i<6;i++)
                                         for(int j=1;j<6;j++)
                                             qDebug()<<Square[i][j].degree;
                                     bianli(Square);
                                     exit(0);
                                 }
                                return 1;
                            }
                            if (Square[x][y + 2].degree == 2)
                            {
                                if (Square[x][y + 2].edge[1] == '1')
                                {
                                    if (Square[x - 1][y + 2].degree >=3&&x>1&&y<4)
                                    {
                                        copy1(Square,first);
                                        Put_chessboard(Square, 1, x - 1, y + 1, turn);
                                        if(Equal(Square,first)){
                                             qDebug()<<"000000000000000 98";
                                             qDebug()<<"x="<<x;
                                             qDebug()<<"y="<<y;
                                             for(int i = 1;i<6;i++)
                                                 for(int j=1;j<6;j++)
                                                     qDebug()<<Square[i][j].degree;
                                             bianli(Square);
                                             exit(0);
                                         }
                                        return 1;
                                    }
                                }
                                if (Square[x][y + 2].edge[2] == '1')
                                {
                                    if (Square[x][y + 3].degree >=3&&x>1&&y<3)
                                    {
                                        copy1(Square,first);
                                        Put_chessboard(Square, 1, x - 1, y + 1, turn);
                                        if(Equal(Square,first)){
                                             qDebug()<<"000000000000000 99";
                                             qDebug()<<"x="<<x;
                                             qDebug()<<"y="<<y;
                                             for(int i = 1;i<6;i++)
                                                 for(int j=1;j<6;j++)
                                                     qDebug()<<Square[i][j].degree;
                                             bianli(Square);
                                             exit(0);
                                         }
                                        return 1;
                                    }
                                }
                                if (Square[x][y + 2].edge[3] == '1')
                                {
                                    if (Square[x + 1][y + 2].degree >=3&&x<5&&y<4)
                                    {

                                        copy1(Square,first);
                                        Put_chessboard(Square, 0, x , y + 1, turn);
                                        if(Equal(Square,first)){
                                             qDebug()<<"000000000000000 100";
                                             qDebug()<<"x="<<x;
                                             qDebug()<<"y="<<y;
                                             for(int i = 1;i<6;i++)
                                                 for(int j=1;j<6;j++)
                                                     qDebug()<<Square[i][j].degree;
                                             bianli(Square);
                                             exit(0);
                                         }
                                        return 1;
                                    }
                                }
                            }
                        }
                        if (Square[x][y + 1].edge[3] == '1')
                        {
                            if (Square[x + 1][y + 1].degree >=3&&x>1&&x<5&&y<5)
                            {
                                copy1(Square,first);
                                Put_chessboard(Square, 1, x - 1, y, turn);
                                if(Equal(Square,first)){
                                     qDebug()<<"000000000000000 101";
                                     qDebug()<<"x="<<x;
                                     qDebug()<<"y="<<y;
                                     for(int i = 1;i<6;i++)
                                         for(int j=1;j<6;j++)
                                             qDebug()<<Square[i][j].degree;
                                     bianli(Square);
                                     exit(0);
                                 }
                                return 1;
                            }
                            if (Square[x + 1][y + 1].degree == 2)
                            {
                                if (Square[x + 1][y + 1].edge[0] == '1')
                                {
                                    if (Square[x + 1][y].degree >=3&&y<5)
                                    {
                                        copy1(Square,first);
                                        Put_chessboard(Square, 0, x, y, turn);
                                        if(Equal(Square,first)){
                                             qDebug()<<"000000000000000 102";
                                             qDebug()<<"x="<<x;
                                             qDebug()<<"y="<<y;
                                             for(int i = 1;i<6;i++)
                                                 for(int j=1;j<6;j++)
                                                     qDebug()<<Square[i][j].degree;
                                             bianli(Square);
                                             exit(0);
                                         }
                                        return 1;
                                    }
                                }
                                if (Square[x + 1][y + 1].edge[2] == '1')
                                {
                                    if (Square[x + 1][y + 2].degree >=3&&x<5&&y<4)
                                    {
                                        copy1(Square,first);
                                        Put_chessboard(Square, 0, x, y, turn);
                                        if(Equal(Square,first)){
                                             qDebug()<<"000000000000000 103";
                                             qDebug()<<"x="<<x;
                                             qDebug()<<"y="<<y;
                                             for(int i = 1;i<6;i++)
                                                 for(int j=1;j<6;j++)
                                                     qDebug()<<Square[i][j].degree;
                                             bianli(Square);
                                             exit(0);
                                         }
                                        return 1;
                                    }
                                }
                                if (Square[x + 1][y + 1].edge[3] == '1')
                                {
                                    if (Square[x + 2][y + 1].degree >=3&&x<4&&y<5)
                                    {
                                        copy1(Square,first);
                                        Put_chessboard(Square, 0, x, y, turn);
                                        if(Equal(Square,first)){
                                             qDebug()<<"000000000000000 104";
                                             qDebug()<<"x="<<x;
                                             qDebug()<<"y="<<y;
                                             for(int i = 1;i<6;i++)
                                                 for(int j=1;j<6;j++)
                                                     qDebug()<<Square[i][j].degree;
                                             bianli(Square);
                                             exit(0);
                                         }
                                        return 1;
                                    }
                                }
                            }
                        }
                    }
                }
                if (Square[x][y].edge[3] == '1')						//找到此自由个字的无边方向 若为下边
                {
                    if (Square[x + 1][y].degree == 2)						//临近三个格子自由度都为二 则不是反双交
                    {
                        if (Square[x + 1][y].edge[0] == '1')
                        {
                            if (Square[x + 1][y - 1].degree >=3&&x<5&&y>1)
                            {
                                copy1(Square,first);
                                Put_chessboard(Square, 0, x, y - 1, turn);
                                if(Equal(Square,first)){
                                     qDebug()<<"000000000000000 105";
                                     qDebug()<<"x="<<x;
                                     qDebug()<<"y="<<y;
                                     for(int i = 1;i<6;i++)
                                         for(int j=1;j<6;j++)
                                             qDebug()<<Square[i][j].degree;
                                     bianli(Square);
                                     exit(0);
                                 }
                                return 1;
                            }
                            if (Square[x + 1][y - 1].degree == 2)
                            {
                                if (Square[x + 1][y - 1].edge[0] == '1')
                                {
                                    if (Square[x + 1][y - 2].degree >=3&&x<5&&y>2)
                                    {
                                        copy1(Square,first);
                                        Put_chessboard(Square, 1, x, y - 1, turn);
                                        if(Equal(Square,first)){
                                             qDebug()<<"000000000000000 106";
                                             qDebug()<<"x="<<x;
                                             qDebug()<<"y="<<y;
                                             for(int i = 1;i<6;i++)
                                                 for(int j=1;j<6;j++)
                                                     qDebug()<<Square[i][j].degree;
                                             bianli(Square);
                                             exit(0);
                                         }
                                        return 1;
                                    }
                                }
                                if (Square[x + 1][y - 1].edge[1] == '1')
                                {
                                    if (Square[x][y - 1].degree >=3&&y>1)
                                    {
                                        copy1(Square,first);
                                        Put_chessboard(Square, 1, x, y - 1, turn);
                                        if(Equal(Square,first)){
                                             qDebug()<<"000000000000000 107";
                                             qDebug()<<"x="<<x;
                                             qDebug()<<"y="<<y;
                                             for(int i = 1;i<6;i++)
                                                 for(int j=1;j<6;j++)
                                                     qDebug()<<Square[i][j].degree;
                                             bianli(Square);
                                             exit(0);
                                         }
                                        return 1;
                                    }
                                }
                                if (Square[x + 1][y - 1].edge[3] == '1')
                                {
                                    if (Square[x + 2][y - 1].degree >=3&&x<4&&y>1)
                                    {
                                        copy1(Square,first);
                                        Put_chessboard(Square, 1, x, y - 1, turn);
                                        if(Equal(Square,first)){
                                             qDebug()<<"000000000000000 108";
                                             qDebug()<<"x="<<x;
                                             qDebug()<<"y="<<y;
                                             for(int i = 1;i<6;i++)
                                                 for(int j=1;j<6;j++)
                                                     qDebug()<<Square[i][j].degree;
                                             bianli(Square);
                                             exit(0);
                                         }
                                        return 1;
                                    }
                                }
                            }
                        }
                        if (Square[x + 1][y].edge[2] == '1')
                        {
                            if (Square[x + 1][y + 1].degree >=3&&x<5&&y>1&&y<5)
                            {
                                copy1(Square,first);
                                Put_chessboard(Square, 0, x, y - 1, turn);
                                if(Equal(Square,first)){
                                     qDebug()<<"000000000000000 109";
                                     qDebug()<<"x="<<x;
                                     qDebug()<<"y="<<y;
                                     for(int i = 1;i<6;i++)
                                         for(int j=1;j<6;j++)
                                             qDebug()<<Square[i][j].degree;
                                     bianli(Square);
                                     exit(0);
                                 }
                                return 1;
                            }
                            if (Square[x + 1][y + 1].degree == 2)
                            {
                                if (Square[x + 1][y + 1].edge[1] == '1')
                                {
                                    if (Square[x][y + 1].degree >=3&&y<5)
                                    {
                                        copy1(Square,first);
                                        Put_chessboard(Square, 1, x, y, turn);
                                        if(Equal(Square,first)){
                                             qDebug()<<"000000000000000 110";
                                             qDebug()<<"x="<<x;
                                             qDebug()<<"y="<<y;
                                             for(int i = 1;i<6;i++)
                                                 for(int j=1;j<6;j++)
                                                     qDebug()<<Square[i][j].degree;
                                             bianli(Square);
                                             exit(0);
                                         }
                                        return 1;
                                    }
                                }
                                if (Square[x + 1][y + 1].edge[2] == '1')
                                {
                                    if (Square[x + 1][y + 2].degree >=3&&x<5&&y<4)
                                    {
                                        copy1(Square,first);
                                        Put_chessboard(Square, 1, x, y, turn);
                                        if(Equal(Square,first)){
                                             qDebug()<<"000000000000000 111";
                                             qDebug()<<"x="<<x;
                                             qDebug()<<"y="<<y;
                                             for(int i = 1;i<6;i++)
                                                 for(int j=1;j<6;j++)
                                                     qDebug()<<Square[i][j].degree;
                                             bianli(Square);
                                             exit(0);
                                         }
                                        return 1;
                                    }
                                }
                                if (Square[x + 1][y + 1].edge[3] == '1')
                                {
                                    if (Square[x + 2][y + 1].degree >=3&&x<4&&y<5)
                                    {
                                        copy1(Square,first);
                                        Put_chessboard(Square, 1, x, y, turn);
                                        if(Equal(Square,first)){
                                             qDebug()<<"000000000000000 112";
                                             qDebug()<<"x="<<x;
                                             qDebug()<<"y="<<y;
                                             for(int i = 1;i<6;i++)
                                                 for(int j=1;j<6;j++)
                                                     qDebug()<<Square[i][j].degree;
                                             bianli(Square);
                                             exit(0);
                                         }
                                        return 1;
                                    }
                                }
                            }
                        }
                        if (Square[x + 1][y].edge[3] == '1')
                        {
                            if (Square[x + 2][y].degree>=3&&x<4)
                            {
                                copy1(Square,first);
                                Put_chessboard(Square, 0, x + 1, y - 1, turn);
                                if(Equal(Square,first)){
                                     qDebug()<<"000000000000000 113";
                                     qDebug()<<"x="<<x;
                                     qDebug()<<"y="<<y;
                                     for(int i = 1;i<6;i++)
                                         for(int j=1;j<6;j++)
                                             qDebug()<<Square[i][j].degree;
                                     bianli(Square);
                                     exit(0);
                                 }
                                return 1;
                            }
                            if (Square[x + 2][y].degree == 2)
                            {
                                if (Square[x + 2][y].edge[0] == '1')
                                {
                                    if (Square[x + 2][y - 1].degree >=3&&x<4&&y>1)
                                    {
                                        copy1(Square,first);
                                        Put_chessboard(Square, 1, x + 1, y - 1, turn);
                                        if(Equal(Square,first)){
                                             qDebug()<<"000000000000000 114";
                                             qDebug()<<"x="<<x;
                                             qDebug()<<"y="<<y;
                                             for(int i = 1;i<6;i++)
                                                 for(int j=1;j<6;j++)
                                                     qDebug()<<Square[i][j].degree;
                                             bianli(Square);
                                             exit(0);
                                         }
                                        return 1;
                                    }
                                }
                                if (Square[x + 2][y].edge[2] == '1')
                                {
                                    if (Square[x + 2][y + 1].degree >=3&&x<4&&y<5)
                                    {
                                        copy1(Square,first);
                                        Put_chessboard(Square, 1, x + 1, y , turn);
                                        if(Equal(Square,first)){
                                             qDebug()<<"000000000000000 115";
                                             qDebug()<<"x="<<x;
                                             qDebug()<<"y="<<y;
                                             for(int i = 1;i<6;i++)
                                                 for(int j=1;j<6;j++)
                                                     qDebug()<<Square[i][j].degree;
                                             bianli(Square);
                                             exit(0);
                                         }
                                        return 1;
                                    }
                                }
                                if (Square[x + 2][y].edge[3] == '1')
                                {
                                    if (Square[x + 3][y].degree >=3&&x<3&&y>1)
                                    {
                                        copy1(Square,first);
                                        Put_chessboard(Square, 0, x + 2, y - 1, turn);
                                        if(Equal(Square,first)){
                                             qDebug()<<"000000000000000 116";
                                             qDebug()<<"x="<<x;
                                             qDebug()<<"y="<<y;
                                             for(int i = 1;i<6;i++)
                                                 for(int j=1;j<6;j++)
                                                     qDebug()<<Square[i][j].degree;
                                             bianli(Square);
                                             exit(0);
                                         }
                                        return 1;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    for (i = 1; i <= 5; i++)
    {
        for (j = 1; j <= 5; j++)
        {
            if (DoubleChain(Square, i, j))								//说明x，y 在DoubleChain上，
            {

                if (Square[i][j].edge[0] == '1' && j==1)
                {
                    copy1(Square,first);
                    Put_chessboard(Square, 1, i - 1, j - 1, turn);
                    if(Equal(Square,first)){
                         qDebug()<<"000000000000000 117";
                         for(int i = 1;i<6;i++)
                             for(int j=1;j<6;j++)
                                 qDebug()<<Square[i][j].degree;
                         bianli(Square);
                         exit(0);
                     }
                    return 1;
                }
                if (Square[i][j].edge[0] == '1' && Square[i][j - 1].degree == 2&&j>1)
                {
                    copy1(Square,first);
                    Put_chessboard(Square, 1, i - 1, j - 1, turn);
                    if(Equal(Square,first)){
                         qDebug()<<"000000000000000 118";
                         for(int i = 1;i<6;i++)
                             for(int j=1;j<6;j++)
                                 qDebug()<<Square[i][j].degree;
                         bianli(Square);
                         exit(0);
                     }
                    return 1;
                }

                if (Square[i][j].edge[1] == '1' && i==1)
                {
                    copy1(Square,first);
                    Put_chessboard(Square, 0, i - 1, j - 1, turn);
                    if(Equal(Square,first)){
                         qDebug()<<"000000000000000 119";
                         for(int i = 1;i<6;i++)
                             for(int j=1;j<6;j++)
                                 qDebug()<<Square[i][j].degree;
                         bianli(Square);
                         exit(0);
                     }
                    return 1;
                }
                if (Square[i][j].edge[1] == '1' && Square[i - 1][j].degree == 2&&i>1)
                {
                    copy1(Square,first);
                    Put_chessboard(Square, 0, i - 1, j - 1, turn);
                    if(Equal(Square,first)){
                         qDebug()<<"000000000000000 120";
                         for(int i = 1;i<6;i++)
                             for(int j=1;j<6;j++)
                                 qDebug()<<Square[i][j].degree;
                         bianli(Square);
                         exit(0);
                     }
                    return 1;
                }
                if (Square[i][j].edge[2] == '1' && j==5)
                {
                    copy1(Square,first);
                    Put_chessboard(Square, 1, i - 1, j, turn);
                    if(Equal(Square,first)){
                         qDebug()<<"000000000000000 121";
                         for(int i = 1;i<6;i++)
                             for(int j=1;j<6;j++)
                                 qDebug()<<Square[i][j].degree;
                         bianli(Square);
                         exit(0);
                     }
                    return 1;
                }
                if (Square[i][j].edge[2] == '1' && Square[i][j + 1].degree == 2&&j<5)
                {
                    copy1(Square,first);
                    Put_chessboard(Square, 1, i - 1, j, turn);
                    if(Equal(Square,first)){
                         qDebug()<<"000000000000000 122";
                         for(int i = 1;i<6;i++)
                             for(int j=1;j<6;j++)
                                 qDebug()<<Square[i][j].degree;
                         bianli(Square);
                         exit(0);
                     }
                    return 1;
                }
                if (Square[i][j].edge[3] == '1' && i==5)
                {
                    copy1(Square,first);
                    Put_chessboard(Square, 0, i, j - 1, turn);
                    if(Equal(Square,first)){
                         qDebug()<<"000000000000000 123";
                         for(int i = 1;i<6;i++)
                             for(int j=1;j<6;j++)
                                 qDebug()<<Square[i][j].degree;
                         bianli(Square);
                         exit(0);
                     }
                    return 1;
                }
                if (Square[i][j].edge[3] == '1' && Square[i + 1][j].degree == 2&&i<5)
                {
                    copy1(Square,first);
                    Put_chessboard(Square, 0, i, j - 1, turn);
                    if(Equal(Square,first)){
                         qDebug()<<"000000000000000 124";
                         for(int i = 1;i<6;i++)
                             for(int j=1;j<6;j++)
                                 qDebug()<<Square[i][j].degree;
                         bianli(Square);
                         exit(0);
                     }
                    return 1;
                }
            }
        }
    }

    return 0;
}

int AI::Chain_lenth(Situation Square[6][6], int i, int j)  //链长度
{

    int m, k;
    int lenth = 1;
    for (k = 0; k<4; k++)
    {
        if (Square[i][j].edge[k] == '1')
        {
            m = k;
            break;
        }
    }

    while (1)
    {

        if (m == 0)
            j = j - 1;
        if (m == 1)
            i = i - 1;
        if (m == 2)
            j = j + 1;
        if (m == 3)
            i = i + 1;
        if (i == 0 || j == 0 || i == 6 || j == 6)
        {
            chain_type = 0;
            break;
        }
        if (Square[i][j].degree == 3 || Square[i][j].degree == 4)
        {
            chain_type = 0;
            break;
        }
        if (Square[i][j].degree == 1)
        {
            chain_type = 1;
            break;
        }
        if (m == 0)
        {
            for (k = 0; k<4; k++)
            {
                if (Square[i][j].edge[k] == '1' && k != 2)
                {
                    m = k;
                    break;
                }
            }
            lenth++;
            continue;
        }
        if (m == 1)
        {
            for (k = 0; k<4; k++)
            {
                if (Square[i][j].edge[k] == '1' && k != 3)
                {
                    m = k;
                    break;
                }
            }
            lenth++;
            continue;
        }
        if (m == 2)
        {
            for (k = 0; k<4; k++)
            {
                if (Square[i][j].edge[k] == '1' && k != 0)
                {
                    m = k;
                    break;
                }

            }
            lenth++;
            continue;
        }
        if (m == 3)
        {
            for (k = 0; k<4; k++)
            {
                if (Square[i][j].edge[k] == '1' && k != 1)
                {
                    m = k;
                    break;
                }
            }
            lenth++;
            continue;
        }
    }
    if (chain_type == 1)
        lenth++;


    return lenth;
}

//吃链
//当前吃链的人是
int AI::Eat_Chain(Situation Square[6][6], int i, int j, int len, int turn)
{
    int s=0;
    for(int i=1;i<6;i++)
    {
        for(int j=1;j<6;j++)
        {
            if(Square[i][j].ower!='A'&&Square[i][j].ower!='B')
                s++;
        }
    }
    if(s==len)
    {
        Eat_all_box(Square,turn);
        return 0;
    }
    int k, m = -1, num;
    if (len == 1)
    {
        Eat_all_box(Square, turn);
        return 0;
    }
//自己家的，判断连续吃链标志
    if (chain_type == 1)                            //环链的造双交
    {

        for (num = 0; num<len - 4; num++)
        {
            for (k = 0; k<4; k++)
            {
                if (Square[i][j].edge[k] == '1')
                {
                    if (k == 0)  Put_chessboard(Square, 1, i - 1, j - 1, turn);
                    if (k == 1)  Put_chessboard(Square, 0, i - 1, j - 1, turn);
                    if (k == 2)  Put_chessboard(Square, 1, i - 1, j, turn);
                    if (k == 3)  Put_chessboard(Square, 0, i, j - 1, turn);
                    m = k;
                    break;
                }
            }

            if (m == 0)
                j = j - 1;
            if (m == 1)
                i = i - 1;
            if (m == 2)
                j = j + 1;
            if (m == 3)
                i = i + 1;
            if(i==0||i==6||j==0||j==6)
            {return 1;}
        }
        for (k = 0; k<4; k++)
        {
            if (Square[i][j].edge[k] == '1')
            {
                m = k;//这步不走z
                break;
            }
        }
        if (m == 0)
        {
            for (k = 0; k<4; k++)
                if (Square[i][j - 1].edge[k] == '1' && k != 2)
                {
                    if (k == 0)  Put_chessboard(Square, 1, i - 1, j - 2, turn);
                    if (k == 1)  Put_chessboard(Square, 0, i - 1, j - 2, turn);
                    if (k == 3)  Put_chessboard(Square, 0, i, j - 2, turn);
                    break;
                }
        }

        if (m == 1)
        {
            for (k = 0; k<4; k++)
                if (Square[i - 1][j].edge[k] == '1' && k != 3)
                {
                    if (k == 0)  Put_chessboard(Square, 1, i - 2, j - 1, turn);
                    if (k == 1)  Put_chessboard(Square, 0, i - 2, j - 1, turn);
                    if (k == 2)  Put_chessboard(Square, 1, i - 2, j, turn);
                    break;
                }
        }

        if (m == 2)
        {
            for (k = 0; k<4; k++)
                if (Square[i][j + 1].edge[k] == '1' && k != 0)
                {
                    if (k == 1)  Put_chessboard(Square, 0, i - 1, j, turn);
                    if (k == 2)  Put_chessboard(Square, 1, i - 1, j + 1, turn);
                    if (k == 3)  Put_chessboard(Square, 0, i, j, turn);
                    break;
                }
        }

        if (m == 3)
        {
            for (k = 0; k<4; k++)
                if (Square[i + 1][j].edge[k] == '1' && k != 1)
                {
                    if (k == 0)  Put_chessboard(Square, 1, i, j - 1, turn);
                    if (k == 2)  Put_chessboard(Square, 1, i, j, turn);
                    if (k == 3)  Put_chessboard(Square, 0, i + 1, j - 1, turn);
                    break;
                }
        }

    }
    else                                                 //这是单链的造双交
    {

        for (num = 0; num<len - 2; num++)              //把链吃的只剩两格
        {
            for (k = 0; k<4; k++)
            {
                if (Square[i][j].edge[k] == '1' == 1)
                {
                    if (k == 0)  Put_chessboard(Square, 1, i - 1, j - 1, turn);
                    if (k == 1)  Put_chessboard(Square, 0, i - 1, j - 1, turn);
                    if (k == 2)  Put_chessboard(Square, 1, i - 1, j, turn);
                    if (k == 3)  Put_chessboard(Square, 0, i, j - 1, turn);
                    m = k;
                    break;
                }
            }
            if (m == 0)
                j = j - 1;
            if (m == 1)
                i = i - 1;
            if (m == 2)
                j = j + 1;
            if (m == 3)
                i = i + 1;
        }
        for (k = 0; k<4; k++)                              //搜索倒数第二格的那边没吃
        {
            if (Square[i][j].edge[k] == '1')
            {
                m = k;
                break;
            }
        }
        if (m == 0)
        {
            for (k = 0; k<4; k++)
                if (Square[i][j - 1].edge[k] == '1' && k != 2)
                {
                    if (k == 0)  Put_chessboard(Square, 1, i - 1, j - 2, turn);
                    if (k == 1)  Put_chessboard(Square, 0, i - 1, j - 2, turn);
                    if (k == 3)  Put_chessboard(Square, 0, i, j - 2, turn);
                    break;
                }
        }

        if (m == 1)
        {
            for (k = 0; k<4; k++)
                if (Square[i - 1][j].edge[k] == '1' && k != 3)
                {
                    if (k == 0)  Put_chessboard(Square, 1, i - 2, j - 1, turn);
                    if (k == 1)  Put_chessboard(Square, 0, i - 2, j - 1, turn);
                    if (k == 2)  Put_chessboard(Square, 1, i - 2, j, turn);
                    break;
                }
        }

        if (m == 2)
        {
            for (k = 0; k<4; k++)
                if (Square[i][j + 1].edge[k] == '1' && k != 0)
                {
                    if (k == 1)  Put_chessboard(Square, 0, i - 1, j, turn);
                    if (k == 2)  Put_chessboard(Square, 1, i - 1, j + 1, turn);
                    if (k == 3)  Put_chessboard(Square, 0, i, j, turn);
                    break;
                }
        }

        if (m == 3)
        {
            for (k = 0; k<4; k++)
                if (Square[i + 1][j].edge[k] == '1' && k != 1)
                {
                    if (k == 0)  Put_chessboard(Square, 1, i, j - 1, turn);
                    if (k == 2)  Put_chessboard(Square, 1, i, j, turn);
                    if (k == 3)  Put_chessboard(Square, 0, i + 1, j - 1, turn);
                    break;
                }
        }
    }
    return 1;
}

void AI::deleteFree2(int x,int y)
{
    for(int i = 0;i<25;i++){
        if(maybeChain[i].x==x&&maybeChain[i].y==y){
            maybeChain[i].x=-1;
            maybeChain[i].y=-1;
            break;
        }
    }
}

void AI::deleteFree2_Cicle(int x,int y)
{
    for(int i = 0;i<25;i++){
        if(maybeCircle[i].x==x&&maybeCircle[i].y==y){
            maybeCircle[i].x=-1;
            maybeCircle[i].y=-1;
            break;
        }
    }
}

bool AI::CheckCircle(int x, int y){
    for(int i=0;i<25;i++){
        if(maybeCircle[i].x==x&&maybeCircle[i].y==y){
            return true;
        }
    }

    return false;
}

int AI::Find_Circle(Situation Square[6][6], int i, int j){

    int lenth = 1,m=0;
    for (int k = 0; k<4; k++)
    {
        if (Square[i][j].edge[k] == '1')
        {
            m = k;
            break;
        }
    }

    while(1)
    {

        if (m == 0)
            j = j - 1;
        if (m == 1)
            i = i - 1;
        if (m == 2)
            j = j + 1;
        if (m == 3)
            i = i + 1;

        if(!CheckCircle(i,j)) break;

        if (m == 0)
        {

            for ( int k = 0; k<4; k++)
            {
                if (Square[i][j].edge[k] == '1' && k != 2)
                {
                    m = k;
                    deleteFree2_Cicle(i,j);
                    break;
                }
            }
            lenth++;

            continue;
        }
        if (m == 1){
            for (int k = 0; k<4; k++)
            {
                if (Square[i][j].edge[k] == '1' && k != 3)
                {
                    m = k;
                    deleteFree2_Cicle(i,j);
                    break;
                }
            }
            lenth++;
            continue;
        }

        if (m == 2)
        {
            for (int k = 0; k<4; k++)
            {
                if (Square[i][j].edge[k] == '1' && k != 0)
                {

                    m = k;
                    deleteFree2_Cicle(i,j);
                    break;
                }

            }
            lenth++;
            continue;
        }
        if (m == 3)
        {

            for (int k = 0; k<4; k++)
            {
                if (Square[i][j].edge[k] == '1' && k != 1)
                {

                    m = k;
                    deleteFree2_Cicle(i,j);
                    break;
                }
            }
            lenth++;
            continue;
        }
    }
    return lenth;
}

int AI::Chain_lenth2(Situation Square[6][6], int i, int j)  //链长度
{

    int m1=-1,m2=-1, k,i1,j1,i2,j2,m;
    int lenth = 1;
    for (k = 0; k<4; k++)
    {
        if (Square[i][j].edge[k] == '1')
        {
            if(m1==-1)
            m1 = k;
            else
            m2 = k;
        }
    }
    if(m1==0){i1=i,j1=j-1;}
    if(m1==1){i1=i-1;j1=j;}
    if(m1==2){i1=i,j1=j+1;}
    if(m1==3){i1=i+1;j1=j;}
    if(m2==0){i2=i;j2=j-1;}
    if(m2==1){i2=i-1;j2=j;}
    if(m2==2){i2=i;j2=j+1;}
    if(m2==3){i2=i+1;j2=j;}

    if(Square[i1][j1].degree == 2)m=m1;
    else
        m=m2;

    while (1)
    {

        if (m == 0)
            j = j - 1;
        if (m == 1)
            i = i - 1;
        if (m == 2)
            j = j + 1;
        if (m == 3)
            i = i + 1;
        if (i == 0 || j == 0 || i == 6 || j == 6)
        {
            chain_type = 0;
            break;
        }
        if (Square[i][j].degree == 3 || Square[i][j].degree == 4)
        {
            chain_type = 0;
            break;
        }
        if (Square[i][j].degree == 1)
        {
            chain_type = 1;
            break;
        }
        if (m == 0)
        {
            for (k = 0; k<4; k++)
            {
                if (Square[i][j].edge[k] == '1' && k != 2)
                {
                    m = k;
                    deleteFree2(i,j);
                    break;
                }
            }
            lenth++;
            continue;
        }
        if (m == 1)
        {
            for (k = 0; k<4; k++)
            {
                if (Square[i][j].edge[k] == '1' && k != 3)
                {
                    m = k;
                    deleteFree2(i,j);
                    break;
                }
            }
            lenth++;
            continue;
        }
        if (m == 2)
        {
            for (k = 0; k<4; k++)
            {
                if (Square[i][j].edge[k] == '1' && k != 0)
                {
                    m = k;
                    deleteFree2(i,j);
                    break;
                }

            }
            lenth++;
            continue;
        }
        if (m == 3)
        {
            for (k = 0; k<4; k++)
            {
                if (Square[i][j].edge[k] == '1' && k != 1)
                {
                    m = k;
                    deleteFree2(i,j);
                    break;
                }
            }
            lenth++;
            continue;
        }
    }
    if (chain_type == 1)
        lenth++;


    return lenth;
}

void AI::initialMaybe(){//初始化MaybeChain
    for(int i=0;i<25;i++){
        if(maybeChain[i].x!=-1&&maybeChain[i].y!=-1){
            maybeChain[i].x = -1;
            maybeChain[i].y = -1;
        }
        if(maybeCircle[i].x!=-1&&maybeCircle[i].y!=-1){
            maybeCircle[i].x = -1;
            maybeCircle[i].y = -1;
        }
    }
}

void AI::None_Antdoublecorse2(Situation Square[6][6], int turn)		//非以自由度为一开头链(找长链个数函数)								//没有反双交是要全吃
{
    initialMaybe();

    chainNum = 0;
    circlenum = 0;
    longestChainLength = 0;
    int i, j,i1,j1,i2,j2, flag = 0, num = 0,num1=0, len1, len2,m1=-1,m2=-1;
    for (i = 1, num = 0; i <= 5; i++)
    {
        for (j = 1; j <= 5; j++)
        {
            m1=-1;
            if (Square[i][j].degree == 2)//自由度为2的格子
            {
                for(int k = 0;k<4;k++){
                    if(Square[i][j].edge[k] == '1'){
                        if(m1==-1)
                            m1=k;
                        else
                            m2=k;
                    }
                }

                if(m1==0){i1=i,j1=j-1;}
                if(m1==1){i1=i-1;j1=j;}
                if(m1==2){i1=i,j1=j+1;}
                if(m1==3){i1=i+1;j1=j;}
                if(m2==0){i2=i;j2=j-1;}
                if(m2==1){i2=i-1;j2=j;}
                if(m2==2){i2=i;j2=j+1;}
                if(m2==3){i2=i+1;j2=j;}

                if((Square[i1][j1].degree == 2&&Square[i2][j2].degree != 2)||(Square[i1][j1].degree != 2&&Square[i2][j2].degree == 2)){
                maybeChain[num].x = i;
                maybeChain[num].y = j;
                num++;
               }
                if(Square[i1][j1].degree == 2&&Square[i2][j2].degree == 2){

                maybeCircle[num1].x = i;
                maybeCircle[num1].y = j;
                num1++;
               }
            }
        }
    }
    for(int z = 0;z<num;z++){
        if(maybeChain[z].x!=-1&&maybeChain[z].y!=-1){
            int length = Chain_lenth2(Square, maybeChain[z].x, maybeChain[z].y);
            if(length>longestChainLength&&length>2){longestChainLength = length;}
            chainNum++;
        }
    }

    for(int z = 0;z<num1;z++){
        if(maybeCircle[z].x!=-1&&maybeCircle[z].y!=-1){
            int length = Find_Circle(Square, maybeCircle[z].x, maybeCircle[z].y);
            if(length>3)
            circlenum++;
        }
    }


}

bool AI::Equal(Situation first[6][6],Situation next[6][6]){
    for(int i=1;i<6;i++)
        for(int j=1;j<6;j++)
            for(int k=0;k<4;k++){
                if(first[i][j].edge[k]!=next[i][j].edge[k]){
                    return false;
                }
            }
    return true;
}

void AI:: None_Antdoublecorse(Situation Square[6][6], int turn)										//没有反双交是要全吃
{   head:

    if(countblack+countwhite>=25||edgeCount>=60){
        qDebug()<<"end！！！！！！！！！！！！；";
        return;
    }
    Situation to[6][6];
    int i, j, flag = 0, num = 0, x1 = 0, x2 = 0, y1 = 0, y2 = 0, len1, len2;
    for (i = 1; i <= 5; i++)
    {
        for (j = 1; j <= 5; j++)
        {


                qDebug()<<Square[i][j].degree;
                if (Square[i][j].degree == 1)//自由度为一的 z
                {
                num++;
                if (x1 == 0)
                {
                    x1 = i; y1 = j;
                }
                else
                {
                    x2 = i; y2 = j;
                }
            }
        }
    }
    qDebug()<<"======================================="<<num;
    if (num==2)
    {
        len1 = Chain_lenth(factcheer, x1, y1);
        len2= Chain_lenth(factcheer, x2, y2);
        qDebug()<<"len1="<<len1<<"len2="<<len2;
        if(len1==1&&len2==1){
            for(int k=0;k<4;k++){
                if(factcheer[x1][y1].edge[k]=='1'){
                    factcheer[x1][y1].edge[k]='*';
                    factcheer[x1][y1].degree--;
                    mutualoccupy1(factcheer, x1,y1,k);
                    getchecksline(x1,y1,k);
                    chaincount--;
                }
                if(factcheer[x2][y2].edge[k]=='1'){
                    factcheer[x2][y2].edge[k]='*';
                    factcheer[x2][y2].degree--;
                    mutualoccupy1(factcheer, x2,y2,k);
                    getchecksline(x2,y2,k);
                    chaincount--;
                }
            }
            Final_Occupy(factcheer,turn);
            return;
        }
        if(len1==4&&len2==4){
            None_Antdoublecorse2(factcheer,turn);
            qDebug()<<"zzzzzzzzzzzzzzzzzzzzzzz"<<circlenum;
                if(circlenum==1){
                    if(countwhite+4<13){
                        qDebug()<<"huanhuanhaun";
                        goto huan;
                    }else{
                        Eat_a_chain(factcheer,x1,y1,len1,turn);
                        Final_Occupy(factcheer,turn);
                        return;
                    }
                }else if(circlenum>1){
                    Eat_a_chain(factcheer,x1,y1,len1,turn);
                    Final_Occupy(factcheer,turn);
                    return;
                }else if(circlenum==0){
                    if(countwhite+4<13){
                        qDebug()<<"huanhuanhaun";
                        goto huan;
                    }else{
                        Eat_a_chain(factcheer,x1,y1,len1,turn);
                        Final_Occupy(factcheer,turn);
                        return;
                    }
                }



        }
        if(len1==len2&&len1==2){
            Eat_a_chain(factcheer,x1,y1,len1,turn);
            int count = find_free1(factcheer);
            if(count==0){
                qDebug()<<"9999999999999999999999";
                Final_Occupy(factcheer,1);
                return;
            }else{
                goto head;
            }
        }
        if(len1==len2&&len1>=5){
            if(countwhite+6<13){
                Eat_a_chain(factcheer,x1,y1,len1-4,turn);
                goto head;
            }else{
                Eat_a_chain(factcheer,x1,y1,len1,turn);
                Final_Occupy(factcheer,turn);
                return;
            }

        }
        if(len1!=len2){
            if(len1>len2){
                 Eat_a_chain(factcheer, x2, y2, len2, turn);
                 if(len1==2){

                  huan:
                    for(int k=0;k<4;k++){
                        if(factcheer[x1][y1].edge[k]=='1'&&k==0){
                            for(int z=0;z<4;z++){
                                copy1(factcheer,to);
                                if(to[x1][y1-1].edge[z]=='1'){
                                    to[x1][y1-1].edge[z]='*';
                                    to[x1][y1-1].degree--;
                                    mutualoccupy1(to, x1,y1-1,z);
                                    if(to[x1][y1-1].degree==1&&to[x1][y1].degree==1){
                                        factcheer[x1][y1-1].edge[z]='*';
                                        factcheer[x1][y1-1].degree--;
                                        mutualoccupy1(factcheer, x1,y1-1,z);
                                        getchecksline(x1,y1-1,z);
                                        chaincount--;
                                    }
                                }
                            }

                        }else if(factcheer[x1][y1].edge[k]=='1'&&k==1){
                            qDebug()<<"aaaaaaaaaa";
                            for(int z=0;z<4;z++){
                                copy1(factcheer,to);
                                if(to[x1-1][y1].edge[z]=='1'){
                                    to[x1-1][y1].edge[z]='*';
                                    to[x1-1][y1].degree--;
                                    mutualoccupy1(to, x1-1,y1,z);
                                    if(to[x1-1][y1].degree==1&&to[x1][y1].degree==1){
                                        factcheer[x1-1][y1].edge[z]='*';
                                        factcheer[x1-1][y1].degree--;
                                        mutualoccupy1(factcheer, x1-1,y1,z);
                                        getchecksline(x1-1,y1,z);
                                        chaincount--;
                                    }
                                }
                            }

                        }else if(factcheer[x1][y1].edge[k]=='1'&&k==2){
                            for(int z=0;z<4;z++){
                                copy1(factcheer,to);
                                if(to[x1][y1+1].edge[z]=='1'){
                                    to[x1][y1+1].edge[z]='*';
                                    to[x1][y1+1].degree--;
                                    mutualoccupy1(to, x1,y1+1,z);
                                    if(to[x1][y1+1].degree==1&&to[x1][y1].degree==1){
                                        factcheer[x1][y1+1].edge[z]='*';
                                        factcheer[x1][y1+1].degree--;
                                        mutualoccupy1(factcheer, x1,y1+1,z);
                                        getchecksline(x1,y1+1,z);
                                        chaincount--;
                                    }
                                }
                            }

                        }else if(factcheer[x1][y1].edge[k]=='1'&&k==3){
                            for(int z=0;z<4;z++){
                                copy1(factcheer,to);
                                if(to[x1+1][y1].edge[z]=='1'){
                                    to[x1+1][y1].edge[z]='*';
                                    to[x1+1][y1].degree--;
                                    mutualoccupy1(to, x1+1,y1,z);
                                    if(to[x1+1][y1].degree==1&&to[x1][y1].degree==1){
                                        factcheer[x1+1][y1].edge[z]='*';
                                        factcheer[x1+1][y1].degree--;
                                        mutualoccupy1(factcheer, x1+1,y1,z);
                                        getchecksline(x1+1,y1,z);
                                        chaincount--;
                                    }
                                }
                            }

                        }
                    }
                    return;
                 }else if(len1>2){
                     if(countwhite+len1>13){

                         Eat_a_chain(factcheer, x1, y1, len1, turn);
                         Final_Occupy(factcheer,turn);
                         return;
                     }else{
                         Eat_Chain(factcheer, x1, y1, len1, turn);
                     }

                 }
            }else{
                 Eat_a_chain(factcheer, x1, y1, len1, turn);
                 if(len2==2){
                     for(int k=0;k<4;k++){
                         if(factcheer[x2][y2].edge[k]=='1'&&k==0){
                             for(int z=0;z<4;z++){
                                 copy1(factcheer,to);
                                 if(to[x2][y2-1].edge[z]=='1'){
                                     to[x2][y2-1].edge[z]='*';
                                     to[x2][y2-1].degree--;
                                     mutualoccupy1(to, x2,y2-1,z);
                                     if(to[x2][y2-1].degree==1&&to[x2][y2].degree==1){
                                         factcheer[x2][y2-1].edge[z]='*';
                                         factcheer[x2][y2-1].degree--;
                                         mutualoccupy1(factcheer, x2,y2-1,z);
                                         getchecksline(x2,y2-1,z);
                                         chaincount--;
                                     }
                                 }
                             }

                         }else if(factcheer[x2][y2].edge[k]=='1'&&k==1){
                             for(int z=0;z<4;z++){
                                 copy1(factcheer,to);
                                 if(to[x2-1][y2].edge[z]=='1'){
                                     to[x2-1][y2].edge[z]='*';
                                     to[x2-1][y2].degree--;
                                     mutualoccupy1(to, x2-1,y2,z);
                                     if(to[x2-1][y2].degree==1&&to[x2][y2].degree==1){
                                         factcheer[x2-1][y2].edge[z]='*';
                                         factcheer[x2-1][y2].degree--;
                                         mutualoccupy1(factcheer, x2-1,y2,z);
                                         getchecksline(x2-1,y2,z);
                                         chaincount--;
                                     }
                                 }
                             }

                         }else if(factcheer[x2][y2].edge[k]=='1'&&k==2){
                             for(int z=0;z<4;z++){
                                 copy1(factcheer,to);
                                 if(to[x2][y2+1].edge[z]=='1'){
                                     to[x2][y2+1].edge[z]='*';
                                     to[x2][y2+1].degree--;
                                     mutualoccupy1(to, x2,y2+1,z);
                                     if(to[x2][y2+1].degree==1&&to[x2][y2].degree==1){
                                         factcheer[x2][y2+1].edge[z]='*';
                                         factcheer[x2-1][y2+1].degree--;
                                         mutualoccupy1(factcheer, x2,y2+1,z);
                                         getchecksline(x2,y2+1,z);
                                         chaincount--;
                                     }
                                 }
                             }

                         }else if(factcheer[x2][y2].edge[k]=='1'&&k==3){
                             for(int z=0;z<4;z++){
                                 copy1(factcheer,to);
                                 if(to[x2+1][y2].edge[z]=='1'){
                                     to[x2+1][y2].edge[z]='*';
                                     to[x2+1][y2].degree--;
                                     mutualoccupy1(to, x2+1,y2,z);
                                     if(to[x2+1][y2].degree==1&&to[x2][y2].degree==1){
                                         factcheer[x2+1][y2].edge[z]='*';
                                         factcheer[x2+1][y2].degree--;
                                         mutualoccupy1(factcheer, x2+1,y2,z);
                                         getchecksline(x2+1,y2,z);
                                         chaincount--;
                                     }
                                 }
                             }

                         }
                     }
                     return;
                  }else if(len2>2){

                     if(countwhite+len1>13){
                         Eat_a_chain(factcheer, x2, y2, len2, turn);
                         Final_Occupy(factcheer,turn);
                         return;
                     }else{
                         Eat_Chain(factcheer, x2, y2, len2, turn);
                     }


                 }
            }

        }


    }
    else if (num == 1)
    {

        qDebug()<<"num1111="<<num;
        len1 = Chain_lenth(Square, x1, y1);
        qDebug()<<"len1="<<len1;
        if(len1==1){
            qDebug()<<"afasdfvaegvaqerfgewf";
            for(int k=0;k<4;k++){
                if(Square[x1][y1].edge[k]=='1'){
                    Square[x1][y1].edge[k]='*';
                    Square[x1][y1].degree--;
                    mutualoccupy1(Square, x1,y1,k);
                    qDebug()<<"启动最后一次CHECK";
                    getchecksline(x1,y1,k);
                    qDebug()<<"完成最后一次CHECK";
                    chaincount--;
                    qDebug()<<"启动最后一次OCCU";
                    Final_Occupy(Square,turn);
                    qDebug()<<"完成afasdfvaegvaqerfgewf";
                    return;
                    qDebug()<<"完2成afasdfvaegvaqerfgewf";
                }
            }
            qDebug()<<"完成afasdfvaegvaqerfgewf";
        }else if(len1==2){
            huanshou:
            if(countblack+countwhite==23){
                Eat_all_box(Square,turn);
            }
            qDebug()<<"88888888asgasdgfasdfafsdgaG88888888888888888888";
            for(int k=0;k<4;k++){
                if(Square[x1][y1].edge[k]=='1'&&k==0){
                    qDebug()<<"aaaaaaaaaaaaaaa";
                    for(int z=0;z<4;z++){
                        copy1(Square,to);
                        if(to[x1][y1-1].edge[z]=='1'){
                            to[x1][y1-1].edge[z]='*';
                            to[x1][y1-1].degree--;
                            mutualoccupy1(to, x1,y1-1,z);
                            if(to[x1][y1-1].degree==1&&to[x1][y1].degree==1){
                                Square[x1][y1-1].edge[z]='*';
                                Square[y1][x1-1].degree--;
                                mutualoccupy1(Square, x1,y1-1,z);
                                getchecksline(x1,y1-1,z);
                                chaincount--;
                                return;
                            }
                        }
                    }

                }else if(Square[x1][y1].edge[k]=='1'&&k==1){
                    qDebug()<<"aaaaaaaaaaaaaaa";
                    for(int z=0;z<4;z++){
                        copy1(Square,to);
                        if(to[x1-1][y1].edge[z]=='1'){
                            to[x1-1][y1].edge[z]='*';
                            to[x1-1][y1].degree--;
                            mutualoccupy1(to, x1-1,y1,z);
                            if(to[x1-1][y1].degree==1&&to[x1][y1].degree==1){
                                Square[x1-1][y1].edge[z]='*';
                                Square[x1-1][y1].degree--;
                                mutualoccupy1(Square, x1-1,y1,z);
                                getchecksline(x1-1,y1,z);
                                chaincount--;
                                return;
                            }
                        }
                    }

                }else if(Square[x1][y1].edge[k]=='1'&&k==2){
                    qDebug()<<"aaaaaaaaaaaaaaa";
                    for(int z=0;z<4;z++){
                        copy1(Square,to);
                        if(to[x1][y1+1].edge[z]=='1'){
                            to[x1][y1+1].edge[z]='*';
                            to[x1][y1+1].degree--;
                            mutualoccupy1(to, x1,y1+1,z);
                            if(to[x1][y1+1].degree==1&&to[x1][y1].degree==1){
                                Square[x1][y1+1].edge[z]='*';
                                Square[x1-1][y1+1].degree--;
                                mutualoccupy1(Square, x1,y1+1,z);
                                getchecksline(x1,y1+1,z);
                                chaincount--;
                                return;
                            }
                        }
                    }

                }else if(Square[x1][y1].edge[k]=='1'&&k==3){
                    qDebug()<<"aaaaaaaaaaaaaaa";
                    for(int z=0;z<4;z++){
                        copy1(Square,to);
                        if(to[x1+1][y1].edge[z]=='1'){
                            to[x1+1][y1].edge[z]='*';
                            to[x1+1][y1].degree--;
                            mutualoccupy1(to, x1+1,y1,z);
                            if(to[x1+1][y1].degree==1&&to[x1][y1].degree==1){
                                Square[x1+1][y1].edge[z]='*';
                                Square[x1+1][y1].degree--;
                                mutualoccupy1(Square, x1+1,y1,z);
                                getchecksline(x1+1,y1,z);
                                chaincount--;return;
                            }
                        }
                    }

                }
            }
         }else if(len1>2){
            int count =0;
            int eat = 0;
            while(eat==0||eat>count){
                count = eat;
                for(int i=1;i<6;i++)
                    for(int j=1;j<6;j++){
                        if(Square[i][j].degree==1){
                            int length = Chain_lenth(Square, i, j);
                            if(length>2){
                                for(int k=0;k<4;k++){
                                    if(Square[i][j].edge[k]=='1'){
                                        Square[i][j].edge[k]='*';
                                        Square[i][j].degree--;
                                        mutualoccupy1(Square, i,j,k);
                                        getchecksline(i,j,k);
                                        chaincount--;
                                        eat++;
                                    }
                                }
                            }else if(length==2){
                                qDebug()<<"准备进入最终"<<countwhite;
                                 qDebug()<<"边的数目"<<edgeCount<<" 总的占领的格子数目"<<countwhite+countblack;
                                if(countwhite+2>13){
                                    for(int k=0;k<4;k++){
                                        if(Square[i][j].edge[k]=='1'){
                                            Square[i][j].edge[k]='*';
                                            Square[i][j].degree--;
                                            mutualoccupy1(Square, i,j,k);
                                            getchecksline(i,j,k);
                                            chaincount--;
                                            eat++;
                                        }
                                    }
                                    qDebug()<<"aaaaaaaaaaa";
                                    Final_Occupy(factcheer,turn);
                                    return;

                                }else{
                                    x1 = i;
                                    y1 = j;
                                    goto huanshou;
                                }


                            }

                        }
                    }
            }


        }


    }else if(num==0){
        qDebug()<<"eeeeeeeeeeeeeeeeeeeeeeeeee";
        Final_Occupy(factcheer,turn);
    }
    else{
        len1 = Chain_lenth(Square, x1, y1);
        len2 = Chain_lenth(Square, x2, y2);
        if(len1>len2){
            Eat_a_chain(factcheer,x1,y1,len1,turn);
        }else{
            Eat_a_chain(factcheer,x2,y2,len2,turn);
        }
        goto head;
    }
}
void AI::Min_Give_Box(Situation Square[6][6], int turn)												//自杀
{
    for (int x = 1; x < 6; x++)
        for (int y = 1; y < 6; y++)
            for (int k = 0; k < 4; k++)
            {
               if(Square[x][y].degree==2)
                 if(Square[x][y].edge[k]=='1')
                  {
                    if(turn==1){
                        Square[x][y].edge[k]='*';
                        getchecksline(x,y,k);
                        chaincount--;
                        Square[x][y].degree--;
                        mutualoccupy1(Square, x,y,k);
                        return;
                    }

                  }
            }
    return;
}

void AI::Eat_a_chain(Situation Square[6][6], int i, int j, int len, int turn)
{
    flag = 1;
    int num, k, m;
    for (num = 0; num<len; num++)
    {
        for (k = 0; k<4; k++)
        {
            if (Square[i][j].edge[k] == '1')
            {
                if (k == 0)  Put_chessboard(Square, 1, i - 1, j - 1, turn);
                if (k == 1)  Put_chessboard(Square, 0, i - 1, j - 1, turn);
                if (k == 2)  Put_chessboard(Square, 1, i - 1, j, turn);
                if (k == 3)  Put_chessboard(Square, 0, i, j - 1, turn);
                m = k;
                break;
            }
        }
        if (m == 0)
            j = j - 1;
        if (m == 1)
            i = i - 1;
        if (m == 2)
            j = j + 1;
        if (m == 3)
            i = i + 1;
        if(i==0||i==6||j==0||j==6)
        {
            flag = 0;
            return;
        }

    }
flag = 0;

}

// eat all c 型
void AI::Eat_all_box(Situation Square[6][6], int turn)
{

chi2: turn = 1;
   for (int i = 1; i < 6; i++)
     for (int j = 1; j < 6; j++)
         for (int k = 0; k < 4; k++) {

             if (Dead1(Square, i, j, k, turn))
             {
                goto chi2;
             }
         }



}

void AI::Odd_Number_Doublecorse(Situation Square[6][6], int turn)									//反双交个数为奇数时
{
                                                                //吃掉所有的能吃的格
    Give_Boxes_Odd(Square, turn);											//奇数时的让子(拆双交)

}

void AI::Oven_Number_Doublecorse(Situation Square[6][6],int turn)									//反双交个数为偶数时的
{
    //偶数时先吃点所有能吃的子
    Give_Boxes_Oven(Square, turn);
    //偶数时的让子策略（不拆双交）
}

int AI::wulian(Situation Square[6][6])
{
    int lian = 0;
    for (int x = 1; x < 6; x++)
        for (int y = 1; y < 6; y++)
        {
            if (Square[x][y].degree == 1)
                lian++;
        }
    return lian;
}

void AI::Final_Occupy(Situation Square[6][6], int turn)												//最后收官总函数
{
    qDebug()<<"进入最终占边,边的数目"<<edgeCount<<" 总的占领的格子数目"<<countwhite+countblack<<"其中我方"<<countwhite;
    if(countblack+countwhite>=25||edgeCount>=60){
        qDebug()<<"已下完！！！！！！！！";
        if(countwhite > countblack){
            //winner = 1;
        }else{
           // winner = 0;
        }
        return;
    }

    int Num_Antdoublecorse;
    Num_Antdoublecorse = Count_AntDoublecorse(Square);
    int lian = wulian(Square);

    if (Num_Antdoublecorse == 0 && lian == 0)
    {
        Situation to[6][6];
        chu Movelist[61];									//储存招法的数组
        int len = move1(factcheer, Movelist);
        for(int i=0;i<len;i++){

            copy1(factcheer,to);
            to[Movelist[i].x][Movelist[i].y].edge[Movelist[i].k]='*';
            to[Movelist[i].x][Movelist[i].y].degree--;
            mutualoccupy1(to, Movelist[i].x,Movelist[i].y,Movelist[i].k);
            int count =0;
            int eat = 0;
            while(eat==0||eat>count){
                count = eat;
                for(int i=1;i<6;i++)
                    for(int j=1;j<6;j++){
                        if(to[i][j].degree==1){
                            for(int k=0;k<4;k++){
                                if(to[i][j].edge[k]=='1'){
                                    to[i][j].edge[k]='*';
                                    to[i][j].degree--;
                                    mutualoccupy1(to, i,j,k);
                                    eat++;
                                }
                            }
                        }
                    }
            }

            Movelist[i].lose_box = eat;
        }
        int count, choice= 0;
        for(int i =0;i<len;i++){
            if(i==0){
                count=Movelist[i].lose_box;
            }
            if(Movelist[i].lose_box<count){
                count=Movelist[i].lose_box;
                choice = i;
            }
        }
        factcheer[Movelist[choice].x][Movelist[choice].y].edge[Movelist[choice].k]='*';
        factcheer[Movelist[choice].x][Movelist[choice].y].degree--;
        mutualoccupy1(factcheer, Movelist[choice].x,Movelist[choice].y,Movelist[choice].k);
        getchecksline(Movelist[choice].x,Movelist[choice].y,Movelist[choice].k);
        chaincount--;return;
    }
    if (Num_Antdoublecorse == 0)									//已无反双交时的吃子策略
    {

        aa:
        None_Antdoublecorse(Square, turn);
        return;
    }
    else
    {
        Eat_all_box(Square, turn);
        Num_Antdoublecorse = Count_AntDoublecorse(Square);
        if(Num_Antdoublecorse==0) {goto aa;qDebug()<<"aaaaaaaa";}

        if (Num_Antdoublecorse % 2 == 1)
        {

            copy1(Square,first);
            Odd_Number_Doublecorse(Square,turn);							//反双交为奇数时的吃子策略
            if(Equal(Square,first)){
                for( int i=1;i<6;i++)
                    for(int j=1;j<6;j++){
                        if(Square[i][j].degree==3){
                            for(int k=0;k<4;k++){
                                if(turn==1){
                                    Square[i][j].edge[k]='*';
                                    getchecksline(i,j,k);
                                    chaincount--;
                                    Square[i][j].degree--;
                                    mutualoccupy1(Square, i,j,k);
                                    return;
                                }
                            }
                        }
                    }
            }

        }
        else
        {

            copy1(Square,first);
            Oven_Number_Doublecorse(Square,turn);							//反双交为偶数时的吃子策略

            if(Equal(Square,first)){
                qDebug()<<"Num_Antdoublecorse="<<Num_Antdoublecorse;
                qDebug()<<"singlechain="<<singlechain;
                qDebug()<<"doublechain="<<doublechain;
                qDebug()<<"fanshuagnjiao="<<fanshuagnjiao;
                for(int i = 0;i<6;i++)
                    for(int j=0;j<6;j++)
                        qDebug()<<Square[i][j].degree;
                bianli(Square);
//                exit(0);
            }

        }
    }

}

bool AI::Dead(Situation Square[6][6])   //判断是否任何一条边下上去都是死格，若是返回true，即任何一步都会形成一死格//否，返回false。
{


    int s = 0;
    for (int x = 1; x < 6; x++)
        for (int y = 1; y < 6; y++)
            for (int k = 0; k < 4; k++)
            {
                if (Square[x][y].edge[k] == '1')
                {

                    if ((x > 1 && x < 5) && (y > 1 && y < 5))
                    {
                        if (Square[x][y].degree <= 2) { continue; }
                        else if (k == 0 && Square[x][y - 1].degree <= 2) { continue; }
                        else if (k == 1 && Square[x - 1][y].degree <= 2) { continue; }
                        else if (k == 2 && Square[x][y + 1].degree <= 2) { continue; }
                        else if (k == 3 && Square[x + 1][y].degree <= 2) { continue; }

                        else
                        {

                            s++;
                        }

                    }
                    else if (x == 1 && y > 1 && y < 5)
                    {
                        if (Square[x][y].degree <= 2) { continue; }
                        else if (k == 0 && Square[x][y - 1].degree <= 2) { continue; }
                        else if (k == 2 && Square[x][y + 1].degree <= 2) { continue; }
                        else if (k == 3 && Square[x + 1][y].degree <= 2) { continue; }
                        else
                        {

                            s++;
                        }

                    }//上3

                    else if (x == 5 && y > 1 && y < 5)
                    {
                        if (Square[x][y].degree <= 2) { continue; }
                        else if (k == 0 && Square[x][y - 1].degree <= 2) { continue; }
                        else if (k == 2 && Square[x][y + 1].degree <= 2) { continue; }
                        else if (k == 1 && Square[x - 1][y].degree <= 2) { continue; }
                        else
                        {

                            s++;
                        }


                    }//下3
                    else if (y == 1 && x > 1 && x < 5)
                    {
                        if (Square[x][y].degree <= 2) { continue; }
                        else if (k == 3 && Square[x + 1][y].degree <= 2) { continue; }
                        else if (k == 2 && Square[x][y + 1].degree <= 2) { continue; }
                        else if (k == 1 && Square[x - 1][y].degree <= 2) { continue; }
                        else
                        {

                            s++;
                        }


                    }//左3
                    else if (y == 5 && x > 1 && x < 5)
                    {
                        if (Square[x][y].degree <= 2) { continue; }
                        else if (k == 3 && Square[x + 1][y].degree <= 2) { continue; }
                        else if (k == 0 && Square[x][y - 1].degree <= 2) { continue; }
                        else if (k == 1 && Square[x - 1][y].degree <= 2) { continue; }
                        else
                        {

                            s++;
                        }


                    }//右3

                    else if (x == 1 && y == 1)
                    {
                        if (Square[x][y].degree <= 2) { continue; }
                        else if (k == 3 && Square[x + 1][y].degree <= 2) { continue; }
                        else if (k == 2 && Square[x][y + 1].degree <= 2) { continue; }
                        else
                        {

                            s++;
                        }



                    }//上点
                    else if (x == 5 && y == 1)
                    {
                        if (Square[x][y].degree <= 2) { continue; }
                        else if (k == 2 && Square[x][y + 1].degree <= 2) { continue; }
                        else if (k == 1 && Square[x - 1][y].degree <= 2) { continue; }
                        else
                        {

                            s++;
                        }


                    }//左下点
                    else if (x == 1 && y == 5)
                    {
                        if (Square[x][y].degree <= 2) { continue; }
                        else if (k == 3 && Square[x + 1][y].degree <= 2) { continue; }
                        else if (k == 0 && Square[x][y - 1].degree <= 2) { continue; }
                        else
                        {
                            s++;
                        }
                    }//右上点
                    else
                    {
                        if (Square[x][y].degree <= 2) { continue; }
                        else if (k == 1 && Square[x - 1][y].degree <= 2) { continue; }
                        else if (k == 0 && Square[x][y - 1].degree <= 2) { continue; }
                        else
                        {

                            s++;
                        }
                    }//右下点
                }

            }

    if (s == 0)  return true;
    if (s >0)  return false;

}
//吃掉一个自由度的函数
bool AI::Dead1(Situation  Square[6][6], int i, int j, int k, int turn)                         //判断是否占领格子，并占领，成功turn
{

    if (Square[i][j].edge[k] == '1'&&k == 3 && (i > 0 && i < 5))
    {
        if (Square[i][j].degree == 1)
        {
           // chaincount--;
            if (turn == 1)
            {
                Square[i][j].edge[3] = '*';
                Square[i][j].degree--;
                chaincount--;
                //相互占格函数
                mutualoccupy1(Square, i, j, k);
                getchecksline(i,j,k);
                opc(Square, turn);
                return true;
            }
        }
        else if (Square[i + 1][j].degree == 1)
        {
            //chaincount--;
            if (turn == 1)

            {
                Square[i + 1][j].edge[1] = '*'; chaincount--;
                Square[i + 1][j].degree--;
                mutualoccupy1(Square, i + 1, j, 1);
                getchecksline(i+1,j,1);
                opc(Square, turn);

                return true;
            }

        }
        //========================================================================
        ;                              //判断横边
    }



    else if (Square[i][j].edge[k] == '1'&&k == 1 && i == 1) {
        if (Square[i][j].degree == 1)
        {
           // chaincount--;
            if (turn == 1)
            {
                Square[i][j].edge[1] = '*'; chaincount--;
                Square[i][j].degree--;
                mutualoccupy1(Square, i , j, 1);
                getchecksline(i,j,1);
                opc(Square, turn);
                return true;
            }

        }
    }
    else if (Square[i][j].edge[k] == '1'&&k == 3 && i == 5) {
        if (Square[i][j].degree == 1)
        {
            //chaincount--;
            if (turn == 1)

            {
                Square[i][j].edge[3] = '*'; chaincount--;
                Square[i][j].degree--;
                mutualoccupy1(Square, i , j, 3);
                getchecksline(i,j,3);
                opc(Square, turn);
                return true;
            }
        }
    }
    //判断横边上底，下底

    else if (Square[i][j].edge[k] == '1'&&k == 2 && j > 0 && j < 5)
    {
        if (Square[i][j].degree == 1)
        {
           // chaincount--;
            if (turn == 1)
            {
                Square[i][j].edge[2] = '*'; chaincount--;
                Square[i][j].degree--;

                mutualoccupy1(Square, i, j, k);
                getchecksline(i,j,2);
                opc(Square, turn);
                return true;
            }
        }
        else if (Square[i][j + 1].degree == 1)
        {
           // chaincount--;
            if (turn == 1)

            {
                Square[i][j + 1].edge[0] = '*';
                chaincount--;
                Square[i][j + 1].degree--;
                mutualoccupy1(Square, i, j + 1, 0);
                getchecksline(i,j+1,0);
                opc(Square, turn);
                return true;
            }

        }
    }                              //判断横边




    else if (Square[i][j].edge[k] == '1'&&k == 0 && j == 1) {
        if (Square[i][1].degree == 1)
        {
            //chaincount--;
            if (turn == 1)
            {
                Square[i][j].edge[0] = '*'; chaincount--;
                Square[i][j].degree--;
                mutualoccupy1(Square, i , j, 0);
                getchecksline(i,j,0);

                opc(Square, turn);
                return true;
            }
        }
    }
    else if (Square[i][j].edge[k] == '1'&&k == 2 && j == 5) {

        if (Square[i][j].degree == 1)
        {
           // chaincount--;
            if (turn == 1)
            {
                Square[i][j].edge[2] = '*'; chaincount--;
                Square[i][j].degree--;
                mutualoccupy1(Square, i , j, 2);
                getchecksline(i,j,2);
                opc(Square, turn);
                return true;
            }
        }
    }
    //判断竖边左右
    return false;
}

void  AI::Winner() { //记得被占格子时候，使myconnt或hecount自增

    int temp;
    temp=countblack+countwhite;
    if(temp==25)
    {
        //项目开头
        string begin("C:\\test\\");
        //项目结束
        string end(".txt");
        tm* local; //本地时间
        time_t t;  //秒时间
        //棋盘
        char buf[128]= {0};

        t = time(NULL); //获取目前秒时间
        local = localtime(&t); //转为本地时间
        strftime(buf, 64, "%Y-%m-%d %H:%M:%S", local);
        string str(buf);

        str.erase(0,str.find_first_not_of(" "));
        str.erase(str.find_last_not_of("\r\n") + 1);
        int index = 0;
           if( !str.empty())
            {
              while( (index = str.find(':',index)) != string::npos)
              {
                  str.erase(index,1);
              }
           }
           begin = begin+str+end;
           const char *p = begin.c_str();
           fstream file;
           file.open( begin, ios::out );
               if (!file)
               {
                   cout << "Failed to create file...\n";

               }
               file.close();
        if (countblack > countwhite) {

            fstream fin(path); //打开文件

                string readline;
                ofstream write(begin,ios::app);
                qDebug()<<"执行uct";
                while (getline(fin, readline)) //逐行读取，直到结束
                {

                    string str("    0");
                    readline=readline+str;

                    write<<readline<<endl;


                }
            write.close();


        QMessageBox::about(this,"结束","敌方胜利");
        }else   {

                fstream fin(path); //打开文件
                     //qDebug()<<"写入文件开始"<<endl;
                    string readline;
                    ofstream write(begin,ios::app);
                    while (getline(fin, readline)) //逐行读取，直到结束
                    {

                        string str("    1");
                        readline=readline+str;

                        write<<readline<<endl;
                        cout<<readline<<endl;

                    }
                write.close();
        QMessageBox::about(this,"结束","我方胜利");
        }


}
}
/*
    流程控制函数
        1.判断当前棋局下一步是否存在安全边
                   存在：找出所有安全边，进行棋局模拟
                   不存在：


*/
//最重要的函数myturn为先后手，1我2他 ，   turn为论数 1为我2他
void AI::Order(Situation Square[6][6], int myturn, int turn) {
    if (myturn == 1)
    {
        if (chaincount <= 60)
        {

            Order1(Square, myturn, 1);
            //Count_AntDoublecorse(Square);
            //None_Antdoublecorse2(Square,turn);
            //CheckFreeom(Square);
            //Find_GuaiDian(Square);

        }else if(chaincount > 46){
/*
chi: turn = 1;
 for (int i = 1; i < 6; i++)
     for (int j = 1; j < 6; j++)
         for (int k = 0; k < 4; k++) {

             if (Dead1(Square, i, j, k, turn))
             {
                goto chi;
             }
         }
 randmove(Square, turn);//我方随机下棋函数
 chaincount--;
 qDebug()<<"可下边"<<chaincount;
 qDebug()<<"调用了rand";
*/
            /*
            chu Movelist[61];									//储存招法的数组
            int len = move(factcheer, Movelist);
            srand(clock()); //随机函数 随机选一条边
            int i = rand()%len;
            factcheer[Movelist[i].x][Movelist[i].y].edge[Movelist[i].k] = '*';
            factcheer[Movelist[i].x][Movelist[i].y].degree--;
            mutualoccupy1(factcheer, Movelist[i].x, Movelist[i].y, Movelist[i].k);
            getchecksline(Movelist[i].x, Movelist[i].y, Movelist[i].k);

            chaincount--;
            */

            Ai_UCT uct ;
            Situation1 *copy_chess = new Situation1;
            qDebug()<<"创建uct";

            copy1(factcheer,copy_chess->cheer);


            uct.UCTSearch(*copy_chess,1);
            delete copy_chess;
            qDebug()<<"执行uct";
            factcheer[uct.Bestmove.x][uct.Bestmove.y].edge[uct.Bestmove.k] = '*';
            factcheer[uct.Bestmove.x][uct.Bestmove.y].degree--;
            mutualoccupy1(factcheer, uct.Bestmove.x, uct.Bestmove.y, uct.Bestmove.k);
            getchecksline(uct.Bestmove.x, uct.Bestmove.y, uct.Bestmove.k);
            opc(factcheer, turn);
            qDebug()<<"调用了uct";
            chaincount--;
                Count_AntDoublecorse(Square);
                None_Antdoublecorse2(Square,turn);
                CheckFreeom(Square);
                Find_GuaiDian(Square);
                qDebug()<<"可下边"<<chaincount;


                }

        /*qDebug()<<"我方先行x1:  "<<(int)aifirst<<""<<"单链个数x2：   "<<singlechain
               <<"长链个数x3:   "<<chainNum<<"最长链长度x4:  "<<longestChainLength
               <<"我方占格x5:   "<<mycount<<"对方占格x6: "<<hecount<<"自由度为4的格子x7: "
               <<free4<<"自由度为3的格子x8: "<<free3<<"自由度为2的格子x9: "<<free2
               <<"自由度为1的格子x10: "<<free1<<"环的个数x11： "<<circlenum<<"拐点个数x12：  "
               <<guaidian<<"反双交的个数x13："<<fanshuagnjiao<<"双链的个数x14："<<doublechain
              << "已下边x15:   "<<60-chaincount;*/
/*
        ofstream write(path,ios::app);
        //write.open(path);     //作为输出文件打开
            write<<(int)aifirst<<"  "<<singlechain<<"   "<<chainNum<<"   "<<
                longestChainLength<<"   "<<mycount<<"   "<<hecount<<"   "<<free4<<"   "<<
                free3<<"   "<<free2<<"   "<<free1<<"   "<<circlenum<<"   "<<guaidian<<"     "
                <<fanshuagnjiao<<"   "<<doublechain<<"   "<<60-chaincount<<endl;   //标题写入文件
            write.close();
          //  } */

    }
    go=false;   //重置GO值

}

void AI::Find_GuaiDian(Situation Square[6][6]){
    guaidian = 0;

    if (Dead(Square))
    {

        for(int i=1;i<6;i++)
            for(int j=1;j<6;j++){
                if (Square[i][j].degree==3) {
                    guaidian++;
                }
            }
    }
}

void AI::Order1(Situation Square[6][6], int myturn, int turn)
{
    if (Dead(Square))
    {
        Order2(turn);
    }else

    {
chi1:    turn = 1;
//     while(chi==1)
    {
        for (int i = 1; i < 6; i++)
        for (int j = 1; j < 6; j++)
            for (int k = 0; k < 4; k++)
            {
                if (Dead1(Square, i, j, k, turn))
                {
                 goto chi1;
                }
            }
    }
            //原函数是chaincount > 33
        if(tiaojian1(Square)){
            if(heixiazi1(Square) >= 1){
                goto line_x;
            }
            else if(heixiazi1(Square) == 0){
                action_move(Square, myturn);
                chaincount--;
                qDebug()<<"可下边"<<chaincount;
                qDebug()<<"调用了rand";
                goto line_y;
            }
/*            else if(heixiazi2(Square) == 0){
                action_move1(Square, myturn);
                chaincount--;
                qDebug()<<"可下边"<<chaincount;
                qDebug()<<"调用了rand";
                goto line_y;
            }*/
        }
        else {

line_x:     qDebug()<<"进入UCT";
            Ai_UCT uct ;
            qDebug()<<"创建完UCT";
            Situation1 *copy_chess = new Situation1;

            copy1(factcheer,copy_chess->cheer);

            uct.UCTSearch(*copy_chess,1);
            delete copy_chess;
            qDebug()<<"调用了uct";
            factcheer[uct.Bestmove.x][uct.Bestmove.y].edge[uct.Bestmove.k] = '*';
            factcheer[uct.Bestmove.x][uct.Bestmove.y].degree--;
            mutualoccupy1(factcheer, uct.Bestmove.x, uct.Bestmove.y, uct.Bestmove.k);
            getchecksline(uct.Bestmove.x, uct.Bestmove.y, uct.Bestmove.k);

            chaincount--;
            qDebug()<<"全部完";


        }



        /*
        Ai_UCT uct ;
        Situation1 *copy_chess = new Situation1;

        copy1(factcheer,copy_chess->cheer);

        uct.UCTSearch(*copy_chess,1);
        delete copy_chess;

        factcheer[uct.Bestmove.x][uct.Bestmove.y].edge[uct.Bestmove.k] = '*';
        factcheer[uct.Bestmove.x][uct.Bestmove.y].degree--;
        mutualoccupy1(factcheer, uct.Bestmove.x, uct.Bestmove.y, uct.Bestmove.k);
        getchecksline(uct.Bestmove.x, uct.Bestmove.y, uct.Bestmove.k);
        qDebug()<<"调用了uct";
        chaincount--;*/

        /*
        Search(1, -1000, 1000, turn);
        factcheer[Bestmove.x][Bestmove.y].edge[Bestmove.k] = '*';
        factcheer[Bestmove.x][Bestmove.y].degree--;
        mutualoccupy1(factcheer, Bestmove.x, Bestmove.y, Bestmove.k);
        getchecksline(Bestmove.x, Bestmove.y, Bestmove.k);
        qDebug()<<"调用了SEARCH";
        chaincount--;*/
        /*
        chu Movelist[61];									//储存招法的数组
        int len = move(factcheer, Movelist);
        srand(clock()); //随机函数 随机选一条边
        int i = rand()%len;
        factcheer[Movelist[i].x][Movelist[i].y].edge[Movelist[i].k] = '*';
        factcheer[Movelist[i].x][Movelist[i].y].degree--;
        mutualoccupy1(factcheer, Movelist[i].x, Movelist[i].y, Movelist[i].k);
        getchecksline(Movelist[i].x, Movelist[i].y, Movelist[i].k);

        chaincount--;
        */

line_y: ;
    }


}

void AI::CheckFreeom(Situation Square[6][6]){

    free1 = 0;free2 = 0;free3 = 0;free4 = 0;
    for(int i=1;i<6;i++)
        for(int j=1;j<6;j++){
            if(Square[i][j].degree==1){
                free1++;
            }else if (Square[i][j].degree==2) {
                free2++;
            }else if (Square[i][j].degree==3) {
                free3++;
            }else if (Square[i][j].degree==4) {

                free4++;
            }
        }
}

int AI::find_free3(Situation Square[6][6]){
    int free3=0;
    for (int i = 1; i <6; i++)
    {
        for (int j = 1; j < 6; j++)
        {
           if(Square[i][j].degree==1){free3++;}
        }
    }
    return free3;
}

int AI::find_free1(Situation Square[6][6]){
    int free1=0;
    for (int i = 1; i <6; i++)
    {
        for (int j = 1; j < 6; j++)
        {
           if(Square[i][j].degree==1){free1++;}
        }
    }
    return free1;
}
/*
void AI::Order2(int turn){
    //检查自由度
    for(int i=1;i<6;i++)
        for(int j=1;j<6;j++){
            int count = 0;
            for(int k=0;k<4;k++){
                if(factcheer[i][j].edge[k]=='1'){
                    count++;
                }
            }
            factcheer[i][j].degree = count;
        }

    int number = Count_AntDoublecorse(factcheer);
    Situation to[6][6];
    qDebug()<<"*****************************";
    qDebug()<<"singllechain="<<singlechain;
    qDebug()<<"doublechain="<<doublechain;
    qDebug()<<"fanshuangjiao="<<fanshuagnjiao;
    qDebug()<<"num="<<number;

    if(number>0){
        if(find_free1(factcheer)>0){
            int i, j, num = 0, x1 = 0, x2 = 0, y1 = 0, y2 = 0, len1, len2;
            for (i = 1; i <= 5; i++)
            {
                for (j = 1; j <= 5; j++)
                {
                    qDebug()<<factcheer[i][j].degree;
                        if (factcheer[i][j].degree == 1)//自由度为一的 z
                        {
                            qDebug()<<"111111111";
                        num++;
                        if (x1 == 0)
                        {
                            x1 = i; y1 = j;
                        }
                        else
                        {
                            x2 = i; y2 = j;
                        }
                    }
                }

             qDebug()<<"num="<<num;
             if(num==1){

             }else if(num==2){

             }else if(num>2){

             }

        }

    }else{//无地方换手
        if(find_free1(factcheer)>0)//有格子可吃
         {
            qDebug()<<"无换手有链可吃";
             None_Antdoublecorse(factcheer, 1);
        }else{//无格子吃
            qDebug()<<"无换手无链可吃";
            Kill();

        }
    }
   }
}
*/
void AI::Kill(){

        Situation to[6][6];
        chu Movelist[61];									//储存招法的数组
        int len = move1(factcheer, Movelist);
        for(int i=0;i<len;i++){

            copy1(factcheer,to);
            to[Movelist[i].x][Movelist[i].y].edge[Movelist[i].k]='*';
            to[Movelist[i].x][Movelist[i].y].degree--;
            mutualoccupy1(to, Movelist[i].x,Movelist[i].y,Movelist[i].k);
            int count =0;
            int eat = 0;
            while(eat==0||eat>count){
                count = eat;
                for(int i=1;i<6;i++)
                    for(int j=1;j<6;j++){
                        if(to[i][j].degree==1){
                            for(int k=0;k<4;k++){
                                if(to[i][j].edge[k]=='1'){
                                    to[i][j].edge[k]='*';
                                    to[i][j].degree--;
                                    mutualoccupy1(to, i,j,k);
                                    eat++;
                                }
                            }
                        }
                    }
            }

            Movelist[i].lose_box = eat;
        }
        int count, choice= 0;
        for(int i =0;i<len;i++){
            if(i==0){
                count=Movelist[i].lose_box;
            }
            if(Movelist[i].lose_box<count){
                count=Movelist[i].lose_box;
                choice = i;
            }
        }
        factcheer[Movelist[choice].x][Movelist[choice].y].edge[Movelist[choice].k]='*';
        factcheer[Movelist[choice].x][Movelist[choice].y].degree--;
        mutualoccupy1(factcheer, Movelist[choice].x,Movelist[choice].y,Movelist[choice].k);
        getchecksline(Movelist[choice].x,Movelist[choice].y,Movelist[choice].k);
        chaincount--;

}

void AI::Order2(int turn)
{
    begin:
    //重新统计自由度
    int three = 0;
    for(int i=1;i<6;i++)
        for(int j=1;j<6;j++){
            int count = 0;
            for(int k=0;k<4;k++){
                if(factcheer[i][j].edge[k]=='1'){
                    count++;
                }
            }
            if(count == 1){
                three++;
            }
            factcheer[i][j].degree = count;
        }

    //反双交个数
    int number = Count_AntDoublecorse(factcheer);
    Situation to[6][6];
    qDebug()<<"*****************************";
    qDebug()<<"singllechain="<<singlechain;
    qDebug()<<"doublechain="<<doublechain;
    qDebug()<<"fanshuangjiao="<<fanshuagnjiao;
    qDebug()<<"num="<<number;


    Situation To[6][6];
    copy1(factcheer,To);
    chu move[61];    //存储招法
    int result[61];  //存储模拟结果
    int myturn = turn;
    int num = 0;

    if(three != 0){
        qDebug()<<"three = "<<three;
        goto line_m;
    }


    num = three_count(To,move);
    qDebug()<<"num2 = "<<num;


    if(num != 0){
        qDebug()<<"残局下某特殊边";
        for(int i=0; i<num; i++){
            Situation to[6][6];
            copy1(factcheer,to);
            putcheer(to,move[i].x,move[i].y,move[i].k,myturn);
            qDebug()<<"模拟下x = "<<move[i].x<<" y = "<<move[i].y<<" k = "<<move[i].k;
            myturn = !myturn;
            for(int x=1; x<6; x++){
                for(int y=1; y<6; y++){
                    if(to[x][y].degree == 1){
                        for(int k=0; k<4; k++){
                            if(to[x][y].edge[k] == '1'){
                                putcheer(to,x,y,k,myturn);
                            }
                        }
                    }
                }
            }
            myturn = !myturn;
            if(Evaluation_I(to,myturn)){
                result[i] = 1;
            }
            else{
                result[i] = 0;
            }
        }
        int max = 0;
        for(int j=1; j<num; j++){
            if(result[j] > result[max]){
                max = j;
            }
        }
        qDebug()<<"最终下x = "<<move[max].x<<" y = "<<move[max].y<<" k = "<<move[max].k;
        factcheer[move[max].x][move[max].y].edge[move[max].k] = '*';
        factcheer[move[max].x][move[max].y].degree--;
        mutualoccupy1(factcheer, move[max].x, move[max].y, move[max].k);
        getchecksline(move[max].x, move[max].y, move[max].k);
        opc(factcheer,myturn);
        goto line_end;
    }

    line_m:
    if(number!=0){
        //有格先吃格
            if(singlechain==0&&doublechain==0&&number==1){
                 qDebug()<<"vvvvvvvvvvvvvvvvvvvvvvvvvvvvvv";
                 int i, j, num = 0, x1 = 0, x2 = 0, y1 = 0, y2 = 0, len1, len2;
                 for (i = 1; i <= 5; i++)
                 {
                     for (j = 1; j <= 5; j++)
                     {
                         qDebug()<<factcheer[i][j].degree;
                             if (factcheer[i][j].degree == 1)//自由度为一的 z
                             {
                                 qDebug()<<"111111111";
                             num++;
                             if (x1 == 0)
                             {
                                 x1 = i; y1 = j;
                             }
                             else
                             {
                                 x2 = i; y2 = j;
                             }
                         }
                     }
                 }
                 qDebug()<<"自由度为1的num="<<num;
                 if (num==2)
                 {
                     qDebug()<<"自由度为1的有两个"<<endl;
                     //统计以该C性格开头的链的链长
                     len1 = Chain_lenth(factcheer, x1, y1);
                     len2= Chain_lenth(factcheer, x2, y2);
                     qDebug()<<"len1="<<len1;
                     qDebug()<<"len2="<<len2;
                     //如果链长为1的化，直接吃掉链
                     if(len1==1&&len2==1){
                         Eat_a_chain(factcheer, x2, y2, len2, turn);
                         //如果还有1自由度的
                         if(find_free1(factcheer)>0){
                             Eat_a_chain(factcheer, x1, y1, len1, turn);
                         }

                         goto begin;
                     }else{
                         if(len1>len2){
                             if(len2<=2){
                                 if(len2==1){
                                     for(int k=0;k<4;k++){
                                         if(factcheer[x2][y2].edge[k]=='1'){
                                             factcheer[x2][y2].edge[k]='*';
                                             factcheer[x2][y2].degree--;
                                             mutualoccupy1(factcheer, x2,y2,k);
                                             getchecksline(x2,y2,k);
                                             opc(factcheer, turn);
                                             chaincount--;
                                         }
                                     }
                                 }else if(len2==2){
                                     int count =0;
                                     int eat = 0;
                                     while(eat==0||eat>count){
                                         count = eat;
                                         for(int i=1;i<6;i++)
                                             for(int j=1;j<6;j++){
                                                 if(factcheer[i][j].degree==1&&i!=x1&&j!=y1){
                                                     for(int k=0;k<4;k++){
                                                         if(factcheer[i][j].edge[k]=='1'){
                                                             factcheer[i][j].edge[k]='*';
                                                             factcheer[i][j].degree--;
                                                             mutualoccupy1(factcheer, i,j,k);
                                                             getchecksline(i,j,k);
                                                              opc(factcheer, turn);
                                                             chaincount--;
                                                             eat++;
                                                         }
                                                     }
                                                 }
                                             }
                                     }
                                 }
                                 goto begin;
                             }else if(len2>2){
                                 Eat_a_chain(factcheer, x2, y2, len2, turn);
                             }


                              if(len1==2){
                                 for(int k=0;k<4;k++){
                                     if(factcheer[x1][y1].edge[k]=='1'&&k==0){
                                         for(int z=0;z<4;z++){
                                             copy1(factcheer,to);
                                             if(to[x1][y1-1].edge[z]=='1'){
                                                 to[x1][y1-1].edge[z]='*';
                                                 to[x1][y1-1].degree--;
                                                 mutualoccupy1(to, x1,y1-1,z);
                                                 if(to[x1][y1-1].degree==1&&to[x1][y1].degree==1){
                                                     factcheer[x1][y1-1].edge[z]='*';
                                                     factcheer[x1][y1-1].degree--;
                                                     mutualoccupy1(factcheer, x1,y1-1,z);
                                                     getchecksline(x1,y1-1,z);
                                                     opc(factcheer, turn);
                                                     chaincount--;
                                                 }
                                             }
                                         }
                                            return;
                                     }else if(factcheer[x1][y1].edge[k]=='1'&&k==1){
                                         for(int z=0;z<4;z++){
                                             copy1(factcheer,to);
                                             if(to[x1-1][y1].edge[z]=='1'){
                                                 to[x1-1][y1].edge[z]='*';
                                                 to[x1-1][y1].degree--;
                                                 mutualoccupy1(to, x1-1,y1,z);
                                                 if(to[x1-1][y1].degree==1&&to[x1][y1].degree==1){
                                                     factcheer[x1-1][y1].edge[z]='*';
                                                     factcheer[x1-1][y1].degree--;
                                                     mutualoccupy1(factcheer, x1-1,y1,z);
                                                     getchecksline(x1-1,y1,z);
                                                      opc(factcheer, turn);
                                                     chaincount--;
                                                 }
                                             }
                                         }
                                            return;
                                     }else if(factcheer[x1][y1].edge[k]=='1'&&k==2){
                                         for(int z=0;z<4;z++){
                                             copy1(factcheer,to);
                                             if(to[x1][y1+1].edge[z]=='1'){
                                                 to[x1][y1+1].edge[z]='*';
                                                 to[x1][y1+1].degree--;
                                                 mutualoccupy1(to, x1,y1+1,z);
                                                 if(to[x1][y1+1].degree==1&&to[x1][y1].degree==1){
                                                     factcheer[x1][y1+1].edge[z]='*';
                                                     factcheer[x1][y1+1].degree--;
                                                     mutualoccupy1(factcheer, x1,y1+1,z);
                                                     getchecksline(x1,y1+1,z);
                                                      opc(factcheer, turn);
                                                     chaincount--;
                                                 }
                                             }

                                         }
                                            return;
                                     }else if(factcheer[x1][y1].edge[k]=='1'&&k==3){
                                         for(int z=0;z<4;z++){
                                             copy1(factcheer,to);
                                             if(to[x1+1][y1].edge[z]=='1'){
                                                 to[x1+1][y1].edge[z]='*';
                                                 to[x1+1][y1].degree--;
                                                 mutualoccupy1(to, x1+1,y1,z);
                                                 if(to[x1+1][y1].degree==1&&to[x1][y1].degree==1){
                                                     factcheer[x1+1][y1].edge[z]='*';
                                                     factcheer[x1+1][y1].degree--;
                                                     mutualoccupy1(factcheer, x1+1,y1,z);
                                                     getchecksline(x1+1,y1,z);
                                                      opc(factcheer, turn);
                                                     chaincount--;
                                                 }
                                             }
                                         }
                                            return;
                                     }
                                 }
                              }else if(len1>2){
                                  qDebug()<<"894596546549513216549649654444444444444555555555555555555555555555555555555555555555";
                                  Eat_Chain(factcheer, x1, y1, len1, turn);
                                  return;
                              }
                         }else{
                             if(len1<=2){
                                 if(len1==1){
                                     for(int k=0;k<4;k++){
                                         if(factcheer[x1][y1].edge[k]=='1'){
                                             factcheer[x1][y1].edge[k]='*';
                                             factcheer[x1][y1].degree--;
                                             mutualoccupy1(factcheer, x1,y1,k);
                                             getchecksline(x1,y1,k);
                                             opc(factcheer, turn);
                                             chaincount--;
                                         }
                                     }
                                 }else if(len1==2){
                                     int count =0;
                                     int eat = 0;
                                     int circle_count  = 0;
                                     while(eat==0||eat>count){
                                         circle_count++;
                                         if(circle_count>30){
                                             break;
                                         }
                                         qDebug()<<"wwwwwwwwwwwwwwwwwwwwww";
                                         count = eat;
                                         for(int i=1;i<6;i++)
                                             for(int j=1;j<6;j++){
                                                 if(factcheer[i][j].degree==1&&i!=x2&&j!=y2){
                                                     for(int k=0;k<4;k++){
                                                         if(factcheer[i][j].edge[k]=='1'){
                                                             factcheer[i][j].edge[k]='*';
                                                             factcheer[i][j].degree--;
                                                             mutualoccupy1(factcheer, i,j,k);
                                                             getchecksline(i,j,k);
                                                              opc(factcheer, turn);
                                                             chaincount--;
                                                             eat++;
                                                         }
                                                     }
                                                 }
                                             }
                                     }
                                 }
                                goto begin;
                             }

                              if(len2==2){
                                  for(int k=0;k<4;k++){
                                      if(factcheer[x2][y2].edge[k]=='1'&&k==0){
                                          for(int z=0;z<4;z++){
                                              copy1(factcheer,to);
                                              if(to[x2][y2-1].edge[z]=='1'){
                                                  to[x2][y2-1].edge[z]='*';
                                                  to[x2][y2-1].degree--;
                                                  mutualoccupy1(to, x2,y2-1,z);
                                                  if(to[x2][y2-1].degree==1&&to[x2][y2].degree==1){
                                                      factcheer[x2][y2-1].edge[z]='*';
                                                      factcheer[x2][y2-1].degree--;
                                                      mutualoccupy1(factcheer, x2,y2-1,z);
                                                      getchecksline(x2,y2-1,z);
                                                       opc(factcheer, turn);
                                                      chaincount--;
                                                      return;
                                                  }
                                              }
                                          }

                                      }else if(factcheer[x2][y2].edge[k]=='1'&&k==1){
                                          for(int z=0;z<4;z++){
                                              copy1(factcheer,to);
                                              if(to[x2-1][y2].edge[z]=='1'){
                                                  to[x2-1][y2].edge[z]='*';
                                                  to[x2-1][y2].degree--;
                                                  mutualoccupy1(to, x2-1,y2,z);
                                                  if(to[x2-1][y2].degree==1&&to[x2][y2].degree==1){
                                                      factcheer[x2-1][y2].edge[z]='*';
                                                      factcheer[x2-1][y2].degree--;
                                                      mutualoccupy1(factcheer, x2-1,y2,z);
                                                      getchecksline(x2-1,y2,z);
                                                       opc(factcheer, turn);
                                                      chaincount--;
                                                      return;
                                                  }
                                              }
                                          }

                                      }else if(factcheer[x2][y2].edge[k]=='1'&&k==2){
                                          for(int z=0;z<4;z++){
                                              copy1(factcheer,to);
                                              if(to[x2][y2+1].edge[z]=='1'){
                                                  to[x2][y2+1].edge[z]='*';
                                                  to[x2][y2+1].degree--;
                                                  mutualoccupy1(to, x2,y2+1,z);
                                                  if(to[x2][y2+1].degree==1&&to[x2][y2].degree==1){
                                                      factcheer[x2][y2+1].edge[z]='*';
                                                      factcheer[x2-1][y2+1].degree--;
                                                      mutualoccupy1(factcheer, x2,y2+1,z);
                                                      getchecksline(x2,y2+1,z);
                                                       opc(factcheer, turn);
                                                      chaincount--;
                                                      return;
                                                  }
                                              }
                                          }

                                      }else if(factcheer[x2][y2].edge[k]=='1'&&k==3){
                                          for(int z=0;z<4;z++){
                                              copy1(factcheer,to);
                                              if(to[x2+1][y2].edge[z]=='1'){
                                                  to[x2+1][y2].edge[z]='*';
                                                  to[x2+1][y2].degree--;
                                                  mutualoccupy1(to, x2+1,y2,z);
                                                  if(to[x2+1][y2].degree==1&&to[x2][y2].degree==1){
                                                      factcheer[x2+1][y2].edge[z]='*';
                                                      factcheer[x2+1][y2].degree--;
                                                      mutualoccupy1(factcheer, x2+1,y2,z);
                                                      getchecksline(x2+1,y2,z);
                                                       opc(factcheer, turn);
                                                      chaincount--;
                                                      return;
                                                  }
                                              }
                                          }

                                      }
                                  }
                               }else if(len2>2){

                                  Eat_Chain(factcheer, x2, y2, len2, turn);
                                  return;
                              }
                         }
                     }


                 }
                 else if (num == 1){
                     //链的长度
                     len1 = Chain_lenth(factcheer, x1, y1);
                        qDebug()<<"!!!!!!!!!!!!!!!!!len1="<<len1;
                     if(len1==1){

                        for(int k=0;k<4;k++){
                            if(factcheer[x1][y1].edge[k]=='1'){
                                factcheer[x1][y1].edge[k]='*';
                                factcheer[x1][y1].degree--;
                                mutualoccupy1(factcheer, x1,y1,k);
                                getchecksline(x1,y1,k);
                                 opc(factcheer, turn);
                                chaincount--;
                                goto begin;
                            }
                        }
                     }
                     //链长为2
                     else if(len1==2){
                         for(int k=0;k<4;k++){
        if(factcheer[x1][y1].edge[k]=='1'&&k==0){
        qDebug()<<"aaaaaaaaaaaaaaa";
        for(int z=0;z<4;z++){
            copy1(factcheer,to);
            if(to[x1][y1-1].edge[z]=='1'){
                to[x1][y1-1].edge[z]='*';
                to[x1][y1-1].degree--;
                mutualoccupy1(to, x1,y1-1,z);
                if(to[x1][y1-1].degree==1&&to[x1][y1].degree==1){
                    factcheer[x1][y1-1].edge[z]='*';
                    factcheer[y1][x1-1].degree--;
                    mutualoccupy1(factcheer, x1,y1-1,z);
                    getchecksline(x1,y1-1,z);
                     opc(factcheer, turn);
                    chaincount--;
                    return;
                }
            }
        }

    }else if(factcheer[x1][y1].edge[k]=='1'&&k==1){
        qDebug()<<"aaaaaaaaaaaaaaa";
        for(int z=0;z<4;z++){
            copy1(factcheer,to);
            if(to[x1-1][y1].edge[z]=='1'){
                to[x1-1][y1].edge[z]='*';
                to[x1-1][y1].degree--;
                mutualoccupy1(to, x1-1,y1,z);
                if(to[x1-1][y1].degree==1&&to[x1][y1].degree==1){
                    factcheer[x1-1][y1].edge[z]='*';
                    factcheer[x1-1][y1].degree--;
                    mutualoccupy1(factcheer, x1-1,y1,z);
                    getchecksline(x1-1,y1,z);
                     opc(factcheer, turn);
                    chaincount--;return;
                }
            }
        }

    }else if(factcheer[x1][y1].edge[k]=='1'&&k==2){
        qDebug()<<"aaaaaaaaaaaaaaa";
        for(int z=0;z<4;z++){
            copy1(factcheer,to);
            if(to[x1][y1+1].edge[z]=='1'){
                to[x1][y1+1].edge[z]='*';
                to[x1][y1+1].degree--;
                mutualoccupy1(to, x1,y1+1,z);
                if(to[x1][y1+1].degree==1&&to[x1][y1].degree==1){
                    factcheer[x1][y1+1].edge[z]='*';
                    factcheer[x1-1][y1+1].degree--;
                    mutualoccupy1(factcheer, x1,y1+1,z);
                    getchecksline(x1,y1+1,z);
                     opc(factcheer, turn);
                    chaincount--;return;
                }
            }
        }

    }else if(factcheer[x1][y1].edge[k]=='1'&&k==3){
        qDebug()<<"aaaaaaaaaaaaaaa";
        for(int z=0;z<4;z++){
            copy1(factcheer,to);
            if(to[x1+1][y1].edge[z]=='1'){
                to[x1+1][y1].edge[z]='*';
                to[x1+1][y1].degree--;
                mutualoccupy1(to, x1+1,y1,z);
                if(to[x1+1][y1].degree==1&&to[x1][y1].degree==1){
                    factcheer[x1+1][y1].edge[z]='*';
                    factcheer[x1+1][y1].degree--;
                    mutualoccupy1(factcheer, x1+1,y1,z);
                    getchecksline(x1+1,y1,z);
                     opc(factcheer, turn);
                    chaincount--;return;
                }
            }
        }

    }
}
                        }else{
                         qDebug()<<"asdghwergberhrtyjesrthsjrw&&链长不是二（大于）";
                         qDebug()<<"此时吃格子的人是1"<<turn;
                         Eat_Chain(factcheer, x1, y1, len1, turn);
                     }

                 }else if(num==0){
                     goto later;
                 }else{

                             len1 = Chain_lenth(factcheer, x1, y1);
                             len2 = Chain_lenth(factcheer, x2, y2);
                             if(len1>len2){
                                 Eat_a_chain(factcheer,x1,y1,len1,turn);
                             }else{
                                 Eat_a_chain(factcheer,x2,y2,len2,turn);
                             }
                             goto begin;

                 }

            }else{

                later:
                number = Count_AntDoublecorse(factcheer);
                copy1(factcheer,to);
                if(find_free1(to)>0){
                    qDebug()<<"1111111111111111111111111111111自由度数量大于1";
                    int count =0;
                    int eat = 0;
                    while(eat==0||eat>count){
                        qDebug()<<"ssssssssssssssssssss吃链";
                        count = eat;
                        for(int i=1;i<6;i++)
                            for(int j=1;j<6;j++){
                                if(to[i][j].degree==1){
                                    for(int k=0;k<4;k++){
                                        if(to[i][j].edge[k]=='1'){
                                            to[i][j].edge[k]='*';
                                            to[i][j].degree--;
                                             opc(to, turn);
                                            chaincount--;
                                            eat++;
                                        }
                                    }
                                }
                            }
                    }

                    int to_count = Count_AntDoublecorse(to);
                    if(to_count%2==0){
                        if(find_free1(factcheer)>0){
                            int count =0;
                            int eat = 0;
                            while(eat==0||eat>count){
                                qDebug()<<"ssssssssssssssssssss吃链";
                                count = eat;
                                for(int i=1;i<6;i++)
                                    for(int j=1;j<6;j++){
                                        if(factcheer[i][j].degree==1){
                                            for(int k=0;k<4;k++){
                                                if(factcheer[i][j].edge[k]=='1'){
                                                    factcheer[i][j].edge[k]='*';
                                                    factcheer[i][j].degree--;
                                                    mutualoccupy1(factcheer, i,j,k);
                                                    getchecksline(i,j,k);
                                                     opc(factcheer, turn);
                                                    chaincount--;
                                                    eat++;
                                                }
                                            }
                                        }
                                    }
                            }
                    goto begin;

                        }
                    }else{
                        qDebug()<<"2121212121212126666666666";
                        bianli(factcheer);
                        if(find_free1(factcheer)>0){
                            int count =0;
                            int eat = 0;
                            while(eat==0||eat>count){
                                qDebug()<<"ssssssssssssssssssss";
                                count = eat;
                                for(int i=1;i<6;i++)
                                    for(int j=1;j<6;j++){
                                        if(factcheer[i][j].degree==1){
                                            for(int k=0;k<4;k++){
                                                if(factcheer[i][j].edge[k]=='1'){
                                                    factcheer[i][j].edge[k]='*';
                                                    factcheer[i][j].degree--;
                                                    mutualoccupy1(factcheer, i,j,k);
                                                    getchecksline(i,j,k);
                                                     opc(factcheer, turn);
                                                    chaincount--;
                                                    eat++;
                                                }
                                            }
                                        }
                                    }
                            }
                    goto begin;

                        }
                }

                }

            }


            //判断有没有一个双交破坏两个拐点情况
                int two_fan = 0;
                int guai_x = 0,guai_y = 0;;
                memset(Searched, 0, sizeof(Searched));
                for (int i = 1; i <6; i++)
                {
                    for (int j = 1; j < 6; j++)
                    {

                        if (Triple_Freedom(factcheer, i, j)) {
                            two_fan++;
                            guai_x = i;
                            guai_y = j;
                        }					//Triple_freedem 某三自由度带来交叉的可能为反双交
                    }
                }
                if(two_fan>0&&number%2==0){
                    qDebug()<<"双拐点！！！！！！！！！！！！！！";
                    number = Count_AntDoublecorse(factcheer);
                    chu BeforeDead[61];
                    Situation to[6][6];
                    if(number>0&&number%2==0){
                        int len = move1(factcheer, BeforeDead);//储存招法的数组
                        for(int i = 0;i<len;i++){
                            copy1(factcheer,to);
                            to[BeforeDead[i].x][BeforeDead[i].y].edge[BeforeDead[i].k]='*';
                            to[BeforeDead[i].x][BeforeDead[i].y].degree--;
                            mutualoccupy1(to, BeforeDead[i].x,BeforeDead[i].y,BeforeDead[i].k);
                            int count =0;
                            int eat = 0;
                            while(eat==0||eat>count){
                                count = eat;
                                for(int i=1;i<6;i++)
                                    for(int j=1;j<6;j++){
                                        if(to[i][j].degree==1){
                                            for(int k=0;k<4;k++){
                                                if(to[i][j].edge[k]=='1'){
                                                    to[i][j].edge[k]='*';
                                                    to[i][j].degree--;
                                                    mutualoccupy1(to, i,j,k);
                                                    eat++;
                                                }
                                            }
                                        }
                                    }
                            }

                            BeforeDead[i].lose_box = eat;
                            int later = Count_AntDoublecorse(to);
                            if((eat==2||eat==1)&&later==number-2){
                                factcheer[BeforeDead[i].x][BeforeDead[i].y].edge[BeforeDead[i].k]='*';
                                factcheer[BeforeDead[i].x][BeforeDead[i].y].degree--;
                                mutualoccupy1(factcheer, BeforeDead[i].x,BeforeDead[i].y,BeforeDead[i].k);
                                getchecksline(BeforeDead[i].x,BeforeDead[i].y,BeforeDead[i].k);
                                 opc(factcheer, turn);
                                chaincount--;
                                return;
                            }

                        }

                    }else{
                        qDebug()<<"破坏一个拐点";
                        int len = move1(factcheer, BeforeDead);//储存招法的数组
                        for(int i = 0;i<len;i++){
                            copy1(factcheer,to);
                            to[BeforeDead[i].x][BeforeDead[i].y].edge[BeforeDead[i].k]='*';
                            to[BeforeDead[i].x][BeforeDead[i].y].degree--;
                            mutualoccupy1(to, BeforeDead[i].x,BeforeDead[i].y,BeforeDead[i].k);
                            int count =0;
                            int eat = 0;
                            while(eat==0||eat>count){
                                count = eat;
                                for(int i=1;i<6;i++)
                                    for(int j=1;j<6;j++){
                                        if(to[i][j].degree==1){
                                            for(int k=0;k<4;k++){
                                                if(to[i][j].edge[k]=='1'){
                                                    to[i][j].edge[k]='*';
                                                    to[i][j].degree--;
                                                    mutualoccupy1(to, i,j,k);
                                                    eat++;
                                                }
                                            }
                                        }
                                    }
                            }

                            BeforeDead[i].lose_box = eat;
                            int later = Count_AntDoublecorse(to);
                            if((eat==2||eat==1)&&later==number-1&&!Triple_Freedom(factcheer, guai_x, guai_y)){
                                qDebug()<<"破坏一个拐点333333333333333";
                                factcheer[BeforeDead[i].x][BeforeDead[i].y].edge[BeforeDead[i].k]='*';
                                factcheer[BeforeDead[i].x][BeforeDead[i].y].degree--;
                                mutualoccupy1(factcheer, BeforeDead[i].x,BeforeDead[i].y,BeforeDead[i].k);
                                getchecksline(BeforeDead[i].x,BeforeDead[i].y,BeforeDead[i].k);
                                 opc(factcheer, turn);
                                chaincount--;
                                return;
                    }
                }
            }
                }
                  //先找自由度为3的格子占边
                /*else if(two_fan>0&&num%2==1){
                    num = Count_AntDoublecorse(factcheer);
                    chu BeforeDead[61];
                    Situation to[6][6];
                    if(num>0&&num%2==0){
                        int len = move1(factcheer, BeforeDead);//储存招法的数组
                        for(int i = 0;i<len;i++){
                            copy1(factcheer,to);
                            to[BeforeDead[i].x][BeforeDead[i].y].edge[BeforeDead[i].k]='*';
                            to[BeforeDead[i].x][BeforeDead[i].y].degree--;
                            mutualoccupy1(to, BeforeDead[i].x,BeforeDead[i].y,BeforeDead[i].k);
                            int count =0;
                            int eat = 0;
                            while(eat==0||eat>count){
                                count = eat;
                                for(int i=1;i<6;i++)
                                    for(int j=1;j<6;j++){
                                        if(to[i][j].degree==1){
                                            for(int k=0;k<4;k++){
                                                if(to[i][j].edge[k]=='1'){
                                                    to[i][j].edge[k]='*';
                                                    to[i][j].degree--;
                                                    mutualoccupy1(to, i,j,k);
                                                    eat++;
                                                }
                                            }
                                        }
                                    }
                            }

                            BeforeDead[i].lose_box = eat;
                            int later = Count_AntDoublecorse(to);
                            int two_fan_later = 0;
                            memset(Searched, 0, sizeof(Searched));
                            for (int i = 1; i <6; i++)
                            {
                                for (int j = 1; j < 6; j++)
                                {

                                    if (Triple_Freedom(factcheer, i, j)) {
                                        two_fan_later++;
                                    }					//Triple_freedem 某三自由度带来交叉的可能为反双交
                                }
                            }
                            if((eat==2||eat==1)&&later==num-1&&two_fan_later<two_fan){
                                factcheer[BeforeDead[i].x][BeforeDead[i].y].edge[BeforeDead[i].k]='*';
                                factcheer[BeforeDead[i].x][BeforeDead[i].y].degree--;
                                mutualoccupy1(factcheer, BeforeDead[i].x,BeforeDead[i].y,BeforeDead[i].k);
                                getchecksline(BeforeDead[i].x,BeforeDead[i].y,BeforeDead[i].k);
                                chaincount--;
                                return;
                            }

                        }

                    }
                }*/

        if(number-singlechain-doublechain!=0){


            chu BeforeDead[61];
            Situation to[6][6];
            int len=0;
            for(int i=1;i<6;i++)
                for(int j=1;j<6;j++){
                    if(factcheer[i][j].degree>2){
                        for(int k=0;k<4;k++){
                            if(factcheer[i][j].edge[k]=='1'){
                                BeforeDead[len].x = i;
                                BeforeDead[len].y = j;
                                BeforeDead[len].k = k;
                                len++;
                            }
                        }
                    }
                }
            for(int i = 0;i<len;i++){
                copy1(factcheer,to);
                for(int x=1;x<6;x++)
                    for(int y=1;y<6;y++){
                        if(to[x][y].degree==1){
                            for(int k=0;k<4;k++){
                                if(to[x][y].edge[k]=='1'&&k==0){
                                    if(to[x][y-1].degree!=3){
                                        to[x][y].degree=0;
                                    }
                                }else if(to[x][y].edge[k]=='1'&&k==1){
                                    if(to[x-1][y].degree!=3){
                                        to[x][y].degree=0;
                                    }
                                }else if(to[x][y].edge[k]=='1'&&k==2){
                                    if(to[x][y+1].degree!=3){
                                        to[x][y].degree=0;
                                    }
                                }else if(to[x][y].edge[k]=='1'&&k==3){
                                    if(to[x+1][y].degree!=3){
                                        to[x][y].degree=0;
                                    }
                                }
                            }
                        }
                    }
                to[BeforeDead[i].x][BeforeDead[i].y].edge[BeforeDead[i].k]='*';
                to[BeforeDead[i].x][BeforeDead[i].y].degree--;
                mutualoccupy1(to, BeforeDead[i].x,BeforeDead[i].y,BeforeDead[i].k);
                int count =0;
                int eat = 0;
                while(eat==0||eat>count){
                    count = eat;
                    for(int i=1;i<6;i++)
                        for(int j=1;j<6;j++){
                            if(to[i][j].degree==1){
                                for(int k=0;k<4;k++){
                                    if(to[i][j].edge[k]=='1'){
                                        to[i][j].edge[k]='*';
                                        to[i][j].degree--;
                                        mutualoccupy1(to, i,j,k);
                                        eat++;
                                    }
                                }
                            }
                        }
                }

                BeforeDead[i].lose_box = eat;
            }
            int count =0;
            int choice = 0;
            for(int i=0;i<len;i++){
                if(i==0){count =BeforeDead[i].lose_box;}
                if(BeforeDead[i].lose_box<count){
                    count = BeforeDead[i].lose_box;
                    choice = i;
                }
            }
            copy1(factcheer,to);
            for(int x=1;x<6;x++)
                for(int y=1;y<6;y++){
                    if(to[x][y].degree==1){
                        for(int k=0;k<4;k++){
                            if(to[x][y].edge[k]=='1'&&k==0){
                                if(to[x][y-1].degree!=3){
                                    to[x][y].degree=0;
                                }
                            }else if(to[x][y].edge[k]=='1'&&k==1){
                                if(to[x-1][y].degree!=3){
                                    to[x][y].degree=0;
                                }
                            }else if(to[x][y].edge[k]=='1'&&k==2){
                                if(to[x][y+1].degree!=3){
                                    to[x][y].degree=0;
                                }
                            }else if(to[x][y].edge[k]=='1'&&k==3){
                                if(to[x+1][y].degree!=3){
                                    to[x][y].degree=0;
                                }
                            }
                        }
                    }
                }
            to[BeforeDead[choice].x][BeforeDead[choice].y].edge[BeforeDead[choice].k]='*';
            to[BeforeDead[choice].x][BeforeDead[choice].y].degree--;
            mutualoccupy1(to, BeforeDead[choice].x,BeforeDead[choice].y,BeforeDead[choice].k);
            for(int i=1;i<6;i++)
                for(int j=1;j<6;j++){
                    if(to[i][j].degree==1){
                        for(int k=0;k<4;k++){
                            if(to[i][j].edge[k]=='1'){
                                factcheer[i][j].edge[k]='*';
                                getchecksline(i,j,k);
                                 opc(factcheer, turn);
                                chaincount--;
                                factcheer[i][j].degree--;
                                mutualoccupy1(factcheer,i,j,k);
                            }
                        }
                    }
                }


        }else if(singlechain!=0){
            memset(Searched, 0, sizeof(Searched));
            for (int i = 1; i <6; i++)
            {
                for (int j = 1; j < 6; j++)
                {
                    if (Searched[i][j]) continue;						//说明已经查找过了
                    if (SingleChain(factcheer, i, j)) { //DoubleChain 双链可能成为反双交
                        for(int k=0;k<4;k++){
                            if(factcheer[i][j].edge[k]=='1'){
                                    factcheer[i][j].edge[k]='*';
                                    factcheer[i][j].degree--;
                                    mutualoccupy1(factcheer, i,j,k);
                                    getchecksline(i,j,k);
                                     opc(factcheer, turn);
                                    chaincount--;
                                    return;
                            }
                        }
                    }

                }
            }
        }else if (singlechain==0&&doublechain!=0) {
            int i, j,free3=0;


            free1 = find_free1(factcheer);
            memset(Searched, 0, sizeof(Searched));
            for (i = 1; i <6; i++)
            {
                for (j = 1; j < 6; j++)
                {
                    if (Searched[i][j]) continue;						//说明已经查找过了
                    if (DoubleChain(factcheer, i, j)) { //DoubleChain 双链可能成为反双交
                        for(int k=0;k<4;k++){
                            if(factcheer[i][j].edge[k]=='1'){
                                copy1(factcheer,to);
                                to[i][j].edge[k]='*';
                                to[i][j].degree--;
                                mutualoccupy1(to, i,j,k);
                                int count = find_free3(to);
                                if(count == free3+2){
                                    factcheer[i][j].edge[k]='*';
                                    factcheer[i][j].degree--;
                                    mutualoccupy1(factcheer, i,j,k);
                                    getchecksline(i,j,k);
                                     opc(factcheer, turn);
                                    chaincount--;
                                    return;
                                }
                            }
                        }
                    }

                }
            }
        }/*else if(singlechain==0&&doublechain==0&&num!=0){


            chu BeforeDead[61];
            Situation to[6][6];
            int len=0;
            for(int i=1;i<6;i++)
                for(int j=1;j<6;j++){
                    if(factcheer[i][j].degree>2){
                        for(int k=0;k<4;k++){
                            if(factcheer[i][j].edge[k]=='1'){
                                BeforeDead[len].x = i;
                                BeforeDead[len].y = j;
                                BeforeDead[len].k = k;
                                len++;
                            }
                        }
                    }
                }
            for(int i = 0;i<len;i++){
                copy1(factcheer,to);
                for(int x=1;x<6;x++)
                    for(int y=1;y<6;y++){
                        if(to[x][y].degree==1){
                            for(int k=0;k<4;k++){
                                if(to[x][y].edge[k]=='1'&&k==0){
                                    if(to[x][y-1].degree!=3){
                                        to[x][y].degree=0;
                                    }
                                }else if(to[x][y].edge[k]=='1'&&k==1){
                                    if(to[x-1][y].degree!=3){
                                        to[x][y].degree=0;
                                    }
                                }else if(to[x][y].edge[k]=='1'&&k==2){
                                    if(to[x][y+1].degree!=3){
                                        to[x][y].degree=0;
                                    }
                                }else if(to[x][y].edge[k]=='1'&&k==3){
                                    if(to[x+1][y].degree!=3){
                                        to[x][y].degree=0;
                                    }
                                }
                            }
                        }
                    }
                to[BeforeDead[i].x][BeforeDead[i].y].edge[BeforeDead[i].k]='*';
                to[BeforeDead[i].x][BeforeDead[i].y].degree--;
                mutualoccupy1(to, BeforeDead[i].x,BeforeDead[i].y,BeforeDead[i].k);
                int count =0;
                int eat = 0;
                while(eat==0||eat>count){
                    count = eat;
                    for(int i=1;i<6;i++)
                        for(int j=1;j<6;j++){
                            if(to[i][j].degree==1){
                                for(int k=0;k<4;k++){
                                    if(to[i][j].edge[k]=='1'){
                                        to[i][j].edge[k]='*';
                                        to[i][j].degree--;
                                        mutualoccupy1(to, i,j,k);
                                        eat++;
                                    }
                                }
                            }
                        }
                }

                BeforeDead[i].lose_box = eat;
            }
            int count =0;
            int choice = 0;
            for(int i=0;i<len;i++){
                if(i==0){count =BeforeDead[i].lose_box;}
                if(BeforeDead[i].lose_box<count){
                    count = BeforeDead[i].lose_box;
                    choice = i;
                }
            }
            copy1(factcheer,to);
            for(int x=1;x<6;x++)
                for(int y=1;y<6;y++){
                    if(to[x][y].degree==1){
                        for(int k=0;k<4;k++){
                            if(to[x][y].edge[k]=='1'&&k==0){
                                if(to[x][y-1].degree!=3){
                                    to[x][y].degree=0;
                                }
                            }else if(to[x][y].edge[k]=='1'&&k==1){
                                if(to[x-1][y].degree!=3){
                                    to[x][y].degree=0;
                                }
                            }else if(to[x][y].edge[k]=='1'&&k==2){
                                if(to[x][y+1].degree!=3){
                                    to[x][y].degree=0;
                                }
                            }else if(to[x][y].edge[k]=='1'&&k==3){
                                if(to[x+1][y].degree!=3){
                                    to[x][y].degree=0;
                                }
                            }
                        }
                    }
                }
            to[BeforeDead[choice].x][BeforeDead[choice].y].edge[BeforeDead[choice].k]='*';
            to[BeforeDead[choice].x][BeforeDead[choice].y].degree--;
            mutualoccupy1(to, BeforeDead[choice].x,BeforeDead[choice].y,BeforeDead[choice].k);
            for(int i=1;i<6;i++)
                for(int j=1;j<6;j++){
                    if(to[i][j].degree==1){
                        for(int k=0;k<4;k++){
                            if(to[i][j].edge[k]=='1'){
                                factcheer[i][j].edge[k]='*';
                                getchecksline(i,j,k);
                                chaincount--;
                                factcheer[i][j].degree--;
                                mutualoccupy1(factcheer,i,j,k);
                            }
                        }
                    }
                }


        }*/

    }else{
        qDebug()<<"2222222222";
        for(int i=1;i<6;i++)
            for(int j=1;j<6;j++){
                int count = 0;
                for(int k=0;k<4;k++){
                    if(factcheer[i][j].edge[k]=='1'){
                        count++;
                    }
                }
                factcheer[i][j].degree = count;
            }

        Final_Occupy(factcheer, turn);
    }
line_end: qDebug()<<"下完，来到这了";

}





//相互占领边函数，减去 领边自由度(自己边已经在占边的时候减去自由度了)
void AI::mutualoccupy1(Situation Square[6][6], int x, int y, int k)
{


    if (x == 1 && y == 1)
    {
        if (k == 2 && Square[x][y].edge[k] != '1')
        {
            Square[x][y + 1].edge[0] = Square[x][y].edge[2];  Square[x][y + 1].degree--;
        }
        if (k == 3 && Square[x][y].edge[3] != '1')
        {
            Square[x + 1][y].edge[1] = Square[x][y].edge[3];  Square[x + 1][y].degree--;
        }
    }
    else if (x == 1 && y == 5)
    {
        if (k == 0 && Square[x][y].edge[k] != '1')
        {
            Square[x][y - 1].edge[2] = Square[x][y].edge[0]; Square[x][y - 1].degree--;
        }
        if (k == 3 && Square[x][y].edge[k] != '1')
        {
            Square[x + 1][y].edge[1] = Square[x][y].edge[3];  Square[x + 1][y].degree--;
        }
    }
    else if (x == 5 && y == 1)
    {
        if (k == 2 && Square[x][y].edge[k] != '1')
        {
            Square[x][y + 1].edge[0] = Square[x][y].edge[2]; Square[x][y + 1].degree--;
        }
        if (k == 1 && Square[x][y].edge[k] != '1')
        {
            Square[x - 1][y].edge[3] = Square[x][y].edge[1]; Square[x - 1][y].degree--;
        }
    }
    else if (x == 5 && y == 5)
    {
        if (k == 0 && Square[x][y].edge[k] != '1')
        {
            Square[x][y - 1].edge[2] = Square[x][y].edge[0];  Square[x][y - 1].degree--;
        }
        if (k == 1 && Square[x][y].edge[k] != '1')
        {
            Square[x - 1][y].edge[3] = Square[x][y].edge[1];  Square[x - 1][y].degree--;
        }
    }                                                               ///////////////四个角

    else if ((x == 2 || x == 3 || x == 4) && y == 1)
    {
        if (k == 1 && Square[x][y].edge[k] != '1')
        {
            Square[x - 1][y].edge[3] = Square[x][y].edge[1];  Square[x - 1][y].degree--;
        }
        if (k == 3 && Square[x][y].edge[k] != '1')
        {
            Square[x + 1][y].edge[1] = Square[x][y].edge[3];  Square[x + 1][y].degree--;
        }
        if (k == 2 && Square[x][y].edge[k] != '1')
        {
            Square[x][y + 1].edge[0] = Square[x][y].edge[2];   Square[x][y + 1].degree--;
        }
    }
    else if ((x == 2 || x == 3 || x == 4) && y == 5)
    {
        if (k == 1 && Square[x][y].edge[k] != '1')
        {
            Square[x - 1][y].edge[3] = Square[x][y].edge[1];  Square[x - 1][y].degree--;
        }
        if (k == 3 && Square[x][y].edge[k] != '1')
        {
            Square[x + 1][y].edge[1] = Square[x][y].edge[3]; Square[x + 1][y].degree--;
        }
        if (k == 0 && Square[x][y].edge[k] != '1')
        {
            Square[x][y - 1].edge[2] = Square[x][y].edge[0];   Square[x][y - 1].degree--;
        }
    }
    else if ((y == 2 || y == 3 || y == 4) && x == 1)
    {
        if (k == 2 && Square[x][y].edge[k] != '1')
        {
            Square[x][y + 1].edge[0] = Square[x][y].edge[2];  Square[x][y + 1].degree--;
        }
        if (k == 3 && Square[x][y].edge[k] != '1')
        {
            Square[x + 1][y].edge[1] = Square[x][y].edge[3]; Square[x + 1][y].degree--;
        }
        if (k == 0 && Square[x][y].edge[k] != '1')
        {
            Square[x][y - 1].edge[2] = Square[x][y].edge[0];  Square[x][y - 1].degree--;
        }
    }
    else if ((y == 2 || y == 3 || y == 4) && x == 5)
    {
        if (k == 2 && Square[x][y].edge[k] != '1')
        {
            Square[x][y + 1].edge[0] = Square[x][y].edge[2];  Square[x][y + 1].degree--;
        }
        if (k == 1 && Square[x][y].edge[k] != '1')
        {
            Square[x - 1][y].edge[3] = Square[x][y].edge[1]; Square[x - 1][y].degree--;
        }
        if (k == 0 && Square[x][y].edge[k] != '1')
        {
            Square[x][y - 1].edge[2] = Square[x][y].edge[0];  Square[x][y - 1].degree--;
        }
    }

    else if (x>1 && x <5 && y>1 && y<5)
    {
        if (k == 0 && Square[x][y].edge[k] != '1')
        {
            Square[x][y - 1].edge[2] = Square[x][y].edge[0];  Square[x][y - 1].degree--;
        }
        if (k == 2 && Square[x][y].edge[k] != '1')
        {
            Square[x][y + 1].edge[0] = Square[x][y].edge[2];  Square[x][y + 1].degree--;
        }
        if (k == 1 && Square[x][y].edge[k] != '1')
        {
            Square[x - 1][y].edge[3] = Square[x][y].edge[1];  Square[x - 1][y].degree--;
        }
        if (k == 3 && Square[x][y].edge[k] != '1')
        {
            Square[x + 1][y].edge[1] = Square[x][y].edge[3];  Square[x + 1][y].degree--;
        }
    }
}

void AI::mutualoccupy2(Situation Square[6][6], int x, int y, int k)
{


    if (x == 1 && y == 1)
    {
        if (k == 2 && Square[x][y].edge[k] == '1')
        {
            Square[x][y + 1].edge[0] = Square[x][y].edge[2];  Square[x][y + 1].degree++;
        }
        if (k == 3 && Square[x][y].edge[3] == '1')
        {
            Square[x + 1][y].edge[1] = Square[x][y].edge[3];  Square[x + 1][y].degree++;
        }
    }
    else if (x == 1 && y == 5)
    {
        if (k == 0 && Square[x][y].edge[k] == '1')
        {
            Square[x][y - 1].edge[2] = Square[x][y].edge[0]; Square[x][y - 1].degree++;
        }
        if (k == 3 && Square[x][y].edge[k] == '1')
        {
            Square[x + 1][y].edge[1] = Square[x][y].edge[3];  Square[x + 1][y].degree++;
        }
    }
    else if (x == 5 && y == 1)
    {
        if (k == 2 && Square[x][y].edge[k] == '1')
        {
            Square[x][y + 1].edge[0] = Square[x][y].edge[2]; Square[x][y + 1].degree++;
        }
        if (k == 1 && Square[x][y].edge[k] == '1')
        {
            Square[x - 1][y].edge[3] = Square[x][y].edge[1]; Square[x - 1][y].degree++;
        }
    }
    else if (x == 5 && y == 5)
    {
        if (k == 0 && Square[x][y].edge[k] == '1')
        {
            Square[x][y - 1].edge[2] = Square[x][y].edge[0];  Square[x][y - 1].degree++;
        }
        if (k == 1 && Square[x][y].edge[k] == '1')
        {
            Square[x - 1][y].edge[3] = Square[x][y].edge[1];  Square[x - 1][y].degree++;
        }
    }                                                               ///////////////四个角

    else if ((x == 2 || x == 3 || x == 4) && y == 1)
    {
        if (k == 1 && Square[x][y].edge[k] == '1')
        {
            Square[x - 1][y].edge[3] = Square[x][y].edge[1];  Square[x - 1][y].degree++;
        }
        if (k == 3 && Square[x][y].edge[k] == '1')
        {
            Square[x + 1][y].edge[1] = Square[x][y].edge[3];  Square[x + 1][y].degree++;
        }
        if (k == 2 && Square[x][y].edge[k] == '1')
        {
            Square[x][y + 1].edge[0] = Square[x][y].edge[2];   Square[x][y + 1].degree++;
        }
    }
    else if ((x == 2 || x == 3 || x == 4) && y == 5)
    {
        if (k == 1 && Square[x][y].edge[k] == '1')
        {
            Square[x - 1][y].edge[3] = Square[x][y].edge[1];  Square[x - 1][y].degree++;
        }
        if (k == 3 && Square[x][y].edge[k] == '1')
        {
            Square[x + 1][y].edge[1] = Square[x][y].edge[3]; Square[x + 1][y].degree++;
        }
        if (k == 0 && Square[x][y].edge[k] == '1')
        {
            Square[x][y - 1].edge[2] = Square[x][y].edge[0];   Square[x][y - 1].degree++;
        }
    }
    else if ((y == 2 || y == 3 || y == 4) && x == 1)
    {
        if (k == 2 && Square[x][y].edge[k] == '1')
        {
            Square[x][y + 1].edge[0] = Square[x][y].edge[2];  Square[x][y + 1].degree++;
        }
        if (k == 3 && Square[x][y].edge[k] == '1')
        {
            Square[x + 1][y].edge[1] = Square[x][y].edge[3]; Square[x + 1][y].degree++;
        }
        if (k == 0 && Square[x][y].edge[k] == '1')
        {
            Square[x][y - 1].edge[2] = Square[x][y].edge[0];  Square[x][y - 1].degree++;
        }
    }
    else if ((y == 2 || y == 3 || y == 4) && x == 5)
    {
        if (k == 2 && Square[x][y].edge[k] == '1')
        {
            Square[x][y + 1].edge[0] = Square[x][y].edge[2];  Square[x][y + 1].degree++;
        }
        if (k == 1 && Square[x][y].edge[k] == '1')
        {
            Square[x - 1][y].edge[3] = Square[x][y].edge[1]; Square[x - 1][y].degree++;
        }
        if (k == 0 && Square[x][y].edge[k] == '1')
        {
            Square[x][y - 1].edge[2] = Square[x][y].edge[0];  Square[x][y - 1].degree++;
        }
    }                                           /////////////四条边

    else if (x>1 && x <5 && y>1 && y<5)
    {
        if (k == 0 && Square[x][y].edge[k] == '1')
        {
            Square[x][y - 1].edge[2] = Square[x][y].edge[0];  Square[x][y - 1].degree++;
        }
        if (k == 2 && Square[x][y].edge[k] == '1')
        {
            Square[x][y + 1].edge[0] = Square[x][y].edge[2];  Square[x][y + 1].degree++;
        }
        if (k == 1 && Square[x][y].edge[k] == '1')
        {
            Square[x - 1][y].edge[3] = Square[x][y].edge[1];  Square[x - 1][y].degree++;
        }
        if (k == 3 && Square[x][y].edge[k] == '1')
        {
            Square[x + 1][y].edge[1] = Square[x][y].edge[3];  Square[x + 1][y].degree++;
        }
    }
}

bool AI::Method1(Situation square[6][6], int turn) {
    bool occupyed = false;
    return  occupyed;
}

int AI::Search(int deep, int alpha, int beta, int turn)
{
    int score = 0, MAX = 0, MIN = 0;
    int HorV;
    int len;
    int i, j;
    int x, y;
    chu Movelist[61];									//储存招法的数组
    len = move(factcheer, Movelist);											//招法生成


    if (deep == 1)
    {
        leni = len;
    }

    if (leni>Max_len)
    {
        if (deep == Max_deep)
        {
            return Evaluation(factcheer, turn);

        }
    }
    if (leni <= Max_len)
    {
        alpha = -50; beta = 50;
        if (Dead(factcheer))
        {
            return Evaluation(factcheer, turn);
        }
    }

    if (turn == myturn)                                      //我方下子，取极大值
    {
        for (i = 0; i<len; i++)
        {
            int x, y, k;

            x = Movelist[i].x;
            y = Movelist[i].y;
            k = Movelist[i].k;
            factcheer[x][y].edge[k] = '%';

            factcheer[x][y].degree--;
            mutualoccupy1(factcheer, x, y, k);


            score = Search(deep + 1, alpha, beta, !turn);


            //撤销招法
            factcheer[x][y].edge[k] = '1';
            factcheer[x][y].degree++;
            mutualoccupy2(factcheer, x, y, k);
            if (leni>Max_len&&deep == Max_deep - 1)
            {

                MAX += score;
                score = MAX;

                if (i != len - 1)
                    continue;
            }
            if (deep == 1) {

            }


            if (score >= alpha)                              //score
            {
                alpha = score;                     //score
                if (deep == 1)
                {

                    Bestmove = Movelist[i];
                }

                if (alpha >= beta)
                {
                    return score;		//beta剪枝
                }
            }
        }
        return score;
    }
    else
    {
        for (j = 0; j<len; j++)
        {
            int x, y, k;

            x = Movelist[j].x;
            y = Movelist[j].y;
            k = Movelist[j].k;
            factcheer[x][y].edge[k] = '%';
            factcheer[x][y].degree--;
            mutualoccupy1(factcheer, x, y, k);


            score = Search(deep + 1, alpha, beta, !turn);


            //撤销招法
            factcheer[x][y].edge[k] = '1';
            factcheer[x][y].degree++;
            mutualoccupy2(factcheer, x, y, k);

            if (leni>Max_len&&deep == Max_deep - 1)
            {
                MIN += score;
                score = MIN;
                if (j != len - 1)
                    continue;
            }

            if (score <= beta)
            {
                beta = score;
            }
            if (alpha >= beta)
            {
                return score;	//alpha剪枝
            }
        }
        return score;
    }
}

int AI::Search1(int deep, int alpha, int beta, int turn)
{
    int score = 0, MAX = 0, MIN = 0;

    int len;
    int i, j;

    chu Movelist[61];									//储存招法的数组
    len = move(factcheer, Movelist);											//招法生成


    if (deep == 1)
    {

        leni = len;
    }

    if(len==0){
        return Evaluation(factcheer, turn);  //返回-50或50或。。。。
    }

    if (leni>Max_len)
    {
        if (deep == Max_deep)
        {

            return Evaluation(factcheer, turn);  //返回-50或50或。。。。

        }
    }
    if (leni <= Max_len)
    {
        alpha = -50; beta = 50;
        if (Dead(factcheer))
        {
            return Evaluation(factcheer, turn);
        }
    }

    if (turn != myturn)                                      //我方下子，取极大值
    {
        for (i = 0; i<len; i++)
        {
            int x, y, k;

            x = Movelist[i].x;
            y = Movelist[i].y;
            k = Movelist[i].k;
            factcheer[x][y].edge[k] = '%';
            factcheer[x][y].degree--;
            mutualoccupy1(factcheer, x, y, k);


            score = Search1(deep + 1, alpha, beta, !turn);


            //撤销招法
            factcheer[x][y].edge[k] = '1';
            factcheer[x][y].degree++;
            mutualoccupy2(factcheer, x, y, k);
            if (leni>Max_len&&deep == Max_deep - 1)
            {

                MAX += score;
                score = MAX;

                if (i != len - 1)
                    continue;
            }
            if (deep == 1) {

            }


            if (score >= alpha)                              //score
            {
                alpha = score;                     //score
                if (deep == 1)
                {

                    Bestmove = Movelist[i];
                }

                if (alpha >= beta)
                {
                    return score;		//beta剪枝
                }
            }
        }
        return score;
    }
    else
    {
        for (j = 0; j<len; j++)
        {
            int x, y, k;

            x = Movelist[j].x;
            y = Movelist[j].y;
            k = Movelist[j].k;
            factcheer[x][y].edge[k] = '%';
            factcheer[x][y].degree--;
            mutualoccupy1(factcheer, x, y, k);


            score = Search1(deep + 1, alpha, beta, !turn);


            //撤销招法
            factcheer[x][y].edge[k] = '1';
            factcheer[x][y].degree++;
            mutualoccupy2(factcheer, x, y, k);

            if (leni>Max_len&&deep == Max_deep - 1)
            {
                MIN += score;
                score = MIN;
                if (j != len - 1)
                    continue;
            }

            if (score <= beta)
            {
                beta = score;
            }
            if (alpha >= beta)
            {
                return score;	//alpha剪枝
            }
        }
        return score;
    }
}

int AI::click(int row, int col)   //与对手交互
{
    if(choice==1)
    {
        QTimer::singleShot(100, this, SLOT(AIMove()));
        //执行完一次后，变为我先，敌方后
        choice=2;
    }else{
    int next=Widget::click(row,col);

    if(next==1)
    {

    //将所下边转换为 格子边,在传给 11*11
    if(_clickid!=0)
    {
        int pt =getcheerrowcol(tempselect,tempclick);
        turn--;
        putcheer(factcheer,tempselect,tempclick,pt,turn);
        chaincount--;

    }

    //人工智能下棋；
    /*
     * 线程稳定度修改
     * 由于之前采用的是旧的线程处理函数,需要将搜索树搜索的整体算法写到另一个线程的待运行函数中
     * 这样,程序兼容性很低,在一些预先算法估算不到的情况下,就算提前采用了时间卡死,但是该线程依旧会继续运行
     * 从而与主线程产生冲突,造成线程占用,由此导致主界面卡死
     * 如今,将搜索树搜索算法并入主线程中,时间卡死后,线程就会强制停止,从而极大地避免了程序提前崩溃
     *
*/
    if(ai_thread1.isRunning())
    {
        qDebug()<<"线程正在运行";
        QMessageBox::about(this,"提示","正在思考，请勿点击");
        Widget::on_whitecancel_clicked();
    }else{
        //获取
        auto func =[&](){
            ContinueEat();
        };

        if(isback==true)
        {
            int times=(temp_backcount-backcount)/2;
            chaincount=chaincount+2*times;
            temp_backcount=backcount;
            isback=false;
        }

        qDebug()<<"进入线程";
        ai_thread1.wait();
        ai_thread1.setCallback(func);
        qDebug()<<"执行setCallback";
        ai_thread1.start();
        qDebug()<<"执行start";
    }
    }
  //  update();
    Winner();


}

}

void AI::ContinueEat()
{
    if(player==true)
    {
        do
        {
            //在线程里不要进行赋值等操作。。
            go=false;
            /* 启动0.1秒定时器，在0.1秒后电脑再思考 */
            qDebug()<<"当前下棋者:"<<player;
            qDebug()<<"是否机器继续下棋"<<go;
            AIMove();
            qDebug()<<"go的值"<<go;
        }while(go==true);
    }
}

void AI::AIMove()
{
    //调用下棋函数
    Order(factcheer, myturn, turn);


    //再次初始化
    tempselect=0;
    tempclick=0;


}

void AI::getchecksline(int x,int y,int k)
{
    //估值格子下标从1 开始
    //求边的两点

    int pt1,pt2;

    if(k==0)        //左边
    {
        pt1=6*(x-1)+y-1;
        pt2=6*x+y-1;
    }else if(k==1)   //上边
    {
        pt1=6*(x-1)+y-1;
        pt2=6*(x-1)+y;
    }else if(k==2)  //右边
    {
        pt1=6*(x-1)+y;
        pt2=6*x+y;
    }else if(k==3)  //下边
    {
        pt1=6*x+y-1;
        pt2=6*x+y;
    }

    //调用绘图数格子
    Widget::click(pt1);
    Widget::click(pt2);
   // update();
   // Winner();


}

int AI::getcheerrowcol(int select,int click)
{
    int x,y,k;
    if(select-click==1 || select-click==-1)
    {
        //同行
        if(select<click)
        {
            x=(select/6)+1;
            y=(select%6)+1;
            k=1;
            if(x==6)
            {
                x--;
                k=3;
            }
        }else
        {
            x=(click/6)+1;
            y=(click%6)+1;
            k=1;
            if(x==6)   //最底行
            {
                x--;
                k=3;
            }
        }
    }

    if(select-click==6 || select-click==-6)
    {
        //同列
        if(select>click)
        {
            x=(select/6);
            y=(select%6)+1;
            k=0;
            if(y==6)    //最右列
            {
                y--;
                k=2;
            }
        }else
        {
            x=(click/6);
            y=(click%6)+1;
            k=0;
            if(y==6)    //最右列
            {
                y--;
                k=2;
            }
        }
    }

    //得到 x,y,k的值，return
    tempselect=x;
    tempclick=y;
    return k;
}

void AI::action_move(Situation Square[6][6], bool myturn){
    int x,y,k;

    //左上
    if(Square[1][1].edge[2] == '1' && Square[1][1].edge[3] == '1' && Square[1][1].degree > 2){
        if((Square[2][2].edge[2] == '1' && Square[2][2].edge[3] == '1' && Square[2][2].degree >1) || (Square[2][2].edge[0] != '1' && Square[2][2].edge[1] != '1')){
            if(Square[1][2].edge[1] == '1' && Square[2][1].edge[0] == '1'){
                if(Square[1][3].degree > 2 || Square[1][3].edge[0] != '1' ){
                    if(Square[3][1].degree > 2 || Square[3][1].edge[1] != '1'){
                        if(Square[2][1].edge[3] == '1'){
                            x = 2;
                            y = 1;
                            k = 3;
                            putcheer(Square,x,y,k,myturn);
                            getchecksline(x,y,k);
                            return ;
                        }
                        if(Square[1][2].edge[2] == '1'){
                            x = 1;
                            y = 2;
                            k = 2;
                            putcheer(Square,x,y,k,myturn);
                            getchecksline(x,y,k);
                            return ;
                        }
                        if(Square[2][1].edge[2] == '1'){
                            x = 2;
                            y = 1;
                            k = 2;
                            putcheer(Square,x,y,k,myturn);
                            getchecksline(x,y,k);
                            return ;
                        }
                        if(Square[1][2].edge[3] == '1'){
                            x = 1;
                            y = 2;
                            k = 3;
                            putcheer(Square,x,y,k,myturn);
                            getchecksline(x,y,k);
                            return ;
                        }
                    }
                }
            }
            else if((Square[1][2].edge[1] != '1' && Square[2][1].edge[0] == '1') || (Square[1][2].edge[1] == '1' && Square[2][1].edge[0] != '1')){
                if(Square[1][2].edge[1] != '1' && Square[2][1].edge[0] == '1'){
                    if(Square[1][3].edge[0] == '1' && Square[1][3].edge[1] == '1'){
                        if(Square[1][4].degree > 1 || Square[1][4].edge[0] != '1'){
                            if(Square[3][1].degree > 1 || Square[3][1].edge[1] != '1'){
                                if(Square[2][3].degree > 1 || Square[2][3].edge[1] != '1'){
                                    if(Square[1][3].edge[2] == '1'){
                                        x = 1;
                                        y = 3;
                                        k = 2;
                                        putcheer(Square,x,y,k,myturn);
                                        getchecksline(x,y,k);
                                        return ;
                                    }
                                    if(Square[2][1].edge[3] == '1'){
                                        x = 2;
                                        y = 1;
                                        k = 3;
                                        putcheer(Square,x,y,k,myturn);
                                        getchecksline(x,y,k);
                                        return ;
                                    }
                                    if(Square[1][2].edge[3] == '1'){
                                        x = 1;
                                        y = 2;
                                        k = 3;
                                        putcheer(Square,x,y,k,myturn);
                                        getchecksline(x,y,k);
                                        return ;
                                    }
                                    if(Square[1][3].edge[3] == '1'){
                                        x = 1;
                                        y = 3;
                                        k = 3;
                                        putcheer(Square,x,y,k,myturn);
                                        getchecksline(x,y,k);
                                        return ;
                                    }
                                    if(Square[2][1].edge[2] == '1'){
                                        x = 2;
                                        y = 1;
                                        k = 2;
                                        putcheer(Square,x,y,k,myturn);
                                        getchecksline(x,y,k);
                                        return ;
                                    }
                                }
                            }
                        }
                    }
                }
                if(Square[1][2].edge[1] == '1' && Square[2][1].edge[0] != '1'){
                    if(Square[3][1].edge[0] == '1' && Square[3][1].edge[1] == '1'){
                        if(Square[4][1].degree > 1 || Square[4][1].edge[1] != '1'){
                            if(Square[1][3].degree > 1 || Square[1][3].edge[2] != '1'){
                                if(Square[3][2].degree > 1 || Square[3][2].edge[0] != '1'){
                                    if(Square[3][1].edge[3] == '1'){
                                        x = 3;
                                        y = 1;
                                        k = 3;
                                        putcheer(Square,x,y,k,myturn);
                                        getchecksline(x,y,k);
                                        return ;
                                    }
                                    if(Square[1][2].edge[2] == '1'){
                                        x = 1;
                                        y = 2;
                                        k = 2;
                                        putcheer(Square,x,y,k,myturn);
                                        getchecksline(x,y,k);
                                        return ;
                                    }
                                    if(Square[2][1].edge[2] == '1'){
                                        x = 2;
                                        y = 1;
                                        k = 2;
                                        putcheer(Square,x,y,k,myturn);
                                        getchecksline(x,y,k);
                                        return ;
                                    }
                                    if(Square[3][1].edge[2] == '1'){
                                        x = 3;
                                        y = 1;
                                        k = 2;
                                        putcheer(Square,x,y,k,myturn);
                                        getchecksline(x,y,k);
                                        return ;
                                    }
                                    if(Square[1][2].edge[3] == '1'){
                                        x = 1;
                                        y = 2;
                                        k = 3;
                                        putcheer(Square,x,y,k,myturn);
                                        getchecksline(x,y,k);
                                        return ;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    //右上
    if(Square[1][5].edge[0] == '1' && Square[1][5].edge[3] == '1' && Square[1][5].degree > 2){
        if((Square[2][4].edge[0] == '1' && Square[2][4].edge[3] == '1' && Square[2][4].degree >1) || (Square[2][4].edge[0] != '1' && Square[2][4].edge[3] != '1')){
            if(Square[1][4].edge[1] == '1' && Square[2][5].edge[2] == '1'){
                if(Square[1][3].degree > 2 || Square[1][3].edge[2] != '1' ){
                    if(Square[3][5].degree > 2 || Square[3][5].edge[1] != '1'){
                        if(Square[1][4].edge[0] == '1'){
                            x = 1;
                            y = 4;
                            k = 0;
                            putcheer(Square,x,y,k,myturn);
                            getchecksline(x,y,k);
                            return ;
                        }
                        if(Square[2][5].edge[3] == '1'){
                            x = 2;
                            y = 5;
                            k = 3;
                            putcheer(Square,x,y,k,myturn);
                            getchecksline(x,y,k);
                            return ;
                        }
                        if(Square[1][4].edge[3] == '1'){
                            x = 1;
                            y = 4;
                            k = 3;
                            putcheer(Square,x,y,k,myturn);
                            getchecksline(x,y,k);
                            return ;
                        }
                        if(Square[2][5].edge[0] == '1'){
                            x = 2;
                            y = 5;
                            k = 0;
                            putcheer(Square,x,y,k,myturn);
                            getchecksline(x,y,k);
                            return ;
                        }
                    }
                }
            }
            else if((Square[1][4].edge[1] != '1' && Square[2][5].edge[2] == '1') || (Square[1][4].edge[1] == '1' && Square[2][5].edge[2] != '1')){
                if(Square[1][4].edge[1] != '1' && Square[2][5].edge[2] == '1'){
                    if(Square[1][3].edge[1] == '1' && Square[1][3].edge[2] == '1'){
                        if(Square[1][2].degree > 1 || Square[1][2].edge[2] != '1'){
                            if(Square[3][5].degree > 1 || Square[3][5].edge[1] != '1'){
                                if(Square[2][3].degree > 1 || Square[2][3].edge[1] != '1'){
                                    if(Square[1][3].edge[0] == '1'){
                                        x = 1;
                                        y = 3;
                                        k = 0;
                                        putcheer(Square,x,y,k,myturn);
                                        getchecksline(x,y,k);
                                        return ;
                                    }
                                    if(Square[2][5].edge[3] == '1'){
                                        x = 2;
                                        y = 5;
                                        k = 3;
                                        putcheer(Square,x,y,k,myturn);
                                        getchecksline(x,y,k);
                                        return ;
                                    }
                                    if(Square[1][4].edge[3] == '1'){
                                        x = 1;
                                        y = 4;
                                        k = 3;
                                        putcheer(Square,x,y,k,myturn);
                                        getchecksline(x,y,k);
                                        return ;
                                    }
                                    if(Square[1][3].edge[3] == '1'){
                                        x = 1;
                                        y = 3;
                                        k = 3;
                                        putcheer(Square,x,y,k,myturn);
                                        getchecksline(x,y,k);
                                        return ;
                                    }
                                    if(Square[2][5].edge[0] == '1'){
                                        x = 2;
                                        y = 5;
                                        k = 0;
                                        putcheer(Square,x,y,k,myturn);
                                        getchecksline(x,y,k);
                                        return ;
                                    }
                                }
                            }
                        }
                    }
                }
                if(Square[1][4].edge[1] == '1' && Square[2][5].edge[2] != '1'){
                    if(Square[3][5].edge[1] == '1' && Square[3][5].edge[2] == '1'){
                        if(Square[4][5].degree > 1 || Square[4][5].edge[1] != '1'){
                            if(Square[1][3].degree > 1 || Square[1][3].edge[2] != '1'){
                                if(Square[3][4].degree > 1 || Square[3][4].edge[2] != '1'){
                                    if(Square[3][5].edge[3] == '1'){
                                        x = 3;
                                        y = 5;
                                        k = 3;
                                        putcheer(Square,x,y,k,myturn);
                                        getchecksline(x,y,k);
                                        return ;
                                    }
                                    if(Square[1][4].edge[0] == '1'){
                                        x = 1;
                                        y = 4;
                                        k = 0;
                                        putcheer(Square,x,y,k,myturn);
                                        getchecksline(x,y,k);
                                        return ;
                                    }
                                    if(Square[2][5].edge[0] == '1'){
                                        x = 2;
                                        y = 5;
                                        k = 0;
                                        putcheer(Square,x,y,k,myturn);
                                        getchecksline(x,y,k);
                                        return ;
                                    }
                                    if(Square[3][5].edge[0] == '1'){
                                        x = 3;
                                        y = 5;
                                        k = 0;
                                        putcheer(Square,x,y,k,myturn);
                                        getchecksline(x,y,k);
                                        return ;
                                    }
                                    if(Square[1][4].edge[3] == '1'){
                                        x = 1;
                                        y = 4;
                                        k = 3;
                                        putcheer(Square,x,y,k,myturn);
                                        getchecksline(x,y,k);
                                        return ;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    //左下
    if(Square[5][1].edge[1] == '1' && Square[5][1].edge[2] == '1' && Square[5][1].degree > 2){
        if((Square[4][2].edge[1] == '1' && Square[4][2].edge[2] == '1' && Square[4][2].degree >1) || (Square[4][2].edge[1] != '1' && Square[4][2].edge[2] != '1')){
            if(Square[4][1].edge[0] == '1' && Square[5][2].edge[3] == '1'){
                if(Square[3][1].degree > 2 || Square[3][1].edge[3] != '1' ){
                    if(Square[5][3].degree > 2 || Square[5][3].edge[0] != '1'){
                        if(Square[4][1].edge[1] == '1'){
                            x = 4;
                            y = 1;
                            k = 1;
                            putcheer(Square,x,y,k,myturn);
                            getchecksline(x,y,k);
                            return ;
                        }
                        if(Square[5][2].edge[2] == '1'){
                            x = 5;
                            y = 2;
                            k = 2;
                            putcheer(Square,x,y,k,myturn);
                            getchecksline(x,y,k);
                            return ;
                        }
                        if(Square[4][1].edge[2] == '1'){
                            x = 4;
                            y = 1;
                            k = 2;
                            putcheer(Square,x,y,k,myturn);
                            getchecksline(x,y,k);
                            return ;
                        }
                        if(Square[5][2].edge[1] == '1'){
                            x = 5;
                            y = 2;
                            k = 1;
                            putcheer(Square,x,y,k,myturn);
                            getchecksline(x,y,k);
                            return ;
                        }
                    }
                }
            }
            else if((Square[4][1].edge[0] != '1' && Square[5][2].edge[3] == '1') || (Square[4][1].edge[0] == '1' && Square[5][2].edge[3] != '1')){
                if(Square[4][1].edge[0] != '1' && Square[5][2].edge[3] == '1'){
                    if(Square[3][1].edge[0] == '1' && Square[3][1].edge[3] == '1'){
                        if(Square[2][1].degree > 1 || Square[2][1].edge[3] != '1'){
                            if(Square[5][3].degree > 1 || Square[5][3].edge[1] != '1'){
                                if(Square[3][2].degree > 1 || Square[3][2].edge[0] != '1'){
                                    if(Square[3][1].edge[1] == '1'){
                                        x = 3;
                                        y = 1;
                                        k = 1;
                                        putcheer(Square,x,y,k,myturn);
                                        getchecksline(x,y,k);
                                        return ;
                                    }
                                    if(Square[5][2].edge[2] == '1'){
                                        x = 5;
                                        y = 2;
                                        k = 2;
                                        putcheer(Square,x,y,k,myturn);
                                        getchecksline(x,y,k);
                                        return ;
                                    }
                                    if(Square[4][1].edge[2] == '1'){
                                        x = 4;
                                        y = 1;
                                        k = 2;
                                        putcheer(Square,x,y,k,myturn);
                                        getchecksline(x,y,k);
                                        return ;
                                    }
                                    if(Square[3][1].edge[2] == '1'){
                                        x = 3;
                                        y = 1;
                                        k = 2;
                                        putcheer(Square,x,y,k,myturn);
                                        getchecksline(x,y,k);
                                        return ;
                                    }
                                    if(Square[5][2].edge[1] == '1'){
                                        x = 5;
                                        y = 2;
                                        k = 1;
                                        putcheer(Square,x,y,k,myturn);
                                        getchecksline(x,y,k);
                                        return ;
                                    }
                                }
                            }
                        }
                    }
                }
                if(Square[4][1].edge[0] == '1' && Square[5][2].edge[3] != '1'){
                    if(Square[5][3].edge[0] == '1' && Square[5][3].edge[3] == '1'){
                        if(Square[5][4].degree > 1 || Square[5][4].edge[0] != '1'){
                            if(Square[3][1].degree > 1 || Square[3][1].edge[3] != '1'){
                                if(Square[4][3].degree > 1 || Square[4][3].edge[3] != '1'){
                                    if(Square[5][3].edge[2] == '1'){
                                        x = 5;
                                        y = 3;
                                        k = 2;
                                        putcheer(Square,x,y,k,myturn);
                                        getchecksline(x,y,k);
                                        return ;
                                    }
                                    if(Square[4][1].edge[1] == '1'){
                                        x = 4;
                                        y = 1;
                                        k = 1;
                                        putcheer(Square,x,y,k,myturn);
                                        getchecksline(x,y,k);
                                        return ;
                                    }
                                    if(Square[5][2].edge[1] == '1'){
                                        x = 5;
                                        y = 2;
                                        k = 1;
                                        putcheer(Square,x,y,k,myturn);
                                        getchecksline(x,y,k);
                                        return ;
                                    }
                                    if(Square[5][3].edge[1] == '1'){
                                        x = 5;
                                        y = 3;
                                        k = 1;
                                        putcheer(Square,x,y,k,myturn);
                                        getchecksline(x,y,k);
                                        return ;
                                    }
                                    if(Square[4][1].edge[2] == '1'){
                                        x = 4;
                                        y = 1;
                                        k = 1;
                                        putcheer(Square,x,y,k,myturn);
                                        getchecksline(x,y,k);
                                        return ;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    //右下
    if(Square[5][5].edge[0] == '1' && Square[5][5].edge[1] == '1' && Square[5][5].degree > 2){
        if((Square[4][4].edge[0] == '1' && Square[4][4].edge[1] == '1' && Square[4][4].degree >1) || (Square[4][4].edge[0] != '1' && Square[4][4].edge[1] != '1')){
            if(Square[5][4].edge[3] == '1' && Square[4][5].edge[2] == '1'){
                if(Square[5][3].degree > 2 || Square[5][3].edge[2] != '1' ){
                    if(Square[3][5].degree > 2 || Square[3][5].edge[3] != '1'){
                        if(Square[5][4].edge[0] == '1'){
                            x = 5;
                            y = 4;
                            k = 0;
                            putcheer(Square,x,y,k,myturn);
                            getchecksline(x,y,k);
                            return ;
                        }
                        if(Square[4][5].edge[1] == '1'){
                            x = 4;
                            y = 5;
                            k = 1;
                            putcheer(Square,x,y,k,myturn);
                            getchecksline(x,y,k);
                            return ;
                        }
                        if(Square[5][4].edge[1] == '1'){
                            x = 5;
                            y = 4;
                            k = 1;
                            putcheer(Square,x,y,k,myturn);
                            getchecksline(x,y,k);
                            return ;
                        }
                        if(Square[4][5].edge[0] == '1'){
                            x = 4;
                            y = 5;
                            k = 0;
                            putcheer(Square,x,y,k,myturn);
                            getchecksline(x,y,k);
                            return ;
                        }
                    }
                }
            }
            else if((Square[5][4].edge[3] != '1' && Square[4][5].edge[2] == '1') || (Square[5][4].edge[3] == '1' && Square[4][5].edge[2] != '1')){
                if(Square[5][4].edge[3] != '1' && Square[4][5].edge[2] == '1'){
                    if(Square[5][3].edge[1] == '1' && Square[5][3].edge[2] == '1'){
                        if(Square[5][2].degree > 1 || Square[5][2].edge[2] != '1'){
                            if(Square[3][5].degree > 1 || Square[3][5].edge[3] != '1'){
                                if(Square[4][3].degree > 1 || Square[4][3].edge[3] != '1'){
                                    if(Square[5][3].edge[0] == '1'){
                                        x = 5;
                                        y = 3;
                                        k = 0;
                                        putcheer(Square,x,y,k,myturn);
                                        getchecksline(x,y,k);
                                        return ;
                                    }
                                    if(Square[4][5].edge[1] == '1'){
                                        x = 4;
                                        y = 5;
                                        k = 1;
                                        putcheer(Square,x,y,k,myturn);
                                        getchecksline(x,y,k);
                                        return ;
                                    }
                                    if(Square[5][4].edge[1] == '1'){
                                        x = 5;
                                        y = 4;
                                        k = 1;
                                        putcheer(Square,x,y,k,myturn);
                                        getchecksline(x,y,k);
                                        return ;
                                    }
                                    if(Square[5][3].edge[1] == '1'){
                                        x = 5;
                                        y = 3;
                                        k = 1;
                                        putcheer(Square,x,y,k,myturn);
                                        getchecksline(x,y,k);
                                        return ;
                                    }
                                    if(Square[4][5].edge[0] == '1'){
                                        x = 4;
                                        y = 5;
                                        k = 0;
                                        putcheer(Square,x,y,k,myturn);
                                        getchecksline(x,y,k);
                                        return ;
                                    }
                                }
                            }
                        }
                    }
                }
                if(Square[5][4].edge[3] == '1' && Square[4][5].edge[2] != '1'){
                    if(Square[3][5].edge[2] == '1' && Square[3][5].edge[3] == '1'){
                        if(Square[3][5].degree > 1 || Square[3][5].edge[3] != '1'){
                            if(Square[5][3].degree > 1 || Square[5][3].edge[2] != '1'){
                                if(Square[3][4].degree > 1 || Square[3][4].edge[2] != '1'){
                                    if(Square[3][5].edge[1] == '1'){
                                        x = 3;
                                        y = 5;
                                        k = 1;
                                        putcheer(Square,x,y,k,myturn);
                                        getchecksline(x,y,k);
                                        return ;
                                    }
                                    if(Square[5][4].edge[0] == '1'){
                                        x = 5;
                                        y = 4;
                                        k = 0;
                                        putcheer(Square,x,y,k,myturn);
                                        getchecksline(x,y,k);
                                        return ;
                                    }
                                    if(Square[4][5].edge[0] == '1'){
                                        x = 4;
                                        y = 5;
                                        k = 0;
                                        putcheer(Square,x,y,k,myturn);
                                        getchecksline(x,y,k);
                                        return ;
                                    }
                                    if(Square[3][5].edge[0] == '1'){
                                        x = 3;
                                        y = 5;
                                        k = 0;
                                        putcheer(Square,x,y,k,myturn);
                                        getchecksline(x,y,k);
                                        return ;
                                    }
                                    if(Square[5][4].edge[1] == '1'){
                                        x = 5;
                                        y = 4;
                                        k = 1;
                                        putcheer(Square,x,y,k,myturn);
                                        getchecksline(x,y,k);
                                        return ;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

void AI::action_move1(Situation Square[6][6],bool myturn)
{
    int x,y,k;

    //上
    if(Square[1][3].edge[1] == '1'){
        if((Square[1][3].edge[0] == '1' && Square[1][3].edge[2] == '1') || (Square[1][3].edge[0] == '1' && Square[1][3].edge[2] != '1')){
            if(Square[1][1].edge[0] == '1' && Square[1][1].edge[2] == '1'){
                if(!(Square[1][1].edge[1] != '1' && Square[1][2].edge[1] != '1')){
                    if(Square[1][4].degree > 2 || Square[1][4].edge[0] != '1'){
                        if(Square[2][3].degree > 2 || Square[2][3].edge[1] != '1'){
                            if(Square[2][2].degree > 2 || Square[2][2].edge[1] != '1'){
                                if(Square[2][1].degree > 2 || Square[2][1].edge[1] != '1'){
                                    if(Square[1][3].edge[2] == '1'){
                                        x = 1;
                                        y = 3;
                                        k = 2;
                                        putcheer(Square,x,y,k,myturn);
                                        getchecksline(x,y,k);
                                        return ;
                                    }
                                    if(Square[1][3].edge[3] == '1'){
                                        x = 1;
                                        y = 3;
                                        k = 3;
                                        putcheer(Square,x,y,k,myturn);
                                        getchecksline(x,y,k);
                                        return ;
                                    }
                                    if(Square[1][2].edge[3] == '1'){
                                        x = 1;
                                        y = 2;
                                        k = 3;
                                        putcheer(Square,x,y,k,myturn);
                                        getchecksline(x,y,k);
                                        return ;
                                    }
                                    if(Square[1][1].edge[3] == '1'){
                                        x = 1;
                                        y = 1;
                                        k = 3;
                                        putcheer(Square,x,y,k,myturn);
                                        getchecksline(x,y,k);
                                        return ;
                                    }
                                }
                            }
                        }
                    }
                }
        }
        else if(Square[1][3].edge[0] != '1' && Square[1][3].edge[2] == '1'){
            if(Square[1][5].edge[0] == '1' && Square[1][5].edge[2] == '1'){
                if(!(Square[1][5].edge[1] != '1' && Square[1][4].edge[1] != '1')){
                    if(Square[1][2].degree > 2 || Square[1][2].edge[2] != '1'){
                        if(Square[2][3].degree > 2 || Square[2][3].edge[1] != '1'){
                            if(Square[2][4].degree > 2 || Square[2][4].edge[1] != '1'){
                                if(Square[2][5].degree > 2 || Square[2][5].edge[1] != 1){
                                    if(Square[1][4].edge[3] == '1'){
                                        x = 1;
                                        y = 4;
                                        k = 3;
                                        putcheer(Square,x,y,k,myturn);
                                        getchecksline(x,y,k);
                                        return ;
                                    }
                                    if(Square[1][3].edge[3] == '1'){
                                        x = 1;
                                        y = 3;
                                        k = 3;
                                        putcheer(Square,x,y,k,myturn);
                                        getchecksline(x,y,k);
                                        return ;
                                    }
                                    if(Square[1][5].edge[3] == '1'){
                                        x = 1;
                                        y = 5;
                                        k = 3;
                                        putcheer(Square,x,y,k,myturn);
                                        getchecksline(x,y,k);
                                        return ;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    }

    //左
    if(Square[3][1].edge[0] == '1'){
        if((Square[3][1].edge[1] == '1' && Square[3][1].edge[3] == '1') || (Square[3][1].edge[1] == '1' && Square[3][1].edge[3] != '1')){
            if(Square[1][1].edge[1] == '1' && Square[1][1].edge[3] == '1'){
                if(!(Square[1][1].edge[0] != '1' && Square[2][1].edge[0] != '1')){
                    if(Square[4][1].degree > 2 || Square[4][1].edge[1] != '1'){
                        if(Square[3][2].degree > 2 || Square[3][2].edge[0] != '1'){
                            if(Square[2][2].degree > 2 || Square[2][2].edge[0] != '1'){
                                if(Square[1][2].degree > 2 || Square[1][2].edge[0] != '1'){
                                    if(Square[3][1].edge[3] == '1'){
                                        x = 3;
                                        y = 1;
                                        k = 3;
                                        putcheer(Square,x,y,k,myturn);
                                        getchecksline(x,y,k);
                                        return ;
                                    }
                                    if(Square[3][1].edge[2] == '1'){
                                        x = 3;
                                        y = 1;
                                        k = 2;
                                        putcheer(Square,x,y,k,myturn);
                                        getchecksline(x,y,k);
                                        return ;
                                    }
                                    if(Square[2][1].edge[2] == '1'){
                                        x = 2;
                                        y = 1;
                                        k = 2;
                                        putcheer(Square,x,y,k,myturn);
                                        getchecksline(x,y,k);
                                        return ;
                                    }
                                    if(Square[1][1].edge[2] == '1'){
                                        x = 1;
                                        y = 1;
                                        k = 2;
                                        putcheer(Square,x,y,k,myturn);
                                        getchecksline(x,y,k);
                                        return ;
                                    }
                                }
                            }
                        }
                    }
                }
        }
        else if(Square[3][1].edge[1] != '1' && Square[3][1].edge[3] == '1'){
            if(Square[5][1].edge[1] == '1' && Square[5][1].edge[3] == '1'){
                if(!(Square[4][1].edge[0] != '1' && Square[5][1].edge[0] != '1')){
                    if(Square[2][1].degree > 2 || Square[2][1].edge[3] != '1'){
                        if(Square[3][2].degree > 2 || Square[3][2].edge[0] != '1'){
                            if(Square[4][2].degree > 2 || Square[4][2].edge[0] != '1'){
                                if(Square[5][2].degree > 2 || Square[5][2].edge[0] != '1'){
                                    if(Square[4][1].edge[2] == '1'){
                                        x = 4;
                                        y = 1;
                                        k = 2;
                                        putcheer(Square,x,y,k,myturn);
                                        getchecksline(x,y,k);
                                        return ;
                                    }
                                    if(Square[3][1].edge[2] == '1'){
                                        x = 3;
                                        y = 1;
                                        k = 2;
                                        putcheer(Square,x,y,k,myturn);
                                        getchecksline(x,y,k);
                                        return ;
                                    }
                                    if(Square[5][1].edge[2] == '1'){
                                        x = 5;
                                        y = 1;
                                        k = 2;
                                        putcheer(Square,x,y,k,myturn);
                                        getchecksline(x,y,k);
                                        return ;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    }

    //下
    if(Square[5][3].edge[3] == '1'){
        if((Square[5][3].edge[0] == '1' && Square[5][3].edge[2] == '1') || (Square[5][3].edge[0] == '1' && Square[5][3].edge[2] != '1')){
            if(Square[5][1].edge[0] == '1' && Square[5][1].edge[2] == '1'){
                if(!(Square[5][1].edge[3] != '1' && Square[5][1].edge[3] != '1')){
                    if(Square[5][4].degree > 2 || Square[5][4].edge[0] != '1'){
                        if(Square[4][3].degree > 2 || Square[4][3].edge[3] != '1'){
                            if(Square[4][2].degree > 2 || Square[4][2].edge[3] != '1'){
                                if(Square[4][1].degree > 2 || Square[4][1].edge[3] != '1'){
                                    if(Square[5][3].edge[2] == '1'){
                                        x = 5;
                                        y = 3;
                                        k = 2;
                                        putcheer(Square,x,y,k,myturn);
                                        getchecksline(x,y,k);
                                        return ;
                                    }
                                    if(Square[5][3].edge[1] == '1'){
                                        x = 5;
                                        y = 3;
                                        k = 1;
                                        putcheer(Square,x,y,k,myturn);
                                        getchecksline(x,y,k);
                                        return ;
                                    }
                                    if(Square[5][2].edge[1] == '1'){
                                        x = 5;
                                        y = 2;
                                        k = 1;
                                        putcheer(Square,x,y,k,myturn);
                                        getchecksline(x,y,k);
                                        return ;
                                    }
                                    if(Square[5][1].edge[1] == '1'){
                                        x = 5;
                                        y = 1;
                                        k = 1;
                                        putcheer(Square,x,y,k,myturn);
                                        getchecksline(x,y,k);
                                        return ;
                                    }
                                }
                            }
                        }
                    }
                }
        }
        else if(Square[5][3].edge[0] != '1' && Square[5][3].edge[2] == '1'){
            if(Square[5][5].edge[0] == '1' && Square[5][5].edge[2] == '1'){
                if(!(Square[5][5].edge[3] != '1' && Square[5][4].edge[3] != '1')){
                    if(Square[5][2].degree > 2 || Square[5][2].edge[2] != '1'){
                        if(Square[4][3].degree > 2 || Square[4][3].edge[3] != '1'){
                            if(Square[4][4].degree > 2 || Square[4][4].edge[3] != '1'){
                                if(Square[4][5].degree > 2 || Square[4][5].edge[3] != 1){
                                    if(Square[5][4].edge[1] == '1'){
                                        x = 5;
                                        y = 4;
                                        k = 1;
                                        putcheer(Square,x,y,k,myturn);
                                        getchecksline(x,y,k);
                                        return ;
                                    }
                                    if(Square[5][3].edge[1] == '1'){
                                        x = 5;
                                        y = 3;
                                        k = 1;
                                        putcheer(Square,x,y,k,myturn);
                                        getchecksline(x,y,k);
                                        return ;
                                    }
                                    if(Square[5][5].edge[1] == '1'){
                                        x = 5;
                                        y = 5;
                                        k = 1;
                                        putcheer(Square,x,y,k,myturn);
                                        getchecksline(x,y,k);
                                        return ;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    }

    //右
    if(Square[3][5].edge[2] == '1'){
        if((Square[3][5].edge[1] == '1' && Square[3][5].edge[3] == '1') || (Square[3][5].edge[1] == '1' && Square[3][5].edge[3] != '1')){
            if(Square[1][5].edge[1] == '1' && Square[1][5].edge[3] == '1'){
                if(!(Square[1][5].edge[2] != '1' && Square[2][5].edge[2] != '1')){
                    if(Square[4][5].degree > 2 || Square[4][5].edge[1] != '1'){
                        if(Square[3][4].degree > 2 || Square[3][4].edge[2] != '1'){
                            if(Square[2][4].degree > 2 || Square[2][4].edge[2] != '1'){
                                if(Square[1][4].degree > 2 || Square[1][4].edge[2] != '1'){
                                    if(Square[3][5].edge[3] == '1'){
                                        x = 3;
                                        y = 5;
                                        k = 3;
                                        putcheer(Square,x,y,k,myturn);
                                        getchecksline(x,y,k);
                                        return ;
                                    }
                                    if(Square[3][5].edge[0] == '1'){
                                        x = 3;
                                        y = 5;
                                        k = 0;
                                        putcheer(Square,x,y,k,myturn);
                                        getchecksline(x,y,k);
                                        return ;
                                    }
                                    if(Square[2][5].edge[0] == '1'){
                                        x = 2;
                                        y = 5;
                                        k = 0;
                                        putcheer(Square,x,y,k,myturn);
                                        getchecksline(x,y,k);
                                        return ;
                                    }
                                    if(Square[1][5].edge[0] == '1'){
                                        x = 1;
                                        y = 5;
                                        k = 0;
                                        putcheer(Square,x,y,k,myturn);
                                        getchecksline(x,y,k);
                                        return ;
                                    }
                                }
                            }
                        }
                    }
                }
        }
        else if(Square[3][5].edge[1] != '1' && Square[3][5].edge[3] == '1'){
            if(Square[5][5].edge[1] == '1' && Square[5][5].edge[3] == '1'){
                if(!(Square[4][5].edge[2] != '1' && Square[5][5].edge[2] != '1')){
                    if(Square[2][5].degree > 2 || Square[2][5].edge[3] != '1'){
                        if(Square[3][4].degree > 2 || Square[3][4].edge[2] != '1'){
                            if(Square[4][4].degree > 2 || Square[4][4].edge[2] != '1'){
                                if(Square[5][4].degree > 2 || Square[5][4].edge[2] != '1'){
                                    if(Square[4][5].edge[0] == '1'){
                                        x = 4;
                                        y = 5;
                                        k = 0;
                                        putcheer(Square,x,y,k,myturn);
                                        getchecksline(x,y,k);
                                        return ;
                                    }
                                    if(Square[3][0].edge[0] == '1'){
                                        x = 3;
                                        y = 5;
                                        k = 0;
                                        putcheer(Square,x,y,k,myturn);
                                        getchecksline(x,y,k);
                                        return ;
                                    }
                                    if(Square[5][5].edge[0] == '1'){
                                        x = 5;
                                        y = 5;
                                        k = 0;
                                        putcheer(Square,x,y,k,myturn);
                                        getchecksline(x,y,k);
                                        return ;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    }
}

//跨行列三格长链形成条件
bool AI::tiaojian1(Situation Square[6][6])
{
    //左上
    if(Square[1][1].edge[2] == '1' && Square[1][1].edge[3] == '1' && Square[1][1].degree > 2){
        if((Square[2][2].edge[2] == '1' && Square[2][2].edge[3] == '1' && Square[2][2].degree >1) || (Square[2][2].edge[0] != '1' && Square[2][2].edge[1] != '1')){
            if(Square[1][2].edge[1] == '1' && Square[2][1].edge[0] == '1'){
                if(Square[1][3].degree > 2 || Square[1][3].edge[0] != '1' ){
                    if(Square[3][1].degree > 2 || Square[3][1].edge[1] != '1'){
                        if(!(Square[1][2].edge[2] != '1' && Square[1][2].edge[3] != '1' && Square[2][1].edge[2] != '1' && Square[2][1].edge[3] != '1')){
                            return true;
                        }
                    }
                }
            }
            else if((Square[1][2].edge[1] != '1' && Square[2][1].edge[0] == '1') || (Square[1][2].edge[1] == '1' && Square[2][1].edge[0] != '1')){
                if(Square[1][2].edge[1] != '1' && Square[2][1].edge[0] == '1'){
                    if(Square[1][3].edge[0] == '1' && Square[1][3].edge[1] == '1'){
                        if(Square[1][4].degree > 1 || Square[1][4].edge[0] != '1'){
                            if(Square[3][1].degree > 1 || Square[3][1].edge[1] != '1'){
                                if(Square[2][3].degree > 1 || Square[2][3].edge[1] != '1'){
                                    if(!(Square[1][3].edge[2] != '1' && Square[1][3].edge[3] != '1' && Square[1][2].edge[3] != '1'
                                        && Square[2][1].edge[2] != '1' && Square[2][1].edge[3] != '1')){
                                            return true;
                                        }
                                }
                            }
                        }
                    }
                }
                if(Square[1][2].edge[1] == '1' && Square[2][1].edge[0] != '1'){
                    if(Square[3][1].edge[0] == '1' && Square[3][1].edge[1] == '1'){
                        if(Square[4][1].degree > 1 || Square[4][1].edge[1] != '1'){
                            if(Square[1][3].degree > 1 || Square[1][3].edge[2] != '1'){
                                if(Square[3][2].degree > 1 || Square[3][2].edge[0] != '1'){
                                    if(!(Square[3][1].edge[2] != '1' && Square[3][1].edge[3] != '1' && Square[2][1].edge[2] != '1'
                                        && Square[1][2].edge[2] != '1' && Square[1][2].edge[3] != '1')){
                                            return true;
                                        }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    //右上
    if(Square[1][5].edge[0] == '1' && Square[1][5].edge[3] == '1' && Square[1][5].degree > 2){
        if((Square[2][4].edge[0] == '1' && Square[2][4].edge[3] == '1' && Square[2][4].degree >1) || (Square[2][4].edge[0] != '1' && Square[2][4].edge[3] != '1')){
            if(Square[1][4].edge[1] == '1' && Square[2][5].edge[2] == '1'){
                if(Square[1][3].degree > 2 || Square[1][3].edge[2] != '1' ){
                    if(Square[3][5].degree > 2 || Square[3][5].edge[1] != '1'){
                        if(!(Square[1][4].edge[0] != '1' && Square[1][4].edge[3] != '1' && Square[2][5].edge[0] != '1' && Square[2][5].edge[3] != '1')){
                            return true;
                        }
                    }
                }
            }
            else if((Square[1][4].edge[1] != '1' && Square[2][5].edge[2] == '1') || (Square[1][4].edge[1] == '1' && Square[2][5].edge[2] != '1')){
                if(Square[1][4].edge[1] != '1' && Square[2][5].edge[2] == '1'){
                    if(Square[1][3].edge[1] == '1' && Square[1][3].edge[2] == '1'){
                        if(Square[1][2].degree > 1 || Square[1][2].edge[2] != '1'){
                            if(Square[3][5].degree > 1 || Square[3][5].edge[1] != '1'){
                                if(Square[2][3].degree > 1 || Square[2][3].edge[1] != '1'){
                                    if(!(Square[1][3].edge[0] != '1' && Square[1][3].edge[3] != '1' && Square[1][4].edge[3] != '1'
                                        && Square[2][5].edge[0] != '1' && Square[2][5].edge[3] != '1')){
                                            return true;
                                        }
                                }
                            }
                        }
                    }
                }
                if(Square[1][4].edge[1] == '1' && Square[2][5].edge[2] != '1'){
                    if(Square[3][5].edge[1] == '1' && Square[3][5].edge[2] == '1'){
                        if(Square[4][5].degree > 1 || Square[4][5].edge[1] != '1'){
                            if(Square[1][3].degree > 1 || Square[1][3].edge[2] != '1'){
                                if(Square[3][4].degree > 1 || Square[3][4].edge[2] != '1'){
                                    if(!(Square[3][5].edge[0] != '1' && Square[3][5].edge[3] != '1' && Square[2][5].edge[0] != '1'
                                        && Square[1][4].edge[0] != '1' && Square[1][4].edge[3] != '1')){
                                            return true;
                                        }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    //左下
    if(Square[5][1].edge[1] == '1' && Square[5][1].edge[2] == '1' && Square[5][1].degree > 2){
        if((Square[4][2].edge[1] == '1' && Square[4][2].edge[2] == '1' && Square[4][2].degree >1) || (Square[4][2].edge[1] != '1' && Square[4][2].edge[2] != '1')){
            if(Square[4][1].edge[0] == '1' && Square[5][2].edge[3] == '1'){
                if(Square[3][1].degree > 2 || Square[3][1].edge[3] != '1' ){
                    if(Square[5][3].degree > 2 || Square[5][3].edge[0] != '1'){
                        if(!(Square[4][1].edge[1] != '1' && Square[4][1].edge[2] && Square[5][2].edge[1] != '1' && Square[5][2].edge[2] != '1')){
                            return true;
                        }
                    }
                }
            }
            else if((Square[4][1].edge[0] != '1' && Square[5][2].edge[3] == '1') || (Square[4][1].edge[0] == '1' && Square[5][2].edge[3] != '1')){
                if(Square[4][1].edge[0] != '1' && Square[5][2].edge[3] == '1'){
                    if(Square[3][1].edge[0] == '1' && Square[3][1].edge[3] == '1'){
                        if(Square[2][1].degree > 1 || Square[2][1].edge[3] != '1'){
                            if(Square[5][3].degree > 1 || Square[5][3].edge[1] != '1'){
                                if(Square[3][2].degree > 1 || Square[3][2].edge[0] != '1'){
                                    if(!(Square[3][1].edge[1] != '1' && Square[3][1].edge[2] != '1' && Square[4][1].edge[2] != '1'
                                        && Square[5][2].edge[1] != '1' && Square[5][2].edge[2] != '1')){
                                            return true;
                                        }
                                }
                            }
                        }
                    }
                }
                if(Square[4][1].edge[0] == '1' && Square[5][2].edge[3] != '1'){
                    if(Square[5][3].edge[0] == '1' && Square[5][3].edge[3] == '1'){
                        if(Square[5][4].degree > 1 || Square[5][4].edge[0] != '1'){
                            if(Square[3][1].degree > 1 || Square[3][1].edge[3] != '1'){
                                if(Square[4][3].degree > 1 || Square[4][3].edge[3] != '1'){
                                    if(!(Square[5][3].edge[1] != '1' && Square[5][3].edge[2] != '1' && Square[5][2].edge[1] != '1'
                                        && Square[4][1].edge[1] != '1' && Square[4][1].edge[2] != '1')){
                                            return true;
                                        }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    //右下
    if(Square[5][5].edge[0] == '1' && Square[5][5].edge[1] == '1' && Square[5][5].degree > 2){
        if((Square[4][4].edge[0] == '1' && Square[4][4].edge[1] == '1' && Square[4][4].degree >1) || (Square[4][4].edge[0] != '1' && Square[4][4].edge[1] != '1')){
            if(Square[5][4].edge[3] == '1' && Square[4][5].edge[2] == '1'){
                if(Square[5][3].degree > 2 || Square[5][3].edge[2] != '1' ){
                    if(Square[3][5].degree > 2 || Square[3][5].edge[3] != '1'){
                        if(!(Square[4][5].edge[0] != '1' && Square[4][5].edge[1] != '1' && Square[5][4].edge[0] != '1' && Square[5][4].edge[1] != '1')){
                            return true;
                        }
                    }
                }
            }
            else if((Square[5][4].edge[3] != '1' && Square[4][5].edge[2] == '1') || (Square[5][4].edge[3] == '1' && Square[4][5].edge[2] != '1')){
                if(Square[5][4].edge[3] != '1' && Square[4][5].edge[2] == '1'){
                    if(Square[5][3].edge[1] == '1' && Square[5][3].edge[2] == '1'){
                        if(Square[5][2].degree > 1 || Square[5][2].edge[2] != '1'){
                            if(Square[3][5].degree > 1 || Square[3][5].edge[3] != '1'){
                                if(Square[4][3].degree > 1 || Square[4][3].edge[3] != '1'){
                                    if(!(Square[5][3].edge[0] != '1' && Square[5][3].edge[1] != '1' && Square[5][4].edge[1] != '1'
                                        && Square[4][5].edge[0] != '1' && Square[4][5].edge[1] != '1')){
                                            return true;
                                        }
                                }
                            }
                        }
                    }
                }
                if(Square[5][4].edge[3] == '1' && Square[4][5].edge[2] != '1'){
                    if(Square[3][5].edge[2] == '1' && Square[3][5].edge[3] == '1'){
                        if(Square[3][5].degree > 1 || Square[3][5].edge[3] != '1'){
                            if(Square[5][3].degree > 1 || Square[5][3].edge[2] != '1'){
                                if(Square[3][4].degree > 1 || Square[3][4].edge[2] != '1'){
                                    if(!(Square[3][5].edge[0] != '1' && Square[3][5].edge[1] != '1' && Square[4][5].edge[0] != '1'
                                        && Square[5][4].edge[0] != '1' && Square[5][4].edge[1] != '1')){
                                            return true;
                                        }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    return false;
}

//单向三格长链形成条件
bool AI::tiaojian2(Situation Square[6][6])
{
    //上
    if(Square[1][3].edge[1] == '1'){
        if((Square[1][3].edge[0] == '1' && Square[1][3].edge[2] == '1') || (Square[1][3].edge[0] == '1' && Square[1][3].edge[2] != '1')){
            if(Square[1][1].edge[0] == '1' && Square[1][1].edge[2] == '1'){
                if(!(Square[1][1].edge[1] != '1' && Square[1][2].edge[1] != '1')){
                    if(Square[1][4].degree > 2 || Square[1][4].edge[0] != '1'){
                        if(Square[2][3].degree > 2 || Square[2][3].edge[1] != '1'){
                            if(Square[2][2].degree > 2 || Square[2][2].edge[1] != '1'){
                                if(Square[2][1].degree > 2 || Square[2][1].edge[1] != '1'){
                                    if(!(Square[1][3].edge[2] != '1' && Square[1][3].edge[3] != '1'
                                        && Square[1][2].edge[3] != '1' && Square[1][1].edge[3] != '1')){
                                            return true;
                                        }
                                }
                            }
                        }
                    }
                }
        }
        else if(Square[1][3].edge[0] != '1' && Square[1][3].edge[2] == '1'){
            if(Square[1][5].edge[0] == '1' && Square[1][5].edge[2] == '1'){
                if(!(Square[1][5].edge[1] != '1' && Square[1][4].edge[1] != '1')){
                    if(Square[1][2].degree > 2 || Square[1][2].edge[2] != '1'){
                        if(Square[2][3].degree > 2 || Square[2][3].edge[1] != '1'){
                            if(Square[2][4].degree > 2 || Square[2][4].edge[1] != '1'){
                                if(Square[2][5].degree > 2 || Square[2][5].edge[1] != 1){
                                    if(!(Square[1][3].edge[0] != '1' && Square[1][3].edge[3] != '1'
                                        && Square[1][4].edge[3] != '1' && Square[1][5].edge[3] != '1')){
                                            return true;
                                        }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    }

    //左
    if(Square[3][1].edge[0] == '1'){
        if((Square[3][1].edge[1] == '1' && Square[3][1].edge[3] == '1') || (Square[3][1].edge[1] == '1' && Square[3][1].edge[3] != '1')){
            if(Square[1][1].edge[1] == '1' && Square[1][1].edge[3] == '1'){
                if(!(Square[1][1].edge[0] != '1' && Square[2][1].edge[0] != '1')){
                    if(Square[4][1].degree > 2 || Square[4][1].edge[1] != '1'){
                        if(Square[3][2].degree > 2 || Square[3][2].edge[0] != '1'){
                            if(Square[2][2].degree > 2 || Square[2][2].edge[0] != '1'){
                                if(Square[1][2].degree > 2 || Square[1][2].edge[0] != '1'){
                                    if(!(Square[3][1].edge[2] != '1' && Square[3][1].edge[3] != '1'
                                        && Square[2][1].edge[2] != '1' && Square[1][1].edge[2] != '1')){
                                            return true;
                                        }
                                }
                            }
                        }
                    }
                }
        }
        else if(Square[3][1].edge[1] != '1' && Square[3][1].edge[3] == '1'){
            if(Square[5][1].edge[1] == '1' && Square[5][1].edge[3] == '1'){
                if(!(Square[4][1].edge[0] != '1' && Square[5][1].edge[0] != '1')){
                    if(Square[2][1].degree > 2 || Square[2][1].edge[3] != '1'){
                        if(Square[3][2].degree > 2 || Square[3][2].edge[0] != '1'){
                            if(Square[4][2].degree > 2 || Square[4][2].edge[0] != '1'){
                                if(Square[5][2].degree > 2 || Square[5][2].edge[0] != '1'){
                                    if(!(Square[3][1].edge[1] != '1' && Square[3][1].edge[2] != '1'
                                        && Square[4][1].edge[2] != '1' && Square[5][1].edge[2] != '1')){
                                            return true;
                                        }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    }

    //下
    if(Square[5][3].edge[3] == '1'){
        if((Square[5][3].edge[0] == '1' && Square[5][3].edge[2] == '1') || (Square[5][3].edge[0] == '1' && Square[5][3].edge[2] != '1')){
            if(Square[5][1].edge[0] == '1' && Square[5][1].edge[2] == '1'){
                if(!(Square[5][1].edge[3] != '1' && Square[5][1].edge[3] != '1')){
                    if(Square[5][4].degree > 2 || Square[5][4].edge[0] != '1'){
                        if(Square[4][3].degree > 2 || Square[4][3].edge[3] != '1'){
                            if(Square[4][2].degree > 2 || Square[4][2].edge[3] != '1'){
                                if(Square[4][1].degree > 2 || Square[4][1].edge[3] != '1'){
                                    if(!(Square[5][3].edge[1] != '1' && Square[5][3].edge[2] != '1'
                                        && Square[5][2].edge[1] != '1' && Square[5][1].edge[1] != '1')){
                                            return true;
                                        }
                                }
                            }
                        }
                    }
                }
        }
        else if(Square[5][3].edge[0] != '1' && Square[5][3].edge[2] == '1'){
            if(Square[5][5].edge[0] == '1' && Square[5][5].edge[2] == '1'){
                if(!(Square[5][5].edge[3] != '1' && Square[5][4].edge[3] != '1')){
                    if(Square[5][2].degree > 2 || Square[5][2].edge[2] != '1'){
                        if(Square[4][3].degree > 2 || Square[4][3].edge[3] != '1'){
                            if(Square[4][4].degree > 2 || Square[4][4].edge[3] != '1'){
                                if(Square[4][5].degree > 2 || Square[4][5].edge[3] != 1){
                                    if(!(Square[5][3].edge[0] != '1' && Square[5][3].edge[1] != '1'
                                        && Square[5][4].edge[1] != '1' && Square[5][5].edge[1] != '1')){
                                            return true;
                                        }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    }

    //右
    if(Square[3][5].edge[2] == '1'){
        if((Square[3][5].edge[1] == '1' && Square[3][5].edge[3] == '1') || (Square[3][5].edge[1] == '1' && Square[3][5].edge[3] != '1')){
            if(Square[1][5].edge[1] == '1' && Square[1][5].edge[3] == '1'){
                if(!(Square[1][5].edge[2] != '1' && Square[2][5].edge[2] != '1')){
                    if(Square[4][5].degree > 2 || Square[4][5].edge[1] != '1'){
                        if(Square[3][4].degree > 2 || Square[3][4].edge[2] != '1'){
                            if(Square[2][4].degree > 2 || Square[2][4].edge[2] != '1'){
                                if(Square[1][4].degree > 2 || Square[1][4].edge[2] != '1'){
                                    if(!(Square[3][5].edge[0] != '1' && Square[3][5].edge[3] != '1'
                                        && Square[2][5].edge[0] != '1' && Square[1][5].edge[0] != '1')){
                                            return true;
                                        }
                                }
                            }
                        }
                    }
                }
        }
        else if(Square[3][5].edge[1] != '1' && Square[3][5].edge[3] == '1'){
            if(Square[5][5].edge[1] == '1' && Square[5][5].edge[3] == '1'){
                if(!(Square[4][5].edge[2] != '1' && Square[5][5].edge[2] != '1')){
                    if(Square[2][5].degree > 2 || Square[2][5].edge[3] != '1'){
                        if(Square[3][4].degree > 2 || Square[3][4].edge[2] != '1'){
                            if(Square[4][4].degree > 2 || Square[4][4].edge[2] != '1'){
                                if(Square[5][4].degree > 2 || Square[5][4].edge[2] != '1'){
                                    if(!(Square[3][5].edge[0] != '1' && Square[3][5].edge[1] != '1'
                                        && Square[4][5].edge[0] != '1' && Square[5][5].edge[0] != '1')){
                                            return true;
                                        }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    }

    return false;
}


int AI::three_count(Situation Square[6][6], chu *move)
{
    qDebug()<<"进入残局某特殊三自由度统计";
    Situation To[6][6];
    copy1(Square,To);

    for(int i=1; i<6; i++){
        for(int j=1; j<6; j++){
            //找某三自由度
            if(To[i][j].degree == 3){
                qDebug()<<"出现某三自由度位置 "<<"x="<<i<<" y="<<j;
                chu BeforeDead[3];
                int count = 0;
                //找三边
                for(int k=0; k<4; k++){
                    if(To[i][j].edge[k] == '1'){
                        BeforeDead[count].x = i;
                        BeforeDead[count].y = j;
                        BeforeDead[count].k = k;
                        count++;
                    }
                }
                //下三边
                qDebug()<<"下三边";
                for(int x=0; x<3; x++){
                    qDebug()<<"下"<<BeforeDead[x].k<<"边";
                    Situation to[6][6];
                    copy1(To,to);

                    //若果相邻的格子是另一某三自由度格子的私有短链，则不下该边，直接跳到下一边
                    if(BeforeDead[x].k == 0)
                    {
                        //如果是另一某三自由度格子的私有短链
                        if(to[BeforeDead[x].x][BeforeDead[x].y -1].degree == -1)
                        {
                            qDebug()<<"出现共享短链";
                            //把该短链变成共有短链
                            To[BeforeDead[x].x][BeforeDead[x].y - 1].degree = -2;
                            for(int s=0; s<4; s++){
                                if((s != 2) && (to[BeforeDead[x].x][BeforeDead[x].y -1].edge[s] == '1')){
                                    qDebug()<<"延伸方向"<<s;
                                    int k = s;
                                    if(k == 0){
                                        if(to[BeforeDead[x].x][BeforeDead[x].y -2].degree == -1){
                                            To[BeforeDead[x].x][BeforeDead[x].y -2].degree = -2;
                                            break;
                                        }
                                    }
                                    if(k == 1){
                                        if(to[BeforeDead[x].x -1][BeforeDead[x].y -1].degree == -1){
                                            To[BeforeDead[x].x -1][BeforeDead[x].y -1].degree = -2;
                                            break;
                                        }
                                    }
                                    if(k == 3){
                                        if(to[BeforeDead[x].x +1][BeforeDead[x].y -1].degree == -1){
                                            To[BeforeDead[x].x +1][BeforeDead[x].y -1].degree = -2;
                                            break;
                                        }
                                    }
                                }
                            }
                            continue;
                        }
                    }

                    if(BeforeDead[x].k == 1)
                    {
                        //如果是另一某三自由度格子的私有短链
                        if(to[BeforeDead[x].x -1][BeforeDead[x].y].degree == -1)
                        {
                            qDebug()<<"出现共享短链";
                            //把该短链变成共有短链
                            To[BeforeDead[x].x -1][BeforeDead[x].y ].degree = -2;
                            for(int s=0; s<4; s++){
                                if((s != 3) && (to[BeforeDead[x].x -1][BeforeDead[x].y].edge[s] == '1')){
                                    qDebug()<<"延伸方向"<<s;
                                    int k = s;
                                    if(k == 0){
                                        if(to[BeforeDead[x].x -1][BeforeDead[x].y -1].degree == -1){
                                            To[BeforeDead[x].x -1][BeforeDead[x].y -1].degree = -2;
                                            break;
                                        }
                                    }
                                    if(k == 1){
                                        if(to[BeforeDead[x].x -2][BeforeDead[x].y].degree == -1){
                                            To[BeforeDead[x].x -2][BeforeDead[x].y].degree = -2;
                                            break;
                                        }
                                    }
                                    if(k == 2){
                                        if(to[BeforeDead[x].x -1][BeforeDead[x].y +1].degree == -1){
                                            To[BeforeDead[x].x -1][BeforeDead[x].y +1].degree = -2;
                                            break;
                                        }
                                    }
                                }
                            }
                            continue;
                        }
                    }

                    if(BeforeDead[x].k == 2)
                    {
                        //如果是另一某三自由度格子的私有短链
                        if(to[BeforeDead[x].x][BeforeDead[x].y +1].degree == -1)
                        {
                            qDebug()<<"出现共享短链";
                            //把该短链变成共有短链
                            To[BeforeDead[x].x][BeforeDead[x].y +1].degree = -2;
                            for(int s=0; s<4; s++){
                                if((s != 0) && (to[BeforeDead[x].x][BeforeDead[x].y +1].edge[s] == '1')){
                                    qDebug()<<"延伸方向"<<s;
                                    int k = s;
                                    if(k == 1){
                                        if(to[BeforeDead[x].x -1][BeforeDead[x].y +1].degree == -1){
                                            To[BeforeDead[x].x -1][BeforeDead[x].y +1].degree = -2;
                                            break;
                                        }
                                    }
                                    if(k == 2){
                                        if(to[BeforeDead[x].x][BeforeDead[x].y +2].degree == -1){
                                            To[BeforeDead[x].x][BeforeDead[x].y +2].degree = -2;
                                            break;
                                        }
                                    }
                                    if(k == 3){
                                        if(to[BeforeDead[x].x +1][BeforeDead[x].y +1].degree == -1){
                                            To[BeforeDead[x].x +1][BeforeDead[x].y +1].degree = -2;
                                            break;
                                        }
                                    }
                                }
                            }
                            continue;
                        }
                    }

                    if(BeforeDead[x].k == 3)
                    {
                        //如果是另一某三自由度格子的私有短链
                        if(to[BeforeDead[x].x +1][BeforeDead[x].y].degree == -1)
                        {
                            qDebug()<<"出现共享短链";
                            //把该短链变成共有短链
                            To[BeforeDead[x].x +1][BeforeDead[x].y].degree = -2;
                            for(int s=0; s<4; s++){
                                if((s != 1) && (to[BeforeDead[x].x +1][BeforeDead[x].y].edge[s] == '1')){
                                    qDebug()<<"延伸方向"<<s;
                                    int k = s;
                                    if(k == 0){
                                        if(to[BeforeDead[x].x +1][BeforeDead[x].y -1].degree == -1){
                                            To[BeforeDead[x].x +1][BeforeDead[x].y -1].degree = -2;
                                            break;
                                        }
                                    }
                                    if(k == 2){
                                        if(to[BeforeDead[x].x +1][BeforeDead[x].y +1].degree == -1){
                                            To[BeforeDead[x].x +1][BeforeDead[x].y +1].degree = -2;
                                            break;
                                        }
                                    }
                                    if(k == 3){
                                        if(to[BeforeDead[x].x +2][BeforeDead[x].y].degree == -1){
                                            To[BeforeDead[x].x +2][BeforeDead[x].y].degree = -2;
                                            break;
                                        }
                                    }
                                }
                            }
                            continue;
                        }
                    }

                    qDebug()<<"该方向无共享短链";
                    int three_x = BeforeDead[x].x;
                    int three_y = BeforeDead[x].y;
                    int three_k = BeforeDead[x].k;

                    to[BeforeDead[x].x][BeforeDead[x].y].edge[BeforeDead[x].k] = '*';
                    to[BeforeDead[x].x][BeforeDead[x].y].degree--;
                    mutualoccupy1(to, BeforeDead[x].x,BeforeDead[x].y,BeforeDead[x].k);

                    int count = 0;
                    int eat = 0;
                    qDebug()<<"计算支链长度";
                    while(eat==0 || eat>count)
                    {
                        count = eat;
                        for(int x=1; x<6; x++){
                            for(int y=1; y<6; y++){
                                if(to[x][y].degree == 1)
                                {
                                    for(int k=0; k<4; k++)
                                    {
                                        if(to[x][y].edge[k] == '1')
                                        {
                                            to[x][y].edge[k] = '*';
                                            to[x][y].degree--;
                                            mutualoccupy1(to,x,y,k);
                                            eat++;
                                        }
                                    }
                                }
                            }
                        }
                        //若果吃了超过三个格子，则此方向是长链，我们不需要
                        if(eat > 2) break;

                    }

                    qDebug()<<"有"<<eat<<"格链";
                    //如果是短链，则把它变成私有的
                    if(eat <= 2)
                    {
                        int three_xx = 0;
                        int three_yy = 0;
                        int three_kk = 0;
                        qDebug()<<"有"<<eat<<"格短链";
                        qDebug()<<"变私有1";
                        if(three_k == 0){
                            To[three_x][three_y -1].degree = -1;
                            for(int s=0; s<4; s++){
                                if((s != 2) && (to[three_x][three_y -1].edge[s] == '1')){
                                    three_kk = s;
                                    if(three_kk == 0){
                                        three_xx = three_x;
                                        three_yy = three_y -2;
                                    }
                                    if(three_kk == 1){
                                        three_xx = three_x -1;
                                        three_yy = three_y -1;
                                    }
                                    if(three_kk == 3){
                                        three_xx = three_x +1;
                                        three_yy = three_y -1;
                                    }
                                    break;
                                }
                            }
                        }
                        if(three_k == 1){
                            To[three_x -1][three_y].degree = -1;
                            for(int s=0; s<4; s++){
                                if((s != 3) && (to[three_x -1][three_y].edge[s] == '1')){
                                    three_kk = s;
                                    if(three_kk == 0){
                                        three_xx = three_x -1;
                                        three_yy = three_y -1;
                                    }
                                    if(three_kk == 1){
                                        three_xx = three_x -2;
                                        three_yy = three_y;
                                    }
                                    if(three_kk == 2){
                                        three_xx = three_x -1;
                                        three_yy = three_y +1;
                                    }
                                    break;
                                }
                            }
                        }
                        if(three_k == 2){
                            To[three_x][three_y +1].degree = -1;
                            for(int s=0; s<4; s++){
                                if((s != 0) && (to[three_x][three_y +1].edge[s] == '1')){
                                    three_kk = s;
                                    if(three_kk == 1){
                                        three_xx = three_x -1;
                                        three_yy = three_y +1;
                                    }
                                    if(three_kk == 2){
                                        three_xx = three_x;
                                        three_yy = three_y +2;
                                    }
                                    if(three_kk == 3){
                                        three_xx = three_x +1;
                                        three_yy = three_y;
                                    }
                                    break;
                                }
                            }
                        }
                        if(three_k == 3){
                            To[three_x +1][three_y].degree = -1;
                            for(int s=0; s<4; s++){
                                if((s != 0) && (to[three_x +1][three_y].edge[s] == '1')){
                                    three_kk = s;
                                    if(three_kk == 0){
                                        three_xx = three_x +1;
                                        three_yy = three_y -1;
                                    }
                                    if(three_kk == 2){
                                        three_xx = three_x +1;
                                        three_yy = three_y +1;
                                    }
                                    if(three_kk == 3){
                                        three_xx = three_x +2;
                                        three_yy = three_y;
                                    }
                                    break;
                                }
                            }
                        }
                        if(eat == 1){
                            goto line_fq;
                        }
                        else{
                            qDebug()<<"变私有2";
                            To[three_xx][three_yy].degree = -1;
                        }
                        qDebug()<<"结束设置变私有短链";
                    }
line_fq:             qDebug()<<"结束下一条边";
                }
                qDebug()<<"结束查看一个某三自由度格子";
            }
        }
    }

    qDebug()<<"开始全局统计";
    int Private = 0;
    int Public = 0;
    int Pri_Pub = 0;
    int gongyou_I = 0;
    int gongyou_II = 0;

    for(int i=1; i<6; i++){
        for(int j=1; j<6; j++){
            if(To[i][j].degree == 3){
                int siyou = 0;
                int gongyou = 0;
                for(int k=0; k<4; k++){
                    if(To[i][j].edge[k] == '1'){
                        if(k == 0){
                            if(To[i][j-1].degree == -1){
                                siyou++;
                            }
                            if(To[i][j-1].degree == -2){
                                gongyou++;
                            }
                        }
                        if(k == 1){
                            if(To[i-1][j].degree == -1){
                                siyou++;
                            }
                            if(To[i-1][j].degree == -2){
                                gongyou++;
                            }
                        }
                        if(k == 2){
                            if(To[i][j+1].degree == -1){
                                siyou++;
                            }
                            if(To[i][j+1].degree == -2){
                                gongyou++;
                            }
                        }
                        if(k == 4){
                            if(To[i+1][j].degree == -1){
                                siyou++;
                            }
                            if(To[i+1][j].degree == -2){
                                gongyou++;
                            }
                        }
                    }
                }

                if((siyou == 0) && (gongyou == 0)){
                    //没有反双交
                }
                if((siyou != 0) && (gongyou == 0)){
                    Private++;  //只有私有短链
                }
                if((siyou == 0) && (gongyou != 0)){
                    Public++;   //只有公用短链
                    if(gongyou == 1){
                        gongyou_I++;
                    }
                    else{
                        gongyou_II++;
                        for(int m=0; m<4; m++){
                            if(To[i][j].edge[m] == '1'){
                                if(m == 0){
                                    if((To[i][j-1].degree == -1) || (To[i][j-1].degree == -2)){
                                        for(int n=0; n<4; n++){
                                            if((n != 2) && (To[i][j-1].edge[n] == '1')){
                                                move[index].x = i;
                                                move[index].y = j-1;
                                                move[index].k = n;
                                                To[i][j-1].edge[n] = '*';
                                                index++;
                                                break;
                                            }
                                        }
                                    }
                                }
                                if(m == 1){
                                    if((To[i-1][j].degree == -1) || (To[i-1][j].degree == -2)){
                                        for(int n=0; n<4; n++){
                                            if((n != 3) && To[i-1][j].edge[n] == '1'){
                                                move[index].x = i-1;
                                                move[index].y = j;
                                                move[index].k = n;
                                                To[i-1][j].edge[n] = '*';
                                                index++;
                                                break;
                                            }
                                        }
                                    }
                                }
                                if(m == 2){
                                    if((To[i][j+1].degree == -1) || (To[i][j+1].degree == -2)){
                                        for(int n=0; n<4; n++){
                                            if((n != 0) && (To[i][j+1].edge[n] == '1')){
                                                move[index].x = i;
                                                move[index].y = j+1;
                                                move[index].k = n;
                                                To[i][j+1].edge[n] = '*';
                                                index++;
                                                break;
                                            }
                                        }
                                    }
                                }
                                if(m == 3){
                                    if((To[i+1][j].degree == -1) || (To[i+1][j].degree == -2)){
                                        for(int n=0; n<4; n++){
                                            if((n != 1) && (To[i+1][j].edge[n] == '1')){
                                                move[index].x = i+1;
                                                move[index].y = j;
                                                move[index].k = n;
                                                To[i+1][j].edge[n] = '*';
                                                index++;
                                                break;
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
                if((siyou != 0) && (gongyou != 0)){
                    Pri_Pub++;   //公私
                    for(int m=0; m<4; m++){
                        if(To[i][j].edge[m] == '1'){
                            if(m == 0){
                                if((To[i][j-1].degree == -1) || (To[i][j-1].degree == -2)){
                                    for(int n=0; n<4; n++){
                                        if((n != 2) && (To[i][j-1].edge[n] == '1')){
                                            move[index].x = i;
                                            move[index].y = j-1;
                                            move[index].k = n;
                                            To[i][j-1].edge[n] = '*';
                                            index++;
                                            break;
                                        }
                                    }
                                }
                            }
                            if(m == 1){
                                if((To[i-1][j].degree == -1) || (To[i-1][j].degree == -2)){
                                    for(int n=0; n<4; n++){
                                        if((n != 3) && To[i-1][j].edge[n] == '1'){
                                            move[index].x = i-1;
                                            move[index].y = j;
                                            move[index].k = n;
                                            To[i-1][j].edge[n] = '*';
                                            index++;
                                            break;
                                        }
                                    }
                                }
                            }
                            if(m == 2){
                                if((To[i][j+1].degree == -1) || (To[i][j+1].degree == -2)){
                                    for(int n=0; n<4; n++){
                                        if((n != 0) && (To[i][j+1].edge[n] == '1')){
                                            move[index].x = i;
                                            move[index].y = j+1;
                                            move[index].k = n;
                                            To[i][j+1].edge[n] = '*';
                                            index++;
                                            break;
                                        }
                                    }
                                }
                            }
                            if(m == 3){
                                if((To[i+1][j].degree == -1) || (To[i+1][j].degree == -2)){
                                    for(int n=0; n<4; n++){
                                        if((n != 1) && (To[i+1][j].edge[n] == '1')){
                                            move[index].x = i+1;
                                            move[index].y = j;
                                            move[index].k = n;
                                            To[i+1][j].edge[n] = '*';
                                            index++;
                                            break;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    int num = 0;
/*    if((Public == 0) && (Pri_Pub == 0)){
//        num = Private;
    }*/
    if(Pri_Pub >= 2){
//        num += Pri_Pub;  //个数不确定性，不参与统计，结合先后手另作评估
        num += index;
    }
/*    if((Public != 0) && (Pri_Pub == 0)){
        if(Public >= 1 && Public <= 3){
            num = Private + 1;   //3个以内只有一个 （主要针对2个的情况）
        }
        if(Public >= 4 && Public <= 5){
            num = Private + 2;
        }
        else{
            num = Private + 3;  //5*5的棋盘很难出现超过6个，6个已经是极限
        }
    }*/
    if((Public != 0) && (Pri_Pub != 0)){
        if((Public == 1) && (Pri_Pub == 1)){
//            num = Private + 1;
        }
        if((Public == 2) && (Pri_Pub == 1)){
            if(gongyou_II == 0){
//                num = Private +1;
            }
            else{
//                num += gongyou_II;
                num += index;
            }
        }
        else{
//            num += gongyou_II;
            num += index;
        }
    }
    qDebug()<<"结束全局统计";
    return num;
}


//跨行列计数（使用）
int AI::heixiazi1(Situation Square[6][6]){
    int s = 0;

    //左上
    if(Square[1][1].edge[2] == '1' && Square[1][1].edge[3] == '1' && Square[1][1].degree >2){
        if(Square[1][2].edge[1] == '1' && Square[2][1].edge[0] == '1'){
            if(Square[1][2].edge[2] != '1' && Square[1][2].edge[3] != '1'){
                if(Square[2][1].edge[2] != '1' && Square[2][1].edge[3] != '1'){
                    s++;
                }
            }
        }
        else if(Square[1][2].edge[1] != '1' && Square[2][1].edge[0] == '1'){
            if(Square[1][3].edge[0] == '1' && Square[1][3].edge[1] == '1'){
                if(Square[1][3].edge[2] != '1' && Square[1][3].edge[3] != '1'){
                    if(Square[1][2].edge[3] != '1'){
                        if(Square[2][1].edge[2] != '1' && Square[2][1].edge[3] != '1'){
                            s++;
                        }
                    }
                }
            }
        }
        else if(Square[1][2].edge[1] == '1' && Square[2][1].edge[0] != '1'){
            if(Square[3][1].edge[0] == '1' && Square[3][1].edge[1] == '1'){
                if(Square[3][1].edge[2] != '1' && Square[3][1].edge[3] != '1'){
                    if(Square[2][1].edge[2] != '1'){
                        if(Square[1][2].edge[2] != '1' && Square[1][2].edge[3] != '1'){
                            s++;
                        }
                    }
                }
            }
        }
    }

    //右上
    if(Square[1][5].edge[1] == '1' && Square[1][5].edge[2] == '1' && Square[1][5].degree >2){
        if(Square[1][4].edge[1] == '1' && Square[2][5].edge[2] == '1'){
            if(Square[1][4].edge[0] != '1' && Square[1][4].edge[3] != '1'){
                if(Square[2][5].edge[0] != '1' && Square[2][5].edge[3] != '1'){
                    s++;
                }
            }
        }
        else if(Square[1][4].edge[1] != '1' && Square[2][5].edge[2] == '1'){
            if(Square[1][3].edge[1] == '1' && Square[1][3].edge[2] == '1'){
                if(Square[1][3].edge[0] != '1' && Square[1][3].edge[3] != '1'){
                    if(Square[1][4].edge[3] != '1'){
                        if(Square[2][5].edge[0] != '1' && Square[2][5].edge[3] != '1'){
                            s++;
                        }
                    }
                }
            }
        }
        else if(Square[1][4].edge[1] == '1' && Square[2][5].edge[2] != '1'){
            if(Square[3][5].edge[1] == '1' && Square[3][5].edge[2] == '1'){
                if(Square[3][5].edge[0] != '1' && Square[3][5].edge[3] != '1'){
                    if(Square[2][5].edge[0] != '1'){
                        if(Square[1][4].edge[0] != '1' && Square[1][4].edge[3] != '1'){
                            s++;
                        }
                    }
                }
            }
        }
    }

    //左下
    if(Square[5][1].edge[1] == '1' && Square[5][1].edge[2] == '1' && Square[5][1].degree >2){
        if(Square[5][2].edge[1] == '1' && Square[4][1].edge[0] == '1'){
            if(Square[5][2].edge[1] != '1' && Square[5][2].edge[2] != '1'){
                if(Square[4][1].edge[1] != '1' && Square[4][1].edge[2] != '1'){
                    s++;
                }
            }
        }
        else if(Square[5][2].edge[3] != '1' && Square[4][1].edge[0] == '1'){
            if(Square[5][3].edge[0] == '1' && Square[5][3].edge[3] == '1'){
                if(Square[5][3].edge[1] != '1' && Square[5][3].edge[2] != '1'){
                    if(Square[5][2].edge[1] != '1'){
                        if(Square[4][1].edge[1] != '1' && Square[4][1].edge[2] != '1'){
                            s++;
                        }
                    }
                }
            }
        }
        else if(Square[5][2].edge[3] == '1' && Square[4][1].edge[0] != '1'){
            if(Square[3][1].edge[0] == '1' && Square[3][1].edge[3] == '1'){
                if(Square[3][1].edge[1] != '1' && Square[3][1].edge[2] != '1'){
                    if(Square[4][1].edge[2] != '1'){
                        if(Square[5][2].edge[1] != '1' && Square[5][2].edge[2] != '1'){
                            s++;
                        }
                    }
                }
            }
        }
    }

    //右下
    if(Square[5][5].edge[0] == '1' && Square[5][5].edge[1] == '1' && Square[5][5].degree >2){
        if(Square[5][4].edge[3] == '1' && Square[4][5].edge[2] == '1'){
            if(Square[5][4].edge[0] != '1' && Square[5][4].edge[1] != '1'){
                if(Square[4][5].edge[0] != '1' && Square[4][5].edge[1] != '1'){
                    s++;
                }
            }
        }
        else if(Square[5][4].edge[3] != '1' && Square[4][5].edge[2] == '1'){
            if(Square[5][3].edge[2] == '1' && Square[5][3].edge[3] == '1'){
                if(Square[5][3].edge[0] != '1' && Square[5][3].edge[1] != '1'){
                    if(Square[5][4].edge[1] != '1'){
                        if(Square[4][5].edge[0] != '1' && Square[4][5].edge[1] != '1'){
                            s++;
                        }
                    }
                }
            }
        }
        else if(Square[5][4].edge[3] == '1' && Square[4][5].edge[2] != '1'){
            if(Square[3][5].edge[2] == '1' && Square[3][5].edge[3] == '1'){
                if(Square[3][5].edge[0] != '1' && Square[3][5].edge[1] != '1'){
                    if(Square[4][5].edge[0] != '1'){
                        if(Square[5][4].edge[0] != '1' && Square[5][4].edge[1] != '1'){
                            s++;
                        }
                    }
                }
            }
        }
    }

    return s;
}

int AI::heixiazi2(Situation Square[6][6]){
    int s = 0;

    //左上横
    if(Square[1][1].edge[0] == '1' && Square[1][1].edge[2] == '1'){
        if(Square[1][3].edge[0] == '1' && Square[1][3].edge[1] == '1'){
            if(!(Square[1][1].edge[1] != '1' && Square[1][2].edge[1] != '1')){
                if(Square[1][1].edge[3] != '1'){
                    if(Square[1][2].edge[3] != '1'){
                        if(Square[1][3].edge[2] != '1' && Square[1][3].edge[3] != '1'){
                            s++;
                        }
                    }
                }
            }
        }
    }

    //左上竖
    if(Square[1][1].edge[1] == '1' && Square[1][1].edge[3] == '1'){
        if(Square[3][1].edge[0] == '1' && Square[3][1].edge[1] == '1'){
            if(!(Square[1][1].edge[0] != '1' && Square[2][1].edge[0] != '1')){
                if(Square[1][1].edge[2] != '1'){
                    if(Square[2][1].edge[2] != '1'){
                        if(Square[3][1].edge[2] != '1' && Square[3][1].edge[3] != '1'){
                            s++;
                        }
                    }
                }
            }
        }
    }

    //右上横
    if(Square[1][5].edge[0] == '1' && Square[1][5].edge[2] == '1'){
        if(Square[1][3].edge[1] == '1' && Square[1][3].edge[2] == '1'){
            if(!(Square[1][4].edge[1] != '1' && Square[1][4].edge[1] != '1')){
                if(Square[1][5].edge[3] != '1'){
                    if(Square[1][4].edge[3] != '1'){
                        if(Square[1][3].edge[0] != '1' && Square[1][3].edge[3] != '1'){
                            s++;
                        }
                    }
                }
            }
        }
    }

    //右上竖
    if(Square[1][5].edge[1] == '1' && Square[1][5].edge[3] == '1'){
        if(Square[3][5].edge[1] == '1' && Square[3][5].edge[2] == '1'){
            if(!(Square[1][5].edge[2] != '1' && Square[2][5].edge[2] != '1')){
                if(Square[1][5].edge[0] != '1'){
                    if(Square[2][5].edge[0] != '1'){
                        if(Square[3][5].edge[0] != '1' && Square[3][5].edge[3] != '1'){
                            s++;
                        }
                    }
                }
            }
        }
    }

    //左下横
    if(Square[5][1].edge[0] == '1' && Square[5][1].edge[2] == '1'){
        if(Square[5][3].edge[0] == '1' && Square[5][3].edge[3] == '1'){
            if(!(Square[5][1].edge[3] != '1' && Square[5][2].edge[3] != '1')){
                if(Square[5][1].edge[1] != '1'){
                    if(Square[5][2].edge[1] != '1'){
                        if(Square[5][3].edge[1] != '1' && Square[5][3].edge[2] != '1'){
                            s++;
                        }
                    }
                }
            }
        }
    }

    //左下竖
    if(Square[5][1].edge[1] == '1' && Square[5][1].edge[3] == '1'){
        if(Square[3][1].edge[0] == '1' && Square[3][1].edge[3] == '1'){
            if(!(Square[4][1].edge[0] != '1' && Square[5][1].edge[0] != '1')){
                if(Square[5][1].edge[2] != '1'){
                    if(Square[4][1].edge[2] != '1'){
                        if(Square[3][1].edge[1] != '1' && Square[3][1].edge[2] != '1'){
                            s++;
                        }
                    }
                }
            }
        }
    }

    //右下横
    if(Square[5][5].edge[0] == '1' && Square[5][5].edge[2] == '1'){
        if(Square[5][3].edge[2] == '1' && Square[5][3].edge[3] == '1'){
            if(!(Square[5][4].edge[3] != '1' && Square[5][5].edge[3] != '1')){
                if(Square[5][5].edge[1] != '1'){
                    if(Square[5][4].edge[1] != '1'){
                        if(Square[5][3].edge[0] != '1' && Square[5][3].edge[1] != '1'){
                            s++;
                        }
                    }
                }
            }
        }
    }

    //右下竖
    if(Square[5][5].edge[1] == '1' && Square[5][5].edge[3] == '1'){
        if(Square[3][5].edge[2] == '1' && Square[3][5].edge[3] == '1'){
            if(!(Square[4][5].edge[2] != '1' && Square[5][5].edge[2] != '1')){
                if(Square[5][5].edge[0] != '1'){
                    if(Square[4][5].edge[0] != '1'){
                        if(Square[3][5].edge[0] != '1' && Square[3][5].edge[1] != '1'){
                            s++;
                        }
                    }
                }
            }
        }
    }

    return s;
}

