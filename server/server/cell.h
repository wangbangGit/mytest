#pragma once
#include "playerobj.h"
#include <set>

class playerobj;

class cell
{
public:
	cell();
	~cell();

	bool addobj(playerobj *obj);
	bool delobj(playerobj *obj);
	bool findobj(playerobj *obj);

private:

	std::set<playerobj *> m_playerset;
};