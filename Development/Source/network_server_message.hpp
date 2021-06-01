#pragma once

#include <string>

using std::string;

struct NetworkServerMessage final
{
	NetworkServerMessage() = default;

	NetworkServerMessage(
		const string& content)
		:
		content(content)
	{

	}

	const string content;
};