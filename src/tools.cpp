#include "tools.hpp"

#include <filesystem>
#include <shlobj_core.h>

using std::to_string;
using std::filesystem::copy;
using std::filesystem::copy_file;
using std::filesystem::exists;
using std::filesystem::create_directory;
using std::filesystem::absolute;
using std::filesystem::rename;
using std::filesystem::remove;
using std::filesystem::remove_all;
using std::filesystem::exists;
using std::filesystem::is_directory;
using std::chrono::duration_cast;
using std::chrono::milliseconds;
using std::chrono::system_clock;
using std::filesystem::directory_iterator;
using std::filesystem::copy_options;
using std::error_code;

const bool Tools::isApplicationExported()
{
	return _configuration->isApplicationExported();
}

const bool Tools::isCursorInsideDisplay()
{
	const auto cursorPosition = getCursorPosition();
	const auto displayPosition = _configuration->getDisplayPosition();
	const auto displaySize = _configuration->getDisplaySize();

	if((cursorPosition.x > displayPosition.x) && (cursorPosition.x < (displayPosition.x + displaySize.x)))
	{
		if((cursorPosition.y > displayPosition.y) && (cursorPosition.y < (displayPosition.y + displaySize.y)))
		{
			return true;
		}
	}

	return false;
}

const bool Tools::isCursorInsideWindow()
{
	const auto cursorPosition = getCursorPosition();
	const auto windowSize = _configuration->getWindowSize();

	if((cursorPosition.x > 1) && (cursorPosition.x < (windowSize.x - 1)))
	{
		if((cursorPosition.y > 1) && (cursorPosition.y < (windowSize.y - 1)))
		{
			return true;
		}
	}

	return false;
}

void Tools::setCursorPosition(const ivec2 & value)
{
	POINT point = {};

	point.x = value.x;
	point.y = value.y;

	SetCursorPos(point.x, (_configuration->getWindowSize().y - point.y));
}

void Tools::setCursorType(CursorType type)
{
	switch(type)
	{
		case CursorType::ARROW:
		{
			SetCursor(LoadCursor(nullptr, IDC_ARROW));

			break;
		}
		case CursorType::HAND:
		{
			SetCursor(LoadCursor(nullptr, IDC_HAND));

			break;
		}
	}

	_cursorType = type;
}

void Tools::setCursorVisible(bool value)
{
	if(value)
	{
		while(ShowCursor(true) < 0);
	}
	else
	{
		while(ShowCursor(false) > -1);
	}

}

const vector<string> Tools::getFileNamesFromDirectory(const string & path)
{
	error_code error = {};

	const auto iterator = directory_iterator(path, error);

	if(error.value() != 0)
	{
		return {};
	}

	vector<string> fileNames = {};

	for(const auto & entry : iterator)
	{
		auto entryPath = entry.path().string();

		if(!isDirectoryExisting(entryPath))
		{
			entryPath.erase(0, path.size());

			fileNames.push_back(entryPath);
		}
	}

	return fileNames;
}

const vector<string> Tools::getDirectoryNamesFromDirectory(const string & path)
{
	error_code error = {};

	const auto iterator = directory_iterator(path, error);

	if(error.value() != 0)
	{
		return {};
	}

	vector<string> directoryNames = {};

	for(const auto & entry : iterator)
	{
		auto entryPath = entry.path().string();

		if(isDirectoryExisting(entryPath))
		{
			entryPath.erase(0, path.size());

			directoryNames.push_back(entryPath);
		}
	}

	return directoryNames;
}

const string & Tools::getWindowTitle()
{
	return _configuration->getWindowTitle();
}

const string Tools::getRootDirectoryPath()
{
	char buffer[256];

	size_t len = sizeof(buffer);

	GetModuleFileName(nullptr, buffer, static_cast<DWORD>(len));

	string rootPath = buffer;

	rootPath = absolute(rootPath).string();

	reverse(rootPath.begin(), rootPath.end());

	for(int index = 0; index < rootPath.size(); index++)
	{
		if(rootPath[index] == '\\')
		{
			rootPath = rootPath.substr(index + string("binaries\\").size());

			break;
		}
	}

	reverse(rootPath.begin(), rootPath.end());

	return rootPath;
}

const float Tools::getWindowAspectRatio()
{
	return (static_cast<float>(_configuration->getWindowSize().x) / static_cast<float>(_configuration->getWindowSize().y));
}

const float Tools::getDisplayAspectRatio()
{
	return (static_cast<float>(_configuration->getDisplaySize().x) / static_cast<float>(_configuration->getDisplaySize().y));
}

const long long Tools::getTimeSinceEpochMS()
{
	return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
}

const int Tools::parseInteger(const string & valueString)
{
	if(!isInteger(valueString))
	{
		abort();
	}

	if(valueString[0] == '-')
	{
		if(valueString.size() >= to_string(INT_MIN).size())
		{
			return MIN_STRING_INTEGER;
		}
	}
	else
	{
		if(valueString.size() >= to_string(INT_MAX).size())
		{
			return MAX_STRING_INTEGER;
		}
	}

	return stoi(valueString);
}

