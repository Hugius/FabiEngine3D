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

const bool ScriptInterpreter::_executeFe3dFilesystemSetter(const string& functionName, vector<ScriptValue>& args, vector<ScriptValue>& returnValues)
{
	if(functionName == "fe3d:directory_create")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types) && _validateSavesDirectory())
		{
			const auto isExported = Config::getInst().isApplicationExported();
			const auto rootPath = Tools::getRootDirectoryPath();
			const auto directoryPath = string(rootPath + (isExported ? "" : ("projects\\" + _currentProjectID + "\\")) + "saves\\");
			const string newDirectoryPath = string(directoryPath + args[0].getString());

			if(Tools::isDirectoryExisting(newDirectoryPath))
			{
				_throwScriptError("cannot create directory \"" + args[0].getString() + "\"!");
			}
			else
			{
				Tools::createDirectory(newDirectoryPath);
			}

			returnValues.push_back(ScriptValue(SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:directory_delete")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types) && _validateSavesDirectory())
		{
			const auto isExported = Config::getInst().isApplicationExported();
			const auto rootPath = Tools::getRootDirectoryPath();
			const auto directoryPath = string(rootPath + (isExported ? "" : ("projects\\" + _currentProjectID + "\\")) + "saves\\");
			const string newDirectoryPath = string(directoryPath + args[0].getString());

			if(Tools::isDirectoryExisting(newDirectoryPath))
			{
				Tools::deleteDirectory(newDirectoryPath);
				returnValues.push_back(ScriptValue(SVT::EMPTY));
			}
			else
			{
				_throwScriptError("cannot delete directory \"" + args[0].getString() + "\"!");
			}
		}
	}
	else if(functionName == "fe3d:file_create")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, 2) && _validateSavesDirectory())
		{
			const auto isExported = Config::getInst().isApplicationExported();
			const auto rootPath = Tools::getRootDirectoryPath();
			const auto directoryPath = string(rootPath + (isExported ? "" : ("projects\\" + _currentProjectID + "\\")) + "saves\\");
			const auto filePath = string(directoryPath + args[0].getString());

			if(Tools::isFileExisting(filePath))
			{
				_throwScriptError("cannot create file \"" + args[0].getString() + "\"!");
			}
			else
			{
				ofstream file(filePath);
				file.close();
			}

			returnValues.push_back(ScriptValue(SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:file_delete")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types) && _validateSavesDirectory())
		{
			const auto isExported = Config::getInst().isApplicationExported();
			const auto rootPath = Tools::getRootDirectoryPath();
			const auto directoryPath = string(rootPath + (isExported ? "" : ("projects\\" + _currentProjectID + "\\")) + "saves\\");
			const auto filePath = string(directoryPath + args[0].getString());

			if(Tools::isFileExisting(filePath))
			{
				auto status = remove(filePath.c_str());
				returnValues.push_back(ScriptValue(SVT::EMPTY));
			}
			else
			{
				_throwScriptError("cannot delete file \"" + args[0].getString() + "\"!");
			}
		}
	}
	else if(functionName == "fe3d:file_write")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, 2) && _validateSavesDirectory())
		{
			const auto isExported = Config::getInst().isApplicationExported();
			const auto rootPath = Tools::getRootDirectoryPath();
			const auto directoryPath = string(rootPath + (isExported ? "" : ("projects\\" + _currentProjectID + "\\")) + "saves\\");
			const auto filePath = string(directoryPath + args[0].getString());

			if(Tools::isFileExisting(filePath))
			{
				ofstream file(filePath, ios::app);

				if(args[1].getType() == SVT::STRING)
				{
					file << args[1].getString();
				}
				else if(args[1].getType() == SVT::DECIMAL)
				{
					file << to_string(args[1].getDecimal());
				}
				else if(args[1].getType() == SVT::INTEGER)
				{
					file << to_string(args[1].getInteger());
				}
				else if(args[1].getType() == SVT::BOOLEAN)
				{
					file << (args[1].getBoolean() ? "<true>" : "<false>");
				}

				file.close();
			}
			else
			{
				_throwScriptError("cannot write to file \"" + args[0].getString() + "\"!");
			}

			returnValues.push_back(ScriptValue(SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:file_add_new_line")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types) && _validateSavesDirectory())
		{
			const auto isExported = Config::getInst().isApplicationExported();
			const auto rootPath = Tools::getRootDirectoryPath();
			const auto directoryPath = string(rootPath + (isExported ? "" : ("projects\\" + _currentProjectID + "\\")) + "saves\\");
			const auto filePath = string(directoryPath + args[0].getString());

			if(Tools::isFileExisting(filePath))
			{
				ofstream file(filePath, ios::app);
				file << endl;
				file.close();
				returnValues.push_back(ScriptValue(SVT::EMPTY));
			}
			else
			{
				_throwScriptError("cannot add new line to file \"" + args[0].getString() + "\"!");
			}
		}
	}
	else if(functionName == "fe3d:file_clear")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types) && _validateSavesDirectory())
		{
			const auto isExported = Config::getInst().isApplicationExported();
			const auto rootPath = Tools::getRootDirectoryPath();
			const auto directoryPath = string(rootPath + (isExported ? "" : ("projects\\" + _currentProjectID + "\\")) + "saves\\");
			const auto filePath = string(directoryPath + args[0].getString());

			if(Tools::isFileExisting(filePath))
			{
				ofstream file(filePath, ios::trunc);
				file.close();
				returnValues.push_back(ScriptValue(SVT::EMPTY));
			}
			else
			{
				_throwScriptError("cannot clear file \"" + args[0].getString() + "\"!");
			}
		}
	}
	else
	{
		return false;
	}

	return true;
}