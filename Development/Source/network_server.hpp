#pragma once

#include <Windows.h>
#include <string>

using std::string;

class NetworkServer final
{
public:
	void start();
	void stop();

private:
	static inline const string SERVER_PORT = "61205";
};