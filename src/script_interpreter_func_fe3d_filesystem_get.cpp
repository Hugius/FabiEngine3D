#include "script_interpreter.hpp"
#include "tools.hpp"
#include "configuration.hpp"

#include <fstream>

using std::ifstream;

using SVT = ScriptValueType;

const bool ScriptInterpreter::_executeFe3dFilesystemGetter(const string& functionName, const vector<shared_ptr<ScriptValue>>& args, vector<shared_ptr<ScriptValue>>& returnValues)
{
	if(functionName == "fe3d:directory_is_existing")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types) && _validateSavesDirectory())
		{
			const auto isExported = Config::getInst().isApplicationExported();
			const auto rootPath = Tools::getRootDirectoryPath();
			const auto directoryPath = string(rootPath + (isExported ? "" : ("projects\\" + _currentProjectId + "\\")) + "saves\\");
			const auto newDirectoryPath = string(directoryPath + args[0]->getString());

			const auto result = Tools::isDirectoryExisting(newDirectoryPath);

			returnValues.push_back(make_shared<ScriptValue>(SVT::BOOLEAN, result));
		}
	}
	else if(functionName == "fe3d:file_is_existing")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types) && _validateSavesDirectory())
		{
			const auto isExported = Config::getInst().isApplicationExported();
			const auto rootPath = Tools::getRootDirectoryPath();
			const auto directoryPath = string(rootPath + (isExported ? "" : ("projects\\" + _currentProjectId + "\\")) + "saves\\");
			const auto filePath = (directoryPath + args[0]->getString());

			const auto result = Tools::isFileExisting(filePath);

			returnValues.push_back(make_shared<ScriptValue>(SVT::BOOLEAN, result));
		}
	}
	else if(functionName == "fe3d:file_read")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types) && _validateSavesDirectory())
		{
			const auto isExported = Config::getInst().isApplicationExported();
			const auto rootPath = Tools::getRootDirectoryPath();
			const auto directoryPath = string(rootPath + (isExported ? "" : ("projects\\" + _currentProjectId + "\\")) + "saves\\");
			const auto filePath = (directoryPath + args[0]->getString());

			auto file = ifstream(filePath);
			if(!file)
			{
				_throwRuntimeError("cannot read from file \"" + args[0]->getString() + "\"");
				return true;
			}

			string line;
			while(!file.eof())
			{
				getline(file, line);

				returnValues.push_back(make_shared<ScriptValue>(SVT::STRING, line));
			}

			file.close();
		}
	}
	else
	{
		return false;
	}

	return true;
}