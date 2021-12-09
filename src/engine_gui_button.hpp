#pragma once

#include "fe3d.hpp"
#include "engine_gui_rectangle.hpp"
#include "engine_gui_text_field.hpp"

class EngineGuiButton
{
public:
	EngineGuiButton(FabiEngine3D& fe3d, const string& parentID, const string& ID, fvec2 position, fvec2 size, fvec3 color, fvec3 hoverColor,
					string textContent, fvec3 textColor, fvec3 textHoverColor, bool isSizeIncreaseEnabled, bool isColorChangeEnabled, bool isCentered);
	EngineGuiButton(FabiEngine3D& fe3d, const string& parentID, const string& ID, fvec2 position, fvec2 size,
					const string& texturePath, fvec3 hoverColor, bool isSizeIncreaseEnabled, bool isColorChangeEnabled, bool isCentered);

	// VOID
	virtual void update(bool isHoverable);
	virtual void changeTextContent(const string& content);
	void setVisible(bool isVisible);
	void setHoverable(bool isHoverable);

	// STRING
	const string& getID() const;
	const string& getParentID() const;

	// BOOL
	const bool isHoverable() const;
	const bool isHovered() const;

	// MISCELLANEOUS
	shared_ptr<EngineGuiRectangle> getRectangle() const;
	shared_ptr<EngineGuiTextField> getTextField() const;

protected:
	// VOID
	void _updateHovering(bool hoverable);

	// STRING
	const string _ID;
	const string _parentID;

	// FVEC3
	const fvec3 _hoverColor;
	const fvec3 _textHoverColor;

	// BOOL
	bool _isHovered = false;
	bool _isHoverable = true;

	// MISCELLANEOUS
	FabiEngine3D& _fe3d;
	shared_ptr<EngineGuiRectangle> _rectangle = nullptr;
	shared_ptr<EngineGuiTextField> _textField = nullptr;

private:
	// FLOAT
	static inline const float TOTAL_SIZE_INCREASE = 1.15f;
	static inline const float INCREASE_MULTIPLIER = 1.005f;
	static inline const float DECREASE_MULTIPLIER = 0.995f;
	static inline const float TEXT_WIDTH_MULTIPLIER = 0.9f;
	static inline const float TEXT_HEIGHT_MULTIPLIER = 0.75f;

	// BOOL
	const bool _isSizeChangeEnabled;
	const bool _isColorChangeEnabled;
};