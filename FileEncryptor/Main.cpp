// FileEncryptor.cpp: Definiert den Einstiegspunkt für die Anwendung.
//

#include "Main.h"
#include "Encryptor/Encryptor.h"

using namespace std;

int main()
{
	Encryptor encryptor =  Encryptor();
	std::cout << "Enter password";
	std::string password;
	std::cin >> password;
	encryptor.encryptFile("C:\\Users\\Jan\\source\\repos\\C++\\FileEncryptor\\example.txt", password.c_str());
	return 0;
}
