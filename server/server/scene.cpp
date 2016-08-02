#include "scene.h"
#include "log.h"

scene::scene()
{
	m_mapinfo = nullptr;
}

scene::~scene()
{
	if (m_mapinfo)
	{
		delete m_mapinfo;
		m_mapinfo = nullptr;
	}
	m_mapinfo = nullptr;
}

bool scene::init(mapinfo * _mapinfo)
{
	if (!_mapinfo)
	{
		return false;
	}

	m_mapinfo = _mapinfo;

	m_mapid = _mapinfo->getmapid();
	_mapinfo->getmapbirthpoint(m_birth_point_x, m_birth_point_y);
	_mapinfo->getmapwidthandheight(m_width, m_height);

	if (m_width <= 0 && m_height <= 0)
	{
		log_error("scene get map width and height failed!");
		return false;
	}
	m_cell = new cell[m_width*m_height];
	return true;
}

bool scene::obj_enter(playerobj * obj)
{
	m_playerset.insert(obj);

	return true;
}

bool scene::canmove(int x, int y)
{
	if (x >= 0 && x < m_width)
	{
		if (y >= 0 && y < m_height)
		{
			if (m_barinfo)
			{
				return !m_barinfo[x * y];
			}
		}
	}
	return false;
}

bool scene::moveto(playerobj * obj, int x, int y)
{
	if (obj)
	{
		if (canmove(x, y))
		{
			int _oldx = 0;
			int _oldy = 0;
			obj->getnowpos(_oldx, _oldy);
			if (m_cell[_oldx * _oldy].delobj(obj))
			{
				m_cell[x * y].addobj(obj);
				obj->setnowpos(x, y);
				return true;
			}
		}
	}

	return false;
}