

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <iostream>
#include <fstream>
#include <regex>
#include <string>

using namespace cv;
using namespace std;

struct VelPoint{
    int x;
    int y;
    int velx;
    int vely;
};
std::istream &operator>>(std::istream &in, VelPoint &r) {
    std::string line;
    std::getline(in, line);
    std::cout << "Parsing line" << std::endl;
    if(line.length() > 1) {
        std::regex digit_regex("-?\\d+");
        std::sregex_iterator words_begin = std::sregex_iterator(line.begin(), line.end(), digit_regex);
        r.x = stoi((*words_begin++).str());
        r.y = stoi((*words_begin++).str());
        r.velx = stoi((*words_begin++).str());
        r.vely = stoi((*words_begin++).str());


    }
    return in;
}

void update(std::vector<VelPoint> &data){
    for(auto &p : data){
        p.x += p.velx;
        p.y += p.vely;
    }
}

void normalise(std::vector<VelPoint> &data){
    int minx = 20000;
    int miny = 20000;
    for(auto p : data){
        minx = std::min(minx, p.x);
        miny = std::min(miny, p.y);
    }
    for(auto &p : data){
        p.x -= minx;
        p.y -= miny;
    }
}
int main(int argc, char* args[]) {
    std::ifstream inFile;
    inFile.open("course/dojo/5_stream_processing/input_day10.txt");

    if(!inFile){
        std::cout << "error reading file";
        exit(1);
    }

    std::vector<VelPoint> data_in(std::istream_iterator<VelPoint>{inFile}, std::istream_iterator<VelPoint>{});


    for(int second = 1 ; second < 11890; second++){
        update(data_in);
        normalise(data_in);

        int maxx = 0;
        int maxy = 0;

        for(auto p : data_in){
            maxx = std::max(maxx, p.x);
            maxy = std::max(maxy, p.y);
        }
        std::cout << "Second " << second << " Max vals: " << maxx << " " << maxy << std::endl;

        if(maxy < 30){
            Mat M(maxy+1, maxx+1, CV_8UC3, Scalar(0,0,0));
            for(auto r : data_in){
                Vec3b & color = M.at<Vec3b>(r.y, r.x);
                color[2] = 255;
            }
            namedWindow( "Display window", WINDOW_AUTOSIZE );// Create a window for display.
            imshow( "Display window", M );                   // Show our image inside it.
            waitKey(1000);
        }
    }

}
