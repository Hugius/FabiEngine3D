#include "script_editor.hpp"

#include <sstream>

using std::istringstream;

void ScriptEditor::_reloadScriptTextDisplay(bool reloadAabbs)
{
	_fe3d.billboard_deleteAll();
	_fe3d.aabb_deleteAll();

	float lineCount = static_cast<float>(_script.getScriptFile(_currentScriptFileID)->getLineCount());
	fvec2 separatorSize = fvec2((TEXT_CHARACTER_SIZE.x / 4.0f), (lineCount * VERTICAL_LINE_OFFSET));
	fvec3 separatorPosition = SCRIPT_TEXT_STARTING_POSITION + fvec3(HORIZONTAL_LINE_OFFSET / 2.0f, -(((lineCount - 1) / 2.0f) * VERTICAL_LINE_OFFSET), 0.0f);
	_fe3d.billboard_create("separator");
	_fe3d.billboard_setPosition("separator", (separatorPosition - fvec3(0.0f, separatorSize.y / 2.0f, 0.0f)));
	_fe3d.billboard_setSize("separator", separatorSize);
	_fe3d.billboard_setColor("separator", SEPARATOR_COLOR);
	_fe3d.billboard_setBright("separator", true);

	for(unsigned int lineIndex = 0; lineIndex < lineCount; lineIndex++)
	{
		const string lineNumberID = to_string(lineIndex);
		const string lineTextID = "text_" + lineNumberID;
		const string lineNumberString = to_string(lineIndex + 1);
		const string lineTextString = _script.getScriptFile(_currentScriptFileID)->getLineText(lineIndex);
		const fvec2 lineNumberSize = fvec2(lineNumberString.size() * TEXT_CHARACTER_SIZE.x, TEXT_CHARACTER_SIZE.y);
		const fvec2 lineTextSize = fvec2(lineTextString.size() * TEXT_CHARACTER_SIZE.x, TEXT_CHARACTER_SIZE.y);
		const fvec3 lineNumberPosition = SCRIPT_TEXT_STARTING_POSITION -
			fvec3((lineNumberString.size() - 1) * (TEXT_CHARACTER_SIZE.x / 2.0f), VERTICAL_LINE_OFFSET * static_cast<float>(lineIndex), 0.0f);
		const fvec3 lineTextPosition = SCRIPT_TEXT_STARTING_POSITION +
			fvec3((lineTextString.size() - 1) * (TEXT_CHARACTER_SIZE.x / 2.0f), -VERTICAL_LINE_OFFSET * static_cast<float>(lineIndex), 0.0f) +
			fvec3(HORIZONTAL_LINE_OFFSET, 0.0f, 0.0f);

		_fe3d.billboard_create(lineNumberID);
		_fe3d.billboard_setFont(lineNumberID, FONT_PATH);
		_fe3d.billboard_setTextContent(lineNumberID, lineNumberString);
		_fe3d.billboard_setPosition(lineNumberID, (lineNumberPosition - fvec3(0.0f, lineNumberSize.y / 2.0f, 0.0f)));
		_fe3d.billboard_setSize(lineNumberID, lineNumberSize);
		_fe3d.billboard_setColor(lineNumberID, LINE_NUMBER_COLOR);
		_fe3d.billboard_setBright(lineNumberID, true);

		const fvec3 lineAabbPosition = (lineNumberPosition - fvec3(0.0f, TEXT_CHARACTER_SIZE.y / 2.0f, AABB_DEPTH));
		const fvec3 lineAabbSize = fvec3(TEXT_CHARACTER_SIZE.x * static_cast<float>(MAX_CHARACTERS_PER_LINE * 2) * 1.1f, TEXT_CHARACTER_SIZE.y, AABB_DEPTH);
		_fe3d.aabb_create(lineNumberID);
		_fe3d.aabb_setBasePosition(lineNumberID, lineAabbPosition);
		_fe3d.aabb_setBaseSize(lineNumberID, lineAabbSize);

		istringstream iss(lineTextString);
		string noWhiteSpace;
		iss >> noWhiteSpace;
		bool isComment = (noWhiteSpace.substr(0, 3) == "///");
		_fe3d.billboard_create(lineTextID);
		_fe3d.billboard_setFont(lineTextID, FONT_PATH);
		_fe3d.billboard_setTextContent(lineTextID, lineTextString);
		_fe3d.billboard_setPosition(lineTextID, (lineTextPosition - fvec3(0.0f, lineTextSize.y / 2.0f, 0.0f)));
		_fe3d.billboard_setSize(lineTextID, lineTextSize);
		_fe3d.billboard_setColor(lineTextID, (isComment ? COMMENT_TEXT_COLOR : DEFAULT_TEXT_COLOR));
		_fe3d.billboard_setBright(lineTextID, true);

		for(unsigned int charIndex = 0; charIndex < lineTextString.size(); charIndex++)
		{
			const string characterID = (lineNumberID + "_" + to_string(charIndex));
			const float characterX = (HORIZONTAL_LINE_OFFSET + (HORIZONTAL_CHARACTER_OFFSET * static_cast<float>(charIndex)));
			const fvec3 characterPosition = (SCRIPT_TEXT_STARTING_POSITION + fvec3(characterX, -VERTICAL_LINE_OFFSET * static_cast<float>(lineIndex), 0.0f));
			_fe3d.billboard_create(characterID);
			_fe3d.billboard_setPosition(characterID, (characterPosition - fvec3(0.0f, TEXT_CHARACTER_SIZE.y / 2.0f, 0.0f)));
			_fe3d.billboard_setSize(characterID, TEXT_CHARACTER_SIZE);
			_fe3d.billboard_setVisible(characterID, false);

			if(reloadAabbs)
			{
				const fvec3 characterAabbPosition = (characterPosition - fvec3(0.0f, TEXT_CHARACTER_SIZE.y / 2.0f, 0.0f));
				const fvec3 characterAabbSize = fvec3(TEXT_CHARACTER_SIZE.x, TEXT_CHARACTER_SIZE.y, AABB_DEPTH);
				_fe3d.aabb_create(characterID);
				_fe3d.aabb_setBasePosition(characterID, characterAabbPosition);
				_fe3d.aabb_setBaseSize(characterID, characterAabbSize);
			}
		}
	}
}

void ScriptEditor::_copySelectedText()
{
	if(_firstSelectedLineIndex != -1) // Check if anything is selected at all
	{
		_copyClipboard.clear(); // Clear last copy

		if(_lastSelectedLineIndex == -1) // Check if only 1 line selected
		{
			_copyClipboard.push_back(_script.getScriptFile(_currentScriptFileID)->getLineText(_firstSelectedLineIndex));
		}
		else // If multiple selected lines
		{
			for(int i = ((_firstSelectedLineIndex > _lastSelectedLineIndex) ? _lastSelectedLineIndex : _firstSelectedLineIndex);
				i <= ((_firstSelectedLineIndex > _lastSelectedLineIndex) ? _firstSelectedLineIndex : _lastSelectedLineIndex); i++)
			{
				_copyClipboard.push_back(_script.getScriptFile(_currentScriptFileID)->getLineText(i)); // Copy text lines
			}
		}
	}
}

ScriptExecutor& ScriptEditor::getScriptExecutor()
{
	return _scriptExecutor;
}

void ScriptEditor::setCurrentProjectID(const string& projectID)
{
	_currentProjectID = projectID;
	_scriptExecutor.setCurrentProjectID(projectID);
}

const bool ScriptEditor::isLoaded() const
{
	return _isEditorLoaded;
}

const bool ScriptEditor::isWritingScript() const
{
	return !_currentScriptFileID.empty();
}