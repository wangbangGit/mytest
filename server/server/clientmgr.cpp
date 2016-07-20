#include"stdfx.h"

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
		lxnet::Socketer::Release(i);
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
	lxnet::Socketer *newclient = NULL;

	for (int i = 0; i < s_backlog; ++i)
	{
		if (!m_listen->CanAccept())
			return;

		if (!(newclient = m_listen->Accept()))
			return;

		newclient->SetSendLimit(-1);

		m_client_list.insert(newclient);

		char ip[128];
		newclient->GetIP(ip, sizeof(ip) - 1);
		printf("accept new client, ip:%s\n", ip);
	}
}

void clientmgr::processallclient()
{
	MessagePack *recvpack = NULL;
	std::set<lxnet::Socketer *>::iterator iter, tempiter;
	for (iter = m_client_list.begin(); iter != m_client_list.end();)
	{
		tempiter = iter;
		iter ++;

		if ((*tempiter)->IsClose())
		{
			lxnet::Socketer::Release((*tempiter));
			m_client_list.erase((*tempiter));
			continue;
		}

		recvpack = (MessagePack *)(*tempiter)->GetMsg();
		if (recvpack)
		{
			std::cout << "get msg!" << std::endl;
		}
	}
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
		i->CheckRecv();
		i->CheckSend();
	}
}