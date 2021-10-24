#pragma once

#include "mathematics.hpp"

#include <string>

using std::string;

class Tools final
{
public:
	Tools() = delete;

	// Voids
	static void createNewDirectory(const string& directoryPath);
	static void setMainRenderingColor(Vec3 color);

	// Strings
	static const string vec2str(Ivec2 vec);
	static const string vec2str(Vec2 vec);
	static const string vec2str(Vec3 vec);
	static const string vec2str(Vec4 vec);
	static const string getRootDirectory();
	static const string getWinExplorerFilename(const string& startingDirectory, const string& fileType);

	// Vectors
	static const Vec2 convertFromScreenCoords(Ivec2 position);
	static const Ivec2 convertToScreenCoords(Vec2 position);

	// Decimals
	static const float getWindowAspectRatio();

	// Integers
	static const long long getTimeSinceEpochMS();

	// Booleans
	static const bool isDirectoryExisting(const string& directoryPath);
	static const bool isFileExisting(const string& filePath);
};