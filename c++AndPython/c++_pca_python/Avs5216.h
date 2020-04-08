/*
 * Avs5216.h
 *
 *  Created on: Apr 7, 2016
 *      Author: inna
 */

#ifndef AVS5216_H_
#define AVS5216_H_


#include "TestOptions.h"
#include "Plot.h"


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///
///
namespace NDUV
{
    typedef map<ConstituteFilterTypes, vector<pair<  mat,mat >> >  FilteredSpectra;
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \brief The BaseFunction class
    ///
    class BaseFunction
	{
        friend class Avs;
        friend class Test;
        public:
        static Plot * m_plot;
        protected:

        //static Statistic m_statistic_Seperated_Spectra;
        //static Statistic m_statistic_with_unknown_interference;
        //static Statistic m_statistic_with_unknown_interference_SeperatedSpectra;



		BaseFunction();
        virtual void Run(Statistic & statistic );
		virtual ~BaseFunction();

        void setCurrentPopulationOfSamples(Statistic & statistic);
        void DisplaySpectrumData(mat value);
        static vector<double> getResonanceFrequency(pair<rowvec,rowvec> filter);

        TaskOptionsParameters m_currentdata;

      /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      std::function<void(TaskOptionsParameters &)> DerivativeFunction = [this](TaskOptionsParameters & param)->void
      {
          param.m_derivativeParameters->outputSpectrum.first.clear();
          param.m_derivativeParameters->outputSpectrum.second.clear();
          SavitzkyFit * sfit = static_cast<SavitzkyFit *>(param.m_derivativeParameters);
          int Gap = sfit->numberOfPoints;

          switch(param.m_derivativeSpectraType.second)
          {
              case SAVITZJY_GOLAY_ALGORITHM:

                  sfit->findCorrection();
                  if((int)sfit->Tj.n_elem > 0)
                  {
                      param.m_CorrectionFunction.first = rowvec((int)sfit->Tj.n_cols);
                      for(int i = sfit->pointsRange.first,j=0; i<= sfit->pointsRange.second && j < (int)param.m_CorrectionFunction.first.n_cols ;i++,j++)
                      {
                          param.m_CorrectionFunction.first(j) = i;
                      }
                      param.m_CorrectionFunction.second = mat(2,(int)sfit->Tj.n_cols);
                      param.m_CorrectionFunction.second.zeros();
                      if((int)sfit->Tj.n_rows <= sfit->derivativeOrder )
                      {
                          sfit->derivativeOrder = (int)sfit->Tj.n_rows - 1;
                      }

                      param.m_CorrectionFunction.second.row(0) = rowvec(sfit->Tj.row(sfit->derivativeOrder));

                  }
                  sfit->convolveWithInputSpectra();
                  for(int i = 0;i < (int) sfit->outputSpectrum.first.size();i++)
                  {
                      sfit->outputSpectrum.first(i) = param.m_currentValuesOfX[sfit->outputSpectrum.first(i)];
                  }
                   sfit->outputSpectrum.first.print("first=");
                   sfit->outputSpectrum.second.print("second=");
                  *param.m_derivativeParameters = *sfit;
                 break;
              case SIMPLE_DIFFERENCE:
              case GAP:

                  sfit->Run(param.m_currentValuesOfX, param.m_CorrectionFunction,Gap);
                  *param.m_derivativeParameters = *sfit;

                  if(param.m_derivativeSpectraType.second ==  GAP && sfit->derivativeOrder > 1)
                  {
                      for(int i = 1;i< sfit->derivativeOrder;i++)
                      {
                        vector<double> valuex = Statistic::convToStd(sfit->outputSpectrum.first);
                        sfit->inputSpectrum = Statistic::convToStd(sfit->outputSpectrum.second);

                        sfit->outputSpectrum.first.clear();
                        sfit->outputSpectrum.second.clear();
                        param.m_CorrectionFunction.first.clear();
                        param.m_CorrectionFunction.second.clear();

                        sfit->Run(valuex, param.m_CorrectionFunction,Gap);
                         *param.m_derivativeParameters = *sfit;
                      }
                  }
                  param.m_CorrectionFunction.first.clear();
                  param.m_CorrectionFunction.second.clear();
                 break;

              case NO_DERIVATIVE_ALGORITHM:
              break;

          };



      };
      /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      /// \brief ApplyFunction
      /// \param f
      /// \param param
      ///
      void ApplyFunction(std::function<void(TaskOptionsParameters & param )> f, TaskOptionsParameters & param)
      {
            f(param);
      }
      //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      /// \brief ApplyFunction
      /// \param f
      /// \param param
      /// \param option
      ///
      void ApplyFunction(std::function<void(TaskOptionsParameters & param,  int )> f, TaskOptionsParameters & param,  int option)
      {
            f(param,option);
      }

