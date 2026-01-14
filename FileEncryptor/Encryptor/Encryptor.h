#pragma once
#include <iostream>
#include <sodium.h>
#include <stdio.h>
#include <fstream>

class Encryptor {	
	public:
		void encryptFile(std::string pathToFile,const char* password);
	private:
		void deriveKeyFromPassword(const char* password, unsigned char* key);
		void encrypt(std::string pathToFile, unsigned char* key);
};