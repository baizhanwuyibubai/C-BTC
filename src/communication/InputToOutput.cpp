#include "InputToOutput.h"
#include "../OverallClass/Hand.h"
InputToOutput::InputToOutput(std::string IP, short Port) : TCP(IP, Port)
{
	this->m_IsThread = true;
	std::thread t1(&InputToOutput::OutThread, this);
	t1.detach();
}

InputToOutput::~InputToOutput()
{
	this->m_IsThread = false;
}

bool InputToOutput::IsOpen()
{
	return this->IsTCPOpen();
}

void InputToOutput::OutThread()
{
	char buff[1024];
	while (this->m_IsThread)
	{
		int Len = this->Read(buff, 1024);
		STR_SocketData* SocketData = (STR_SocketData*)buff;
		if (Len != 0 && SocketData->Initial.OneWord == INITIAL)
		{
			ReadSocketData(buff);
		}
	}
}

void InputToOutput::ReadSocketData(void* buff)
{
	STR_SocketData* SocketData = (STR_SocketData*)buff;

	switch (SocketData->Initial.Type)
	{
	case UI_Type::Socket_End:
	{
		exit(0);
		break;
	}
	case 0x1001:

		break;
	default:

		break;
	}
}

int InputToOutput::GroupData(UI_Type Type, char* buff, int len)
{
	STR_SocketData Data;
	Data.Initial.OneWord = INITIAL;
	Data.Initial.Type = Type;
	if (len != 0)
	{
		memcpy(Data.buff, buff, len);
		Data.Initial.SocketSize = len;
	}
	return this->Write((char*)&Data, sizeof(Data.Initial) + Data.Initial.SocketSize);
}

int InputToOutput::GroupData(UI_Type Type, void* buff, int len)
{
	STR_SocketData Data;
	Data.Initial.OneWord = INITIAL;
	Data.Initial.Type = Type;
	char* buf = (char*)buff;
	if (len != 0)
	{
		memcpy(Data.buff, buf, len);
		Data.Initial.SocketSize = len;
	}
	return this->Write((char*)&Data, sizeof(Data.Initial) + Data.Initial.SocketSize);
}