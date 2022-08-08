#include <fstream>
#include <iostream>

int main() {

	std::ofstream file("File.txt");
	if( file.is_open() ) {
		file << "No kaman" << std::endl;
		file.flush();
		file.close();
	}
	else {
		std::cout << "It supose to work\n";
	}
	return 0;
}