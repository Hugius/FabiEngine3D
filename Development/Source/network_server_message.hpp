#pragma once

#include "network_protocol.hpp"

#include <string>

using std::string;

struct NetworkServerMessage final
{
	NetworkServerMessage(
		const string& content,
		const NetworkProtocol protocol)
		:
		content(content),
		protocol(protocol)
	{

	}

	const string content;
	const NetworkProtocol protocol;
};