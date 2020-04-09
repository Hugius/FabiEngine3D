#pragma once

#include "FabiEngine3D.hpp"
#include "EngineGuiRectangle.hpp"
#include "EngineGuiTextfield.hpp"

class EngineGuiButton
{
public:
	EngineGuiButton(FabiEngine3D& fe3d, const string& parentID, const string& ID, vec2 position, vec2 size, vec3 color, string textContent, vec3 textColor);
	
	void update();

	bool isHovered();

	const string& getID();
	const string& getParentID();

	EngineGuiRectangle& getRectangle();
	EngineGuiTextfield& getText();

private:
	FabiEngine3D& _fe3d;

	const string _ID;
	const string _parentID;

	EngineGuiRectangle _rectangle;
	EngineGuiTextfield _textfield;

	bool _isHovered = false;
};