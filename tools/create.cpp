#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <iterator>
#include <json/json.h>

template<typename Out>
void split(const std::string &s, char delim, Out result) {
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        *(result++) = item;
    }
}

std::vector<std::string> split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    split(s, delim, std::back_inserter(elems));
    return elems;
}

int main() {
    Json::Value root;
    std::string name;
    std::string tempval;
    int width;
    int height;
    std::cout << "File name: ";
    std::cout.flush();
    std::cin >> name;
    std::cin.ignore(100, '\n');
    std::cout << "Width: ";
    std::cout.flush();
    std::cin >> tempval;
    width = std::stoi(tempval);
    root["width"] = Json::Value(width);
    std::cin.ignore(100, '\n');
    std::cout << "Height: ";
    std::cout.flush();
    std::cin >> tempval;
    height = std::stoi(tempval);
    root["height"] = Json::Value(height);
    std::cin.ignore(100, '\n');
    std::cout << "Box width: ";
    std::cout.flush();
    std::cin >> tempval;
    root["boxWidth"] = Json::Value(std::stoi(tempval));
    std::cin.ignore(100, '\n');
    std::cout << "Box height: ";
    std::cout.flush();
    std::cin >> tempval;
    root["boxHeight"] = Json::Value(std::stoi(tempval));
    std::cin.ignore(100, '\n');
    std::cout << "Maximum number: ";
    std::cout.flush();
    std::cin >> tempval;
    root["maxNum"] = std::stoi(tempval);
    root["grid"] = Json::Value(Json::arrayValue);
    std::cout << "Enter each line, delimited with spaces, below. The file will be completed once all lines are entered.\n";
    std::cin.ignore(100, '\n');
    for (int i = 0; i < height; i++) {
        std::cout << "Line " << i + 1 << ": ";
        std::cout.flush();
        std::getline(std::cin, tempval);
        std::vector<std::string> nums = split(tempval, ' ');
        Json::Value temp(Json::arrayValue);
        for (int j = 0; j < width; j++) temp.append(Json::Value(std::stoi(nums[j])));
        root["grid"].append(temp);
    }
    std::ofstream out;
    out.open(name.c_str());
    out << root;
    out.close();
    return 0;
}
