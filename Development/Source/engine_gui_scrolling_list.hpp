#pragma once

#include "fe3d.hpp"
#include "engine_gui_rectangle.hpp"
#include "engine_gui_button.hpp"

class EngineGuiScrollingList final : public EngineGuiRectangle
{
public:
	EngineGuiScrollingList(FabiEngine3D& fe3d, const string& parentID, const string& ID, Vec2 position, Vec2 size, Vec3 color, 
		Vec3 buttonColor, Vec3 buttonHoverColor, Vec3 textColor, Vec3 textHoverColor, Vec2 charSize);

	void update(bool isHoverable);
	void createButton(const string& ID, string textContent);
	void deleteButton(const string& ID);
	void deleteButtons();
	void setVisible(bool isVisible);

	bool isHovered();

	shared_ptr<EngineGuiButton> getButton(const string& ID);
	vector<shared_ptr<EngineGuiButton>>& getButtons();

private:
	void _updateHovering();
	void _updateButtons(bool hoverable);
	void _updateScolling();

	Vec2 _convertPosition(Vec2 position);
	Vec2 _convertSize(Vec2 size);
	
	float _scrollingOffset = 0.0f;
	float _scrollingSpeed = 0.0f;
	static inline const float SCROLL_WHEEL_DIVIDER = 100.0f;

	const Vec3 _buttonColor;
	const Vec3 _buttonHoverColor;
	const Vec3 _textColor;
	const Vec3 _textHoverColor;

	const Vec2 _charSize;

	vector<shared_ptr<EngineGuiButton>> _buttons;

	bool _isHovered = false;
};