      /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      /// \brief ApplyFunction
      /// \param f
      /// \param stat
      ///
      void ApplyFunction(std::function<void(Statistic &,const  Statistic &)> f,Statistic  &stat,const  Statistic & calib_stat)
      {
            f(stat,calib_stat);
      }
      ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      /// \brief ApplyFunction
      /// \param f
      /// \param hadamardSize
      /// \param hadamardMatrix
      /// \return
      ///
      mat ApplyFunction(std::function<mat(int , mat)> f, int hadamardSize, mat  hadamardMatrix)
      {
          return f(hadamardSize,hadamardMatrix);
      }
      /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      /// \brief ApplyFunction
      /// \param f
      /// \param sample
      /// \param filter
      ///
      void ApplyFunction(std::function<void(vector<double>&,vector<double>)> f, vector<double>& sample,vector<double> filter)
      {
          f(sample,filter);
      }
      void ApplyFunction
      (
              std::function<void(pair<vector<double> ,vector<double>> &,pair<mat,mat> &,vector<double>,string)> f,
              pair<vector<double> ,vector<double>>& sample,
              pair<mat,mat> &filter,
              vector<double> currentValueOfX,
              string option
      )
      {
          f(sample,filter,currentValueOfX,option);
      }
      /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      /// \brief ApplyFunction
      /// \param f
      /// \param sample
      ///
      void ApplyFunction(std::function<void(vector<double>&)> f, vector<double>& sample)
      {
          f(sample);
      }
      ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      /// \brief ApplyFunction
      /// \param f
      /// \param sample
      ///
      void ApplyFunction(std::function<void(pair<vector<double> ,vector<double>> &)> f, pair<vector<double> ,vector<double>> & sample)
      {
          f(sample);
      }

    };
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \brief The Preprocessing class
    ///
    class Preprocessing : public BaseFunction
    {
        friend class Avs;
         Preprocessing(TaskOptionsParameters task);
         void Run(Statistic & statistic);
         bool CheckScale();
    };
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \brief The BaseLineCorrection class
    ///
    class BaseLineCorrection : public BaseFunction
    {
         friend class Avs;

         protected:
                BaseLineCorrection(){}
                BaseLineCorrection(TaskOptionsParameters task);
                ~BaseLineCorrection(){m_currentdata.clear();}
               //private:
                /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                // this is for Function Fit Baseline
                typedef   void(*FitFunction)(vector<double> xValues,FitParameters &fitParameters);
                map<FunctionTypes,FitFunction> fitFunctionsMap =
                {
                    { POLYNOMIAL ,&Polynomial },
                    { EXPONENTIAL,&Exponential},
                    { LOGARITHMIC,&Logarithm  },
                    { POWER      ,&Power      }
                };

               void Run(Statistic & statistic);
               ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                // Simple Offcet correction
               void ApplyFunction
               (
                       std::function<void(vector<double> &,double,int )> f,
                       vector<double> & values,
                       double offset,
                       int option
               );
               // For two and multiple baseline correction
               // For Function Fit Correction
               void ApplyFunction
               (
                       std::function<void(TaskOptionsParameters&,vector<double> &  ,std::vector<NDUV::Point> ,int)> f,
                       TaskOptionsParameters &param,
                       vector<double> & values,
                       std::vector<NDUV::Point> points,
                       int
               );
               ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                std::function<void(TaskOptionsParameters&,vector<double> &  ,std::vector<NDUV::Point> ,int)> FunctionPointCorrection =

