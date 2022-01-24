#pragma once

#include "engine_interface.hpp"

class GuiTextField final
{
public:
	GuiTextField(shared_ptr<EngineInterface> fe3d, const string& parentId, const string& id, const fvec2& position, const fvec2& size, const string& textContent, const fvec3& color, bool isCentered);
	~GuiTextField();

	void setVisible(bool isVisible);
	void changeTextContent(const string& content);
	void updateInitialPosition();
	void updateInitialSize();
	void updateInitialColor();

	const string& getId() const;
	const string& getEntityId() const;
	const string& getParentId() const;

	const fvec3& getInitialColor() const;

	const fvec2& getInitialPosition() const;
	const fvec2& getInitialSize() const;

private:
	const string _id;
	const string _entityId;
	const string _parentId;
	static inline const string FONT_MAP_PATH = "engine\\assets\\image\\font_map\\font.tga";

	fvec3 _initialColor;

	fvec2 _initialPosition;
	fvec2 _initialSize;

	shared_ptr<EngineInterface> _fe3d = nullptr;
};