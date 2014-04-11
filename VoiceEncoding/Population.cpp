#include "Population.h"
#include "WavData.h"

Population::Population(std::string filename)
{
	m_trainingData = new WavData(filename);
}


Population::~Population()
{
	printf("deleting:\tPopulation\n");
	delete m_trainingData;
}

void Population::start() {

}