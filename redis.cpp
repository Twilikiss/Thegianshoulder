#include "redis.h"
#include <QDebug>
#include<QString>
QString Redis::hMget(QString str)
{
    m_ip = "127.0.0.1";
    m_port = 6379;

    /*
        连接测试
    */

    ConnectRedis();
    QString u="get ";
    u.append(str);
    m_cmd =u.toLatin1().data();
    ExecRedis();
    u="";
    u.append(m_reply->str);
    FreeReply();
    FreeRedis();
    return u;
}
Redis::Redis()
{
    // 初始化 ip, 端口
    m_ip = "127.0.0.1";
    m_port = 6379;

    /*
        连接测试
    */

    ConnectRedis();
    // 设置一个整数
    m_cmd = "set m_int 110";
    ExecRedis();
    FreeReply();

    // 获取设置到的整数
    m_cmd = "get m_int";
    ExecRedis();
    if(m_reply != NULL)
    {
        qDebug() << m_reply->str;
    }
    else
    {
        qDebug() << "no reply";
    }

    FreeRedis();
}

// 连接 redis
void Redis::ConnectRedis()
{
    m_context = redisConnect(m_ip, m_port);
    if(m_context == NULL)
    {
        qDebug() << "connect error";
    }
}

// 执行 redis 命令
void Redis::ExecRedis()
{
    m_reply = (redisReply*)redisCommand(m_context, m_cmd);
}

// 释放 redis 资源
void Redis::FreeRedis()
{
    // 释放数据库连接
    if(m_context)
    {
       redisFree(m_context);
    }

    // 释放可能没有释放掉的 redisReply
    FreeReply();
}

// 释放 reply 指针
void Redis::FreeReply()
{
    if(m_reply != NULL)
    {
        freeReplyObject(m_reply);
    }
}
