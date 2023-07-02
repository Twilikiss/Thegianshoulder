#include "widget.h"
#include "ui_widget.h"
#include "point.h"
#include<QPainter>
#include<QPoint>
#include<QPen>
#include<QMouseEvent>
#include<QDebug>
#include<QMessageBox>
#include"AI.h"
#include<QFileDialog>
#include<QDataStream>
#include<QTimerEvent>
#include<QString>
#include<QJsonArray>
#include<QJsonObject>
#include<QJsonDocument>
#include<QJsonValue>
#include<QFile>
#include<QTextStream>
#include<QDateTime>
int bko=-1;
int bkt=-1;
Widget::Widget(QWidget *parent)  : QFrame(parent)
    ,
    ui(new Ui::Widget)
{

    isback=false;   //悔棋标志初始化
    final1_x=final1_y=final2_x=final2_y=final_line1=final_line2=0;
    bignum=100000;  //线值
    backcount=0;    //悔棋索引
    edgeCount=-1;   //已下边
    retb=0;
    retw=0;
    ui->setupUi(this);
    dist=50;   //点之间的间隔
    _r=6 ;     //原点半径为4 像素点
    _selected=-1;
    _clickid=-1;
    tempselect=0;
    tempclick=0;
    temp=0;
    choice=0;
    qipu=0;
    go=true;        //  判断是否连续占格
    countblack=0;   //  敌方占格
    countwhite=0;   //  我方占格
    timeblack=0;    //  地方时间
    timewhite=0;    //  我方时间
    ui->blacktime->setText("<center><h1>Time: 00:00</h1></center>");
    ui->whitetime->setText("<center><h1>Time: 00:00</h1></center>");

  //  timeblack=this->startTimer(1000);
  //  timewhite=this->startTimer(500);

    //初始化原点
    for(int i=0;i<6;i++)
    {
        for(int j=0;j<6;j++)
        {
            _p[i*6+j].row=i;     //行位置
            _p[i*6+j].col=j;     //列位置
            _p[i*6+j].id=i*6+j;  //id号
            if(i<5&&j<5)
            {
                //初始化格子下标
                _g[i][j].row=i;
                _g[i][j].col=j;
            }
        }
    }

    for (int i = 1; i < 6; i++) {

        for (int j = 1; j < 6; j++) {

            factcheer[i][j].ower = ' ';
            factcheer[i][j].degree = 4;
            factcheer[i][j].edge[0] = '1';
            factcheer[i][j].edge[1] = '1';
            factcheer[i][j].edge[2] = '1';
            factcheer[i][j].edge[3] = '1';
            //测试
        }
    }

    //初始化悔棋数组
    for(int i=0;i<60;i++)
    {
        back_player[i]=0;
        if(back_player[i]==true)
            qDebug()<<i;
        for(int j=0;j<4;j++)
            back_ui[i][j]=-1;
        for(int k=0;k<2;k++)
            back_board[i][k]=-1;
        for(int h=0;h<5;h++)
            back_box[i][h]=-1;
    }

}

Widget::~Widget()
{

    delete ui;
}

//绘图函数
void Widget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawPixmap(0,0,width(),height(),QPixmap(":/new/prefix1/image/background2.jpg"));

    QPen pen=painter.pen();
    pen.setWidth(4);
    painter.setPen(pen);

    for(int i=0;i<36;i++)
    {
        //调用drawpoint函数---画原点。
        drawpoint(painter,i);
    }
    countblack=0;
    countwhite=0;
    for(int i=0;i<5;i++)
    {
        for(int j=0;j<5;j++)
        {
            if(_g[i][j].owner==1)
            {
                countwhite++;
                painter.drawPixmap((_g[i][j].row+1)*dist+5,(_g[i][j].col+1)*dist+5,dist-10,dist-10,QPixmap(":/new/prefix1/image/red.png"));
            }
            else if(_g[i][j].owner==2)
            {
                countblack++;
                painter.drawPixmap((_g[i][j].row+1)*dist+5,(_g[i][j].col+1)*dist+5,dist-10,dist-10,QPixmap(":/new/prefix1/image/black.png"));
            }
        }
    }

    ui->di->setText(QString("敌方占格%1").arg(countblack));
    ui->wo->setText(QString("我方占格%1").arg(countwhite));


}

