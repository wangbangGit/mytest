#include "playerobj.h"

playerobj::playerobj()
{
	m_now_mapid = 0;
	m_now_pos_x = 0;
	m_now_pos_y = 0;
	m_name.clear();
	m_scene = nullptr;
}

playerobj::~playerobj()
{
	m_now_mapid = 0;
	m_now_pos_x = 0;
	m_now_pos_y = 0;
	m_name.clear();
	m_scene = nullptr;
}

bool playerobj::load(int mapid, int x, int y, std::string name, scene* _scene)
{
	m_now_mapid = mapid;
	m_now_pos_x = x;
	m_now_pos_y = y;
	m_name = name;

	if(_scene)
		m_scene = _scene;

	return true;
}

bool playerobj::moveto(int x, int y)
{
	if (!m_scene->moveto(this, x, y))
	{
		return false;
	}

	return true;
}

void playerobj::getnowpos(int &x, int &y)
{
	x = m_now_pos_x;
	y = m_now_pos_y;
}

void playerobj::setnowpos(const int &x, int const &y)
{
	m_now_pos_x = x;
	m_now_pos_y = y;
}