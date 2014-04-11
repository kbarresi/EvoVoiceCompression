#include <stdlib.h>
#include <fstream>
#include <iostream>

#include "WavData.h"


WavData::WavData(std::string filename)
{
	m_data = 0;
	m_size = 0;

	load(filename);
}

WavData::~WavData()
{
	printf("deleting:\tWavData: %d bytes\n", m_size);

	if (m_data)
		free(m_data);
}

void WavData::load(std::string filename) {
	FILE *fp;
	errno_t err = fopen_s(&fp, filename.c_str(), "rb");

	if (err == 0) {
		char id[5];
		unsigned long size;
		short format_tag, channels, block_align, bps;
		unsigned long format_length, sample_rate, avg_bytes_sec, data_size;

		fread(id, sizeof(char), 4, fp);
		id[4] = '\0';

		if (!strcmp(id, "RIFF")) {
			fread(&size, sizeof(unsigned long), 1, fp);
			fread(id, sizeof(char), 4, fp);
			id[4] = '\0';

			if (!strcmp(id, "WAVE")) {
				fread(id, sizeof(char), 4, fp);
				fread(&format_length, sizeof(unsigned long), 1, fp);
				fread(&format_tag, sizeof(short), 1, fp);
				fread(&channels, sizeof(short), 1, fp);
				fread(&sample_rate, sizeof(unsigned long), 1, fp);
				fread(&avg_bytes_sec, sizeof(unsigned long), 1, fp);
				fread(&block_align, sizeof(short), 1, fp);
				fread(&bps, sizeof(short), 1, fp);
				fread(id, sizeof(char), 4, fp);
				fread(&data_size, sizeof(unsigned long), 1, fp);

				m_size = data_size / sizeof(short);
				m_data = (short*)malloc(data_size);
				fread(m_data, sizeof(short), m_size, fp);
				printf("Read WAV file. Size: %d\n", m_size);
			}
			else {
				printf("Error: RIFF file but not a wave file\n");
			}
		}
		else {
			printf("Error: not a RIFF file: %s\n", filename.c_str());

		}
	}
	else {
		printf("Error: unable to open file: %s\n", filename.c_str());
	}
	fclose(fp);
}
