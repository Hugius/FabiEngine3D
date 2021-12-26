#pragma once

#include "image_entity.hpp"
#include "render_buffer.hpp"

#include <memory>

using std::shared_ptr;

class TextEntity final : public ImageEntity
{
public:
	using ImageEntity::ImageEntity;

	void setContent(const string& value);
	void setFontPath(const string& value);

	const string& getContent() const;
	const string& getFontPath() const;

private:
	string _content = "";
	string _fontPath = "";
};