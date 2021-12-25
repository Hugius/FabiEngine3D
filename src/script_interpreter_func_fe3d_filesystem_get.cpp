#include "script_interpreter.hpp"
#include "tools.hpp"
#include "configuration.hpp"

#include <fstream>

using std::ifstream;

using SVT = ScriptValueType;

const bool ScriptInterpreter::_executeFe3dFilesystemGetter(const string& functionName, vector<ScriptValue>& args, vector<ScriptValue>& returnValues)
{
	if(functionName == "fe3d:directory_is_existing")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types) && _validateSavesDirectory())
		{
			const auto isExported = Config::getInst().isApplicationExported();
			const auto rootPath = Tools::getRootDirectoryPath();
			const string directoryPath = string(rootPath + (isExported ? "" : ("projects\\" + _currentProjectID + "\\")) + "saves\\");
			const string newDirectoryPath = string(directoryPath + args[0].getString());

			auto result = Tools::isDirectoryExisting(newDirectoryPath);
			returnValues.push_back(ScriptValue(_fe3d, SVT::BOOLEAN, result));
		}
	}
	else if(functionName == "fe3d:file_is_existing")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types) && _validateSavesDirectory())
		{
			const auto isExported = Config::getInst().isApplicationExported();
			const auto rootPath = Tools::getRootDirectoryPath();
			const string directoryPath = string(rootPath + (isExported ? "" : ("projects\\" + _currentProjectID + "\\")) + "saves\\");
			const string filePath = (directoryPath + args[0].getString());

			auto result = Tools::isFileExisting(filePath);
			returnValues.push_back(ScriptValue(_fe3d, SVT::BOOLEAN, result));
		}
	}
	else if(functionName == "fe3d:file_read")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types) && _validateSavesDirectory())
		{
			const auto isExported = Config::getInst().isApplicationExported();
			const auto rootPath = Tools::getRootDirectoryPath();
			const string directoryPath = string(rootPath + (isExported ? "" : ("projects\\" + _currentProjectID + "\\")) + "saves\\");
			const string filePath = (directoryPath + args[0].getString());

			if(Tools::isFileExisting(filePath))
			{
				ifstream file(filePath);
				string line;

				while(!file.eof())
				{
					getline(file, line);
					returnValues.push_back(ScriptValue(_fe3d, SVT::STRING, line));
				}

				file.close();
			}
			else
			{
				_throwScriptError("cannot read from file \"" + args[0].getString() + "\"!");
			}
		}
	}
	else
	{
		return false;
	}

	return true;
}