//画原点函数
void Widget::drawpoint(QPainter& painter, int id)
{

    QPen pen=painter.pen();
    pen.setWidth(4);

        for(int i =0;i<36;i++)
        {
            for(int j=0;j<4;j++)
            {
                for(int k=0;k<4;k++)
                {
                    if(_p[id].line[j] ==_p[i].line[k] && _p[id].line[j]!=-1)
                    {

                        if(_p[id].colour[j]==1)
                        {
                            pen.setColor(Qt::red);
                            painter.setPen(pen);

                        }
                        else
                        {
                            pen.setColor(Qt::black);
                            painter.setPen(pen);
                        }

                        painter.drawLine(center(_p[id].row,_p[id].col),center(_p[i].row,_p[i].col));

                        painter.setPen(Qt::black);
                        if(i==_selected)
                            painter.setBrush(Qt::white);
                        else
                            painter.setBrush(Qt::black);
                        painter.drawEllipse(center(_p[i].row,_p[i].col),_r,_r);


                    }
                }
            }
        }

    painter.setPen(Qt::black);
    if(id==_selected)
        painter.setBrush(Qt::white);
    else
        painter.setBrush(Qt::black);

    painter.drawEllipse(center(_p[id].row,_p[id].col),_r,_r);
}

//将行列坐标转换为窗口像素点位置
QPoint Widget::center(int row, int col)
{
    QPoint ret;
    ret.rx() = (col+1)*dist;
    ret.ry() = (row+1)*dist;
    return ret;
}

//搜索算法，需要优化
bool Widget::getrowcol(QPoint pt, int& row, int& col)
{
    for(row=0;row<6;row++)
    {
        for(col=0;col<6;col++)
        {
            QPoint c= center(row,col);
            int dx = pt.x()-c.x();
            int dy = pt.y()-c.y();
            int dis= dx*dx+dy*dy;
            if(dis<_r*_r)
            {
                return true;
            }
        }
    }
    return false;
}

//点击函数
void Widget::click(QPoint ev)
{
    QPoint pt =ev ;   //获取当前像素点
    // 将PT转化为象棋行列值；
    // 判断在这上面是否有原点；
    int row,col;
    bool Ret =getrowcol(pt,row,col);
    if(Ret== false)    // 点在棋盘外
        return ;

    click(row,col);
}

//连线方法可优化，利用等值法容易出问题
int Widget::click(int row,int col)
{

    //选择点击的原点的 id
    int i,j;
    for(i=0;i<36;i++)
    {
        if(_p[i].row==row  && _p[i].col == col)
        {
            break;
        }
    }
    //传给clickid
    if(i<36)
    {
        _clickid=i;
    }
    //selected为-1说明 点击的为第一个点
    if(_selected==-1)
    {
        if(_clickid !=-1)
        {

            _selected=_clickid;
            _clickid=0;
            for(j=0;j<4;j++)
            {
                if(_p[i].line[j]==-1)
                {
                    bko=_p[i].colour[j];
                    bkt=_p[i].line[j];
                    if(player==true)
                        _p[i].colour[j]=1;
                    else
                        _p[i].colour[j]=2;
                    _p[i].line[j]=temp;
                    tempchoice=j;
                    //悔棋数据,可封装
                    back_ui[backcount][0]=i;
                    back_ui[backcount][1]=j;
                    back_board[backcount][0]=i;
                    break;
                }
            }
        }
    }else
    {
        if(_clickid==_selected)
        {
            _p[_selected].colour[tempchoice]=bko;
            _p[_selected].line[tempchoice]=bkt;
            _selected=-1;
            update();
            return 2;
        }

        if(_clickid==_selected+1 || _clickid==_selected -1 || _clickid==_selected+6 || _clickid==_selected-6 )
        {
            for(j=0;j<4;j++)
            {
                if(_p[i].line[j]==-1)
                {
                    // 1为红线，2为黑线，看下棋方为谁
                    if(player==true)
                        _p[i].colour[j]=1;
                    else
                        _p[i].colour[j]=2;

                    _p[i].line[j]=temp;


//                    if(sender()==ui->whiteok){
                    //悔棋数据
                    back_ui[backcount][2]=i;
                    back_ui[backcount][3]=j;
                    back_board[backcount][1]=i;

                    //增加已下边数目
                    edgeCount++;


                    //！！！！！！！！！！！顺序问题
                    //存储棋盘函数；
                    saveSteps(_selected,_clickid);
                    //判断占格函数;
                    CountEdge(_selected,_clickid,player);
                    //储存temp值
                    temp_backcount=backcount;
                    break;

                    }
//                }

            }
            temp++;          //变量自增

            tempselect=_selected;   //储存上一次的两个点击点
            tempclick=_clickid;

            _selected=-1;    //重置选取点
            _clickid=-1;

            player=!player;  //更换下棋方
        }
        else
        {
            QMessageBox::about(this,"错误","请重新选择");
            return 2;
        }
    }
    update();
    return 1;
}

