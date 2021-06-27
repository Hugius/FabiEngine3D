#pragma once

#include "network_protocol.hpp"

#include <string>

using std::string;

struct NetworkClientMessage final
{
	NetworkClientMessage() = default;

	NetworkClientMessage(
		const string& IP,
		const string& port,
		const string& username,
		const string& content,
		const NetworkProtocol protocol)
		:
		IP(IP),
		port(port),
		username(username),
		content(content),
		protocol(protocol)
	{

	}

	const string IP;
	const string port;
	const string username;
	const string content;
	const NetworkProtocol protocol;
};