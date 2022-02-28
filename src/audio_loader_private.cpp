#pragma warning(disable:6001)

#include "audio_loader.hpp"
#include "tools.hpp"
#include "logger.hpp"

using std::make_shared;

shared_ptr<Audio> AudioLoader::_loadAudio(const string& filePath)
{
	const auto rootPath = Tools::getRootDirectoryPath();
	const auto fullFilePath = (rootPath + filePath);

	FILE* file = nullptr;

	if(fopen_s(&file, fullFilePath.c_str(), "rb") != 0)
	{
		return nullptr;
	}

	auto chunkHeaderData = new unsigned char[12];

	for(int index = 0; index < 12; index++)
	{
		chunkHeaderData[index] = static_cast<unsigned int>(getc(file));
	}

	string chunkId = "";
	chunkId.push_back(chunkHeaderData[0]);
	chunkId.push_back(chunkHeaderData[1]);
	chunkId.push_back(chunkHeaderData[2]);
	chunkId.push_back(chunkHeaderData[3]);

	if(chunkId != "RIFF")
	{
		return nullptr;
	}

	const auto chunkSize = static_cast<unsigned int>((chunkHeaderData[7] << 24) | (chunkHeaderData[6] << 16) | (chunkHeaderData[5] << 8) | chunkHeaderData[4]);

	string format = "";
	format.push_back(chunkHeaderData[8]);
	format.push_back(chunkHeaderData[9]);
	format.push_back(chunkHeaderData[10]);
	format.push_back(chunkHeaderData[11]);

	if(format != "WAVE")
	{
		return nullptr;
	}

	unsigned int channelCount = 0;
	unsigned int sampleRate = 0;
	unsigned int byteRate = 0;
	unsigned int bytesPerBlock = 0;
	unsigned int bitsPerSample = 0;

	while(true)
	{
		auto subChunkHeaderData = new unsigned char[8];

		for(int index = 0; index < 8; index++)
		{
			subChunkHeaderData[index] = static_cast<unsigned int>(getc(file));
		}

		string subChunkId = "";
		subChunkId.push_back(subChunkHeaderData[0]);
		subChunkId.push_back(subChunkHeaderData[1]);
		subChunkId.push_back(subChunkHeaderData[2]);
		subChunkId.push_back(subChunkHeaderData[3]);

		const auto subChunkSize = static_cast<unsigned int>((subChunkHeaderData[7] << 24) | (subChunkHeaderData[6] << 16) | (subChunkHeaderData[5] << 8) | subChunkHeaderData[4]);

		if(subChunkId == "fmt ")
		{
			auto subChunkBodyData = new unsigned char[16];

			for(int index = 0; index < 16; index++)
			{
				subChunkBodyData[index] = static_cast<unsigned int>(getc(file));
			}

			const auto compressionFormat = static_cast<unsigned int>((subChunkBodyData[1] << 8) | subChunkBodyData[0]);

			// 1 = PCM
			if(compressionFormat != 1)
			{
				return nullptr;
			}

			channelCount = static_cast<unsigned int>((subChunkBodyData[3] << 8) | subChunkBodyData[2]);

			if(channelCount != 1 && channelCount != 2)
			{
				return nullptr;
			}

			sampleRate = static_cast<unsigned int>((subChunkBodyData[7] << 24) | (subChunkBodyData[6] << 16) | (subChunkBodyData[5] << 8) | subChunkBodyData[4]);
			byteRate = static_cast<unsigned int>((subChunkBodyData[11] << 24) | (subChunkBodyData[10] << 16) | (subChunkBodyData[9] << 8) | subChunkBodyData[8]);
			bytesPerBlock = static_cast<unsigned int>((subChunkBodyData[13] << 8) | subChunkBodyData[12]);
			bitsPerSample = static_cast<unsigned int>((subChunkBodyData[15] << 8) | subChunkBodyData[14]);
		}
		else if(subChunkId == "data")
		{
			const auto samples = new unsigned char[subChunkSize];

			for(unsigned int index = 0; index < subChunkSize; index++)
			{
				samples[index] = static_cast<unsigned char>(getc(file));
			}

			fclose(file);

			return make_shared<Audio>(samples, subChunkSize, (channelCount == 1 ? ChannelFormat::MONO : ChannelFormat::STEREO), sampleRate, byteRate, bytesPerBlock, bitsPerSample);
		}
		else
		{
			for(unsigned int index = 0; index < subChunkSize; index++)
			{
				const auto temp = getc(file);
			}
		}
	}
}