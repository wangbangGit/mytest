#include"mapinfo.h"
#include"tinyxml2.h"
#include"log.h"

using namespace tinyxml2;

mapinfo::mapinfo()
{
	m_mapid = 0;
	m_width = 0;
	m_height = 0;
	m_barinfo = nullptr;
	m_bar_filename.clear();
}

mapinfo::~mapinfo()
{
	if (m_barinfo)
	{
		delete m_barinfo;
		m_barinfo = nullptr;
	}
	m_barinfo = nullptr;
	m_bar_filename.clear();
	m_mapid = 0;
	m_width = 0;
	m_height = 0;
}

bool mapinfo::init(int mapid, std::string bar_filename)
{
	// 设置读取的路径
	m_mapid = mapid;
	m_bar_filename = bar_filename;
	return true;
}

bool mapinfo::loadbar()
{
	const char *filename = m_bar_filename.c_str();
	XMLDocument doc;
	if (doc.LoadFile(filename) != XML_SUCCESS)
	{
		log_error("load %s failed!", filename);
		return false;
	}

	// 添加地图阻挡点信息

	XMLElement *pinfo = doc.FirstChildElement("bar_map");
	if (!pinfo)
	{
		log_error("not find first child element, element name: 'bar_map'");
		return false;
	}

	int width = 0;
	int height = 0;
	if (pinfo->QueryIntAttribute("width", &width) != XML_SUCCESS)
	{
		log_error("query int attribute failed, attribute name: 'width'");
		return false;
	}

	if (width <= 0)
	{
		log_error("map width <= 0 ,mapid:%d ",m_mapid);
		return false;
	}
	
	m_width = width;

	if (pinfo->QueryIntAttribute("height", &height) != XML_SUCCESS)
	{
		log_error("query int attribute failed, attribute name: 'height'");
		return false;
	}

	if (height <= 0)
	{
		log_error("map height <= 0 ,mapid:%d ", m_mapid);
		return false;
	}

	m_height = height;

	m_barinfo = new bool[m_width * m_height];
	
	if (!m_barinfo)
	{
		log_error("application memory failed! new m_barinfo ");
		return false;
	}
	memset(m_barinfo, 0, sizeof(m_barinfo));

	pinfo = pinfo->FirstChildElement("bar");
	if (!pinfo)
	{
		log_error("not find first child element, element name: 'bar'");
		return false;
	}

	while (pinfo)
	{
		int row = 0;
		int col = 0;

		if (pinfo->QueryIntAttribute("row", &row) != XML_SUCCESS)
		{
			log_error("query int attribute failed, attribute name: 'row'");
			return false;
		}

		if (row < 0 || row >= m_width)
		{
			log_error("map bar row < 0 or row >= m_width ,mapid:%d ", m_mapid);
			return false;
		}

		if (pinfo->QueryIntAttribute("col", &col) != XML_SUCCESS)
		{
			log_error("query int attribute failed, attribute name: 'col'");
			return false;
		}

		if (col < 0 || col >= m_height)
		{
			log_error("map bar col < 0 or col >= m_height ,mapid:%d ", m_mapid);
			return false;
		}

		m_barinfo[row * col] = true;

		pinfo = pinfo->NextSiblingElement("bar");
	}

	return true;
}

void mapinfo::getmapbirthpoint(int &x, int &y)
{
	x = m_birth_point_x;
	y = m_birth_point_y;
}
int mapinfo::getmapid()
{
	return m_mapid;
}
void mapinfo::getmapwidthandheight(int &x, int &y)
{
	x = m_width;
	y = m_height;
}