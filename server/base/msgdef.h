#pragma once
#include"cmd.h"
#include"msgbase.h"

struct MsgPing :public Msg
{
	MsgPing()
	{
		SetLength(sizeof(*this));
		SetType(MSG_PING);
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