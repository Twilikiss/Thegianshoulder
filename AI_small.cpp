
#include"AI_small.h"
#include"Situation1.h"

#include"widget.h"
#include<QMessageBox>
#include<QTimer>
#include<QDebug>
#include"Ai_uct.h"

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
#define random(x)(rand()%x)
#define Max_deep	8				//模糊搜索最大深度
#define Max_len		25				//精确深度最大深度
using namespace std;


AI_small::AI_small()
{

}

//相互占领边函数，减去 领边自由度(自己边已经在占边的时候减去自由度了)
void AI_small::mutualoccupy1(Situation Square[6][6], int x, int y, int k)
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

int AI_small::SingleChain(Situation Square[6][6], int x, int y)
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

int AI_small::DoubleChain(Situation Square[6][6], int x, int y)     //判断双链的情况
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

int AI_small::Triple_Freedom(Situation Square[6][6], int x, int y)                //判断某三自由度格的情况
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

int AI_small::Count_AntDoublecorse(Situation Square[6][6])    //查找反双交的个数
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

bool AI_small::Dead(Situation Square[6][6])   //判断是否任何一条边下上去都是死格，若是返回true，即任何一步都会形成一死格//否，返回false。
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

void AI_small::copy1(Situation  from[6][6], Situation  to[6][6])
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

