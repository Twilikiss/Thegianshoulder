#ifndef THREADFORAI_H
#define THREADFORAI_H
#include<QThread>
#include <functional>


class ThreadForAI: public QThread
{
    Q_OBJECT

public:
    ThreadForAI(QObject *parent=0);
    ~ThreadForAI(){}

public:
    //回调函数
    void setCallback(std::function<void(void)> func);
    int count;

signals:
    //信号
    void reBcak();


protected:
    //虚函数
    virtual void run();

private:
    //函数
    std::function<void(void)> m_func;


};

#endif // THREADFORAI_H