                        [this](TaskOptionsParameters& param,vector<double> & values,std::vector<NDUV::Point> points,int option)->void  // option 1 -> finds Correction,option 2 -> apply the correction, option 3 = does both
               {

                 std::vector<double>  Y;

                 if(option == 1 || option == 3)
                 {
                      std::sort(points.begin(), points.end(),points[0]);

                      std::vector<pair<double,double>>  CorrectionVector;

                      for(int i=0;i < (int)points.size() -1 ;i++)
                      {
                          double a = (points[i+1].y - points[i].y) / (points[i+1].x - points[i].x);
                          double b = points[i].y - a * points[i].x;
                          CorrectionVector.push_back(pair<double,double>(a,b));

                      }

                     int i = 0;
                     int j = 0;

                     for(int a = 0 ;a <(int) values.size() && a < (int)param.m_currentValuesOfX.size();a++)
                     {
                         double x = param.m_currentValuesOfX[a];
                         if(x >= points[i + 1].x)
                         {
                             i++;j++;
                         }
                         if(j == (int)CorrectionVector.size())
                         {
                             j=(int)CorrectionVector.size() - 1;
                         }
                         if(i == (int)points.size() - 1)
                         {
                             i = (int)points.size() - 2;
                         }

                         Y.push_back(CorrectionVector[j].first * x + CorrectionVector[j].second );

                     }
                     if(Y.size() > 0)
                     {
                        Statistic::addrow(param.m_CorrectionFunction.second,rowvec(Y));
                     }

                 }

                 rowvec currentcorrectionFunction =  (param.m_CorrectionFunction.second.row((int)param.m_CorrectionFunction.second.n_rows - 1));

                 if(option == 2 || option == 3)
                 {
                     for(int a = 0 ;a <(int) values.size() && a < (int) currentcorrectionFunction.n_cols;a++)
                     {
                         values[a] = values[a] -  currentcorrectionFunction(a);
                     }
                 }

               };

                //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                std::function<void(TaskOptionsParameters &,vector<double> & ,std::vector<NDUV::Point>,int )> FunctionFitCorrection =

                        [this](TaskOptionsParameters & param,vector<double> & values,std::vector<NDUV::Point> points,int option)->void
                {

                    if(option == 1 || option == 3)
                    {
                        FitFunction f;
                        if(fitFunctionsMap.find(param.m_fitParameters.functionType) != fitFunctionsMap.end())
                        {
                             f = fitFunctionsMap.at(param.m_fitParameters.functionType);
                        }

                        param.m_fitParameters.Ai = mat((int)points.size(), param.m_fitParameters.NumberOfCofficients );
                        for(int i = 0;i< (int)points.size(); i++)
                        {

                            for(int j = 0;j < param.m_fitParameters.NumberOfCofficients ;j++)
                            {
                                if(param.m_fitParameters.functionType == LOGARITHMIC || param.m_fitParameters.functionType == POWER)
                                     param.m_fitParameters.Ai(i,j)= pow(log(points[i].x), j);
                                else
                                     param.m_fitParameters.Ai(i,j)= pow(points[i].x, j);

                            }
                        }

                        param.m_fitParameters.bi = mat(points.size(),1);
                        for(int i = 0;i< (int)points.size(); i++)
                        {
                               if(param.m_fitParameters.functionType == EXPONENTIAL || param.m_fitParameters.functionType == POWER)
                                       param.m_fitParameters.bi(i,0) = log(points[i].y);
                               else
                                       param.m_fitParameters.bi(i,0)= points[i].y;
                        }
                        param.m_fitParameters.Ai.print("Ai = ");
                        param.m_fitParameters.bi.print("bi = ");

                        mat B = (param.m_fitParameters.Ai.t() * param.m_fitParameters.Ai);
                       // B.print("B=");
                        cout << "det(B): " << det(B) << endl;
                        try
                        {
                            bool valid = det(B) == det(B);
                            if(valid)
                            {
                                param.m_fitParameters.ai = pinv(B,0.01)  * param.m_fitParameters.Ai.t() * param.m_fitParameters.bi;
                                // or alternative uncomment next line
                                //fitParameters.ai = solve(fitParameters.Ai,fitParameters.bi);
                                param.m_fitParameters.ai.print("ai=");

                                mat I = pinv(B,0.01) * B;
                                //I.print("Identity Matrix = ");

                                //////////////////////////////////////////////////////////////////////////
                               f(param.m_currentValuesOfX,param.m_fitParameters);

                               /* for( int i =0;i < (int)fitParameters.Yxi.size();i++)
                                {
                                    cout << fitParameters.Yxi[i] << " ";
                                }*/
                               if(param.m_fitParameters.Yxi.size() > 0)
                               {
                                    Statistic::addrow(param.m_CorrectionFunction.second ,rowvec(param.m_fitParameters.Yxi));
                               }
                               // cout << endl;

                            }
                            else
                            {
                                cout << "Inverse can not be found . Determinant is null "<< endl;
                            }
                        }
                        catch(std::exception e)
                        {
                            cout << e.what()<< endl;
                        }
                    }
                    if(option == 2 || option == 3)
                    {
                        rowvec currentcorrectionFunction =  (param.m_CorrectionFunction.second.row((int)param.m_CorrectionFunction.second.n_rows - 1));


                        for(int i = 0 ; i < (int)values.size() &&  i < (int)currentcorrectionFunction.n_cols; i++)
                        {
                            values[i] = values[i] - currentcorrectionFunction(i);
                        }
                    }
                };

                ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                /// \brief Polynomial
                /// \param function
                /// \param degree
                /// \param coefficients
                ///
                static void Polynomial( pair<rowvec,rowvec> &function ,int degree,  rowvec coefficients )
                {
                    function.second.zeros();
                    for( int i =0;i < (int)function.first.n_cols;i++)
                    {
                        for(int j = 0;j < (int)coefficients.n_cols;j++)
                        {
                           function.second(i) =  function.second(i) + pow(function.first(i),coefficients(j));

                        }
                    }
                };

