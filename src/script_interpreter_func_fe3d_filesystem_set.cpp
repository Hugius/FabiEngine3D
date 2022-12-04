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
	if(functionName == "fe3d:file_write")
	{
		if(_validateArgumentCount(args, 2))
		{
			if(args[0]->getString().find('/') != string::npos ||
			   args[0]->getString().find('\\') != string::npos)
			{
				_throwRuntimeError("path cannot contain '/' or '\\'");
			}

			if(_validateSavesDirectory())
			{
				const auto isExported = Tools::isApplicationExported();
				const auto rootPath = Tools::getRootDirectoryPath();
				const auto directoryPath = (rootPath + (isExported ? "" : ("projects\\" + _currentProjectId + "\\")) + "saves\\");
				const auto filePath = (directoryPath + args[0]->getString() + ".fe3d");

				auto file = ofstream(filePath, ios::app);

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
	else if(functionName == "fe3d:file_copy")
	{
		const auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(args[0]->getString().find('/') != string::npos ||
			   args[0]->getString().find('\\') != string::npos ||
			   args[1]->getString().find('/') != string::npos ||
			   args[1]->getString().find('\\') != string::npos)
			{
				_throwRuntimeError("paths cannot contain '/' or '\\'");
			}

			if(_validateSavesDirectory())
			{
				const auto isExported = Tools::isApplicationExported();
				const auto rootPath = Tools::getRootDirectoryPath();
				const auto directoryPath = (rootPath + (isExported ? "" : ("projects\\" + _currentProjectId + "\\")) + "saves\\");
				const auto fromFilePath = (directoryPath + args[0]->getString() + ".fe3d");
				const auto toFilePath = (directoryPath + args[1]->getString() + ".fe3d");

				if(!Tools::isFileExisting(fromFilePath) || !Tools::copyFile(fromFilePath, toFilePath))
				{
					_throwRuntimeError("cannot copy file");

					return true;
				}

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:file_rename")
	{
		const auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(args[0]->getString().find('/') != string::npos ||
			   args[0]->getString().find('\\') != string::npos ||
			   args[1]->getString().find('/') != string::npos ||
			   args[1]->getString().find('\\') != string::npos)
			{
				_throwRuntimeError("paths cannot contain '/' or '\\'");
			}

			if(_validateSavesDirectory())
			{
				const auto isExported = Tools::isApplicationExported();
				const auto rootPath = Tools::getRootDirectoryPath();
				const auto directoryPath = (rootPath + (isExported ? "" : ("projects\\" + _currentProjectId + "\\")) + "saves\\");
				const auto oldFilePath = (directoryPath + args[0]->getString() + ".fe3d");
				const auto newFilePath = (directoryPath + args[1]->getString() + ".fe3d");

				if(!Tools::isFileExisting(oldFilePath) || !Tools::renameFile(oldFilePath, newFilePath))
				{
					_throwRuntimeError("cannot rename file");

					return true;
				}

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:file_delete")
	{
		const auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(args[0]->getString().find('/') != string::npos ||
			   args[0]->getString().find('\\') != string::npos)
			{
				_throwRuntimeError("path cannot contain '/' or '\\'");
			}

			if(_validateSavesDirectory())
			{
				const auto isExported = Tools::isApplicationExported();
				const auto rootPath = Tools::getRootDirectoryPath();
				const auto directoryPath = (rootPath + (isExported ? "" : ("projects\\" + _currentProjectId + "\\")) + "saves\\");
				const auto filePath = (directoryPath + args[0]->getString() + ".fe3d");

				if(!Tools::isFileExisting(filePath) || !Tools::deleteFile(filePath))
				{
					_throwRuntimeError("cannot delete file");

					return true;
				}

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