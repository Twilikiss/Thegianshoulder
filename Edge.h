 #ifndef EDGE_H
#define EDGE_H


class Edge
{
public:
    Edge();
    Edge(int line, int queue) {
        this->line = line;
        this->queue = queue;
    }
    Edge(int line, int queue, int check) {
        this->line = line;
        this->queue = queue;
        this->check = check;
    }
    void set1(int check) {
        this->check = check;
    }
    void set(int x, int y, int z) {
        this->line = x;
        this->queue = y;
        this->check = z;
    }

    //属性
    int line;               //边所在行数
    int queue;              //边所在列数
    int check;             //边是否被占，未被占0，被我方占"*",对方占“#”

};

#endif // EDGE_H
