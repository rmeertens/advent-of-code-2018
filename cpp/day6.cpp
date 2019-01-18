struct Point{
    int x;
    int y;
};


std::istream &operator>>(std::istream &in, Point &x) {
    char discard;
    in >> x.x >> discard >> x.y;
    return in;
}

std::vector<Point> get_input(std::string filename){
    std::ifstream in(filename);
    
    std::istream_iterator<Point> b{in};
    std::istream_iterator<Point> e;
    std::vector<Point> input(b, e);
    return input;
}

// Return the index of the element which has the min distance...
int mindist(Point point, std::vector<Point> coords){
    std::vector<int> distances;
    for(Point p : coords){
        distances.push_back(abs(p.x-point.x)+abs(p.y-point.y));
    }
    std::vector<int> copy(distances);
    std::sort(copy.begin(), copy.end(), std::less<int>());
    if(copy[0] == copy[1]){
        return -1;
    }
    if(copy[0] != copy[1]){
        for(int index=0; index < coords.size(); index++){
            if(distances[index] == copy[0]){
                return index;
            }
        }
    }
    std::cout << "THis should not happen " << std::endl;
    return -1;
}

int a(std::vector<Point> coords){
    
    int max_x = 0;
    int max_y = 0;
    for(auto p : coords){
        max_x = std::max(max_x, p.x);
        max_y = std::max(max_y, p.y);
    }
    max_x+=1;
    max_y+=1;
    
    std::set<int> valids;
    int grid[max_y][max_x];
    
    for(int x=0; x < coords.size(); x++){
        valids.insert(x);
    }
    
    for(int x=0; x < max_x; x++){
        for(int y=0; y < max_y; y++){
            grid[y][x] = -1;
        }
    }
    
    for(int x=0; x < max_x; x++){
        for(int y=0; y < max_y; y++){
            grid[y][x] = mindist({x,y}, coords);
            bool edge = (x == 0 || y == 0 || x == max_x - 1 || y == max_y - 1);
            if(edge){
                if(valids.find(grid[y][x]) != valids.end()){
                    valids.erase(valids.find(grid[y][x]));
                }
            }
            
        }
    }
    
    std::map<int,int> counts;

    for(int v : valids){
        counts[v] = 0;
    }
    
    for(int x=0; x < max_x; x++){
        for(int y=0; y < max_y; y++){
            int ic = grid[y][x];
            if (valids.find(ic) != valids.end()){
                counts[ic] = counts[ic]+ 1;
            }
        }
    }
    
    int max = 0;
    for ( auto it = counts.begin(); it != counts.end(); it++ ){
        max = std::max(max, it->second);
    }
    return max;
}

int b(std::vector<Point> coords){
    int max_x = 400;
    int max_y = 400;
    
    int total_in_reach = 0;
    for(int x=0; x < max_x; x++){
        for(int y=0; y < max_y; y++){
            int sum = 0;
            for(auto p : coords){
                sum += abs(x-p.x) + abs(y-p.y);
            }
            if(sum < 10000){
                total_in_reach++;
            }
        }
    }
    return total_in_reach;
}

int main(int argc, const char * argv[]) {
    std::vector<Point> input = get_input("/Users/roland/Dropbox/workspace/adventofcode2018/input_day6.txt");
    std::cout << "Part a: " << a(input) << std::endl;
    std::cout << "Part b: " << b(input) << std::endl;
    
    return 0;
}