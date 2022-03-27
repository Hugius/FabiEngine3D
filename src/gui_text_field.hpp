#pragma once

#include "engine_interface.hpp"

class GuiTextField final
{
public:
	GuiTextField(shared_ptr<EngineInterface> fe3d, const string & id, const string & parentId, const fvec2 & position, const fvec2 & size, const string & textContent, const fvec3 & color, bool isCentered);
	~GuiTextField();

	void setTextContent(const string & value);
	void setVisible(bool value);
	void setColor(const fvec3 & value);
	void setPosition(const fvec2 & value);
	void setSize(const fvec2 & value);
	void setOpacity(float value);
	void setMinPosition(const fvec2 & value);
	void setMaxPosition(const fvec2 & value);

	const string & getId() const;
	const string & getParentId() const;
	const string & getEntityId() const;
	const string & getTextContent() const;

	const fvec3 & getColor() const;

	const fvec2 & getPosition() const;
	const fvec2 & getSize() const;

	const bool isVisible() const;

private:
	static inline const string FONT_MAP_PATH = "engine\\assets\\image\\font_map\\font.tga";

	const string _id;
	const string _parentId;
	const string _entityId;

	shared_ptr<EngineInterface> _fe3d = nullptr;
};