                //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                /// \brief Polynomial
                /// \param xValues
                /// \param fitParameters
                ///
               static void Polynomial(vector<double> xValues,FitParameters &fitParameters)
               {
                   fitParameters.Yxi.clear();
                   for( int i =0;i < (int)xValues.size();i++)
                   {
                       double sum = 0.0;
                       for(int j = 0;j < fitParameters.NumberOfCofficients;j++)
                       {
                           sum = sum + fitParameters.ai(j,0) * pow( xValues[i],j);

                       }
                       fitParameters.Yxi.push_back(sum);
                   }

               };
               ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
               /// \brief Exponential
               /// \param xValues
               /// \param fitParameters
               ///
               static void Exponential(vector<double> xValues,FitParameters &fitParameters)
               {
                    fitParameters.Yxi.clear();
                   // yi =  exp (a0 + a1 * xi) = exp(fitParameters.ai[0] + fitParameters.ai[1] * xValues[i];
                   for( int i =0;i < (int)xValues.size()  && (int)fitParameters.ai.n_rows == 2;i++)
                   {
                       double a0 = fitParameters.ai(0,0);
                       double a1 = fitParameters.ai(1,0);
                       fitParameters.Yxi.push_back( exp(a0) * exp(a1 * xValues[i]) );
                       //fitParameters.Yxi.push_back( a0 + a1 * xValues[i] );
                   }
               };
               //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
               /// \brief Logarithm
               /// \param xValues
               /// \param fitParameters
               ///
               static void Logarithm(vector<double> xValues,FitParameters &fitParameters)
               {
                    fitParameters.Yxi.clear();
                   // y =  A + B(Lnx)
                   // yi = fitParameters.ai[0] + fitParameters.ai[1] * lnx
                   for( int i =0;i < (int)xValues.size()  && (int)fitParameters.ai.n_rows == 2;i++)
                   {
                       double a0 = fitParameters.ai(0,0);
                       double a1 = fitParameters.ai(1,0);
                       fitParameters.Yxi.push_back( a0 + a1 * log(xValues[i]));
                      // fitParameters.Yxi.push_back( a0 + a1 * xValues[i] );

                   }
               };
               /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
               /// \brief Power
               /// \param xValues
               /// \param fitParameters
               ///
               static void Power(vector<double> xValues,FitParameters &fitParameters)
               {
                   // y = A * X ^ B   assume
                   // lny= lnA + B*lnX ;   assume  lnx = Z then lny = lnA + B * Z
                   // lny = ln(fitParameters[0]) + fitParameters[1] * Z = >  ln(fitParameters[0]) + fitParameters[1] * lnx
                   // y = e ^ (fitParameters[0]) + fitParameters[1] * lnx)

                   // yi =  exp (a0 + a1 * lnxi) = exp(fitParameters.ai[0] + fitParameters.ai[1] * ln(xValues[i]));
                   fitParameters.Yxi.clear();
                   for( int i =0;i < (int)xValues.size() && (int)fitParameters.ai.n_rows == 2;i++)
                   {
                       double a0 = fitParameters.ai(0,0);
                       double a1 = fitParameters.ai(1,0);
                       fitParameters.Yxi.push_back(exp(a0) * pow(xValues[i],a1));
                       //fitParameters.Yxi.push_back( a0 + a1 * xValues[i] );
                   }

               };

