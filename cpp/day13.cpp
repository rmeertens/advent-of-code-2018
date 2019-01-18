#include <iostream>
#include <fstream>
#include <set>
#include <vector>
#include <numeric>
#include <iterator>
#include <algorithm>
#include <cassert>
#include <map>
#include <queue>
//#include "day1.h"
//#include "day2.h"
//
//void day1(){
//    int sum = countSumFile("/Users/roland/Dropbox/workspace/adventofcode2018/input.txt");
//    std::cout << sum << std::endl;
//    int dup = findFirstDuplicate("/Users/roland/Dropbox/workspace/adventofcode2018/input.txt");
//    std::cout << dup << std::endl;
//}
//
//void day2(){
//    typedef std::pair<std::string, std::string> stringpair;
//    print_checksum_day2part1("/Users/roland/Dropbox/workspace/adventofcode2018/input_day2.txt");
//    std::vector<std::string> inputs = get_input("/Users/roland/Dropbox/workspace/adventofcode2018/input_day2.txt");
//
//    std::vector<stringpair> combinations = get_id_combinations(inputs);
//
//    auto diff_char_distance = [&](const std::string id1, const std::string id2){
//        int distance = 0 ;
//        for(int index = 0; index < id1.size(); index++){
//            if(id1[index] != id2[index]){
//                distance++;
//            }
//        }
//        return distance;
//    };
//
//    for(stringpair combi : combinations){
//        if (diff_char_distance(combi.first, combi.second)==1){
//
//            // Print the common part...
//            for(int index_word = 0; index_word < combi.first.size(); index_word++){
//                if(combi.first[index_word] == combi.second[index_word]){
//                    std::cout << combi.first[index_word] ;
//                }
//
//            }
//            std::cout <<std::endl;
//        }
//    }
//}




//struct Point{
//    int x;
//    int y;
//};
//
//
//std::istream &operator>>(std::istream &in, Point &x) {
//    char discard;
//    in >> x.x >> discard >> x.y;
//    return in;
//}
//
//std::vector<Point> get_input(std::string filename){
//    std::ifstream in(filename);
//
//    std::istream_iterator<Point> b{in};
//    std::istream_iterator<Point> e;
//    std::vector<Point> input(b, e);
//    return input;
//}
//
//// Return the index of the element which has the min distance...
//int mindist(Point point, std::vector<Point> coords){
//    std::vector<int> distances;
//    for(Point p : coords){
//        distances.push_back(abs(p.x-point.x)+abs(p.y-point.y));
//    }
//    std::vector<int> copy(distances);
//    std::sort(copy.begin(), copy.end(), std::less<int>());
//    if(copy[0] == copy[1]){
//        return -1;
//    }
//    if(copy[0] != copy[1]){
//        for(int index=0; index < coords.size(); index++){
//            if(distances[index] == copy[0]){
//                return index;
//            }
//        }
//    }
//    throw "For some reason did  ";
//}
//
//int a(std::vector<Point> coords){
//    int max_x = 0;
//    int max_y = 0;
//    for(auto p : coords){
//        max_x = std::max(max_x, p.x);
//        max_y = std::max(max_y, p.y);
//    }
//    max_x+=1;
//    max_y+=1;
//
//    std::set<int> valids;
//    int grid[max_y][max_x];
//
//    for(int x=0; x < coords.size(); x++){
//        valids.insert(x);
//    }
//
//    for(int x=0; x < max_x; x++){
//        for(int y=0; y < max_y; y++){
//            grid[y][x] = -1;
//        }
//    }
//
//    for(int x=0; x < max_x; x++){
//        for(int y=0; y < max_y; y++){
//            grid[y][x] = mindist({x,y}, coords);
//            bool edge = (x == 0 || y == 0 || x == max_x - 1 || y == max_y - 1);
//            if(edge){
//                if(valids.find(grid[y][x]) != valids.end()){
//                    valids.erase(valids.find(grid[y][x]));
//                }
//            }
//
//        }
//    }
//
//    std::map<int,int> counts;
//
//    for(int v : valids){
//        counts[v] = 0;
//    }
//
//    for(int x=0; x < max_x; x++){
//        for(int y=0; y < max_y; y++){
//            int ic = grid[y][x];
//            if (valids.find(ic) != valids.end()){
//                counts[ic] = counts[ic]+ 1;
//            }
//        }
//    }
//
//    int max = 0;
//    for ( auto it = counts.begin(); it != counts.end(); it++ ){
//        max = std::max(max, it->second);
//    }
//    return max;
//}
//
//int b(std::vector<Point> coords){
//    int max_x = 400;
//    int max_y = 400;
//
//    int total_in_reach = 0;
//    for(int x=0; x < max_x; x++){
//        for(int y=0; y < max_y; y++){
//            int sum = 0;
//            for(auto p : coords){
//                sum += abs(x-p.x) + abs(y-p.y);
//            }
//            if(sum < 10000){
//                total_in_reach++;
//            }
//        }
//    }
//    return total_in_reach;
//}
//
//struct Tree{
//    std::vector<Tree> children;
//    std::vector<int> metadata;
//};
//
//template<typename T>
//T fuckingpop(std::queue<T> &queue){
//    T head = queue.front();
//    queue.pop();
//    return head;
//}
//
//Tree extract_data(std::queue<int> &numbers){
//    Tree tree;
//    int childnodes = fuckingpop(numbers);
//    int num_metadata = fuckingpop(numbers);
//
//    for (int x =0; x < childnodes; x++){
//        tree.children.push_back(extract_data(numbers));
//    }
//
//    for(int x=0; x < num_metadata; x++){
//        tree.metadata.push_back(fuckingpop(numbers));
//    }
//    return tree;
//}
//
//int sum_metadata(Tree tree){
//    int summetadata = std::accumulate(begin(tree.metadata), end(tree.metadata), 0);
//
//    int sumchildren = 0;
//    for(Tree child : tree.children){
//        sumchildren += sum_metadata(child);
//    }
//    return sumchildren + summetadata;
//}
//
//int second_sum(Tree tree){
//    if (tree.children.size()== 0){
//        return std::accumulate(begin(tree.metadata), end(tree.metadata), 0);
//    }
//
//    int sumofthisone = 0;
//    for(int childindex : tree.metadata){
//        childindex-=1; // No Matlab here!
//        if (childindex < tree.children.size()){
//            sumofthisone += second_sum(tree.children[childindex]);
//        }
//    }
//    return sumofthisone;
//
//}
//
//int main(int argc, const char * argv[]) {
//    int nextnum;
//    std::ifstream inFile;
//    inFile.open("/Users/roland/Dropbox/workspace/adventofcode2018/input/input_day8.txt");
//    std::queue<int> input;
//    while(inFile >> nextnum){
//        input.push(nextnum);
//    }
//    Tree tree = extract_data(input);
//    std::cout << sum_metadata(tree) << std::endl;
//    std::cout << second_sum(tree) << std::endl;
//    return 0;
//}

