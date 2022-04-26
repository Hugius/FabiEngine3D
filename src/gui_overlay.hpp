#pragma once

#include "engine_interface.hpp"
#include "gui_scrolling_list.hpp"
#include "gui_input_box.hpp"
#include "gui_button.hpp"
#include "gui_quad_field.hpp"
#include "gui_text_field.hpp"

using std::tuple;

class GuiOverlay final
{
public:
	GuiOverlay(shared_ptr<EngineInterface> fe3d);

	void update(bool isInteractable);
	void setFocused(bool value);
	void createScrollingList(const string & id, const fvec2 & position, const fvec2 & size, const fvec3 & color, const fvec3 & defaultQuadColor, const fvec3 & hoveredQuadColor, const fvec3 & defaultTextColor, const fvec3 & hoveredTextColor, const fvec2 & characterSize, float scrollingSpeed, bool isCentered);
	void createInputBox(const string & id, const fvec2 & position, const fvec2 & size, const fvec3 & defaultQuadColor, const fvec3 & hoveredQuadColor, const fvec3 & defaultTextColor, const fvec3 & hoveredTextColor, int maxCharacterCount, bool isLettersAllowed, bool isNumbersAllowed, bool isSpecialsAllowed, bool isCentered);
	void createButton(const string & id, const fvec2 & position, const fvec2 & size, const string & diffuseMapPath, const fvec3 & defaultQuadColor, const fvec3 & hoveredQuadColor, const string & textContent, const fvec3 & defaultTextColor, const fvec3 & hoveredTextColor, bool isCentered);
	void createQuadField(const string & id, const fvec2 & position, const fvec2 & size, const string & diffuseMapPath, const fvec3 & color, bool isCentered);
	void createTextField(const string & id, const fvec2 & position, const fvec2 & size, const string & textContent, const fvec3 & textColor, bool isCentered);
	void deleteScrollingList(const string & id);
	void deleteInputBox(const string & id);
	void deleteButton(const string & id);
	void deleteQuadField(const string & id);
	void deleteTextField(const string & id);
	void deleteScrollingLists();
	void deleteInputBoxes();
	void deleteButtons();
	void deleteQuadFields();
	void deleteTextFields();
	void openChoiceForm(const string & id, const string & title, const fvec2 & position, const vector<string> & buttonTitles);
	void openValueForm(const string & id, const string & title, const string & value, const fvec2 & position, int maxCharacterCount, bool isLettersAllowed, bool isNumbersAllowed, bool isSpecialsAllowed);
	void openValueForm(const string & id, const string & title, float value, const fvec2 & position, int maxCharacterCount, bool isLettersAllowed, bool isNumbersAllowed, bool isSpecialsAllowed);
	void openValueForm(const string & id, const string & title, int value, const fvec2 & position, int maxCharacterCount, bool isLettersAllowed, bool isNumbersAllowed, bool isSpecialsAllowed);
	void openAnswerForm(const string & id, const string & title, const string & left, const string & right, const fvec2 & position);

	const unordered_map<string, shared_ptr<GuiScrollingList>> & getScrollingLists() const;
	const unordered_map<string, shared_ptr<GuiInputBox>> & getInputBoxes() const;
	const unordered_map<string, shared_ptr<GuiButton>> & getButtons() const;
	const unordered_map<string, shared_ptr<GuiQuadField>> & getQuadFields() const;
	const unordered_map<string, shared_ptr<GuiTextField>> & getTextFields() const;

	const shared_ptr<GuiScrollingList> getScrollingList(const string & id) const;
	const shared_ptr<GuiInputBox> getInputBox(const string & id) const;
	const shared_ptr<GuiButton> getButton(const string & id) const;
	const shared_ptr<GuiQuadField> getQuadField(const string & id) const;
	const shared_ptr<GuiTextField> getTextField(const string & id) const;

	const string getChoiceFormId() const;
	const string getValueFormId() const;
	const string getAnswerFormId() const;
	const string getChoiceFormOptionId() const;
	const string getValueFormContent() const;
	const string getAnswerFormDecision() const;