const string Tools::chooseWindowsExplorerFile(const string & startingDirectory, const string & fileType)
{
	const auto wasCursorVisible = isCursorVisible();

	OPENFILENAME ofn;
	char pathBuffer[256] = {};
	char titleBuffer[100] = {};

	string filter = fileType;

	filter.push_back('\0');
	filter += "*." + fileType + '\0';

	ZeroMemory(&ofn, sizeof(ofn));

	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = nullptr;
	ofn.lpstrFile = pathBuffer;
	ofn.lpstrFile[0] = '\0';
	ofn.nMaxFile = sizeof(pathBuffer);
	ofn.lpstrFilter = filter.c_str();
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = titleBuffer;
	ofn.lpstrFileTitle[0] = '\0';
	ofn.nMaxFileTitle = sizeof(titleBuffer);
	ofn.lpstrInitialDir = startingDirectory.c_str();
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	setCursorVisible(true);

	GetOpenFileName(&ofn);

	setCursorVisible(wasCursorVisible);

	return ofn.lpstrFile;
}

const string Tools::chooseWindowsExplorerDirectory(const string & startingDirectory)
{
	const auto wasCursorVisible = isCursorVisible();

	BROWSEINFO browseInfo = {};

	browseInfo.ulFlags = (BIF_RETURNONLYFSDIRS | BIF_NEWDIALOGSTYLE);
	browseInfo.lpfn = nullptr;
	browseInfo.lParam = LPARAM(startingDirectory.c_str());

	setCursorVisible(true);

	LPITEMIDLIST pidl = SHBrowseForFolder(&browseInfo);

	setCursorVisible(wasCursorVisible);

	if(pidl != 0)
	{
		char directoryPath[MAX_PATH];

		SHGetPathFromIDList(pidl, directoryPath);

		IMalloc * imalloc = 0;

		if(SUCCEEDED(SHGetMalloc(&imalloc)))
		{
			imalloc->Free(pidl);
			imalloc->Release();
		}

		return directoryPath;
	}

	return "";
}

const string Tools::mergeStrings(const string & firstString, const string & secondString, char delimiter)
{
	return (firstString + delimiter + secondString);
}

const string Tools::mergeStrings(const vector<string> & stringList, char delimiter)
{
	if(stringList.empty())
	{
		return "";
	}

	string result = "";

	for(const auto & value : stringList)
	{
		result += value;
		result += delimiter;
	}

	result.pop_back();

	return result;
}

const pair<string, string> Tools::splitStringIntoTwo(const string & mergedString, char delimiter)
{
	const auto delimiterIndex = mergedString.find(delimiter);

	if(delimiterIndex == string::npos)
	{
		return {"", ""};
	}

	const auto firstString = mergedString.substr(0, delimiterIndex);
	const auto secondString = mergedString.substr(delimiterIndex + 1);

	return {firstString, secondString};
}

const vector<string> Tools::splitStringIntoMultiple(const string & mergedString, char delimiter)
{
	vector<string> result = {};
	string tempString = "";

	for(int index = 0; index < static_cast<int>(mergedString.size()); index++)
	{
		if(mergedString[index] == delimiter)
		{
			result.push_back(tempString);

			tempString = "";
		}
		else
		{
			tempString += mergedString[index];
		}
	}

	result.push_back(tempString);

	return result;
}

const bool Tools::isCursorVisible()
{
	CURSORINFO ci = {};

	ci.cbSize = sizeof(CURSORINFO);

	if(!GetCursorInfo(&ci))
	{
		abort();
	}

	return (ci.flags & CURSOR_SHOWING);
}

const bool Tools::isDirectoryExisting(const string & path)
{
	return (exists(path) && is_directory(path));
}

const bool Tools::isFileExisting(const string & path)
{
	return (exists(path) && !is_directory(path));
}

const bool Tools::createDirectory(const string & path)
{
	if(isDirectoryExisting(path))
	{
		return false;
	}

	create_directory(path);

	return true;
}

const bool Tools::copyDirectory(const string & fromPath, const string & toPath)
{
	error_code error = {};

	copy(fromPath, toPath, copy_options::recursive, error);

	return (error.value() == 0);
}

const bool Tools::copyFile(const string & fromPath, const string & toPath)
{
	error_code error = {};

	copy_file(fromPath, toPath, error);

	return (error.value() == 0);
}

const bool Tools::renameDirectory(const string & oldPath, const string & newPath)
{
	error_code error = {};

	rename(oldPath, newPath, error);

	return (error.value() == 0);
}

const bool Tools::renameFile(const string & oldPath, const string & newPath)
{
	error_code error = {};

	rename(oldPath, newPath, error);

	return (error.value() == 0);
}

const bool Tools::deleteDirectory(const string & path)
{
	error_code error = {};

	remove_all(path, error);

	return (error.value() == 0);
}

const bool Tools::deleteFile(const string & path)
{
	error_code error = {};

	remove(path, error);

	return (error.value() == 0);
}

