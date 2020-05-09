#pragma once

#include "fabi_engine_3d.hpp"
#include "engine_gui_rectangle.hpp"
#include "engine_gui_button.hpp"

class EngineGuiScrollingList final : public EngineGuiRectangle
{
public:
	EngineGuiScrollingList(FabiEngine3D& fe3d, const string& parentID, const string& ID, vec2 position, vec2 size, vec3 color, 
		vec3 buttonColor, vec3 buttonHoverColor, vec3 textColor, vec3 textHoverColor, vec2 charSize);

	void update(float delta, bool hoverable);
	void addButton(const string& ID, string textContent);
	void deleteButton(const string& ID);
	void deleteButtons();
	void show();
	void hide();

	bool isHovered();

	shared_ptr<EngineGuiButton> getButton(const string& ID);
	vector<shared_ptr<EngineGuiButton>>& getButtons();

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

	const vec2 _charSize;

	vector<shared_ptr<EngineGuiButton>> _buttons;

	bool _isHovered = false;
};