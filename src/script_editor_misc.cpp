#include "script_editor.hpp"

#include <sstream>

using std::istringstream;

void ScriptEditor::_reloadScriptTextDisplay(bool mustLoadAabbs)
{
	const auto lineCount = _script->getScriptFile(_currentScriptFileId)->getLineCount();

	for(const auto& id : _fe3d->quad3d_getIds())
	{
		_fe3d->quad3d_delete(id);
	}
	for(const auto& id : _fe3d->text3d_getIds())
	{
		_fe3d->text3d_delete(id);
	}
	for(const auto& id : _fe3d->aabb_getIds())
	{
		_fe3d->aabb_delete(id);
	}

	const auto separatorPosition = (TEXT_STARTING_POSITION + fvec3(HORIZONTAL_LINE_OFFSET * 0.5f, -(((static_cast<float>(lineCount) - 1) * 0.5f) * VERTICAL_LINE_OFFSET), 0.0f));
	const auto separatorSize = fvec2((TEXT_CHARACTER_SIZE.x * 0.25f), (static_cast<float>(lineCount) * VERTICAL_LINE_OFFSET));

	_fe3d->quad3d_create("separator", false);
	_fe3d->quad3d_setPosition("separator", (separatorPosition - fvec3(0.0f, separatorSize.y * 0.5f, 0.0f)));
	_fe3d->quad3d_setSize("separator", separatorSize);
	_fe3d->quad3d_setColor("separator", SEPARATOR_COLOR);
	_fe3d->quad3d_setBright("separator", true);

	for(unsigned int lineIndex = 0; lineIndex < lineCount; lineIndex++)
	{
		const auto lineNumberId = ("number_" + to_string(lineIndex));
		const auto lineNumberString = to_string(lineIndex + 1);
		const auto lineNumberOffset = -fvec3((lineNumberString.size() - 1) * (TEXT_CHARACTER_SIZE.x * 0.5f), VERTICAL_LINE_OFFSET * static_cast<float>(lineIndex), 0.0f);
		const auto lineNumberPosition = (TEXT_STARTING_POSITION + lineNumberOffset);
		const auto lineNumberSize = fvec2((lineNumberString.size() * TEXT_CHARACTER_SIZE.x), TEXT_CHARACTER_SIZE.y);

		_fe3d->text3d_create(lineNumberId, FONT_MAP_PATH, false);
		_fe3d->text3d_setMinTextureAlpha(lineNumberId, 0.05f);
		_fe3d->text3d_setContent(lineNumberId, lineNumberString);
		_fe3d->text3d_setPosition(lineNumberId, (lineNumberPosition - fvec3(0.0f, (lineNumberSize.y * 0.5f), 0.0f)));
		_fe3d->text3d_setSize(lineNumberId, lineNumberSize);
		_fe3d->text3d_setColor(lineNumberId, LINE_NUMBER_COLOR);
		_fe3d->text3d_setBright(lineNumberId, true);

		const auto lineTextId = ("text_" + to_string(lineIndex));
		const auto lineTextString = _script->getScriptFile(_currentScriptFileId)->getLineText(lineIndex);
		const auto lineTextOffset = fvec3((((lineTextString.size() - 1) * (TEXT_CHARACTER_SIZE.x * 0.5f)) + HORIZONTAL_LINE_OFFSET), (-VERTICAL_LINE_OFFSET * static_cast<float>(lineIndex)), 0.0f);
		const auto lineTextPosition = (TEXT_STARTING_POSITION + lineTextOffset);
		const auto lineTextSize = fvec2(lineTextString.size() * TEXT_CHARACTER_SIZE.x, TEXT_CHARACTER_SIZE.y);

		istringstream iss(lineTextString);
		string noWhiteSpace;
		iss >> noWhiteSpace;
		const auto isComment = (noWhiteSpace.substr(0, 3) == "///");

		_fe3d->text3d_create(lineTextId, FONT_MAP_PATH, false);
		_fe3d->text3d_setMinTextureAlpha(lineTextId, 0.05f);
		_fe3d->text3d_setContent(lineTextId, lineTextString);
		_fe3d->text3d_setPosition(lineTextId, (lineTextPosition - fvec3(0.0f, (lineTextSize.y * 0.5f), 0.0f)));
		_fe3d->text3d_setSize(lineTextId, lineTextSize);
		_fe3d->text3d_setColor(lineTextId, (isComment ? COMMENT_TEXT_COLOR : DEFAULT_TEXT_COLOR));
		_fe3d->text3d_setBright(lineTextId, true);

		const auto lineAabbId = to_string(lineIndex);
		const auto lineAabbOffset = -fvec3(0.0f, (TEXT_CHARACTER_SIZE.y * 0.5f), AABB_DEPTH);
		const auto lineAabbPosition = (lineNumberPosition + lineAabbOffset);
		const auto lineAabbSize = fvec3(TEXT_CHARACTER_SIZE.x * static_cast<float>(MAX_CHARACTERS_PER_LINE * 2) * 1.1f, TEXT_CHARACTER_SIZE.y, AABB_DEPTH);

		_fe3d->aabb_create(lineAabbId, false);
		_fe3d->aabb_setBasePosition(lineAabbId, lineAabbPosition);
		_fe3d->aabb_setBaseSize(lineAabbId, lineAabbSize);

		for(unsigned int charIndex = 0; charIndex < lineTextString.size(); charIndex++)
		{
			const auto characterId = (to_string(lineIndex) + "_" + to_string(charIndex));
			const auto characterOffset = fvec3(((HORIZONTAL_CHARACTER_OFFSET * static_cast<float>(charIndex)) + HORIZONTAL_LINE_OFFSET), (-VERTICAL_LINE_OFFSET * static_cast<float>(lineIndex)), 0.0f);
			const auto characterPosition = (TEXT_STARTING_POSITION + characterOffset);
			const auto characterAabbOffset = -fvec3(0.0f, (TEXT_CHARACTER_SIZE.y * 0.5f), 0.0f);
			const auto characterAabbPosition = (characterPosition + characterAabbOffset);
			const auto characterAabbSize = fvec3(TEXT_CHARACTER_SIZE.x, TEXT_CHARACTER_SIZE.y, AABB_DEPTH);

			_fe3d->aabb_create(characterId, false);
			_fe3d->aabb_setBasePosition(characterId, characterAabbPosition);
			_fe3d->aabb_setBaseSize(characterId, characterAabbSize);
		}
	}
}

void ScriptEditor::_copySelectedText()
{
	if(_firstSelectedLineIndex != -1)
	{
		_copyClipboard.clear();

		if(_lastSelectedLineIndex == -1)
		{
			_copyClipboard.push_back(_script->getScriptFile(_currentScriptFileId)->getLineText(_firstSelectedLineIndex));
		}
		else
		{
			for(int index = ((_firstSelectedLineIndex > _lastSelectedLineIndex) ? _lastSelectedLineIndex : _firstSelectedLineIndex);
				index <= ((_firstSelectedLineIndex > _lastSelectedLineIndex) ? _firstSelectedLineIndex : _lastSelectedLineIndex); index++)
			{
				_copyClipboard.push_back(_script->getScriptFile(_currentScriptFileId)->getLineText(index));
			}
		}
	}
}

void ScriptEditor::inject(shared_ptr<Script> script)
{
	_script = script;
}

const bool ScriptEditor::isWritingScript() const
{
	return !_currentScriptFileId.empty();
}