//
//struct Marble{
//    Marble *next;
//    Marble *prev;
//    long int value;
//};
//
//void insertAfter(Marble *current, long int value){
//    Marble *newone = new Marble;
//    newone->value = value;
//
//    newone->next = current->next;
//    current->next = newone;
//    newone->prev = current;
//    newone->next->prev = newone;
//}
//
//void removeAfter(Marble *current){
//    current->prev->next = current->next;
//    current->next->prev = current->prev-> next;
//
//    // TODO do not have memory loss...
//}
//
//
//long int get_score_marble_game(int num_players, long int last_marble){
//    Marble *first = new Marble;
//    first->next  = first;
//    first->prev = first;
//    first->value = 0;
//
//    Marble* current = first;
//    std::vector<long int> scores;
//    for(int x =0; x < num_players; x++){
//        scores.push_back(0);
//    }
//
//    for(long int marblenum=1; marblenum < last_marble+1; marblenum++){
//        long int currentplayer = ((marblenum-1)%num_players);
//        if(marblenum % 23 != 0){
//            current = current->next;
//            insertAfter(current, marblenum);
//            current = current->next;
//        }
//        else{
//            scores[currentplayer] += marblenum;
//            // Shift 7 to the left...
//            for(int x =0; x < 7; x++){
//                current = current->prev;
//            }
//            scores[currentplayer] += current->value;
//            removeAfter(current);
//            current = current->next;
//        }
//    }
//
//    long int max =0 ;
//    for(long int score : scores){
//        if(score > max){
//            max = score;
//        }
//    }
//    return max;
//}
//
//
//int main(int argc, const char * argv[]) {
//    assert(get_score_marble_game(6,25)==32);
//    assert(get_score_marble_game(10,1618)==8317);
//    assert(get_score_marble_game(13,7999)==146373);
//    assert(get_score_marble_game(17,1104)==2764);
//    assert(get_score_marble_game(21,6111)==54718);
//    assert(get_score_marble_game(30,5807)==37305);
//
//    long int score1 = get_score_marble_game(486,70833);
//    std::cout << "Score is " << score1 << std::endl;
//
//    long int score2 = get_score_marble_game(486,100*70833);
//    std::cout << "Score is " << score2 << std::endl;
//}


struct Cart{
    int x;
    int y;
    int dx;
    int dy;
    int orientation;

};

typedef std::vector<Cart> cartCollection;
typedef std::vector<std::vector<char>> mazeType;

