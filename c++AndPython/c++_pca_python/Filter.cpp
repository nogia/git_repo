/*
 * Filter.cpp
 *
 *  Created on: Jun 20, 2016
 *      Author: inna
 */

#include "Filter.h"

namespace NDUV {

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \brief Filter::Filter
    ///
	Filter::Filter(){}
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \brief Filter::~Filter
    ///
    Filter::~Filter(){}
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \brief Filter::DesignFilter
    /// \param filterParameters
    /// \return
    ///
    pair<mat,mat> Filter::DesignFilter(FilterParameters filterParameters)
    {
             pair<mat,mat> frequencyResponce =  CreateFrequencyResponse(DesignFilterKernel(filterParameters ),filterParameters.maxWindowPoints);
             vector<double> frequenceRspY((int)filterParameters.maxWavelength + 1 - (int)filterParameters.minWaveLength   ,0.0);

             vector<double> frequenceRspX((int)filterParameters.maxWavelength + 1 - (int)filterParameters.minWaveLength  , 0.0);


             for(int i = 0;i< (int)frequenceRspX.size() ;i++)
             {
                 frequenceRspX[i] = (int)filterParameters.minWaveLength + i ;
             }
             for(int i = (int)filterParameters.minWaveLength ,j=0;i < (int)frequencyResponce.second.n_cols && j < (int)frequenceRspY.size();i++,j++)
             {
                 frequenceRspY[j] = frequencyResponce.second(i);
             }
             vector<double> frequenceRspYY(filterParameters.totalPointsSize  ,0.0);

             vector<double> frequenceRspXX(filterParameters.totalPointsSize , 0.0);
             double delta = (filterParameters.maxWavelength - filterParameters.minWaveLength)  / filterParameters.totalPointsSize;
             double deltaY = 1 / delta;
             int j = 0;
             for(double i =filterParameters.minWaveLength;j < (int)frequenceRspXX.size() ;i = i + delta,j++)
             {
                frequenceRspXX[j] = i;
             }
              j = 0;
             for(double i = 0;i <  frequenceRspY.size() ;i++)
             {
                 for(;j< (i+1) * deltaY &&  j < (int)frequenceRspYY.size();j++)
                 {
                     frequenceRspYY[j] = frequenceRspY[i];
                 }
             }
             frequencyResponce.first = rowvec(frequenceRspXX);
             frequencyResponce.second = rowvec(frequenceRspYY);
             FilterGraph = frequencyResponce;
             return frequencyResponce;
       }
       ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
       /// \brief Filter::DesignFilterKernel
       /// \param filterParameters
       /// \return
       ///
       pair<vector<double>,vector<double>>  Filter::DesignFilterKernel(FilterParameters filterParameters )
       {
           pair<vector<double>,vector<double>> result;
           if(filterParameters.minwindow <= 0)
               return result;
           //'This program calculates an 801 point band-pass filter kernel

           // 'A[ ] workspace for the lower cutoff
           vector<double> A(filterParameters.minwindow, 0.0);
           vector<double> B(filterParameters.minwindow, 0.0);
           vector<double> H = vector<double>(filterParameters.minwindow, 0.0);
           vector<double> valuesOfX(filterParameters.minwindow,0.0);
           double m = (double)filterParameters.minwindow;
           //Calculate the first low - pass filter kernel via Eq. 16 - 4,
           for (int i = 0; i < m; i++)
           {
               if (i - m / 2 == 0)
               {
                   A[i] = 2 * PI * filterParameters.lambdalow ;
               }
               else
               {

                   A[i] = (sin(2 * PI * filterParameters.lambdalow * (i - m / 2))) / (i - m / 2);
               }
               // The Blackman window.
               A[i] = A[i] * (0.42 - 0.5*cos(2 * PI* i / m) + 0.08 * cos(4 * PI*i / m));
           }

           //'Normalize the first low-pass filter kernel for
           long double sum = 0;
           for (int i = 0; i < m; i++)
           {
               sum = sum + A[i];
           }
           for (int i = 0; i < m; i++)
           {
               A[i] = A[i] / sum;
           }

           //Calculate the second low - pass filter kernel via
           for (int i = 0; i < m; i++)
           {
               if (i - m / 2 == 0)
               {
                   B[i] = 2 * PI * filterParameters.lambdaupper;
               }
               else
               {
                   B[i] = (sin(2 * PI * filterParameters.lambdaupper * (i - m / 2))) / (i - m / 2);

               }
               // The Blackman window.
               B[i] = B[i] * (0.42 - 0.5*cos(2 * PI* i / m) + 0.08 * cos(4 * PI*i / m));

           }
           sum = 0;
           for (int i = 0; i < m; i++)
           {
               sum = sum + B[i];
           }
           for (int i = 0; i < m; i++)
           {
               B[i] = B[i] / sum;
           }
           // 'Change the low-pass filter kernel in B[ ] into a high-pass
           for (int i = 0; i < m; i++)
           {
               B[i] = -B[i];
           }
           B[m / 2] = B[m / 2] + 1;
           switch(filterParameters.type)
           {
                   case LPF:
                           for (int i = 0; i < m; i++)
                           {
                               H[i] =  A[i];
                           }
                   break;
                   case HPF:
                           for (int i = 0; i < m; i++)
                           {
                               H[i] =  B[i];
                           }
                   break;
                   case STOPBANDF:
                   case BPF:
                           // Add the low-pass filter kernel in A[ ], to the high-pass	filter kernel in B[ ], to form a band-reject filter kernel
                           for (int i = 0; i < m; i++)
                           {
                               H[i] =  A[i] + B[i];
                           }
                           // Change the band-reject filter kernel into a band-pass filter kernel by using spectral inversion
                           if(filterParameters.type == BPF)
                           {
                               for (int i = 0; i < m; i++)
                               {
                                   H[i] = -H[i];
                               }
                           }

                           H[m / 2] = H[m / 2] + 1;
                   break;
           };


           for(int i = 0;i < (int)valuesOfX.size() && i < (int)H.size();i++)
           {
               valuesOfX[i] = i;
           }

           return pair<vector<double>,vector<double>>(valuesOfX,H);

       }
       //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
       /// \brief Filter::CreateFrequencyResponse
       /// \param filter
       /// \param totalFilterLength
       /// \return
       ///
       pair< mat,mat> Filter::CreateFrequencyResponse(pair<vector<double>,vector<double>> filter,int totalFilterLength)
       {

            rowvec filterSecond = ConvertToAbsolute(   fft(   conv_to< vec >::from( rowvec(filter.second)  )  ,totalFilterLength )  );

            filter.second = convToStd(filterSecond);
            for (int i = 0; i < (int)filter.second.size()  - 1; i++)
            {
                filter.second[i] =  filter.second[i + 1];
            }
            filter.second.pop_back();
            filterSecond = rowvec(filter.second);
            if((int)filter.first.size() != (int)filterSecond.n_cols)
            {
                 filter.first.clear();
                 for(int i = 0;i < (int)filter.second.size() ;i++)
                 {
                     filter.first.push_back(i);

                 }
            }
            return pair< mat,mat>(rowvec(filter.first),filterSecond);
        }
       ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
       /// \brief Filter::DesignFilter
       /// \param filterParameters
       /// \param range
       /// \return
       ///
        pair<mat,mat> Filter::DesignFilter(FilterParameters filterParameters ,vector<double> range)
        {
                   vector<double> valueX;
                   vector<double> valueY;
                   double llow = filterParameters.fc - (double)filterParameters.bw / 2;
                   double lupper = filterParameters.fc + (double)filterParameters.bw / 2;
                   if(llow <  range[0])
                       llow = range[0];
                   if(lupper > range[(int)range.size() - 1])
                       lupper = range[(int)range.size() - 1];

                   if(llow < lupper   )
                   {
                       for(int i=0;i< (int)range.size();i++)
                       {
                           switch(filterParameters.type)
                           {
                                   case BPF:
                                           if(range[i] >=llow && range[i] < lupper)
                                           {
                                               valueX.push_back(i);
                                               valueY.push_back(1);
                                           }
                                           else
                                           {

                                               valueY.push_back(0);
                                           }

                                    break;

                                   case LPF:
                                           if(range[i] < llow )
                                           {
                                               valueX.push_back(i);
                                               valueY.push_back(1);
                                           }
                                           else
                                           {

                                               valueY.push_back(0);
                                           }
                                       break;

                                   case HPF:
                                           if(range[i] > llow )
                                           {
                                                valueX.push_back(i);
                                               valueY.push_back(1);
                                           }
                                           else
                                           {

                                               valueY.push_back(0);
                                           }
                                       break;

                                   case STOPBANDF:
                                           if(range[i] >llow && range[i] < lupper)
                                           {
                                               valueX.push_back(i);
                                               valueY.push_back(0);
                                           }
                                           else
                                           {

                                               valueY.push_back(1);
                                           }
                                           break;

                            };
                       }
                  }

                  FilterGraph = pair<mat,mat>(rowvec(valueX),rowvec(valueY));
                  return FilterGraph;

                }
                /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                /// \brief convToStd
                /// \param rowvector
                /// \return
                ///
                vector<double> Filter::convToStd(rowvec rowvector)
                {
                    vector<double> result;
                    for(int i = 0;i<(int)rowvector.size();i++)
                    {
                        result.push_back(rowvector(i));
                    }
                    return result;
                }
                ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                /// \brief ConvertToAbsolute
                /// \param XX
                /// \return
                ///
                rowvec Filter::ConvertToAbsolute(cx_vec XX)
                {
                    vec R = real(XX);
                    vec I = imag(XX);
                    rowvec DD((int)R.n_rows);
                    for(int a =0;a< (int)R.n_rows;a++)
                    {
                        DD(a) = pow(pow(R(a),2) + pow(I(a),2),0.5);
                    }
                    return DD;
                }
                /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                /// \brief ConvertToReal
                /// \param XX
                /// \return
                ///
                rowvec Filter::ConvertToReal(cx_vec XX)
                {
                    vec R = real(XX);
                    return conv_to< rowvec >::from(R);
                }
                /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                /// \brief ConvertToImaginary
                /// \param XX
                /// \return
                ///
                rowvec Filter::ConvertToImaginary(cx_vec XX)
                {
                    vec I = imag(XX);
                    return conv_to< rowvec >::from(I);
                }

} /* namespace NDUV */
