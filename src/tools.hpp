#pragma once

#include "mathematics.hpp"

#include <string>

using std::string;

class Tools final
{
public:
	Tools() = delete;

	static void createDirectory(const string& path);
	static void copyDirectory(const string& fromPath, const string& toPath);
	static void copyFile(const string& fromPath, const string& toPath);
	static void renameDirectory(const string& oldPath, const string& newPath);
	static void renameFile(const string& oldPath, const string& newPath);
	static void deleteDirectory(const string& path);
	static void deleteFile(const string& path);

	static const vector<string> getFilesFromDirectory(const string& path);
	static const vector<string> getDirectoriesFromDirectory(const string& path);
	static const string vec2str(ivec2 vec);
	static const string vec2str(fvec2 vec);
	static const string vec2str(fvec3 vec);
	static const string vec2str(fvec4 vec);
	static const string getRootDirectoryPath();
	static const string chooseExplorerFile(const string& startingDirectory, const string& fileType);
	static const string chooseExplorerDirectory(const string& startingDirectory);

	static const fvec2 convertFromScreenCoords(ivec2 position);
	static const ivec2 convertToScreenCoords(fvec2 position);
	static const fvec2 _calculateMinViewportPosition();
	static const fvec2 _calculateMaxViewportPosition();
	static const fvec2 _convertPositionToViewport(fvec2 position);
	static const fvec2 _convertPositionFromViewport(fvec2 position);
	static const fvec2 _convertSizeToViewport(fvec2 size);
	static const fvec2 _convertSizeFromViewport(fvec2 size);

	static const float getWindowAspectRatio();

	static const long long getTimeSinceEpochMS();

	static const bool isDirectoryExisting(const string& path);
	static const bool isFileExisting(const string& path);
};