void Widget::click(int id)
{

    int row,col;
    row=_p[id].row;
    col=_p[id].col;
    qDebug()<<row+1<<col+1;
    Widget::click(row,col);
}

//鼠标点击事件
void Widget::mouseReleaseEvent(QMouseEvent *ev)
{
    //强制选择先后手
    if(choice==0)
    {
        QMessageBox::about(this,"错误","先后手未确定！");
    }
    else
    {

        click(ev->pos());
    }
}


void Widget::CountEdge(int click, int selcet,bool play)
{
    int x1,x2,y1,y2;  //两个点的位置
    int dx,dy;        //两个坐标的差值
    int retx,rety;    //格子的下标   从1开始
  //  int nx1,nx2,ny1,ny2;

    x1=_p[click].row;
    x2=_p[selcet].row;
    y1=_p[click].col;
    y2=_p[selcet].col;
    dx=abs(_p[click].row-_p[selcet].row);
    dy=abs(_p[click].col-_p[selcet].col);

    //当两点同行时
    if(dx==1)
    {
        retx=(x1+x2-1)/2;
        rety=(y1+y2)/2;
        if(y1==5&&y2==5)
        {
            //在第五行，边只影响一个格子
            _g[rety-1][retx].num++;
            //赋值给悔棋变量
            final1_x=rety-1;
            final1_y=retx;
            final_line1=3;   //南边

            if(_g[rety-1][retx].num==4)
            {
                go=true;
                // 1为白色，2为黑色
                if(play==true)
                {
                    _g[rety-1][retx].owner=1;
                    countwhite++;
                }
                else
                {
                    _g[rety-1][retx].owner=2;
                    countblack++;
                }

                player=!player; // 这里进行了一次换手
                 update();
            }
        }else if(y1==0&&y2==0)   //同上
        {
            _g[rety][retx].num++;
            //赋值给悔棋变量
            final1_x=rety;
            final1_y=retx;
            final_line1=1;   //北边

            if(_g[rety][retx].num==4)
            {
                go=true;
                if(play==true)
                {
                    _g[rety][retx].owner=1;
                    countwhite++;
                }
                else
                {
                    _g[rety][retx].owner=2;
                    countblack++;
                }
                player=!player;     // 也是换手
                 update();
            }
        }
        else    //除这两行外，其余边都影响两个格子
        {
            _g[rety][retx].num++;
            _g[rety-1][retx].num++;

            //赋值给两个悔棋变量
            final1_x=rety;
            final1_y=retx;
            final2_x=rety-1;
            final2_y=retx;
            final_line1=1;  //下边的格子
            final_line2=3;

            if(_g[rety][retx].num==4)
            {
                go=true;
                if(play==true)
                {
                    _g[rety][retx].owner=1;
                    countwhite++;
                }
                else
                {
                    _g[rety][retx].owner=2;
                    countblack++;
                }
                player=!player;
                 update();
            }
            if(_g[rety-1][retx].num==4)
            {
                go=true;
                if(play==true)
                {
                    _g[rety-1][retx].owner=1;
                    countwhite++;
                }
                else
                {
                    _g[rety-1][retx].owner=2;
                    countblack++;
                }
                player=!player;
                if(_g[rety][retx].num==4)
                    player=!player;
                 update();
            }
        }
    }

    //当两点同列时 ，列状况与行状况类似   👆
    if(dy==1)
    {
        retx=(x1+x2)/2;
        rety=(y1+y2-1)/2;
        if(x1==5&&x2==5)
        {
            _g[rety][retx-1].num++;
            //赋值给两个悔棋变量
            final1_x=rety;
            final1_y=retx-1;
            final_line1=2;  //最右边的格子


            if(_g[rety][retx-1].num==4)
            {
                go=true;
                if(play==true)
                {
                    _g[rety][retx-1].owner=1;
                    countwhite++;
                }
                else
                {
                    _g[rety][retx-1].owner=2;
                    countblack++;
                }
                player=!player;
                update();
            }
        }else if(x1==0&&x2==0)
        {
            _g[rety][retx].num++;
            //赋值给两个悔棋变量
            final1_x=rety;
            final1_y=retx;
            final_line1=0;  //最左边的格子


            if(_g[rety][retx].num==4)
            {
                go=true;
                if(play==true)
                {
                    _g[rety][retx].owner=1;
                    countwhite++;
                }
                else
                {
                    _g[rety][retx].owner=2;
                    countblack++;
                }
                player=!player;     //占格后不换手
                update();
            }
        }
        else        //其他都影响两个格子
        {
            _g[rety][retx].num++;
            _g[rety][retx-1].num++;
            //赋值给两个悔棋变量
            final1_x=rety;  //右边的格子为主
            final1_y=retx;
            final2_x=rety;
            final2_y=retx-1;
            final_line1=0;
            final_line2=2;

            if(_g[rety][retx].num==4)
            {
                go=true;
                if(play==true)
                {
                    _g[rety][retx].owner=1;
                    countwhite++;
                }
                else
                {
                    _g[rety][retx].owner=2;
                    countblack++;
                }
                player=!player;
                update();
            }
            if(_g[rety][retx-1].num==4)
            {
                go=true;
                if(play==true)
                {
                    _g[rety][retx-1].owner=1;
                    countwhite++;
                }
                else
                {
                    _g[rety][retx-1].owner=2;
                    countblack++;
                }
                player=!player;
                if(_g[rety][retx].num==4)    //同时占两格
                    player=!player;
                update();
            }
        }
    }

    //将所找final值，存入数组
    back_box[backcount][0]=final1_x;
    back_box[backcount][1]=final1_y;
    back_box[backcount][2]=final2_x;
    back_box[backcount][3]=final2_y;
    back_box[backcount][4]=final_line1;
    back_box[backcount][5]=final_line2;
//    nx1=final1_x;
//    ny1=final1_y;
//    nx2=final2_x;
//    ny2=final2_y;
    //存储下棋方
     back_player[backcount] = player;

//    if(go == true)  // 如果占了格，那下次下棋方不变
//        back_player[backcount] = !player;
//    else
//        back_player[backcount] = player;
    //  ui->textBrowser->setText(tr("(%1,%2)连(%3,%4)").arg(nx1).arg(ny1).arg(nx2).arg(ny2));
    //backcount自增
    backcount++;
    //执行完后清除临时变量值
    final1_x=final1_y=final2_x=final2_y=final_line1=final_line2=0;

}


