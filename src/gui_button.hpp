#pragma once

#include "engine_interface.hpp"
#include "gui_quad_field.hpp"
#include "gui_text_field.hpp"

class GuiButton final
{
public:
	GuiButton(shared_ptr<EngineInterface> fe3d, const string & id, const string & parentId, const fvec2 & position, const fvec2 & size, const string & diffuseMapPath, const fvec3 & defaultQuadColor, const fvec3 & hoveredQuadColor, const string & textContent, const fvec3 & defaultTextColor, const fvec3 & hoveredTextColor, bool isCentered);

	void update(bool isInteractable);
	void setVisible(bool value);
	void setHoverable(bool value);
	void setDefaultQuadColor(const fvec3 & value);
	void setHoveredQuadColor(const fvec3 & value);
	void setDefaultTextColor(const fvec3 & value);
	void setHoveredTextColor(const fvec3 & value);
	void setPosition(const fvec2 & value);
	void setSize(const fvec2 & value);
	void setMinClipPosition(const fvec2 & value);
	void setMaxClipPosition(const fvec2 & value);
	void setDiffuseMap(const string & value);
	void setTextContent(const string & value);

	const string & getId() const;
	const string & getParentId() const;
	const string & getDiffuseMapPath() const;
	const string & getTextContent() const;

	const fvec3 & getDefaultQuadColor();
	const fvec3 & getHoveredQuadColor();
	const fvec3 & getDefaultTextColor();
	const fvec3 & getHoveredTextColor();

	const fvec2 & getPosition() const;
	const fvec2 & getSize() const;

	const bool isHoverable() const;
	const bool isHovered() const;
	const bool isVisible() const;
	const bool isCentered() const;

private:
	void _updateHovering(bool isInteractable);

	static inline constexpr float TEXT_WIDTH_MULTIPLIER = 0.9f;
	static inline constexpr float TEXT_HEIGHT_MULTIPLIER = 0.75f;
	static inline constexpr float FULL_OPACITY = 1.0f;
	static inline constexpr float PART_OPACITY = 0.25f;

	static inline const string POINTING_CURSOR_PATH = "engine\\assets\\image\\diffuse_map\\cursor_pointing.tga";

	const string _id;
	const string _parentId;

	shared_ptr<EngineInterface> _fe3d = nullptr;
	shared_ptr<GuiQuadField> _quadField = nullptr;
	shared_ptr<GuiTextField> _textField = nullptr;

	fvec3 _defaultQuadColor = fvec3(0.0f);
	fvec3 _hoveredQuadColor = fvec3(0.0f);
	fvec3 _defaultTextColor = fvec3(0.0f);
	fvec3 _hoveredTextColor = fvec3(0.0f);

	bool _isHovered = false;
	bool _isHoverable = true;
};