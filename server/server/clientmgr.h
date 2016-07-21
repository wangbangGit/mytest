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

	void init(int port);
	void release();
	void testandlisten();
	void acceptnewclient();
	void processallclient();
	void processallclientmsg(client *cl);
	void run();
	void endrun();

public:
	void SendMsgToAll(Msg *pMsg,client *cl = NULL);

private:
	void OnClientDisconnect(client *cl);

private:
	int m_listen_port;
	bool m_needlisten;

	lxnet::Listener *m_listen;

	std::set<client *> m_client_list;
};