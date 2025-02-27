#include "NewFileSave.h"
NewFileSave::NewFileSave(bool isSeve) : m_IsSave(isSeve), m_Outfile(nullptr)
{
	this->m_Outfile = nullptr;
}

NewFileSave::~NewFileSave()
{
	if (m_IsSave == true)
		this->m_Outfile->close();
}

void NewFileSave::NewFile(std::string string)
{
	m_IsSave = true;
	std::string Path = string;
	this->m_Outfile = new std::fstream(Path, std::ios::in | std::ios::out | std::ios::trunc | std::ios::binary);
}

void NewFileSave::NewFile(std::string string, std::vector<std::string>Hand)
{
	m_IsSave = true;
	std::string Path = string;
	this->m_Outfile = new std::fstream(Path, std::ios::in | std::ios::out | std::ios::trunc | std::ios::binary);
	for (int i = 0; i < Hand.size(); i++)
	{
		if (i == Hand.size() - 1)
			this->WriteFile(Hand[i] + "\n");
		else
			this->WriteFile(Hand[i] + ",");
	}
}

void NewFileSave::WriteFile(std::string string)
{
	if (this->m_Outfile != nullptr)
		*this->m_Outfile << string;
}

void NewFileSave::WriteFile(std::vector<std::string>string)
{
	for (int i = 0; i < string.size(); i++)
	{
		if (i == string.size() - 1)
			this->WriteFile(string[i] + "\n");
		else
			this->WriteFile(string[i] + ",");
	}
}