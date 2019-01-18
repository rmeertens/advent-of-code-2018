

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <set>
#include <vector>
#include <numeric>
#include <iterator>


int countSumFile(std::string fileName){
    std::ifstream inFile(fileName);
    std::istream_iterator<int> i_begin{ inFile};
    std::istream_iterator<int> i_end{};
    int sum = std::accumulate(i_begin, i_end, 0);
    return sum;
}

int findFirstDuplicate(std::string fileName){
    std::ifstream inFile;
    inFile.open(fileName);

    if (!inFile) {
        std::cerr << "Unable to open file " << fileName;
        exit(1);   // call system to stop
    }
    std::set<int> seennumbers;
    int sum = 0;
    int x;
    while(true){
        inFile.clear();
        inFile.seekg(0, std::ios::beg);

        while (inFile >> x) {
            sum += x;
            if(seennumbers.find(sum) != seennumbers.end()){
                return sum;
            }
            seennumbers.insert(sum);

        }
    }
}


int main(int argc, const char * argv[]) {
    std::cout << countSumFile("/Users/rmeertens/Dropbox/workspace/adventofcode2018/input/input_day1.txt") << std::endl;
    std::cout << findFirstDuplicate("/Users/rmeertens/Dropbox/workspace/adventofcode2018/input/input_day1.txt") << std::endl;
}
