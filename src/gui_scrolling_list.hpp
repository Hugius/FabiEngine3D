#pragma once

#include "engine_interface.hpp"
#include "gui_button.hpp"

class GuiScrollingList final : public GuiQuadField
{
public:
	GuiScrollingList(shared_ptr<EngineInterface> fe3d, const string& id, const string& parentId, const fvec2& position, const fvec2& size, const fvec3& color, const fvec3& buttonColor, const fvec3& buttonHoverColor, const fvec3& textColor, const fvec3& textHoverColor, const fvec2& charSize, bool isCentered);

	void update(bool isHoverable);
	void createButton(const string& id, const string& textContent);
	void deleteButton(const string& id);
	void deleteButtons();
	void setVisible(bool isVisible);

	const unordered_map<string, shared_ptr<GuiButton>>& getButtons() const;

	const shared_ptr<GuiButton> getButton(const string& id) const;

	const bool hasButton(const string& id);
	const bool isHovered() const;

private:
	void _updateHovering();
	void _updateScrolling();

	const fvec2 _convertPosition(const fvec2& position) const;
	const fvec2 _convertSize(const fvec2& size) const;

	const fvec3 _buttonColor;
	const fvec3 _buttonHoverColor;
	const fvec3 _textColor;
	const fvec3 _textHoverColor;
	const fvec2 _charSize;

	unordered_map<string, shared_ptr<GuiButton>> _buttons = {};

	float _scrollingOffset = 0.0f;

	bool _isHovered = false;
};