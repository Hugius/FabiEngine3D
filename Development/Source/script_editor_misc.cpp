#include "script_editor.hpp"

void ScriptEditor::_unloadScript()
{
	_script = nullptr;
	_scriptExecutor = nullptr;
}

void ScriptEditor::_reloadLineNumbersDisplay()
{
	// Generation values
	const vec3 startingPos = vec3(-11.0f, 5.5f, 0.5f);
	const vec3 color = vec3(0.0f, 1.0f, 0.0f);
	const float charWidth = 0.25f;
	const float charHeight = 0.75f;
	const float yOffset = 1.0f;

	// Create a billboard for every line number
	for (unsigned int lineIndex = 0; lineIndex < _script->getScriptFile(_currentScriptFileID)->getLineCount(); lineIndex++)
	{
		// Generation values
		string ID = to_string(lineIndex);
		string textContent = to_string(lineIndex + 1);
		vec3 position = startingPos - vec3((textContent.size() - 1) * (charWidth / 2.0f), yOffset * static_cast<float>(lineIndex), 0.0f);
		vec2 size = vec2(textContent.size() * charWidth, charHeight);

		// Delete old billboard
		if (_fe3d.billboardEntity_isExisting(ID))
		{
			_fe3d.billboardEntity_delete(ID);
		}

		// Create new billboard
		_fe3d.billBoardEntity_add(ID, textContent, _fontPath, color, position, vec3(0.0f), size, 0, 0);
	}
}

void ScriptEditor::_reloadScriptTextDisplay()
{
	// Loop over every scriptline
	for (unsigned int lineIndex = 0; lineIndex < _script->getScriptFile(_currentScriptFileID)->getLineCount(); lineIndex++)
	{
		// Retrieve line text
		string textContent = _script->getScriptFile(_currentScriptFileID)->getLineText(lineIndex);
	
		// Generation values
		vec3 color = vec3(1.0f);
		vec3 linePosition = _fe3d.billboardEntity_getPosition(to_string(lineIndex));
		const float charWidth = 0.25f;
		const float charHeight = 0.75f;
		float xOffset = 0.25f;
		float lineOffset = 0.5f;

		// Loop over every character
		for (unsigned int charIndex = 0; charIndex < textContent.size(); charIndex++)
		{
			// Generation values
			string ID = to_string(lineIndex) + "_" + to_string(charIndex);
			string charContent = string(1, textContent[charIndex]);
			vec3 position = linePosition + vec3(lineOffset + (xOffset * static_cast<float>(charIndex)), 0.0f, 0.0f);
			vec2 size = vec2(charWidth, charHeight);

			// Delete old billboard
			if (_fe3d.billboardEntity_isExisting(ID))
			{
				_fe3d.billboardEntity_delete(ID);
			}

			// Create new billboard
			_fe3d.billBoardEntity_add(ID, charContent, _fontPath, color, position, vec3(0.0f), size, 0, 0);
		}
	}
}

shared_ptr<ScriptExecutor> ScriptEditor::getScriptExecutor()
{
	// Check if script is loaded yet
	if (_scriptExecutor == nullptr)
	{
		_loadScriptFromFile();
	}
	
	return _scriptExecutor;
}

void ScriptEditor::setCurrentProjectName(const string& projectName)
{
	_currentProjectName = projectName;
}

bool ScriptEditor::isLoaded()
{
	return _isLoaded;
}