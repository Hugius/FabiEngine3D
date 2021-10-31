#pragma once

#include "network_protocol.hpp"

#include <string>

using std::string;

struct NetworkClientMessage final
{
	NetworkClientMessage(
		const string& username,
		const string& content,
		const NetworkProtocol protocol)
		:
		username(username),
		content(content),
		protocol(protocol)
	{

	}

	const string username;
	const string content;
	const NetworkProtocol protocol;
};