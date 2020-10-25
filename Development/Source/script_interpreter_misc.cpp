#include "script_interpreter.hpp"

vector<ScriptValue> ScriptInterpreter::_extractArguments(string argumentString)
{
	// Temporary variables
	vector<ScriptValue> argumentList;
	bool buildingString = false;
	bool buildingNumber = false;
	bool buildingDecimal = false;
	bool buildingBoolean = false;
	bool finishedArgument = false;
	string currentArgument = "";

	// Argument string cannot be empty
	if (argumentString.empty())
	{
		return {};
	}

	// Argument string cannot start with a comma
	if (argumentString[0] == ',')
	{
		return {};
	}

	// For every character in argument string
	unsigned int index = 0;
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
				if (c == '"') // Add new string argument
				{
					auto newArgument = ScriptValue(_fe3d, ScriptValueType::STRING);
					newArgument.setString(currentArgument);
					argumentList.push_back(newArgument);
					buildingString = false;
					finishedArgument = true;
				}
				else // Keep building string
				{
					currentArgument += c;
				}
			}
			else if (buildingNumber) // Processing NUMBER argument
			{
				if (isdigit(c)) // Keep building number
				{
					currentArgument += c;
				}
				else if (c == '.' && !buildingDecimal) // Start building decimal
				{
					currentArgument += c;
					buildingDecimal = true;
				}
				
				// Check if number building finished
				if (c == ',' || index == argumentString.size() - 1)
				{
					if (buildingDecimal) // Convert to decimal
					{
						// Check if decimal argument is valid
						if (currentArgument.back() == '.')
						{
							return {};
						}
						else
						{
							auto newArgument = ScriptValue(_fe3d, ScriptValueType::DECIMAL);
							newArgument.setDecimal(stof(currentArgument));
							argumentList.push_back(newArgument);
							buildingNumber = false;
							buildingDecimal = false;
						}
					}
					else // Convert to integer
					{
						auto newArgument = ScriptValue(_fe3d, ScriptValueType::INTEGER);
						newArgument.setInteger(stoi(currentArgument));
						argumentList.push_back(newArgument);
						buildingNumber = false;
					}
				}
			}
			else if (buildingBoolean) // Processing BOOLEAN argument
			{
				currentArgument += c;

				// Check if argument is true, false, or invalid
				if (currentArgument.size() == 4)
				{
					if (currentArgument == "true") // Add new boolean argument
					{
						auto newArgument = ScriptValue(_fe3d, ScriptValueType::BOOLEAN);
						newArgument.setBoolean(true);
						argumentList.push_back(newArgument);
						buildingBoolean = false;
						finishedArgument = true;
					}
					else if (currentArgument != "fals") // Must be "fals" if 4 letter string
					{
						return {};
					}
				}
				else if (currentArgument.size() == 5 && currentArgument == "false") // Add new boolean argument
				{
					auto newArgument = ScriptValue(_fe3d, ScriptValueType::BOOLEAN);
					newArgument.setBoolean(false);
					argumentList.push_back(newArgument);
					buildingBoolean = false;
					finishedArgument = true;
				}
				else if(currentArgument.size() > 5) // Invalid boolean string
				{
					return {};
				}
			}
			else // Starting build of new argument
			{
				if (c == '"') // STRING
				{
					currentArgument = "";
					buildingString = true;
				}
				else if (isdigit(c)) // NUMBER
				{
					currentArgument = "";
					currentArgument.push_back(c);
					buildingNumber = true;
				}
				else if (c == 't' || c == 'f') // BOOLEAN
				{
					currentArgument = "";
					currentArgument.push_back(c);
					buildingBoolean = true;
				}
			}
		}

		index++;
	}

	// Check if not still building any arguments
	if (!buildingString && !buildingNumber && !buildingBoolean)
	{
		return argumentList;
	}
	else // Syntax is wrong
	{
		return {};
	}
}