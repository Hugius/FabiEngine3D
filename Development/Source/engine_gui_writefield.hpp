#pragma once

#include "fabi_engine_3d.hpp"
#include "engine_gui_button.hpp"

class EngineGuiWriteField final : public EngineGuiButton
{
public:
	EngineGuiWriteField(FabiEngine3D& fe3d, const string& parentID, const string& ID, Vec2 position, Vec2 size, Vec3 color, Vec3 hoverColor, 
		Vec3 textColor, Vec3 textHoverColor, bool noNumbers, bool noCaps, bool noSpecials, bool noLetters, bool minusAllowed);

	void update(bool hoverable) override;
	void setActive(bool active);
	void setPermActive(bool active);

	bool confirmedInput();
	bool isActive();
	bool hasTextContentChanged();

	string getTextContent();

	void setTextContent(const string& content);

private:
	void _updateActivation();
	void _updateTyping();

	bool _mustBeActive = false;
	bool _isActive = false;
	bool _confirmedInput = false;

	const bool _noNumbers;
	const bool _noCaps;
	const bool _noSpecials;
	const bool _noLetters;
	const bool _minusAllowed;

	static inline const int MAX_PASSED_BAR_FRAMES = 50;
	static inline const int MAX_PASSED_BACKSPACE_FRAMES = 20;

	string _lastTextContent = "";
	string _currentTextContent = "";

	static inline const float CHAR_WIDTH = 0.02f;
};