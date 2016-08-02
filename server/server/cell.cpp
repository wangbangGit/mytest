#include "cell.h"

cell::cell()
{
	m_playerset.clear();
}

cell::~cell()
{
	m_playerset.clear();
}

bool cell::addobj(playerobj *obj)
{
	if (obj)
	{
		m_playerset.insert(obj);
		return true;
	}
	return false;
}

bool cell::delobj(playerobj *obj)
{
	if (obj)
	{
		if (findobj(obj))
		{
			m_playerset.erase(obj);
			return true;
		}
	}
	return false;
}

bool cell::findobj(playerobj *obj)
{
	auto iter = m_playerset.find(obj);
	if (iter != m_playerset.end())
	{
		return true;
	}
	return false;
}