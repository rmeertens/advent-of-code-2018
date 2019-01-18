
#include <map>


bool has_n_occurances(std::string input, int n){
    for(int index=0; index < input.size(); index++){
        char atindex = input[index];
        if (std::count(input.begin(), input.end(), atindex) == n){
            return true;
        }
    }
    return false;
}

void print_checksum_day2part1(std::string filename){
    std::ifstream inFile(filename);
    std::string input;
    int with_two = 0;
    int with_three = 0;
    while(inFile >> input){
        if(has_n_occurances(input, 2)){
            with_two++;
        }
        if(has_n_occurances(input, 3)){
            with_three++;
        }


    }
    std::cout << with_two * with_three << std::endl;
}

std::vector<std::string> get_input(std::string filename){
    std::ifstream in(filename);
    std::istream_iterator<std::string> b{in};
    std::istream_iterator<std::string> e;
    std::vector<std::string> input(b, e);
    return input;
}

std::vector<std::pair<std::string, std::string>> get_id_combinations(std::vector<std::string> input){
    std::vector<std::pair<std::string, std::string>> combinations;
    for(int i=0; i < input.size(); i++){
        for(int j=0; j < i; j++ ){
            combinations.push_back({input[i], input[j]});
        }
    }
    return combinations;
}

int main(int argc, const char * argv[]) {
    print_checksum_day2part1("/Users/rmeertens/Dropbox/workspace/adventofcode2018/input/input_day2.txt");
}
