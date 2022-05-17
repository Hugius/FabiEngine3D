#include "script_interpreter.hpp"
#include "tools.hpp"
#include "configuration.hpp"

using SVT = ScriptValueType;

const bool ScriptInterpreter::_executeFe3dWorldSetter(const string & functionName, const vector<shared_ptr<ScriptValue>> & args, vector<shared_ptr<ScriptValue>> & returnValues)
{
	if(functionName == "fe3d:world_load_editor")
	{
		const auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(!_worldEditor->getLoadedWorldId().empty() || !_customWorldBuilder->getLoadedWorldId().empty())
			{
				_throwRuntimeError("there is already a world loaded");

				return true;
			}

			if(!_worldEditor->loadWorldFromFile(args[0]->getString()))
			{
				_throwRuntimeError("cannot load world");

				return true;
			}

			returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:world_clear_editor")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			if(!_worldEditor->getLoadedWorldId().empty())
			{
				_throwRuntimeError("no editor world is loaded");

				return true;
			}

			_worldEditor->clearLoadedWorld();

			returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:world_reset_custom_build")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			_customWorldBuilder->resetWorldBuild();

			returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:world_add_custom_sky")
	{
		const auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_customWorldBuilder->isSkyAdded(args[0]->getString()))
			{
				_throwRuntimeError("sky already added");

				return true;
			}

			_customWorldBuilder->addSky(args[0]->getString());

			returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:world_add_custom_terrain")
	{
		const auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_customWorldBuilder->isTerrainAdded(args[0]->getString()))
			{
				_throwRuntimeError("terrain already added");

				return true;
			}

			_customWorldBuilder->addTerrain(args[0]->getString());

			returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:world_add_custom_water")
	{
		const auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_customWorldBuilder->isWaterAdded(args[0]->getString()))
			{
				_throwRuntimeError("water already added");

				return true;
			}

			_customWorldBuilder->addWater(args[0]->getString());

			returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:world_add_custom_model")
	{
		const auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_customWorldBuilder->isModelAdded(args[0]->getString()))
			{
				_throwRuntimeError("model already added");

				return true;
			}

			_customWorldBuilder->addModel(args[0]->getString());

			returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:world_add_custom_quad3d")
	{
		const auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_customWorldBuilder->isQuad3dAdded(args[0]->getString()))
			{
				_throwRuntimeError("quad3D already added");

				return true;
			}

			_customWorldBuilder->addQuad3d(args[0]->getString());

			returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:world_add_custom_text3d")
	{
		const auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_customWorldBuilder->isText3dAdded(args[0]->getString()))
			{
				_throwRuntimeError("text3D already added");

				return true;
			}

			_customWorldBuilder->addText3d(args[0]->getString());

			returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:world_add_custom_aabb")
	{
		const auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_customWorldBuilder->isAabbAdded(args[0]->getString()))
			{
				_throwRuntimeError("AABB already added");

				return true;
			}

			_customWorldBuilder->addAabb(args[0]->getString());

			returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:world_add_custom_pointlight")
	{
		const auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_customWorldBuilder->isPointlightAdded(args[0]->getString()))
			{
				_throwRuntimeError("pointlight already added");

				return true;
			}

			_customWorldBuilder->addPointlight(args[0]->getString());

			returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:world_add_custom_spotlight")
	{
		const auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_customWorldBuilder->isSpotlightAdded(args[0]->getString()))
			{
				_throwRuntimeError("spotlight already added");

				return true;
			}

			_customWorldBuilder->addSpotlight(args[0]->getString());

			returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:world_add_custom_captor")
	{
		const auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_customWorldBuilder->isCaptorAdded(args[0]->getString()))
			{
				_throwRuntimeError("captor already added");

				return true;
			}

			_customWorldBuilder->addCaptor(args[0]->getString());

			returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:world_add_custom_sound3d")
	{
		const auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_customWorldBuilder->isSound3dAdded(args[0]->getString()))
			{
				_throwRuntimeError("sound3D already added");

				return true;
			}

			_customWorldBuilder->addSound3d(args[0]->getString());

			returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:world_add_custom_graphics")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			if(_customWorldBuilder->isGraphicsAdded())
			{
				_throwRuntimeError("graphics already added");

				return true;
			}

			_customWorldBuilder->addGraphics();

			returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:world_save_custom")
	{
		const auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			_customWorldBuilder->saveWorldToFile(args[0]->getString());

			returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:world_load_custom")
	{
		const auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(!_worldEditor->getLoadedWorldId().empty() || !_customWorldBuilder->getLoadedWorldId().empty())
			{
				_throwRuntimeError("there is already a world loaded");

				return true;
			}

			if(!_customWorldBuilder->loadWorldFromFile(args[0]->getString()))
			{
				_throwRuntimeError("cannot load world");

				return true;
			}

			returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:world_clear_custom")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			if(!_customWorldBuilder->getLoadedWorldId().empty())
			{
				_throwRuntimeError("no custom world is loaded");

				return true;
			}

			_customWorldBuilder->clearLoadedWorld();

			returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:world_delete_custom")
	{
		const auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			const auto isExported = Configuration::getInst().isApplicationExported();
			const auto rootPath = Tools::getRootDirectoryPath();
			const auto directoryPath = (rootPath + (isExported ? "" : ("projects\\" + _currentProjectId + "\\")) + "worlds\\custom\\");
			const auto filePath = (directoryPath + args[0]->getString() + ".fe3d");

			if(!Tools::deleteFile(filePath))
			{
				_throwRuntimeError("cannot delete custom world");

				return true;
			}

			returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
		}
	}
	else
	{
		return false;
	}

	if(_fe3d->server_isRunning())
	{
		_throwRuntimeError("cannot access `fe3d:world` functionality as a networking server");

		return true;
	}

	return true;
}