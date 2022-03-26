#pragma once

#include "engine_interface.hpp"

class GuiQuadField
{
public:
	GuiQuadField(shared_ptr<EngineInterface> fe3d, const string & parentId, const string & id, const fvec2 & position, const fvec2 & size, const fvec3 & color, bool isCentered);
	GuiQuadField(shared_ptr<EngineInterface> fe3d, const string & parentId, const string & id, const fvec2 & position, const fvec2 & size, const string & texturePath, bool isCentered);
	~GuiQuadField();

	virtual void setVisible(bool value);
	void setColor(const fvec3 & value);
	void setPosition(const fvec2 & value);
	void setSize(const fvec2 & value);
	void setOpacity(float value);

	const string & getId() const;
	const string & getParentId() const;

	const fvec3 & getColor() const;

	const fvec2 & getPosition() const;
	const fvec2 & getSize() const;

	const bool isVisible() const;

protected:
	const string _id;
	const string _parentId;
	const string _entityId;

	shared_ptr<EngineInterface> _fe3d = nullptr;
};