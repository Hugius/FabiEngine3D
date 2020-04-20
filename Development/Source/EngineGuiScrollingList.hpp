#pragma once

#include "FabiEngine3D.hpp"
#include "EngineGuiRectangle.hpp"
#include "EngineGuiButton.hpp"

class EngineGuiScrollingList final : public EngineGuiRectangle
{
public:
	EngineGuiScrollingList(FabiEngine3D& fe3d, const string& parentID, const string& ID, vec2 position, vec2 size, vec3 color, 
		vec3 buttonColor, vec3 buttonHoverColor, vec3 textColor, vec3 textHoverColor, float charWidth);

	void update(float delta, bool hoverable);
	void addButton(const string& ID, string textContent);
	void deleteButton(const string& ID);
	void show();
	void hide();

	bool isHovered();

	const string& getHoveredButtonID();

private:
	void _updateHovering();
	void _updateButtons(bool hoverable);
	void _updateScolling();

	vec4 _convertDimensions(vec2 position, vec2 size);

	float _delta = 0.0f;
	float _scrollingOffset = 0.0f;
	float _scrollingSpeed = 0.0f;

	const vec3 _buttonColor;
	const vec3 _buttonHoverColor;
	const vec3 _textColor;
	const vec3 _textHoverColor;

	const float _charWidth;

	const int _maxButtonsPerPage = 13;

	vector<shared_ptr<EngineGuiButton>> _buttons;

	string _hoveredButtonID = "";

	bool _isHovered = false;
};