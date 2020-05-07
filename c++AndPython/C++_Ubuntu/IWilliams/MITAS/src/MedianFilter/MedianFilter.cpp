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
        cube matrix;
        imat filter;
        read2DArray( matrix);
        readFilter( filter);
        print_filter(filter);
        cout << "Start filename " << filename << " filter = " << file_filter << " Number Of Frames = " << matrix.size() << endl;
        cout << "#####################################################################################" << endl;
        for(int n = 0; n < matrix.n_slices;n++)
        {
            cout <<"Start Frame Number = "<< n + 1 << " rows = "<< matrix.slice(n).n_rows << " cols = " << matrix.slice(n).n_cols << endl;
            cout << " Original matrix = " << endl;
            printFrame(matrix.slice(n),n);
            apply_filter(matrix.slice(n), filter);
            cout << " Resulting matrix = " << endl;
            printFrame(matrix.slice(n),n);
            cout <<"End Frame Number = "<< n + 1<< endl;
        }
        cout << "End filename " << filename << " filter = " << file_filter << " Number Of Frames = " << matrix.size() << endl;
        cout << "#####################################################################################" << endl;
        cout << "End run" << endl;
        cout << "#####################################################################################" << endl;
    }

    void MedianFilter::read2DArray(cube  &matrix)
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
            matrix = cube(rows,cols,n_frames);
            matrix.zeros();
            for(int n = 0; n < n_frames; n++)
            {
                for (int j = 0; j < cols; j++)
                {
                    colvec temp(rows);
                    for (int i = 0; i < rows; i++)
                    {
                        uint32_t data;
                        file.read((char*)&data, sizeof(data));
                        temp(i) = reinterpret_cast<float &>(data);
                    }
                    matrix.slice(n).col(j) = temp;
                }
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
    void MedianFilter::readFilter(imat  &filter)
    {
        std::string str;
        std::vector<std::string>  vecOfStrs;
        getFileContent(vecOfStrs);
        filter = imat(vecOfStrs.size(),vecOfStrs.size());
        for (int i = 0; i < vecOfStrs.size(); i++)
        {
            irowvec temp(vecOfStrs.size());
            int count = 0;
            for (int j = 0; j <  vecOfStrs[i].size(); j++)
            {
                if (isdigit( vecOfStrs[i][j]))
                {
                    temp(count ) = std::atoi(&vecOfStrs[i][j]);
                    count++;
                }
            }
            filter.row(i) = temp;
        }
    }
    void MedianFilter::apply_filter(mat &matrix, imat  filter)
    {
        int num_pad_row = filter.n_rows / 2;
        int num_pad_col = filter.n_cols / 2;
        mat  temp_mat(matrix.n_rows + 2 * num_pad_row, matrix.n_cols + 2 * num_pad_col);
        temp_mat.zeros();
        temp_mat.submat( num_pad_row,num_pad_col,num_pad_row + matrix.n_rows - 1, num_pad_col + matrix.n_cols - 1) = matrix;
        //cout << "Temp Padded Matrix = "<< endl;
        //cout << temp_mat;
        //cout << "#############################################################"<< endl;
        for (int a = 0; a < temp_mat.n_rows - filter.n_rows + 1; a++)
        {
            for (int b = 0; b < temp_mat.n_cols - filter.n_cols + 1; b++)
            {
                vector<float> values;
                for (int n = a, i = 0; n < a + filter.n_rows; n++, i++)
                {
                    if (i < filter.n_rows)
                    {
                        for (int m = b, j = 0; m < b + filter.n_cols; m++, j++)
                        {
                            if (j < filter.n_cols)
                            {
                                float value = temp_mat(n,m) * filter(i,j);
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
                rowvec temp = conv_to<rowvec>::from(values);
                matrix(a , b) = find_median(temp, a, b);
                values.clear();
            }
        }
    }

    void MedianFilter::printFrame(const mat  &frame,int frame_number) {
        cout <<"Start Frame Number = "<< frame_number + 1 << " rows = "<< frame.n_rows << " cols = " << frame.n_cols << endl;
        cout << setw(10) << frame << endl;
    }

    void MedianFilter::print_filter(imat filter)
    {
        cout << "#####################################################################################" << endl;
        cout << " Filter = " << endl;
        cout  <<  std::setprecision(0) << filter << endl;
        cout << "#####################################################################################" << endl;
    }
    float MedianFilter::find_median(rowvec values, int a, int b)
    {
        sort(values);
        return  median(values);
    }
    std::string filename;
    std::string file_filter;


