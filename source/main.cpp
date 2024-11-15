#include "CSV_Parser.h"
#include <iostream>

int main(int argc, char* argv[]) {
	try {
		CSV_Parser csv_parser;
		csv_parser.load("C:/Users/2/Documents/CSV_JSON_Parser/source/data.txt", true, ',');
		csv_parser.save("C:/Users/2/Documents/CSV_JSON_Parser/source/data1.txt", true, ';');
	}
	catch (std::exception e) {
		std::cout << e.what();
	}
	
}