#pragma once

#include <string>

using std::string;

struct NetworkClientMessage final
{
	NetworkClientMessage() = default;

	NetworkClientMessage(
		const string& ipAddress,
		const string& port,
		const string& username,
		const string& content)
		:
		ipAddress(ipAddress),
		port(port),
		username(username),
		content(content)
	{

	}

	const string ipAddress;
	const string port;
	const string username;
	const string content;
};