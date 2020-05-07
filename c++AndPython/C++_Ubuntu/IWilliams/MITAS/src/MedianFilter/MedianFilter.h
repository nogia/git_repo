#include<fstream>
#include<vector>
#include <sstream>
#include <numeric>
#include <cstdlib>
#include <cstdint>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <armadillo>
using namespace std;
using namespace arma;

class MedianFilter
{
public:

    MedianFilter(std::string filename_m, std::string file_filter_m);
    MedianFilter();
    void run();

private:

    void read2DArray(cube &matrix);
    void getFileContent( std::vector<std::string> & vecOfStrs);
    void readFilter(imat  &filter);
    void apply_filter(mat &matrix, imat filter);
    void printFrame(const mat  &frame,int frame_number);
    void print_filter(imat v);
    float find_median(rowvec values, int a, int b);

    std::string filename;
    std::string file_filter;
};

