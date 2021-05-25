#pragma once

#include <string>

using std::string;

// Manually declare SOCKET, because winsock2.h cannot be included in this header
typedef unsigned __int64 SOCKET;

struct NetworkRequest final
{
	NetworkRequest(const string& ipAddress, const string& message) :
		ipAddress(ipAddress),
		message(message)
	{

	}

	const string ipAddress;
	const string message;
};