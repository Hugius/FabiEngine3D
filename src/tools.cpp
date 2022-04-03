#include "tools.hpp"
#include "tools.hpp"
#include "tools.hpp"
#include "tools.hpp"
#include "configuration.hpp"
#include "logger.hpp"

#include <filesystem>
#include <windows.h>
#include <direct.h>
#include <shlobj_core.h>

using std::max;
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

const vector<string> Tools::getFileNamesFromDirectory(const string & path)
{
	error_code error = {};
	const auto iterator = directory_iterator(path, error);

	if(error.value() != 0)
	{
		return {};
	}

	vector<string> fileNames;
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

	vector<string> directoryNames;
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

const string Tools::getRootDirectoryPath()
{
	char buffer[256];
	size_t len = sizeof(buffer);

	GetModuleFileName(nullptr, buffer, static_cast<DWORD>(len));

	string rootPath = buffer;

	rootPath = absolute(rootPath).string();

	rootPath = rootPath.substr(0, (rootPath.size() - string("binaries\\fe3d.exe").size()));

	return rootPath;
}

const float Tools::getWindowAspectRatio()
{
	return (static_cast<float>(Configuration::getInst().getWindowSize().x) / static_cast<float>(Configuration::getInst().getWindowSize().y));
}

const long long Tools::getTimeSinceEpochMS()
{
	return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
}

const unsigned int Tools::parseUnsignedInteger(const string & valueString)
{
	if(valueString.empty())
	{
		abort();
	}

	for(unsigned int index = 0; index < valueString.size(); index++)
	{
		if(!isdigit(valueString[index]))
		{
			abort();
		}
	}

	return static_cast<unsigned int>(stoi(valueString));
}

const int Tools::parseSignedInteger(const string & valueString)
{
	if(valueString.empty())
	{
		abort();
	}

	unsigned int startingIndex = 0;

	if(valueString[0] == '-')
	{
		startingIndex = 1;
	}

	for(unsigned int index = startingIndex; index < valueString.size(); index++)
	{
		if(!isdigit(valueString[index]))
		{
			abort();
		}
	}

	return stoi(valueString);
}

const string Tools::chooseExplorerFile(const string & startingDirectory, const string & fileType)
{
	string filter = fileType;
	filter.push_back('\0');
	filter += "*." + fileType + '\0';

	OPENFILENAME ofn;
	char pathBuffer[256] = {};
	char titleBuffer[100] = {};
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
	GetOpenFileName(&ofn);

	return ofn.lpstrFile;
}

const string Tools::chooseExplorerDirectory(const string & startingDirectory)
{
	BROWSEINFO browseInfo = {};
	browseInfo.ulFlags = (BIF_RETURNONLYFSDIRS | BIF_NEWDIALOGSTYLE);
	browseInfo.lpfn = nullptr;
	browseInfo.lParam = LPARAM(startingDirectory.c_str());

	LPITEMIDLIST pidl = SHBrowseForFolder(&browseInfo);

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
	vector<string> result;

	string tempString = "";

	for(unsigned int index = 0; index < mergedString.size(); index++)
	{
		if(mergedString[index] == delimiter)
		{
			if(index == 0)
			{
				continue;
			}
			else
			{
				result.push_back(tempString);
				tempString = "";
			}
		}
		else if(index == (mergedString.size() - 1))
		{
			tempString += mergedString[index];
			result.push_back(tempString);
		}
		else
		{
			tempString += mergedString[index];
		}
	}

	return result;
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

const fvec2 Tools::getMinViewportPosition()
{
	if(Configuration::getInst().isApplicationExported())
	{
		return fvec2(0.0f);
	}

	const auto rawPosition = Configuration::getInst().getDisplayPosition();
	const auto result = convertToNdc(rawPosition);

	return result;
}

const fvec2 Tools::getMaxViewportPosition()
{
	if(Configuration::getInst().isApplicationExported())
	{
		return fvec2(1.0f);
	}

	const auto rawPosition = (Configuration::getInst().getDisplayPosition() + Configuration::getInst().getDisplaySize());
	const auto result = convertToNdc(rawPosition);

	return result;
}

const fvec2 Tools::convertPositionRelativeToDisplay(const fvec2 & position)
{
	if(Configuration::getInst().isApplicationExported())
	{
		return position;
	}

	const auto sizeMultiplier = (fvec2(Configuration::getInst().getDisplaySize()) / fvec2(Configuration::getInst().getWindowSize()));
	const auto positionMultiplier = (fvec2(Configuration::getInst().getDisplayPosition()) / fvec2(Configuration::getInst().getWindowSize()));
	const auto offset = (fvec2(1.0f) - fvec2(((positionMultiplier.x * 2.0f) + sizeMultiplier.x), ((positionMultiplier.y * 2.0f) + sizeMultiplier.y)));

	fvec2 result = position;
	result *= sizeMultiplier;
	result += fvec2(fabsf(offset.x), fabsf(offset.y));

	return result;
}

const fvec2 Tools::convertPositionRelativeFromDisplay(const fvec2 & position)
{
	if(Configuration::getInst().isApplicationExported())
	{
		return position;
	}

	const auto sizeMultiplier = (fvec2(Configuration::getInst().getDisplaySize()) / fvec2(Configuration::getInst().getWindowSize()));
	const auto positionMultiplier = (fvec2(Configuration::getInst().getDisplayPosition()) / fvec2(Configuration::getInst().getWindowSize()));
	const auto invertedSizeMultiplier = fvec2(Configuration::getInst().getWindowSize()) / fvec2(Configuration::getInst().getDisplaySize());
	const auto invertedPositionMultiplier = (fvec2(Configuration::getInst().getWindowSize()) / fvec2(Configuration::getInst().getDisplayPosition()));
	const auto offset = (fvec2(1.0f) - fvec2(((positionMultiplier.x * 2.0f) + sizeMultiplier.x), ((positionMultiplier.y * 2.0f) + sizeMultiplier.y)));

	fvec2 result = position;
	result -= fvec2(fabsf(offset.x), fabsf(offset.y));
	result *= invertedSizeMultiplier;

	return result;
}

const fvec2 Tools::convertSizeRelativeToDisplay(const fvec2 & size)
{
	if(Configuration::getInst().isApplicationExported())
	{
		return size;
	}

	const auto sizeMultiplier = (fvec2(Configuration::getInst().getDisplaySize()) / fvec2(Configuration::getInst().getWindowSize()));

	fvec2 result = size;
	result *= sizeMultiplier;

	return result;
}

const fvec2 Tools::convertSizeRelativeFromDisplay(const fvec2 & size)
{
	if(!Configuration::getInst().isApplicationExported())
	{
		return size;
	}

	const auto sizeMultiplier = (fvec2(Configuration::getInst().getDisplaySize()) / fvec2(Configuration::getInst().getWindowSize()));

	fvec2 result = size;
	result /= sizeMultiplier;

	return result;
}

const fvec2 Tools::convertToNdc(const ivec2 & position)
{
	const auto x = (static_cast<float>(position.x) / static_cast<float>(Configuration::getInst().getWindowSize().x));
	const auto y = (static_cast<float>(position.y) / static_cast<float>(Configuration::getInst().getWindowSize().y));

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

	const auto x = (ndc.x * static_cast<float>(Configuration::getInst().getWindowSize().x));
	const auto y = (ndc.y * static_cast<float>(Configuration::getInst().getWindowSize().y));

	return ivec2(static_cast<int>(x), static_cast<int>(y));
}