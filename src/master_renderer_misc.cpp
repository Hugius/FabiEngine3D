#include "master_renderer.hpp"

void MasterRenderer::setBackgroundColor(fvec4 color)
{
	glClearColor(color.r, color.g, color.b, color.a);
}

/* https://stackoverflow.com/questions/850774/how-to-determine-the-hardware-cpu-and-ram-on-a-machine */
const string MasterRenderer::getCpuName() const
{
	int CPUInfo[4];
	char model[48];

	__cpuid(CPUInfo, 0x80000002);
	memcpy(model, CPUInfo, sizeof(CPUInfo));
	__cpuid(CPUInfo, 0x80000003);
	memcpy(model + 16, CPUInfo, sizeof(CPUInfo));
	__cpuid(CPUInfo, 0x80000004);
	memcpy(model + 32, CPUInfo, sizeof(CPUInfo));

	string nameString;
	for(unsigned int i = 0; i < 48; i++)
	{
		nameString.push_back(model[i]);
	}

	string result;
	reverse(nameString.begin(), nameString.end());
	for(size_t i = 0; i < nameString.size(); i++)
	{
		if(nameString[i] != 0)
		{
			result = nameString.substr(i);
			break;
		}
	}

	reverse(result.begin(), result.end());
	return result;
}

const string MasterRenderer::getGpuName() const
{
	return string(reinterpret_cast<char*>(const_cast<GLubyte*>(glGetString(GL_RENDERER))));
}

const string MasterRenderer::getOpenglVersion() const
{
	return string(reinterpret_cast<char*>(const_cast<GLubyte*>(glGetString(GL_VERSION)))).substr(0, 3);
}