void Widget::on_blackfirst_clicked()
{
    //改变choice的值，确定先后手
    player=false;
    choice=2;
    qipu=2;

    if(retw==0)
    {
        timewhite=this->startTimer(1000);
        retw=1;
    }
    ui->blackfirst->setEnabled(false);
    ui->whitefirst->setEnabled(false);
}


void Widget::on_whitefirst_clicked()
{
    player=true;
    choice=1;
    qipu=1;
    if(retb==0)
    {
        timeblack=this->startTimer(1000);
        retb=1;
    }
    ui->whitefirst->setEnabled(false);
    ui->blackfirst->setEnabled(false);
}

void Widget::on_save_clicked()
{
    QString path=QFileDialog::getSaveFileName(this,"save","../","TXT(*.txt)");
    if(path.isEmpty()==false)
    {
        //判断胜负方
        QString winner_str;
        if(countwhite>countblack)
        {
            winner_str="R";
        }
        else if(countwhite<countblack)
        {
             winner_str="B";
        }
        else{
            winner_str="未知";
        }

        //按棋谱创建键值对
        //1.GAME落子数组
        QJsonArray steps;
        for(int i=0;i<=edgeCount;i++)
        {
            steps.append(QJsonValue(RB_step[i]));
        }
        //获取DATE当天的时间
        QDateTime today=QDateTime::currentDateTime();
        QString today_str = today.toString("yyyy-MM-dd");
        QString Event_str= "China Computer Game Competition";
        //创建数组

        QJsonObject json;
        json.insert("R","RedPlayer");
        json.insert("B","BluePlayer");
        json.insert("winner",winner_str);
        json.insert("RScore",countwhite);
        json.insert("BScore",countblack);
        json.insert("Date",today_str);
        json.insert("Event",Event_str);
        json.insert("game",QJsonValue(steps));

        //转成文本，toJSON
        QJsonDocument docu;
        docu.setObject(json);
        QByteArray byte=docu.toJson(QJsonDocument::Compact);
        QString strJson(byte);      //转换后的最终信息

        //创建文件对象；
        QFile file;
        //关联文件名
        file.setFileName(path);
        bool temp=file.open(QIODevice::WriteOnly | QIODevice::Text);
        //打开文件
        if(temp==true)
        {
            QTextStream stream(&file);
            stream.setCodec("UTF-8");   //  设置输出为UTF-8格式
            stream<<strJson<<endl;
            file.close();
        }
    }
}



