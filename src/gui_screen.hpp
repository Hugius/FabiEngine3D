#pragma once

#include "engine_interface.hpp"
#include "gui_scrolling_list.hpp"
#include "gui_write_field.hpp"
#include "gui_button.hpp"
#include "gui_rectangle.hpp"
#include "gui_text_field.hpp"

class GuiScreen final
{
public:
	GuiScreen(shared_ptr<EngineInterface> fe3d, const string& parentId, const string& id, const fvec2& position, const fvec2& size);

	void update(bool isHoverable);
	void show();
	void hide();
	void createScrollingList(const string& id, const fvec2& position, const fvec2& size, const fvec3& color, const fvec3& buttonColor, const fvec3& buttonHoverColor, const fvec3& textColor, const fvec3& textHoverColor, const fvec2& charSize, bool isCentered);
	void createWriteField(const string& id, const fvec2& position, const fvec2& size, const fvec3& color, const fvec3& hoverColor, const fvec3& textColor, const fvec3& textHoverColor, bool noNumbers, bool noCaps, bool noSpecials, bool noLetters, bool minusAllowed, bool isCentered);
	void createButton(const string& id, const fvec2& position, const fvec2& size, const fvec3& color, const fvec3& hoverColor, const string& textContent, const fvec3& textColor, const fvec3& textHoverColor, bool isCentered);
	void createButton(const string& id, const fvec2& position, const fvec2& size, const string& texturePath, const fvec3& hoverColor, bool isCentered);
	void createRectangle(const string& id, const fvec2& position, const fvec2& size, const fvec3& color, bool isCentered);
	void createRectangle(const string& id, const fvec2& position, const fvec2& size, const string& texturePath, bool isCentered);
	void createTextField(const string& id, const fvec2& position, const fvec2& size, const string& textContent, const fvec3& textColor, bool isCentered);
	void deleteScrollingList(const string& id);
	void deleteWriteField(const string& id);
	void deleteButton(const string& id);
	void deleteRectangle(const string& id);
	void deleteTextField(const string& id);

	const string& getId() const;
	const string& getParentId() const;

	const fvec2 convertPosition(const fvec2& position) const;
	const fvec2 convertSize(const fvec2& size) const;

	const bool isScrollingListExisting(const string& id) const;
	const bool isWriteFieldExisting(const string& id) const;
	const bool isButtonExisting(const string& id) const;
	const bool isRectangleExisting(const string& id) const;
	const bool isTextFieldExisting(const string& id) const;

	shared_ptr<GuiScrollingList> getScrollingList(const string& id) const;
	shared_ptr<GuiWriteField> getWriteField(const string& id) const;
	shared_ptr<GuiButton> getButton(const string& id) const;
	shared_ptr<GuiRectangle> getRectangle(const string& id) const;
	shared_ptr<GuiTextField> getTextField(const string& id) const;
	const vector<shared_ptr<GuiScrollingList>>& getScrollingLists() const;
	const vector<shared_ptr<GuiWriteField>>& getWriteFields() const;
	const vector<shared_ptr<GuiButton>>& getButtons() const;
	const vector<shared_ptr<GuiRectangle>>& getRectangles() const;
	const vector<shared_ptr<GuiTextField>>& getTextFields() const;

private:
	const fvec4 _convertDimensions(const fvec2& position, const fvec2& size) const;

	fvec2 _parentPosition;
	fvec2 _parentSize;

	const string _id;
	const string _parentId;

	bool _isActive = false;

	vector<shared_ptr<GuiScrollingList>> _scrollingLists;
	vector<shared_ptr<GuiWriteField>> _writeFields;
	vector<shared_ptr<GuiButton>> _buttons;
	vector<shared_ptr<GuiRectangle>> _rectangles;
	vector<shared_ptr<GuiTextField>> _textFields;

	shared_ptr<EngineInterface> _fe3d = nullptr;
};