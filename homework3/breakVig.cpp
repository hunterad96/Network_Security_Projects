#include <iostream>
#include <fstream>
using namespace std;

char mostFrequent(char array[], int size);

int main() {
	char firstPart[10];
	char secondPart[10];
	char thirdPart[10];
	char firstPartMostFrequent;
	char secondPartMostFrequent;
	char thirdPartMostFrequent;
	int ciphertextIndex;


	char alphabet[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
	float actualFrequencies[] = {0.08167, 0.01492, 0.02782, 0.04253, 0.12702, 0.0228, 0.02015, 0.06094, 0.06966, 0.00153, 0.00772, 0.04025, 0.02406, 0.06749, 0.07507, 0.01929, 0.00095, 0.05987, 0.06327, 0.09056, 0.02758, 0.00978, 0.02360, 0.00150, 0.01974, 0.00074};
	char ciphertext[] = {'T', 'I', 'C', 'E', 'I', 'S', 'N', 'I', 'U', 'T', 'I', 'C', 'E', 'N', 'I', 'A', 'N', 'J', 'S', 'N', 'I', 'E', 'K', 'V', 'E', 'M', 'U', 'I', 'I', 'O'};
	int ciphertextLength = (sizeof(ciphertext)/sizeof(*ciphertext));

	for (int i = 0; i < 3; i++) {
		if (i == 0) {
			ciphertextIndex = 0;
			for (int j = 0; ((j < 10) && (ciphertextIndex < ciphertextLength)); j++) {
				firstPart[j] = ciphertext[ciphertextIndex];
				ciphertextIndex += 3;
			}
		}
		else if (i == 1) {
			ciphertextIndex = 1;
			for (int j = 0; ((j < 10) && (ciphertextIndex < ciphertextLength)); j++) {
				secondPart[j] = ciphertext[ciphertextIndex];
				ciphertextIndex += 3;
			}
		}
		else if (i == 2) {
			ciphertextIndex = 2;
			for (int j = 0; ((j < 10) && (ciphertextIndex < ciphertextLength)); j++) {
				thirdPart[j] = ciphertext[ciphertextIndex];
				ciphertextIndex += 3;
			}
		}
	}

	firstPartMostFrequent = mostFrequent(firstPart, 10);

	return 0;
}

char mostFrequent(char array[], int size) {
	sort(array, size + 1);

	int maxCount = 1;
	int result = array[0];
	int currentCount = 	1;
	for (int i = 1; i < size; i++) {
		if (array[i] == array[i - 1]) {
			currentCount++;
		} 
		else {
			if (currentCount > maxCount) {
				maxCount = currentCount;
				result = array[i - 1];
			}
		}
	}

	if (currentCount > maxCount) {
		maxCount = currentCount;
		result = array[size - 1];
	}
	return result;
}