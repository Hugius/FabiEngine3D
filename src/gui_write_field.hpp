#pragma once

#include "engine_interface.hpp"
#include "gui_button.hpp"

class GuiWriteField final : public GuiButton
{
public:
	GuiWriteField(shared_ptr<EngineInterface> fe3d, const string& parentId, const string& id, const fvec2& position, const fvec2& size, const fvec3& color, const fvec3& hoverColor,
				  const fvec3& textColor, const fvec3& textHoverColor, bool noNumbers, bool noCaps, bool noSpecials, bool noLetters, bool minusAllowed, bool isCentered);

	void update(bool isHoverable);
	void setActive(bool active);
	void setPermActive(bool active);
	void changeTextContent(const string& content);

	const string getTextContent() const;

	const bool confirmedInput() const;
	const bool isActive() const;
	const bool hasTextContentChanged();

private:
	void _updateActivation();
	void _updateTyping();

	string _lastTextContent = "";
	string _currentTextContent = "";

	static inline constexpr float CHAR_WIDTH = 0.02f;

	static inline constexpr int MAX_PASSED_BAR_FRAMES = 50;
	static inline constexpr int MAX_PASSED_BACKSPACE_FRAMES = 20;

	const bool _noNumbers;
	const bool _noCaps;
	const bool _noSpecials;
	const bool _noLetters;
	const bool _minusAllowed;
	bool _mustBeActive = false;
	bool _isActive = false;
	bool _confirmedInput = false;
};