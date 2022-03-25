#pragma once

#include "engine_interface.hpp"
#include "gui_scrolling_list.hpp"
#include "gui_input_field.hpp"
#include "gui_button.hpp"
#include "gui_quad_field.hpp"
#include "gui_text_field.hpp"

class GuiScreen final
{
public:
	GuiScreen(shared_ptr<EngineInterface> fe3d, const string& id, const string& parentId, const fvec2& position, const fvec2& size);

	void update(bool isHoverable);
	void setVisible(bool value);
	void createScrollingList(const string& id, const fvec2& position, const fvec2& size, const fvec3& color, const fvec3& buttonColor, const fvec3& buttonHoverColor, const fvec3& textColor, const fvec3& textHoverColor, const fvec2& charSize, bool isCentered);
	void createInputField(const string& id, const fvec2& position, const fvec2& size, const fvec3& color, const fvec3& hoverColor, const fvec3& textColor, const fvec3& textHoverColor, bool noNumbers, bool noCaps, bool noSpecials, bool noLetters, bool minusAllowed, bool isCentered);
	void createButton(const string& id, const fvec2& position, const fvec2& size, const fvec3& color, const fvec3& hoverColor, const string& textContent, const fvec3& textColor, const fvec3& textHoverColor, bool isCentered);
	void createButton(const string& id, const fvec2& position, const fvec2& size, const string& texturePath, const fvec3& hoverColor, bool isCentered);
	void createQuadField(const string& id, const fvec2& position, const fvec2& size, const fvec3& color, bool isCentered);
	void createQuadField(const string& id, const fvec2& position, const fvec2& size, const string& texturePath, bool isCentered);
	void createTextField(const string& id, const fvec2& position, const fvec2& size, const string& textContent, const fvec3& textColor, bool isCentered);
	void deleteScrollingList(const string& id);
	void deleteInputField(const string& id);
	void deleteButton(const string& id);
	void deleteQuadField(const string& id);
	void deleteTextField(const string& id);
	void deleteScrollingLists();
	void deleteInputFields();
	void deleteButtons();
	void deleteQuadFields();
	void deleteTextFields();

	const unordered_map<string, shared_ptr<GuiScrollingList>>& getScrollingLists() const;
	const unordered_map<string, shared_ptr<GuiInputField>>& getInputFields() const;
	const unordered_map<string, shared_ptr<GuiButton>>& getButtons() const;
	const unordered_map<string, shared_ptr<GuiQuadField>>& getQuadFields() const;
	const unordered_map<string, shared_ptr<GuiTextField>>& getTextFields() const;

	const shared_ptr<GuiScrollingList> getScrollingList(const string& id) const;
	const shared_ptr<GuiInputField> getInputField(const string& id) const;
	const shared_ptr<GuiButton> getButton(const string& id) const;
	const shared_ptr<GuiQuadField> getQuadField(const string& id) const;
	const shared_ptr<GuiTextField> getTextField(const string& id) const;

	const string& getId() const;
	const string& getParentId() const;

	const fvec2 convertPosition(const fvec2& position) const;
	const fvec2 convertSize(const fvec2& size) const;

	const bool hasScrollingList(const string& id) const;
	const bool hasInputField(const string& id) const;
	const bool hasButton(const string& id) const;
	const bool hasQuadField(const string& id) const;
	const bool hasTextField(const string& id) const;
	const bool isVisible() const;

private:
	const fvec4 _convertDimensions(const fvec2& position, const fvec2& size) const;

	const string _id;
	const string _parentId;

	unordered_map<string, shared_ptr<GuiScrollingList>> _scrollingLists = {};
	unordered_map<string, shared_ptr<GuiInputField>> _inputFields = {};
	unordered_map<string, shared_ptr<GuiButton>> _buttons = {};
	unordered_map<string, shared_ptr<GuiQuadField>> _quadFields = {};
	unordered_map<string, shared_ptr<GuiTextField>> _textFields = {};

	shared_ptr<EngineInterface> _fe3d = nullptr;

	fvec2 _parentPosition;
	fvec2 _parentSize;

	bool _isVisible = false;
};