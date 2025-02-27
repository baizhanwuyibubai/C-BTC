#include "Json.h"
#include <fstream>
#include <sstream>
#include <json/json.h>
#include <iostream>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

std::string Jump::JsonRead(std::string FileName, std::string Key)
{
	//std::string jsonFilePath("Ini/数据相关配置.json");
	std::string jsonFilePath = FileName;
	// 创建一个ifstream对象来读取文件
	std::ifstream inputStream(jsonFilePath);
	// 检查文件是否成功打开
	if (!inputStream.is_open())
	{
		return "";
	}
	// 读取文件内容到字符串中
	std::ostringstream ss;
	ss << inputStream.rdbuf();
	std::string jsonString = ss.str();
	// 关闭文件流
	inputStream.close();
	// 使用Json::Reader解析JSON字符串
	Json::Value root;
	Json::Reader reader;
	bool parsingSuccessful = reader.parse(jsonString, root);
	if (parsingSuccessful)
	{
		// 解析成功，处理JSON数据
		std::string string = root[Key].asString();
		return string;
		// ... 其他字段的处理 ...
	}
	else
	{
		// 解析失败，输出错误信息
		std::cout << u8"Failed to parse JSON: " << reader.getFormattedErrorMessages() << std::endl;
		return "";
	}
}

void Debug()
{
	boost::property_tree::ptree root;
	try
	{
		boost::property_tree::read_json(u8"E:/Project/VirtualCurrency/Simulation/Middle/Ini/Socket2.json", root);
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl;
		return;
	}
	std::cout << root.get<std::string>("1735473420000") << std::endl;
}