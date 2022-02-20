#pragma once

#include "mathematics.hpp"

#include <string>
#include <utility>

using std::string;
using std::pair;

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
	static const string vec2str(const ivec2& vec);
	static const string vec2str(const fvec2& vec);
	static const string vec2str(const fvec3& vec);
	static const string vec2str(const fvec4& vec);
	static const string getRootDirectoryPath();
	static const string chooseExplorerFile(const string& startingDirectory, const string& fileType);
	static const string chooseExplorerDirectory(const string& startingDirectory);
	static const string mergeStrings(const string& firstString, const string& secondString, char delimiter);
	static const string mergeStrings(const vector<string>& stringList, char delimiter);
	static const pair<string, string> splitStringIntoTwo(const string& mergedString, char delimiter);
	static const vector<string> splitStringIntoMultiple(const string& mergedString, char delimiter);

	static const fvec2 convertToNdc(const ivec2& position);
	static const fvec2 convertPositionRelativeToDisplay(const fvec2& position);
	static const fvec2 convertPositionRelativeFromDisplay(const fvec2& position);
	static const fvec2 convertSizeRelativeToDisplay(const fvec2& size);
	static const fvec2 convertSizeRelativeFromDisplay(const fvec2& size);
	static const fvec2 getMinViewportPosition();
	static const fvec2 getMaxViewportPosition();

	static const ivec2 convertFromNdc(const fvec2& position);

	static const float getWindowAspectRatio();

	static const long long getTimeSinceEpochMS();

	static const bool isDirectoryExisting(const string& path);
	static const bool isFileExisting(const string& path);
};