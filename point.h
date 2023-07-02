#ifndef POINT_H
#define POINT_H


class Point
{
public:
    Point();


    int row;   //行坐标
    int col;   //列坐标
    int id;    //编号
    int line[4];  //连线编号
    int colour[4];   //线的颜色


};

#endif // POINT_H
