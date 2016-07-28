#pragma once
#include"mapinfo.h"
#include"playerobj.h"
#include"cell.h"
#include<set>

class playerobj;
class cell;

class scene
{
public:
	scene();
	~scene();

	bool init(mapinfo * _mapinfo);

	bool obj_enter(playerobj * obj);

	bool canmove(int x, int y);
	bool moveto(playerobj * obj, int x, int y);
private:
	int m_mapid;
	int m_width;
	int m_height;

	int m_birth_point_x;
	int m_birth_point_y;

	bool *m_barinfo; //×èµ²ÐÅÏ¢
	cell *m_cell;
	std::set<playerobj *> m_playerset;
	mapinfo *m_mapinfo;
};