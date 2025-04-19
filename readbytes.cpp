/*  Bytes Reader
	Copyright 2024 KeyofBlueS

	Bytes Reader is free software;
	you can redistribute it and/or modify it under the terms of the
	GNU General Public License as published by the Free Software Foundation;
	either version 3, or (at your option) any later version.
	See the file COPYING for more details.
*/

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>
#include <vector>
#include <cstdlib>

// Function to extract bytes from a binary file and return them as a hexadecimal string.
std::string extractBytes(const std::string& filePath, int offset, int length) {
	std::ifstream file(filePath, std::ios::binary);
	if (!file.is_open()) {
		std::cerr << "* ERROR: Unable to open file: " << filePath << std::endl;
		return "";
	}

	file.seekg(offset, std::ios::beg);
	std::vector<char> buffer(length);
	file.read(buffer.data(), length);
	file.close();

	std::stringstream hexStream;
	for (int i = 0; i < length; ++i) {
		hexStream << std::hex << std::setw(2) << std::setfill('0') << (int)(unsigned char)buffer[i];
	}

	return hexStream.str();
}

// Function to print the help message
void printHelpMessage() {
	std::cout << "\n";
	std::cout << "Bytes Reader v0.0.1\n";
	std::cout << "\n";
	std::cout << "Usage: readbytes <input_file> [options]\n";
	std::cout << "\n";
	std::cout << "Options:\n";
	std::cout << "  -s, --seek <offset>		Set the offset (default is 0)\n";
	std::cout << "  -l, --length <length>		Set the number of bytes to read (default is 4)\n";
	std::cout << "  -h, --help			Show this help message and exit\n";
	std::cout << "\n";
	std::cout << "Copyright © 2024 KeyofBlueS: <https://github.com/KeyofBlueS>.\n";
	std::cout << "License GPLv3+: GNU GPL version 3 or later <https://gnu.org/licenses/gpl.html>.\n";
	std::cout << "This is free software: you are free to change and redistribute it.\n";
	std::cout << "There is NO WARRANTY, to the extent permitted by law.\n";
}

// Main function
int main(int argc, char* argv[]) {
	std::string inputFile;
	int offset = 0;
	int length = 4;

	// Parse command-line arguments
	for (int i = 1; i < argc; ++i) {
		std::string arg = argv[i];

		if (arg == "-h" || arg == "--help") {
			printHelpMessage();
			return 0;
		} else if (arg == "-s" || arg == "--seek") {
			if (i + 1 < argc) {
				offset = std::stoi(argv[++i]);
			} else {
				std::cerr << "* ERROR: Missing value for option '" << arg << "'\n";
				return 1;
			}
		} else if (arg == "-l" || arg == "--length") {
			if (i + 1 < argc) {
				length = std::stoi(argv[++i]);
			} else {
				std::cerr << "* ERROR: Missing value for option '" << arg << "'\n";
				return 1;
			}
		} else {
			inputFile = arg;	// Assume any other argument is the input file
		}
	}

	// Validate input file
	if (inputFile.empty()) {
		std::cerr << "* ERROR: No input file specified.\n";
		printHelpMessage();
		return 1;
	}

	// Validate length
	if (length <= 0) {
		std::cerr << "* ERROR: Length must be greater than 0.\n";
		return 1;
	}

	// Validate offset
	if (offset < 0) {
		std::cerr << "* ERROR: Offset must not be negative.\n";
		return 1;
	}

	// Extract bytes from the file at the specified offset and length
	std::string bytesHex = extractBytes(inputFile, offset, length);

	// Print the extracted bytes in hexadecimal format
	std::cout << bytesHex << std::endl;

	return 0;
}
