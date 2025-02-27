#pragma once
#include <string>
#include <vector>
#include <fstream>
class NewFileSave
{
public:
	NewFileSave(bool isSeve = false);
	~NewFileSave();
	void NewFile(std::string FileName);
	void WriteFile(std::string);
protected:
	void NewFile(std::string FileName, std::vector<std::string>Hand);
	void WriteFile(std::vector<std::string>string);
private:
	bool m_IsSave;
	std::fstream* m_Outfile;
};