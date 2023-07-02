#include "ThreadForAI.h"
#include"AI.h"
#include"widget.h"
#include<QDebug>

//Qt开启多线程,第一种方法用一个类继承QThread,然后重新改写虚函数run();
//当要开启新线程时,只需要实例化该类,然后调用函数start,就可以开启一个多线程

ThreadForAI::ThreadForAI(QObject *parent): QThread(parent)
{
    //nullptr表示任何类型的空指针
    m_func = nullptr;
    count=0;
}

//虚函数实例化
void ThreadForAI::run()
{
    qDebug()<<"进入RUN";
    //只要函数不为空
    if (m_func != nullptr)
    {
        //执行函数
        m_func();
        //执行完后变为空函数
        m_func=nullptr;

    }
}
//回调函数
void ThreadForAI::setCallback(std::function<void(void)> func)
{
    m_func = func;
}
