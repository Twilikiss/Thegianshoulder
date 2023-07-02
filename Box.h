#ifndef BOX_H
#define BOX_H


class Box
{
public:
    Box();
    Box(int line, int queue) {
        this->line = line;
        this->queue = queue;
    }
    Box(int x, int y, bool z) {
        this->line = x;
        this->queue = y;
        this->check = z;
    }

    void set(int x, int y, bool z) {
        this->line = x;
        this->queue = y;
        this->check = z;
    }

    //属性
    int line;               //格子所在行数
    int queue;              //格子所在列数
    bool check;
};

#endif // BOX_H
