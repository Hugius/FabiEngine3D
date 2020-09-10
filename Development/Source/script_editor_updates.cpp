#include "script_editor.hpp"

void ScriptEditor::update()
{
	// Update header visibility
	for (int i = 0; i < static_cast<int>(Header::TOTAL); i++)
	{
		if (i <= static_cast<int>(_currentHeader))
		{
			_fe3d.gameEntity_show(std::to_string(i));
		}
		else
		{
			_fe3d.gameEntity_hide(std::to_string(i));
		}
	}
}