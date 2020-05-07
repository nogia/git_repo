#include<fstream>
#include<vector>
#include<array>
#include <sstream>
#include <numeric>
#include <cstdlib>
#include <cstdint>
#include <cstring>
#include <algorithm>
#include <iomanip>
#include <iostream>
using namespace std;

class MedianFilter
{
public:

    MedianFilter(std::string filename_m, std::string file_filter_m);
    MedianFilter();
    void run();

private:
    void read2DArray(vector<vector<vector<float>>>  &mat);
    void getFileContent( std::vector<std::string> & vecOfStrs);
    void readFilter(vector<vector<int>>  &filter);
    void apply_filter(vector<vector<float>> &mat, vector<vector<int>>  filter);
    void printMatrix(vector<vector<float>> const &mat);
    void addColumn(vector<float> const &vec, vector<vector<float>>  &mat, int column);
    void print_values(vector<float> v, int row, int col);
    float find_median(vector<float> values, int a, int b);
    std::string filename;
    std::string file_filter;
};

