#include "script_interpreter.hpp"

#include <fstream>
#include <algorithm>
#include <direct.h>
#include <filesystem>

bool ScriptInterpreter::_executeFe3dMiscFunction(const string& functionName, vector<ScriptValue>& arguments, vector<ScriptValue>& returnValues)
{
	// Determine type of function
	if (functionName == "fe3d:game_pause")
	{
		if (_validateListValueAmount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			_fe3d.engine_pause();
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
		}
	}
	else if (functionName == "fe3d:game_unpause")
	{
		if (_validateListValueAmount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			_fe3d.engine_resume();
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
		}
	}
	else if (functionName == "fe3d:game_stop")
	{
		if (_validateListValueAmount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			if (_fe3d.engine_isGameExported()) // Game preview
			{
				_fe3d.engine_stop();
			}
			else // Engine preview
			{
				_gameMustStop = true;
			}
			
			// Return
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
		}
	}
	else if (functionName == "fe3d:print")
	{
		// Validate amount of arguments
		if (_validateListValueAmount(arguments, 1))
		{
			// Determine which type of value to print
			if (arguments[0].getType() == ScriptValueType::VEC3)
			{
				_fe3d.logger_throwInfo(_fe3d.misc_vec2str(arguments[0].getVec3()));
			}
			else if (arguments[0].getType() == ScriptValueType::STRING)
			{
				_fe3d.logger_throwInfo(arguments[0].getString());
			}
			else if (arguments[0].getType() == ScriptValueType::DECIMAL)
			{
				_fe3d.logger_throwInfo(arguments[0].getDecimal());
			}
			else if (arguments[0].getType() == ScriptValueType::INTEGER)
			{
				_fe3d.logger_throwInfo(arguments[0].getInteger());
			}
			else if (arguments[0].getType() == ScriptValueType::BOOLEAN)
			{
				_fe3d.logger_throwInfo(arguments[0].getBoolean() ? "true" : "false");
			}

			// Return
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
		}
	}
	else if (functionName == "fe3d:scene_load")
	{
		auto types = { ScriptValueType::STRING };

		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			_sceneEditor.clearScene();
			_sceneEditor.loadSceneFromFile(arguments[0].getString());
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
		}
	}
	else if (functionName == "fe3d:scene_clear")
	{
		if (_validateListValueAmount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			_sceneEditor.clearScene();
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
		}
	}
	else if (functionName == "fe3d:scene_get_current_id")
	{
		if (_validateListValueAmount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			auto result = _sceneEditor.getLoadedSceneID();
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::STRING, result));
		}
	}
	else if (functionName == "fe3d:cursor_show")
	{
		if (_validateListValueAmount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			_fe3d.misc_showCursor();
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
		}
	}
	else if (functionName == "fe3d:cursor_hide")
	{
		if (_validateListValueAmount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			_fe3d.misc_hideCursor();
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
		}
	}
	else if (functionName == "fe3d:cursor_get_position_x")
	{
		if (_validateListValueAmount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			auto result = _fe3d.misc_convertToNDC(_fe3d.misc_convertFromScreenCoords(_fe3d.misc_getCursorPositionRelativeToViewport())).x;
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::DECIMAL, std::clamp(result, -1.0f, 1.0f)));
		}
	}
	else if (functionName == "fe3d:cursor_get_position_y")
	{
		if (_validateListValueAmount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			auto result = _fe3d.misc_convertToNDC(_fe3d.misc_convertFromScreenCoords(_fe3d.misc_getCursorPositionRelativeToViewport())).y;
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::DECIMAL, std::clamp(result, -1.0f, 1.0f)));
		}
	}
	else if (functionName == "fe3d:window_get_width")
	{
		if (_validateListValueAmount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			auto result = _fe3d.misc_getWindowSize().x;
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::INTEGER, result));
		}
	}
	else if (functionName == "fe3d:window_get_height")
	{
		if (_validateListValueAmount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			auto result = _fe3d.misc_getWindowSize().y;
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::INTEGER, result));
		}
	}
	else if (functionName == "fe3d:timer_start")
	{
		if (_validateListValueAmount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			_fe3d.misc_startMillisecondTimer();
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
		}
	}
	else if (functionName == "fe3d:timer_stop")
	{
		if (_validateListValueAmount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			auto result = _fe3d.misc_stopMillisecondTimer();
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::DECIMAL, result));
		}
	}
	else if (functionName == "fe3d:directory_is_existing")
	{
		auto types = { ScriptValueType::STRING };

		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types) && _validateCurrentProject())
		{
			// Compose directory paths
			string directoryPath = _fe3d.misc_getRootDirectory() + (_fe3d.engine_isGameExported() ? "" : ("projects\\" + _currentProjectID)) + "\\saves\\";
			string newDirectoryPath = string(directoryPath + arguments[0].getString());

			// Return
			auto result = (_fe3d.misc_isFileExisting(newDirectoryPath) && _fe3d.misc_isDirectory(newDirectoryPath));
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::BOOLEAN, result));
		}
	}
	else if (functionName == "fe3d:directory_create")
	{
		auto types = { ScriptValueType::STRING };

		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types) && _validateCurrentProject())
		{
			// Compose directory paths
			string directoryPath = _fe3d.misc_getRootDirectory() + (_fe3d.engine_isGameExported() ? "" : ("projects\\" + _currentProjectID)) + "\\saves\\";
			string newDirectoryPath = string(directoryPath + arguments[0].getString());

			// Try to create new directory
			auto status = _mkdir(newDirectoryPath.c_str());

			// Check for error
			if (status == -1)
			{
				_throwScriptError("Cannot create directory \"" + arguments[0].getString() + "\"!");
			}

			// Return
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
		}
	}
	else if (functionName == "fe3d:directory_delete")
	{
		auto types = { ScriptValueType::STRING };

		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types) && _validateCurrentProject())
		{
			// Compose directory paths
			string directoryPath = _fe3d.misc_getRootDirectory() + (_fe3d.engine_isGameExported() ? "" : ("projects\\" + _currentProjectID)) + "\\saves\\";
			string newDirectoryPath = string(directoryPath + arguments[0].getString());

			// Check if directory exists
			if (_fe3d.misc_isFileExisting(newDirectoryPath) && _fe3d.misc_isDirectory(newDirectoryPath))
			{
				std::filesystem::remove_all(newDirectoryPath);
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
			}
			else
			{
				_throwScriptError("Cannot delete directory \"" + arguments[0].getString() + "\"!");
			}
		}
	}
	else if (functionName == "fe3d:file_is_existing")
	{
		auto types = { ScriptValueType::STRING };

		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types) && _validateCurrentProject())
		{
			// Compose file path
			string directoryPath = _fe3d.misc_getRootDirectory() + (_fe3d.engine_isGameExported() ? "" : ("projects\\" + _currentProjectID)) + "\\saves\\";
			string filePath = directoryPath + arguments[0].getString();

			// Return
			auto result = _fe3d.misc_isFileExisting(filePath);
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::BOOLEAN, result));
		}
	}
	else if (functionName == "fe3d:file_read")
	{
		auto types = { ScriptValueType::STRING };

		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types) && _validateCurrentProject())
		{
			// Compose file path
			string directoryPath = _fe3d.misc_getRootDirectory() + (_fe3d.engine_isGameExported() ? "" : ("projects\\" + _currentProjectID)) + "\\saves\\";
			string filePath = directoryPath + arguments[0].getString();

			// Check if file exists
			if (_fe3d.misc_isFileExisting(filePath))
			{
				// Open file
				std::ifstream file(filePath);
				string line;

				// Add lines to list
				while (std::getline(file, line))
				{
					returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::STRING, line));
				}

				// Close file
				file.close();
			}
			else
			{
				_throwScriptError("Cannot read from file \"" + arguments[0].getString() + "\"!");
			}
		}
	}
	else if (functionName == "fe3d:file_write")
	{
		auto types = { ScriptValueType::STRING };

		if (_validateListValueAmount(arguments, 2) && _validateCurrentProject())
		{
			// Compose file path
			string directoryPath = _fe3d.misc_getRootDirectory() + (_fe3d.engine_isGameExported() ? "" : ("projects\\" + _currentProjectID)) + "\\saves\\";
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

		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types) && _validateCurrentProject())
		{
			// Compose file path
			string directoryPath = _fe3d.misc_getRootDirectory() + (_fe3d.engine_isGameExported() ? "" : ("projects\\" + _currentProjectID)) + "\\saves\\";
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

		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types) && _validateCurrentProject())
		{
			// Compose file path
			string directoryPath = _fe3d.misc_getRootDirectory() + (_fe3d.engine_isGameExported() ? "" : ("projects\\" + _currentProjectID)) + "\\saves\\";
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
				_throwScriptError("Cannot clear file \"" + arguments[0].getString() + "\"!");
			}
		}
	}
	else if (functionName == "fe3d:file_delete")
	{
		auto types = { ScriptValueType::STRING };

		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types) && _validateCurrentProject())
		{
			// Compose file path
			string directoryPath = _fe3d.misc_getRootDirectory() + (_fe3d.engine_isGameExported() ? "" : ("projects\\" + _currentProjectID)) + "\\saves\\";
			string filePath = directoryPath + arguments[0].getString();

			// Check if file exists
			if (_fe3d.misc_isFileExisting(filePath))
			{
				auto status = std::remove(filePath.c_str());
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
			}
			else
			{
				_throwScriptError("Cannot delete file \"" + arguments[0].getString() + "\"!");
			}
		}
	}
	else
	{
		return false;
	}

	return true;
}