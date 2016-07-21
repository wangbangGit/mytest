#pragma once
#include"lxnet.h"
#include"crosslib.h"

class client
{
public:
	client();
	~client();

	enum
	{
		enum_remove_delay_time = 5000,		//延时移除 ms
	};

	void SetConnectTime(int64 currenttime) { m_connecttime = currenttime; }
	void SetPingTime(int64 currenttime) { m_pingtime = currenttime; }
	void SetRemoveTime(int64 currenttime) { m_removetime = currenttime + enum_remove_delay_time; }
	bool bNeedRemove() { return m_removetime != 0; }
	bool bCanRemove(int64 currenttime);

public:
	
	void SetSocket(lxnet::Socketer *socket);
	lxnet::Socketer *GetSocket() { return m_socket; }
	void SendMsg(Msg *pMsg);
	Msg *GetMsg();
	void SetIP(const char *ip) { memcpy(m_ip, ip, strlen(ip)); }
	char *GetIP() { return m_ip; }
private:

	int64 m_connecttime;	//连接时间
	int64 m_pingtime;		//ping的时间
	int64 m_removetime;		//需要被移除的时间

	char m_Buff[1024 * 1024];
	char m_ip[128];
	lxnet::Socketer *m_socket;
};