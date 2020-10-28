#include "script_editor.hpp"

void ScriptEditor::_reloadScriptTextDisplay()
{
	if (_isLoaded)
	{
		// Remove all existing billboards & their respective AABBs
		_fe3d.billboardEntity_deleteAll();
		_fe3d.aabbEntity_deleteAll();

		// Create a billboard for every line number
		for (unsigned int lineIndex = 0; lineIndex < _script.getScriptFile(_currentScriptFileID)->getLineCount(); lineIndex++)
		{
			// Generation values
			string newID = to_string(lineIndex);
			string textContent = to_string(lineIndex + 1);
			vec3 billboardPosition = _scriptTextStartingPosition - 
				vec3((textContent.size() - 1) * (_textCharacterSize.x / 2.0f), _verticalLineOffset * static_cast<float>(lineIndex), 0.0f);
			vec2 billboardSize = vec2(textContent.size() * _textCharacterSize.x, _textCharacterSize.y);

			// Create new billboard
			_fe3d.billBoardEntity_add(newID, textContent, _fontPath, _lineNumberColor, billboardPosition, vec3(0.0f), billboardSize, 0, 0);
			vec3 aabbPosition = billboardPosition - vec3(0.0f, _textCharacterSize.y / 2.0f, 0.0f);
			vec3 aabbSize = vec3(_textCharacterSize.x * static_cast<float>(_maxCharactersPerLine * 2), _textCharacterSize.y, 0.05f);
			_fe3d.aabbEntity_add(newID, aabbPosition, aabbSize, true);
		}

		// Create a billboard for every character in every scriptline
		for (unsigned int lineIndex = 0; lineIndex < _script.getScriptFile(_currentScriptFileID)->getLineCount(); lineIndex++)
		{
			// Retrieve line text
			string textContent = _script.getScriptFile(_currentScriptFileID)->getLineText(lineIndex);

			// Generation values
			const vec3 linePosition = _fe3d.billboardEntity_getPosition(to_string(lineIndex));
			
			// Loop over every character
			for (unsigned int charIndex = 0; charIndex < textContent.size(); charIndex++)
			{
				// Generation values
				string newID = to_string(lineIndex) + "_" + to_string(charIndex);
				string charContent = string(1, textContent[charIndex]);
				vec3 position = linePosition + vec3(_horizontalLineOffset + (_horizontalCharacterOffset * static_cast<float>(charIndex)), 0.0f, 0.0f);

				// Create new billboard
				_fe3d.billBoardEntity_add(newID, charContent, _fontPath, _characterColor, position, vec3(0.0f), _textCharacterSize, 0, 0);
				_fe3d.aabbEntity_bindToBillboardEntity(newID, true);
			}
		}
	}
}

ScriptExecutor& ScriptEditor::getScriptExecutor()
{
	// Check if script is loaded yet
	if (!_isScriptLoadedFromFile)
	{
		_loadScriptsFromFile();
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