	const bool isFocused() const;
	const bool hasScrollingList(const string & id) const;
	const bool hasInputBox(const string & id) const;
	const bool hasButton(const string & id) const;
	const bool hasQuadField(const string & id) const;
	const bool hasTextField(const string & id) const;
	const bool isChoiceFormConfirmed() const;
	const bool isValueFormConfirmed() const;
	const bool isAnswerFormConfirmed() const;

private:
	void _updateForms();
	void _closeChoiceForm();
	void _closeValueForm();
	void _closeAnswerForm();

	static inline const fvec3 CF_TITLE_QUAD_COLOR = fvec3(0.05f);
	static inline const fvec3 CF_TITLE_TEXT_COLOR = fvec3(1.0f);
	static inline const fvec3 CF_LIST_COLOR = fvec3(0.25f);
	static inline const fvec3 CF_DEFAULT_OPTION_QUAD_COLOR = fvec3(0.0f, 0.1f, 0.0f);
	static inline const fvec3 CF_HOVERED_OPTION_QUAD_COLOR = fvec3(0.0f, 1.0f, 0.0f);
	static inline const fvec3 CF_DEFAULT_OPTION_TEXT_COLOR = fvec3(1.0f);
	static inline const fvec3 CF_HOVERED_OPTION_TEXT_COLOR = fvec3(0.0f);
	static inline const fvec3 CF_DEFAULT_CANCEL_QUAD_COLOR = fvec3(0.1f, 0.0f, 0.0f);
	static inline const fvec3 CF_HOVERED_CANCEL_QUAD_COLOR = fvec3(1.0f, 0.0f, 0.0f);
	static inline const fvec3 CF_DEFAULT_CANCEL_TEXT_COLOR = fvec3(1.0f);
	static inline const fvec3 CF_HOVERED_CANCEL_TEXT_COLOR = fvec3(0.0f);
	static inline const fvec3 VF_TITLE_QUAD_COLOR = fvec3(0.05f);
	static inline const fvec3 VF_TITLE_TEXT_COLOR = fvec3(1.0f);
	static inline const fvec3 VF_DEFAULT_BOX_QUAD_COLOR = fvec3(0.25f);
	static inline const fvec3 VF_HOVERED_BOX_QUAD_COLOR = fvec3(0.5f);
	static inline const fvec3 VF_DEFAULT_BOX_TEXT_COLOR = fvec3(1.0f);
	static inline const fvec3 VF_HOVERED_BOX_TEXT_COLOR = fvec3(0.0f);
	static inline const fvec3 VF_DEFAULT_ENTER_QUAD_COLOR = fvec3(0.0f, 0.1f, 0.0f);
	static inline const fvec3 VF_HOVERED_ENTER_QUAD_COLOR = fvec3(0.0f, 1.0f, 0.0f);
	static inline const fvec3 VF_DEFAULT_ENTER_TEXT_COLOR = fvec3(1.0f);
	static inline const fvec3 VF_HOVERED_ENTER_TEXT_COLOR = fvec3(0.0f);
	static inline const fvec3 VF_DEFAULT_CANCEL_QUAD_COLOR = fvec3(0.1f, 0.0f, 0.0f);
	static inline const fvec3 VF_HOVERED_CANCEL_QUAD_COLOR = fvec3(1.0f, 0.0f, 0.0f);
	static inline const fvec3 VF_DEFAULT_CANCEL_TEXT_COLOR = fvec3(1.0f);
	static inline const fvec3 VF_HOVERED_CANCEL_TEXT_COLOR = fvec3(0.0f);
	static inline const fvec3 AF_TITLE_QUAD_COLOR = fvec3(0.05f);
	static inline const fvec3 AF_TITLE_TEXT_COLOR = fvec3(1.0f);
	static inline const fvec3 AF_DEFAULT_LEFT_QUAD_COLOR = fvec3(0.0f, 0.1f, 0.0f);
	static inline const fvec3 AF_HOVERED_LEFT_QUAD_COLOR = fvec3(0.0f, 1.0f, 0.0f);
	static inline const fvec3 AF_DEFAULT_LEFT_TEXT_COLOR = fvec3(1.0f);
	static inline const fvec3 AF_HOVERED_LEFT_TEXT_COLOR = fvec3(0.0f);
	static inline const fvec3 AF_DEFAULT_CANCEL_QUAD_COLOR = fvec3(0.1f, 0.0f, 0.0f);
	static inline const fvec3 AF_HOVERED_CANCEL_QUAD_COLOR = fvec3(1.0f, 0.0f, 0.0f);
	static inline const fvec3 AF_DEFAULT_CANCEL_TEXT_COLOR = fvec3(1.0f);
	static inline const fvec3 AF_HOVERED_CANCEL_TEXT_COLOR = fvec3(0.0f);
	static inline const fvec3 AF_DEFAULT_RIGHT_QUAD_COLOR = fvec3(0.0f, 0.1f, 0.0f);
	static inline const fvec3 AF_HOVERED_RIGHT_QUAD_COLOR = fvec3(0.0f, 1.0f, 0.0f);
	static inline const fvec3 AF_DEFAULT_RIGHT_TEXT_COLOR = fvec3(1.0f);
	static inline const fvec3 AF_HOVERED_RIGHT_TEXT_COLOR = fvec3(0.0f);