               /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                 //for Simple Correction
                double m_correction_value;
    };
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \brief The SimpleOffsetCorrection class
    ///
    class SimpleOffsetCorrection : public BaseLineCorrection
    {
       friend class BaseLineCorrection;
       friend class Avs;

       SimpleOffsetCorrection(TaskOptionsParameters task);

       //Simple Baseline
      std::function<void(vector<double> &,double ,int )> FunctionSimpleCorrection = [this](vector<double> & values,double offset,int option)->void
      {
        if(option == 1 || option == 3)
        {
            int  numberOfFunctionValues = (int)values.size();
            m_currentdata.m_CorrectionFunction.second = mat(1,(int)values.size());
            for(int i = 0;i<numberOfFunctionValues;i++)
            {
                m_currentdata.m_CorrectionFunction.second(0,i) = offset;
            }

        }
        if(option == 2 || option == 3)
        {
            for(auto & v: values)
            {
                v =  v - offset;
            }
        }
      };

    };
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \brief The TwoPointBaseLineCorrection class
    ///
    class TwoPointBaseLineCorrection : public BaseLineCorrection
    {
        friend class BaseLineCorrection;
        friend class Avs;
        TwoPointBaseLineCorrection(TaskOptionsParameters task);
    };
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \brief The MultiPointBaseLineCorrection class
    ///
    class MultiPointBaseLineCorrection : public BaseLineCorrection
    {
       friend class BaseLineCorrection;
       friend class Avs;
       MultiPointBaseLineCorrection(TaskOptionsParameters task);
    };
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \brief The InteractivePolinomialBaseLineCorrection class
    ///
    class InteractivePolinomialBaseLineCorrection : public BaseLineCorrection
    {
       friend class BaseLineCorrection;
       friend class Avs;
       InteractivePolinomialBaseLineCorrection(TaskOptionsParameters task);
    };
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \brief The FunctionFitBaseLineCorrection class
    ///
    class FunctionFitBaseLineCorrection : public BaseLineCorrection
    {
       friend class BaseLineCorrection;
       friend class Avs;
       FunctionFitBaseLineCorrection(TaskOptionsParameters task);
    };

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \brief The GIFTSBaseLineCorrection class
    ///
    class GIFTSBaseLineCorrection : public BaseLineCorrection
    {
           friend class BaseLineCorrection;
           friend class Avs;

           GIFTSBaseLineCorrection(TaskOptionsParameters task);
           void Run(Statistic & statistic);

           void calculate
           (
               TaskOptionsParameters & param,
               vector<double> & values,
               std::vector<NDUV::Point> currentPoints,
               std::vector<NDUV::Point> currentPointsBelow,
               int option,
               vector<pair<mat,double>> &CorrectionFunctions
           );

           std::function<void(TaskOptionsParameters &, vector<double> &  ,std::vector<NDUV::Point> ,int )> FunctionLeastSquareFitLine =

                   [this](TaskOptionsParameters & param,vector<double> & values,std::vector<NDUV::Point> points,int option)->void
           {

               if(option == 1 || option == 3)
               {
                  param.m_fitParameters.Yxi.clear();
                  param.m_fitParameters.ai.clear();
                  param.m_fitParameters.bi.clear();


                  findStatisticsValues( param.m_fitParameters,points);

                  // Create Correction vector Yxi = a0 + a1 * xAverage
                  for(auto point: param.m_currentValuesOfX)
                  {
                       param.m_fitParameters.Yxi.push_back( param.m_fitParameters.ai(0,0) +   param.m_fitParameters.ai(1,0) * point);
                  }
                  // Create Correction Function
                  if( param.m_fitParameters.Yxi.size() > 0)
                  {
                      param.m_CorrectionFunction.second = rowvec(param.m_fitParameters.Yxi);
                  }
               }
               // Apply the correction to the sample
               if(option == 2 || option == 3)
               {
                   for(int i = 0 ; i < (int)values.size() &&  i < (int) param.m_CorrectionFunction.second.n_cols; i++)
                   {
                       values[i] = values[i] - param.m_CorrectionFunction.second(0,i);
                   }
               }
           };

           //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


