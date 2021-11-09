#pragma once

#include "mathematics.hpp"

#include <string>

using std::string;

class Tools final
{
public:
	Tools() = delete;

	// Voids
	static void setMainRenderingColor(Vec3 color);
	static void createDirectory(const string& path);
	static void copyDirectory(const string& fromPath, const string& toPath);
	static void copyFile(const string& fromPath, const string& toPath);
	static void deleteDirectory(const string& path);
	static void deleteFile(const string& path);

	// Strings
	static const vector<string> getFilesFromDirectory(const string& path);
	static const vector<string> getDirectoriesFromDirectory(const string& path);
	static const string vec2str(Ivec2 vec);
	static const string vec2str(Vec2 vec);
	static const string vec2str(Vec3 vec);
	static const string vec2str(Vec4 vec);
	static const string getRootDirectoryPath();
	static const string chooseExplorerFile(const string& startingDirectory, const string& fileType);
	static const string chooseExplorerDirectory(const string& startingDirectory);
	static const string convertToAbsolutePath(const string& path);

	// Vectors
	static const Vec2 convertFromScreenCoords(Ivec2 position);
	static const Ivec2 convertToScreenCoords(Vec2 position);

	// Decimals
	static const float getWindowAspectRatio();

	// Integers
	static const long long getTimeSinceEpochMS();

	// Booleans
	static const bool isDirectoryExisting(const string& path);
	static const bool isFileExisting(const string& path);
};