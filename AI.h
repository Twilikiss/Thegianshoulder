#ifndef AI_H
#define AI_H
#include"widget.h"
#include"Situation1.h"
#include"situation.h"
#include <string>
#include"ThreadForAI.h"
using namespace  std;
extern string path ;
//最终版本
class AI:public Widget
{
        Q_OBJECT
public:
    AI();
    ~AI();
    int find_free3(Situation Square[6][6]);
    int find_free1(Situation Square[6][6]);
    void bianli(Situation Square[6][6]);
    //对接所用函数
    void ContinueEat(); //给线程执行的
    void CheckFreeom(Situation Square[6][6]);
    int Chain_lenth2(Situation Square[6][6], int i, int j);
    void None_Antdoublecorse2(Situation Square[6][6], int turn)	;
    void  Winner();
    void Order(Situation Square[6][6], int myturn, int turn);
    int SingleChain(Situation Square[6][6], int x, int y);
    int DoubleChain(Situation Square[6][6], int x, int y);
    int Triple_Freedom(Situation Square[6][6], int x, int y);
    int Count_AntDoublecorse(Situation Square[6][6]);
    int UCT_Count_AntDoublecorse(Situation Square[6][6]);
    bool Dead(Situation Square[6][6]);
    void deleteFree2(int x,int y);
    int Evaluation(Situation Square[6][6], int Turn);
    void Kill();
    void hecheer(Situation Square[6][6]);
    void mutualoccupy1(Situation Square[6][6], int x, int y, int k);
    bool Dead1(Situation Square[6][6], int i, int j, int k, int turn);
    void zhuanhuan(Situation1 bt);
    int randmove(Situation Square[6][6], int turn);
    void Put_chessboard(Situation Square[6][6], int etype, int i, int j, int turn);
    int Give_Boxes_Oven(Situation Square[6][6], int turn);
    int Give_Boxes_Odd(Situation Square[6][6], int turn);
    int Chain_lenth(Situation Square[6][6], int i, int j);
    int Eat_Chain(Situation Square[6][6], int i, int j, int len, int turn);
    void None_Antdoublecorse(Situation Square[6][6], int turn);
    void Min_Give_Box(Situation Square[6][6], int turn);
    void Eat_a_chain(Situation Square[6][6], int i, int j, int len, int turn);
    void Eat_all_box(Situation Square[6][6], int turn);
    void Odd_Number_Doublecorse(Situation Square[6][6], int turn);
    void Oven_Number_Doublecorse(Situation Square[6][6], int turn);
    void Final_Occupy(Situation Square[6][6], int turn);
    void putedge(Situation Square[6][6]);
    void opc(Situation Square[6][6], int turn);
    int Search(int deep, int alpha, int beta, int turn);
    bool Method1(Situation Square[6][6], int turn);
    void copy(Situation1  from, Situation1  to);
    void copy1(Situation  from[6][6], Situation  to[6][6]);
    void putcheer(Situation Square[6][6], int x, int y, int k, int turn);
    int Triple_Freedom1(Situation Square[6][6], int x, int y) ;
   // void copy2(zhSituation1  from[60], zhSituation1  to[60]);
    int  Dead2(Situation  Square[6][6]);
    int move(Situation Square[6][6], chu *move);
    int move1(Situation Square[6][6], chu move[61]);
    void mutualoccupy2(Situation Square[6][6], int x, int y, int k);
    void Order1(Situation Square[6][6], int myturn, int turn);
    void Order2(int turn);
    int wulian(Situation Square[6][6]);
    void initialMaybe();
    void deleteFree2_Cicle(int x,int y);
    bool CheckCircle(int x,int y);
    int Find_Circle(Situation Square[6][6], int i, int j);
    int Search1(int deep, int alpha, int beta, int turn);
    void Find_GuaiDian(Situation Square[6][6]);
    void Initial_All();
    bool Equal(Situation first[6][6],Situation next[6][6]);
    void action_move(Situation Square[6][6], bool myturn);
    void action_move1(Situation Square[6][6], bool myturn);
    bool tiaojian1(Situation Square[6][6]);
    bool tiaojian2(Situation Square[6][6]);
    int three_count(Situation Square[6][6], chu *move);
    int Evaluation_I(Situation Square[6][6], int Turn);
    int heixiazi1(Situation Square[6][6]);
    int heixiazi2(Situation Square[6][6]);

    //属性

    int doubcount = 0;
    int index = 0;
    int Searched[6][6];
    int chaincount;//可下边条数计数器
    int text;//辅助计数器1
    int text1;//辅助计数器2
    int mycount;//我方占领数目
    int hecount;//敌方占领数目

    int  myturn;//1为先手，0为后手
    int turn;//标记轮数，1为 我方，2为对方

    int chain_type;
    int endx, endy;
    int s[10];//链长存储器
    int leni;
    chu Bestmove;
    int chi;
    int singlechain = 0;
    int doublechain = 0;
    int fanshuagnjiao = 0;
    int guaidian=0;

    //线程专用
    ThreadForAI ai_thread1;



    //界面所用函数
    virtual int click(int row,int col);
    void getchecksline(int x,int y,int k);
    int getcheerrowcol(int select,int click);  //由边转换成，格子边
    void yichang();
  //  virtual void timerEvent(QTimerEvent *event);  //计时器


public slots:
    void AIMove();
    void Threadfinish();   //线程用

};

#endif // AI_H
