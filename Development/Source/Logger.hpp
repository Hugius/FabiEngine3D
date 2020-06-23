#pragma once

#pragma warning (disable : 4996)

#include <conio.h>
#include <Windows.h>
#include <iostream>
#include <ctime>
#include <string>
#include <GLM\\glm.hpp>
#include <type_traits>


using std::string;
using glm::vec3;

class Logger final
{
public:
	// Global instance
	static Logger& getInst()
	{
		static Logger instance;
		return instance;
	}

	// Safe singleton
	Logger(Logger const&) = delete;
	void operator=(Logger const&) = delete;

	template<typename T, typename...Rest> 
	inline void throwInfo(T first, Rest...rest)
	{
		_printPrefix(MessageType::INFO, first, rest...);
	}

	template<typename T, typename...Rest> 
	inline void throwError(T first, Rest...rest)
	{
		std::cout << std::endl;
		_printPrefix(MessageType::ERR, first, rest...);
		std::cout << std::endl;
		throwInfo("Type something to quit...");
		auto temp = _getch();
		exit(420);
	}

	template<typename T, typename...Rest> 
	inline void throwDebug(T first, Rest...rest)
	{
		_printPrefix(MessageType::DEBUG, first, rest...);
	}

	template<typename T, typename...Rest> 
	inline void throwWarning(T first, Rest...rest)
	{
		_printPrefix(MessageType::WARNING, first, rest...);
	}

private:
	Logger() = default;

	enum class MessageType { INFO, ERR, DEBUG, WARNING };

	string _level_string[4] = { "Info", "Error", "Debug", "Warn" };

	template<typename T, typename...Rest> 
	inline void _printPrefix(MessageType type, T first, Rest&&...rest)
	{
		HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE); //Console access

		//Current time
		char timeBuffer[64];
		auto t = std::time(nullptr);
		auto foo = *std::localtime(&t);
		std::strftime(timeBuffer, 64, "%H:%M:%S", &foo);

		SetConsoleTextAttribute(console, 6); //White
		std::cout << "[" << timeBuffer << "]";
		SetConsoleTextAttribute(console, 12); //Red
		std::cout << "[" + _level_string[static_cast<int>(type)] + "]";
		SetConsoleTextAttribute(console, 7); //Yellow

		//Proper indentation
		if (type == MessageType::DEBUG || type == MessageType::ERR) //5 chars
		{
			std::cout << "> ";

		}
		else //4 chars
		{
			std::cout << " > ";
		}

		_printMessage(first, rest...);
	}

	template<typename T, typename...Rest>
	inline void _printMessage(T first, Rest&&...rest)
	{
		std::cout << first;
		(std::cout << ... << rest);
		std::cout << std::endl;
	}
};