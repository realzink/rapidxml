// testMj.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>
#include <sstream>
#include <iomanip>


#include <rapidxml.hpp>
#include <rapidxml_print.hpp>
#include <rapidxml_utils.hpp>
using namespace rapidxml;


std::string makeMJXML(std::string strXML)
{
	xml_document<> doc;
	xml_node<>* rot = doc.allocate_node(rapidxml::node_pi, doc.allocate_string("xml version='1.0' encoding='utf-8'"));
	doc.append_node(rot);
	xml_node<>* node = doc.allocate_node(node_element, "root", NULL);
	doc.append_node(node);

	xml_node<>* fix = doc.allocate_node(node_element, "fix", "infinova");
	node->append_node(fix);

	xml_node<>* cmd = doc.allocate_node(node_element, "cmd", NULL);
	cmd->append_attribute(doc.allocate_attribute("Id", "1"));
	cmd->append_attribute(doc.allocate_attribute("uid", "0"));
	cmd->append_attribute(doc.allocate_attribute("pwd", ""));
	node->append_node(cmd);

	xml_node<>* TreeRoot = doc.allocate_node(node_element, "TreeRoot", NULL);
	cmd->append_node(TreeRoot);
	TreeRoot->append_attribute(doc.allocate_attribute("Classid", "0"));
	TreeRoot->append_attribute(doc.allocate_attribute("Id", "0"));
	TreeRoot->append_node(doc.allocate_node(node_element, "ClassId", "3/63/59/58/62/79"));

	std::string text;
	rapidxml::print(std::back_inserter(text), doc, 0);

	//std::ofstream out("config.xml");
	//out << text.c_str();

	return text.c_str();
}

std::string makeMJPacket(std::string strXML)
{
	string strdata;
	std::string strHeader = "J[l}0001";
	std::ostringstream os;
	os << std::setw(8) << std::setfill('0') << strXML.length();
	strdata = strHeader + os.str() + strXML;

	std::cout << strdata << std::endl;
	std::ofstream out("config.xml");

	return strdata.c_str();
}



int _tmain(int argc, _TCHAR* argv[])
{
	std::string strXML = makeMJXML("");

	std::string strRequestXML = makeMJPacket(strXML);

	std::ofstream out("config.xml");
	out << strRequestXML.c_str();

	system("PAUSE");

	return 0;
}

