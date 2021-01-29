/* Hunter Donald 
   hzd0011
   COMP 5370 
   Homework3

   compile with "g++ -std=c++11 hamming.cpp -o hamming
*/

#include <iostream>
#include <math.h>
using namespace std;

int * encode(int inputData[15]);
int * decode(int encodedData[19]);

int main() {
	int data[15] = {1,0,0,1,1,0,1,1,1,0,1,0,0,1,1};
	int *encDataPointer;
	int *decDataPointer;

	encDataPointer = encode(data);
	cout << endl << "Original Data:" << endl;
	for (int i = 0; i < 15; i++) {
		cout << data[i];
	}
	cout << endl << endl << "Encoded Data:" << endl;
	for (int i = 0; i < 19; i++) {
		cout << encDataPointer[i];
	}
	cout << endl << endl << "Now decoding data." << endl << endl;
	decDataPointer = decode(encDataPointer);
	cout << endl << "Decoded Data:" << endl;
	for (int i = 0; i < 15; i++) {
		cout << decDataPointer[i];
	}
	cout << endl << endl;
	cout << "Now inserting error into encoded data." << endl << endl;
	encDataPointer[11] = 0;
	cout << "Encoded Data with error:" << endl;
	for (int i = 0; i < 19; i++) {
		cout << encDataPointer[i];
	}
	cout << endl << endl << "Decoding with error." << endl << endl;
	decDataPointer = decode(encDataPointer);
	cout << "Decoded Data after error fix:" << endl;
	for (int i = 0; i < 15; i++) {
		cout << decDataPointer[i];
	}
	cout << endl << endl;
}

int * encode(int inputData[15]) {
	static int encData[19];
	int c1;
	int c2;
	int c4;
	int c8;
	int dataIndex;
	int encDataIndex;

	// Here I use XOR on the relevant data bits to calculate the parity bits. It is not exactly the same
	// as parity, but serves the same purpose and is easier to implement.
	c1 = inputData[0]^inputData[2]^inputData[4]^inputData[6]^inputData[8]^inputData[10]^inputData[12]^inputData[14];
	c2 = inputData[1]^inputData[2]^inputData[5]^inputData[6]^inputData[9]^inputData[10]^inputData[13]^inputData[14];
	c4 = inputData[3]^inputData[4]^inputData[5]^inputData[6]^inputData[11]^inputData[12]^inputData[13]^inputData[14];
	c8 = inputData[7]^inputData[8]^inputData[9]^inputData[10]^inputData[11]^inputData[12]^inputData[13]^inputData[14];
	
	dataIndex = 0;
	// Here I fill in the encoded data with the calculated parity bits and the original data 
	for (int encDataIndex = 0; encDataIndex < 19; encDataIndex++) {
		if (encDataIndex == 0) {
			encData[encDataIndex] = c1;
		}
		else if (encDataIndex == 1) {
			encData[encDataIndex] = c2;
		}
		else if (encDataIndex == 3) {
			encData[encDataIndex] = c4;
		}
		else if (encDataIndex == 7) {
			encData[encDataIndex] = c8;
		}
		else {
			encData[encDataIndex] = inputData[dataIndex];
			dataIndex++;
		}
	}
	return encData;
}

int * decode(int encodedData[19]) {
	static int receivedData[15];
	int c1;
	int c2;
	int c4;
	int c8;
	int calculatedC1;
	int calculatedC2;
	int calculatedC4;
	int calculatedC8;
	int encodedDataIndex;
	int receivedDataIndex;
	int errorPosition = 0;

	receivedDataIndex = 0;
	// Here I copy the encoded data without the parity bits and record the parity bits to check against later
	for (encodedDataIndex = 0; encodedDataIndex < 19; encodedDataIndex++) {
		if (encodedDataIndex == 0) {
			c1 = encodedData[encodedDataIndex];
		}
		else if (encodedDataIndex == 1) {
			c2 = encodedData[encodedDataIndex];
		}
		else if (encodedDataIndex == 3) {
			c4 = encodedData[encodedDataIndex];
		}
		else if (encodedDataIndex == 7) {
			c8 = encodedData[encodedDataIndex];
		}
		else {
			receivedData[receivedDataIndex] = encodedData[encodedDataIndex];
			receivedDataIndex++;
		}
	}

	// Here I use XOR calculate the parity bits on the received data
	calculatedC1 = receivedData[0]^receivedData[2]^receivedData[4]^receivedData[6]^receivedData[8]^receivedData[10]^receivedData[12]^receivedData[14];
	calculatedC2 = receivedData[1]^receivedData[2]^receivedData[5]^receivedData[6]^receivedData[9]^receivedData[10]^receivedData[13]^receivedData[14];
	calculatedC4 = receivedData[3]^receivedData[4]^receivedData[5]^receivedData[6]^receivedData[11]^receivedData[12]^receivedData[13]^receivedData[14];
	calculatedC8 = receivedData[7]^receivedData[8]^receivedData[9]^receivedData[10]^receivedData[11]^receivedData[12]^receivedData[13]^receivedData[14];

	// Here I find the position of an error
	// If a calculated parity bit does not match the received parity bit, the position of the error
	// increases by which parity bit was erroneous. For example, if the 8 and 1 parity bits are wrong, 
	// the position of the error will be 8 + 1 or 9.
	if (calculatedC1 != c1) {
		errorPosition += 1;
	}
	if (calculatedC2 != c2) {
		errorPosition += 2;
	}
	if (calculatedC4 != c4) {
		errorPosition += 4;
	}
	if (calculatedC8 != c8) {
		errorPosition += 8;
	}

	if (errorPosition == 0) {
		cout << "No errors in decoded data." << endl;
		return receivedData;
	}
	else {
		cout << "There was an error found at position " << errorPosition;
		cout << "." << endl;
		cout << "Erroneous data:" << endl;
		for (int i = 0; i < 15; i++) {
			cout << receivedData[i];
		}
		cout << endl;
		if (receivedData[errorPosition - 1] == 1) {
			cout << "Changing 1 at position " << errorPosition << " to 0." << endl;
			receivedData[errorPosition - 1] = 0;
		}
		else {
			cout << "Changing 0 at position " << errorPosition << " to 1." << endl;
			receivedData[errorPosition - 1] = 1;
		}
		cout << "Data should now be correct." << endl;
	}
	return receivedData;	
}