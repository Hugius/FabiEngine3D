#pragma once

#include "fe3d.hpp"
#include "engine_gui_rectangle.hpp"
#include "engine_gui_button.hpp"

class EngineGuiScrollingList final : public EngineGuiRectangle
{
public:
	EngineGuiScrollingList(FabiEngine3D& fe3d, const string& parentID, const string& ID, fvec2 position, fvec2 size, fvec3 color,
						   fvec3 buttonColor, fvec3 buttonHoverColor, fvec3 textColor, fvec3 textHoverColor, fvec2 charSize, bool isCentered);

	// Voids
	void update(bool isHoverable);
	void createButton(const string& ID, string textContent);
	void deleteButton(const string& ID);
	void deleteButtons();
	void setVisible(bool isVisible);

	// Booleans
	const bool isHovered() const;

	// Miscellaneous
	const vector<shared_ptr<EngineGuiButton>>& getButtons() const;
	shared_ptr<EngineGuiButton> getButton(const string& ID) const;

private:
	// Voids
	void _updateHovering();
	void _updateButtons(bool hoverable);
	void _updateScolling();

	// Vectors
	const fvec2 _convertPosition(fvec2 position) const;
	const fvec2 _convertSize(fvec2 size) const;

	// Vectors
	const fvec3 _buttonColor;
	const fvec3 _buttonHoverColor;
	const fvec3 _textColor;
	const fvec3 _textHoverColor;
	const fvec2 _charSize;

	// Decimals
	static inline const float SCROLL_WHEEL_DIVIDER = 100.0f;
	float _scrollingOffset = 0.0f;
	float _scrollingSpeed = 0.0f;

	// Booleans
	bool _isHovered = false;

	// Miscellaneous
	vector<shared_ptr<EngineGuiButton>> _buttons;
};