#include "script_interpreter.hpp"

#include <fstream>
#include <direct.h>
#include <filesystem>

bool ScriptInterpreter::_executeFe3dFilesystemFunction(const string& functionName, vector<ScriptValue>& arguments, vector<ScriptValue>& returnValues)
{
	// Determine type of function
	if (functionName == "fe3d:directory_is_existing")
	{
		auto types = { ScriptValueType::STRING };

		if (_validateListValueAmount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types) && _validateCurrentProject())
		{
			// Compose directory paths
			string directoryPath = (_fe3d.misc_getRootDirectory() + (_fe3d.application_isExported() ? "" : 
				("projects\\" + _currentProjectID)) + "\\saves\\");
			string newDirectoryPath = string(directoryPath + arguments[0].getString());

			// Return
			auto result =  _fe3d.misc_isDirectoryExisting(newDirectoryPath);
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::BOOLEAN, result));
		}
	}
	else if (functionName == "fe3d:directory_create")
	{
		auto types = { ScriptValueType::STRING };

		if (_validateListValueAmount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types) && _validateCurrentProject())
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
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
		}
	}
	else if (functionName == "fe3d:directory_delete")
	{
		auto types = { ScriptValueType::STRING };

		if (_validateListValueAmount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types) && _validateCurrentProject())
		{
			// Compose directory paths
			string directoryPath = (_fe3d.misc_getRootDirectory() + (_fe3d.application_isExported() ? "" : 
				("projects\\" + _currentProjectID)) + "\\saves\\");
			string newDirectoryPath = string(directoryPath + arguments[0].getString());

			// Check if directory exists
			if (_fe3d.misc_isDirectoryExisting(newDirectoryPath))
			{
				std::filesystem::remove_all(newDirectoryPath);
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
			}
			else
			{
				_throwScriptError("cannot delete directory \"" + arguments[0].getString() + "\"!");
			}
		}
	}
	else if (functionName == "fe3d:file_is_existing")
	{
		auto types = { ScriptValueType::STRING };

		if (_validateListValueAmount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types) && _validateCurrentProject())
		{
			// Compose file path
			string directoryPath = (_fe3d.misc_getRootDirectory() + (_fe3d.application_isExported() ? "" : 
				("projects\\" + _currentProjectID)) + "\\saves\\");
			string filePath = directoryPath + arguments[0].getString();

			// Return
			auto result = _fe3d.misc_isFileExisting(filePath);
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::BOOLEAN, result));
		}
	}
	else if (functionName == "fe3d:file_read")
	{
		auto types = { ScriptValueType::STRING };

		if (_validateListValueAmount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types) && _validateCurrentProject())
		{
			// Compose file path
			string directoryPath = (_fe3d.misc_getRootDirectory() + (_fe3d.application_isExported() ? "" : 
				("projects\\" + _currentProjectID)) + "\\saves\\");
			string filePath = directoryPath + arguments[0].getString();

			// Check if file exists
			if (_fe3d.misc_isFileExisting(filePath))
			{
				// Open file
				std::ifstream file(filePath);
				string line;

				// Add lines to list
				while (!file.eof())
				{
					std::getline(file, line);
					returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::STRING, line));
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
	else if (functionName == "fe3d:file_write")
	{
		auto types = { ScriptValueType::STRING };

		if (_validateListValueAmount(arguments, 2) && _validateCurrentProject())
		{
			// Compose file path
			string directoryPath = (_fe3d.misc_getRootDirectory() + (_fe3d.application_isExported() ? "" : 
				("projects\\" + _currentProjectID)) + "\\saves\\");
			string filePath = directoryPath + arguments[0].getString();

			// Open file
			std::ofstream file(filePath, std::ios::app);

			// Determine which type of value to print
			if (arguments[1].getType() == ScriptValueType::VEC3)
			{
				file << "[" + 
					to_string(arguments[1].getVec3().x) << " " <<
					to_string(arguments[1].getVec3().y) << " " <<
					to_string(arguments[1].getVec3().z) + "]";
			}
			else if (arguments[1].getType() == ScriptValueType::STRING)
			{
				file << arguments[1].getString();
			}
			else if (arguments[1].getType() == ScriptValueType::DECIMAL)
			{
				file << to_string(arguments[1].getDecimal());
			}
			else if (arguments[1].getType() == ScriptValueType::INTEGER)
			{
				file << to_string(arguments[1].getInteger());
			}
			else if (arguments[1].getType() == ScriptValueType::BOOLEAN)
			{
				file << (arguments[1].getBoolean() ? "<true>" : "<false>");
			}

			// Close file
			file.close();

			// Return
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
		}
	}
	else if (functionName == "fe3d:file_add_new_line")
	{
		auto types = { ScriptValueType::STRING };

		if (_validateListValueAmount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types) && _validateCurrentProject())
		{
			// Compose file path
			string directoryPath = (_fe3d.misc_getRootDirectory() + (_fe3d.application_isExported() ? "" : 
				("projects\\" + _currentProjectID)) + "\\saves\\");
			string filePath = directoryPath + arguments[0].getString();

			// Write line to file
			std::ofstream file(filePath, std::ios::app);
			file << std::endl;
			file.close();
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
		}
	}
	else if (functionName == "fe3d:file_clear")
	{
		auto types = { ScriptValueType::STRING };

		if (_validateListValueAmount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types) && _validateCurrentProject())
		{
			// Compose file path
			string directoryPath = (_fe3d.misc_getRootDirectory() + (_fe3d.application_isExported() ? "" : 
				("projects\\" + _currentProjectID)) + "\\saves\\");
			string filePath = directoryPath + arguments[0].getString();

			// Check if file exists
			if (_fe3d.misc_isFileExisting(filePath))
			{
				std::ofstream file(filePath, std::ios::trunc);
				file.close();
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
			}
			else
			{
				_throwScriptError("cannot clear file \"" + arguments[0].getString() + "\"!");
			}
		}
	}
	else if (functionName == "fe3d:file_delete")
	{
		auto types = { ScriptValueType::STRING };

		if (_validateListValueAmount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types) && _validateCurrentProject())
		{
			// Compose file path
			string directoryPath = (_fe3d.misc_getRootDirectory() + (_fe3d.application_isExported() ? "" : 
				("projects\\" + _currentProjectID)) + "\\saves\\");
			string filePath = directoryPath + arguments[0].getString();

			// Check if file exists
			if (_fe3d.misc_isFileExisting(filePath))
			{
				auto status = std::remove(filePath.c_str());
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
			}
			else
			{
				_throwScriptError("cannot delete file \"" + arguments[0].getString() + "\"!");
			}
		}
	}
	else
	{
		return false;
	}

	return true;
}