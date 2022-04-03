#pragma once

#include "engine_interface.hpp"
#include "gui_scrolling_list.hpp"
#include "gui_input_box.hpp"
#include "gui_button.hpp"
#include "gui_quad_field.hpp"
#include "gui_text_field.hpp"

class GuiOverlay final
{
public:
	GuiOverlay(shared_ptr<EngineInterface> fe3d);

	void update();
	void setFocused(bool value);
	void createScrollingList(const string & id, const fvec2 & position, const fvec2 & size, const fvec3 & color, const fvec3 & defaultQuadColor, const fvec3 & hoveredQuadColor, const fvec3 & defaultTextColor, const fvec3 & hoveredTextColor, const fvec2 & characterSize, float scrollingSpeed, bool isCentered);
	void createInputBox(const string & id, const fvec2 & position, const fvec2 & size, const fvec3 & defaultQuadColor, const fvec3 & hoveredQuadColor, const fvec3 & defaultTextColor, const fvec3 & hoveredTextColor, unsigned int maxCharacterCount, bool isLettersAllowed, bool isNumbersAllowed, bool isSpecialsAllowed, bool isCentered);
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
	void openValueForm(const string & id, const string & title, const string & value, const fvec2 & position, const fvec2 & size, unsigned int maxCharacterCount, bool isLettersAllowed, bool isNumbersAllowed, bool isSpecialsAllowed);
	void openAnswerForm(const string & id, const string & title, const fvec2 & position);
	void closeChoiceForm();
	void closeValueForm();
	void closeAnswerForm();

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

	const string getSelectedChoiceFormOptionId() const;
	const string getValueFormContent() const;

	const bool isFocused() const;
	const bool hasScrollingList(const string & id) const;
	const bool hasInputBox(const string & id) const;
	const bool hasButton(const string & id) const;
	const bool hasQuadField(const string & id) const;
	const bool hasTextField(const string & id) const;
	const bool isValueFormOpen(const string & id) const;
	const bool isValueFormConfirmed() const;
	const bool isValueFormCancelled() const;
	const bool isChoiceFormOpen(const string & id) const;
	const bool isChoiceFormCancelled() const;
	const bool isAnswerFormOpen(const string & id) const;
	const bool isAnswerFormAccepted();
	const bool isAnswerFormDenied();
	const bool isAnswerFormCancelled();

private:
	static inline const fvec3 FORM_TITLE_QUAD_COLOR = fvec3(0.05f);
	static inline const fvec3 FORM_TITLE_TEXT_COLOR = fvec3(1.0f);

	unordered_map<string, shared_ptr<GuiScrollingList>> _scrollingLists = {};
	unordered_map<string, shared_ptr<GuiInputBox>> _inputBoxes = {};
	unordered_map<string, shared_ptr<GuiButton>> _buttons = {};
	unordered_map<string, shared_ptr<GuiQuadField>> _quadFields = {};
	unordered_map<string, shared_ptr<GuiTextField>> _textFields = {};

	shared_ptr<EngineInterface> _fe3d = nullptr;

	string _choiceFormId = "";
	string _valueFormId = "";
	string _answerFormId = "";

	bool _isFocused = false;
};