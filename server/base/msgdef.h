/*
*
*	消息体定义
*
*/

#pragma once
#include"cmd.h"
#include"msgbase.h"

struct MsgPing :public Msg
{
	int64 m_servertime;
	MsgPing()
	{
		SetLength(sizeof(*this));
		SetType(MSG_PING);
		m_servertime = 0;
	}
};

struct MsgEnd :public Msg
{
	MsgEnd()
	{
		SetLength(sizeof(*this));
		SetType(MSG_END);
	}
};