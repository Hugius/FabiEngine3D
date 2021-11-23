#include "script_interpreter.hpp"
#include "tools.hpp"
#include "configuration.hpp"

#include <fstream>
#include <direct.h>
#include <filesystem>

using std::endl;
using std::ios;
using std::ofstream;

using SVT = ScriptValueType;

const bool ScriptInterpreter::_executeFe3dFilesystemSetterFunction(const string& functionName, vector<ScriptValue>& arguments, vector<ScriptValue>& returnValues)
{
	// Determine type of function
	if(functionName == "fe3d:directory_create")
	{
		auto types = {SVT::STRING};

		// Validate arguments
		if(_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types) && _validateSavesDirectory())
		{
			// Compose directory path
			const auto isExported = Config::getInst().isApplicationExported();
			const auto rootPath = Tools::getRootDirectoryPath();
			const string directoryPath = string(rootPath + (isExported ? "" : ("projects\\" + _currentProjectID + "\\")) + "saves\\");
			const string newDirectoryPath = string(directoryPath + arguments[0].getString());

			// Check if directory exists
			if(Tools::isDirectoryExisting(newDirectoryPath))
			{
				_throwScriptError("cannot create directory \"" + arguments[0].getString() + "\"!");
			}
			else
			{
				Tools::createDirectory(newDirectoryPath);
			}

			// Return
			returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:directory_delete")
	{
		auto types = {SVT::STRING};

		// Validate arguments
		if(_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types) && _validateSavesDirectory())
		{
			// Compose directory path
			const auto isExported = Config::getInst().isApplicationExported();
			const auto rootPath = Tools::getRootDirectoryPath();
			const string directoryPath = string(rootPath + (isExported ? "" : ("projects\\" + _currentProjectID + "\\")) + "saves\\");
			const string newDirectoryPath = string(directoryPath + arguments[0].getString());

			// Check if directory exists
			if(Tools::isDirectoryExisting(newDirectoryPath))
			{
				Tools::deleteDirectory(newDirectoryPath);
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
			else
			{
				_throwScriptError("cannot delete directory \"" + arguments[0].getString() + "\"!");
			}
		}
	}
	else if(functionName == "fe3d:file_create")
	{
		auto types = {SVT::STRING};

		// Validate arguments
		if(_validateListValueCount(arguments, 2) && _validateSavesDirectory())
		{
			// Compose file path
			const auto isExported = Config::getInst().isApplicationExported();
			const auto rootPath = Tools::getRootDirectoryPath();
			const string directoryPath = string(rootPath + (isExported ? "" : ("projects\\" + _currentProjectID + "\\")) + "saves\\");
			const string filePath = string(directoryPath + arguments[0].getString());

			// Check if file exists
			if(Tools::isFileExisting(filePath))
			{
				_throwScriptError("cannot create file \"" + arguments[0].getString() + "\"!");
			}
			else
			{
				ofstream file(filePath);
				file.close();
			}

			// Return
			returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:file_delete")
	{
		auto types = {SVT::STRING};

		// Validate arguments
		if(_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types) && _validateSavesDirectory())
		{
			// Compose file path
			const auto isExported = Config::getInst().isApplicationExported();
			const auto rootPath = Tools::getRootDirectoryPath();
			const string directoryPath = string(rootPath + (isExported ? "" : ("projects\\" + _currentProjectID + "\\")) + "saves\\");
			const string filePath = string(directoryPath + arguments[0].getString());

			// Check if file exists
			if(Tools::isFileExisting(filePath))
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
	else if(functionName == "fe3d:file_write")
	{
		auto types = {SVT::STRING};

		// Validate arguments
		if(_validateListValueCount(arguments, 2) && _validateSavesDirectory())
		{
			// Compose file path
			const auto isExported = Config::getInst().isApplicationExported();
			const auto rootPath = Tools::getRootDirectoryPath();
			const string directoryPath = string(rootPath + (isExported ? "" : ("projects\\" + _currentProjectID + "\\")) + "saves\\");
			const string filePath = string(directoryPath + arguments[0].getString());

			// Check if file exists
			if(Tools::isFileExisting(filePath))
			{
				// Open file
				ofstream file(filePath, ios::app);

				// Determine which type of value to print
				if(arguments[1].getType() == SVT::STRING)
				{
					file << arguments[1].getString();
				}
				else if(arguments[1].getType() == SVT::DECIMAL)
				{
					file << to_string(arguments[1].getDecimal());
				}
				else if(arguments[1].getType() == SVT::INTEGER)
				{
					file << to_string(arguments[1].getInteger());
				}
				else if(arguments[1].getType() == SVT::BOOLEAN)
				{
					file << (arguments[1].getBoolean() ? "<true>" : "<false>");
				}

				// Close file
				file.close();
			}
			else
			{
				_throwScriptError("cannot write to file \"" + arguments[0].getString() + "\"!");
			}

			// Return
			returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:file_add_new_line")
	{
		auto types = {SVT::STRING};

		// Validate arguments
		if(_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types) && _validateSavesDirectory())
		{
			// Compose file path
			const auto isExported = Config::getInst().isApplicationExported();
			const auto rootPath = Tools::getRootDirectoryPath();
			const string directoryPath = string(rootPath + (isExported ? "" : ("projects\\" + _currentProjectID + "\\")) + "saves\\");
			const string filePath = string(directoryPath + arguments[0].getString());

			// Check if file exists
			if(Tools::isFileExisting(filePath))
			{
				ofstream file(filePath, ios::app);
				file << endl;
				file.close();
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
			else
			{
				_throwScriptError("cannot add new line to file \"" + arguments[0].getString() + "\"!");
			}
		}
	}
	else if(functionName == "fe3d:file_clear")
	{
		auto types = {SVT::STRING};

		// Validate arguments
		if(_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types) && _validateSavesDirectory())
		{
			// Compose file path
			const auto isExported = Config::getInst().isApplicationExported();
			const auto rootPath = Tools::getRootDirectoryPath();
			const string directoryPath = string(rootPath + (isExported ? "" : ("projects\\" + _currentProjectID + "\\")) + "saves\\");
			const string filePath = string(directoryPath + arguments[0].getString());

			// Check if file exists
			if(Tools::isFileExisting(filePath))
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