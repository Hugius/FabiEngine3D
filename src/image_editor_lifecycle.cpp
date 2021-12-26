#include "image_editor.hpp"
#include "left_viewport_controller.hpp"
#include "configuration.hpp"

using VPC = BaseViewportController;
using LVPC = LeftViewportController;

#define TW(text) VPC::calculateTextWidth(text, CW)

ImageEditor::ImageEditor(FabiEngine3D& fe3d, GuiManager& gui)
	:
	_fe3d(fe3d),
	_gui(gui)
{

}

void ImageEditor::load()
{
	_loadGUI();

	_fe3d.camera_reset();
	_fe3d.camera_setYaw(270.0f);

	_fe3d.billboard_create(PREVIEW_BILLBOARD_ID);
	_fe3d.billboard_setPosition(PREVIEW_BILLBOARD_ID, PREVIEW_BILLBOARD_POSITION);
	_fe3d.billboard_setVisible(PREVIEW_BILLBOARD_ID, false);

	_gui.getOverlay()->createTextField("imageID", fvec2(0.0f, 0.85f), fvec2(0.5f, 0.1f), "", fvec3(0.0f), true);

	_isEditorLoaded = true;
}

void ImageEditor::unload()
{
	for(const auto& ID : _loadedImageIDs)
	{
		_fe3d.image_delete(ID);
	}

	_unloadGUI();

	_fe3d.billboard_delete(PREVIEW_BILLBOARD_ID);

	_gui.getOverlay()->deleteTextField("imageID");

	_loadedImageIDs.clear();
	_currentImageID = "";
	_hoveredImageID = "";
	_isEditorLoaded = false;
	_isCreatingImage = false;
	_isChoosingImage = false;
	_isDeletingImage = false;
}

void ImageEditor::_loadGUI()
{
	auto leftWindow = _gui.getViewport("left")->getWindow("main");

	auto positions = VPC::calculateButtonPositions(4, CH);
	leftWindow->createScreen("imageEditorMenuMain");
	leftWindow->getScreen("imageEditorMenuMain")->createButton("create", fvec2(0.0f, positions[0]), fvec2(TW("Create Image"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Create Image", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);
	leftWindow->getScreen("imageEditorMenuMain")->createButton("edit", fvec2(0.0f, positions[1]), fvec2(TW("Edit Image"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Edit Image", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);
	leftWindow->getScreen("imageEditorMenuMain")->createButton("delete", fvec2(0.0f, positions[2]), fvec2(TW("Delete Image"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Delete Image", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);
	leftWindow->getScreen("imageEditorMenuMain")->createButton("back", fvec2(0.0f, positions[3]), fvec2(TW("Go Back"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go Back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);

	positions = VPC::calculateButtonPositions(2, CH);
	leftWindow->createScreen("imageEditorMenuChoice");
	leftWindow->getScreen("imageEditorMenuChoice")->createButton("diffuseMap", fvec2(0.0f, positions[0]), fvec2(TW("Diffuse Map"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Diffuse Map", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);
	leftWindow->getScreen("imageEditorMenuChoice")->createButton("back", fvec2(0.0f, positions[1]), fvec2(TW("Go Back"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go Back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);
}

void ImageEditor::_unloadGUI()
{
	_gui.getViewport("left")->getWindow("main")->deleteScreen("imageEditorMenuMain");
	_gui.getViewport("left")->getWindow("main")->deleteScreen("imageEditorMenuChoice");
}

void ImageEditor::update()
{
	if(_isEditorLoaded)
	{
		_updateMainMenu();
	}
	if(_isEditorLoaded)
	{
		_updateChoiceMenu();
	}
	if(_isEditorLoaded)
	{
		_updateImageCreating();
	}
	if(_isEditorLoaded)
	{
		_updateImageChoosing();
	}
	if(_isEditorLoaded)
	{
		_updateImageDeleting();
	}
}