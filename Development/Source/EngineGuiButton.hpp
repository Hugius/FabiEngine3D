#pragma once

#include "FabiEngine3D.hpp"
#include "EngineGuiRectangle.hpp"
#include "EngineGuiTextfield.hpp"

class EngineGuiButton
{
public:
	EngineGuiButton(FabiEngine3D& fe3d, const string& parentID, const string& ID, vec2 position, vec2 size, vec3 color, vec3 hoverColor,
		string textContent, vec3 textColor, vec3 textHoverColor, bool sizeIncreaseEnabled = true, bool colorChangeEnabled = true);

	virtual void update(float delta, bool hoverable);
	void show();
	void hide();
	void setHoverable(bool val);

	bool isHovered();

	const string& getID();
	const string& getParentID();

	shared_ptr<EngineGuiRectangle> getRectangle();
	shared_ptr<EngineGuiTextfield> getTextfield();

protected:
	FabiEngine3D& _fe3d;

	const string _ID;
	const string _parentID;

	const vec3 _hoverColor;
	const vec3 _textHoverColor;

	shared_ptr<EngineGuiRectangle> _rectangle;
	shared_ptr<EngineGuiTextfield> _textfield;

	bool _isHovered = false;
	bool _isHoverable = true;

	void _updateHovering(bool hoverable);

private:
	const bool _sizeIncreaseEnabled = true;
	const bool _colorChangeEnabled  = true;
};