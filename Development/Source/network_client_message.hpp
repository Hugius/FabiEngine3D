#pragma once

#include <string>

using std::string;

struct NetworkClientMessage final
{
	NetworkClientMessage() = default;

	NetworkClientMessage(
		const string& IP,
		const string& port,
		const string& username,
		const string& content)
		:
		IP(IP),
		port(port),
		username(username),
		content(content)
	{

	}

	const string IP;
	const string port;
	const string username;
	const string content;
};