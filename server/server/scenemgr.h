#pragma once
#include"scene.h"
#include<vector>


class scenemgr
{
public:
	scenemgr();
	~scenemgr();

	static scenemgr &Instance()
	{
		static scenemgr m;
		return m;
	}

	bool init();
	bool loadscene(int mapid);
	scene *createscene(int mapid);

private:

	std::vector<scene *> m_scenelist;
};