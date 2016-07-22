#include"stdfx.h"
#include"msgbase.h"

extern int64 g_currenttime;
extern bool g_run;

clientmgr::clientmgr()
{
	m_listen_port = 0;
	m_needlisten = false;
	m_listen = NULL;
	m_client_list.clear();
}

clientmgr::~clientmgr()
{
	m_listen_port = 0;
	m_needlisten = false;
	m_listen = NULL;
	m_client_list.clear();
}

void clientmgr::init(int port)
{
	m_listen_port = port;

	m_listen = lxnet::Listener::Create();
	if (!m_listen)
	{
		std::cout << "create Listener failed!" << std::endl;
	}
	else
	{
		m_needlisten = true;
	}
}

void clientmgr::release()
{
	for (auto &i : m_client_list)
	{
		OnClientDisconnect(i);
	}

	lxnet::Listener::Release(m_listen);
}

void clientmgr::testandlisten()
{
	if (!m_needlisten)
		return ;

	if (!m_listen->IsClose())
	{
		m_needlisten = false;
		return;
	}

	if (m_listen->Listen(m_listen_port, s_backlog))
	{
		m_needlisten = false;
		std::cout << "listen "<< m_listen_port <<" succeed!" << std::endl;
	}
	else
	{
		std::cout << "listen " << m_listen_port << " error!" << std::endl;
	}
}

void clientmgr::acceptnewclient()
{
	lxnet::Socketer *socket = NULL;

	for (int i = 0; i < s_backlog; ++i)
	{
		if (!m_listen->CanAccept())
			return;

		if (!(socket = m_listen->Accept()))
			return;

		//这边可以做一个client pool
		client *newclient = new client;
		assert(newclient != NULL);

		socket->SetSendLimit(-1);
		char ip[128];
		socket->GetIP(ip, sizeof(ip) - 1);

		newclient->SetSocket(socket);
		newclient->SetConnectTime(g_currenttime);
		newclient->SetPingTime(g_currenttime);
		newclient->SetIP(ip);
		m_client_list.insert(newclient);

		printf("accept new client, ip:%s\n", ip);
	}
}

void clientmgr::processallclient()
{
	MessagePack *recvpack = NULL;
	std::set<client *>::iterator iter, tempiter;
	for (iter = m_client_list.begin(); iter != m_client_list.end();)
	{
		tempiter = iter;
		iter ++;

		if ((*tempiter)->GetSocket()->IsClose())
		{
			OnClientDisconnect(*tempiter);
			m_client_list.erase((*tempiter));
			continue;
		}

		processclientmsg(*tempiter);
	}
}

void clientmgr::processclientmsg(client *cl)
{
	assert(cl != NULL);
	Msg *pMsg = NULL;
	while (1)
	{
		pMsg = cl->GetMsg();
		if (!pMsg)
			break;
		switch (pMsg->GetType())
		{
		case MSG_PING:
		{
			//收到ping消息的时候，也发送ping消息给前端，然后设置ping消息的接受时间
			cl->SendMsg(pMsg);
			cl->SetPingTime(g_currenttime);
			break;
		}
		case MSG_END:
		{
			std::cout << cl->GetIP() << ":get end msg" << std::endl;
			break;
		}
		case MSG_CHAT:
		{
			//把收到的chat消息发给所有在线的client
			MessagePack * msg = (MessagePack *)pMsg;
			char stBuff[521] = { 0 };
			msg->Begin();
			msg->GetString(stBuff, 512);
			std::cout << cl->GetIP() << ":" << stBuff << std::endl;
			SendMsgToAll(msg);
			break;
		}
		default:
		{
			std::cout << "msg type error!" << std::endl;
		}
		}
	}
}

void clientmgr::SendMsgToAll(Msg *pMsg,client *cl)
{
	for (auto &i : m_client_list)
	{
		if (cl != NULL)
		{
			if(i == cl)
				continue;
		}
		i->SendMsg(pMsg);
	}
}

void clientmgr::OnClientDisconnect(client *cl)
{
	assert(cl != NULL);
	std::cout << "client disconnect! ip:" << cl->GetIP() << std::endl;
	cl->~client();
	delete cl;
	cl = NULL;
}

void clientmgr::run()
{
	testandlisten();
	acceptnewclient();

	processallclient();
}

void clientmgr::endrun()
{
	for (auto &i : m_client_list)
	{
		i->GetSocket()->CheckRecv();
		i->GetSocket()->CheckSend();
	}
}