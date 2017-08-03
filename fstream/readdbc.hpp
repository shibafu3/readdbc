#ifndef READDBC_HPP
#define READDBC_HPP

#include <iostream>
#include <fstream>
#include <sstream>

#include <vector>


int GetWord(std::string file_path, std::vector<std::string> &strings, std::vector<int> &id, std::vector<int> &num){
	std::ifstream ifs(file_path, std::ios::in);
	std::string line;

	while (getline(ifs, line)){
		std::istringstream iss(line);
		std::string str;
		int count = 0;
		if (line != "\0"){
			while (getline(iss, str, ' ')){
				if (str != "\0"){
					switch (count){
					case 0:
						strings.push_back(str);
						++count;
						break;
					case 1:
						id.push_back(std::stoi(str, nullptr, 16));
						++count;
						break;
					case 2:
						num.push_back(std::stoi(str));
						++count;
						break;
					default:
						break;
					}
				}
			}
		}
	}
	return 0;
}

class DbcFile{
public:
	int id;
	std::string name;
	int length;
	std::string reference;
	std::vector<std::string> names;
	std::vector<int> start_bit;
	std::vector<int> bit_num;
	std::vector<double> endian;
	std::vector<char> type;
	std::vector<double> gain;
	std::vector<double> bias;
	std::vector<double> minimum;
	std::vector<double> maximum;
	std::vector<std::string> unit;
	std::vector<std::string> references;
	DbcFile(){};
	DbcFile(int id_in, std::string name_in, int length_in, std::vector<std::string> names_in, std::vector<int> from_bit_in, std::vector<int> bit_num_in){
		id = id_in;
		name = name_in;
		length = length_in;
		names = names_in;
		start_bit = from_bit_in;
		bit_num = bit_num_in;
	}
	void Clear(){
		id = 0;
		name = "\0";
		length = 0;
		names.clear();
		start_bit.clear();
		bit_num.clear();
	}
};
std::string Split(const std::string &line, const char c, int n){
	std::istringstream ifs(line);
	std::string str = "\0";
	int i = 0;
	while (getline(ifs, str, c)){
		if ((++i) == n){ return str; }
	}
	return str;
}
std::vector<DbcFile> ReadDbcFile(const char *dbc_file){
	std::ifstream ifs(dbc_file, std::ios::in);
	std::string line;
	std::string str;
	std::vector<DbcFile> datas;
	while (getline(ifs, line)){
		std::istringstream BO_SG_(line);
		while (getline(BO_SG_, str, ' ')){
			if (str == "BO_"){
				datas.resize(datas.size() + 1);

				getline(BO_SG_, str, ' ');
				datas[datas.size() - 1].id = stoi(str);

				getline(BO_SG_, str, ' ');
				datas[datas.size() - 1].name = Split(str, ':', 1);

				getline(BO_SG_, str, ' ');
				datas[datas.size() - 1].length = stoi(str);

				getline(BO_SG_, str, ' ');
				datas[datas.size() - 1].reference = str;
			}

			if (str == "SG_"){
				getline(BO_SG_, str, ' ');
				datas[datas.size() - 1].names.push_back(str);

				getline(BO_SG_, str, ' ');
				getline(BO_SG_, str, ' ');
				datas[datas.size() - 1].start_bit.push_back(stoi(Split(str, '|', 1)));
				datas[datas.size() - 1].bit_num.push_back(stoi(Split(Split(str, '|', 2), '@', 1)));
				datas[datas.size() - 1].endian.push_back(atoi(&Split(Split(str, '|', 2), '@', 2)[0]));
				datas[datas.size() - 1].type.push_back(Split(Split(str, '|', 2), '@', 2)[1]);

				getline(BO_SG_, str, ' ');
				datas[datas.size() - 1].gain.push_back(stod(Split(Split(str, ',', 1), '(', 2)));
				datas[datas.size() - 1].bias.push_back(stod(Split(Split(str, ',', 2), ')', 1)));

				getline(BO_SG_, str, ' ');
				datas[datas.size() - 1].minimum.push_back(stod(Split(Split(str, '|', 1), '[', 2)));
				datas[datas.size() - 1].maximum.push_back(stod(Split(Split(str, '|', 2), ']', 1)));

				getline(BO_SG_, str, ' ');
				datas[datas.size() - 1].unit.push_back(Split(str, '"', 1));

				getline(BO_SG_, str, ' ');
				datas[datas.size() - 1].references.push_back(str);
			}
		}
	}

	//for (int i = 0; i < datas.size(); ++i){
	//	std::cout << "ID: 0x" << std::hex << datas[i].id << ", " << std::dec;
	//	std::cout << "Name: " << datas[i].name << ", ";
	//	std::cout << "Length: " << datas[i].length << ", ";
	//	std::cout << "Reference: " << datas[i].length << ", " << std::endl;
	//	for (int j = 0; j < datas[i].names.size(); ++j){
	//		std::cout << "    Names: " << datas[i].names[j] << ", ";
	//		std::cout << "StartBit: " << datas[i].start_bit[j] << ", ";
	//		std::cout << "Endian: " << datas[i].endian[j] << ", ";
	//		std::cout << "Type: " << datas[i].type[j] << ", ";
	//		std::cout << "Gain: " << datas[i].gain[j] << ", ";
	//		std::cout << "Bias: " << datas[i].bias[j] << ", ";
	//		std::cout << "Min: " << datas[i].minimum[j] << ", ";
	//		std::cout << "Max: " << datas[i].maximum[j] << ", ";
	//		std::cout << "Unit: " << datas[i].unit[j] << ", ";
	//		std::cout << "References: " << datas[i].references[j] << std::endl;
	//	}
	//}
	//getchar();
	return datas;
}


#endif