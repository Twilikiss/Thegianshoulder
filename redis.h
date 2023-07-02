#ifndef REDIS_H
#define REDIS_H
#include <hiredis.h>
#include<QString>
class Redis
{

public:
    Redis();

    // 连接 redis
    void ConnectRedis();
    QString hMget(QString str);
    // 执行 redis命令
    void ExecRedis();

    // 释放资源
    void FreeRedis();

    // 释放 reply 指针
    void FreeReply();

    // redis 句柄
    redisContext *m_context;

    // redis 执行返回数据
    redisReply *m_reply;

    // 执行命令的 cmd 字符串
    char * m_cmd;

    // 连接 ip，端口
    char * m_ip;
    int m_port;
};
#endif // REDIS_H
