#include "EngineGuiWritefield.hpp"

EngineGuiWritefield::EngineGuiWritefield(FabiEngine3D& fe3d, const string& parentID, const string& ID, vec2 position, vec2 size, vec3 color, vec3 textColor) :
	EngineGuiButton(fe3d, parentID, ID, position, size, color, "|", textColor, false, true)
{

}

void EngineGuiWritefield::update(float delta)
{
	_updateHovering();
	_updateTyping(delta);
}

void EngineGuiWritefield::_updateTyping(float delta)
{
	static float passedDelta = 0.0f;
	static bool barEnabled = true;
	
	// Check if time passed
	if (passedDelta >= 500.0f)
	{
		passedDelta = 0.0f;

		// Toggle bar animation
		barEnabled = !barEnabled;
		_fe3d.textEntity_setText(_textfield->getEntityID(), barEnabled ? "|" : " ", 0.02f);
	}
	else
	{
		passedDelta += delta;
	}
}