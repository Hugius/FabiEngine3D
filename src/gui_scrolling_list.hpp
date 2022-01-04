#pragma once

#include "fe3d.hpp"
#include "gui_rectangle.hpp"
#include "gui_button.hpp"

class GuiScrollingList final : public GuiRectangle
{
public:
	GuiScrollingList(FabiEngine3D& fe3d, const string& parentID, const string& ID, fvec2 position, fvec2 size, fvec3 color,
					 fvec3 buttonColor, fvec3 buttonHoverColor, fvec3 textColor, fvec3 textHoverColor, fvec2 charSize, bool isCentered);

	void update(bool isHoverable);
	void createButton(const string& ID, string textContent);
	void deleteButton(const string& ID);
	void deleteButtons();
	void setVisible(bool isVisible);

	const bool isHovered() const;

	const vector<shared_ptr<GuiButton>>& getButtons() const;
	shared_ptr<GuiButton> getButton(const string& ID) const;

private:
	void _updateHovering();
	void _updateButtons(bool hoverable);
	void _updateScrolling();

	const fvec3 _buttonColor;
	const fvec3 _buttonHoverColor;
	const fvec3 _textColor;
	const fvec3 _textHoverColor;

	const fvec2 _convertPosition(fvec2 position) const;
	const fvec2 _convertSize(fvec2 size) const;

	const fvec2 _charSize;

	static inline const float SCROLL_WHEEL_DIVIDER = 100.0f;
	float _scrollingOffset = 0.0f;
	float _scrollingSpeed = 0.0f;

	bool _isHovered = false;

	vector<shared_ptr<GuiButton>> _buttons;
};