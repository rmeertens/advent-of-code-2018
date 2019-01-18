
#include <benchmark/benchmark.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <set>
#include <algorithm>
#include <cassert>
#include <list>

using Charvector = std::list<char>;

struct DependencyAndLetter{
    Charvector vec;
    char letter;
};

struct Dependency{
    char first;
    char second;
};


using DependencyList = std::vector<DependencyAndLetter>;

std::istream &operator>>(std::istream &in, Dependency &r) {
    std::string line;
    std::getline(in, line);

    r.first = line[5];
    r.second= line[36];

    return in;
}

Charvector get_dependencys(char letter, std::vector<Dependency> dependencies){
    Charvector dofirst;
    for(auto d : dependencies){
        if(d.second == letter){
            Charvector deps = get_dependencys(d.first, dependencies);
            for(auto letter : deps){
                dofirst.push_back(letter);
            }
            dofirst.push_back(d.first);
        }
    }
    return dofirst;
}

bool wayToSort(DependencyAndLetter i, DependencyAndLetter j) {
    if(i.vec.size() != j.vec.size()){
        return i.vec.size() < j.vec.size();
    }
    return i.letter < j.letter;
}

void resolve_dependency(char letter, DependencyList& list){
    for(auto& temp : list){
        temp.vec.remove(letter);
    }
}
std::string parta(std::vector<DependencyAndLetter> copy_letter_prio){
    std::string result;
    while(copy_letter_prio.size() > 0){
        std::sort(copy_letter_prio.begin(), copy_letter_prio.end(), wayToSort);

        DependencyAndLetter nextup = copy_letter_prio[0];
        copy_letter_prio.erase(copy_letter_prio.begin()); // TODO use a datastructure that allows me to pop...

        if(nextup.vec.size()!=0){
            throw "NOOO";
        }

        result += nextup.letter;

        resolve_dependency(nextup.letter, copy_letter_prio);
    }

    return result;
}

struct TimeRemainingForChar{
    int seconds;
    char character;
};

bool still_processing(std::vector<TimeRemainingForChar> vec){
    for(auto p : vec){
        if(p.seconds > 1){
            return true;
        }
    }
    return false;
}

void partb(std::vector<DependencyAndLetter> letter_prio){


    int second = 0;
    int NUM_WORKERS = 5;
    int TIME_PENALTY = 60;
    std::vector<TimeRemainingForChar> remaining_seconds;
    for(int x = 0; x < NUM_WORKERS; x++){
        remaining_seconds.push_back({0, '*'});
    }

    while(letter_prio.size() > 0 || still_processing(remaining_seconds)) {
        second++;
        for (int index = 0; index < remaining_seconds.size(); index++) {
            remaining_seconds[index].seconds--;
        }

        for (int index_seconds = 0; index_seconds < remaining_seconds.size(); index_seconds++) {
            TimeRemainingForChar temp = remaining_seconds[index_seconds];
            if (temp.seconds <= 0) {
                // remove the letter that just got resolved
                for (int x = 0; x < letter_prio.size(); x++) {
                    letter_prio[x].vec.remove(temp.character);
                }

                std::sort(letter_prio.begin(), letter_prio.end(), wayToSort);


                // If we are already resolving the last one: keep resolving this...
                if(letter_prio.size() == 0)
                    continue;

                // Start tackling the next challenge...
                DependencyAndLetter nextChallenge = letter_prio[0];
                if(nextChallenge.vec.size() == 0){ // Can be non-empty if not all dependencies resolved...
                    letter_prio.erase(letter_prio.begin());

                    TimeRemainingForChar newChallenge;
                    newChallenge.character = nextChallenge.letter;
                    newChallenge.seconds = TIME_PENALTY + newChallenge.character - 'A' +1;
                    remaining_seconds[index_seconds] = newChallenge;
                }
            }
        }

    }

    std::cout << "Done after seconds: " << second << std::endl;
}
int main(int argc, char* args[]){
   std::ifstream inFile;
   inFile.open(args[1]);
   std::vector<Dependency> data_in(std::istream_iterator<Dependency>{inFile}, std::istream_iterator<Dependency>{});
   std::set<char> knowncharacters;
   for(auto d : data_in){
       knowncharacters.insert(d.first);
       knowncharacters.insert(d.second);
   }
   std::vector<DependencyAndLetter> letter_prio;
   for(char letter : knowncharacters){
       DependencyAndLetter temp;
       temp.letter = letter;
       temp.vec = get_dependencys(letter, data_in);

       letter_prio.push_back(temp);
   }

   std::string resparta = parta(letter_prio);
   std::cout << "Part a: " << resparta << std::endl;
   if(resparta != "DFOQPTELAYRVUMXHKWSGZBCJIN"){
       throw "You fucked up son";
   }
   partb(letter_prio);
}





//
//
// class MyFixture : public benchmark::Fixture
// {
// public:
//     MyFixture(){
//
//     }
//
// };
//
// BENCHMARK_DEFINE_F(MyFixture, MyMethod)(benchmark::State& state)
// {
//     std::ifstream inFile;
//     inFile.open("course/dojo/5_stream_processing/input_day7.txt");
//     std::vector<Dependency> data_in(std::istream_iterator<Dependency>{inFile}, std::istream_iterator<Dependency>{});
//     std::set<char> knowncharacters;
//     for(auto d : data_in){
//         knowncharacters.insert(d.first);
//         knowncharacters.insert(d.second);
//     }
//     std::vector<DependencyAndLetter> letter_prio;
//     for(char letter : knowncharacters){
//         DependencyAndLetter temp;
//         temp.letter = letter;
//         temp.vec = get_dependencys(letter, data_in);
//
//         letter_prio.push_back(temp);
//     }
//
//
//
//     for (auto _ : state)
//     {
//         std::string resparta = parta(letter_prio);
//     }
//
// }
//
//
// BENCHMARK_REGISTER_F(MyFixture, MyMethod)->Unit(benchmark::kMillisecond);
// BENCHMARK_MAIN();
