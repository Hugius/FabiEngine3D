#pragma once

#pragma warning (disable : 4996)

#include <conio.h>
#include <Windows.h>
#include <iostream>
#include <ctime>
#include <string>
#include <GLM/glm.hpp>
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
		p_printPrefix(MessageType::INFO, first, rest...);
	}

	template<typename T, typename...Rest> 
	inline void throwError(T first, Rest...rest)
	{
		std::cout << std::endl;
		p_printPrefix(MessageType::ERR, first, rest...);
		std::cout << std::endl;
		throwInfo("Type something to quit...");
		auto temp = _getch();
		exit(420);
	}

	template<typename T, typename...Rest> 
	inline void throwDebug(T first, Rest...rest)
	{
		p_printPrefix(MessageType::DEBUG, first, rest...);
	}

	template<typename T, typename...Rest> 
	inline void throwWarning(T first, Rest...rest)
	{
		p_printPrefix(MessageType::WARNING, first, rest...);
	}

private:
	Logger() = default;

	enum class MessageType { INFO, ERR, DEBUG, WARNING };

	string p_level_string[4] = { "Info", "Error", "Debug", "Warn" };

	template<typename T, typename...Rest> 
	inline void p_printPrefix(MessageType type, T first, Rest&&...rest)
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
		std::cout << "[" + p_level_string[static_cast<int>(type)] + "]";
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

		p_printMessage(first, rest...);
	}

	template<typename T, typename...Rest>
	inline void p_printMessage(T first, Rest&&...rest)
	{
		std::cout << first;
		(std::cout << ... << rest);
		std::cout << std::endl;
	}
};