           void findStatisticsValues(FitParameters &fitParameters,vector<Point> points)
           {
               double sumX;
               double sumY;
               double sumXY;
               double sumXX;
               double meanX;
               double meanY;
               double sum;
               double sumXSquared;
               vector<double> yPoints;
               vector<double> xPoints;
               fitParameters.ai = mat(2,1);
               sumXSquared = 0;
               sum = 0;
               for(auto i :  points)
               {
                       yPoints.push_back(i.y);
                       xPoints.push_back(i.x);
               }
               // Method 1
               sumX = 0;
               for(int i=0;i < (int)xPoints.size();i++)
               {
                   sumX = sumX + xPoints[i];

               }

               for(int i=0;i < (int)yPoints.size();i++)
               {
                    sumY = sumY + yPoints[i];
               }

               sumXY=0;
               for(int i=0;i < (int)xPoints.size() && i < (int)yPoints.size();i++)
               {
                   sumXY = sumXY + xPoints[i] * yPoints[i];
               }
               sumXX = 0;
               for(auto & xpoint :  xPoints)
               {
                   sumXX = sumXX + xpoint * xpoint;
               }
               // Slope(b) = (NΣXY - (ΣX)(ΣY)) / (NΣX^2 - (ΣX)^2)
               // Intercept(a) = (ΣY - b(ΣX)) / N

                fitParameters.ai(1,0) = (xPoints.size() * sumXY - sumX * sumY) / (xPoints.size() * sumXX - sumX * sumX);
                fitParameters.ai(0,0) = (sumY - fitParameters.ai(1,0) * sumX) / xPoints.size();
               // fitParameters.ai.print("ai0=");

               // Method 2
               rowvec xVector = (rowvec)(xPoints);
               rowvec yVector = (rowvec)(yPoints);
               meanX = arma::mean( xVector);

               meanY = arma::mean( yVector );

               // calculate xi - xAverage and (xi - xAverage)^2
               for(auto & xpoint :  xPoints)
               {
                    xpoint = xpoint - meanX;
                    sumXSquared =  sumXSquared + pow(xpoint,2);
               }
               // calculate yi - yAverage
              for(auto & ypoint :  yPoints)
              {
                   ypoint = ypoint - meanY;
              }
              // calculate (xi - meanX) * (yi -  meanY)
              for(int i=0;i < (int)xPoints.size();i++)
              {
                  sum = sum + xPoints[i] * yPoints[i];
              }

               fitParameters.ai(1,0) = sum / sumXSquared;
               fitParameters.ai(0,0) = meanY -  fitParameters.ai(1,0) * meanX;
               //fitParameters.ai.print("ai1=");
           }

    };
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \brief The DataSmoothing class
    ///
    class DataSmoothing : public BaseFunction
    {
       friend class Avs;
       protected:
        DataSmoothing(){}
        DataSmoothing(TaskOptionsParameters task){}
         void Run(Statistic & statistic);
   } ;

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \brief The BinomialSmoothing class
    ///
   class BinomialSmoothing : public DataSmoothing
   {
       friend class DataSmoothing;
       friend class Avs;

       BinomialSmoothing(TaskOptionsParameters task);


       std::function<void(TaskOptionsParameters &,int)> BinomialSmoothingFunction = [this](TaskOptionsParameters &param,int option)->void
       {
           BinomialFit * fit = static_cast<BinomialFit *>(param.m_dataSmoothingParameters);
           fit->outputSpectrum.first.clear();
           fit->outputSpectrum.second.clear();

           if(option == 1 || option == 3)
           {
                param.m_CorrectionFunction.first.clear();
                param.m_CorrectionFunction.second.clear();
                fit->calculateCoefficients( );

                param.m_CorrectionFunction.first = rowvec((int)fit->coefficients.size());
                for(int i = 0;i < (int)fit->coefficients.size();i++)
                {
                     param.m_CorrectionFunction.first(i) = i;
                }
                param.m_CorrectionFunction.second = rowvec(fit->coefficients);
           }
           else if(option == 2 || option == 3)
           {
               fit->convolveWithInputSpectra();
               for(int i = 0;i < (int) fit->outputSpectrum.first.size();i++)
               {
                    fit->outputSpectrum.first(i) = param.m_currentValuesOfX[fit->outputSpectrum.first(i)];
               }
           }
           *param.m_dataSmoothingParameters = *fit;
       };

};
   ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   /// \brief The SavitzkyGolaySmoothing class
   ///
   class SavitzkyGolaySmoothing : public DataSmoothing
   {
       friend class DataSmoothing;
       friend class Avs;
       SavitzkyGolaySmoothing(TaskOptionsParameters task);