	static inline const fvec2 CF_TITLE_QUAD_SIZE = fvec2(0.0275f, 0.125f);
	static inline const fvec2 CF_TITLE_TEXT_SIZE = fvec2(0.025f, 0.1f);
	static inline const fvec2 CF_TITLE_OFFSET = fvec2(0.0f, 0.475f);
	static inline const fvec2 CF_LIST_OFFSET = fvec2(0.0f, 0.475f);
	static inline const fvec2 CF_LIST_SIZE = fvec2(0.5, 0.75f);
	static inline const fvec2 CF_LIST_CHAR_SIZE = fvec2(0.1f, 0.175f);
	static inline const fvec2 CF_CANCEL_OFFSET = fvec2(0.0f, -0.475f);
	static inline const fvec2 CF_CANCEL_SIZE = fvec2(0.18f, 0.1f);
	static inline const fvec2 VF_TITLE_QUAD_SIZE = fvec2(0.0275f, 0.125f);
	static inline const fvec2 VF_TITLE_TEXT_SIZE = fvec2(0.025f, 0.1f);
	static inline const fvec2 VF_TITLE_OFFSET = fvec2(0.0f, 0.2f);
	static inline const fvec2 VF_BOX_SIZE = fvec2(0.025f, 0.1f);
	static inline const fvec2 VF_ENTER_OFFSET = fvec2(-0.15f, -0.2f);
	static inline const fvec2 VF_ENTER_SIZE = fvec2(0.15f, 0.1f);
	static inline const fvec2 VF_CANCEL_OFFSET = fvec2(0.15f, -0.2f);
	static inline const fvec2 VF_CANCEL_SIZE = fvec2(0.18f, 0.1f);
	static inline const fvec2 AF_TITLE_QUAD_SIZE = fvec2(0.0275f, 0.125f);
	static inline const fvec2 AF_TITLE_TEXT_SIZE = fvec2(0.025f, 0.1f);
	static inline const fvec2 AF_TITLE_OFFSET = fvec2(0.0f, 0.2f);
	static inline const fvec2 AF_LEFT_CHAR_SIZE = fvec2(0.03f, 0.1f);
	static inline const fvec2 AF_CANCEL_OFFSET = fvec2(0.0f, -0.2f);
	static inline const fvec2 AF_CANCEL_SIZE = fvec2(0.18f, 0.1f);
	static inline const fvec2 AF_RIGHT_CHAR_SIZE = fvec2(0.03f, 0.1f);

	static inline constexpr float CF_SCROLLING_SPEED = 0.25f;

	unordered_map<string, shared_ptr<GuiScrollingList>> _scrollingLists = {};
	unordered_map<string, shared_ptr<GuiInputBox>> _inputBoxes = {};
	unordered_map<string, shared_ptr<GuiButton>> _buttons = {};
	unordered_map<string, shared_ptr<GuiQuadField>> _quadFields = {};
	unordered_map<string, shared_ptr<GuiTextField>> _textFields = {};

	vector<tuple<string, string, string, fvec2, int, bool, bool, bool>> _valueFormQueue = {};

	shared_ptr<EngineInterface> _fe3d = nullptr;

	string _choiceFormId = "";
	string _valueFormId = "";
	string _answerFormId = "";

	bool _isFocused = false;
	bool _mustCloseChoiceForm = false;
	bool _mustCloseValueForm = false;
	bool _mustCloseAnswerForm = false;
};