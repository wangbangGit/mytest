#include"mapconfig.h"
#include"scenemgr.h"
#include"tinyxml2.h"
#include"log.h"

using namespace tinyxml2;

mapconfig::mapconfig()
{
	m_maplist.clear();
}

mapconfig::~mapconfig()
{
	auto iterB = m_maplist.begin();
	auto iterE = m_maplist.end();
	for (; iterB != iterE; iterB++)
	{
		delete iterB->second;
	}

	m_maplist.clear();
}

bool mapconfig::init()
{
	const char *filename = "./data/maplist.xml";
	XMLDocument doc;
	if (doc.LoadFile(filename) != XML_SUCCESS)
	{
		log_error("load %s failed!", filename);
		return false;
	}

	// 将maplist.xml中的信息添加到m_maplist

	XMLElement *pinfo = doc.FirstChildElement("maplist");
	if (!pinfo)
	{
		log_error("not find first child element, element name: 'maplist'");
		return false;
	}

	pinfo = pinfo->FirstChildElement("maps");
	if (!pinfo)
	{
		log_error("not find first child element, element name: 'maps'");
		return false;
	}

	while (pinfo)
	{
		mapinfo* m_mapinfo = new mapinfo;
		if (!m_mapinfo)
		{
			log_error("application memory failed! new m_mapinfo ");
			return false;
		}

		int mapid = 0;

		if (pinfo->QueryIntAttribute("mapid", &mapid) != XML_SUCCESS)
		{
			log_error("query int attribute failed, attribute name: 'mapid'");
			return false;
		}

		if (mapid <= 0)
		{
			log_error("error: mapid <= 0 !");
			return false;
		}

		std::string filename = pinfo->Attribute("bar_filename");
		if (filename.empty())
		{
			log_error("attribute failed, attribute name: 'bar_filename'");
			return false;
		}
		m_mapinfo->init(mapid, filename);

		auto iter = m_maplist.find(mapid);
		if (iter != m_maplist.end())
		{
			log_error("add map list error ,mapid: %d already exist!", mapid);
			return false;
		}

		m_maplist.insert(std::make_pair(mapid, m_mapinfo));

		pinfo = pinfo->NextSiblingElement("maps");
	}

	loadbar();

	return true;
}

bool mapconfig::loadbar()
{
	auto iterB = m_maplist.begin();
	auto iterE = m_maplist.end();

	for (; iterB != iterE; iterB++)
	{
		mapinfo* _mapinfo = iterB->second;
		if (_mapinfo)
		{
			if (!_mapinfo->loadbar())
			{
				log_error("load map bar error ,mapid: %d", iterB->first);
				return false;
			}
		}
	}

	return true;
}

mapinfo *mapconfig::getmapinfo(int mapid)
{
	auto iter = m_maplist.find(mapid);
	if (iter != m_maplist.end())
	{
		return iter->second;
	}

	return nullptr;
}

bool mapconfig::loadallscene()
{
	auto iterB = m_maplist.begin();
	auto iterE = m_maplist.end();

	for (; iterB != iterE; iterB++)
	{
		mapinfo* _mapinfo = iterB->second;
		if (_mapinfo)
		{
			if (!scenemgr::Instance().loadscene(iterB->first))
			{
				return false;
			}
		}
	}
	return true;
}