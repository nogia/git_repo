#include "MedianFilter.h"

using namespace std;

    MedianFilter::MedianFilter(std::string filename_m, std::string file_filter_m)
    {
        filename = filename_m;
        file_filter = file_filter_m;
    }
    MedianFilter::MedianFilter() {}
    void MedianFilter::run()
    {
        if (filename == "" || file_filter == "")
            return;
        cout << "#####################################################################################" << endl;
        cout << "Start new run" << endl;
        vector<vector<vector<float>>> mat;
        vector<vector<int>>  filter;
        read2DArray( mat);
        readFilter( filter);
        cout << "#####################################################################################" << endl;
        cout << " Filter = " << endl;
        for (auto it : filter)
        {
            for (auto i : it)
                cout << setw(5) << i << " ";
            cout << endl;
        }
        cout << "#####################################################################################" << endl;
        cout << "Start filename " << filename << " filter = " << file_filter << " Number Of Frames = " << mat.size() << endl;
        cout << "#####################################################################################" << endl;
        for(int n = 0; n < mat.size();n++)
        {
            cout <<"Start Frame Number = "<< n + 1 << " rows = "<< mat[n].size() << " cols = " << mat[n][0].size() << endl;
            cout << " Original matrix = " << endl;
            printMatrix(mat[n]);
            apply_filter(mat[n], filter);
            cout << " Resulting matrix = " << endl;
            printMatrix(mat[n]);
            cout <<"End Frame Number = "<< n + 1<< endl;
        }
        cout << "End filename " << filename << " filter = " << file_filter << " Number Of Frames = " << mat.size() << endl;
        cout << "#####################################################################################" << endl;
        cout << "End run" << endl;
        cout << "#####################################################################################" << endl;
    }

    void MedianFilter::read2DArray(vector<vector<vector<float>>>  &mat)
    {
        ifstream file(filename, ios::in | ios::binary);
        uint32_t n_frames;
        uint32_t rows;
        uint32_t cols;

        if (file.is_open())
        {
            file.read((char*)&n_frames, sizeof(n_frames));
            file.read((char*)&rows, sizeof(rows));
            file.read((char*)&cols, sizeof(cols));
            vector<vector<float>> mat_n;
            for(int n = 0; n < n_frames; n++)
            {
                mat_n.resize(rows, std::vector<float>(cols));
                for (int j = 0; j < cols; j++)
                {
                    vector<float> temp(rows, 0);
                    for (int i = 0; i < rows; i++)
                    {
                        uint32_t data;
                        file.read((char*)&data, sizeof(data));
                        temp[i] = reinterpret_cast<float &>(data);
                    }
                    addColumn(temp, mat_n, j);
                }
                mat.push_back(mat_n);
            }
        }
    }
    void MedianFilter::getFileContent( std::vector<std::string> & vecOfStrs)
    {
        std::ifstream in(file_filter.c_str());

        std::string str;

        while (std::getline(in, str))
        {
            if (str.size() > 0)
                vecOfStrs.push_back(str);
        }
        in.close();
    }
    void MedianFilter::readFilter(vector<vector<int>>  &filter)
    {
        std::string str;
        std::vector<std::string>  vecOfStrs;
        getFileContent(vecOfStrs);

        for (auto it : vecOfStrs)
        {
            vector<int> temp;
            for (auto i : it)
            {
                if (isdigit(i))
                {
                    int num = std::atoi(&i);
                    temp.push_back(num);
                }
            }
            filter.push_back(temp);
        }
    }
    void MedianFilter::apply_filter(vector<vector<float>> &mat, vector<vector<int>>  filter)
    {
        int num_pad = filter.size() / 2;
        vector<vector<float>>  temp_mat;

        temp_mat.resize(mat.size() + 2 * num_pad, std::vector<float>(mat[0].size() + 2 * num_pad));
        auto first = temp_mat.begin() + num_pad;
        auto last = temp_mat.begin() + mat.size();

        for (int i = 0; i < mat.size(); i++)
        {
            copy(mat[i].begin(), mat[i].end(), temp_mat[i + num_pad].begin() + num_pad);
        }
        //cout << "Temp Padded Matrix = "<< endl;
        //printVector(temp_mat);
        //cout << "#############################################################"<< endl;
        for (int a = 0; a < temp_mat.size() - filter.size() + 1; a++)
        {
            for (int b = 0; b < temp_mat[a].size() - filter.size() + 1; b++)
            {
                vector<float> values;
                for (int n = a, i = 0; n < a + filter.size(); n++, i++)
                {
                    if (i < filter.size())
                    {
                        for (int m = b, j = 0; m < b + filter.size(); m++, j++)
                        {
                            if (j < filter.size())
                            {
                                float value = temp_mat[n][m] * filter[i][j];
                                if (value != 0)
                                {
                                    values.push_back(value);
                                }
                            }
                            else
                            {
                                break;
                            }
                        }
                    }
                    else
                    {
                        break;
                    }
                }
                mat[a][b] = find_median(values, a, b);
                values.clear();
            }
        }
    }

    void MedianFilter::printMatrix(vector<vector<float>> const &mat_n) {

            for (int i = 0; i < mat_n.size(); i++)
            {
                for (int j = 0; j < mat_n[i].size(); j++)
                {
                    cout << setw(10) << mat_n[i][j] << " ";
                }
                cout << '\n';
            }
    }
    void MedianFilter::addColumn(vector<float> const &vec, vector<vector<float>>  &mat, int column) {
        for (int i = 0; i < vec.size(); i++)
        {
            mat[i][column] = vec[i];
        }

    }

    void MedianFilter::print_values(vector<float> v, int row, int col)
    {
        cout << " Output values start row = " << row << " col = " << col << endl;
        for (auto it : v)
        {
            cout << it << " ";
        }
        cout << endl;
        cout << " Output values end row = " << row << " col = " << col << endl;
    }
    float MedianFilter::find_median(vector<float> values, int a, int b)
    {
        std::sort(values.begin(), values.end());
        float median;
        if (values.size() % 2 == 0)
        {
            int temp = values.size() / 2;
            median = (values.at(temp - 1) + values.at(temp)) / 2;
        }
        else
        {
            median = values.at(values.size() / 2);
        }
        //print_values(values, a, b);
        //cout << " Median = " << median << endl;
        return median;
    }

    std::string filename;
    std::string file_filter;


