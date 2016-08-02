#include "scenemgr.h"
#include "mapconfig.h"

scenemgr::scenemgr()
{
	m_scenelist.clear();
}

scenemgr::~scenemgr()
{
	m_scenelist.clear();
}

bool scenemgr::init()
{
	return true;
}

bool scenemgr::loadscene(int mapid)
{
	scene * m_scene = createscene(mapid);
	if (!m_scene)
		return false;

	m_scenelist.push_back(m_scene);

	return true;
}

scene *scenemgr::createscene(int mapid)
{
	mapinfo * m_mapinfo = mapconfig::Instance().getmapinfo(mapid);
	if (!m_mapinfo)
	{
		return nullptr;
	}
	scene * m_scene = new scene;
	if (m_scene)
	{
		m_scene->init(m_mapinfo);
		return m_scene;
	}

	return nullptr;
}