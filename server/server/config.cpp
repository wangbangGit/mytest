#include"config.h"
#include"tinyxml2.h"
#include"log.h"

using namespace tinyxml2;

config::config()
{
	m_listen_port = 0;
	m_clientovertime = 0;
}
config::~config()
{

}

bool config::init()
{
	const char *filename = "./config/config.xml";
	XMLDocument doc;
	if (doc.LoadFile(filename) != XML_SUCCESS)
	{
		log_error("load %s failed!", filename);
		return false;
	}

	XMLElement *pinfo = doc.FirstChildElement("config");
	if (!pinfo)
	{
		log_error("not find first child element, element name: 'config'");
		return false;
	}

	if (pinfo->QueryIntAttribute("listen_port", &m_listen_port)!=XML_SUCCESS)
	{
		log_error("query int attribute failed!, attribute name: 'listen_port'");
		return false;
	}

	if (pinfo->QueryIntAttribute("client_over_time", &m_clientovertime) != XML_SUCCESS)
	{
		log_error("query int attribute failed!, attribute name: 'listen_port'");
		return false;
	}
	return true;
}