       std::function<void(TaskOptionsParameters &,int )> SavitzkySmoothingFunction = [](TaskOptionsParameters &param,int option)->void
       {
                 SavitzkyFit * fit = static_cast<SavitzkyFit *>(param.m_dataSmoothingParameters);
                 fit->outputSpectrum.first.clear();
                 fit->outputSpectrum.second.clear();
                 if(option == 1 || option == 3)
                 {
                     param.m_CorrectionFunction.first.clear();
                     param.m_CorrectionFunction.second.clear();

                     fit->findCorrection();
                     if((int)fit->Tj.n_elem > 0)
                     {
                         param.m_CorrectionFunction.second = rowvec(fit->Tj.row(0));
                     }

                     param.m_CorrectionFunction.first = rowvec((int)param.m_CorrectionFunction.second.size());
                     for(int i = fit->pointsRange.first,j=0;i <= fit->pointsRange.second && j < (int)param.m_CorrectionFunction.first.size();i++,j++)
                     {
                          param.m_CorrectionFunction.first(j) = i;
                     }
                 }
                 else if(option == 2 || option == 3)
                 {
                     fit->convolveWithInputSpectra();
                     for(int i = 0;i < (int) fit->outputSpectrum.first.size();i++)
                     {
                          fit->outputSpectrum.first(i) = param.m_currentValuesOfX[fit->outputSpectrum.first(i)];
                     }
                 }
                 *param.m_dataSmoothingParameters = *fit;
       };

   };
   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   /// \brief The DerivativeSpectra class
   ///
   class DerivativeSpectra : public BaseFunction
   {
       friend class Avs;
       DerivativeSpectra(TaskOptionsParameters task);
       void Run(Statistic & statistic);


   };
   ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   /// \brief The MeanCenteringMethod class
   ///
   class MeanCenteringMethod : public BaseFunction
   {
         friend class Avs;
         MeanCenteringMethod(){}
         MeanCenteringMethod(TaskOptionsParameters task);
         void  Run(Statistic & statistic);

   };

   //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   /// \brief The CalibrationMethod class
   ///
   class CalibrationMethod : public BaseFunction
   {
       friend class Avs;
       protected:
       CalibrationMethod() {}
       CalibrationMethod(TaskOptionsParameters task);
   };
   //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   /// \brief The UnivariateCalibration class
   ///
   class UnivariateCalibration : public CalibrationMethod
   {
       friend class Avs;
       UnivariateCalibration(TaskOptionsParameters task);
       void Run(Statistic & statistic);
       FilteredSpectra m_filteredScaledSpectrum;
       void getFilteredData(const Statistic & statistic);
       void polinomialInterpolation(pair<rowvec,rowvec> sample,vector<int> polinomialDegrees);
       void testFilters1();
       void testFilters2();
   };
   ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   /// \brief The MultivariateCalibration class
   ///
   class MultivariateCalibration : public CalibrationMethod
   {
     friend class Avs;
      MultivariateCalibration(TaskOptionsParameters task);
      void Run(Statistic & statistic);
   };
   /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   /// \brief The Validation class
   ///
   class Validation : public BaseFunction
   {
      friend class Avs;
       Validation(TaskOptionsParameters task);
       void Run(Statistic & statistic);
   };
   /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   /// \brief The Prediction class
   ///
   class Prediction : BaseFunction
   {
        friend class Avs;
        Prediction(TaskOptionsParameters task);
        void Run(Statistic & statistic);
   };
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \brief The Avs class
    ///
    class Avs
    {
        public:
            Avs(){};

            virtual ~Avs(){clear();};

            void clear(){m_tasks.clear();}
            void AddTask(FunctionName name,string nametext,TaskOptionsParameters task);

            void ProcessSpectrum(Statistic &s);
            void ProcessSpectrum(FunctionName taskname,Statistic &s);
            void ProcessSpectrum(pair<FunctionName,BaseFunction *> task,Statistic &s);

            void ClearTasks();

            BaseFunction * GetFunction(FunctionName);
        private:
             BaseFunction* createTask(FunctionName name,string nametext,TaskOptionsParameters task);
             void deleteTask(FunctionName name);
             map< FunctionName,BaseFunction *> m_tasks;
    };

} /* namespace NDUV */

#endif /* AVS5216_H_ */
