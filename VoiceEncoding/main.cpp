#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>

#include "Population.h"

int main(int argc, char** argv) {
	std::cout << "\n\n";
	std::string trainingData = "";
	for (int i = 0; i < argc; i++) {
		if (strcmp(argv[i], "-f") == 0) {
			if (i + 1 == argc) {
				std::cout << "Error: No training data given\n\n";
				return -1;
			}
			trainingData = argv[i + 1];
			break;
		}
	}

	printf("Training data...\t%s\n", trainingData.c_str());

	Population* population = new Population(trainingData);
	population->start();

	delete population;
	std::cin.get();
	return 0;
}