#include <iostream>
#include <fstream>
#include <regex>
#include <string>
#include <cassert>
#include <Eigen/Dense>
#include <benchmark/benchmark.h>


using Eigen::ArrayXXf;
using Eigen::ArrayXXd;

struct Val{
    int x;
    int y;
    int width;
    int sum;
};
int getpowerlevel(int x, int y, int grid_serial_number){
    int rackid = x+10;
    long int powerlevel = rackid*y;
    powerlevel += grid_serial_number;
    powerlevel *= rackid;
    powerlevel = powerlevel%1000;
    powerlevel = powerlevel/100;
    powerlevel -=5;
    return powerlevel;
}


bool compareBySum(const Val &a, const Val &b)
{
    return a.sum > b.sum;
}

ArrayXXf calculate_grid(int serial_num, int wh){
    ArrayXXf m = ArrayXXf::Constant(wh, wh, 0);
    for(int x=1; x < wh; x++){
        for(int y=1; y < wh; y++){
            m(y,x) = getpowerlevel(x,y,serial_num);
        }
    }
    return m;
}


ArrayXXd calculate_summed_area_table(int serial_num, int wh){
    ArrayXXd m = ArrayXXd::Constant(wh, wh, 0);
    for(int y=1; y < wh; y++){
        for(int x=1; x < wh; x++){
            int powerhere = getpowerlevel(x,y,serial_num);
            int sumleft = m(y-1,x);
            int sumup = m(y, x - 1);
            int sumdiag = m(y - 1, x - 1);
            m(y,x) = powerhere + sumleft + sumup - sumdiag;
        }
    }
    return m;
}

void append_values(std::vector<Val> &values, ArrayXXd &m, int blockwidth, int wh){
    for(int x=1; x < wh-blockwidth; x++){
        for(int y=1; y < wh-blockwidth; y++){
            int sum = m.block(y,x,blockwidth,blockwidth).sum();
            values.push_back({x,y, blockwidth, sum});
        }
    }
}


int get_sum_summed_area_table(ArrayXXd &m, int xstart, int ystart, int blockwidth){
    // Removing 1 from xstart to get the right bounds...
    xstart -= 1;
    ystart -= 1;
    int a = m(ystart, xstart);
    int b = m(ystart, xstart+blockwidth);
    int c = m(ystart+blockwidth, xstart);
    int d = m(ystart+blockwidth, xstart+blockwidth);
//    std::cout << "a " << a << " b " << b << " c " << c << " d " << d << std::endl;
    return d-b-c+a;
}

Val get_max_values_summed_area_table(ArrayXXd &m, int blockwidth, int wh){
    Val currentmax{0,0,0,-100};
    for(int x=1; x < wh-blockwidth; x++){
        for(int y=1; y < wh-blockwidth; y++){
            int sum = get_sum_summed_area_table(m, x,y,blockwidth);
            if(sum > currentmax.sum){
                Val newmax{x,y,wh, sum};
                currentmax = newmax;
            }
        }
    }
    return currentmax;
}




class MyFixture : public benchmark::Fixture
{
public:
    MyFixture(){

    }

};

BENCHMARK_DEFINE_F(MyFixture, MyMethod)(benchmark::State& state)
{
    for (auto _ : state)
    {
        int wh = 301;
        int serialnum = 5034;
        ArrayXXd m = calculate_summed_area_table(serialnum, 301);
        Val max = get_max_values_summed_area_table(m, 3, wh);
//        std::cout << max.sum << " : " << max.x << " " << max.y << std::endl;


        for(int gridsize = 4; gridsize < wh; gridsize++) {
            Val possiblenewmax = get_max_values_summed_area_table(m, gridsize, wh);
            if(possiblenewmax.sum > max.sum){
                max = possiblenewmax;
            }
        }
    }
}


BENCHMARK_REGISTER_F(MyFixture, MyMethod);
BENCHMARK_MAIN();

//
//int main(int argc, char* args[]){
//    int wh = 301;
//
//
//    assert(getpowerlevel(3,5,8)==4);
//    assert(getpowerlevel(122,79,57)==-5);
//    assert(getpowerlevel(217,196,39)==0);
//    assert(getpowerlevel(101,153,71)==4);
//
//// OLD BORING SOLUTION!
////    ArrayXXf m = calculate_grid(5034, wh);
//
////    std::vector<Val> values;
////    append_values(values, m, 3, wh);
////    std::sort(begin(values), end(values), compareBySum);
////    std::cout << values[0].sum << " : " << values[0].x << " " << values[0].y << std::endl;
////
////
////    for(int gridsize = 4; gridsize < 200; gridsize++) {
////        append_values(values, m, gridsize, wh);
////        std::sort(begin(values), end(values), compareBySum);
////        std::cout << values[0].sum << " : " << values[0].x << " " << values[0].y << " " << values[0].width << std::endl;
////        values.erase(values.begin()+1); // Only keep our best one so far...
////    }
//
//    int serialnum = 5034;
//    ArrayXXd m = calculate_summed_area_table(serialnum, 301);
//    Val max = get_max_values_summed_area_table(m, 3, wh);
//    std::cout << max.sum << " : " << max.x << " " << max.y << std::endl;
//
//
//    for(int gridsize = 4; gridsize < 200; gridsize++) {
//        Val possiblenewmax = get_max_values_summed_area_table(m, gridsize, wh);
//        if(possiblenewmax.sum > max.sum){
//            max = possiblenewmax;
//        }
//    }
//    std::cout << max.sum << " : " << max.x << " " << max.y << std::endl;
//
//    return 0;
//}