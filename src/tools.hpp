#pragma once

#include "mathematics.hpp"

#include <string>

using std::string;
using std::pair;

class Tools final
{
public:
	Tools() = delete;

	static void setCursorPosition(const ivec2 & value);
	static void setCursorVisible(bool value);

	static const vector<string> getFileNamesFromDirectory(const string & path);
	static const vector<string> getDirectoryNamesFromDirectory(const string & path);
	static const vector<string> splitStringIntoMultiple(const string & mergedString, char delimiter);

	static const pair<string, string> splitStringIntoTwo(const string & mergedString, char delimiter);

	static const string getRootDirectoryPath();
	static const string chooseExplorerFile(const string & startingDirectory, const string & fileType);
	static const string chooseExplorerDirectory(const string & startingDirectory);
	static const string mergeStrings(const string & firstString, const string & secondString, char delimiter);
	static const string mergeStrings(const vector<string> & stringList, char delimiter);

	static const fvec2 convertToNdc(const ivec2 & position);
	static const fvec2 convertPositionRelativeToDisplay(const fvec2 & position);
	static const fvec2 convertPositionRelativeFromDisplay(const fvec2 & position);
	static const fvec2 convertSizeRelativeToDisplay(const fvec2 & size);
	static const fvec2 convertSizeRelativeFromDisplay(const fvec2 & size);
	static const fvec2 getMinViewportPosition();
	static const fvec2 getMaxViewportPosition();

	static const ivec2 convertFromNdc(const fvec2 & position);
	static const ivec2 getCursorPosition();
	static const ivec2 getMonitorSize();

	static const float getWindowAspectRatio();

	static const long long getTimeSinceEpochMS();

	static const int parseInteger(const string & valueString);

	static const bool isCursorInsideDisplay();
	static const bool isCursorInsideWindow();
	static const bool isCursorVisible();
	static const bool isDirectoryExisting(const string & path);
	static const bool isFileExisting(const string & path);
	static const bool createDirectory(const string & path);
	static const bool copyDirectory(const string & fromPath, const string & toPath);
	static const bool copyFile(const string & fromPath, const string & toPath);
	static const bool renameDirectory(const string & oldPath, const string & newPath);
	static const bool renameFile(const string & oldPath, const string & newPath);
	static const bool deleteDirectory(const string & path);
	static const bool deleteFile(const string & path);
};