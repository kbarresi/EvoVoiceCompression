#pragma once
#include <string>

using namespace std;

class WavData;
class Population
{
public:
	Population(std::string filename);
	~Population();

	void start();

private:
	WavData* m_trainingData;
};

