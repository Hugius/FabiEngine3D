#pragma once

#include "fabi_engine_3d.hpp"
#include "engine_gui_scrollinglist.hpp"
#include "engine_gui_writefield.hpp"
#include "engine_gui_button.hpp"
#include "engine_gui_rectangle.hpp"
#include "engine_gui_textfield.hpp"

class EngineGuiScreen final
{
public:
	EngineGuiScreen(FabiEngine3D& fe3d, const string& parentID, const string& ID, Vec2 position, Vec2 size);

	// Core
	void update(bool hoverable);
	void show();
	void hide();

	// Create
	void createScrollingList(const string& ID, Vec2 position, Vec2 size, Vec3 color, Vec3 buttonColor, Vec3 buttonHoverColor, Vec3 textColor, 
		Vec3 textHoverColor, Vec2 charSize);
	void createWritefield(const string& ID, Vec2 position, Vec2 size, Vec3 color, Vec3 hoverColor, Vec3 textColor, Vec3 textHoverColor, 
		bool noNumbers, bool noCaps, bool noSpecials, bool noLetters, bool minusAllowed);
	void createButton(const string& ID, Vec2 position, Vec2 size, Vec3 color, Vec3 hoverColor, string textContent, Vec3 textColor, Vec3 textHoverColor);
	void createButton(const string& ID, Vec2 position, Vec2 size, const string& texturePath, Vec3 hoverColor);
	void createRectangle(const string& ID, Vec2 position, Vec2 size, Vec3 color, bool isCentered = true);
	void createRectangle(const string& ID, Vec2 position, Vec2 size, const string& texturePath, bool isCentered = true);
	void createTextfield(const string& ID, Vec2 position, Vec2 size, string textContent, Vec3 textColor, bool isCentered = true, bool isDynamic = false);

	// Delete
	void deleteScrollingList(const string& ID);
	void deleteWritefield(const string& ID);
	void deleteButton(const string& ID);
	void deleteRectangle(const string& ID);
	void deleteTextfield(const string& ID);

	// Check
	bool checkScrollingList(const string& ID);
	bool checkWritefield(const string& ID);
	bool checkButton(const string& ID);
	bool checkRectangle(const string& ID);
	bool checkTextfield(const string& ID);

	// Get single
	shared_ptr<EngineGuiScrollingList> getScrollingList(const string& ID);
	shared_ptr<EngineGuiWritefield>    getWritefield(const string& ID);
	shared_ptr<EngineGuiButton>        getButton(const string& ID);
	shared_ptr<EngineGuiRectangle>     getRectangle(const string& ID);
	shared_ptr<EngineGuiTextfield>     getTextfield(const string& ID);

	// Get multiple
	vector<shared_ptr<EngineGuiScrollingList>>& getScrollingLists();
	vector<shared_ptr<EngineGuiWritefield>>&    getWritefields();
	vector<shared_ptr<EngineGuiButton>>&		getButtons();
	vector<shared_ptr<EngineGuiRectangle>>&		getRectangles();
	vector<shared_ptr<EngineGuiTextfield>>&		getTextfields();

	// Miscellaneous
	const string& getID();
	const string& getParentID();
	Vec2 convertPosition(Vec2 position);
	Vec2 convertSize(Vec2 size);

private:
	Vec4 _convertDimensions(Vec2 position, Vec2 size);

	FabiEngine3D& _fe3d;

	Vec2 _parentPosition;
	Vec2 _parentSize;

	const string _ID;
	const string _parentID;

	bool _isActive = false;

	vector<shared_ptr<EngineGuiScrollingList>> _scrollingLists;
	vector<shared_ptr<EngineGuiWritefield>> _writefields;
	vector<shared_ptr<EngineGuiButton>> _buttons;
	vector<shared_ptr<EngineGuiRectangle>> _rectangles;
	vector<shared_ptr<EngineGuiTextfield>> _textfields;
};