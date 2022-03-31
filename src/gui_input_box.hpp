#pragma once

#include "engine_interface.hpp"
#include "gui_button.hpp"

class GuiInputBox final
{
public:
	GuiInputBox(shared_ptr<EngineInterface> fe3d, const string & id, const string & parentId, const fvec2 & position, const fvec2 & size, const fvec3 & defaultQuadColor, const fvec3 & hoveredQuadColor, const fvec3 & defaultTextColor, const fvec3 & hoveredTextColor, unsigned int maxCharacterCount, bool isLettersAllowed, bool isNumbersAllowed, bool isSpecialsAllowed, bool isCapsAllowed, bool isCentered);

	void update(bool isFocused);
	void setActive(bool value);
	void setTextContent(const string & value);
	void setVisible(bool value);
	void setHoverable(bool value);
	void setMaxCharacterCount(unsigned int value);

	const string getId() const;
	const string getParentId() const;
	const string getTextContent() const;

	const fvec3 & getDefaultQuadColor();
	const fvec3 & getHoveredQuadColor();
	const fvec3 & getDefaultTextColor();
	const fvec3 & getHoveredTextColor();

	const fvec2 & getPosition() const;
	const fvec2 & getSize() const;

	const unsigned int getMaxCharacterCount() const;

	const bool isHovered() const;
	const bool isHoverable() const;
	const bool isVisible() const;
	const bool isConfirmed() const;
	const bool isActive() const;
	const bool isCentered() const;

private:
	void _updateHovering(bool isFocused);
	void _updateActivation();
	void _updateTyping();

	static inline const unordered_map<char, char> SPECIAL_CHARACTERS =
	{
		{'.', '>'},
		{',', '<'},
		{'/', '?'},
		{';', ':'},
		{'\'', '\"'},
		{'[', '{'},
		{']', '}'},
		{'\\', '|'},
		{'-', '_'},
		{'=', '+'}
	};
	static inline const unordered_map<char, char> NUMBER_CHARACTERS =
	{
		{'0', ')'},
		{'1', '!'},
		{'2', '@'},
		{'3', '#'},
		{'4', '$'},
		{'5', '%'},
		{'6', '^'},
		{'7', '&'},
		{'8', '*'},
		{'9', '('}
	};
	static inline const unordered_map<char, char> ALPHABET_CHARACTERS =
	{
		{'a', 'A'},
		{'b', 'B'},
		{'c', 'C'},
		{'d', 'D'},
		{'e', 'E'},
		{'f', 'F'},
		{'g', 'G'},
		{'h', 'H'},
		{'i', 'I'},
		{'j', 'J'},
		{'k', 'K'},
		{'l', 'L'},
		{'m', 'M'},
		{'n', 'N'},
		{'o', 'O'},
		{'p', 'P'},
		{'q', 'Q'},
		{'r', 'R'},
		{'s', 'S'},
		{'t', 'T'},
		{'u', 'U'},
		{'v', 'V'},
		{'w', 'W'},
		{'x', 'X'},
		{'y', 'Y'},
		{'z', 'Z'},
	};
	static inline constexpr float FULL_OPACITY = 1.0f;
	static inline constexpr float PART_OPACITY = 0.25f;

	const string _id;
	const string _parentId;

	shared_ptr<EngineInterface> _fe3d = nullptr;
	shared_ptr<GuiQuadField> _quadField = nullptr;
	shared_ptr<GuiTextField> _textField = nullptr;

	string _lastTextContent = "";

	fvec3 _defaultQuadColor = fvec3(0.0f);
	fvec3 _hoveredQuadColor = fvec3(0.0f);
	fvec3 _defaultTextColor = fvec3(0.0f);
	fvec3 _hoveredTextColor = fvec3(0.0f);

	unsigned int _maxCharacterCount = 0;

	bool _isHovered = false;
	bool _isHoverable = true;
	bool _isActive = false;
	bool _isConfirmed = false;
	bool _isLettersAllowed = false;
	bool _isNumbersAllowed = false;
	bool _isSpecialsAllowed = false;
	bool _isCapsAllowed = false;
	bool _isBarVisible = false;
};