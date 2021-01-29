#include <iostream>
#include <string>

using namespace std;

string decrypt(string ciphertext, string key);

int main() {
	int maxNumUniqueCommonWords = 0;
	int numUniqueCommonWords = 0;
	string key;
	string keyWithMaxUniqueCommonWords;
	string plaintext;
	string ciphertext = "TICEISNIUTICENIANJSNIEKVEMUIIO";
	string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	string commonTwoLetterWords[] = {"OF", "TO", "IN", "IT", "IS", "BE", "AS", 
									"AT", "SO", "WE", "HE", "BY", "OR", "ON", 
									"DO", "IF", "ME", "MY", "UP", "AN", "GO", 
									"NO", "US", "AM"};

	for (int i = 0; i < alphabet.length(); i++) {
		for (int j = 0; j < alphabet.length(); j++) {
			for (int k = 0; k < alphabet.length(); k++) {
				for (int z = 0; z < ciphertext.length() - 2; z+=3) {
					key.push_back(alphabet.at(i));
					key.push_back(alphabet.at(j));
					key.push_back(alphabet.at(k));
				}
				plaintext = decrypt(ciphertext, key);
				/*
				cout << "Attempted Key: " << key.at(0) << key.at(1) << key.at(2);
				cout << "    Result : " << plaintext << endl;
				*/
				for (string str : commonTwoLetterWords) {
					std::size_t found = plaintext.find(str);
					if (found != std::string::npos) {
						numUniqueCommonWords++;
					}
				}
				if (numUniqueCommonWords > maxNumUniqueCommonWords) {
					maxNumUniqueCommonWords = numUniqueCommonWords;
					keyWithMaxUniqueCommonWords.erase(keyWithMaxUniqueCommonWords.begin(), keyWithMaxUniqueCommonWords.end());
					keyWithMaxUniqueCommonWords.push_back(alphabet.at(i));
					keyWithMaxUniqueCommonWords.push_back(alphabet.at(j));
					keyWithMaxUniqueCommonWords.push_back(alphabet.at(k));
				}
				numUniqueCommonWords = 0;
				key.erase(key.begin(), key.end());
			}
		}
	}
	key = keyWithMaxUniqueCommonWords;
	for (int i = 0; i < 10; i++) {
		keyWithMaxUniqueCommonWords.append(key);
	}
	plaintext = decrypt(ciphertext, keyWithMaxUniqueCommonWords);
	cout << endl << "Most likely key: " << key << endl;
	cout << "Encrypted text: " << ciphertext << endl;
	cout << "Plaintext after decrypting ciphertext with most likely key: " << plaintext << endl << endl;
	return 0;
}

string decrypt(string ciphertext, string key) {
	string plaintext;

	for (int i = 0; i < ciphertext.length(); i++) {
		int x = (ciphertext.at(i) - key.at(i) + 26) % 26;

		x += 'A';
		plaintext.push_back(x);
	}
	return plaintext;
}