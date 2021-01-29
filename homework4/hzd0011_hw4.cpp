#include <iostream>

void cathy(int state, std::string message);
void bob(int state, std::string message);
void alice(int state, std::string message);

void cathy(int state, std::string message) {
	std::time_t result = std::time(nullptr);
	std::string timeString = std::asctime(std::localtime(&result));
	timeString.pop_back(); // get rid of newline char
	std::string messageToSend;
	std::string unencryptedMessage;
	
	switch(state) {
		case 0:
			std::cout << "\nCathy is receiving request from Alice for session key with Bob\n";
			std::cout << "Received message: " << message << "\n";
		case 1:
			messageToSend = "{Alice || Bob || r1 || ks || {Alice || " + timeString + " || ks}kB}kA";
			unencryptedMessage = "Alice || Bob || r1 || ks || {Alice || " + timeString + " || ks}kB";
			std::cout << "\nCathy is sending message with session key to Alice\n";
			std::cout << "Unencrypted message: " << unencryptedMessage << "\n";
			alice(1, messageToSend);
			break;
	}
}

void alice(int state, std::string message) {
	std::time_t result = std::time(nullptr);
	std::string timeString = std::asctime(std::localtime(&result));
	timeString.pop_back();
	std::string messageToSend;
	std::string unencryptedMessage;
	switch(state) {
		case 0 :
			messageToSend = "Alice || Bob || r1";
			std::cout << "\nAlice is sending request to Cathy for session key with Bob\n";
			std::cout << "Sent Message: " << messageToSend << "\n";
			cathy(0, messageToSend);
			break;
		case 1:
			std::cout << "\nAlice has received message with session key from Cathy\n";
			std::cout << "Encrypted message: " << message << "\n";
		case 2:
			messageToSend = "{Alice || " + timeString + " || ks}kB";
			unencryptedMessage = "Alice || " + timeString + " || ks";
			std::cout << "\nAlice is sending session key to Bob\n";
			std::cout << "Unencrypted message: " << unencryptedMessage << "\n";
			bob(0, messageToSend);
			break;
		case 3:
			std::cout << "\nAlice has received nonce from Bob\n";
			std::cout << "Unencrypted message: " << message << "\n";
		case 4:
			messageToSend = "{r2 - 1}ks";
			unencryptedMessage = "r2 - 1";
			std::cout << "\nAlice is sending nonce reply to Bob\n";
			std::cout << "Unencrypted message: " << unencryptedMessage << "\n";
			bob(2, messageToSend);
			break;
		case 5:
			std::cout << "\nAlice has received a message from Bob\n";
			std::cout << "Encrypted message: " << message << "\n";
			break; 
	}
}

void bob(int state, std::string message) {
	std::string messageToSend;
	std::string unencryptedMessage;
	switch(state) {
		case 0:
			std::cout << "\nBob has recieved session key from Alice\n";
			std::cout << "Encrypted message: " << message << "\n";
		case 1:
			messageToSend = "{r2}ks";
			unencryptedMessage = "r2";
			std::cout << "\nBob is sending nonce to Alice\n";
			std::cout << "Unencrypted message: " << unencryptedMessage << "\n";
			alice(3, messageToSend);
			break;
		case 2:
			std::cout << "\nBob has received nonce reply from Alice\n";
			std::cout << "Encrypted message: " << message << "\n";
		case 3:
			messageToSend = "{m}ks";
			unencryptedMessage = "m";
			std::cout << "\nBob is sending a message to Alice\n";
			std::cout << "Unencrypted message: " << unencryptedMessage << "\n";
			alice(5, messageToSend);
			break;
	}
}

int main() {
	std::string message = "";
	alice(0, message);
	std::cout << "\n";
	return 0;
}