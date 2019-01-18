#include <iostream>
#include <fstream>
#include <cassert>
#include <vector>
#include <sstream>
#include <string>
#include <regex>
#include <string>

#include <Eigen/Dense>
using Eigen::ArrayXXf;

int main()
{
    std::ifstream inFile;
    inFile.open("/Users/roland/Dropbox/workspace/adventofcode2018/input/input_day3.txt");
    std::string input_string;

    if(!inFile){
        std::cout << "error reading file";
        exit(1);
    }

    std::string line;
    std::regex digit_regex("\\d+");
    int width_square = 1000;

    ArrayXXf m = ArrayXXf::Constant(width_square, width_square, 0);
    while(std::getline(inFile, line)){
        std::sregex_iterator words_begin = std::sregex_iterator(line.begin(), line.end(), digit_regex);
        std::sregex_iterator words_end = std::sregex_iterator();
        assert(std::distance(words_begin, words_end) == 5);
        int id = std::stoi((*words_begin++).str());
        int xstart = std::stoi((*words_begin++).str());
        int ystart = std::stoi((*words_begin++).str());
        int width = std::stoi((*words_begin++).str());
        int height = std::stoi((*words_begin++).str());
        ArrayXXf toadd = ArrayXXf::Constant(height, width, 1);
        m.block(ystart,xstart,height, width) += toadd;
    }

    std::cout << (m > 1.0).count() << std::endl;
    inFile.clear();
    inFile.seekg(0, std::ios::beg);

    while(std::getline(inFile, line)){
        std::sregex_iterator words_begin = std::sregex_iterator(line.begin(), line.end(), digit_regex);
        std::sregex_iterator words_end = std::sregex_iterator();
        assert(std::distance(words_begin, words_end) == 5);
        int id = std::stoi((*words_begin++).str());
        int xstart = std::stoi((*words_begin++).str());
        int ystart = std::stoi((*words_begin++).str());
        int width = std::stoi((*words_begin++).str());
        int height = std::stoi((*words_begin++).str());

        ArrayXXf compare = ArrayXXf::Constant(height, width, 1);
        auto compared = (m.block(ystart,xstart,height, width) ==compare);
        if(compared.all()){
            std::cout << id << std::endl;
        }

    }
    inFile.close();

    return 0;
}