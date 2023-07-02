
#ifndef AI_UCT_H
#define AI_UCT_H
#include"Situation1.h"
#include <sys\timeb.h>
#include<iostream>
#include <windows.h>
#include"AI.h"
#include"AI_small.h"
using namespace std;
#include<QDebug>
#include <math.h>
#include<redis.h>
#include<fstream>
#include<QString>
class Ai_UCT
{
public:
    int index= 0;
    bool realTurn;
    bool first;
    chu Bestmove;
    int sonCount=0;
    time_t tv;
    AI_small ai;
    Redis r1;
    Ai_UCT(){
        qDebug()<<"初始化开始";
    }

    //
/*
    int Evaluation(Situation Square[6][6], int Turn)				//评估函数，评估某步棋下过之后的局面 返回股指
    {
        AI_small ai;
        int Num = 0;
//        Situation to[6][6];
        if (Turn == 1)
        {
            Num = ai.Count_AntDoublecorse(Square);
            if (Num % 2 == 1)
            {
                return 1;
            }
            else
            {
                return 0;
            }
        }

        if (Turn != 1)
        {
            Num = ai.Count_AntDoublecorse(Square);
            if (Num % 2 == 0)
            {
                return 1;
            }
            else
            {
                return 0;
            }

        }
        qDebug()<<"555555555555";
    }
*/
    int Evaluation(Situation Square[6][6], int Turn){
//        qDebug()<<"进入棋局评估";
        AI_small ai;
        int Num1 = 0;  //一格、二格短链数量
        int Num2_1 = 0;   //某三自由度得准确估值
        int Num2_2[2] = {0,0};   //某不确定三自由度个数
        Num1 = ai.Count_AntDoublecorse(Square);
//        qDebug()<<"Num1="<<Num1;
        Num2_1 = ai.three_count(Square,Num2_2);
//        qDebug()<<"Num2_1="<<Num2_1;

        if(Num2_2[0] != 0 || Num2_2[1] != 0){
//            qDebug()<<"出现特殊三自由度格子";
            if(Turn == 1){
                return 1;
            }
            if(Turn != 1){
                return 0;
            }
        }
        if(Num2_2[0] ==0 && Num2_2[1] == 0){
            if(Turn == 1){
                if((Num1 + Num2_1) % 2 == 1){
                    return 1;
                }
                else{
                    return 0;
                }
            }
            if(Turn != 1){
                if((Num1 + Num2_1) % 2 ==0){
                    return 1;
                }
                else{
                    return 0;
                }
            }
        }
//        qDebug()<<"退出棋局评估";
    }

