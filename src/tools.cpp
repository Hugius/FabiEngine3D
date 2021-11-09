#include "tools.hpp"
#include "configuration.hpp"

#include <filesystem>
#include <windows.h>
#include <direct.h>
#include <shlobj_core.h>
#include <GLEW/glew.h>

using std::to_string;
using std::filesystem::absolute;
using std::chrono::duration_cast;
using std::chrono::milliseconds;
using std::chrono::system_clock;

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
	string rootDir = buffer;

	// Convert to absolute path if it's relative
	rootDir = absolute(rootDir).string();

	// Cut to engine root directory
	rootDir = rootDir.substr(0, rootDir.size() - string("binaries\\FabiEngine3D.exe").size());

	// Return
	return rootDir;
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

const bool Tools::isDirectoryExisting(const string& filePath)
{
	struct stat fileInfo;
	int result = stat(filePath.c_str(), &fileInfo);
	return (result == 0 && (fileInfo.st_mode & S_IFDIR));
}

const bool Tools::isFileExisting(const string& filePath)
{
	struct stat fileInfo;
	bool isExisting = stat(filePath.c_str(), &fileInfo) == 0;
	return (isExisting && !isDirectoryExisting(filePath));
}

void Tools::createNewDirectory(const string& directoryPath)
{
	auto temp = _mkdir(directoryPath.c_str());
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