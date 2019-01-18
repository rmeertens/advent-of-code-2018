#include <iostream>
#include <fstream>
#include <regex>
#include <string>
#include <map>

struct SoldierInput{
    int id;
    std::string time;
    int minutes;
    std::string raw;
};


bool myfunction (SoldierInput i,SoldierInput j) {
    long long int time1 = std::stoi(i.time);
    long long int time2 = std::stoi(j.time);
    return (time1 < time2);
}

std::istream &operator>>(std::istream &in, SoldierInput &r) {
    std::string line;

    std::getline(in, line);
    r.raw = line;
    if(line.length() > 1) {

        std::regex digit_regex("\\d+");
        std::sregex_iterator words_begin = std::sregex_iterator(line.begin(), line.end(), digit_regex);
        std::string year = (*words_begin++).str();
        std::string month = (*words_begin++).str();
        std::string day = (*words_begin++).str();
        std::string hour = (*words_begin++).str();
        std::string minute = (*words_begin++).str();
        r.minutes = std::stoi(minute);

        std::sregex_iterator words_end = std::sregex_iterator();
        if (std::distance(words_begin, words_end) == 1) { // 1 left...
            std::string guardid = (*words_begin++).str();

            r.id = std::stoi(guardid);
        }
        else{
            r.id = -1;
        }

        r.time = month + day + hour + minute;
    }
    return in;
}


struct Result1{
    int totalAsleep;
    int soldierId;
    int minuteMostAsleep;
};

bool compareTotalSleeptime (Result1 i, Result1 j) {

    return (i.totalAsleep < j.totalAsleep);
}

int main(int argc, char* args[]){
    std::cout << "Hey jude" << argc << std::endl;
    for(int x=0; x < argc ; x++){
        std::cout << "file: " << args[x] << std::endl;
    }
    std::ifstream inFile;
    inFile.open(args[1]);

    if(!inFile){
        std::cout << "error reading file";
        exit(1);
    }

    std::vector<SoldierInput> data_in(std::istream_iterator<SoldierInput>{inFile}, std::istream_iterator<SoldierInput>{});
    std::sort(data_in.begin(), data_in.end(), myfunction);

    std::map<int, std::vector<int>> id_array;
    int currentSoldier = 0;
    int fellasleep = 0;
    for(auto a : data_in){
        if(a.id > 0){
            currentSoldier = a.id;
            if(id_array.find(currentSoldier) == id_array.end()){
                std::vector<int> m(60, 0);
                id_array[currentSoldier] = m;
            }
        }
        else if(a.raw.find("falls") !=std::string::npos){
            fellasleep = a.minutes;
        }
        else if(a.raw.find("wakes") != std::string::npos){
            for(int pos=fellasleep; pos < a.minutes; pos++){
                id_array[currentSoldier][pos]++;//block(fellasleep, a.minutes - fellasleep) += toadd;
            }
        }
    }

    std::vector<Result1> results;
    for (auto const& x : id_array)
    {
        Result1 result;
        result.soldierId = x.first;
        int sum = 0;
        int max = 0;
        int argmax = 0;
        for(int pos=0; pos < x.second.size(); pos++ ){
            sum += x.second[pos];
            if(x.second[pos] > max){
                max = x.second[pos];
                argmax = pos;
            }
        }
        result.totalAsleep = sum;
        result.minuteMostAsleep = argmax;
        results.push_back(result);
    }


    std::sort(results.begin(), results.end(), compareTotalSleeptime);
    for(auto a : results){
        std::cout << a.soldierId << " " << a.totalAsleep << " " << a.minuteMostAsleep << std::endl;
    }

    // Print the top minute!
    int maxMinute = 0;
    int maxGuardTimesMinute;

    for(int minute = 0; minute < 60; minute++){
        for (auto const& x : id_array)
        {
            if(x.second[minute] > maxMinute){
                maxMinute = x.second[minute];
                maxGuardTimesMinute = minute * x.first;

            }
        }
    }
    std::cout << maxGuardTimesMinute;
    return 0;
}
