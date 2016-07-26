/*
*
*	Client链接管理类
*
*/

#pragma once

static const int s_backlog = 128;

class clientmgr
{
public:
	clientmgr();
	~clientmgr();

	static clientmgr &Instance()
	{
		static clientmgr m;
		return m;
	}

	//初始化--指定监听端口和创建listener
	bool init(int port,int clientovertime);
	//释放资源
	void release();
	//尝试启动监听
	void testandlisten();
	//检测和接受新的连接
	void acceptnewclient();
	//处理所有的client连接
	void processallclient();
	//client的msg处理
	void processclientmsg(client *cl);
	//每帧调用
	void run();
	void endrun();

public:
	//将消息发送给所有client连接
	void SendMsgToAll(Msg *pMsg,client *cl = NULL);

private:
	//client连接断开的处理
	void OnClientDisconnect(client *cl);

private:
	//监听端口
	int m_listen_port;
	//是否需要Listen()
	bool m_needlisten;
	//超时时间
	int m_clientovertime;

	//listener
	lxnet::Listener *m_listen;

	//所有的client连接
	std::set<client *> m_client_list;
};