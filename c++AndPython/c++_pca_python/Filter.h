/*
 * Filter.h
 *
 *  Created on: Jun 20, 2016
 *      Author: inna
 */

#ifndef FILTER_H_
#define FILTER_H_

#include "PCAComponent.h"
#include "Optimization.h"
#include "Statistics.h"

static pair<vector<double>,vector<double>> x = pair<vector<double>,vector<double>>({},{});
namespace NDUV
{
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \brief The FilterParameters struct
    ///
    class FilterParameters
    {
        friend class Filter;
        friend class UnivariateCalibration;
        friend struct TaskOptionsParameters;
       // public:
            //////////////////////////////////////////////////////////////////////////////////////////////////////////////
            /// \brief FilterParameters
            /// \param findex
            /// \param ftype
            /// \param ffc
            /// \param fbw
            /// \param ftotalPointsSize
            /// \param min
            /// \param max
            ///
            FilterParameters(int findex,filterType ftype,double ffc,double fbw,int ftotalPointsSize,double min,double max)
            {
                    type = ftype;
                    fc = ffc;
                    bw = fbw;
                    totalPointsSize = ftotalPointsSize;
                    minWaveLength = min;
                    maxWavelength = max ;
                    index = findex;
                    if(fc > maxWavelength || fc < minWaveLength)
                    {
                        fc = (maxWavelength + minWaveLength) / 2;
                    }

                    maxWindowPoints = 2 * fc + 2;

                    lambdaupper = 0.5;

                    lambdalow = 0.5 -  bw * 0.25 / fc;
                    minwindow = 4 / (lambdaupper - lambdalow);
                    if(minwindow % 2 != 0)
                    {
                            minwindow++;
                    }
             }
             static FilterParameters getdefaultFilterParameters()
             {
                 return {0,BPF,190,35,1074,188.00,499.00};

             }



                filterType type;
                double fc;
                double bw;
                int totalPointsSize;
                double minWaveLength;
                double maxWavelength;



                int minwindow;
                double maxWindowPoints;
                double lambdalow;
                double lambdaupper;
                int index;

        };
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief The Filter class
        ///
        class Filter
        {
             friend class UnivariateCalibration;
             friend struct TaskOptionsParameters;
            public:
              ~Filter();
            private:
             typedef map<ConstituteFilterTypes,vector<Filter>> FilterMap;

                Filter();

                pair<mat,mat> DesignFilter(FilterParameters filterParameters = FilterParameters::getdefaultFilterParameters());
                pair<mat,mat> DesignFilter(FilterParameters filterParameters ,vector<double> range );
                pair<mat, mat> GetFilter()
                {
                     return FilterGraph;
                }
                std::function<void(vector<double> &,vector<double>)> ConvolveSample = [this](vector<double> & sample,vector<double> filter)->void
                {
                    vector<double> outputsample((int)sample.size(),0.0);
                    for(int j =0;j< (int)outputsample.size();j++)
                    {
                              for(int i =0;i< (int)filter.size();i++)
                              {
                                  outputsample[j]=outputsample[j] + sample[j - i] * filter[i];
                              }
                    }
                     sample = outputsample;
                   /* rowvec A = conv_to<rowvec>::from(sample);
                    rowvec B = conv_to<rowvec>::from(filter);
                    rowvec C = conv(A,B,"same");

                    sample = convToStd(C);*/
                    cout << endl;
                };
                std::function<void(pair<vector<double> ,vector<double>> &,pair<mat,mat> &,  vector<double>,string )> Multiplysample =
                       [this](pair<vector<double> ,vector<double>> & sample,pair<mat,mat> & filter,  vector<double> currentValueOfX,string option)->void
                {

                    sample.first.clear();

                    int i=0;
                    for( i = 0; i < (int)filter.second.n_cols;i++)
                    {
                        sample.second[i] = sample.second[i] * filter.second(i);


                    }

                    sample.first = currentValueOfX;
                    filter.first = rowvec( currentValueOfX);
                };
                std::function<void(pair<vector<double> ,vector<double>> & )> ScaleSample =
                         [this](pair<vector<double> ,vector<double>> & sample)->void
                {
                       pair<vector<double> ,vector<double>> outsample;
                       double meansample = abs(arma::mean(rowvec(sample.second)));
                       double zero = 0.05;
                       for(int i =0;i< (int)sample.second.size();i++)
                       {
                           if(abs(sample.second[i] / meansample) > zero)
                           {
                               outsample.first.push_back(sample.first[i]);
                               outsample.second.push_back(sample.second[i]);
                           }
                       }
                       sample = outsample;
                };

                /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                /// \brief convToStd
                /// \param rowvector
                /// \return
                ///
                static vector<double> convToStd(rowvec rowvector);
                static rowvec ConvertToAbsolute(cx_vec XX);
                static rowvec ConvertToReal(cx_vec XX);
                static rowvec ConvertToImaginary(cx_vec XX);

                pair<vector<double>,vector<double>>  DesignFilterKernel(FilterParameters filterParameters = FilterParameters::getdefaultFilterParameters());
                pair< mat,mat> CreateFrequencyResponse(pair<vector<double>,vector<double>> filter,int totalFilterLength);

                ////////////////////////////////////////////////////////////////////////////////

                pair<mat, mat> FilterGraph;
        };

} /* namespace NDUV */

#endif /* FILTER_H_ */
