#pragma once

#include "network_protocol.hpp"

#include <string>

using std::string;

class NetworkingClientMessage final
{
public:
	NetworkingClientMessage(const string& username, const string& content, const NetworkProtocol protocol);

	const string& getUsername() const;
	const string& getContent() const;

	const NetworkProtocol getProtocol() const;

private:
	string _username;
	string _content;

	NetworkProtocol _protocol;
};