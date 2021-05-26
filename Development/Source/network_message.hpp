#pragma once

#include <string>

using std::string;

// Manually declare SOCKET, because winsock2.h cannot be included in this header
typedef unsigned __int64 SOCKET;

struct NetworkMessage final
{
	NetworkMessage(const string& ipAddress, const string& content) :
		ipAddress(ipAddress),
		content(content)
	{

	}

	const string ipAddress;
	const string content;
};