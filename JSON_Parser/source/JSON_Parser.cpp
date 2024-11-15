#include "JSON_Parser.h"
#include <fstream>
#include <sstream>

std::pair<std::string, std::vector<std::string>> JSON_Parser::parse(const std::string& s) {
	std::stringstream ss;
	ss << s;
	std::string key;
	std::getline(ss, key, ':');
	std::vector<std::string> values;
	std::string val;
	while (std::getline(ss, val, ',')) {
		values.push_back(val);
	}
	return { key, values };
}

void JSON_Parser::load(const std::string& filename) {
	std::ifstream file(filename);
	if (!file.is_open()) {
		throw std::runtime_error("Cant open the file");
	}
	std::string line;
	while (std::getline(file, line)) {
		if ([](std::string str) -> bool {
			for (auto& s : str) {
				if (s == '}' || s == '{') return true;
			}
			return false;
			}(line)) continue;
		else {
			std::pair<std::string, std::vector<std::string>> parsedLine = parse(line);
			data_[parsedLine.first] = parsedLine.second;
		}
	}
	file.close();
	return;
}

std::string JSON_Parser::get(const std::string& key, int id) {
	if (data_.find(key) == data_.end()) throw std::runtime_error("No such key in map");
	if (id > data_[key].size()) throw std::out_of_range("Out of range");
	return data_[key][id];
}

std::vector<std::string> JSON_Parser::operator[](const std::string& key) {
	if (data_.find(key) == data_.end()) throw std::runtime_error("No such key in map");
	return data_[key];
}

void JSON_Parser::set(const std::string& key, int id, const std::string& s) {
	if (data_.find(key) == data_.end()) throw std::runtime_error("No such key in map");
	if (data_[key].size() < id) throw std::out_of_range("Out of range");
	data_[key][id] = s;
	return;
}

void JSON_Parser::add(const std::string& key, const std::string& s) {
	data_[key].push_back(s);
}

void JSON_Parser::save(const std::string& filename) {
	std::ofstream file(filename);
	if (!file.is_open()) throw std::runtime_error("Cant open the file");
	file << '{';
	for (std::map<std::string, std::vector<std::string>>::iterator itr = data_.begin(); itr != data_.end(); ++itr) {
		file << (*itr).first << ":";
		for (auto& s : (*itr).second) {
			file << s << ",";
		}
		file << '\n';
	}
	file << '}';
	return;
}
