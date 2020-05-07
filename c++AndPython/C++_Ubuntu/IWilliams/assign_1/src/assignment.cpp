#include "MedianFilter/MedianFilter.h"

int main(int argc, char *argv[])
{
    std::string filename_bin;
    std::string filename_filter;
    bool check = false;
    if(argc == 3)
    {
        filename_bin = argv[1];
        filename_filter = argv[2];
        string bin  = filename_bin.substr(filename_bin.length()-3, filename_bin.length()-3);
        string txt  = filename_filter.substr(filename_filter.length()-3, filename_filter.length()-3);
        if (bin == "bin" && txt == "txt")
        {
            MedianFilter median_filter(filename_bin, filename_filter);
            median_filter.run();
            check  = true;
        }
    }
    if(! check)
    {
        cout << "###   Runs default filter and default bin files  #####################" << endl;
        std::vector<std::string> binfiles = { "frames.1.8.6.bin","frames.3.10.4.bin"};
        std::vector<std::string> filters = {"filter.3x3.txt","filter.5x5.txt"};
        for(auto i : binfiles)
        {
            for(auto j : filters)
            {
                MedianFilter median_filter(i, j);
                median_filter.run();
            }
        }
    }

    return 0;
}