int AI_small::heixiazi1(Situation Square[6][6],chu *move, int len){
    int s = 0;

    //左上
    if(Square[1][1].edge[2] == '1' && Square[1][1].edge[3] == '1' && Square[1][1].degree >2){
        if(Square[1][2].edge[1] == '1' && Square[2][1].edge[0] == '1'){
            if(Square[1][2].edge[2] != '1' && Square[1][2].edge[3] != '1'){
                if(Square[2][1].edge[2] != '1' && Square[2][1].edge[3] != '1'){
                    move[len].x = 1;
                    move[len].y = 1;
                    move[len].k = 2;
                    len++;
                    s++;
                }
            }
        }
        else if(Square[1][2].edge[1] != '1' && Square[2][1].edge[0] == '1'){
            if(Square[1][3].edge[0] == '1' && Square[1][3].edge[1] == '1'){
                if(Square[1][3].edge[2] != '1' && Square[1][3].edge[3] != '1'){
                    if(Square[1][2].edge[3] != '1'){
                        if(Square[2][1].edge[2] != '1' && Square[2][1].edge[3] != '1'){
                            move[len].x = 1;
                            move[len].y = 2;
                            move[len].k = 2;
                            len++;
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
                            move[len].x = 2;
                            move[len].y = 1;
                            move[len].k = 3;
                            len++;
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
                    move[len].x = 1;
                    move[len].y = 5;
                    move[len].k = 3;
                    len++;
                    s++;
                }
            }
        }
        else if(Square[1][4].edge[1] != '1' && Square[2][5].edge[2] == '1'){
            if(Square[1][3].edge[1] == '1' && Square[1][3].edge[2] == '1'){
                if(Square[1][3].edge[0] != '1' && Square[1][3].edge[3] != '1'){
                    if(Square[1][4].edge[3] != '1'){
                        if(Square[2][5].edge[0] != '1' && Square[2][5].edge[3] != '1'){
                            move[len].x = 1;
                            move[len].y = 3;
                            move[len].k = 2;
                            len++;
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
                            move[len].x = 2;
                            move[len].y = 5;
                            move[len].k = 3;
                            len++;
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
                    move[len].x = 5;
                    move[len].y = 1;
                    move[len].k = 1;
                    len++;
                    s++;
                }
            }
        }
        else if(Square[5][2].edge[3] != '1' && Square[4][1].edge[0] == '1'){
            if(Square[5][3].edge[0] == '1' && Square[5][3].edge[3] == '1'){
                if(Square[5][3].edge[1] != '1' && Square[5][3].edge[2] != '1'){
                    if(Square[5][2].edge[1] != '1'){
                        if(Square[4][1].edge[1] != '1' && Square[4][1].edge[2] != '1'){
                            move[len].x = 5;
                            move[len].y = 2;
                            move[len].k = 2;
                            len++;
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
                            move[len].x = 4;
                            move[len].y = 1;
                            move[len].k = 1;
                            len++;
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
                    move[len].x = 5;
                    move[len].y = 5;
                    move[len].k = 0;
                    len++;
                    s++;
                }
            }
        }
        else if(Square[5][4].edge[3] != '1' && Square[4][5].edge[2] == '1'){
            if(Square[5][3].edge[2] == '1' && Square[5][3].edge[3] == '1'){
                if(Square[5][3].edge[0] != '1' && Square[5][3].edge[1] != '1'){
                    if(Square[5][4].edge[1] != '1'){
                        if(Square[4][5].edge[0] != '1' && Square[4][5].edge[1] != '1'){
                            move[len].x = 5;
                            move[len].y = 3;
                            move[len].k = 2;
                            len++;
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
                            move[len].x = 4;
                            move[len].y = 5;
                            move[len].k = 1;
                            len++;
                            s++;
                        }
                    }
                }
            }
        }
    }

    return len;
}

//单向三格长链找着法
int AI_small::heixiazi2(Situation Square[6][6], chu *move, int len){
    int s = 0;

    //左上横
    if(Square[1][1].edge[0] == '1' && Square[1][1].edge[2] == '1'){
        if(Square[1][3].edge[0] == '1' && Square[1][3].edge[1] == '1'){
            if(!(Square[1][1].edge[1] != '1' && Square[1][2].edge[1] != '1')){
                if(Square[1][1].edge[3] != '1'){
                    if(Square[1][2].edge[3] != '1'){
                        if(Square[1][3].edge[2] != '1' && Square[1][3].edge[3] != '1'){
                            if(Square[1][1].edge[1] != '1'){
                                move[len].x = 1;
                                move[len].y = 1;
                                move[len].k = 2;
                                len++;
                                s++;
                            }
                            else if(Square[1][2].edge[1] != '1'){
                                move[len].x = 1;
                                move[len].y = 2;
                                move[len].k = 2;
                                len++;
                                s++;
                            }
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
                            if(Square[1][1].edge[0] != '1'){
                                move[len].x = 1;
                                move[len].y = 1;
                                move[len].k = 3;
                                len++;
                                s++;
                            }
                            else if(Square[2][1].edge[0] != '1'){
                                move[len].x = 2;
                                move[len].y = 1;
                                move[len].k = 3;
                                len++;
                                s++;
                            }
                        }
                    }
                }
            }
        }
    }

    //右上横
    if(Square[1][5].edge[0] == '1' && Square[1][5].edge[2] == '1'){
        if(Square[1][3].edge[1] == '1' && Square[1][3].edge[2] == '1'){
            if(!(Square[1][4].edge[1] != '1' && Square[1][5].edge[1] != '1')){
                if(Square[1][5].edge[3] != '1'){
                    if(Square[1][4].edge[3] != '1'){
                        if(Square[1][3].edge[0] != '1' && Square[1][3].edge[3] != '1'){
                            if(Square[1][4].edge[1] != '1'){
                                move[len].x = 1;
                                move[len].y = 4;
                                move[len].k = 1;
                                len++;
                                s++;
                            }
                            else if(Square[1][5].edge[1] != '1'){
                                move[len].x = 1;
                                move[len].y = 5;
                                move[len].k = 1;
                                len++;
                                s++;
                            }
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
                            if(Square[1][5].edge[2] != '1'){
                                move[len].x = 1;
                                move[len].y = 5;
                                move[len].k = 3;
                                len++;
                                s++;
                            }
                            else if(Square[2][5].edge[2] != '1'){
                                move[len].x = 2;
                                move[len].y = 5;
                                move[len].k = 3;
                                len++;
                                s++;
                            }
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
                            if(Square[5][1].edge[3] != '1'){
                                move[len].x = 5;
                                move[len].y = 1;
                                move[len].k = 2;
                                len++;
                                s++;
                            }
                            else if(Square[5][2].edge[3] != '1'){
                                move[len].x = 5;
                                move[len].y = 2;
                                move[len].k = 2;
                                len++;
                                s++;
                            }
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
                            if(Square[4][1].edge[0] != '1'){
                                move[len].x = 4;
                                move[len].y = 1;
                                move[len].k = 1;
                                len++;
                                s++;
                            }
                            else if(Square[5][1].edge[0] != '1'){
                                move[len].x = 5;
                                move[len].y = 1;
                                move[len].k = 1;
                                len++;
                                s++;
                            }
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
                            if(Square[5][4].edge[3] != '1'){
                                move[len].x = 5;
                                move[len].y = 4;
                                move[len].k = 0;
                                len++;
                                s++;
                            }
                            else if(Square[5][5].edge[3] != '1'){
                                move[len].x = 5;
                                move[len].y = 5;
                                move[len].k = 0;
                                len++;
                                s++;
                            }
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
                            if(Square[4][5].edge[2] != '1'){
                                move[len].x = 4;
                                move[len].y = 5;
                                move[len].k = 1;
                                len++;
                                s++;
                            }
                            else if(Square[5][5].edge[2] != '1'){
                                move[len].x = 5;
                                move[len].y = 5;
                                move[len].k = 1;
                                len++;
                                s++;
                            }
                        }
                    }
                }
            }
        }
    }

    return len;
}

int AI_small::three_count(Situation Square[6][6], int *Num2_2)
{
//    qDebug()<<"进入某三自由度统计";
    Situation To[6][6];
    copy1(Square,To);

    for(int i=1; i<6; i++){
        for(int j=1; j<6; j++){
            //找某三自由度
            if(To[i][j].degree == 3){
//                qDebug()<<"出现某三自由度位置 "<<"x="<<i<<" y="<<j;
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
//                qDebug()<<"下三边";
                for(int x=0; x<3; x++){
//                    qDebug()<<"下"<<BeforeDead[x].k<<"边";
                    Situation to[6][6];
                    copy1(To,to);

                    //若果相邻的格子是另一某三自由度格子的私有短链，则不下该边，直接跳到下一边
                    if(BeforeDead[x].k == 0)
                    {
                        //如果是另一某三自由度格子的私有短链
                        if(to[BeforeDead[x].x][BeforeDead[x].y -1].degree == -1)
                        {
//                            qDebug()<<"出现共享短链";
                            //把该短链变成共有短链
                            To[BeforeDead[x].x][BeforeDead[x].y - 1].degree = -2;
                            for(int s=0; s<4; s++){
                                if((s != 2) && (to[BeforeDead[x].x][BeforeDead[x].y -1].edge[s] == '1')){
//                                    qDebug()<<"延伸方向"<<s;
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
//                            qDebug()<<"出现共享短链";
                            //把该短链变成共有短链
                            To[BeforeDead[x].x -1][BeforeDead[x].y ].degree = -2;
                            for(int s=0; s<4; s++){
                                if((s != 3) && (to[BeforeDead[x].x -1][BeforeDead[x].y].edge[s] == '1')){
//                                    qDebug()<<"延伸方向"<<s;
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
//                            qDebug()<<"出现共享短链";
                            //把该短链变成共有短链
                            To[BeforeDead[x].x][BeforeDead[x].y +1].degree = -2;
                            for(int s=0; s<4; s++){
                                if((s != 0) && (to[BeforeDead[x].x][BeforeDead[x].y +1].edge[s] == '1')){
//                                    qDebug()<<"延伸方向"<<s;
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
//                            qDebug()<<"出现共享短链";
                            //把该短链变成共有短链
                            To[BeforeDead[x].x +1][BeforeDead[x].y].degree = -2;
                            for(int s=0; s<4; s++){
                                if((s != 1) && (to[BeforeDead[x].x +1][BeforeDead[x].y].edge[s] == '1')){
//                                    qDebug()<<"延伸方向"<<s;
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

//                    qDebug()<<"该方向无共享短链";
                    int three_x = BeforeDead[x].x;
                    int three_y = BeforeDead[x].y;
                    int three_k = BeforeDead[x].k;

                    to[BeforeDead[x].x][BeforeDead[x].y].edge[BeforeDead[x].k] = '*';
                    to[BeforeDead[x].x][BeforeDead[x].y].degree--;
                    mutualoccupy1(to, BeforeDead[x].x,BeforeDead[x].y,BeforeDead[x].k);

                    int count = 0;
                    int eat = 0;
//                    qDebug()<<"计算支链长度";
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
                        if(eat > 8) break;

                    }

//                    qDebug()<<"有"<<eat<<"格链";
                    //如果是短链，则把它变成私有的
                    if(eat <= 2)
                    {
                        int three_xx = 0;
                        int three_yy = 0;
                        int three_kk = 0;
//                        qDebug()<<"有"<<eat<<"格短链";
//                        qDebug()<<"变私有1";
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
                            goto line_f;
                        }
                        else{
//                            qDebug()<<"变私有2";
                            To[three_xx][three_yy].degree = -1;
                        }
//                        qDebug()<<"结束设置变私有短链";
                    }
line_f:             ;
                }
//                qDebug()<<"结束查看一个某三自由度格子";
            }
        }
    }

//    qDebug()<<"开始全局统计";
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
                    }
                }
                if((siyou != 0) && (gongyou != 0)){
                    Pri_Pub++;   //公私
                }
            }
        }
    }

//    qDebug()<<"ceshi2";
    int num = 0;
    if((Public == 0) && (Pri_Pub == 0)){
        num = Private;
    }
    if(Pri_Pub >= 2){
        Num2_2[0] = Pri_Pub;  //个数不确定性，不参与统计，结合先后手另作评估
    }
    if((Public != 0) && (Pri_Pub == 0)){
        if(Public >= 1 && Public <= 3){
            num = Private + 1;   //3个以内只有一个 （主要针对2个的情况）
        }
        if(Public >= 4 && Public <= 5){
            num = Private + 2;
        }
        else{
            num = Private + 3;  //5*5的棋盘很难出现超过6个，6个已经是极限
        }
    }
    if((Public != 0) && (Pri_Pub != 0)){
        if((Public == 1) && (Pri_Pub == 1)){
            num = Private + 1;
        }
        if((Public == 2) && (Pri_Pub == 1)){
            if(gongyou_II == 0){
                num = Private +1;
            }
            else{
                Num2_2[1] = gongyou_II;
            }
        }
        else{
            Num2_2[1] = gongyou_II;
        }
    }
//    qDebug()<<num;
//    qDebug()<<"结束全局统计";
    return num;
}
