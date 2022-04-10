#pragma once

#include "engine_interface.hpp"
#include "gui_button.hpp"

class GuiInputBox final
{
public:
	GuiInputBox(shared_ptr<EngineInterface> fe3d, const string & id, const string & parentId, const fvec2 & position, const fvec2 & size, const fvec3 & defaultQuadColor, const fvec3 & hoveredQuadColor, const fvec3 & defaultTextColor, const fvec3 & hoveredTextColor, unsigned int maxCharacterCount, bool isLettersAllowed, bool isNumbersAllowed, bool isSpecialsAllowed, bool isCentered);

	void update(bool isInteractable);
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
	const bool isActive() const;
	const bool isCentered() const;

private:
	void _updateHovering(bool isInteractable);
	void _updateTyping();

	static inline const unordered_map<InputType, string> FIRST_ALPHABET_CHARACTERS =
	{
		{InputType::KEY_A, "a"},
		{InputType::KEY_B, "b"},
		{InputType::KEY_C, "c"},
		{InputType::KEY_D, "d"},
		{InputType::KEY_E, "e"},
		{InputType::KEY_F, "f"},
		{InputType::KEY_G, "g"},
		{InputType::KEY_H, "h"},
		{InputType::KEY_I, "i"},
		{InputType::KEY_J, "j"},
		{InputType::KEY_K, "k"},
		{InputType::KEY_L, "l"},
		{InputType::KEY_M, "m"},
		{InputType::KEY_N, "n"},
		{InputType::KEY_O, "o"},
		{InputType::KEY_P, "p"},
		{InputType::KEY_Q, "q"},
		{InputType::KEY_R, "r"},
		{InputType::KEY_S, "s"},
		{InputType::KEY_T, "t"},
		{InputType::KEY_U, "u"},
		{InputType::KEY_V, "v"},
		{InputType::KEY_W, "w"},
		{InputType::KEY_X, "x"},
		{InputType::KEY_Y, "y"},
		{InputType::KEY_Z, "z"},
	};
	static inline const unordered_map<InputType, string> SECOND_ALPHABET_CHARACTERS =
	{
		{InputType::KEY_A, "A"},
		{InputType::KEY_B, "B"},
		{InputType::KEY_C, "C"},
		{InputType::KEY_D, "D"},
		{InputType::KEY_E, "E"},
		{InputType::KEY_F, "F"},
		{InputType::KEY_G, "G"},
		{InputType::KEY_H, "H"},
		{InputType::KEY_I, "I"},
		{InputType::KEY_J, "J"},
		{InputType::KEY_K, "K"},
		{InputType::KEY_L, "L"},
		{InputType::KEY_M, "M"},
		{InputType::KEY_N, "N"},
		{InputType::KEY_O, "O"},
		{InputType::KEY_P, "P"},
		{InputType::KEY_Q, "Q"},
		{InputType::KEY_R, "R"},
		{InputType::KEY_S, "S"},
		{InputType::KEY_T, "T"},
		{InputType::KEY_U, "U"},
		{InputType::KEY_V, "V"},
		{InputType::KEY_W, "W"},
		{InputType::KEY_X, "X"},
		{InputType::KEY_Y, "Y"},
		{InputType::KEY_Z, "Z"},
	};
	static inline const unordered_map<InputType, string> FIRST_NUMBER_CHARACTERS =
	{
		{InputType::KEY_0, "0"},
		{InputType::KEY_1, "1"},
		{InputType::KEY_2, "2"},
		{InputType::KEY_3, "3"},
		{InputType::KEY_4, "4"},
		{InputType::KEY_5, "5"},
		{InputType::KEY_6, "6"},
		{InputType::KEY_7, "7"},
		{InputType::KEY_8, "8"},
		{InputType::KEY_9, "9"},
	};
	static inline const unordered_map<InputType, string> SECOND_NUMBER_CHARACTERS =
	{
		{InputType::KEY_0, "!"},
		{InputType::KEY_1, "@"},
		{InputType::KEY_2, "#"},
		{InputType::KEY_3, "$"},
		{InputType::KEY_4, "%"},
		{InputType::KEY_5, "^"},
		{InputType::KEY_6, "&"},
		{InputType::KEY_7, "*"},
		{InputType::KEY_8, "("},
		{InputType::KEY_9, ")"},
	};
	static inline const unordered_map<InputType, string> FIRST_SPECIAL_CHARACTERS =
	{
		{InputType::KEY_SEMICOLON, ";"},
		{InputType::KEY_EQUAL, "="},
		{InputType::KEY_COMMA, ","},
		{InputType::KEY_MINUS, "-"},
		{InputType::KEY_PERIOD, "."},
		{InputType::KEY_FORWARDSLASH, "/"},
		{InputType::KEY_GRAVE, "`"},
		{InputType::KEY_LEFTBRACKET, "["},
		{InputType::KEY_BACKWARDSLASH, "\\"},
		{InputType::KEY_RIGHTBRACKET, "]"},
		{InputType::KEY_QUOTE, "'"},
	};
	static inline const unordered_map<InputType, string> SECOND_SPECIAL_CHARACTERS =
	{
		{InputType::KEY_SEMICOLON, ":"},
		{InputType::KEY_EQUAL, "+"},
		{InputType::KEY_COMMA, "<"},
		{InputType::KEY_MINUS, "_"},
		{InputType::KEY_PERIOD, ">"},
		{InputType::KEY_FORWARDSLASH, "?"},
		{InputType::KEY_GRAVE, "~"},
		{InputType::KEY_LEFTBRACKET, "{"},
		{InputType::KEY_BACKWARDSLASH, "|"},
		{InputType::KEY_RIGHTBRACKET, "}"},
		{InputType::KEY_QUOTE, "\""},
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
	bool _isLettersAllowed = false;
	bool _isNumbersAllowed = false;
	bool _isSpecialsAllowed = false;
	bool _isBarVisible = false;
};