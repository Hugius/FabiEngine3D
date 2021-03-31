#pragma once

#include "render_buffer.hpp"

#include <string>

using std::string;

class BaseEntity
{
public:
	BaseEntity(const string& ID);
	virtual ~BaseEntity();

	void addRenderBuffer(RenderBuffer* buffer, bool deleteOnDestroy = true);
	void clearRenderBuffers();
	void setVisible(bool value);

	const vector<RenderBuffer*>& getRenderBuffers() const;
	const RenderBuffer* getRenderBuffer(int index) const;
	const RenderBuffer* getRenderBuffer() const;

	const string& getID() const;
	const bool isVisible() const;

private:
	vector<RenderBuffer*> _renderBuffers;
	vector<bool> _renderBufferMemoryManagement;

	string _ID = "ID_NULL";

	bool _visible = true;
};