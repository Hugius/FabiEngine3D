#pragma once

#include "FabiEngine3D.hpp"
#include "EngineGuiButton.hpp"

class EngineGuiScreen
{
public:
	EngineGuiScreen(FabiEngine3D& fe3d, const string& parentID, const string& ID, vec2 position, vec2 size);

	void update();

	const string& getID();
	const string& getParentID();

	void addButton(const string& ID, vec2 position, vec2 size, vec3 color, string textContent, vec3 textColor);
	void addRectangle(const string& ID, vec2 position, vec2 size, vec3 color);
	void addTextfield(const string& ID, vec2 position, vec2 size, string textContent, vec3 textColor);

	vector<EngineGuiButton>& getButtons();

	const string& getHoveredButtonID();

private:
	FabiEngine3D& _fe3d;

	string _hoveredButtonID = "";

	vec2 _parentPosition;
	vec2 _parentSize;

	const string _ID;
	const string _parentID;

	vector<EngineGuiButton> _buttons;
	vector<EngineGuiRectangle> _rectangles;
	vector<EngineGuiTextfield> _textfields;

	vec4 _convertDimensions(vec2 position, vec2 size);
	bool _isHovered(const string& ID);
};