#include "CSV_Parser.h"
#include "CSV_Parser.h"
#include "CSV_Parser.h"
#include "CSV_Parser.h"
#include "sstream"
#include <iostream>
#include <iomanip>
#include <functional>

void CSV_Parser::load(const std::string& filename, bool hasheader, char delimiter)
{
	std::ifstream file(filename);

	if (!file.is_open()) throw std::runtime_error("Cant open this file");

	bool fl = true;
	std::string line;

	while (std::getline(file, line)) {
		if (fl && hasheader) {
			header_ = parseLine(line, delimiter);
			fl = false;
		}
		else {
			data_.push_back(parseLine(line, delimiter));
		}
	}
	int i = 0;
	for (auto& s : header_) {
		indtocolname_[s] = i;
		i += 1;
	}

	file.close();
	return;
}

std::vector<std::string> CSV_Parser::parseLine(const std::string& line, char delimiter)
{
	std::vector<std::string> delimited_line;
	std::stringstream ss;
	ss << line;
	std::string word;
	while (std::getline(ss, word, delimiter)) {
		delimited_line.push_back(word);
	}
	return delimited_line;
}

std::vector<std::string> CSV_Parser::operator[](int n) {
	if (n > data_.size()) throw std::out_of_range("Out of range");
	return data_[n];
}

std::string CSV_Parser::get(int rowindex, const std::string& colname) const
{
	if (rowindex > data_.size()) throw std::out_of_range("Out of range");
	if (indtocolname_.find(colname) != indtocolname_.end()) throw std::invalid_argument("No such column");
	return data_[rowindex][indtocolname_[colname]];
}

void CSV_Parser::set(int rowindex, const std::string& colname, std::string val)
{
	if (rowindex > data_.size()) throw std::out_of_range("Out of range");
	if (indtocolname_.find(colname) != indtocolname_.end()) throw std::invalid_argument("No such column");
	data_[rowindex][indtocolname_[colname]] = val;
	return;
}

void CSV_Parser::save(const std::string& filename, bool writeheader, char delimiter) const
{
	std::ofstream file(filename);
	if (!file.is_open()) throw std::runtime_error("Cant open the file");
	if (hasheader_ && writeheader) {
		for (auto& s : header_) {
			file << s << delimiter;
		}
		file << '\n';
	}
	for (auto& v : data_) {
		for (auto& s : v) {
			file << s << delimiter;
		}
		file << '\n';
	}
	file.close();
	std::cout << "File saved";
	return;
}

std::ostream& operator<<(std::ostream& os, const CSV_Parser& csvp) {
	
	return os;
}