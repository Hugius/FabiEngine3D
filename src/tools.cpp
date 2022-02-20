#include "tools.hpp"
#include "tools.hpp"
#include "tools.hpp"
#include "configuration.hpp"
#include "logger.hpp"

#include <filesystem>
#include <windows.h>
#include <direct.h>
#include <shlobj_core.h>

using std::to_string;
using std::make_pair;
using std::filesystem::exists;
using std::filesystem::create_directory;
using std::filesystem::absolute;
using std::filesystem::rename;
using std::filesystem::remove;
using std::filesystem::remove_all;
using std::filesystem::exists;
using std::filesystem::is_directory;
using std::filesystem::directory_iterator;
using std::chrono::duration_cast;
using std::chrono::milliseconds;
using std::chrono::system_clock;

const vector<string> Tools::getFilesFromDirectory(const string& path)
{
	if(!isDirectoryExisting(path))
	{
		abort();
	}

	vector<string> fileNames;
	for(const auto& entry : directory_iterator(path))
	{
		string filePath = entry.path().string();
		filePath.erase(0, path.size());
		fileNames.push_back(filePath);
	}
	return fileNames;
}

const vector<string> Tools::getDirectoriesFromDirectory(const string& path)
{
	if(!isDirectoryExisting(path))
	{
		abort();
	}

	vector<string> directoryNames;
	for(const auto& entry : directory_iterator(path))
	{
		string directoryPath = entry.path().string();

		if(isDirectoryExisting(directoryPath))
		{
			directoryPath.erase(0, path.size());
			directoryNames.push_back(directoryPath);
		}
	}
	return directoryNames;
}

const string Tools::vec2str(const ivec2& vec)
{
	return (to_string(vec.x) + " " + to_string(vec.y));
}

const string Tools::vec2str(const fvec2& vec)
{
	return (to_string(vec.x) + " " + to_string(vec.y));
}

const string Tools::vec2str(const fvec3& vec)
{
	return (to_string(vec.x) + " " + to_string(vec.y) + " " + to_string(vec.z));
}

const string Tools::vec2str(const fvec4& vec)
{
	return (to_string(vec.x) + " " + to_string(vec.y) + " " + to_string(vec.z) + " " + to_string(vec.w));
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
	return (static_cast<float>(Config::getInst().getWindowSize().x) / static_cast<float>(Config::getInst().getWindowSize().y));
}

const long long Tools::getTimeSinceEpochMS()
{
	return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
}

const string Tools::chooseExplorerFile(const string& startingDirectory, const string& fileType)
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

const string Tools::chooseExplorerDirectory(const string& startingDirectory)
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

		IMalloc* imalloc = 0;
		if(SUCCEEDED(SHGetMalloc(&imalloc)))
		{
			imalloc->Free(pidl);
			imalloc->Release();
		}

		return directoryPath;
	}

	return "";
}

const string Tools::mergeStrings(const string& firstString, const string& secondString, char delimiter)
{
	return (firstString + delimiter + secondString);
}

const pair<string, string> Tools::splitString(const string& mergedString, char delimiter)
{
	const auto delimiterIndex = mergedString.find(delimiter);

	if(delimiterIndex == string::npos)
	{
		return make_pair("", "");
	}

	const auto firstString = mergedString.substr(0, delimiterIndex);
	const auto secondString = mergedString.substr(delimiterIndex + 1);

	return make_pair(firstString, secondString);
}

const bool Tools::isDirectoryExisting(const string& path)
{
	return (exists(path) && is_directory(path));
}

const bool Tools::isFileExisting(const string& path)
{
	return (exists(path) && !is_directory(path));
}

void Tools::createDirectory(const string& path)
{
	create_directory(path);
}

void Tools::copyDirectory(const string& fromPath, const string& toPath)
{
	if(!isDirectoryExisting(fromPath))
	{
		abort();
	}

	using namespace std;
	filesystem::copy(fromPath, toPath, filesystem::copy_options::recursive);
}

void Tools::copyFile(const string& fromPath, const string& toPath)
{
	if(!isFileExisting(fromPath))
	{
		abort();
	}

	using namespace std;
	filesystem::copy_file(fromPath, toPath);
}

void Tools::renameDirectory(const string& oldPath, const string& newPath)
{
	if(!isDirectoryExisting(oldPath))
	{
		abort();
	}

	rename(oldPath, newPath);
}

void Tools::renameFile(const string& oldPath, const string& newPath)
{
	if(!isFileExisting(oldPath))
	{
		abort();
	}

	rename(oldPath, newPath);
}