    int move1(Situation Square[6][6], chu *move) ///////存储可下边
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

                        }//中九

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
    int move2(Situation Square[6][6], chu *move) ///////存储可下边
    {

        int s = 0;
        for (int x = 1; x < 6; x++)
            for (int y = 1; y < 6; y++)
                for (int k = 0; k < 4; k++)
                {
                    if (Square[x][y].edge[k] == '1') {

                        if ((x > 1 && x < 5) && (y > 1 && y < 5))
                        {

                                if(k==0||k==1){
                                    move[s].k = k;
                                    move[s].x = x;
                                    move[s].y = y;
                                    s++;
                                }

                            

                        }//中九

                        else if (x == 1 && y > 1 && y < 5)
                        {
    
                                if(k==0||k==1){
                                    move[s].k = k;
                                    move[s].x = x;
                                    move[s].y = y;
                                    s++;
                                }
                            

                        }//上3

                        else if (x == 5 && y > 1 && y < 5)
{
                                if(k==0||k==1||k==3){
                                    move[s].k = k;
                                    move[s].x = x;
                                    move[s].y = y;
                                    s++;
                                }
                            
                        }//下3

                        else if (y == 1 && x > 1 && x < 5)
                        {

                                if(k==0||k==1){
                                    move[s].k = k;
                                    move[s].x = x;
                                    move[s].y = y;
                                    s++;
                                }
                            
                        }//左3

                        else if (y == 5 && x > 1 && x < 5)
                        {

                                if(k==0||k==1||k==2){
                                    move[s].k = k;
                                    move[s].x = x;
                                    move[s].y = y;
                                    s++;
                                }
                            
                        }//右3

                        else if (x == 1 && y == 1)
                        {

                                if(k==0||k==1){
                                    move[s].k = k;
                                    move[s].x = x;
                                    move[s].y = y;
                                    s++;
                                }
                            
                        }//左上点

                        else if (x == 5 && y == 1)
                        {

                                if(k==0||k==1||k==3){
                                    move[s].k = k;
                                    move[s].x = x;
                                    move[s].y = y;
                                    s++;
                                }
                            
                        }//左下点

                        else if (x == 1 && y == 5)
                        {

                                if(k==0||k==1||k==2){
                                    move[s].k = k;
                                    move[s].x = x;
                                    move[s].y = y;
                                    s++;
                                }
                            
                        }//右上点

                        else
                        {

                                move[s].k = k;
                                move[s].x = x;
                                move[s].y = y;
                                s++;
                            
                        }//右下点

                    }
                }

        return s;

    }
    void bianli(Situation Square[6][6]) {

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


    void copy1(Situation  from[6][6], Situation  to[6][6])
    {
        for (int i = 1; i < 6; i++)
            for (int j = 1; j < 6; j++)

            {
                to[i][j].ower = from[i][j].ower;
                to[i][j].degree = from[i][j].degree;
                to[i][j].edge[0] = from[i][j].edge[0];
                to[i][j].edge[1] = from[i][j].edge[1];
                to[i][j].edge[2] = from[i][j].edge[2];
                to[i][j].edge[3] = from[i][j].edge[3];
            }
    }

    void copy(Situation1  *from, Situation1  *to)
    {

        for (int i = 1; i < 6; i++)
            for (int j = 1; j < 6; j++)

            {
                to->cheer[i][j].ower = from->cheer[i][j].ower;

                to->cheer[i][j].degree = from->cheer[i][j].degree;
                to->cheer[i][j].edge[0] = from->cheer[i][j].edge[0];
                to->cheer[i][j].edge[1] = from->cheer[i][j].edge[1];
                to->cheer[i][j].edge[2] = from->cheer[i][j].edge[2];
                to->cheer[i][j].edge[3] = from->cheer[i][j].edge[3];
            }
    }

    int move(Situation Square[6][6], chu *move) ///////存储可下边
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

    void putcheer(Situation Square[6][6], int x, int y, int k, int turn)
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
     }

    //相互占领边函数，减去领边自由度(自己边已经在占边的时候减去自由度了)
    void mutualoccupy1(Situation Square[6][6], int x, int y, int k)
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

    //判断占格
    bool opc(Situation1 *Square, int turn) {
        bool occupy2 = false;
        for (int i = 1; i < 6; i++)
            for (int j = 1; j < 6; j++){
                if (Square->cheer[i][j].edge[0] != '1'&&Square->cheer[i][j].edge[1] != '1' &&Square->cheer[i][j].edge[2] != '1'
                        &&Square->cheer[i][j].edge[3] != '1'&&Square->cheer[i][j].ower != 'A'&&
                        Square->cheer[i][j].ower != 'B')
                   {

                    occupy2 = true;
                    if (turn == 1)
                    {
                        Square->cheer[i][j].ower= 'A';
                        //chesssborad.my_Occupy++;
                    }
                    else
                    {
                        Square->cheer[i][j].ower = 'B';

                    }
                }
        }
        return occupy2;
    }

    bool win(Situation1 *chess){
        int A=0;

        for (int i = 1; i < 6; i++)
            for (int j = 1; j < 6; j++){
                if(chess->cheer[i][j].ower=='A'){
                    A++;
                }
        }

        if(A>12){
            return true;
        }else{
            return false;
        }

    }

    void checkFreeDom(Situation Square[6][6]){

        for(int i = 1;i<6;i++)
            for(int j=1;j<6;j++){
                if(i==1&&j==1){
                    if(Square[i][j].edge[2]!='1'){
                        Square[i][j+1].edge[0] = Square[i][j].edge[2];
                    }else if (Square[i][j].edge[3]!='1') {
                        Square[i+1][j].edge[1] = Square[i][j].edge[3];
                    }
                }else if(i==1&&j==5){
                    if(Square[i][j].edge[0]!='1'){
                        Square[i][j-1].edge[3] = Square[i][j].edge[0];   //2=0
                    }else if (Square[i][j].edge[3]!='1') {
                        Square[i+1][j].edge[1] = Square[i][j].edge[3];
                    }
                }else if (i==5&&j==1) {
                    if(Square[i][j].edge[1]!='1'){
                        Square[i-1][j].edge[3] = Square[i][j].edge[1];
                    }else if(Square[i][j].edge[2]!='1'){
                        Square[i][j+1].edge[0] = Square[i][j].edge[2];
                    }
                }else if (i==5&&j==5) {
                    if(Square[i][j].edge[0]!='1'){
                        Square[i][j-1].edge[3] = Square[i][j].edge[0];   //2=0
                    }else if(Square[i][j].edge[1]!='1'){
                        Square[i-1][j].edge[3] = Square[i][j].edge[1];
                    }
                }else if(i==1&&j!=1&&j!=5){
                    if(Square[i][j].edge[0]!='1'){
                        Square[i][j-1].edge[3] = Square[i][j].edge[0];   //2=0
                    }else if(Square[i][j].edge[2]!='1'){
                        Square[i][j+1].edge[0] = Square[i][j].edge[2];
                    }else if (Square[i][j].edge[3]!='1') {
                        Square[i+1][j].edge[1] = Square[i][j].edge[3];
                    }
                }else if (i==5&&j!=1&&j!=5) {
                    if(Square[i][j].edge[0]!='1'){
                        Square[i][j-1].edge[3] = Square[i][j].edge[0];   //2=0
                    }else if(Square[i][j].edge[1]!='1'){
                        Square[i-1][j].edge[3] = Square[i][j].edge[1];
                    }else if(Square[i][j].edge[2]!='1'){
                        Square[i][j+1].edge[0] = Square[i][j].edge[2];
                    }
                }else if (j==1&&i!=1&&j!=5) {
                    if(Square[i][j].edge[1]!='1'){
                         Square[i-1][j].edge[3] = Square[i][j].edge[1];
                    }else if(Square[i][j].edge[2]!='1'){
                         Square[i][j+1].edge[0] = Square[i][j].edge[2];
                    }else if (Square[i][j].edge[3]!='1') {
                        Square[i+1][j].edge[1] = Square[i][j].edge[3];
                    }
                }else if (j==5&&i!=1&&j!=5) {
                    if(Square[i][j].edge[0]!='1'){
                        Square[i][j-1].edge[3] = Square[i][j].edge[0];   //2=0
                    }else if(Square[i][j].edge[1]!='1'){
                        Square[i-1][j].edge[3] = Square[i][j].edge[1];
                    }else if (Square[i][j].edge[3]!='1') {
                        Square[i+1][j].edge[1] = Square[i][j].edge[3];
                    }
                }else if (i>1&&i<5&&j<1&&j<5) {
                    if(Square[i][j].edge[0]!='1'){
                        Square[i][j-1].edge[3] = Square[i][j].edge[0];   //2=0
                    }else if(Square[i][j].edge[1]!='1'){
                        Square[i-1][j].edge[3] = Square[i][j].edge[1];
                    }else if(Square[i][j].edge[2]!='1'){
                        Square[i][j+1].edge[0] = Square[i][j].edge[2];
                    }else if (Square[i][j].edge[3]!='1') {
                        Square[i+1][j].edge[1] = Square[i][j].edge[3];
                    }
                }
            }

        for(int i = 1;i<6;i++)
            for(int j=1;j<6;j++){
                int freedom = 0;
                for(int k=0;k<4;k++){

                    if(Square[i][j].edge[k]=='1'){
                        freedom++;
                    }

                }
                if(Square[i][j].degree!=freedom){
                    Square[i][j].degree = freedom;
                }
            }
    }



    bool end(Situation Square[6][6]){
        int countA = 0,countB = 0;
        for(int i=1;i<6;i++)
            for(int j=1;j<6;j++){
                if(Square[i][j].ower=='A'){
                    countA++;
                }else if (Square[i][j].ower=='B') {
                    countB++;
                }
            }
        if(countA>12||countB>12){
            return true;
        }else {
            return false;
        }
    }

   void SelectedMaxUCBnode(Situation1 *chesssborad)
   {

        double biggestUCB=0;
        int choiced=-1;  //记录哪个子节点被选中
        UpdateUCB_Value(chesssborad);         //每次选择UCB最大节点前更新所有节点UCB值
        for(int i=0;i<chesssborad->childNum;i++)
        {
            //奇偶层选择UCB策略不一样！！！！！！！！！！！！！！！！！
            if(chesssborad->son[i]->end)
            {
                continue;
            }

            if(chesssborad->occupy==realTurn)
            {
                if(chesssborad->son[i]->ucb>biggestUCB)
                {

                    biggestUCB = chesssborad->son[i]->ucb;
                    choiced = i;
                }
            }

            else
            {
                if(i==0)
                {
                    biggestUCB = chesssborad->son[i]->ucb;
                    choiced = i;
                }
                if(chesssborad->son[i]->ucb<biggestUCB)
                {

                    biggestUCB = chesssborad->son[i]->ucb;
                    choiced = i;
                }
            }

        }

        if(choiced==-1)
        {
//            qDebug()<<"opopopoppoppp"<<chesssborad->childNum<<choiced;
            chesssborad->end = true;
            return;
        }

        if(chesssborad->son[choiced]->childNum!=0)
        {  //若此子节点不是叶节点，则重复直至搜索到叶子节点

            SelectedMaxUCBnode(chesssborad->son[choiced]);  //考虑要不要换手！！！！！！！！！！！
        }
        else
        {

            if(((float)(chesssborad->son[choiced]->winCount)/chesssborad->son[choiced]->count >= 0.6) && chesssborad->son[choiced]->count>=8 && !(ai.Dead(chesssborad->son[choiced]->cheer)))
            {                         //判断子节点是否达到访问次数

                Expand(chesssborad->son[choiced],chesssborad->son[choiced]->occupy);            //扩展子节点

            }
            else
            {   //未达到访问次数
                chesssborad->son[choiced]->count++;  //访问次数+1
                Situation1 *son = chesssborad->son[choiced];
                while (son->parent!=NULL)
                {      //更新父节点访问次数
                    son->parent->count++;
                    son = son->parent;

                }

                int result = Playsimulation(chesssborad->son[choiced],chesssborad->son[choiced]->occupy);
                if(result ==1)
                {
                    chesssborad->son[choiced]->winCount++;   //胜利次数+1
                    Situation1 *Win = chesssborad->son[choiced];
                    while (Win->parent!=NULL)
                    {      //跟新父节点访问次数
                          Win->parent->winCount++;
                          Win = Win->parent;
                    }

                }
            }
        }
    }

    //奇偶层选择UCB策略不一样！！！！！！！！！！！！！！！！！

   /*
    基于并行算法的注解
    新建线程
    初始化根节点
    在系统时间内进行搜索树的扩展与更新操作
    由于扩展节点与模拟棋局都是相对独立，不会更新搜索树数据
    因此并发执行
    但是回溯更新结点与更新UCB值会更新搜索树，因此此时只能串行执行

*/
/*
   void UCTSearch(Situation1 chessborad,bool myturn)
   {
      //搜索时间
       int searchTime = 0;
       //当前棋局
       chu Movelist[61];
       //安全边长度
       int len1 = 0;
       //获得安全边长度
       len1 = move1(chessborad.cheer,Movelist);

       int len2 = 0;
       len2 = ai.heixiazi1(chessborad.cheer,Movelist,len1);
       int len3 = len1 + len2;

       int len4 = 0;
       len4 = ai.heixiazi1(chessborad.cheer,Movelist,len3);
       int len = len3 + len4;

      if(len > 25){
          searchTime = 25;
      }
      else if(len >15 && len <= 25){
          searchTime = 40;
      }
      else if(len >7 && len <= 15){
          searchTime = 16;
      }
      else{
          searchTime = 10;
      }


       qDebug()<<"此时搜索时间:"<<searchTime;
       qDebug()<<"count="<<len;
       qDebug()<<"进入UCT并行算法!!!!!!!!!!"<<myturn;

       Situation1 *root=new Situation1;       //初始化根节点
       realTurn = myturn;

       copy(&chessborad,root);

       //time_t tv;
       tv = time(NULL);                     //得到系统时间以限定搜索时间 time(NULL)-tv<45
       int simulateNum = 0;
       //初始化搜索树
       //可扩展子节点与父节点都为空
       root->childNum=0;
       root->parent = NULL;
       root->occupy = true;
       //当搜索时间内

       while(time(NULL)-tv<searchTime){
           if(root->childNum==0){
                 Expand(root,myturn);  //扩展子节点
           }
           else {   //根据ＵＣＢ值选择节点
               SelectedMaxUCBnode(root);
           }
                                    //删除树
           simulateNum++;
       }
       qDebug()<<"模拟局数："<<simulateNum;
       qDebug()<<"搜索时间道，结束。";
       //选出最佳招法
       double bestcount=0;
       int bestSon = 0;
       for(int i=0;i<root->childNum;i++){
           qDebug()<<"i="<<i;

           qDebug()<<"UCB="<<root->son[i]->ucb
                   <<"wincount="<<root->son[i]->winCount
                   <<"count="<<root->son[i]->count;
           if(root->son[i]->count>bestcount){
               bestcount = root->son[i]->count;
               bestSon = i;
           }
       }
       qDebug()<<"bestson="<<bestSon;

       Compare(root,root->son[bestSon]);
       //删除树
       DeleteTree(root);

   }

   void Expand(Situation1 *root,bool myturn)
   {

       chu Movelist[61];
       int len1 = 0;
       len1 = move1(root->cheer,Movelist);

       int len2 = 0;
       len2 = ai.heixiazi1(root->cheer,Movelist,len1);
       int len3 = len1 + len2;

       int len4 = 0;
       len4 = ai.heixiazi2(root->cheer,Movelist,len3);
       int len = len3 + len4;

       root->childNum = len;
       //生成子节点
       for(int i=0;i<len;i++)
       {
           root->son[i] = new Situation1;
           root->son[i]->parent = root;//指明父节点
           root->son[i]->end = false;
           copy(root,root->son[i]);//复制棋盘
           putcheer(root->son[i]->cheer, Movelist[i].x, Movelist[i].y, Movelist[i].k, myturn);
           //  !chesssborad.child[i]->cheer 对子节点赋值
           //子节点是否占格
           if(opc(root->son[i],myturn)){//如果发生占格

               root->son[i]->occupy = myturn;
           }else{     //未发生占格

               root->son[i]->occupy = !myturn;
           }
       }

       for(int j=0;j<len;j++)
       {
           root->son[j]->count++;  //访问次数+1
           Situation1 *child = root->son[j];
           while (child->parent!=NULL)
           {      //更新父节点访问次数
               child->parent->count++;
               child = child->parent;
           }
           int result = Playsimulation(root->son[j],root->son[j]->occupy);        //模拟下棋  ！此处为对方下棋
           if(result ==1)
           {
               root->son[j]->winCount++;  //胜利次数+1
               Situation1 *Win = root->son[j];
               while (Win->parent!=NULL)
               {      //更新父节点访问次数
                   Win->parent->winCount++;
                   Win = Win->parent;
               }

           }

       }


   }


   int Playsimulation(Situation1 *chess,bool myturn)
   {     //模拟下棋

       Situation1 simul;
       copy(chess,&simul);

       while(!ai.Dead(simul.cheer))
       {//用指定策略下完棋盘

           chu BeforeDead[61];
           int step1 = 0;
           step1 = move1(simul.cheer,BeforeDead);

           int step2 = 0;
           step2 = ai.heixiazi1(simul.cheer,BeforeDead,step1);
           int step3 = step1 + step2;

           int step4 = 0;
           step4 =ai. heixiazi2(simul.cheer,BeforeDead,step3);
           int step = step3 + step4;

           int free_one_x = 0;
           int free_one_y = 0;
           int free_one_k = 0;
           //有格吃格
           for(int x=1;x<6;x++)
               for(int y=1;y<6;y++)
               {
                   if(simul.cheer[x][y].degree==1)
                   {
                       for(int k=0;k<4;k++)
                       {
                           if(simul.cheer[x][y].edge[k]=='1')
                           {
                               free_one_x = x;
                               free_one_y = y;
                               free_one_k = k;
                               break;
                           }
                       }
                   }
               }

           if(free_one_x!=0)
           {
               putcheer(simul.cheer, free_one_x, free_one_y, free_one_k, myturn);
           }
           else
           {
               srand(clock()); //随机函数 随机选一条边
               int i = rand()%step;
               putcheer(simul.cheer, BeforeDead[i].x, BeforeDead[i].y, BeforeDead[i].k, myturn);

           }

           //判断是否占格
           if(opc(&simul,myturn))
           {//如果发生占格

           }
           else
           {     //未发生占格

               myturn = !myturn;
           }


       }

       if(Evaluation(simul.cheer,myturn))
       {   //胜利
           return 1;
       }
       else
       {
           return 0;
       }

   }

*/

   void UCTSearch(Situation1 chessborad, bool myturn)
   {
       int SearchTime = 0;
       Situation1 *root = new Situation1;
       realTurn = myturn;

       chu Movelist[61];
       int len = 0;
       int len1 = 0;
       int len2 = 0;
       int len3 = 0;
       len1 = move1(chessborad.cheer,Movelist);

       if(len1 <= 20){
           len2 = ai.heixiazi1(chessborad.cheer,Movelist,len1);
           len3 = ai.heixiazi2(chessborad.cheer,Movelist,len2);
           len = len3;
           qDebug()<<len;
       }
       else{
           len = len1;
       }
//       if(len1 <= 10){
//           len3 = move2(chessborad.cheer,Movelist);
//           len = len3;
//       }
//       else{
//           len = len1;
//       }
       if(len > 25){
           SearchTime =16;
       }
       else if(len >15 && len <= 25){
           SearchTime = 30;
       }
       else if(len >7 && len <= 15){
           SearchTime = 22;
       }
       else if(len==0)
       {
           SearchTime=0;
       }
       else{
           SearchTime = 13;
       }
       copy(&chessborad,root);

       tv = time(NULL);

       root->childNum = 0;
       root->parent = NULL;
       root->occupy = true;
       int simulateNum = 0;

       for(int i=0;time(NULL)-tv < SearchTime;){
           if(root->childNum == 0){
               Expand(root,myturn);
           }else{
               SelectedMaxUCBnode(root);
           }
           simulateNum++;
           if(simulateNum>10000000)
               break;
       }

       qDebug()<<"模拟局数："<<simulateNum;
       qDebug()<<"搜索时间道，结束。";
       //选出最佳招法
       double bestcount=0;
       int bestSon = 0;
       for(int i=0;i<root->childNum;i++)
       {
           qDebug()<<"i="<<i;

           qDebug()<<"UCB="<<root->son[i]->ucb;
           qDebug()<<"wincount="<<root->son[i]->winCount;
           qDebug()<<"count="<<root->son[i]->count;

           if(root->son[i]->count>bestcount){
               bestcount = root->son[i]->count;
               bestSon = i;
           }
       }
       qDebug()<<"bestson="<<bestSon;

       Compare(root,root->son[bestSon]);
       //删除树
       DeleteTree(root);

   }
  void Expand(Situation1 *root, bool myturn)
   {
        chu Movelist[61];
        int len = 0;
        int len1 = 0;
        int len2 = 0;
        int len3 = 0;
        len1 = move1(root->cheer,Movelist);

        if(len1 <= 20){
            len2 = ai.heixiazi1(root->cheer,Movelist,len1);
            len3 = ai.heixiazi2(root->cheer,Movelist,len2);
            len = len3;
        }
        else{
            len = len1;
        }
//        if(len1 <= 10){
//            len3 =move2(root->cheer,Movelist);
//            len = len3;
//        }
//        else{
//            len = len1;
//        }
//        QString tcs("");
//        QString mu("");
        root->childNum = len;
       //生成子节点
//        r1.m_ip = "127.0.0.1";
//        r1.m_port = 6379;
//        r1.ConnectRedis();
       for(int i=0;i<len;i++)
       {
           root->son[i] = new Situation1;
           root->son[i]->parent = root;//指明父节点
           root->son[i]->end = false;
           copy(root,root->son[i]);//复制棋盘
//           tcs.append(QString::fromStdString(bak(root->son[i])));
           putcheer(root->son[i]->cheer, Movelist[i].x, Movelist[i].y, Movelist[i].k, myturn);
           //  !chesssborad.child[i]->cheer 对子节点赋值
           //子节点是否占格
           if(opc(root->son[i],myturn)){//如果发生占格
               root->son[i]->occupy = myturn;
           }else{     //未发生占格
//               tcs.append(QString::number(Movelist[i].x));
//               tcs.append(QString::number(Movelist[i].y));
//               tcs.append(QString::number(Movelist[i].k));
//               QString u="get ";
//               u.append(tcs);
//               r1.m_cmd =u.toLatin1().data();
//               r1.ExecRedis();
//               u="";
//               u.append(r1.m_reply->str);
//               r1.FreeReply();
//               mu.append(u);
//               if(tcs.size()>63)
//                   qDebug()<<"02000000000**************************/*/*/-*/*/---/7*/*--*/-+02000000000**************************/*/*/-*/*/---/7*/*--*/-+02000000000**************************/*/*/-*/*/---/7*/*--*/-+02000000000**************************/*/*/-*/*/---/7*/*--*/-+02000000000**************************/*/*/-*/*/---/7*/*--*/-+02000000000**************************/*/*/-*/*/---/7*/*--*/-+02000000000**************************/*/*/-*/*/---/7*/*--*/-+02000000000**************************/*/*/-*/*/---/7*/*--*/-+02000000000**************************/*/*/-*/*/---/7*/*--*/-+02000000000**************************/*/*/-*/*/---/7*/*--*/-+02000000000**************************/*/*/-*/*/---/7*/*--*/-+02000000000**************************/*/*/-*/*/---/7*/*--*/-+02000000000**************************/*/*/-*/*/---/7*/*--*/-+02000000000**************************/*/*/-*/*/---/7*/*--*/-+02000000000**************************/*/*/-*/*/---/7*/*--*/-+02000000000**************************/*/*/-*/*/---/7*/*--*/-+";
//               if(mu.indexOf(",")>0&&tcs.size()==63){
//               QStringList ql=mu.split(",");
//               root->son[i]->winCount+=ql.at(0).toInt();
//               root->son[i]->count+=ql.at(1).toInt();
//               qDebug()<<tcs;
//               qDebug()<<mu;
//               qDebug()<<root->son[i]->winCount<<endl<<root->son[i]->count;
//               ql.clear();
//               }
//               if(root->son[i]->count>100)
//                   {
//                   root->son[i]->winCount=floor((root->son[i]->winCount/root->son[i]->count)*100);
//               }
               root->son[i]->occupy = !myturn;
           }
//           tcs="";
//           mu="";
       }
//           r1.FreeRedis();
       for(int j=0;j<len;j++)
       {
           root->son[j]->count++;  //访问次数+1
           Situation1 *child = root->son[j];
           while (child->parent!=NULL)
           {      //更新父节点访问次数
               child->parent->count++;
               child = child->parent;
           }
           int result = Playsimulation(root->son[j],root->son[j]->occupy);        //模拟下棋  ！此处为对方下棋
           if(result ==1)
           {
               root->son[j]->winCount++;  //胜利次数+1
               Situation1 *Win = root->son[j];
               while (Win->parent!=NULL)
               {      //更新父节点访问次数
                   Win->parent->winCount++;
                   Win = Win->parent;
               }

           }

       }

   }
  string bak(Situation1 *chess)
  {
      Situation1 simul;
      copy(chess,&simul);
      string hms("");
      for(int j=1;j<6;j++)
      {
          for(int i=1;i<6;i++)
          {
              if(simul.cheer[i][j].edge[0]=='1')
                  hms.append("0");
              else
                  hms.append("1");
          }
          for(int i=1;i<6;i++)
          {
              if(simul.cheer[i][j].edge[1]=='1')
                  hms.append("0");
              else
                  hms.append("1");
              if(i==5)
              {
                  if(simul.cheer[i][j].edge[3]=='1')
                      hms.append("0");
                  else
                      hms.append("1");
              }
          }
          if(j==5)
          {
              for(int i=1;i<6;i++)
              {
                  if(simul.cheer[i][j].edge[2]=='1')
                      hms.append("0");
                  else
                      hms.append("1");
              }
          }
  }return hms;
    }
    QString rlcg(QString s)
    {
        if(s.size()!=63)
            return "-1";
        QString str("");
        int j=0;
        while(j<60){
        for(int i=0;i<5;i++)
        {
            str.append(s.mid(j+4-i,1));
        }
        j+=5;
        for(int i=0;i<6;i++)
        {
            if(j+5-i>60)
                break;
            str.append(s.mid(j+5-i,1));
        }
        j+=6;
        }
        str.append(QString::number(6-s.mid(60,1).toInt()));
        str.append(s.mid(61,1));
        if(s.mid(62,1)=="0"||s.mid(62,1)=="2")
            str.append(s.mid(62,1));
        else if(s.mid(62,1)=="1")
            str.append("3");
        else if(s.mid(62,1)=="3")
            str.append("1");
        return str;
    }
    QString xycg(QString s)
    {
        if(s.size()!=63)
            return "-1";
        QStringList ql;
        int j=0;
        while(j<60){
            ql.append(s.mid(j,5));
            j+=5;
            if(j==59)
                break;
            ql.append(s.mid(j,6));
            j+=6;
        }
        QString str("");
        str.append(ql.at(0));
        ql.replace(0,ql.at(10));
        ql.replace(10,str);
        str="";
        str.append(ql.at(1));
        ql.replace(1,ql.at(9));
        ql.replace(9,str);
        str="";
        str.append(ql.at(2));
        ql.replace(2,ql.at(8));
        ql.replace(8,str);
        str="";
        str.append(ql.at(3));
        ql.replace(3,ql.at(7));
        ql.replace(7,str);
        str="";
        str.append(ql.at(4));
        ql.replace(4,ql.at(6));
        ql.replace(6,str);
        str="";
        for(int i=0;i<=10;i++)
        {
            str.append(ql.at(i));
        }
        str.append(s.mid(60,1));
        str.append(QString::number(6-s.mid(61,1).toInt()));
        if(s.mid(62,1)=="1"||s.mid(62,1)=="3")
            str.append(s.mid(62,1));
        else if(s.mid(62,1)=="0")
            str.append("2");
        else if(s.mid(62,1)=="2")
            str.append("0");
        return str;
        }
    //新
    int Playsimulation(Situation1 *chess,bool myturn)
    {     //模拟下棋

        Situation1 simul;
        copy(chess,&simul);
        while(!ai.Dead(simul.cheer))
        {//用指定策略下完棋盘

            chu BeforeDead[61];
            int step = 0;
            int step1 = 0;
            int step2 = 0;
            int step3 = 0;
            step1 = move1(simul.cheer,BeforeDead);
            if(step1 <= 10){
                step2 = ai.heixiazi1(simul.cheer,BeforeDead,step1);
                step3 = ai.heixiazi2(simul.cheer,BeforeDead,step2);
                step = step3;
            }
            else{
                step = step1;
            }

            int free_one_x = 0;
            int free_one_y = 0;
            int free_one_k = 0;
            //有格吃格
            for(int x=1;x<6;x++)
                for(int y=1;y<6;y++)
                {
                    if(simul.cheer[x][y].degree==1)
                    {
                        for(int k=0;k<4;k++)
                        {
                            if(simul.cheer[x][y].edge[k]=='1')
                            {
                                free_one_x = x;
                                free_one_y = y;
                                free_one_k = k;
                                break;
                            }
                        }
                    }
                }

            if(free_one_x!=0)
            {
                putcheer(simul.cheer, free_one_x, free_one_y, free_one_k, myturn);
            }
            else
            {
                srand(clock()); //随机函数 随机选一条边
                int i = rand()%step;
                putcheer(simul.cheer, BeforeDead[i].x, BeforeDead[i].y, BeforeDead[i].k, myturn);
            }

            //判断是否占格
            if(opc(&simul,myturn))
            {//如果发生占格

            }
            else
            {     //未发生占格

                myturn = !myturn;
            }


        }

        if(Evaluation(simul.cheer,myturn))
        {   //胜利
            return 1;
        }
        else
        {
            return 0;
        }
    }

    void DeleteTree(Situation1 *chesssborad){

        for(int i=0;i<chesssborad->childNum;i++){
            if(chesssborad->son[i]->childNum!=0){
                DeleteTree(chesssborad->son[i]);
            }
            delete chesssborad->son[i];
        }
    }

    void Compare(Situation1 *parent,Situation1 *son){
        int num = 0;
        for(int x = 1;x<6;x++)
            for(int y=1;y<6;y++)
                for(int k=0;k<4;k++){
                    if(son->cheer[x][y].edge[k]=='*'&&parent->cheer[x][y].edge[k]!='*'){
                        num++;
                        Bestmove.x = x;
                        Bestmove.y = y;
                        Bestmove.k = k;
                    }
                }
          if(num!=2){
              qDebug()<<"错误！！！num为："<<num;

          }
    }

    void UpdateUCB_Value(Situation1 *chesssborad)
    {
        double totalVisitedCount = 0;
        for(int i=0;i<chesssborad->childNum;i++){
            totalVisitedCount=totalVisitedCount+chesssborad->son[i]->count;
        }

        for(int i=0;i<chesssborad->childNum;i++)
        {
            //准确估值函数
            chesssborad->son[i]->ucb = chesssborad->son[i]->winCount/chesssborad->son[i]->count
                    +0.3*sqrt(1*log(totalVisitedCount)/chesssborad->son[i]->count);

        }
    }
};


#endif // AI_UCT_H
