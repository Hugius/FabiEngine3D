#include "audio_loader.hpp"

shared_ptr<Audio> AudioLoader::_loadAudio(const string& filePath)
{
	FILE* file = nullptr;
	if(fopen_s(&file, std::string("Medxion - I feel bass.wav").c_str(), "rb") != 0)
	{
		return 0;
	}

	auto header = new unsigned char[44];

	for(int i = 0; i < 44; i++)
	{
		header[i] = getc(file);
	}

	string firstString = "";
	firstString.push_back(header[0]);
	firstString.push_back(header[1]);
	firstString.push_back(header[2]);
	firstString.push_back(header[3]);

	if(firstString != "RIFF")
	{
		return nullptr;
	}

	string secondString = "";
	secondString.push_back(header[8]);
	secondString.push_back(header[9]);
	secondString.push_back(header[10]);
	secondString.push_back(header[11]);

	if(secondString != "WAVE")
	{

	}

	string thirdString = "";
	thirdString.push_back(header[12]);
	thirdString.push_back(header[13]);
	thirdString.push_back(header[14]);
	thirdString.push_back(header[15]);

	if(thirdString != "fmt")
	{
		return nullptr;
	}

	string fourthString = "";
	fourthString.push_back(header[36]);
	fourthString.push_back(header[37]);
	fourthString.push_back(header[38]);
	fourthString.push_back(header[39]);

	if(fourthString != "data")
	{
		return nullptr;
	}

	const auto compressionFormat = static_cast<unsigned int>((header[21] << 8) | header[20]);

	if(compressionFormat != 1)
	{
		return nullptr;
	}

	const auto channelCount = static_cast<unsigned int>((header[23] << 8) | header[22]);
	const auto bitsPerSample = static_cast<unsigned int>((header[35] << 8) | header[34]);
	const auto sampleRate = static_cast<unsigned int>((header[27] << 24) | (header[26] << 16) | (header[25] << 8) | header[24]);
	const auto sampleCount = static_cast<unsigned int>((header[43] << 24) | (header[42] << 16) | (header[41] << 8) | header[40]);
	const auto samples = new unsigned char[sampleCount];

	for(unsigned int i = 0; i < sampleCount; i++)
	{
		samples[i] = static_cast<unsigned char>(getc(file));
	}

	delete[] header;

	fclose(file);

	return make_shared<Audio>(samples, sampleCount, sampleRate, bitsPerSample, (channelCount == 1 ? ChannelFormat::MONO : ChannelFormat::STEREO));
}