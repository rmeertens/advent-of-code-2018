
#include <string>
#include <map>
#include <fstream>
#include <iostream>
#include <vector>
#include <cassert>

void create_recipe(std::vector<int> &state, int &elf1, int &elf2){
    int combined = state[elf1] + state[elf2];
    if (combined >= 10){
        state.push_back(combined/10);
    }
    state.push_back(combined%10);
    
    elf1 = elf1 + state[elf1]+1;
    elf2 = elf2 + state[elf2]+1;
    elf1 %= state.size();
    elf2 %= state.size();
}

void print_score(std::vector<int>::iterator begin, std::vector<int>::iterator end){
    assert(std::distance(begin, end)==10);
    while(begin != end){
        std::cout << *begin;
        begin++;
    }
    std::cout << std::endl;
}
int main(int arc, const char* argv[]){
    std::vector<int> state;
    state.push_back(3);
    state.push_back(7);
    
    int elf1 = 0;
    int elf2 = 1;
    
    int watchfor = 306281;
    std::string s = "306281";
    std::vector<int> tofind;
    for(const char x : s){
        tofind.push_back(x - '0');
    }
    
    
    for (int x=0; x < 30298300; x++){
        create_recipe(state, elf1, elf2);
        if(state.size() > tofind.size()){
            if(std::equal(tofind.begin(), tofind.end(), state.end()-tofind.size())){
                std::cout << "FOUND after " << x << " and distance is " << std::distance(state.begin(), state.end()-tofind.size()) << std::endl;
                
            }
            if(std::equal(tofind.begin(), tofind.end(), state.end()-tofind.size()-1)){
                std::cout << "FOUND after " << x << " and distance is " << std::distance(state.begin(), state.end()-tofind.size()-1) << std::endl;
            }
        }
        
    }
    
    
    print_score(state.begin()+watchfor , state.begin()+watchfor +10);
    
    
    
}
