#include "readdbc.hpp"


int main(){
	std::vector<DbcFile> dbc = ReadDbcFile("C:\\Users\\0133752\\Documents\\Visual Studio 2013\\Projects\\CANUSB\\Release\\DPX_CAN.dbc");
	for (unsigned int i = 0; i < dbc.size(); ++i){
		std::cout << "ID: 0x" << std::hex << dbc[i].id << ", " << std::dec;
		std::cout << "Name: " << dbc[i].name << ", ";
		std::cout << "Length: " << dbc[i].length << ", ";
		std::cout << "Reference: " << dbc[i].length << ", " << std::endl;
		for (int j = 0; j < dbc[i].names.size(); ++j){
			std::cout << "    Names: " << dbc[i].names[j] << ", ";
			std::cout << "StartBit: " << dbc[i].start_bit[j] << ", ";
			std::cout << "Endian: " << dbc[i].endian[j] << ", ";
			std::cout << "Type: " << dbc[i].type[j] << ", ";
			std::cout << "Gain: " << dbc[i].gain[j] << ", ";
			std::cout << "Bias: " << dbc[i].bias[j] << ", ";
			std::cout << "Min: " << dbc[i].minimum[j] << ", ";
			std::cout << "Max: " << dbc[i].maximum[j] << ", ";
			std::cout << "Unit: " << dbc[i].unit[j] << ", ";
			std::cout << "References: " << dbc[i].references[j] << std::endl;
		}
	}
	getchar();
	return 0;
}