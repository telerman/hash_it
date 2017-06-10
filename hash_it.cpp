//============================================================================
// Name        : crypto_pp.cpp
// Version     :
// Copyright   :
// Description :
//============================================================================
#include "openssl/sha.h"
#include <stdio.h>
#include <string>
#include <iostream>
#include <sstream>
#include <iterator>
#include <unistd.h>
#include <termios.h>
#include <cstring>
using namespace std;

void str2bin(const std::string& in, unsigned char out[])
{
    const char* data = in.data();
    const std::string::size_type size = in.size();
    for(std::string::size_type i = 0; i < size; i+= 2) {
        unsigned int tmp;
        std::sscanf(data+i, "%02X", &tmp);
        out[i/2] = tmp;
    }
}

string sha1sum(string in_text="test", int _cut=20) {

	unsigned char * cData = new unsigned char[in_text.length()];

	strcpy((char *)cData, in_text.c_str());

	size_t length = in_text.length();

	unsigned char hash[SHA_DIGEST_LENGTH];

	SHA1(cData, length, hash);

	stringstream et1;

	for(int i = 0; i < _cut/2; i++)
		et1 << hex << (unsigned int)hash[i];

	return et1.str();
}

int main(int argc, char *argv[]) {
	int _cut;
	if (argc > 1)
		_cut = atoi(argv[1]);
	else
		_cut = 40;

	std::cout << flush;
	std::cout << endl << ": ";

	termios oldt;
	tcgetattr(STDIN_FILENO, &oldt);
	termios newt = oldt;
	newt.c_lflag &= ~ECHO;
	tcsetattr(STDIN_FILENO, TCSANOW, &newt);

	std::string plain1;
	std::cin >> plain1;
	tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
	cout << endl << (sha1sum(plain1, _cut)) << endl;
	return 0;
}
