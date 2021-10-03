#include "script_interpreter.hpp"

#include <fstream>
#include <direct.h>
#include <filesystem>

using std::endl;
using std::ios;
using std::ofstream;
using std::filesystem::remove_all;

using SVT = ScriptValueType;

bool ScriptInterpreter::_executeFe3dFilesystemSetterFunction(const string& functionName, vector<ScriptValue>& arguments, vector<ScriptValue>& returnValues)
{
	// Determine type of function
	if (functionName == "fe3d:directory_create")
	{
		auto types = { SVT::STRING };

		// Validate arguments
		if (_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types) && _validateSavesDirectory())
		{
			// Compose directory paths
			string directoryPath = (_fe3d.misc_getRootDirectory() + (_fe3d.application_isExported() ? "" : 
				("projects\\" + _currentProjectID)) + "\\saves\\");
			string newDirectoryPath = string(directoryPath + arguments[0].getString());

			// Try to create new directory
			if (_fe3d.misc_createNewDirectory(newDirectoryPath))
			{
				_throwScriptError("cannot create directory \"" + arguments[0].getString() + "\"!");
			}

			// Return
			returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
		}
	}
	else if (functionName == "fe3d:directory_delete")
	{
		auto types = { SVT::STRING };

		// Validate arguments
		if (_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types) && _validateSavesDirectory())
		{
			// Compose directory paths
			string directoryPath = (_fe3d.misc_getRootDirectory() + (_fe3d.application_isExported() ? "" : 
				("projects\\" + _currentProjectID)) + "\\saves\\");
			string newDirectoryPath = string(directoryPath + arguments[0].getString());

			// Check if directory exists
			if (_fe3d.misc_isDirectoryExisting(newDirectoryPath))
			{
				remove_all(newDirectoryPath);
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
			else
			{
				_throwScriptError("cannot delete directory \"" + arguments[0].getString() + "\"!");
			}
		}
	}
	else if (functionName == "fe3d:file_delete")
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
				auto status = remove(filePath.c_str());
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
			else
			{
				_throwScriptError("cannot delete file \"" + arguments[0].getString() + "\"!");
			}
		}
	}
	else if (functionName == "fe3d:file_write")
	{
		auto types = { SVT::STRING };

		// Validate arguments
		if (_validateListValueCount(arguments, 2) && _validateSavesDirectory())
		{
			// Compose file path
			string directoryPath = (_fe3d.misc_getRootDirectory() + (_fe3d.application_isExported() ? "" : 
				("projects\\" + _currentProjectID)) + "\\saves\\");
			string filePath = directoryPath + arguments[0].getString();

			// Open file
			ofstream file(filePath, ios::app);

			// Determine which type of value to print
			if (arguments[1].getType() == SVT::VEC3)
			{
				file << "[" + 
					to_string(arguments[1].getVec3().x) << " " <<
					to_string(arguments[1].getVec3().y) << " " <<
					to_string(arguments[1].getVec3().z) + "]";
			}
			else if (arguments[1].getType() == SVT::STRING)
			{
				file << arguments[1].getString();
			}
			else if (arguments[1].getType() == SVT::DECIMAL)
			{
				file << to_string(arguments[1].getDecimal());
			}
			else if (arguments[1].getType() == SVT::INTEGER)
			{
				file << to_string(arguments[1].getInteger());
			}
			else if (arguments[1].getType() == SVT::BOOLEAN)
			{
				file << (arguments[1].getBoolean() ? "<true>" : "<false>");
			}

			// Close file
			file.close();

			// Return
			returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
		}
	}
	else if (functionName == "fe3d:file_add_new_line")
	{
		auto types = { SVT::STRING };

		// Validate arguments
		if (_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types) && _validateSavesDirectory())
		{
			// Compose file path
			string directoryPath = (_fe3d.misc_getRootDirectory() + (_fe3d.application_isExported() ? "" : 
				("projects\\" + _currentProjectID)) + "\\saves\\");
			string filePath = directoryPath + arguments[0].getString();

			// Write line to file
			ofstream file(filePath, ios::app);
			file << endl;
			file.close();
			returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
		}
	}
	else if (functionName == "fe3d:file_clear")
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
				ofstream file(filePath, ios::trunc);
				file.close();
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
			else
			{
				_throwScriptError("cannot clear file \"" + arguments[0].getString() + "\"!");
			}
		}
	}
	else
	{
		return false;
	}

	return true;
}