std::vector<char> parse_line(std::string line, int ypos, cartCollection &collection){
    std::vector<char> trackline;
    for(int xpos=0; xpos < line.size(); xpos++){
        char character = line[xpos];
        if(character=='>'){
            Cart newcart{.x=xpos, .y=ypos, .dx=1, .dy=0, .orientation=0};
            collection.push_back(newcart);
            trackline.push_back('-');
        }
        else if(character=='<'){
            Cart newcart{.x=xpos, .y=ypos, .dx=-1, .dy=0, .orientation=0};
            collection.push_back(newcart);
            trackline.push_back('-');
        }
        else if(character=='^'){
            Cart newcart{.x=xpos, .y=ypos, .dx=0, .dy=-1, .orientation=0};
            collection.push_back(newcart);
            trackline.push_back('|');
        }
        else if(character=='v'){
            Cart newcart{.x=xpos, .y=ypos, .dx=0, .dy=1, .orientation=0};
            collection.push_back(newcart);
            trackline.push_back('|');
        }
        else{
            assert(character=='\\' || character=='|' || character=='+' || character=='/' || character=='-' || character==' ');
            trackline.push_back(character);

        }
    }

    return trackline;
}

void make_turn(Cart &cart){
    if(cart.orientation==0){
        // Turn left
        int temp = cart.dx;
        if(cart.dx == 0){
            cart.dx = cart.dy;
            cart.dy = temp;
        }
        else{
            cart.dx = -1*cart.dy;
            cart.dy = -1*temp;
        }
    }
    else if(cart.orientation == 1){
        // Go straight
    }
    else if(cart.orientation == 2){
        // Turn left

        if(cart.dx == 0){
            int temp = cart.dx;
            cart.dx = -1*cart.dy;
            cart.dy = -1*temp;
        }
        else{
            std::swap(cart.dx, cart.dy);
        }
    }
    cart.orientation++;
    cart.orientation%=3;
}


bool compareCarts(Cart i1, Cart i2)
{
    if(i1.y != i2.y){
        return i1.y < i2.y;
    }
    return i1.x < i2.x;
}

void check_crash(cartCollection &carts){
    for(int xpos = 0; xpos < carts.size(); xpos++){
        for(int ypos = xpos+1; ypos < carts.size(); ypos++){
            if(carts[xpos].x == carts[ypos].x && carts[xpos].y == carts[ypos].y){
                std::cout << "Crash at: " << carts[xpos].x << " " << carts[xpos].y << std::endl;
                carts.erase(carts.begin()+ypos);
                carts.erase(carts.begin()+xpos);
                xpos--;

            }
        }
    }
}
void tick(mazeType maze, cartCollection &carts){
    std::sort(carts.begin(), carts.end(), compareCarts);
    cartCollection loopover = carts;
    for(int index=0; index < carts.size(); index++){

        carts[index].x += carts[index].dx;
        carts[index].y += carts[index].dy;
        char thinghere = maze[carts[index].y][carts[index].x];
        if(thinghere == '\\'){
            // (0, 1) -> (1, 0)
            // (-1, 0) -> (0, -1)
            std::swap(carts[index].dx, carts[index].dy);

        }
        else if(thinghere == '/'){
            // (0, -1) -> (1, 0)
            // (-1, 0) -> (0, 1)
            std::swap(carts[index].dx, carts[index].dy);
            carts[index].dx *=-1;
            carts[index].dy *= -1;
        }
        else if (thinghere=='+'){
            make_turn(carts[index]);
        }
        assert(maze[carts[index].y][carts[index].x] != ' ');
        check_crash(carts);
    }
}

void draw_maze_and_carts(mazeType maze, cartCollection carts){
    std::cout << "$$$$$$$$$$$$$$$$$$$$$$$" << std::endl;
    for(Cart c : carts){
        maze[c.y][c.x] = 'x';
    }
    for(auto a : maze){
        for(char c : a){
            std::cout << c;
        }
        std::cout << std::endl;
    }
    std::cout << "$$$$$$$$$$$$$$$$$$$$$$$" << std::endl;
}

int main(int arc, const char* argv[]){
//  std::ifstream in("/Users/roland/Dropbox/workspace/adventofcode2018/python/untitled2.txt");
    std::ifstream in(argv[1]);
    std::string line;
    cartCollection carts;
    mazeType maze;
    int ypos=0;
    for (std::string line; std::getline(in, line); ) {
        std::vector<char> toap = parse_line(line, ypos, carts);
        maze.push_back(toap);
        ypos++;
    }

    for(int x=0; x<1000000; x++){
//        draw_maze_and_carts(maze, carts);
        tick(maze, carts);
        if(carts.size() <=1)
        {
            std::cout << "DONE!" << std::endl;
            if(carts.size()==1){
                carts[0].x += carts[0].dx;
                carts[0].y += carts[0].dy;
                std::cout << carts[0].x << "," << carts[0].y << std::endl;
            }
            break;
        }
    }
}
