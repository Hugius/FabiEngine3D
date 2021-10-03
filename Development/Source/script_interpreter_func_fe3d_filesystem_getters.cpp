#include "script_interpreter.hpp"

#include <fstream>

using std::ifstream;

using SVT = ScriptValueType;

bool ScriptInterpreter::_executeFe3dFilesystemGetterFunction(const string& functionName, vector<ScriptValue>& arguments, vector<ScriptValue>& returnValues)
{
	// Determine type of function
	if (functionName == "fe3d:directory_is_existing")
	{
		auto types = { SVT::STRING };

		// Validate arguments
		if (_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types) && _validateSavesDirectory())
		{
			// Compose directory paths
			string directoryPath = (_fe3d.misc_getRootDirectory() + (_fe3d.application_isExported() ? "" : 
				("projects\\" + _currentProjectID)) + "\\saves\\");
			string newDirectoryPath = string(directoryPath + arguments[0].getString());

			// Return
			auto result =  _fe3d.misc_isDirectoryExisting(newDirectoryPath);
			returnValues.push_back(ScriptValue(_fe3d, SVT::BOOLEAN, result));
		}
	}
	else if (functionName == "fe3d:file_is_existing")
	{
		auto types = { SVT::STRING };

		// Validate arguments
		if (_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types) && _validateSavesDirectory())
		{
			// Compose file path
			string directoryPath = (_fe3d.misc_getRootDirectory() + (_fe3d.application_isExported() ? "" : 
				("projects\\" + _currentProjectID)) + "\\saves\\");
			string filePath = directoryPath + arguments[0].getString();

			// Return
			auto result = _fe3d.misc_isFileExisting(filePath);
			returnValues.push_back(ScriptValue(_fe3d, SVT::BOOLEAN, result));
		}
	}
	else if (functionName == "fe3d:file_read")
	{
		auto types = { SVT::STRING };

		// Validate arguments
		if (_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types) && _validateSavesDirectory())
		{
			// Compose file path
			string directoryPath = (_fe3d.misc_getRootDirectory() + (_fe3d.application_isExported() ? "" : 
				("projects\\" + _currentProjectID)) + "\\saves\\");
			string filePath = directoryPath + arguments[0].getString();

			// Check if file exists
			if (_fe3d.misc_isFileExisting(filePath))
			{
				// Open file
				ifstream file(filePath);
				string line;

				// Add lines to list
				while (!file.eof())
				{
					getline(file, line);
					returnValues.push_back(ScriptValue(_fe3d, SVT::STRING, line));
				}

				// Close file
				file.close();
			}
			else
			{
				_throwScriptError("cannot read from file \"" + arguments[0].getString() + "\"!");
			}
		}
	}
	else
	{
		return false;
	}

	return true;
}