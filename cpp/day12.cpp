#include <iostream>
#include <fstream>
#include <regex>
#include <string>
#include <cassert>

struct BeforeAfter{
    std::string before;
    std::string after;
};


std::istream &operator>>(std::istream &in, BeforeAfter &r) {
    std::string junk;
    in >> r.before;
    in >> junk;
    in >> r.after;
    return in;
}

char get_transition(std::string input, std::vector<BeforeAfter> &transitions){
    for(BeforeAfter a : transitions)
    {
        if(input == a.before){
            return a.after[0];
        }
    }
    return '?';
}

std::pair<int,std::string> get_string_and_offset(int offset, std::string s, std::vector<BeforeAfter> &transitions){
    s = "......" + s + ".....";
    offset -=4;
    std::string toappend = "";
    for(unsigned int index = 0; index < s.size()-5; index++){
        std::string whatthefuck = s.substr(index, 5);
        toappend += get_transition(whatthefuck, transitions);
    }
    while(toappend[0] == '.'){
        toappend = toappend.substr(1,toappend.size());
        offset += 1;
    }
    while(toappend[toappend.size()-1] == '.'){
        toappend = toappend.substr(0,toappend.size()-1);
    }
    return std::pair<int,std::string>(offset, toappend);
};

int get_value(int offset, std::string s){
    int totalsum = 0;
    for(int index=0; index < s.size(); index++){
        if(s[index] == '#'){
            int toadd = index+offset;
            totalsum += toadd;
        }
    }
    return totalsum;
}
int main(int argc, char* args[]) {
    std::ifstream inFile;
    inFile.open(args[1]);

    if(!inFile){
        std::cout << "error reading file";
        exit(1);
    }
    std::string junk;
    std::string startinput;
    inFile >> junk >> junk >> startinput;
    std::cout << startinput << std::endl;
    std::vector<BeforeAfter> data_in(std::istream_iterator<BeforeAfter>{inFile}, std::istream_iterator<BeforeAfter>{});

    int offset = 0;
    long long int totaliterations = 50000000000;
    std::string state = startinput;

    for(long long int iteration=0; iteration < totaliterations; iteration++) {
        std::cout << "State now: " << state << std::endl;
         if(iteration==20){
             std::cout << "\n\nIteration " << iteration << " has value " << get_value(offset, state) << std::endl;
         }

        std::pair<int, std::string> newvals = get_string_and_offset(offset, state, data_in);
        if(newvals.second == state){
            std::cout << "LOOPED! at " << iteration << std::endl;
            int old_value = get_value(offset, state);
            int new_value = get_value(newvals.first, newvals.second);
            int loopadd = new_value - old_value;
            std::cout << new_value + (totaliterations-iteration-1)*loopadd << std::endl;
            break;
        }
        state = newvals.second;
        offset = newvals.first;
    }
}
