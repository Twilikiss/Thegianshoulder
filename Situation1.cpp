#include "Situation1.h"

Situation1::Situation1()
{
        for (int i = 0; i<6; i++)
            for (int j = 0; j < 6; j++) {
                cheer[i][j].degree = 0;
                cheer[i][j].edge[0] = '1';
                cheer[i][j].edge[1] = '1';
                cheer[i][j].edge[2] = '1';
                cheer[i][j].edge[3] = '1';
                cheer[i][j].ower = ' ';
            }

}
