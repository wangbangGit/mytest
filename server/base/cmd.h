/*
*
*	消息号定义
*	对应Msg里面的Type（SetType、GetType）
*
*/

#pragma once

enum
{
	MSG_BEGIN	= 0,
	MSG_PING	= 1,
	MSG_END		= 2,
	MSG_CHAT	= 3,
	MSG_MAX
};