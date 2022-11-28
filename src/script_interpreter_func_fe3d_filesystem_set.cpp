#include "script_interpreter.hpp"
#include "tools.hpp"

#include <fstream>
#include <direct.h>
#include <filesystem>

using std::endl;
using std::ios;
using std::ofstream;

using SVT = ScriptValueType;

const bool ScriptInterpreter::_executeFe3dFilesystemSetter(const string & functionName, const vector<shared_ptr<ScriptValue>> & args, vector<shared_ptr<ScriptValue>> & returnValues)
{
	if(functionName == "fe3d:directory_create")
	{
		const auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateSavesDirectory())
			{
				const auto isExported = Tools::isApplicationExported();
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
	}
	else if(functionName == "fe3d:directory_delete")
	{
		const auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateSavesDirectory())
			{
				const auto isExported = Tools::isApplicationExported();
				const auto rootPath = Tools::getRootDirectoryPath();
				const auto directoryPath = (rootPath + (isExported ? "" : ("projects\\" + _currentProjectId + "\\")) + "saves\\");
				const auto newDirectoryPath = (directoryPath + args[0]->getString());

				if(!Tools::deleteDirectory(newDirectoryPath))
				{
					_throwRuntimeError("cannot delete directory");

					return true;
				}

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:file_create")
	{
		const auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateSavesDirectory())
			{
				const auto isExported = Tools::isApplicationExported();
				const auto rootPath = Tools::getRootDirectoryPath();
				const auto directoryPath = (rootPath + (isExported ? "" : ("projects\\" + _currentProjectId + "\\")) + "saves\\");
				const auto filePath = (directoryPath + args[0]->getString() + ".fe3d");

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
	}
	else if(functionName == "fe3d:file_delete")
	{
		const auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateSavesDirectory())
			{
				const auto isExported = Tools::isApplicationExported();
				const auto rootPath = Tools::getRootDirectoryPath();
				const auto directoryPath = (rootPath + (isExported ? "" : ("projects\\" + _currentProjectId + "\\")) + "saves\\");
				const auto filePath = (directoryPath + args[0]->getString() + ".fe3d");

				if(!Tools::deleteFile(filePath))
				{
					_throwRuntimeError("cannot delete file");

					return true;
				}

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:file_write")
	{
		if(_validateArgumentCount(args, 2))
		{
			if(_validateSavesDirectory())
			{
				const auto isExported = Tools::isApplicationExported();
				const auto rootPath = Tools::getRootDirectoryPath();
				const auto directoryPath = (rootPath + (isExported ? "" : ("projects\\" + _currentProjectId + "\\")) + "saves\\");
				const auto filePath = (directoryPath + args[0]->getString() + ".fe3d");

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

				file << endl;

				file.close();

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:file_clear")
	{
		const auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateSavesDirectory())
			{
				const auto isExported = Tools::isApplicationExported();
				const auto rootPath = Tools::getRootDirectoryPath();
				const auto directoryPath = (rootPath + (isExported ? "" : ("projects\\" + _currentProjectId + "\\")) + "saves\\");
				const auto filePath = (directoryPath + args[0]->getString() + ".fe3d");

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
	}
	else
	{
		return false;
	}

	return true;
}