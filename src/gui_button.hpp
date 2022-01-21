#pragma once

#include "engine_interface.hpp"
#include "gui_rectangle.hpp"
#include "gui_text_field.hpp"

class GuiButton
{
public:
	GuiButton(shared_ptr<EngineInterface> fe3d, const string& parentID, const string& ID, const fvec2& position, const fvec2& size, const fvec3& color, const fvec3& hoverColor,
			  string textContent, const fvec3& textColor, const fvec3& textHoverColor, bool isCentered);
	GuiButton(shared_ptr<EngineInterface> fe3d, const string& parentID, const string& ID, const fvec2& position, const fvec2& size,
			  const string& texturePath, const fvec3& hoverColor, bool isCentered);

	virtual void update(bool isHoverable);
	virtual void changeTextContent(const string& content);
	void setVisible(bool isVisible);
	void setHoverable(bool isHoverable);

	const string& getID() const;
	const string& getParentID() const;

	const bool isHoverable() const;
	const bool isHovered() const;

	shared_ptr<GuiRectangle> getRectangle() const;
	shared_ptr<GuiTextField> getTextField() const;

protected:
	void _updateHovering(bool isHoverable);

	const string _ID;
	const string _parentID;

	const fvec3 _hoverColor;
	const fvec3 _textHoverColor;

	bool _isHovered = false;
	bool _isHoverable = true;

	shared_ptr<EngineInterface> _fe3d = nullptr;
	shared_ptr<GuiRectangle> _rectangle = nullptr;
	shared_ptr<GuiTextField> _textField = nullptr;

private:
	static inline const float TOTAL_SIZE_INCREASE = 1.15f;
	static inline const float INCREASE_MULTIPLIER = 1.005f;
	static inline const float DECREASE_MULTIPLIER = 0.995f;
	static inline const float TEXT_WIDTH_MULTIPLIER = 0.9f;
	static inline const float TEXT_HEIGHT_MULTIPLIER = 0.75f;
};