void Tools::deleteDirectory(const string& path)
{
	if(!isDirectoryExisting(path))
	{
		abort();
	}

	remove_all(path);
}

void Tools::deleteFile(const string& path)
{
	if(!isFileExisting(path))
	{
		abort();
	}

	remove(path);
}

const fvec2 Tools::getMinViewportPosition()
{
	if(Config::getInst().isApplicationExported())
	{
		return fvec2(0.0f);
	}

	const auto rawPosition = Config::getInst().getDisplayPosition();
	const auto result = convertToNdc(rawPosition);

	return result;
}

const fvec2 Tools::getMaxViewportPosition()
{
	if(Config::getInst().isApplicationExported())
	{
		return fvec2(1.0f);
	}

	const auto rawPosition = (Config::getInst().getDisplayPosition() + Config::getInst().getDisplaySize());
	const auto result = convertToNdc(rawPosition);

	return result;
}

const fvec2 Tools::convertPositionRelativeToDisplay(const fvec2& position)
{
	if(Config::getInst().isApplicationExported())
	{
		return position;
	}

	const auto sizeMultiplier = (fvec2(Config::getInst().getDisplaySize()) / fvec2(Config::getInst().getWindowSize()));
	const auto positionMultiplier = (fvec2(Config::getInst().getDisplayPosition()) / fvec2(Config::getInst().getWindowSize()));
	const auto offset = (fvec2(1.0f) - fvec2(((positionMultiplier.x * 2.0f) + sizeMultiplier.x), ((positionMultiplier.y * 2.0f) + sizeMultiplier.y)));

	fvec2 result = position;
	result *= sizeMultiplier;
	result += fvec2(fabsf(offset.x), fabsf(offset.y));

	return result;
}

const fvec2 Tools::convertPositionRelativeFromDisplay(const fvec2& position)
{
	if(Config::getInst().isApplicationExported())
	{
		return position;
	}

	const auto sizeMultiplier = (fvec2(Config::getInst().getDisplaySize()) / fvec2(Config::getInst().getWindowSize()));
	const auto positionMultiplier = (fvec2(Config::getInst().getDisplayPosition()) / fvec2(Config::getInst().getWindowSize()));
	const auto invertedSizeMultiplier = fvec2(Config::getInst().getWindowSize()) / fvec2(Config::getInst().getDisplaySize());
	const auto invertedPositionMultiplier = (fvec2(Config::getInst().getWindowSize()) / fvec2(Config::getInst().getDisplayPosition()));
	const auto offset = (fvec2(1.0f) - fvec2(((positionMultiplier.x * 2.0f) + sizeMultiplier.x), ((positionMultiplier.y * 2.0f) + sizeMultiplier.y)));

	fvec2 result = position;
	result -= fvec2(fabsf(offset.x), fabsf(offset.y));
	result *= invertedSizeMultiplier;

	return result;
}

const fvec2 Tools::convertSizeRelativeToDisplay(const fvec2& size)
{
	if(Config::getInst().isApplicationExported())
	{
		return size;
	}

	const auto sizeMultiplier = (fvec2(Config::getInst().getDisplaySize()) / fvec2(Config::getInst().getWindowSize()));

	fvec2 result = size;
	result *= sizeMultiplier;

	return result;
}

const fvec2 Tools::convertSizeRelativeFromDisplay(const fvec2& size)
{
	if(!Config::getInst().isApplicationExported())
	{
		return size;
	}

	const auto sizeMultiplier = (fvec2(Config::getInst().getDisplaySize()) / fvec2(Config::getInst().getWindowSize()));

	fvec2 result = size;
	result /= sizeMultiplier;

	return result;
}

const fvec2 Tools::convertToNdc(const ivec2& position)
{
	const auto x = (static_cast<float>(position.x) / static_cast<float>(Config::getInst().getWindowSize().x));
	const auto y = (static_cast<float>(position.y) / static_cast<float>(Config::getInst().getWindowSize().y));

	auto ndc = fvec2(x, y);

	ndc.x *= 2.0f;
	ndc.y *= 2.0f;
	ndc.x -= 1.0f;
	ndc.y -= 1.0f;

	return ndc;
}

const ivec2 Tools::convertFromNdc(const fvec2& position)
{
	auto ndc = position;

	ndc.x += 1.0f;
	ndc.y += 1.0f;
	ndc.x *= 0.5f;
	ndc.y *= 0.5f;

	const auto x = (ndc.x * static_cast<float>(Config::getInst().getWindowSize().x));
	const auto y = (ndc.y * static_cast<float>(Config::getInst().getWindowSize().y));

	return ivec2(static_cast<int>(x), static_cast<int>(y));
}