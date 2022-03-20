#pragma once

#include "engine_interface.hpp"
#include "gui_rectangle.hpp"
#include "gui_button.hpp"

class GuiScrollingList final : public GuiRectangle
{
public:
	GuiScrollingList(shared_ptr<EngineInterface> fe3d, const string& parentId, const string& id, const fvec2& position, const fvec2& size, const fvec3& color,
					 const fvec3& buttonColor, const fvec3& buttonHoverColor, const fvec3& textColor, const fvec3& textHoverColor, const fvec2& charSize, bool isCentered);

	void update(bool isHoverable);
	void createButton(const string& id, const string& textContent);
	void deleteButton(const string& id);
	void deleteButtons();
	void setVisible(bool isVisible);

	const vector<shared_ptr<GuiButton>>& getButtons() const;

	const bool isHovered() const;

	const shared_ptr<GuiButton> getButton(const string& id) const;

private:
	void _updateHovering();
	void _updateButtons(bool isHoverable);
	void _updateScrolling();

	static inline constexpr float SCROLL_WHEEL_DIVIDER = 100.0f;

	const fvec3 _buttonColor;
	const fvec3 _buttonHoverColor;
	const fvec3 _textColor;
	const fvec3 _textHoverColor;
	const fvec2 _convertPosition(const fvec2& position) const;
	const fvec2 _convertSize(const fvec2& size) const;
	const fvec2 _charSize;

	vector<shared_ptr<GuiButton>> _buttons = {};

	float _scrollingOffset = 0.0f;
	float _scrollingSpeed = 0.0f;

	bool _isHovered = false;
};