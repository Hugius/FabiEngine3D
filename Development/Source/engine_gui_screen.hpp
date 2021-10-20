#pragma once

#include "fe3d.hpp"
#include "engine_gui_scrolling_list.hpp"
#include "engine_gui_write_field.hpp"
#include "engine_gui_button.hpp"
#include "engine_gui_rectangle.hpp"
#include "engine_gui_text_field.hpp"

class EngineGuiScreen final
{
public:
	EngineGuiScreen(FabiEngine3D& fe3d, const string& parentID, const string& ID, Vec2 position, Vec2 size);

	// Voids
	void update(bool hoverable);
	void show();
	void hide();
	void createScrollingList(const string& ID, Vec2 position, Vec2 size, Vec3 color, Vec3 buttonColor, Vec3 buttonHoverColor, Vec3 textColor, Vec3 textHoverColor, Vec2 charSize);
	void createWriteField(const string& ID, Vec2 position, Vec2 size, Vec3 color, Vec3 hoverColor, Vec3 textColor, Vec3 textHoverColor, bool noNumbers, bool noCaps, bool noSpecials, bool noLetters, bool minusAllowed);
	void createButton(const string& ID, Vec2 position, Vec2 size, Vec3 color, Vec3 hoverColor, string textContent, Vec3 textColor, Vec3 textHoverColor);
	void createButton(const string& ID, Vec2 position, Vec2 size, const string& texturePath, Vec3 hoverColor);
	void createRectangle(const string& ID, Vec2 position, Vec2 size, Vec3 color, bool isCentered = true);
	void createRectangle(const string& ID, Vec2 position, Vec2 size, const string& texturePath, bool isCentered = true);
	void createTextField(const string& ID, Vec2 position, Vec2 size, string textContent, Vec3 textColor, bool isCentered = true, bool isDynamic = false);
	void deleteScrollingList(const string& ID);
	void deleteWriteField(const string& ID);
	void deleteButton(const string& ID);
	void deleteRectangle(const string& ID);
	void deleteTextField(const string& ID);

	// GUI elements
	shared_ptr<EngineGuiScrollingList> getScrollingList(const string& ID);
	shared_ptr<EngineGuiWriteField> getWriteField(const string& ID);
	shared_ptr<EngineGuiButton> getButton(const string& ID);
	shared_ptr<EngineGuiRectangle> getRectangle(const string& ID);
	shared_ptr<EngineGuiTextField> getTextField(const string& ID);
	vector<shared_ptr<EngineGuiScrollingList>>& getScrollingLists();
	vector<shared_ptr<EngineGuiWriteField>>& getWriteFields();
	vector<shared_ptr<EngineGuiButton>>& getButtons();
	vector<shared_ptr<EngineGuiRectangle>>& getRectangles();
	vector<shared_ptr<EngineGuiTextField>>& getTextFields();

	// Strings
	const string& getID();
	const string& getParentID();

	// Vectors
	Vec2 convertPosition(Vec2 position);
	Vec2 convertSize(Vec2 size);

	// Booleans
	bool isScrollingListExisting(const string& ID);
	bool isWriteFieldExisting(const string& ID);
	bool isButtonExisting(const string& ID);
	bool isRectangleExisting(const string& ID);
	bool isTextFieldExisting(const string& ID);

private:
	// Instances
	FabiEngine3D& _fe3d;

	// GUI elements
	vector<shared_ptr<EngineGuiScrollingList>> _scrollingLists;
	vector<shared_ptr<EngineGuiWriteField>> _writeFields;
	vector<shared_ptr<EngineGuiButton>> _buttons;
	vector<shared_ptr<EngineGuiRectangle>> _rectangles;
	vector<shared_ptr<EngineGuiTextField>> _textFields;

	// Vectors
	Vec4 _convertDimensions(Vec2 position, Vec2 size);
	Vec2 _parentPosition;
	Vec2 _parentSize;

	// Strings
	const string _ID;
	const string _parentID;

	// Booleans
	bool _isActive = false;
};