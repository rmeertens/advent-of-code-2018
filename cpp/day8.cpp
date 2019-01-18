#include <iostream>
#include <fstream>
#include <set>
#include <vector>
#include <numeric>
#include <iterator>
#include <algorithm>
#include <cassert>
#include <map>

struct Tree{
    std::vector<Tree> children;
    std::vector<int> metadata;
};


Tree extract_data(std::vector<int> &numbers ){
    Tree tree;
    int childnodes = numbers[0];
    int num_metadata = numbers[1];
    numbers.erase(numbers.begin());
    numbers.erase(numbers.begin());

    for (int x =0; x < childnodes; x++){
        tree.children.push_back(extract_data(numbers));
    }

    for(int x=0; x < num_metadata; x++){
        tree.metadata.push_back(numbers[0]);
        numbers.erase(numbers.begin());
    }
    return tree;
}

int sum_metadata(Tree tree){
    int summetadata = 0;
    for(int x : tree.metadata){
        summetadata += x;
    }

    int sumchildren = 0;
    for(Tree child : tree.children){
        sumchildren += sum_metadata(child);
    }
    return sumchildren + summetadata;
}

int second_sum(Tree tree){
    if (tree.children.size()== 0){
        int summeta = 0;
        for(int x : tree.metadata){
            summeta += x;
        }
        return summeta;
    }

    int sumofthisone = 0;
    for(int childindex : tree.metadata){
        childindex-=1; // No Matlab here!
        if (childindex < tree.children.size()){
            sumofthisone += second_sum(tree.children[childindex]);
        }
    }
    return sumofthisone;

}

int main(int argc, const char * argv[]) {
    int nextnum;
    std::ifstream inFile;
    inFile.open(argv[1]);
    std::vector<int> input;
    while(inFile >> nextnum){
        input.push_back(nextnum);
    }
    Tree tree = extract_data(input);
    std::cout << sum_metadata(tree) << std::endl;
    std::cout << second_sum(tree) << std::endl;
    return 0;
}
