#pragma warning(disable:6385)
#pragma warning(disable:6386)

#include "image_loader.hpp"
#include "tools.hpp"

using std::make_shared;

shared_ptr<Image> ImageLoader::_loadImage(const string & filePath) const
{
	const auto rootPath = Tools::getRootDirectoryPath();
	const auto fullFilePath = (rootPath + filePath);

	FILE * file = nullptr;

	if(fopen_s(&file, fullFilePath.c_str(), "rb") != 0)
	{
		return nullptr;
	}

	auto header = new unsigned char[HEADER_SIZE];

	for(int index = 0; index < 18; index++)
	{
		header[index] = getc(file);
	}

	unsigned char rawIdLength = (header[0]);
	unsigned char rawColorMap = (header[1]);
	unsigned char rawImageType = (header[2]);
	unsigned short rawOriginX = ((header[9] << 8) | header[8]);
	unsigned short rawOriginY = ((header[11] << 8) | header[10]);
	unsigned short rawWidth = ((header[13] << 8) | header[12]);
	unsigned short rawHeight = ((header[15] << 8) | header[14]);
	unsigned char rawFormat = (header[16]);

	if(rawIdLength != 0)
	{
		return nullptr;
	}

	if(rawColorMap != 0)
	{
		return nullptr;
	}

	if((rawImageType != 2) && (rawImageType != 3))
	{
		return nullptr;
	}

	if((rawOriginX != 0) || (rawOriginY != 0))
	{
		return nullptr;
	}

	if((rawWidth == 0) || (rawHeight == 0))
	{
		return nullptr;
	}

	if((rawFormat != 24) && (rawFormat != 32))
	{
		return nullptr;
	}

	const auto width = static_cast<int>(rawWidth);
	const auto height = static_cast<int>(rawHeight);
	const auto bitsPerPixel = static_cast<int>(rawFormat);
	const auto bytesPerPixel = (bitsPerPixel / 8);
	const auto size = (width * height * bytesPerPixel);
	const auto pixels = new unsigned char[size];

	for(unsigned int y = 0; y < height; y++)
	{
		for(unsigned int x = 0; x < width; x++)
		{
			const auto index = ((y * width * bytesPerPixel) + (x * bytesPerPixel));

			if(bytesPerPixel == 3)
			{
				const auto blue = static_cast<unsigned char>(getc(file));
				const auto green = static_cast<unsigned char>(getc(file));
				const auto red = static_cast<unsigned char>(getc(file));

				pixels[index + 0] = red;
				pixels[index + 1] = green;
				pixels[index + 2] = blue;
			}
			if(bytesPerPixel == 4)
			{
				const auto blue = static_cast<unsigned char>(getc(file));
				const auto green = static_cast<unsigned char>(getc(file));
				const auto red = static_cast<unsigned char>(getc(file));
				const auto alpha = static_cast<unsigned char>(getc(file));

				pixels[index + 0] = red;
				pixels[index + 1] = green;
				pixels[index + 2] = blue;
				pixels[index + 3] = alpha;
			}
		}
	}

	delete[] header;

	fclose(file);

	return make_shared<Image>(pixels, width, height, bitsPerPixel);
}