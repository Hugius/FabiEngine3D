#pragma once

#include "engine_interface.hpp"
#include "gui_scrolling_list.hpp"
#include "gui_input_field.hpp"
#include "gui_button.hpp"
#include "gui_quad_field.hpp"
#include "gui_text_field.hpp"

class GuiOverlay final
{
public:
	GuiOverlay(shared_ptr<EngineInterface> fe3d);

	void update();
	void createScrollingList(const string & id, const fvec2 & position, const fvec2 & size, const fvec3 & color, const fvec3 & defaultQuadColor, const fvec3 & hoveredQuadColor, const fvec3 & defaultTextColor, const fvec3 & hoveredTextColor, bool isCentered);
	void createInputField(const string & id, const fvec2 & position, const fvec2 & size, const fvec3 & color, const fvec3 & hoverColor, const fvec3 & textColor, const fvec3 & textHoverColor, bool noNumbers, bool noCaps, bool noSpecials, bool noLetters, bool minusAllowed, bool isCentered);
	void createButton(const string & id, const fvec2 & position, const fvec2 & size, const fvec3 & color, const fvec3 & hoverColor, const string & textContent, const fvec3 & textColor, const fvec3 & textHoverColor, bool isCentered);
	void createButton(const string & id, const fvec2 & position, const fvec2 & size, const string & texturePath, const fvec3 & hoverColor, bool isCentered);
	void createQuadField(const string & id, const fvec2 & position, const fvec2 & size, const fvec3 & color, bool isCentered);
	void createQuadField(const string & id, const fvec2 & position, const fvec2 & size, const string & texturePath, bool isCentered);
	void createTextField(const string & id, const fvec2 & position, const fvec2 & size, const string & textContent, const fvec3 & textColor, bool isCentered);
	void deleteScrollingList(const string & id);
	void deleteInputField(const string & id);
	void deleteButton(const string & id);
	void deleteQuadField(const string & id);
	void deleteTextField(const string & id);
	void deleteScrollingLists();
	void deleteInputFields();
	void deleteButtons();
	void deleteQuadFields();
	void deleteTextFields();
	void createValueForm(const string & id, const string & title, unsigned int value, const fvec2 & position, const fvec2 & size, const fvec2 & buttonsPosition);
	void createValueForm(const string & id, const string & title, int value, const fvec2 & position, const fvec2 & size, const fvec2 & buttonsPosition);
	void createValueForm(const string & id, const string & title, float value, const fvec2 & position, const fvec2 & size, const fvec2 & buttonsPosition);
	void createValueForm(const string & id, const string & title, double value, const fvec2 & position, const fvec2 & size, const fvec2 & buttonsPosition);
	void createValueForm(const string & id, const string & title, const string & value, const fvec2 & position, const fvec2 & size, const fvec2 & buttonsPosition);
	void createChoiceForm(const string & id, const string & title, const fvec2 & position, const vector<string> & buttonTitles);
	void deleteChoiceForm(const string & id);
	void createAnswerForm(const string & id, const string & title, const fvec2 & position);
	void setFocused(bool value);

	const unordered_map<string, shared_ptr<GuiScrollingList>> & getScrollingLists() const;
	const unordered_map<string, shared_ptr<GuiInputField>> & getInputFields() const;
	const unordered_map<string, shared_ptr<GuiButton>> & getButtons() const;
	const unordered_map<string, shared_ptr<GuiQuadField>> & getQuadFields() const;
	const unordered_map<string, shared_ptr<GuiTextField>> & getTextFields() const;

	const shared_ptr<GuiScrollingList> getScrollingList(const string & id) const;
	const shared_ptr<GuiInputField> getInputField(const string & id) const;
	const shared_ptr<GuiButton> getButton(const string & id) const;
	const shared_ptr<GuiQuadField> getQuadField(const string & id) const;
	const shared_ptr<GuiTextField> getTextField(const string & id) const;

	const string checkChoiceForm(const string & id) const;

	const bool isFocused() const;
	const bool hasScrollingList(const string & id) const;
	const bool hasInputField(const string & id) const;
	const bool hasButton(const string & id) const;
	const bool hasQuadField(const string & id) const;
	const bool hasTextField(const string & id) const;
	const bool checkValueForm(const string & id, unsigned int & value, const vector<unsigned int> & forbiddenValues = {});
	const bool checkValueForm(const string & id, int & value, const vector<int> & forbiddenValues = {});
	const bool checkValueForm(const string & id, float & value, const vector<float> & forbiddenValues = {});
	const bool checkValueForm(const string & id, double & value, const vector<double> & forbiddenValues = {});
	const bool checkValueForm(const string & id, string & value, const vector<string> & forbiddenValues = {});
	const bool isValueFormConfirmed() const;
	const bool isValueFormCancelled() const;
	const bool isValueFormExisting(const string & id) const;
	const bool isChoiceFormCancelled(const string & id) const;
	const bool isChoiceFormExisting(const string & id) const;
	const bool isAnswerFormConfirmed(const string & id);
	const bool isAnswerFormDenied(const string & id);
	const bool isAnswerFormExisting(const string & id) const;

private:
	void _createValueForm(const string & id, const string & title, const string & valueString, const fvec2 & position, const fvec2 & size, const fvec2 & buttonsPosition, bool onlyNumbers, bool minusAllowed);
	void _updateValueFormDeleting();
	void _deleteAnswerForm(const string & id);

	const bool _checkValueForm(const string & id, string & valueString, const vector<string> & forbiddenValueStrings);

	static inline const fvec3 FORM_TITLE_RECT_COLOR = fvec3(0.05f);
	static inline const fvec3 FORM_TITLE_TEXT_COLOR = fvec3(1.0f);

	unordered_map<string, shared_ptr<GuiScrollingList>> _scrollingLists = {};
	unordered_map<string, shared_ptr<GuiInputField>> _inputFields = {};
	unordered_map<string, shared_ptr<GuiButton>> _buttons = {};
	unordered_map<string, shared_ptr<GuiQuadField>> _quadFields = {};
	unordered_map<string, shared_ptr<GuiTextField>> _textFields = {};
	vector<string> _valueFormIds = {};

	shared_ptr<EngineInterface> _fe3d = nullptr;

	string _choiceFormId = "";
	string _answerFormId = "";

	bool _isFocused = false;
	bool _mustDeleteValueForms = false;
};