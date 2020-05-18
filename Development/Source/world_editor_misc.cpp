#include "world_editor.hpp"

void WorldEditor::setCurrentProjectName(string projectName)
{
	_currentProjectName = projectName;
}

bool WorldEditor::isLoaded()
{
	return _isLoaded;
}

void WorldEditor::_addValueForm(string ID, float value)
{
	_activeWritefield = ID;
	_gui->getGlobalScreen()->addWriteField(ID, vec2(0.0f), vec2(0.2f, 0.1f), vec3(0.25f), vec3(0.5f), vec3(1.0f), vec3(0.0f), 0, 1, 1, 1);
	_gui->getGlobalScreen()->getWriteField(ID)->setTextContent(std::to_string(int(value)));
	_gui->getGlobalScreen()->getWriteField(ID)->setActive(true);
	_gui->getGlobalScreen()->addButton("done", vec2(-0.15f, -0.2f), vec2(0.1f, 0.1f), vec3(0.0f, 0.5f, 0.0f), vec3(0.0f, 1.0f, 0.0f), "Done", vec3(1.0f), vec3(0.0f));
	_gui->getGlobalScreen()->addButton("cancel", vec2(0.15f, -0.2f), vec2(0.15f, 0.1f), vec3(0.5f, 0.0f, 0.0f), vec3(1.0f, 0.0f, 0.0f), "Cancel", vec3(1.0f), vec3(0.0f));

	_gui->setFocus(true);
}

void WorldEditor::_checkValueForm(string ID, float& value)
{
	if (_activeWritefield == ID)
	{
		bool done = _fe3d.input_getMousePressed(Input::MOUSE_BUTTON_LEFT) && _gui->getGlobalScreen()->getButton("done")->isHovered();
		bool cancelled = _fe3d.input_getMousePressed(Input::MOUSE_BUTTON_LEFT) && _gui->getGlobalScreen()->getButton("cancel")->isHovered();
		bool entered = _gui->getGlobalScreen()->getWriteField(_activeWritefield)->confirmedInput();
		bool escaped = _gui->getGlobalScreen()->getWriteField(_activeWritefield)->cancelledInput();

		// Check if user confirmed or cancelled
		if (done || entered || cancelled || escaped)
		{
			if (done || entered)
			{
				string content = _gui->getGlobalScreen()->getWriteField(_activeWritefield)->getTextContent();

				// Check if writefield is not empty
				if (content != "")
				{
					value = float(std::stoi(content));
					_removeValueForm();
				}
			}
			else
			{
				_removeValueForm();
			}
		}
	}
}

void WorldEditor::_removeValueForm()
{
	_gui->getGlobalScreen()->deleteWriteField(_activeWritefield);
	_gui->getGlobalScreen()->deleteButton("done");
	_gui->getGlobalScreen()->deleteButton("cancel");
	_gui->setFocus(false);
	_activeWritefield = "";
}