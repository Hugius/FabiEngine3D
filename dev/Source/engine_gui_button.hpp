#pragma once

#include "fe3d.hpp"
#include "engine_gui_rectangle.hpp"
#include "engine_gui_text_field.hpp"

class EngineGuiButton
{
public:
	EngineGuiButton(FabiEngine3D& fe3d, const string& parentID, const string& ID, Vec2 position, Vec2 size, Vec3 color, Vec3 hoverColor,
					string textContent, Vec3 textColor, Vec3 textHoverColor, bool isSizeIncreaseEnabled, bool isColorChangeEnabled, bool isCentered);
	EngineGuiButton(FabiEngine3D& fe3d, const string& parentID, const string& ID, Vec2 position, Vec2 size,
					const string& texturePath, Vec3 hoverColor, bool isSizeIncreaseEnabled, bool isColorChangeEnabled, bool isCentered);

	// Voids
	virtual void update(bool isHoverable);
	virtual void changeTextContent(const string& content);
	void setVisible(bool isVisible);
	void setHoverable(bool isHoverable);

	// Strings
	const string& getID() const;
	const string& getParentID() const;

	// Booleans
	const bool isHoverable() const;
	const bool isHovered() const;

	// Miscellaneous
	shared_ptr<EngineGuiRectangle> getRectangle() const;
	shared_ptr<EngineGuiTextField> getTextField() const;

protected:
	// Voids
	void _updateHovering(bool hoverable);

	// Strings
	const string _ID;
	const string _parentID;

	// Vectors
	const Vec3 _hoverColor;
	const Vec3 _textHoverColor;

	// Booleans
	bool _isHovered = false;
	bool _isHoverable = true;

	// Miscellaneous
	FabiEngine3D& _fe3d;
	shared_ptr<EngineGuiRectangle> _rectangle = nullptr;
	shared_ptr<EngineGuiTextField> _textField = nullptr;

private:
	// Decimals
	static inline const float TOTAL_SIZE_INCREASE = 1.125f;
	static inline const float INCREASE_MULTIPLIER = 1.005f;
	static inline const float DECREASE_MULTIPLIER = 0.995f;
	static inline const float TEXT_WIDTH_MULTIPLIER = 0.9f;
	static inline const float TEXT_HEIGHT_MULTIPLIER = 0.75f;

	// Booleans
	const bool _isSizeChangeEnabled;
	const bool _isColorChangeEnabled;
};