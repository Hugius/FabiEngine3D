#include "script_interpreter.hpp"

vector<ScriptValue> ScriptInterpreter::_extractArguments(string argumentString)
{
	vector<ScriptValue> argumentList;
	bool buildingString = false;
	bool buildingNumber = false;
	bool buildingBoolean = false;
	bool finishedArgument = false;
	string argumentContent = "";

	// Argument string cannot start with a comma
	if (argumentString[0] == ',')
	{
		return {};
	}

	// For every character in argument string
	for (auto& c : argumentString)
	{
		if (finishedArgument) // First character after an argument has been extracted
		{
			if (c == ',') // Ready for next argument extraction
			{
				finishedArgument = false;
			}
			else // After an argument has been extracted, a comma must ALWAYS follow
			{
				return {};
			}
		}
		else
		{
			if (buildingString) // Processing STRING argument
			{
				if (c == '"')
				{
					argumentList.push_back(ScriptValue(ScriptValueType::STRING, argumentContent));
					buildingString = false;
					finishedArgument = true;
				}
				else
				{
					argumentContent += c;
				}
			}
			else if (buildingNumber) // Processing NUMBER argument
			{
				if (isdigit(c)) // Keep building number
				{
					argumentContent += c;
				}
			}
			else if (buildingBoolean) // Processing BOOLEAN argument
			{
				argumentContent += c;

				// Check if argument is true, false, or invalid
				if (argumentContent.size() == 4)
				{
					if (argumentContent == "true") // Add new boolean argument
					{
						argumentList.push_back(ScriptValue(ScriptValueType::BOOLEAN, true));
						buildingBoolean = false;
						finishedArgument = true;
					}
					else if (argumentContent != "fals") // Must be "fals" if 4 letter string
					{
						return {};
					}
				}
				else if (argumentContent.size() == 5 && argumentContent == "false") // Add new boolean argument
				{
					argumentList.push_back(ScriptValue(ScriptValueType::BOOLEAN, false));
					buildingBoolean = false;
					finishedArgument = true;
				}
				else // Invalid boolean string
				{
					return {};
				}
			}
			else // Starting build of new argument
			{
				if (c == '"')
				{
					argumentContent = "";
					buildingString = true;
				}
				else if (isdigit(c))
				{
					argumentContent = "";
					argumentContent.push_back(c);
					buildingNumber = true;
				}
				else if (c == 't' || c == 'f')
				{
					argumentContent = "";
					argumentContent.push_back(c);
					buildingBoolean = true;
				}
			}
		}
	}

	return argumentList;
}