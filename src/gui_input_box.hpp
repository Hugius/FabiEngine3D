#pragma once

#include "engine_interface.hpp"
#include "gui_button.hpp"

class GuiInputBox final
{
public:
	GuiInputBox(shared_ptr<EngineInterface> fe3d, const string & id, const string & parentId, const fvec2 & position, const fvec2 & size, const fvec3 & defaultQuadColor, const fvec3 & hoveredQuadColor, const fvec3 & defaultTextColor, const fvec3 & hoveredTextColor, bool noNumbers, bool noCaps, bool noSpecials, bool noLetters, bool minusAllowed, bool isCentered);

	void update(bool isFocused);
	void setActive(bool value);
	void setTextContent(const string & value);
	void setVisible(bool value);
	void setHoverable(bool value);

	const string getId() const;
	const string getParentId() const;
	const string getTextContent() const;

	const fvec2 & getPosition() const;
	const fvec2 & getSize() const;

	const bool isHovered() const;
	const bool isHoverable() const;
	const bool isVisible() const;
	const bool confirmedInput() const;
	const bool isActive() const;
	const bool hasTextContentChanged() const;
	const bool isCentered() const;

private:
	void _updateHovering(bool isFocused);
	void _updateActivation();
	void _updateTyping();

	static inline constexpr float FULL_OPACITY = 1.0f;
	static inline constexpr float PART_OPACITY = 0.25f;
	static inline constexpr float CHAR_WIDTH = 0.02f;
	static inline constexpr int MAX_PASSED_BAR_FRAMES = 50;
	static inline constexpr int MAX_PASSED_BACKSPACE_FRAMES = 20;

	const string _id;
	const string _parentId;

	shared_ptr<EngineInterface> _fe3d = nullptr;
	shared_ptr<GuiQuadField> _quadField = nullptr;
	shared_ptr<GuiTextField> _textField = nullptr;

	string _lastTextContent = "";
	string _currentTextContent = "";

	fvec3 _defaultQuadColor = fvec3(0.0f);
	fvec3 _hoveredQuadColor = fvec3(0.0f);
	fvec3 _defaultTextColor = fvec3(0.0f);
	fvec3 _hoveredTextColor = fvec3(0.0f);

	bool _isHovered = false;
	bool _isHoverable = true;
	bool _isActive = false;
	bool _confirmedInput = false;
	bool _noNumbers = false;
	bool _noCaps = false;
	bool _noSpecials = false;
	bool _noLetters = false;
	bool _minusAllowed = false;
};