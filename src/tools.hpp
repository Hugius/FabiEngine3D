#pragma once

#include "mathematics.hpp"
#include "configuration.hpp"
#include "cursor_type.hpp"

#include <string>

using std::string;
using std::pair;
using std::unique_ptr;
using std::make_unique;

class Tools final
{
public:
	Tools() = delete;

	static void setCursorVisible(bool value);
	static void setCursorPosition(const ivec2 & value);
	static void setCursorType(CursorType type);

	static const vector<string> getFileNamesFromDirectory(const string & path);
	static const vector<string> getDirectoryNamesFromDirectory(const string & path);
	static const vector<string> splitStringIntoMultiple(const string & mergedString, char delimiter);

	static const pair<string, string> splitStringIntoTwo(const string & mergedString, char delimiter);

	static const string & getWindowTitle();
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

	static const ivec2 convertFromNdc(const fvec2 & position);
	static const ivec2 getCursorPosition();
	static const ivec2 getMonitorSize();
	static const ivec2 & getWindowSize();
	static const ivec2 & getDisplaySize();
	static const ivec2 & getDisplayPosition();

	static const float getWindowAspectRatio();
	static const float getDisplayAspectRatio();

	static const long long getTimeSinceEpochMS();

	static const int parseInteger(const string & valueString);

	static const bool isApplicationExported();
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
	static const bool isInteger(const string & valueString);

	static const CursorType getCursorType();

private:
	static inline unique_ptr<Configuration> _configuration = make_unique<Configuration>();

	static inline constexpr int MIN_STRING_INTEGER = -999999999;
	static inline constexpr int MAX_STRING_INTEGER = 999999999;

	static inline CursorType _cursorType = CursorType::ARROW;
};