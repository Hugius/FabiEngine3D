#include "tools.hpp"
#include "configuration.hpp"
#include "logger.hpp"

#include <filesystem>
#include <windows.h>
#include <direct.h>
#include <shlobj_core.h>
#include <GLEW/glew.h>

using std::to_string;
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
	// Error checking
	if(!isDirectoryExisting(path))
	{
		Logger::throwError("Tools::getFilesFromDirectory");
		return {};
	}

	// Retrieve files
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
	// Error checking
	if(!isDirectoryExisting(path))
	{
		Logger::throwError("Tools::getDirectoriesFromDirectory");
		return {};
	}

	// Retrieve directories
	vector<string> directoryNames;
	for(const auto& entry : directory_iterator(path))
	{
		// Extract path
		string directoryPath = entry.path().string();

		// Check if path is directory
		if(isDirectoryExisting(directoryPath))
		{
			directoryPath.erase(0, path.size());
			directoryNames.push_back(directoryPath);
		}
	}
	return directoryNames;
}

const string Tools::vec2str(Ivec2 vec)
{
	return string(to_string(vec.x) + " " + to_string(vec.y));
}

const string Tools::vec2str(Vec2 vec)
{
	return string(to_string(vec.x) + " " + to_string(vec.y));
}

const string Tools::vec2str(Vec3 vec)
{
	return string(to_string(vec.x) + " " + to_string(vec.y) + " " + to_string(vec.z));
}

const string Tools::vec2str(Vec4 vec)
{
	return string(to_string(vec.x) + " " + to_string(vec.y) + " " + to_string(vec.z) + " " + to_string(vec.w));
}

const string Tools::getRootDirectoryPath()
{
	// Temporary values
	char buffer[256];
	size_t len = sizeof(buffer);

	// Get executable path
	GetModuleFileName(nullptr, buffer, static_cast<DWORD>(len));

	// Create final string
	string rootDirectoryPath = buffer;

	// Convert to absolute path if path is relative
	rootDirectoryPath = absolute(rootDirectoryPath).string();

	// Cut to engine root directory
	rootDirectoryPath = rootDirectoryPath.substr(0, (rootDirectoryPath.size() - string("binaries\\fe3d.exe").size()));

	// Return
	return rootDirectoryPath;
}

const float Tools::getWindowAspectRatio()
{
	return static_cast<float>(Config::getInst().getWindowSize().x) / static_cast<float>(Config::getInst().getWindowSize().y);
}

const long long Tools::getTimeSinceEpochMS()
{
	return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
}

const string Tools::chooseExplorerFile(const string& startingDirectory, const string& fileType)
{
	// Temporary values
	string filter = fileType;
	filter.push_back('\0');
	filter += "*." + fileType + '\0';

	// Open file explorer
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

	// Return chosen file
	return ofn.lpstrFile;
}

const string Tools::chooseExplorerDirectory(const string& startingDirectory)
{
	// Compose brose info
	BROWSEINFO browseInfo = {};
	browseInfo.ulFlags = (BIF_RETURNONLYFSDIRS | BIF_NEWDIALOGSTYLE);
	browseInfo.lpfn = nullptr;
	browseInfo.lParam = LPARAM(startingDirectory.c_str());

	// Open file explorer
	LPITEMIDLIST pidl = SHBrowseForFolder(&browseInfo);

	// Check if user selected a directory
	if(pidl != 0)
	{
		// Extract directory path
		char directoryPath[MAX_PATH];
		SHGetPathFromIDList(pidl, directoryPath);

		// Free memory
		IMalloc* imalloc = 0;
		if(SUCCEEDED(SHGetMalloc(&imalloc)))
		{
			imalloc->Free(pidl);
			imalloc->Release();
		}

		// Return chosen directory
		return directoryPath;
	}

	// No directory chosen
	return "";
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
	// Error checking
	if(!isDirectoryExisting(fromPath))
	{
		Logger::throwError("Tools::copyDirectory");
		return;
	}

	using namespace std;
	filesystem::copy(fromPath, toPath, filesystem::copy_options::recursive);
}

void Tools::copyFile(const string& fromPath, const string& toPath)
{
	// Error checking
	if(!isFileExisting(fromPath))
	{
		Logger::throwError("Tools::copyFile");
		return;
	}

	using namespace std;
	filesystem::copy_file(fromPath, toPath);
}

void Tools::renameDirectory(const string& oldPath, const string& newPath)
{
	// Error checking
	if(!isDirectoryExisting(oldPath))
	{
		Logger::throwError("Tools::renameDirectory");
		return;
	}

	rename(oldPath, newPath);
}

void Tools::renameFile(const string& oldPath, const string& newPath)
{
	// Error checking
	if(!isFileExisting(oldPath))
	{
		Logger::throwError("Tools::renameFile");
		return;
	}

	rename(oldPath, newPath);
}

void Tools::deleteDirectory(const string& path)
{
	// Error checking
	if(!isDirectoryExisting(path))
	{
		Logger::throwError("Tools::deleteDirectory");
		return;
	}

	remove_all(path);
}

void Tools::deleteFile(const string& path)
{
	// Error checking
	if(!isFileExisting(path))
	{
		Logger::throwError("Tools::deleteFile");
		return;
	}

	remove(path);
}

void Tools::setMainRenderingColor(Vec3 color)
{
	glClearColor(color.r, color.g, color.b, 1.0f);
}

const Ivec2 Tools::convertToScreenCoords(Vec2 position)
{
	const float x = (position.x * static_cast<float>(Config::getInst().getWindowSize().x));
	const float y = (position.y * static_cast<float>(Config::getInst().getWindowSize().y));

	return Ivec2(static_cast<int>(x), static_cast<int>(y));
}

const Vec2 Tools::convertFromScreenCoords(Ivec2 position)
{
	const float x = (static_cast<float>(position.x) / static_cast<float>(Config::getInst().getWindowSize().x));
	const float y = (static_cast<float>(position.y) / static_cast<float>(Config::getInst().getWindowSize().y));

	return Vec2(x, y);
}