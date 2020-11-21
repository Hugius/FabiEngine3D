#pragma once

#include "fabi_engine_3d.hpp"
#include "engine_gui_rectangle.hpp"
#include "engine_gui_textfield.hpp"

class EngineGuiButton
{
public:
	EngineGuiButton(FabiEngine3D& fe3d, const string& parentID, const string& ID, Vec2 position, Vec2 size, Vec3 color, Vec3 hoverColor,
		string textContent, Vec3 textColor, Vec3 textHoverColor, bool sizeIncreaseEnabled = true, bool colorChangeEnabled = true);
	EngineGuiButton(FabiEngine3D& fe3d, const string& parentID, const string& ID, Vec2 position, Vec2 size,
		const string& textureName, Vec3 hoverColor, bool sizeIncreaseEnabled = true, bool colorChangeEnabled = true);

	virtual void update(bool hoverable);
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

	const Vec3 _hoverColor;
	const Vec3 _textHoverColor;

	shared_ptr<EngineGuiRectangle> _rectangle = nullptr;
	shared_ptr<EngineGuiTextfield> _textfield = nullptr;

	bool _isHovered = false;
	bool _isHoverable = true;

	void _updateHovering(bool hoverable);

private:
	const bool _sizeIncreaseEnabled = true;
	const bool _colorChangeEnabled  = true;

	const float _totalSizeIncrease = 1.1f;
	const float _increaseFactor = 1.003f;
	const float _decreaseFactor = 0.997f;
};