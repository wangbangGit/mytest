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

bool mapinfo::init(std::string bar_filename)
{
	// todo 
	// 设置读取的路径

	m_bar_filename = bar_filename;
	return true;
}

bool mapinfo::load()
{
	const char *filename = m_bar_filename.c_str();
	XMLDocument doc;
	if (doc.LoadFile(filename) != XML_SUCCESS)
	{
		log_error("load %s failed!", filename);
		return false;
	}

	// todo 
	// 添加地图信息

	m_barinfo = new bool[m_width * m_height];
	memset(m_barinfo, 0, sizeof(m_barinfo));
	return true;
}

void mapinfo::addbar(int row, int col)
{
	if (m_barinfo)
	{
		if (row >= 0 && row < m_width)
		{
			if (col >= 0 && col < m_height)
			{
				m_barinfo[row * col] = true;
			}
		}
	}
}