const bool Tools::isInteger(const string & valueString)
{
	if(valueString.empty())
	{
		return false;
	}

	int startingIndex = 0;

	if(valueString[0] == '-')
	{
		startingIndex = 1;
	}

	for(int index = startingIndex; index < static_cast<int>(valueString.size()); index++)
	{
		if(!isdigit(valueString[index]))
		{
			return false;
		}
	}

	return true;
}

const CursorType Tools::getCursorType()
{
	return _cursorType;
}

const fvec2 Tools::convertPositionRelativeToDisplay(const fvec2 & position)
{
	if(_configuration->isApplicationExported())
	{
		return position;
	}

	const auto windowSize = _configuration->getWindowSize();
	const auto displaySize = _configuration->getDisplaySize();
	const auto displayPosition = _configuration->getDisplayPosition();
	const auto sizeMultiplier = (fvec2(displaySize) / fvec2(windowSize));
	const auto positionMultiplier = (fvec2(displayPosition) / fvec2(windowSize));
	const auto offset = (fvec2(1.0f) - fvec2(((positionMultiplier.x * 2.0f) + sizeMultiplier.x), ((positionMultiplier.y * 2.0f) + sizeMultiplier.y)));

	fvec2 result = position;

	result *= sizeMultiplier;
	result += fvec2(fabsf(offset.x), fabsf(offset.y));

	return result;
}

const fvec2 Tools::convertPositionRelativeFromDisplay(const fvec2 & position)
{
	if(_configuration->isApplicationExported())
	{
		return position;
	}

	const auto windowSize = _configuration->getWindowSize();
	const auto displaySize = _configuration->getDisplaySize();
	const auto displayPosition = _configuration->getDisplayPosition();
	const auto sizeMultiplier = (fvec2(displaySize) / fvec2(windowSize));
	const auto positionMultiplier = (fvec2(displayPosition) / fvec2(windowSize));
	const auto invertedSizeMultiplier = fvec2(windowSize) / fvec2(displaySize);
	const auto invertedPositionMultiplier = (fvec2(windowSize) / fvec2(displayPosition));
	const auto offset = (fvec2(1.0f) - fvec2(((positionMultiplier.x * 2.0f) + sizeMultiplier.x), ((positionMultiplier.y * 2.0f) + sizeMultiplier.y)));

	fvec2 result = position;

	result -= fvec2(fabsf(offset.x), fabsf(offset.y));
	result *= invertedSizeMultiplier;

	return result;
}

const fvec2 Tools::convertSizeRelativeToDisplay(const fvec2 & size)
{
	if(_configuration->isApplicationExported())
	{
		return size;
	}

	const auto sizeMultiplier = (fvec2(_configuration->getDisplaySize()) / fvec2(_configuration->getWindowSize()));

	fvec2 result = size;

	result *= sizeMultiplier;

	return result;
}

const fvec2 Tools::convertSizeRelativeFromDisplay(const fvec2 & size)
{
	if(!_configuration->isApplicationExported())
	{
		return size;
	}

	const auto sizeMultiplier = (fvec2(_configuration->getDisplaySize()) / fvec2(_configuration->getWindowSize()));

	fvec2 result = size;

	result /= sizeMultiplier;

	return result;
}

const fvec2 Tools::convertToNdc(const ivec2 & position)
{
	const auto windowSize = _configuration->getWindowSize();
	const auto x = (static_cast<float>(position.x) / static_cast<float>(windowSize.x));
	const auto y = (static_cast<float>(position.y) / static_cast<float>(windowSize.y));

	auto ndc = fvec2(x, y);

	ndc.x *= 2.0f;
	ndc.y *= 2.0f;
	ndc.x -= 1.0f;
	ndc.y -= 1.0f;

	return ndc;
}

const ivec2 Tools::convertFromNdc(const fvec2 & position)
{
	auto ndc = position;

	ndc.x += 1.0f;
	ndc.y += 1.0f;
	ndc.x *= 0.5f;
	ndc.y *= 0.5f;

	const auto windowSize = _configuration->getWindowSize();
	const auto x = (ndc.x * static_cast<float>(windowSize.x));
	const auto y = (ndc.y * static_cast<float>(windowSize.y));

	return ivec2(static_cast<int>(x), static_cast<int>(y));
}

const ivec2 Tools::getCursorPosition()
{
	POINT point = {};

	GetCursorPos(&point);

	const auto monitorSize = getMonitorSize();
	const auto windowSize = getWindowSize();
	const auto cursorOffset = ((monitorSize - windowSize) / 2);
	const auto cursorPosition = ivec2(point.x, (monitorSize.y - point.y));

	return (cursorPosition - cursorOffset);
}

const ivec2 Tools::getMonitorSize()
{
	RECT rectangle = {};

	GetWindowRect(GetDesktopWindow(), &rectangle);

	return ivec2(rectangle.right, rectangle.bottom);
}

const ivec2 & Tools::getWindowSize()
{
	return _configuration->getWindowSize();
}

const ivec2 & Tools::getDisplaySize()
{
	return _configuration->getDisplaySize();
}

const ivec2 & Tools::getDisplayPosition()
{
	return _configuration->getDisplayPosition();
}