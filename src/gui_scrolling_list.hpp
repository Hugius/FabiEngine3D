#pragma once

#include "engine_interface.hpp"
#include "gui_button.hpp"

class GuiScrollingList final
{
public:
	GuiScrollingList(shared_ptr<EngineInterface> fe3d, const string & id, const string & parentId, const fvec2 & position, const fvec2 & size, const fvec3 & color, const fvec3 & defaultQuadColor, const fvec3 & hoveredQuadColor, const fvec3 & defaultTextColor, const fvec3 & hoveredTextColor, bool isCentered);

	void update(bool isFocused);
	void createOption(const string & id, const string & textContent);
	void deleteOption(const string & id);
	void deleteOptions();
	void setPosition(const fvec2 & value);
	void setSize(const fvec2 & value);
	void setVisible(bool value);

	const vector<string> getOptionIds() const;

	const string getHoveredOptionId() const;

	const fvec2 & getPosition() const;
	const fvec2 & getSize() const;

	const bool hasOption(const string & id) const;
	const bool isHovered() const;
	const bool isVisible() const;
	const bool isCentered() const;

private:
	void _updateHovering();
	void _updateScrolling();

	const fvec2 _convertPosition(const fvec2 & position) const;
	const fvec2 _convertSize(const fvec2 & size) const;

	static inline constexpr float SCROLLING_SPEED = 0.25f;
	static inline constexpr float CHARACTER_WIDTH = 0.075f;
	static inline constexpr float CHARACTER_HEIGHT = 0.15f;

	const string _id;
	const string _parentId;

	const fvec3 _defaultQuadColor;
	const fvec3 _hoveredQuadColor;
	const fvec3 _defaultTextColor;
	const fvec3 _hoveredTextColor;
	const fvec2 _charSize;

	vector<shared_ptr<GuiButton>> _buttons = {};

	shared_ptr<GuiQuadField> _quadField = nullptr;
	shared_ptr<EngineInterface> _fe3d = nullptr;

	float _scrollingOffset = 0.0f;

	bool _isHovered = false;
};