#ifndef WIDGET_H
#define WIDGET_H

//#include <QWidget>
//#include <QPainter>
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




namespace Ui {
class Widget;
}

class Widget : public QFrame
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    Point _p[36];  //定义36个原点
    Checks _g[5][5];    //格子
    int qipu;           //棋谱先后手相关
    int _selected;      //确定的上一个点击原点
    int _clickid;       //当前点击原点
    bool player;        //当前玩家
    int countblack;     //黑方占领格子数
    int countwhite;     //白方占领格子数
    void drawpoint(QPainter& painter,int id );    //画原点函数。
    QPoint center(int row,int col );
    bool getrowcol(QPoint pt, int& row ,int& col);
    void CountEdge(int click,int selcet,bool player);   //相互占格函数
    void click(QPoint ev);
    virtual int click(int row,int col);
    void click(int id);
    void saveSteps(int point_1,int point_2);     //保存下子棋谱
    void switch_cheerstep(int row,int col,QString direction);      //把行列值转换为标准棋谱值
    void backstep_ui(int id);   //界面悔棋
    void backstep_board(int id);//棋盘悔棋

    //界面所用属性
    int dist;       //间距
    int _r;         //半径
    int temp;       //标志，连线
    int choice;         //是否选择先后手
    int tempchoice;     //用于取消选取点
    int tempselect;     //暂时储存点击点
    int tempclick;
    bool go;            //占格后是否继续
    int timeblack;      //黑方时间
    int timewhite;      //白方时间
    int retb;
    int retw;
    //悔棋用
    int back_ui[60][4];    //界面存10步棋（原点，线号）X2
    int back_board[60][2]; //棋盘存两个（原点，原点）
    int back_box[60][6];   //消除格子影响
    int back_player[60];   //存储下棋方
    int backcount;         //悔棋索引
    int temp_backcount;    //temp索引
    int bignum;            //初始化线值
    int final1_x,final1_y;  //第一个格子
    int final2_x,final2_y;  //第二个格子，便于封装
    int final_line1;         //最后的一条线
    int final_line2;
    bool isback;           //判断是否执行过悔棋

    Situation  factcheer[6][6];     //实际中这个棋盘的格子表示

    //棋谱所用对象
    int edgeCount;      //已下边
    QJsonArray steps;   //保存标准棋谱的GAME键值
    QJsonObject RB_step[60];    // 红蓝方的下子



protected:
    void mouseReleaseEvent(QMouseEvent *ev);  //鼠标点击事件
    void paintEvent(QPaintEvent *);         //绘图事件
    virtual void timerEvent(QTimerEvent *ev);  //计时器

public slots:
    void on_whitecancel_clicked();

private slots:
    void on_blackfirst_clicked();

    void on_whitefirst_clicked();

    void on_save_clicked();

    void on_blackok_clicked();

    void on_whiteok_clicked();

    //void on_whitecancel_clicked();

    void on_blackcancel_clicked();

    void on_esc_clicked();

    void on_backstep_clicked();

signals:
    void Realboard_backstep(int id);


private:
    Ui::Widget *ui;
    QThread* m_currentRunLoaclThread;


};

#endif // WIDGET_H
