#pragma once
#include <string>

class WavData
{
public:
	WavData(std::string filename);
	~WavData();

	short* data() { return m_data; }
	unsigned long size() const { return m_size; }

private:
	short* m_data;
	unsigned long m_size;

	void load(std::string filename);
};

