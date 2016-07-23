/*
*
*	server≈‰÷√
*
*/

#pragma once

class config
{
public:
	config();
	~config();

	static config &Instance()
	{
		static config m;
		return m;
	}

	bool init();
	int GetListenPort() { return m_listen_port; }
	int GetClientOverTime() { return m_clientovertime; }
private:
	int m_listen_port;
	int m_clientovertime;
};