void Widget::timerEvent(QTimerEvent *ev)
{
    //敌方时间
    if(ev->timerId()==this->timewhite)
    {
        static int ws=0,wm=0;
        ws++;
        if(ws==60)
        {
            ws=0;
            wm++;
        }
        ui->blacktime->setText(QString("<center><h1>Time: %1:%2</h1></center>").arg(wm).arg(ws));
    }
    else if(ev->timerId()==this->timeblack)
    {
        static int bs=0,bm=0;
        bs++;
        if(bs==60)
        {
            bs=0;
            bm++;
        }
        ui->whitetime->setText(QString("<center><h1>Time: %1:%2</h1></center>").arg(bm).arg(bs));
    }
}

void Widget::on_blackok_clicked()
{
    timeblack=this->startTimer(1000);
    this->killTimer(timewhite);

}

void Widget::on_whiteok_clicked()
{
    timewhite=this->startTimer(1000);
    this->killTimer(timeblack);

}

void Widget::on_whitecancel_clicked()
{
    if(_selected!=-1)
    {
        _p[_selected].line[tempchoice]=-1;
        _p[_selected].colour[tempchoice]=0;
        _selected=-1;
        update();
    }/*else{
        _p[_selected].line[tempchoice]=-1;
        _p[_selected].colour[tempchoice]=0;
        _p[_clickid].line[tempchoice]=-1;
        _p[_clickid].colour[tempchoice]=0;
        _selected=-1;
        _clickid=-1;
        update();
    }*/
}

void Widget::on_blackcancel_clicked()
{
    if(_selected!=-1)
    {
        _p[_selected].line[tempchoice]=-1;
        _p[_selected].colour[tempchoice]=0;
        _selected=-1;
        update();
    }


}

void Widget::on_esc_clicked()
{
    close();
}


//将坐标原点转换成JSON格式的棋谱
void Widget::saveSteps(int point_1,int point_2)
{
    int diffenerce_value=qAbs(point_1-point_2);     //计算差值
    QString cheers_direction="1";                  //最终方向
    int start_point=0;                          //起始坐标

    //两点相邻
    if(diffenerce_value==1)
    {
        if(point_1>point_2) //相邻取左边的点（较小值）
        {
            start_point=point_2;
            cheers_direction="h";
        }else{
            start_point=point_1;
            cheers_direction="h";
        }
    }
    //两点相竖
    else if(diffenerce_value==6)
    {
        if(point_1>point_2) //相竖取下边的点（较大值）
        {
            start_point=point_1;
            cheers_direction="v";
        }else{
            start_point=point_2;
            cheers_direction="v";
        }
    }
    else
        QMessageBox::about(this,"错误","两点距离不正确");

    //存进JSON里
    switch_cheerstep(_p[start_point].row,_p[start_point].col,cheers_direction);

}

