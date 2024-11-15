#pragma once
#include <map>
#include <string>
#include <vector>

class JSON_Parser {
private:
	std::map<std::string, std::vector<std::string>> data_;
	std::pair<std::string, std::vector<std::string>> parse(const std::string& s);
public:
	void load(const std::string& filename);
	std::string get(const std::string& key, int id);
	std::vector<std::string> operator[](const std::string& key);
	void set(const std::string& key, int id, const std::string& s);
	void add(const std::string& key, const std::string& s);
	void save(const std::string& filename);
};