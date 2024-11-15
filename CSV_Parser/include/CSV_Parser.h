#pragma once
#include <vector>
#include <string>
#include <fstream>
#include <map>

class CSV_Parser {
private:
	bool hasheader_;
	std::vector<std::string> header_;
	std::vector<std::vector<std::string>> data_;
	std::map<const std::string, int> indtocolname_;

	std::vector<std::string> parseLine(const std::string& line, char delimiter);
public:
	friend std::ostream& operator<<(std::ostream& os, const CSV_Parser& csvp);
	void load(const std::string& filename, bool hasheader, char delimiter);
	std::vector<std::string> operator[](int n);
	std::string get(int rowindex, const std::string& colname) const;
	void set(int rowindex, const std::string& colname, std::string val);
	void save(const std::string& filename, bool writeheader, char delimiter) const;
};