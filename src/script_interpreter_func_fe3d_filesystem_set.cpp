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

const bool ScriptInterpreter::_executeFe3dFilesystemSetter(const string& functionName, const vector<shared_ptr<ScriptValue>>& args, vector<shared_ptr<ScriptValue>>& returnValues)
{
	if(functionName == "fe3d:directory_create")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types) && _validateSavesDirectory())
		{
			const auto isExported = Config::getInst().isApplicationExported();
			const auto rootPath = Tools::getRootDirectoryPath();
			const auto directoryPath = (rootPath + (isExported ? "" : ("projects\\" + _currentProjectId + "\\")) + "saves\\");
			const auto newDirectoryPath = (directoryPath + args[0]->getString());

			if(Tools::isDirectoryExisting(newDirectoryPath))
			{
				_throwRuntimeError("cannot create directory");
				return true;
			}

			Tools::createDirectory(newDirectoryPath);

			returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:directory_delete")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types) && _validateSavesDirectory())
		{
			const auto isExported = Config::getInst().isApplicationExported();
			const auto rootPath = Tools::getRootDirectoryPath();
			const auto directoryPath = (rootPath + (isExported ? "" : ("projects\\" + _currentProjectId + "\\")) + "saves\\");
			const string newDirectoryPath = (directoryPath + args[0]->getString());

			if(!Tools::isDirectoryExisting(newDirectoryPath))
			{
				_throwRuntimeError("cannot delete directory");
				return true;
			}

			Tools::deleteDirectory(newDirectoryPath);

			returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:file_create")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, 2) && _validateSavesDirectory())
		{
			const auto isExported = Config::getInst().isApplicationExported();
			const auto rootPath = Tools::getRootDirectoryPath();
			const auto directoryPath = (rootPath + (isExported ? "" : ("projects\\" + _currentProjectId + "\\")) + "saves\\");
			const auto filePath = (directoryPath + args[0]->getString());

			if(Tools::isFileExisting(filePath))
			{
				_throwRuntimeError("cannot create file");
				return true;
			}

			auto file = ofstream(filePath);

			file.close();

			returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:file_delete")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types) && _validateSavesDirectory())
		{
			const auto isExported = Config::getInst().isApplicationExported();
			const auto rootPath = Tools::getRootDirectoryPath();
			const auto directoryPath = (rootPath + (isExported ? "" : ("projects\\" + _currentProjectId + "\\")) + "saves\\");
			const auto filePath = (directoryPath + args[0]->getString());

			if(!Tools::isFileExisting(filePath))
			{
				_throwRuntimeError("cannot delete file");
				return true;
			}

			Tools::deleteFile(filePath);

			returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:file_write")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, 2) && _validateSavesDirectory())
		{
			const auto isExported = Config::getInst().isApplicationExported();
			const auto rootPath = Tools::getRootDirectoryPath();
			const auto directoryPath = (rootPath + (isExported ? "" : ("projects\\" + _currentProjectId + "\\")) + "saves\\");
			const auto filePath = (directoryPath + args[0]->getString());

			auto file = ofstream(filePath, ios::app);

			if(!file)
			{
				_throwRuntimeError("cannot open file");
				return true;
			}

			if(args[1]->getType() == SVT::STRING)
			{
				file << args[1]->getString();
			}
			else if(args[1]->getType() == SVT::DECIMAL)
			{
				file << to_string(args[1]->getDecimal());
			}
			else if(args[1]->getType() == SVT::INTEGER)
			{
				file << to_string(args[1]->getInteger());
			}
			else if(args[1]->getType() == SVT::BOOLEAN)
			{
				file << (args[1]->getBoolean() ? "<true>" : "<false>");
			}

			file.close();

			returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:file_add_new_line")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types) && _validateSavesDirectory())
		{
			const auto isExported = Config::getInst().isApplicationExported();
			const auto rootPath = Tools::getRootDirectoryPath();
			const auto directoryPath = (rootPath + (isExported ? "" : ("projects\\" + _currentProjectId + "\\")) + "saves\\");
			const auto filePath = (directoryPath + args[0]->getString());

			auto file = ofstream(filePath, ios::app);

			if(!file)
			{
				_throwRuntimeError("cannot open file");
				return true;
			}

			file << endl;

			file.close();

			returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:file_clear")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types) && _validateSavesDirectory())
		{
			const auto isExported = Config::getInst().isApplicationExported();
			const auto rootPath = Tools::getRootDirectoryPath();
			const auto directoryPath = (rootPath + (isExported ? "" : ("projects\\" + _currentProjectId + "\\")) + "saves\\");
			const auto filePath = (directoryPath + args[0]->getString());

			auto file = ofstream(filePath, ios::trunc);

			if(!file)
			{
				_throwRuntimeError("cannot open file");
				return true;
			}

			file.close();

			returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
		}
	}
	else
	{
		return false;
	}

	return true;
}