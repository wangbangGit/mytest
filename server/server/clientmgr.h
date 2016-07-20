#pragma once
#include<set>

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
	void run();
	void endrun();

private:
	int m_listen_port;
	bool m_needlisten;

	lxnet::Listener *m_listen;

	std::set<lxnet::Socketer *> m_client_list;
};