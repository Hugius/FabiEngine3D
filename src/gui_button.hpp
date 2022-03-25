#pragma once

#include "engine_interface.hpp"
#include "gui_quad_field.hpp"
#include "gui_text_field.hpp"

class GuiButton
{
public:
	GuiButton(shared_ptr<EngineInterface> fe3d, const string& parentId, const string& id, const fvec2& position, const fvec2& size,
			  const fvec3& color, const fvec3& hoverColor, const string& textContent, const fvec3& textColor, const fvec3& textHoverColor, bool isCentered);
	GuiButton(shared_ptr<EngineInterface> fe3d, const string& parentId, const string& id, const fvec2& position, const fvec2& size,
			  const string& texturePath, const fvec3& hoverColor, bool isCentered);

	virtual void update(bool isHoverable);
	virtual void changeTextContent(const string& content);

	void setVisible(bool isVisible);
	void setHoverable(bool isHoverable);

	const shared_ptr<GuiQuadField> getQuadField() const;
	const shared_ptr<GuiTextField> getTextField() const;

	const string& getId() const;
	const string& getParentId() const;

	const bool isHoverable() const;
	const bool isHovered() const;

protected:
	void _updateHovering(bool isHoverable);

	const string _id;
	const string _parentId;
	const fvec3 _hoverColor;
	const fvec3 _textHoverColor;

	shared_ptr<EngineInterface> _fe3d = nullptr;
	shared_ptr<GuiQuadField> _quadField = nullptr;
	shared_ptr<GuiTextField> _textField = nullptr;

	bool _isHovered = false;
	bool _isHoverable = true;

private:
	static inline constexpr float TEXT_WIDTH_MULTIPLIER = 0.9f;
	static inline constexpr float TEXT_HEIGHT_MULTIPLIER = 0.75f;
};