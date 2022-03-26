#pragma once

#include "engine_interface.hpp"
#include "gui_quad_field.hpp"
#include "gui_text_field.hpp"

class GuiButton
{
public:
	GuiButton(shared_ptr<EngineInterface> fe3d, const string & id, const string & parentId, const fvec2 & position, const fvec2 & size, const fvec3 & defaultQuadColor, const fvec3 & hoveredQuadColor, const string & textContent, const fvec3 & defaultTextColor, const fvec3 & hoveredTextColor, bool isCentered);
	GuiButton(shared_ptr<EngineInterface> fe3d, const string & id, const string & parentId, const fvec2 & position, const fvec2 & size, const string & texturePath, const fvec3 & hoveredQuadColor, bool isCentered);

	virtual void update(bool isHoverable);
	virtual void changeTextContent(const string & content);

	void setVisible(bool value);
	void setHoverable(bool value);

	const string & getId() const;
	const string & getParentId() const;

	const bool isHoverable() const;
	const bool isHovered() const;

	const bool isVisible() const;

protected:
	void _updateHovering(bool isHoverable);

	const string _id;
	const string _parentId;
	const fvec3 _defaultQuadColor;
	const fvec3 _hoveredQuadColor;
	const fvec3 _defaultTextColor;
	const fvec3 _hoveredTextColor;

	shared_ptr<EngineInterface> _fe3d = nullptr;
	shared_ptr<GuiQuadField> _quadField = nullptr;
	shared_ptr<GuiTextField> _textField = nullptr;

	bool _isVisible = true;
	bool _isHovered = false;
	bool _isHoverable = true;

private:
	static inline constexpr float TEXT_WIDTH_MULTIPLIER = 0.9f;
	static inline constexpr float TEXT_HEIGHT_MULTIPLIER = 0.75f;
	static inline constexpr float DEFAULT_OPACITY = 1.0f;
	static inline constexpr float HOVER_OPACITY = 0.25f;
};