//承接上一个函数，继续转换标准棋盘
void Widget::switch_cheerstep(int row,int col,QString direction)
{

    QString newRow;           //储存新值
    QString newCol;           //储存新值
    QString strname;          //下子的信息
    QString strplayer;        //下子方

    //行倒叙
    int daoxu=6-row;
    newRow=QString::number(daoxu);  //转换类型，否则会有字符编码
    //列switch选择
    switch(col+1){
    case 1:newCol="a";  break;
    case 2:newCol="b";  break;
    case 3:newCol="c";  break;
    case 4:newCol="d";  break;
    case 5:newCol="e";  break;
    case 6:newCol="f";  break;
    }

    //棋谱标准     （根据先后手来设定，保证r起始才能通过官方棋谱软件检测）
    if(qipu==1){
        if(player==true){
            strplayer="r";
        }else{
            strplayer="b";
        }
    }else if(qipu==2){
        if(player==true){
            strplayer="b";
        }else{
            strplayer="r";
        }
    }


    //转换成功形如r(e3,v)，加入JSON
    strname=QString("%1(%2%3,%4)").arg(strplayer).arg(newCol).arg(newRow).arg(direction);
    RB_step[edgeCount].insert("piece",strname);

}

//当连续占格时未能悔棋，待优化
void Widget::on_backstep_clicked()
{
    isback=true;    //更改标志
    qDebug()<<"执行悔棋 backcount="<<backcount;
    //执行悔棋,界面跟棋盘一起悔
    if(backcount>0)
    {

            backcount--;
            backstep_ui(backcount);
            backstep_board(backcount);   
            if(back_player[backcount]!=player)
            {
                while(back_player[backcount]!=player)
                {
                    backcount--;
                    backstep_ui(backcount);
                    backstep_board(backcount);
                }

             }




//        while(back_player[backcount]==player)
//            {
//                //处理连续占格的情况
//                 backcount--;
//                 backstep_ui(backcount);
//                 backstep_board(backcount);
//            }
//        backcount--;
//        backstep_ui(backcount);
//        backstep_board(backcount);
//        while(back_player[backcount]==player){
//            backcount--;
//            backstep_ui(backcount);
//            backstep_board(backcount);
//        }
    }else{
        QMessageBox::about(this,"错误","没有可悔棋步骤");
    }
    qDebug()<<"全部执行完毕 backcount="<<backcount;
    qDebug()<<"temp值为"<<temp_backcount;
    qDebug()<<"当前玩家"<<player;
    update();
}

void Widget::backstep_ui(int id)
{
    //界面悔棋，消除格子线关系
    int point1=back_ui[id][0];
    int point2=back_ui[id][2];
    int line1=back_ui[id][1];
    int line2=back_ui[id][3];

    //消除线和颜色
    _p[point1].line[line1]=--bignum;
    _p[point2].line[line2]=--bignum;
    _p[point1].colour[line1]=0;
    _p[point2].colour[line2]=0;

    //消除格子占有
    int check1_y=back_box[id][0];
    int check1_x=back_box[id][1];
    int check2_y=back_box[id][2];
    int check2_x=back_box[id][3];

    //格子自由度减去，占有度清除
    _g[check1_x][check1_y].num--;
    _g[check1_x][check1_y].owner=-1;

    qDebug()<<"消除的格子是"<<check1_x+1<<check1_y+1;
    if(check2_x>0&&check2_y>0)  //存在第二个格子
    {
        qDebug()<<"消除的格子是"<<check2_x+1<<check2_y+1;
        _g[check2_x][check2_y].num--;
        _g[check2_x][check2_y].owner=-1;
    }
}

void Widget::backstep_board(int id)
{
    //棋盘悔棋，直接利用BOX数组

    int check1_y=back_box[id][0]+1;
    int check1_x=back_box[id][1]+1;
    int check2_y=back_box[id][2]+1;
    int check2_x=back_box[id][3]+1;
    int check1_line=back_box[id][4];
    int check2_line=back_box[id][5];

    //消除格子边和占有度
    factcheer[check1_x][check1_y].edge[check1_line]='1';
    factcheer[check1_x][check1_y].degree++;
    factcheer[check1_x][check1_y].ower=' ';
    if(check2_x>0&&check2_y>1)  //第二个格子存在
    {
        factcheer[check2_x][check2_y].edge[check2_line]='1';
        factcheer[check2_x][check2_y].degree++;
        factcheer[check2_x][check2_y].ower=' ';

    }
}
