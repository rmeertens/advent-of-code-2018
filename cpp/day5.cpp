
#include <string>
#include <vector>
#include <stack>
#include <iostream>
#include <fstream>
#include <algorithm>

bool polarityEqual(char a, char b){
    return tolower(a) == tolower(b) && a !=b;
}

std::string replace(std::string input, char character){
    input.erase(std::remove(input.begin(), input.end(), character), input.end());
    input.erase(std::remove(input.begin(), input.end(), toupper(character)), input.end());
    return input;
}
unsigned long sizesimplify(std::string input){
    std::stack<char> simplified;
    simplified.push(input[0]);
    for(int index=1; index < input.size(); index++){
        // std::cout << "Adding: " << input[index] << " top is: " << simplified.top() << std::endl;
        if(simplified.size() > 0 && polarityEqual(input[index], simplified.top())){
            simplified.pop();
        }
        else{
            simplified.push(input[index]);
        }
    }
    return simplified.size();
}
int main(int argc, char* args[]) {
    std::string alphabet = "abcdefghijklmnopqrstuvwxyz";
    std::ifstream inFile;
    inFile.open(args[1]);

    std::string dailyinput;
    inFile >> dailyinput;

    std::cout << sizesimplify(dailyinput) << std::endl;

    int minneeded = 1000000;
    for(char c : alphabet){
        std::string withoutc = replace(dailyinput, c);
        int length = sizesimplify(withoutc);
        minneeded = std::min(length, minneeded);
    }
    std::cout << minneeded << std::endl;

}
