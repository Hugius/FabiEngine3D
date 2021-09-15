#pragma once

#include "fabi_engine_3d.hpp"
#include "engine_gui_rectangle.hpp"
#include "engine_gui_text_field.hpp"

class EngineGuiButton
{
public:
	EngineGuiButton(FabiEngine3D& fe3d, const string& parentID, const string& ID, Vec2 position, Vec2 size, Vec3 color, Vec3 hoverColor,
		string textContent, Vec3 textColor, Vec3 textHoverColor, bool sizeIncreaseEnabled = true, bool colorChangeEnabled = true);
	EngineGuiButton(FabiEngine3D& fe3d, const string& parentID, const string& ID, Vec2 position, Vec2 size,
		const string& texturePath, Vec3 hoverColor, bool sizeChangeEnabled = true, bool colorChangeEnabled = true);

	virtual void update(bool isHoverable);
	virtual void changeTextContent(const string& content);
	void setVisible(bool isVisible);
	void setHoverable(bool isHoverable);

	bool isHoverable();
	bool isHovered();

	const string& getID();
	const string& getParentID();

	shared_ptr<EngineGuiRectangle> getRectangle();
	shared_ptr<EngineGuiTextField> getTextField();

protected:
	FabiEngine3D& _fe3d;

	const string _ID;
	const string _parentID;

	const Vec3 _hoverColor;
	const Vec3 _textHoverColor;

	shared_ptr<EngineGuiRectangle> _rectangle = nullptr;
	shared_ptr<EngineGuiTextField> _textField = nullptr;

	bool _isHovered = false;
	bool _isHoverable = true;

	void _updateHovering(bool hoverable);

private:
	const bool _sizeChangeEnabled;
	const bool _colorChangeEnabled;

	static inline const float TOTAL_SIZE_INCREASE = 1.125f;
	static inline const float INCREASE_MULTIPLIER = 1.005f;
	static inline const float DECREASE_MULTIPLIER = 0.995f;
	static inline const float TEXT_WIDTH_MULTIPLIER = 0.9f;
	static inline const float TEXT_HEIGHT_MULTIPLIER = 0.75f;
};