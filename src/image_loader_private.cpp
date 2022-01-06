#pragma warning(disable:6385)
#pragma warning(disable:6386)

#include "image_loader.hpp"
#include "logger.hpp"
#include "tools.hpp"

using std::clamp;

shared_ptr<Image> ImageLoader::_loadImage(const string& filePath)
{
	FILE* file = nullptr;
	const auto rootPath = Tools::getRootDirectoryPath();
	const auto fullFilePath = string(rootPath + filePath);
	if(fopen_s(&file, fullFilePath.c_str(), "rb") != 0)
	{
		std::cout << fopen_s(&file, fullFilePath.c_str(), "rb");
		return nullptr;
	}

	auto header = new uint8_t[18];
	for(int i = 0; i < 18; i++)
	{
		header[i] = getc(file);
	}
	std::cout << int(header[0]) << std::endl;
	std::cout << int(header[1]) << std::endl;
	std::cout << int(header[2]) << std::endl;

	unsigned short rawWidth = ((header[13] << 8) | header[12]);
	unsigned short rawHeight = ((header[15] << 8) | header[14]);
	unsigned char rawFormat = (header[16]);

	delete[] header;

	if((rawWidth == 0) || (rawHeight == 0))
	{
		return nullptr;
	}

	if((rawFormat != 8) && (rawFormat != 24) && (rawFormat != 32))
	{
		return nullptr;
	}

	const auto width = static_cast<unsigned int>(rawWidth);
	const auto height = static_cast<unsigned int>(rawHeight);
	const auto bitFormat = static_cast<unsigned int>(rawFormat);
	const auto byteFormat = (bitFormat / 8);
	const auto size = (width * height * byteFormat);
	const auto pixels = new unsigned char[size];

	for(unsigned y = 0; y < height; y++)
	{
		for(unsigned x = 0; x < width; x++)
		{
			const auto index = ((y * width * byteFormat) + (x * byteFormat));

			if(byteFormat == 1)
			{
				pixels[index] = static_cast<unsigned char>(getc(file));
			}
			if(byteFormat == 3)
			{
				auto b = static_cast<unsigned char>(getc(file));
				auto g = static_cast<unsigned char>(getc(file));
				auto r = static_cast<unsigned char>(getc(file));

				pixels[index + 0] = r;
				pixels[index + 1] = g;
				pixels[index + 2] = b;
			}
			if(byteFormat == 4)
			{
				auto b = static_cast<unsigned char>(getc(file));
				auto g = static_cast<unsigned char>(getc(file));
				auto r = static_cast<unsigned char>(getc(file));
				auto a = static_cast<unsigned char>(getc(file));

				pixels[index + 0] = r;
				pixels[index + 1] = g;
				pixels[index + 2] = b;
				pixels[index + 3] = a;
			}
		}
	}

	fclose(file);

	return make_shared<Image>(pixels,
							  static_cast<unsigned int>(width),
							  static_cast<unsigned int>(height),
							  PixelFormat(bitFormat == 8 ? PixelFormat::GRAY : bitFormat == 24 ? PixelFormat::RGB : PixelFormat::RGBA));
}