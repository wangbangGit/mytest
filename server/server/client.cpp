#include"stdfx.h"

client::client()
{
	m_connecttime = 0;
	m_pingtime = 0;
	m_removetime = 0;
	m_socket = NULL;
	memset(m_ip, 0, sizeof(m_ip));
}

client::~client()
{
	m_connecttime = 0;
	m_pingtime = 0;
	m_removetime = 0;
	if (m_socket)
	{
		lxnet::Socketer::Release(m_socket);
		m_socket = NULL;
	}
	memset(m_ip, 0, sizeof(m_ip));
}

bool client::bCanRemove(int64 currenttime)
{
	if (!bNeedRemove())
		return false;

	return currenttime >= m_removetime;
}

void client::SetSocket(lxnet::Socketer *socket)
{
	m_socket = socket;
}

void client::SendMsg(Msg *pMsg)
{
	assert(pMsg != NULL);
	if (!pMsg)
		return;
	assert(m_socket != NULL);
	m_socket->SendMsg(pMsg);
}

Msg *client::GetMsg()
{
	assert(m_socket != NULL);
	Msg *msg = m_socket->GetMsg();
	if (!msg)
		return NULL;

	return msg;
}