#include <cstdint>
#include <iostream>
#include <string>
#include <vector>

#include "crypto_utils.h"

/* Conversion from value to base64 character */
const char BASE64[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '+', '/'};

/* Binary 111111 (lowest 6 bits set only) */ 
const uint32_t MASK = 0x3F;

int hex_to_bytes(const std::string & input, std::vector<uint8_t> & bytes)
{
	if (input.size() % 2 != 0) {
		std::cout << "Input string must be byte aligned" << std::endl;
		return -1;
	}

	char * endptr;
	char tmp[3];
	tmp[2] = '\0';
	for (int i = 0; i < input.size()/2; i++) {
		tmp[0] = input.at(i*2);
		tmp[1] = input.at(i*2 + 1);
		uint8_t value = strtol(tmp, &endptr, 16);
		if (*endptr != '\0') {
			std::cout << "Invalid hex string" << std::endl;
			return -1;
		}
		bytes.push_back(value);
	}

	return 0;

}

void base64_encode(const std::vector<uint8_t> & bytes, std::vector<char> & output)
{
	// ceil(len/3)
	int rounds = (bytes.size() + (3-1)) / 3;

	bool use_pad_1 = false;
	bool use_pad_2 = false;
	for (int round = 0; round < rounds; round++) {
		// Determine if any padding is needed
		if (round + 1 == rounds) { 
			if (bytes.size() % 3 == 1) {
				use_pad_1 = true;
				use_pad_2 = true;
			} else if (bytes.size() % 3 == 2) {
				use_pad_2 = true;
			}
		}

		// Find value of each 24-bit word (3 bytes)
		int firstbyte = bytes.at(round*3 + 0) << 16;
		int secondbyte = use_pad_1 ? 0 : bytes.at(round*3 + 1) << 8;
		int thirdbyte = use_pad_2 ? 0 : bytes.at(round*3 + 2);

		int fullnum = firstbyte + secondbyte + thirdbyte;

		// Split into 6-bit words
		int n1 = (fullnum >> 18) & MASK;
		int n2 = (fullnum >> 12) & MASK;
		int n3 = (fullnum >> 6) & MASK;
		int n4 = fullnum & MASK;

		output.push_back(BASE64[n1]);
		output.push_back(BASE64[n2]);
		output.push_back(use_pad_1 ? '=' : BASE64[n3]);
		output.push_back(use_pad_2 ? '=' : BASE64[n4]);
	}
}
