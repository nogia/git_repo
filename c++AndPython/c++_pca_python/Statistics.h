/*
 * Statistics.h
 *
 *  Created on: May 3, 2016
 *      Author: inna
 */

#ifndef STATISTICS_H_
#define STATISTICS_H_

#include "PCAComponent.h"
#include "Optimization.h"


namespace NDUV
{
    static std::tuple<double, double,double> resulttuple;
    static  std::tuple<double, double,double> * createTuple(double a, double b,double c)
    {

        resulttuple =  make_tuple(a,b,c);
        return & resulttuple;
    }
   static std::tuple<double, double,double> * defaultFourierFit = createTuple( 3.0, 2.0, 20.0 );
   static std::tuple<double, double,double> * defaultParametersForBinomial = createTuple( 3, 0, 0 );
   static std::tuple<double, double,double> * defaultParametersForSavitzkyGolaySmoothing = createTuple( 5, 3, 0 );

   static std::tuple<int, int,int> defaultParametersFirstDerivative{ 8, 4, 1 };
   static std::tuple<int, int,int> defaultParametersSecondDerivative{ 7, 6, 2 };

   static vector<Constituents> mapGetKeys( map<Constituents,int> collection)
   {
       vector<Constituents>  keys;
       for (std::map<Constituents, int>::iterator i = collection.begin(); i != collection.end(); ++i)
       {
           keys.push_back(i->first);
       }
       return keys;
   }


   class Optimization;


  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  /// \brief The FitParameters struct
  ///
  struct FitParameters
  {
    public:
      ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      /// \brief FitParameters
      /// \param f
      /// \param N
      /// \param xpoints
      ///
     FitParameters(FunctionTypes f = POLYNOMIAL,int N = 2,std::vector<int> xpoints = defaultMultipleBaselineXpoints) : m_Xpoints(xpoints)

     {
         functionType = f;
         NumberOfCofficients = N;
     }
     //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
     /// \brief FitParameters
     /// \param x
     ///
     FitParameters(const FitParameters& x)
     {

                 clear();
                 NumberOfCofficients      = x.NumberOfCofficients ;
                 m_Xpoints                = x.m_Xpoints;
                 Ai                       = x.Ai;
                 bi                       = x.bi;
                 ai                       = x.ai;
                 Yxi                      = x.Yxi;
                 functionType             = x.functionType;

     }
     ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
     /// \brief operator ==
     /// \param x
     /// \return
     ///
     bool operator==(const FitParameters& x) const
     {
         bool result = true;
         if(
                 (int)functionType             == (int)x.functionType             &&
                 (int)NumberOfCofficients      == (int)x.NumberOfCofficients      &&
                 approx_equal(Ai, x.Ai  , "absdiff", 0.001)                       &&
                 approx_equal(bi, x.bi  , "absdiff", 0.001)                       &&
                 approx_equal(ai, x.ai  , "absdiff", 0.001)                       &&
                 Yxi                           ==  x.Yxi                          &&
                 m_Xpoints                      ==  x.m_Xpoints
           )
         {
             result = true;
         }
         else
         {
             result = false;
         }
         return result;
     }
     //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
     /// \brief operator =
     /// \param fitparam
     /// \return
     ///
     FitParameters& operator=(const FitParameters & fitparam)
     {
         if(this != &fitparam)
         {
                 clear();
                 NumberOfCofficients      = fitparam.NumberOfCofficients ;
                 m_Xpoints                = fitparam.m_Xpoints;
                 Ai                       = fitparam.Ai;
                 bi                       = fitparam.bi;
                 ai                       = fitparam.ai;
                 Yxi                      = fitparam.Yxi;
                 functionType             = fitparam.functionType;

         }
         return *this;
     }
     ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
     /// \brief clear
     ///
     void clear()
     {
         m_Xpoints.clear();
         Ai.clear();
         bi.clear();
         ai.clear();
         Yxi.clear();
         functionType = NOT_SET;
     }
     ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
     /// \brief setFitParameters
     /// \param ftype
     /// \param number
     /// \param points
     /// \return
     ///
     FitParameters setFitParameters(FunctionTypes ftype,int number,vector<int> points)
     {
          FitParameters result;
          result.functionType = ftype;
          result.NumberOfCofficients = number;
          result.m_Xpoints = points;
          return result;
     }
     ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
     /// \brief functionType
     ///
     FunctionTypes functionType;
     int NumberOfCofficients;

      mat Ai;
      mat bi;
      mat ai;
      std::vector<double> Yxi;

      std::vector<int> m_Xpoints;


  };

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  /// \brief The Fit struct
  ///
    struct Fit
    {
        int numberOfPoints;
        int polinomialDegree;
        mat leastSquareFit;
        pair<mat,mat> outputSpectrum;
        std::vector<double> inputSpectrum;

        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Run
        /// \param valuex
        /// \param function
        /// \param Gap
        ///
        void Run(vector<double> valuex,pair<mat,mat> & function, double Gap)
        {
            outputSpectrum.second = rowvec(((int)inputSpectrum.size() / (1 + Gap)) - 1);
            outputSpectrum.first  = rowvec(((int)inputSpectrum.size() / (1 + Gap)) - 1);
            function.second = mat(2,((int)inputSpectrum.size()/ (1 + Gap)) - 1);
            function.second.zeros();
            function.first = rowvec(((int)inputSpectrum.size() / (1 + Gap)) - 1);

            for(int i=0,j=0;i < (int)inputSpectrum.size() - 1 && j <  (int)outputSpectrum.first.size();i = i + 1 + Gap,j++)
            {
                 if( i + 1 + Gap < (int)inputSpectrum.size() - 1 )
                 {
                      outputSpectrum.first(j) =  valuex[ i+1 + Gap];
                      outputSpectrum.second(j) = inputSpectrum[i+1 + Gap] - inputSpectrum[i];
                 }
                 else
                 {
                      outputSpectrum.first(j) =  valuex[(int) valuex.size() - 1];
                      outputSpectrum.second(j) = inputSpectrum[(int)inputSpectrum.size() - 1] - inputSpectrum[i];
                 }
            }
            /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

            if( outputSpectrum.second.n_elem > 0)
            {
                function.first = outputSpectrum.first;
                function.second.row(0) =  outputSpectrum.second;
            }
            else
            {
                function.first = rowvec(valuex);
                function.second = rowvec(valuex);
                function.second.zeros();
                outputSpectrum.first = rowvec(valuex);
                outputSpectrum.second = rowvec(valuex);
                outputSpectrum.second.zeros();
            }

        }
    };
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \brief The FourierFit struct
    ///
   struct  FourierFit : public Fit
   {
       //for  Fourier
       double m_deltaT;
       double m_cutOffFrequency;

       FourierFit(std::tuple<double, double, double> inparam = *defaultFourierFit)
       {
           numberOfPoints = (int)std::get<0>(inparam);
           m_deltaT = (int)std::get<1>(inparam);
           m_cutOffFrequency = (int)std::get<2>(inparam);
           cout << "m_cutOffFrequency="<<  m_cutOffFrequency << endl;
           polinomialDegree  = -1;
       }

        vector<double> coefficients;
   };

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  /// \brief The BinomialFit struct
  ///
  struct BinomialFit : public Fit
  {
      ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      /// \brief BinomialFit
      /// \param inparam
      ///
      BinomialFit(std::tuple<double, double, double> inparam = *defaultParametersForBinomial)
      {
          numberOfPoints = (int)std::get<0>(inparam);
          polinomialDegree = 2 * numberOfPoints + 1;
      }
      ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      /// \brief calculateCoefficients
      ///
      void calculateCoefficients()
      {
          coefficients = vector<double>(polinomialDegree  ,0.0);

          double Constant = pow(2, -(2 * numberOfPoints));
          coefficients[0] =1;
          calculateCoefficients(polinomialDegree-1);
          for(int i = 0;i < (int)coefficients.size();i++)
          {

              coefficients[i] = Constant * coefficients[i];
              //cout << coefficients[i] <<" ";
          }
         // cout << endl;
      }
      //  Binomial coefficients are
      //  S    Polinomial Order  Number Of Coefficients                       Values Of a coefficients
      //  0           0                  1                                                  1
      //  1           2                  3                                           1    0.500      1
      //  2           4                  5                                     1   0.250  0.167    0.250   1
      //  3           6                  7                                1  0.167 0.067  0.050    0.067  0.167  1

      ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      /// \brief calculateCoefficients
      /// \param start
      ///
      void calculateCoefficients(int start)
      {
          for(int i=start;i>-1;i--)
          {
               coefficients[i] = factorial(start) / (factorial(i) * factorial(start - i));
          }
      }
      ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      /// \brief convolveWithInputSpectra
      ///
      void convolveWithInputSpectra()
      {
              rowvec A  = conv_to<rowvec>::from(inputSpectrum);
              rowvec B = conv_to<rowvec>::from(coefficients);
              outputSpectrum.second = conv(A,B,"same");

              outputSpectrum.first = rowvec((int)outputSpectrum.second.size());

              for(int i = 0;i < (int) outputSpectrum.second.size();i++)
               {
                  outputSpectrum.first(i) = double(i);
               }

              cout << endl;
       }

      vector<double> coefficients;
  };

  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  /// \brief The SavitzkyFit struct
  ///
  struct SavitzkyFit : public Fit
  {

          std::pair<double,double> pointsRange;//(-(numberOfPoints-1)/2,(numberOfPoints-1)/2);
          int derivativeOrder;
          mat Tj;
          //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
          /// \brief SavitzkyFit
          /// \param inparam
          ///
          SavitzkyFit(std::tuple<double, double, double> inparam = *defaultParametersForSavitzkyGolaySmoothing)
          {
              numberOfPoints = (int)std::get<0>(inparam);
              polinomialDegree = (int)std::get<1>(inparam);
              derivativeOrder = (int)std::get<2>(inparam);
              if(numberOfPoints >= 1)
              {
                  pointsRange.first = -(double)((int)(numberOfPoints-1)/2);
                  pointsRange.second = (double)((int)(numberOfPoints-1)/2);
              }
              else
              {
                  pointsRange.first = (double)((int)(numberOfPoints-1)/2);
                  pointsRange.second = -(double)((int)(numberOfPoints-1)/2);
              }
              leastSquareFit= mat(pointsRange.second * 2 + 1,polinomialDegree + 1);

              cout << "numberOfPoints = "    << numberOfPoints
                   << " polinomialDegree = " << polinomialDegree
                   << " derivativeOrder = "  << derivativeOrder
                   << " Range = [ "          << pointsRange.first << " , " << pointsRange.second << " ] "<< endl;
              cout << endl;

          }
          ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
          /// \brief findCorrection
          ///
          void findCorrection()
          {
              for(double j = pointsRange.first; j <= pointsRange.second;j++)
              {
                       for(int i=0;i < polinomialDegree +1;i++)
                       {
                           leastSquareFit(j + pointsRange.second,i) = pow(j,i);
                       }
               }

                leastSquareFit.print("Vandemode Matrix=");
                Tj = (pinv(  leastSquareFit.t() *  leastSquareFit) *  leastSquareFit.t());

                if(Tj.n_elem > 0)
                {
                   Tj.row(0).print("Derivative 0 =");
                   if(Tj.n_rows >= 1)
                         Tj.row(1).print("Derivative 1 =");
                }
                Tj.print("Tj=");
          }
          /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
          /// \brief convolveWithInputSpectra
          ///
          void convolveWithInputSpectra()
          {
              if(polinomialDegree >= derivativeOrder)
              {
                 // (rowvec(inputSpectrum)).print("In=");
                  rowvec A  = conv_to<rowvec>::from(inputSpectrum);
                  rowvec B = conv_to<rowvec>::from(Tj.row(derivativeOrder));
                 // B.print("Tj(0)=");
                  outputSpectrum.second = conv(A,B,"same");

                  outputSpectrum.second =  factorial(derivativeOrder) * outputSpectrum.second;
                  outputSpectrum.first = rowvec((int)outputSpectrum.second.size());
                 // outputSpectrum.second.print("OUT");

              }
              else
              {
                  outputSpectrum = pair<mat,mat>( rowvec((int)inputSpectrum.size()),rowvec((int)inputSpectrum.size()) );
                  outputSpectrum.second.zeros();
              }

              for(int i = 0;i < (int) outputSpectrum.first.size();i++)
              {
                  outputSpectrum.first(i) = double(i);
              }
                //outputSpectrum.second.print("O=");
           }

   };

  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  /// \brief The Stat class
  ///
   class Stat
    {
      friend class Statistic;
      friend class Plot;
     public:
      ~Stat()
      {
          variables.clear();
          meani.clear();
          SEi.clear();
          CVi.clear();
          PRESSi.clear();
          MSEi.clear();
          RMSEi.clear();
      }

      private:

        mat meani;
        mat SEi;
        mat CVi;
        mat PRESSi;
        mat MSEi;
        mat  RMSEi;

        double meanValue;
        double stdeviationValue;
        double TRV;
        double ERV;
        double CV;

        double MSEAVERAGE;


       int index;
       mat RecreatedConcentrations;
       mat OriginalConcentrations;
       mat ResidualSpectra;
       mat ResidualConcentration;

       int kfold;
       public:
        int numberOfPCA;
        double PRESSAVERAGE;
        double RMSEAVERAGE;
        double R2;
        int start;
        int end;
        int variableStart;
        int variableEnd;
        vector<int> variables;
       ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
       /// \brief getIndex
       /// \return
       ///
       int getIndex()
       {
           return index;
       }
       //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
       /// \brief getPCANumber
       /// \return
       ///
       int getPCANumber() const
       {
           return numberOfPCA;
       }

       //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
       /// \brief setPCANumber
       /// \param number
       ///
       void setPCANumber(int number)
       {
           numberOfPCA = number;
       }
       void printToFile(string filename,int delta = -1,int start=-1,int end = -1,int size = -1,bool printvariableslist= false)
       {
           ofstream out;
           out.open (filename,ios::out | ios::app );
           out << "#####   Generation = [" << delta <<  "] varstart= [" <<start<<"] varend = ["<<end<<"] PopulationSize = ["<<size <<"]   #####"<< endl;
           out << "VarSize        VarStart          VarEnd          PCA          R2          PRESS          RMSE          TRV              " << endl;
           string strout =  "[" + to_string((int)variables.size()) +  "]          [" + to_string(variableStart) + "]              [" + to_string(variableEnd) + "]          [" + to_string(index + 1) + "]      [" + to_string(R2) + "] [" + to_string(PRESSAVERAGE) +
                   "]   [" + to_string(RMSEAVERAGE) + "] [" + to_string(TRV) + " ] ";
           out    << strout << endl;
           if(printvariableslist)
           {
               out << "[ ";
               for(auto  v: variables)
               {
                   out << v <<" ";
               }
               out << " ]"<< endl;
           }
           out << "############################################################################################################################" << endl;
           out.close();
       }

       /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
       /// \brief print
       /// \param crossvalidation
       /// \param reportConcentrations
       ///
       void print(bool crossvalidation = false,bool reportConcentrations = false) const
       {

           if(crossvalidation)
           {
                string out = "PCA=[" + to_string(index + 1) +   "] R2=[" + to_string(R2) + "] CV=[" + to_string(CV) + "] TRV=[" + to_string(TRV) + "] PRESS=[" + to_string(PRESSAVERAGE) + "]" +
                        " ] RMSE=[" + to_string(RMSEAVERAGE)  + " ] ERV=[" + to_string(ERV) + " [KFold = " + to_string(kfold) + "] [Sample start = " + to_string(start) + " Sample end = " + to_string(end) + "]" +
                        " ] Var Size =[" +  to_string((int)variables.size()) + " ] VarStart=[" + to_string(variableStart) + " ] VarEnd=[" + to_string(variableEnd) + " ]";
                if(reportConcentrations)
                {
                    int cols = min((int)OriginalConcentrations.n_cols,(int)RecreatedConcentrations.n_cols);
                    int rows = min((int)OriginalConcentrations.n_rows,(int)RecreatedConcentrations.n_rows);
                    out = out + "\n";
                    for(int j = 0;j < rows;j++)
                    {
                        out = out + " O=[";
                        for(int i = 0;i < cols;i++)
                        {
                            out = out + " " + to_string(OriginalConcentrations(j,i));
                            out = out + "] R=[";
                            out = out + " " + to_string(RecreatedConcentrations(j,i));
                        }
                        out = out + "]\n";
                    }

                }
                cout << "*****************************************************************************************************"<<endl;
                cout << out << endl;
                //ResidualConcentration.print("Residual Concentration = ");
                cout << "*****************************************************************************************************"<<endl;
                //RMSEi.print("RMSi=");

           }
           else
           {
              cout  << "PCA=["            << setw(2) << index + 1                  <<
                     "] R2=["           << setw(4) << R2                         <<
                     "] CV=["           << setw(4) << CV                         <<
                     "] TRV=["          << setw(4) << TRV                        <<
                     "] PRESS=["        << setw(4) << PRESSAVERAGE               <<
                     "] MSE=["           << setw(4) << MSEAVERAGE               <<
                     "] RMSE=["         << setw(4) << RMSEAVERAGE                <<
                     "] ERV=["          << setw(4) << ERV                        <<
              endl;
           }
        }

       /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
       /// \brief CalculateErrors
       /// \param New
       /// \param Original
       /// \param npca
       /// \return
       ///
        Stat CalculateErrors(const mat &New,const mat & Original,int iindex,int npca,int kkfold = -1,int istart=-1,int iend=-1,int vstart =-1,int vend = -1)
        {

            RecreatedConcentrations = New;
            OriginalConcentrations = Original;
            start = istart;
            end = iend;
            variableStart = vstart;
            variableEnd = vend;
            kfold = kkfold;
            numberOfPCA = npca;
            index = iindex;

            if((int)New.n_elem < 0 || (int)Original.n_elem < 0)
                return *this;
            if((int) New.n_rows != (int)Original.n_rows)
                return *this;

            int numcolsmax = max((int)Original.n_cols,(int)New.n_cols);

            mat Originalm,Newm, E;

            Originalm = mat((int)Original.n_rows,numcolsmax);
            Newm      = mat((int)New.n_rows,numcolsmax);
            Originalm.zeros();
            Newm.zeros();
            Originalm.cols(0,(int)Original.n_cols -1)  =  Original.cols(0,(int)Original.n_cols -1);
            Newm.cols(0,(int)New.n_cols - 1) = New.cols(0,(int)New.n_cols  - 1);

            E = Originalm - Newm;


            meani = mat((int)E.n_rows,1);
            MSEi  = mat((int)E.n_rows,1);
            SEi   = mat((int)E.n_rows,1);
            for(int i=0; i < (int)E.n_rows ; ++i)
            {
               meani.row(i) = arma::mean(E.row(i));
               SEi.row(i) = stddev(E.row(i));// SE
            }
            PRESSi = mat((int)E.n_rows,1);
            PRESSi.zeros();

            for(int i=0; i < (int)E.n_rows ; ++i)
            {

                 for(int j=0; j < (int)E.n_cols ; ++j)
                 {
                    PRESSi(i,0) = PRESSi(i,0) + pow(E(i,j),2);
                 }
            }

            MSEi = PRESSi / (int)E.n_cols;
            MSEAVERAGE = arma::mean(arma::mean(MSEi));


            RMSEi = MSEi;
            for(int i=0; i < (int)MSEi.n_rows ; ++i)
            {
                    RMSEi(i,0) = pow(RMSEi(i,0),0.5);
            }

            RMSEAVERAGE = arma::mean(arma::mean(RMSEi));

            if(SEi.n_rows == 0)
            {
                SEi = mat(size(meani));
                SEi.zeros();
            }

            CVi = 100 * SEi ;
            if(CVi.n_rows == 0)
            {
                CVi = mat(size(meani));
                CVi.zeros();
            }
            //average CV
            if(CVi.n_rows != 0)
               CV =  mean(mean(CVi));
            else
               CV = 0;
            TRV = 0;
            double sumOriginal =0;

            vec origvar((int)E.n_rows *  (int)E.n_cols);
            vec residvar((int)E.n_rows *  (int)E.n_cols);
            int count = 0;
            for(int i=0;i < (int)E.n_rows;i++)
            {
                   for(int j=0;j < (int)E.n_cols;j++)
                   {
                       TRV =   TRV + pow(E(i,j),2);
                       sumOriginal = sumOriginal + pow(Originalm(i,j),2);
                       origvar(count ) = Originalm(i,j);
                       residvar(count ) = E(i,j);
                       count++;
                   }
            }

            PRESSAVERAGE = TRV;
            if(sumOriginal == 0)
                ERV = -1000000;
            else
                ERV = 1 -(TRV / sumOriginal);

            //Values of R2 outside the range 0 to 1 can occur where it is used to measure
            //the agreement between observed and modeled values and where the "modeled"
            //values are not obtained by linear regression and depending on which formulation of R2 is used


            double variencetotal = var(origvar);

            double evarience = var(residvar);


            if(variencetotal == 0 && evarience == 0)
                R2 = 1;
            else if(variencetotal == 0 && evarience < 0)
                R2 = 100000;
            else if(variencetotal == 0 && evarience > 0)
                R2 = -100000;
            else
                R2 = 1 - (evarience / variencetotal);

            TRV = TRV / E.n_elem;

            return *this;
        }
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief StudentTest
        /// \param Ec_error
        /// \param meanConcentrations
        /// \return
        ///
        bool StudentTest( mat Ec_error,mat meanConcentrations)
        {
           // Ec_error.print("Ec=");
            bool result = true;
            for(int i =0;i < (int)meanConcentrations.n_cols && i < (int)Ec_error.n_cols;i++)
            {
                colvec temp = abs(Ec_error.col(i));
               // temp.print("t=");
                meanValue = arma::mean(arma::mean(temp,1));
                stdeviationValue =  arma::stddev(temp,1);

                double p = (int)temp.n_rows;
                double testValue =  pow(p,0.5);
                testValue = testValue * meanValue;
                testValue = testValue / stdeviationValue;
                if(abs(testValue) > STUDENTTEST_SRESHOLD )
                {
                    result = false;
                    break;
                }
            }
            return result;
        }
        ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief operator ()
        /// \param a
        /// \param b
        /// \return
        ///
        bool operator()(const  Stat a,const  Stat b)const
        {
            if(a.R2 == b.R2 )
            {
                return a.PRESSAVERAGE < b.PRESSAVERAGE;
            }

            return a.R2 > b.R2;
        }
        bool operator>(const  Stat b)const
        {
            if(R2 == b.R2 )
            {
                return PRESSAVERAGE < b.PRESSAVERAGE;
            }

            return R2 > b.R2;
        }
        bool operator<(const  Stat b)const
        {
            if(R2 == b.R2 )
            {
                return PRESSAVERAGE > b.PRESSAVERAGE;
            }

            return R2 < b.R2;
        }
        bool operator==(const  Stat b)const
        {
            if(R2 == b.R2 && PRESSAVERAGE == b.PRESSAVERAGE && variableStart == b.variableStart && variableEnd == b.variableEnd && RMSEAVERAGE == b.RMSEAVERAGE)
            {
                return true;
            }
            else
            {
                 return  false;
            }
        }

    };
   /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   /// \brief The ValidationModel struct
   ///
   struct ValidationModel
   {
       Stat ModelCrossValidation;
       int PCANumber;
       mat Factors;
       mat Scores;
       mat BCofficients;

       bool operator()(const  ValidationModel a,const  ValidationModel b)const
       {
           return a.PCANumber < b.PCANumber;
       }
   };
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \brief The Statistic struct
    ///
   struct Statistic
   {
        Statistic
        (
                int nsamples = 0,int npoints = 0) :
                meanSpectrum(npoints,1), standardDeviationSpectrum(npoints,1),correlationSpectrum(nsamples,npoints)
        {
                Clear();
        }
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief print
        /// \param value
        ///
        void print(string value = "")
        {
            cout << "###################################################     "<<value << "     ################################################"<<endl;

            cout << "Mean Spectra for population of calibration spectra = " << endl;
            for(int i =0;i < (int)meanSpectrum.n_cols;i++)
            {
                cout << std::setprecision(2)<<std::setw(4 )<< meanSpectrum(0,i)<<" ";
            }
            cout << endl;
            cout << "Standard Deviation Spectra for population of calibration spectra = " << endl;

            for(int i =0;i < (int)standardDeviationSpectrum.n_cols;i++)
            {
                cout << std::setprecision(2)<<std::setw(4) << standardDeviationSpectrum(0,i)<<" ";
            }
            cout << endl;

            correlationSpectrum.print("Correlation Spectra for population of calibration spectra");
            covarienceMatrixSpectrum.print("Covarience Spectra for population of calibration spectra");
            cout << "X*X' ="<<endl;
            cout << currentPopulationMatrix * currentPopulationMatrix.t() << endl;
            cout << "###################################################     "<<value << "     ################################################"<<endl;
        }
        ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief DisplayPopulationMatrix
        ///
        void  DisplayPopulationMatrix()
        {
           currentPopulationMatrix.print("currentPopulationMatrix=");

        }
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief mean
        ///
        void mean()
        {
              meanSpectrum =  currentPopulationOfSamples.mean();

              //meanSpectrum.print("meanSpectrum=");
              meanConcentrations = currentPopulationOfConcentrations.mean();

        }
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief stddev
        ///
        void stddev()
        {
               standardDeviationSpectrum =   currentPopulationOfSamples.stddev();

               if(standardDeviationSpectrum.n_rows == 0 )
               {
                   mat mean =  currentPopulationOfSamples.mean();
                   standardDeviationSpectrum = mat(size(mean));
                   standardDeviationSpectrum.zeros();
               }

        }
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief corelationMatrix
        ///
        void corelationMatrix()
        {
            correlationSpectrum = cor(currentPopulationMatrix);

        }
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief covarienceMatrix
        ///
        void covarienceMatrix()
        {
            covarienceMatrixSpectrum = cov(currentPopulationMatrix);

        }
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief substractmean
        /// \return
        ///
        pair<mat,mat> substractmean()
        {
            pair<mat,mat> result;
            result.first = currentPopulationMatrix;
            if(result.first.n_rows > 1 && result.first.n_cols > 0 && meanSpectrum.n_elem > 0)
            {
                for(int i = 0;i < (int)result.first.n_rows;i++)
                {
                     result.first.row(i)  = result.first.row(i) - meanSpectrum.row(0);
                }
            }
            result.second = currentConcentrationMatrix;
            if(result.second.n_cols > 1 && meanConcentrations.n_elem > 0)
            {
                colvec concentrationsmean  = conv_to< colvec >::from(meanConcentrations.row(0));
                for(int i=0;i<(int)result.second.n_cols;i++)
                {
                    result.second.col(i) = result.second.col(i) - concentrationsmean;
                }
            }

            return result;
        }
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        std::function<void(Statistic &,const  Statistic &)> NipalsFunction = [](Statistic& stat,const  Statistic & calib_stat)->void
        {
            if(stat.currentConcentrationMatrix.n_elem == 0 || stat.currentPopulationMatrix.n_elem == 0)
            {
                cout << "Error PopulationMatrix Or Concentration Matrix are empty exiting the program."<<endl;
                return;
            }
            //cout << " Start Nipals Algorithm " << endl;
            double d0,d;


            vector<int> lengthdata = {(int)stat.currentPopulationMatrix.n_cols,stat.numberOfPcaComponents};
            stat.numberOfPcaComponents = *std::min_element(lengthdata.begin(),lengthdata.end());

            stat.ClearStatistics(stat);

            mat concentrations = mat(stat.currentConcentrationMatrix);
            concentrations.zeros();
            int conscollen = min(stat.currentConcentrationMatrix.n_cols-1,calib_stat.currentConcentrationMatrix.n_cols - 1);
            concentrations.cols(0,conscollen) = calib_stat.currentConcentrationMatrix.cols(0,conscollen);

            for(int x=0; x < (int)stat.numberOfPcaComponents;x++)
            {
                mat E = stat.currentPopulationMatrix.cols(0, x );

                mat ORIG = E;

                mat T(E.n_rows, x + 1);

                mat P( x + 1,E.n_cols);

                T.zeros();
                P.zeros();

                //stat.RunNipalsLoopAlg1(T,P,E,d0,d,x);
                stat.RunNipalsLoopAlg2(T,P,E,d0,d,x );
                // Eigenvectors is a rows : A * F.t() = S
                stat.F_pcaFactors.push_back(P);

                stat.S_pcaScores.push_back(T);
                //stat.PCA.push_back( (ORIG * stat.F_pcaFactors[x].t()).t());
                stat.PCA.push_back(ORIG * stat.F_pcaFactors[x].t());
                //ORIG.print("O=");
               // (T * P.t()).print("T * P.t()=");
               // (T * P).print("T * P=");

                stat.newcurrentPopulationMatrix.push_back(stat.S_pcaScores[x] * stat.F_pcaFactors[x]);

                stat.eigenvectorValues.push_back(stat.CalculateEigenValues(stat.S_pcaScores[x]));

                 mat temp1 = mat(size(stat.currentPopulationMatrix) );
                 temp1.zeros();
                 temp1.cols(0,x) = stat.newcurrentPopulationMatrix[x].cols(0,x );
                 stat.Ea_error.push_back(stat.currentPopulationMatrix - temp1); // it is the same as E = currentPopulationMatrix - newcurrentPopulationMatrix

                 Stat errors;

                 errors = errors.CalculateErrors( temp1,stat.currentPopulationMatrix,x + 1,x+1);
                 stat.errrorsStat.push_back(errors);


                 stat.m_OptimizationParameters.push_back(stat.CalculateOptimizationParameters(stat,x));
                 stat.Concentration_WithUnknown.push_back(concentrations);
                // stat.ParamPrint(x ,NIPALS_ALGORITHM);
                // stat.printsomedata(stat,x,ORIG);
                // cout << endl;
            }

            stat.CalculateTPV(stat);
            stat.CalculateMalinovskiIndicator(stat);

            //cout << " Finish Nipals Algorithm " << endl;
        };
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief RunNipalsLoopAlg1
        /// \param T
        /// \param P
        /// \param E
        /// \param d0
        /// \param d
        /// \param currentMaxPCAIndex
        ///
       void RunNipalsLoopAlg1(mat &T, mat &P, mat &E ,double &d0,double &d,int currentMaxPCAIndex)
       {
           int x = currentMaxPCAIndex;
           int f=0;
           for( f = 0; f <  x + 1; f++)
           {
              // stat.RunNipalsLoopAlg1(T,P,E,d0,d,x,f);
              // stat.RunNipalsLoopAlg2(T,P,E,d0,d,x,f);

               mat t(E.n_rows,1);

               mat p(1,E.n_cols);
               mat z;

               int index = rand() % ( x + 1 ) + 1;
               if(index > (int)E.n_cols-1)
                   index = (int)E.n_cols-1;
               t.col(0) = E.col(index);


               do
               {
                   p = E.t() * t;
                   z = ( t.t() * t);
                   d0 = z(0,0);
                   p = p / d0;
                   //p = p * pow(p.t() * p,0.5);
                   p = p / norm(p,"fro");

                   t = E * p;
                   z = (p.t() * p);
                   t = t / z(0,0);
                   t=t / norm(t,"fro");
                  // t = t * pow(t.t() * t,0.5);
                   z = t.t() * t;
                   d = z(0,0);


               }
               while(abs(d - d0) > CONVERGENCE_DISTANCE);

               // next PCA

               E = E - (t * p.t());

              // T.print("T=");
               P.print("P=");
              // t.print("t" + to_string(f));
               p.t().print("p " + to_string(f));

               P.row(f) = p.t();
               T.col(f) = t;
           }


       }
       ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
       /// \brief RunNipalsLoopAlg2
       /// \param T
       /// \param P
       /// \param E
       /// \param d0
       /// \param d
       /// \param currentMaxPCAIndex
       ///
       void RunNipalsLoopAlg2(mat &T, mat &P, mat &E ,double &d0,double &d,int currentMaxPCAIndex)
       {
           mat Orig = E;
           int x = currentMaxPCAIndex;
           int f=0;
           for( f = 0; f <  x + 1; f++)
           {
               mat t((int)E.n_rows,1);

               mat p(1,(int)E.n_cols);

               mat z;
               //choose the index of the column to select the population

               int  index = rand() % ( x + 1 ) + 1;
               if(index >(int) E.n_cols-1)
                      index = (int)E.n_cols-1;
               t.col(0) = E.col(index);
               int count =0;
               do
                {
                        p = pinv( t.t() * t ) * t.t() * E;
                        p = p.t();
                        //p =  p * pow(p.t() * p,-0.5);
                        p = p / norm(p,"fro");
                        z = t.t() * t;
                        d0=z(0,0);
                        t = E * p * pinv(p.t() * p);
                        //t = t / norm(p,"fro");
                        // t =  t * pow(t.t() * t,-0.5);
                        z = t.t() * t;
                        d = z(0,0);
                        count++;

                }while(abs(d - d0) > 0.0000001 && count <= MAX_LOOP_VALUE);

                   // next PCA

                   E = E - (t * p.t());
                  //t.print("t   x=" + to_string(x) + "   f= "+ to_string(f));
                 // p.print("p   x=" + to_string(x) + "   f="+ to_string(f));
                 // P.row(f).print("P=");
                  P.row(f) = p.t();
                  T.col(f) = t;

           }
          // T.print("T=");
          // P.print("P=");
          // (T * P).print("T * P =");

          // cout << endl;

       }
        void printsomedata(Statistic& stat,int npca,mat Orig ,bool end = false)
        {
              // cout << "Number Of PCA = "<< npca + 1 << endl;
              // stat.Ea_error[npca].print("ea=");
              // stat.Concentration_WithUnknown[npca].print("Concentration = ");

               stat.F_pcaFactors[npca].print("F=");

              // stat.S_pcaScores[npca].print("S=");
              // stat.PCA[npca].print("PCA=");
               if(end)
                  stat.B_calibrationCofficients[npca].print("B=");


               //(stat.newcurrentPopulationMatrix[npca]).print("S*F = " );
              // Orig.print("Orig=");

        };
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief CalculateEigenValues
        /// \param score
        /// \return
        ///
        mat CalculateEigenValues(mat score)
        {
            mat eigenvectorValues = mat((int)score.n_cols,(int)score.n_cols);

            eigenvectorValues.zeros();
            int count =0;
            for(int j=0;j < (int)score.n_cols;j++)
             {
                double sum = 0.0;
                for(int i = 0;i < (int)score.n_rows;i++)
                {
                        sum = sum + pow(score(i,j),2);

                }
                sum = pow(sum,0.5);
                eigenvectorValues(count,count) = pow(sum,0.5);
                count++;

             }
            return eigenvectorValues;
        }
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        std::function<void(Statistic &,const Statistic &)> LibpcaAlgorithm = [](Statistic& stat,const Statistic & calib_stat)->void
        {
                    if(stat.currentConcentrationMatrix.n_elem == 0 || stat.currentPopulationMatrix.n_elem == 0)
                    {
                        cout << "Error PopulationMatrix Or Concentration Matrix are empty exiting the program."<<endl;
                        return;
                    }
                    cout << " Start Armadillo Library PCA  Algorithm " << endl;
                    vector<int> lengthdata = {(int)stat.currentPopulationMatrix.n_cols,stat.numberOfPcaComponents};
                    stat.numberOfPcaComponents = *std::min_element(lengthdata.begin(),lengthdata.end());

                    stat.ClearStatistics(stat);

                    mat Fi;
                    mat Si;
                    vec Evalues;
                    vec Ea;
                    int f=0;
                    stat.errrorsStat.clear();
                    stat.m_OptimizationParameters.clear();

                    mat concentrations = mat(stat.currentConcentrationMatrix);
                    concentrations.zeros();
                    int conscollen = min(stat.currentConcentrationMatrix.n_cols-1,calib_stat.currentConcentrationMatrix.n_cols - 1);
                    concentrations.cols(0,conscollen) = calib_stat.currentConcentrationMatrix.cols(0,conscollen);


                    for( f = 0;f <  stat.numberOfPcaComponents; f++)
                    {
                        mat E = stat.currentPopulationMatrix.cols(0,f );

                        princomp(Fi, Si, Evalues, Ea, E);

                        stat.S_pcaScores.push_back(Si);
                        stat.F_pcaFactors.push_back(Fi.t());

                        stat.PCA.push_back(  E * stat.F_pcaFactors[f].t());

                        stat.newcurrentPopulationMatrix.push_back( stat.S_pcaScores[f] * stat.F_pcaFactors[f]) ;

                        mat temp1 = mat(size(stat.currentPopulationMatrix));
                        temp1.zeros();
                        temp1.cols(0,f) = stat.newcurrentPopulationMatrix[f].cols(0,f);
                        stat.Ea_error.push_back(stat.currentPopulationMatrix - temp1); // it is the same as E = currentPopulationMatrix - newcurrentPopulationMatrix

                        stat.eigenvectorValues.push_back(Evalues);

                        Stat errors;
                        errors = errors.CalculateErrors( temp1,stat.currentPopulationMatrix,f + 1,f+1);
                        stat.errrorsStat.push_back(errors);

                        stat.m_OptimizationParameters.push_back(stat.CalculateOptimizationParameters(stat,f));

                        stat.Concentration_WithUnknown.push_back(concentrations);
                        stat.printsomedata(stat,f,E);
                    }

                    stat.CalculateTPV(stat);
                    stat.CalculateMalinovskiIndicator(stat);

                    cout << " Finish Start Armadillo Library PCA  Algorithm " << endl;

        };
        ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        std::function<void(Statistic &,const Statistic &)> DecompozitionOfVarCovMatAlgorithm = [](Statistic& stat,const Statistic & calib_stat)->void
        {
            stat.errrorsStat.clear();
            stat.m_OptimizationParameters.clear();
            stat.eigenvectorValues.clear();
            stat.F_pcaFactors.clear();
            stat.S_pcaScores.clear();
            stat.newcurrentPopulationMatrix.clear();

            mat Z = stat.currentPopulationMatrix * stat.currentPopulationMatrix.t();

            mat E = Z;
            mat Eprevious;
            mat z;

            mat t(size(E));
            t.ones();

            t = 0.1 * t;
            int f=0;

            mat told;
            bool nextv = true;
            for( f = 0;f < (int)E.n_cols ; f++)
            {
                do
                {
                    told = t;
                    t = E * t.t();

                    t=t / norm(t,"fro");
                    mat r = 10000 *(abs(t)-abs(told));
                    nextv = true;
                    for(int i =0;i< (int)r.n_rows;i++)
                    {
                        for(int j=0;j< (int)r.n_cols;j++)
                        {
                            bool check = ((int)abs(r(i,j))  > 5) ;

                            if (check )
                                nextv=false;

                        }
                    }
                   // t.print("t=");
                   // told.print("told=");
                   //cout  << endl;

                }
                while(!nextv  );
                Eprevious = E;
                E = E - (t * t.t());

                mat eigvec1 = t.t() * Z;
                mat Xnew = t * eigvec1.t();// + E;
                //Xnew.print("Xnew=");
               // Z.print("Z=");

                stat.S_pcaScores.push_back(t);
                stat.F_pcaFactors.push_back(eigvec1);
                stat.Ea_error.push_back(E);
                stat.newcurrentPopulationMatrix.push_back( Xnew);

                Stat errors;
                mat ZERO = mat(size(E));
                ZERO.zeros();
                errors.CalculateErrors(ZERO,E,f + 1,f+1);

                stat.errrorsStat.push_back(errors);

                mat eigenvectorValues = mat((int)stat.S_pcaScores[f].n_cols,(int)stat.S_pcaScores[f].n_cols);

                eigenvectorValues.zeros();
                int count =0;
                for(int j=0;j < (int)stat.S_pcaScores[f].n_rows;j++)
                 {
                    double sum = 0.0;
                    for(int i = 0;i < (int)stat.S_pcaScores[f].n_cols;i++)
                    {
                            sum = sum + pow(stat.S_pcaScores[f](j,i),2);

                    }
                    sum = pow(sum,0.5);
                    eigenvectorValues(count,count) = pow(sum,0.5);
                    count++;

                 }
                 stat.eigenvectorValues.push_back(eigenvectorValues);

            }
        };
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief ParamPrint
        /// \param nPCAComponents
        /// \param type
        ///
        void ParamPrint(int nPCAComponents,AlgorithmType type)
        {
            //mat Z = currentPopulationMatrix * currentPopulationMatrix.t();
           // Z.print("Original CovarienceMatrix = ");
           for(int i=0;i < nPCAComponents && i < numberOfPcaComponents;i++)
           // if(nPCAComponents < numberOfPcaComponents)
            {
                PCA[i].print("PCA "+ to_string(i));
                // currentPopulationMatrix.cols(0,i).print("currentPopulationMatrix =");
                // Ea_error[i].print("Ea_error");
                // S_pcaScores[i].print("S_pcaScores =");
                // F_pcaFactors[i].print("F_pcaFactors =");
                // (currentPopulationMatrix.cols(0,i) * F_pcaFactors[i]).print("SCORES 1=");


                 //newcurrentPopulationMatrix[i].print("Error After PCA Finished =");
                // eigenvectorValues[i].print("Eigen Values = ");
                 if(type ==  LIBPCA)
                 {
                   // TsquareOfLibAlgorithm[i].print("TsquareOfLibAlgorithm = ");
                 }
                // errrorsStat[i].print();
            }
            cout <<endl;
        }
        void ReconstituteSPectrum(Statistic  stat)
        {
              mat C = stat.currentConcentrationMatrix.t();

              vector<mat> SumForNPCA;
              vector<mat> ResidualSpectra;
              for(int i=0;i < (int)stat.PCA.size();i++)
              {

                  mat F = stat.F_pcaFactors[i];
                  mat B = stat.B_calibrationCofficients[i];
                  if((int)C.n_cols - 1 < i)
                  {
                      colvec col = (colvec(C.n_rows)).zeros();
                      addcol(C,col);
                  }
                  //C.print("C=");
                  mat Spectra = C * F.t() * B;
                  //Spectra.print("Spectra=");
                 // stat.B_calibrationCofficients[i].print("B=");
                  // PCA[i].print("PCA "+ to_string(i));
                  //mat Sum=mat((int)stat.currentPopulationMatrix.n_rows,(int)stat.currentPopulationMatrix.n_cols(0,i));
                 // Sum.zeros();
                 // for(int a =0;a < (int)stat.PCA[i].n_rows;a++)
                 //(stat.S_pcaScores[i] * stat.F_pcaFactors[i]).print("S * F");
                 // stat.S_pcaScores[i].print("S=");
                 //(stat.currentPopulationMatrix.cols(0,i) * stat.F_pcaFactors[i].t()).print("A * F'=");

                  //ResidualSpectra.push_back(());
                 //cout << endl;
              }
              // stat.currentPopulationMatrix.print("Current Polulation Matrix = ");
              //cout << endl;
        }
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief addcol
        /// \param x
        /// \param value
        ///
        static void addcol(mat &x,colvec value)
        {
            mat temp = mat(x.n_rows,x.n_cols + 1);
            temp.zeros();
            temp.cols(0,x.n_cols -1) = x;
            if(value.n_rows == temp.n_rows)
            {
               temp.col(x.n_cols) = value;
            }
            x = temp;
        }
        /*void deleterow(mat &x,int index)
        {
            if(x.n_rows > 0)
            {
                mat temp = mat(x.n_rows - 1,x.n_cols);
                temp.zeros();
                temp.rows(0,x.n_rows-1) = x;

            }
        }*/

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief convToStd
        /// \param rowvector
        /// \return
        ///
        static vector<double> convToStd(rowvec rowvector)
        {
            vector<double> result;
            for(int i = 0;i<(int)rowvector.size();i++)
            {
                result.push_back(rowvector(i));
            }
            return result;
        }
        ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief addrow
        /// \param x
        /// \param value
        ///
        static void addrow( mat &x,rowvec value,int sameNumberOfCols=1)
        {
           // x.print("Before=");
            int cols;
            if(x.n_rows <= 0)
            {
                cols = (int) value.n_cols;
            }
            else
            {
              if(sameNumberOfCols == 0)
              {
                cols = max((int) x.n_cols,(int)value.n_cols);
              }
              else
              {
                   cols = (int) x.n_cols;
              }
            }


            mat temp = mat(x.n_rows + 1,cols);
            temp.zeros();
            if(x.n_elem > 0)
            {
                temp.rows(0,(int)x.n_rows-1) = x.rows(0,(int)x.n_rows-1);
            }
            temp.row((int)x.n_rows) = value;

            x = temp;
           // x.print("After=");

        }
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief deleterow
        /// \param x
        /// \param index
        ///
        mat deleterow(const mat& x,int index)
        {
            if((int)x.n_rows >= 0 && index < (int)x.n_rows)
            {
                mat temp = mat((int)x.n_rows - 1,(int)x.n_cols);
                temp.zeros();
                if(index != 0)
                {
                   temp.rows(0,index -1) = x.rows(0,index - 1);
                }
                if(index < (int)x.n_rows - 1)
                {
                   temp.rows(index,(int)temp.n_rows - 1) = x.rows(index + 1,(int)x.n_rows - 1);
                }
                return temp;
            }
        }
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief deleterow
        /// \param x
        /// \param index
        ///
        mat deleterows(const mat& x,int start,int end )
        {
            mat temp;
            if((int)x.n_rows > 0 && start >= 0 && start < end && (end-start) <= (int)x.n_rows)
            {
                temp = mat((int)x.n_rows - (end-start),(int)x.n_cols);
                temp.zeros();
                if(start != 0)
                {
                   temp.rows(0,start -1) = x.rows(0,start - 1);
                }
                if(end < (int)x.n_rows - 1)
                {
                   temp.rows(start,(int)temp.n_rows - 1) = x.rows(end ,(int)x.n_rows - 1);
                }

            }
            return temp;
        }
        void ClearStatistics(Statistic & stat)
        {
            stat.errrorsStat.clear();
            stat.m_OptimizationParameters.clear();
            stat.eigenvectorValues.clear();
            stat.F_pcaFactors.clear();
            stat.S_pcaScores.clear();
            stat.Ea_error.clear();
            stat.newcurrentPopulationMatrix.clear();
            stat.Concentration_WithUnknown.clear();

            stat.B_calibrationCofficients.clear();
            stat.CalibrationStat.clear();
            stat.PCA.clear();
            stat.C_RecreatedConcentrations.clear();
            stat.m_bestFitCalibration.clear();

        }

        vector<Optimization> EvaluatePCADecompozitionModels(const vector<Optimization> &parameters )
        {
            vector<Optimization> optimalPCA =  parameters;
            if(parameters.size() > 0)
            {
                 std::sort(optimalPCA.begin(),optimalPCA.end(),optimalPCA[0]);
            }

            return optimalPCA;
        }
        void PrintEvaluatedPCADecompozitionModels(const vector<Optimization> &parameters)
        {

            for(auto param : parameters)
            {
                param.print();
            }

        }
        //finds percentage of models with lowest CV
        vector<Stat> sortCalibrationModels(vector<Stat> statParameters )
        {
                vector<Stat> optimalPCA =  statParameters;
                if(statParameters.size() > 0)
                {
                     std::sort(optimalPCA.begin(),optimalPCA.end(),optimalPCA[0]);
                }
                /*int numberToSelect = std::max(PERCENTAGE_TO_SELECT_BESTMODEL * (int)optimalPCA.size() / 100,1.00);
                while((int)optimalPCA.size() > numberToSelect)
                {
                    optimalPCA.pop_back();
                }*/
                return optimalPCA;
        }
        void ErrorsPrint(vector<Stat> stat)
        {

            for(auto error : stat)
            {
                error.print();
            }

        }
        void printPCAModels(vector<Stat> models)
        {
            cout << "###########       Models based on PCA number =             ###########"<< endl;
            if(models.size() > 0)
            {
                models[0].print(true,false);
            }
            /*for(auto model : models)
            {
                model.print(true,true);
            }*/
        }

        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief step2PCR
        /// \param B_calibration_coefficients_include_residualError
        /// \param Score_with_Residual
        /// \param concentrationMatrix
        ///
        void step2PCR(mat & B_calibration_coefficients,const mat & Score,const mat &concentrationMatrix)
        {
               mat B0;
              // mat S = Score.cols(Score.n_cols - 1,Score.n_cols - 1);
               mat c0 = concentrationMatrix.t();
              // colvec d0 = c0.col(1);
               try
               {
                    B0 = Score.t() * pinv(Score * Score.t());

               }
               catch(std::exception& e)
               {
                   cout << e.what()<< endl;
               }
               B0.print("B0=");
               B0 = B0 * c0;
                B0.print("B0=");
              // (B0 * c0.cols(0,c0.n_cols - 1)).print("CCol 0=");
               (Score * B0.cols(0,B0.n_cols -2)).print("Score * B00 =");
               (Score * B0.cols(B0.n_cols - 1,B0.n_cols - 1)).print("Score * B00 =");

               (concentrationMatrix.t()).print("C=");
              // S.cols(SS.cols(0,SS.n_cols - 2) *
              // (  B0.t() * (SS.cols(0,SS.n_cols - 2))).print("Score * B00 =");
              // (  B0.t() * (SS.cols(SS.n_cols - 1,SS.n_cols - 1))).print("Score * B00 =");

               B_calibration_coefficients.print("Bbefore=");
               B0.print("B0=");
               B_calibration_coefficients = B0.cols(0,B0.n_cols - 2);
               (Score *  B_calibration_coefficients).print("CR=");
                (concentrationMatrix.t()).print("C=");
                B_calibration_coefficients.print("Bafter=");
               cout << endl;

        }

        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief step2PCR
        /// \param models
        /// This Function calculates Calibration coefficients from step Multivarieted Calibrattion = PCR regression step
        void step2PCR(vector<Stat> models,Statistic &cur_statistic)
        {
            if(cur_statistic.currentConcentrationMatrix.n_elem < 0)
                return;
           mat C = cur_statistic.currentConcentrationMatrix.t();
           for(auto model : models)
           {
                   int npca = model.getIndex() - 1;

                  //  m_Cconstitute[f x n] * m_Sscore[n x f] * (m_Sscore'[f x n] * m_Sscore[n x f)-1 = [f x f]  -> Multi

                  //  m_Cconstitute[f x 1] * m_Sscore[1 x f] * (m_Sscore'[f x 1] * m_Sscore[1 x f)-1 = [f x f]  -> Uni
                  //  currentConcentrationMatrix(0,N_Sample) =  HC ->  B_calibrationCofficients(0,N_Sample)
                  //  currentConcentrationMatrix(1,N_Sample) =  NO ->  B_calibrationCofficients(1,N_Sample)
                  mat B0,B1,B,BB;
                  mat F = cur_statistic.F_pcaFactors[npca];

                  mat S = cur_statistic.S_pcaScores[npca];

                  mat A = cur_statistic.currentPopulationMatrix.cols(0,npca);

                  mat L = cur_statistic.eigenvectorValues[npca];
                  mat newA = cur_statistic.newcurrentPopulationMatrix[npca];

                  try
                  {
                       B0 = pinv(S * S.t());
                  }
                  catch(std::exception& e)
                  {
                       cout << e.what()<< endl;
                       cur_statistic.S_pcaScores[npca] = S;
                       cur_statistic.B_calibrationCofficients.push_back(mat(0,0));
                       return;
                  }

                  B = S.t() * B0 * C ;


                  cur_statistic.S_pcaScores[npca] = S;
                  cur_statistic.B_calibrationCofficients.push_back(B);
                 // (A * F.t() * B).print("C1=");
                 // (A * F.t() * BB).print("C2=");
                 // C.print("C=");
                 //cur_statistic.Ev_validationError.push_back(C - S * B);
                 //printsomedata(cur_statistic,npca,A,true);
           }

        }

        map<int,map<Constituents,mat>>  seperateSpectra(vector<Stat> models,Statistic &cur_statistic)
        {
            map<int,map<Constituents,mat>> contituteSpectors;
            for(auto model : models)
            {
                map<Constituents,mat> contituteSpectorsForCurrentPCA;
                int index = model.getIndex() - 1;
                mat tempcons =  cur_statistic.Concentration_WithUnknown[index].t();
                mat zerocons(size(tempcons));
                zerocons.zeros();
                mat spectraProjections;
                try
                {
                    mat tempspectra = cur_statistic.F_pcaFactors[index].t() * cur_statistic.B_calibrationCofficients[index];

                    spectraProjections = pinv(tempspectra);

                    bool validvalue = true;

                     for(int a = 0;a < (int)spectraProjections.n_rows;a++)
                     {
                         for(int b = 0; b < (int)spectraProjections.n_cols;b++)
                         {
                             if(spectraProjections(a,b)  == INFINITY)
                             {
                                  spectraProjections.ones();
                                  spectraProjections = spectraProjections * INFINITY0;
                                  validvalue = false;

                                  break;
                             }
                         }
                         if(!validvalue)
                             break;
                     }


                    mat sum= mat(size(cur_statistic.newcurrentPopulationMatrix[index]));
                    sum.zeros();
                    vector<Constituents> keys = mapGetKeys(cur_statistic.m_ConstituesIndexMap);
                    int len = std::min((int)keys.size() -1 ,(int)tempcons.n_cols);
                    for(int i =0;i < len;i++ )
                    {
                            mat temp = (tempcons).cols(i,i) * spectraProjections.rows(i,i);
                            contituteSpectorsForCurrentPCA[keys[i]] = temp;

                            for(int a=0;a<(int)temp.n_cols;a++)
                            {
                                sum.cols(a,a) = sum.cols(a,a) + temp.cols(a,a);
                            }

                    }
                    // sum.print("sum=");
                   // cur_statistic.newcurrentPopulationMatrix[index].print("NEwA="+ to_string(index));
                    bool same = approx_equal(sum, cur_statistic.newcurrentPopulationMatrix[index], "absdiff", 0.001);
                    if(!same)
                    {
                        //cur_statistic.newcurrentPopulationMatrix[index].print("NEwA="+ to_string(index));
                         mat tempa = cur_statistic.newcurrentPopulationMatrix[index] - sum;
                         //tempa.print("Difference="+to_string(index));
                         contituteSpectorsForCurrentPCA[UNKNOWN] = tempa;

                         mat recalculateConcentration( cur_statistic.Concentration_WithUnknown[index].n_rows + 1,cur_statistic.currentConcentrationMatrix.n_cols);
                         recalculateConcentration.zeros();
                         recalculateConcentration.rows(0,cur_statistic.currentConcentrationMatrix.n_rows-1) = cur_statistic.currentConcentrationMatrix.rows(0,cur_statistic.currentConcentrationMatrix.n_rows - 1);

                         mat concentrationofUnknown =   contituteSpectorsForCurrentPCA[UNKNOWN] * spectraProjections.t();
                        // concentrationofUnknown.print("concentration of unknown = ");
                        //  tempspectra.t() = pinv(spectraProjections.t());

                         concentrationofUnknown =  concentrationofUnknown.t();
                         recalculateConcentration.rows(recalculateConcentration.n_rows - 1,recalculateConcentration.n_rows - 1).zeros();

                         for(int i = 0; i< (int)concentrationofUnknown.n_rows;i++)
                         {
                              recalculateConcentration.rows(recalculateConcentration.n_rows - 1,recalculateConcentration.n_rows - 1) =
                              recalculateConcentration.rows(recalculateConcentration.n_rows - 1,recalculateConcentration.n_rows - 1) +
                              concentrationofUnknown.row(i);

                         }

                         cur_statistic.Concentration_WithUnknown[index] = recalculateConcentration;

                         // if concentration of unknown found recalculate B coefficients

                         step2PCR(cur_statistic.B_calibrationCofficients[index],cur_statistic.S_pcaScores[index], cur_statistic.Concentration_WithUnknown[index]);
                        // printsomedata(cur_statistic,index,cur_statistic.Concentration_WithUnknown[index]);

                    }

                    contituteSpectors[index] = contituteSpectorsForCurrentPCA;

                    /*mat sumspectra = cur_statistic.newcurrentPopulationMatrix[index] ;
                    mat sum1= mat(size(sumspectra));
                    sum1.zeros();
                    for(auto cc:  contituteSpectorsForCurrentPCA)
                    {
                        mat temp = contituteSpectorsForCurrentPCA[Constituents(cc.first)] ;

                        sum1 = sum1 + temp;

                    }
                    sum1.print("SUM1=");

                    (cur_statistic.newcurrentPopulationMatrix[index] ).print("Total=");*/
                   /* for(auto constitute : contituteSpectorsForCurrentPCA)
                    {
                        constitute.second.print("PCA Number = " + to_string(index) + " Constitute = " + ConstituentsName.at(constitute.first));
                    }
                    cout << endl;*/
                }
                catch(std::exception)
                {
                    cout << "Inverse matrix does not exist for number of samples = "<<(int)cur_statistic.currentPopulationMatrix.n_rows  << " <<< "<<
                         " number of variables = " <<  (int)cur_statistic.currentPopulationMatrix.n_cols << endl;
                    cout << "increase number Of Samples at least on << " << (int)cur_statistic.currentPopulationMatrix.n_cols - (int)cur_statistic.currentPopulationMatrix.n_rows;
                }
            }

            return contituteSpectors;

        }
        void printSeperatedSpectra( map<int,map<Constituents,mat>>  spectra)
        {
            for(auto npcamodel : spectra)
            {
                for(auto constitute : npcamodel.second)
                {
                    constitute.second.print("PCA Number = " + to_string(npcamodel.first ) + " Constitute = " + ConstituentsName.at(constitute.first));
                }
            }
        }


        void printCoefficients(vector<Stat> models,Statistic &cur_statistic)
        {
            for(auto model : models)
            {
                int npca = model.getIndex() - 1;
                cur_statistic.B_calibrationCofficients[npca].print("B_calibrationCofficients");
            }
        }

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief recreateConcentrationMatrix
        /// \param models
        ///
        void Validate( Statistic &cur_statistic, Statistic calib_statistic)
        {

            cur_statistic.CalibrationStat.clear();
            cur_statistic.C_RecreatedConcentrations.clear();
            //cur_statistic.Ev_validationError.clear();
            for(auto model : calib_statistic.errrorsStat)
            {
                int index = model.getIndex() - 1;
                int npca  = model.getPCANumber() -1;

                // Calculate Calibration Error  ECal = abs(Cnew - CActual)
                // C is matrix [f x n]
                //                                           [f x f] * [f * n]             [f x f] * [f * n]   = [f x f]  * ([n x f] * [f x f])   =
                //  C[f x n]   = B_calibrationCofficients[npca ] * S_pcaScores[npca].t()  = B      * S'        =    B     * (   A    *    F'  )'  =
                // [f x f] * (f x n)  =  [f x f]
                //   B     * (     )  =     B     * ((S * F + newcurrentPopulationMatrix[npca]) * F')'// +  ErrorEC
                // [n x f]
                //recreatedConcentrations = S_pcaScores[npca] * F_pcaFactors[npca] + newcurrentPopulationMatrix[npca];
                // [n x f]
                //
                // use intensity matrix from PCA decomposition
                //recreatedConcentrations = recreatedConcentrations * F_pcaFactors[nbestpca];
                // [f x n]              =            [f x f]                  *                                     [n x f]'
                //recreatedConcentrations = B_calibrationCofficients[npca ] *((S_pcaScores [npca] * F_pcaFactors[npca] + Ea_error[npca]) * F_pcaFactors[npca].t()  ).t();

                // or use original intersity matrix
                //HC  index 0 corresponds to row 0 of B_calibrationCofficients[npca ] - > Concentrations of HC
                //NO  index 1 corresponds to row 1 of B_calibrationCofficients[npca ]
                //NO2 index 2 corresponds to row 2 of B_calibrationCofficients[npca ]
                //N2O index 3 corresponds to row 3 of B_calibrationCofficients[npca ]
                //NH3 index 4 corresponds to row 4 of B_calibrationCofficients[npca ]
                //SO2 index 5 corresponds to row 5 of B_calibrationCofficients[npca ]
                //O3  index 6 corresponds to row 6 of B_calibrationCofficients[npca ]

                mat A;

                mat recreatedConcentrations;
                mat originalConcentrations = cur_statistic.Concentration_WithUnknown[index].t();

                A = cur_statistic.currentPopulationMatrix.cols(0,index) ;

                cur_statistic.C_RecreatedConcentrations.push_back(((A * calib_statistic.F_pcaFactors[index].t()) * calib_statistic.B_calibrationCofficients[index]).t());
                Stat errors;
                errors = errors.CalculateErrors(cur_statistic.C_RecreatedConcentrations[index].t(),originalConcentrations,index,npca);
                cur_statistic.CalibrationStat.push_back(errors);
            }
        }
       /* void Validate()
        {

            cur_statistic.CalibrationStat.clear();
            cur_statistic.C_RecreatedConcentrations.clear();

            for(auto model : calib_statistic.errrorsStat)
            {
                int index = model.getIndex() - 1;
                int npca  = model.getPCANumber() -1;

                mat A;

                mat recreatedConcentrations;
                mat originalConcentrations = cur_statistic.Concentration_WithUnknown[index].t();


                A = cur_statistic.currentPopulationMatrix.cols(0,index) ;


                cur_statistic.C_RecreatedConcentrations.push_back(((A * calib_statistic.F_pcaFactors[index].t()) * calib_statistic.B_calibrationCofficients[index]).t());
                Stat errors;

                errors = errors.CalculateErrors(cur_statistic.C_RecreatedConcentrations[index].t(),originalConcentrations,index,npca);
                cur_statistic.CalibrationStat.push_back(errors);
            }
        }*/

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief CrossValidateSample
        /// \param cur_statistic
        /// \param calib_statistic
        /// \param sample
        /// \param number
        /// \param start
        /// \param end
        /// \param calculateresidual
        ///
        void CrossValidateSample(Statistic &cur_statistic,  Statistic &calib_statistic,mat sample,mat sampleTest,int number,int start,int end,bool calculateresidual = false)
        {
            if(number < (int)cur_statistic.m_CrossValidation.size())
            {
                cur_statistic.CalibrationStat.clear();
                cur_statistic.C_RecreatedConcentrations.clear();
                cur_statistic.m_bestFitCalibration.clear();

                mat originalConcentrations = cur_statistic.currentConcentrationMatrix.t();
                mat concentrKFold = originalConcentrations.rows(start,end - 1);

                if(!(end <= (int)cur_statistic.currentConcentrationMatrix.n_cols + 1))
                    return;
                if(end - start < (int)cur_statistic.currentConcentrationMatrix.n_cols && end <= (int)cur_statistic.currentConcentrationMatrix.n_cols && start >=0)
                {
                   originalConcentrations = deleterows(cur_statistic.currentConcentrationMatrix.t(),start,end);
                }
                if(originalConcentrations.n_elem <= 0)
                    return;
                calib_statistic.currentPopulationMatrix = sample;
                calib_statistic.currentConcentrationMatrix =  originalConcentrations.t();
                calib_statistic.NipalsFunction(calib_statistic,calib_statistic);
                calib_statistic.step2PCR(calib_statistic.errrorsStat,calib_statistic);

                for(auto model : calib_statistic.errrorsStat)
                {
                    int index = model.getIndex() - 1;
                    int npca  = model.getPCANumber() -1;
                    if(index < (int)cur_statistic.Concentration_WithUnknown.size() && index < (int)cur_statistic.currentPopulationMatrix.n_cols)
                    {

                        originalConcentrations = concentrKFold;

                        if(start >= 0 && start < end )
                        {
                            mat A = sampleTest.cols(0,index) ;
                            //printsomedata(calib_statistic,npca,A,true);

                            cur_statistic.C_RecreatedConcentrations.push_back(((A * calib_statistic.F_pcaFactors[index].t()) * calib_statistic.B_calibrationCofficients[index]).t());

                            Stat errors;

                            errors = errors.CalculateErrors(cur_statistic.C_RecreatedConcentrations[index].t(),originalConcentrations,index,npca,number,start, end);
                            mat temp = calib_statistic.F_pcaFactors[index].t();
                            errors.ResidualSpectra = (originalConcentrations - cur_statistic.C_RecreatedConcentrations[index].t()) * pinv(calib_statistic.B_calibrationCofficients[index]) * pinv(temp);
                            errors.ResidualConcentration = ((errors.ResidualSpectra * calib_statistic.F_pcaFactors[index].t()) * calib_statistic.B_calibrationCofficients[index]).t();

                            cur_statistic.CalibrationStat.push_back(errors);
                        }
                    }
                }
                if(cur_statistic.CalibrationStat.size() > 0)
                {
                    cur_statistic.m_bestFitCalibration = cur_statistic.sortCalibrationModels(cur_statistic.CalibrationStat);
                    cur_statistic.m_CrossValidation[number].ModelCrossValidation = *(cur_statistic.m_bestFitCalibration.begin());
                    cur_statistic.m_CrossValidation[number].PCANumber = cur_statistic.m_CrossValidation[number].ModelCrossValidation.getPCANumber();
                    int modelIndex = cur_statistic.m_CrossValidation[number].ModelCrossValidation.getIndex();
                    cur_statistic.m_CrossValidation[number].Factors = calib_statistic.F_pcaFactors[modelIndex];
                    cur_statistic.m_CrossValidation[number].BCofficients = calib_statistic.B_calibrationCofficients[modelIndex];
                    cur_statistic.m_CrossValidation[number].Scores = calib_statistic.S_pcaScores[modelIndex];


                }
            }
        }
        Statistic CreateModel(Statistic &cur_statistic,  Statistic &calib_statistic,mat sample,mat sampleTest,int number,int start,int end)
        {
                Statistic s;
                mat originalConcentrations = cur_statistic.currentConcentrationMatrix.t();
                mat concentrKFold = originalConcentrations.rows(start,end - 1);

                if(!(end <= (int)cur_statistic.currentConcentrationMatrix.n_cols + 1))
                    return s;
                if(end - start < (int)cur_statistic.currentConcentrationMatrix.n_cols && end <= (int)cur_statistic.currentConcentrationMatrix.n_cols && start >=0)
                {
                   originalConcentrations = deleterows(cur_statistic.currentConcentrationMatrix.t(),start,end);
                }
                if(originalConcentrations.n_elem <= 0)
                    return s;

                calib_statistic.currentPopulationMatrix = sample;
                calib_statistic.currentConcentrationMatrix =  originalConcentrations.t();
                s = calib_statistic;
                s.NipalsFunction(s,s);
                s.step2PCR(s.errrorsStat,s);
                return s;

        }
         void CreateKFoldPCAModels(Statistic &cur_statistic,  Statistic& calib_statistic,bool calculateresidual = false,int kfolds = -1,bool validation = true)
         {
             cout << "Start Cross K Fold Validation"  << endl;
             int nsamples = (int)cur_statistic.currentPopulationMatrix.n_rows;
             int delta = nsamples / kfolds;
             if(nsamples % kfolds != 0)
                 delta++;
             vector<Statistic> models;
             for(int i=0;i < kfolds;i++)
             {
                 int start = i * delta;
                 int end = min((int)cur_statistic.currentPopulationMatrix.n_rows , (i + 1) * delta);
                 mat Atest = cur_statistic.currentPopulationMatrix.rows(start,end-1);
                 mat A = cur_statistic.currentPopulationMatrix;
                 if(end <= (int)cur_statistic.currentPopulationMatrix.n_rows )
                 {
                    A = deleterows(cur_statistic.currentPopulationMatrix, start, end);

                    models.push_back(CreateModel(cur_statistic, calib_statistic, A,Atest, i , start,  end));

                 }
             }

             /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
             for(int i=0;i < (int)models.size();i++)
             {
                 models[i].C_RecreatedConcentrations = vector<mat>((int)models[i].errrorsStat.size());
             }
             for(int i=0;i < (int)models.size();i++)
             {
               for(auto pcaStat : models[i].errrorsStat)
               {
                    int index = pcaStat.getIndex() - 1;

                    for(int a=0;a < (int)models.size();a++)
                    {
                        int start = a * delta;
                        int end = min((int)cur_statistic.currentPopulationMatrix.n_rows , (a + 1) * delta);
                        mat Atest = cur_statistic.currentPopulationMatrix.rows(start,end-1);
                        mat A = Atest.cols(0,index) ;

                         mat C = ((A * models[i].F_pcaFactors[index].t()) * models[i].B_calibrationCofficients[index]).t();
                         models[i].C_RecreatedConcentrations[index] = join_rows(models[i].C_RecreatedConcentrations[index],C);
                     }
                }

             }
             ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
              cur_statistic.m_bestFitCalibration.clear();
             for(int i=0;i < (int)models.size();i++)
             {
                 mat originalConcentrations = cur_statistic.currentConcentrationMatrix.t();

                 for(auto pcaStat : models[i].errrorsStat)
                 {
                      int index = pcaStat.getIndex() - 1;
                      int npca  = pcaStat.getPCANumber() -1;
                      Stat errors;

                     errors = errors.CalculateErrors( models[i].C_RecreatedConcentrations[index].t(),originalConcentrations,index,npca,i,0,(int)originalConcentrations.n_rows);
                     mat temp = models[i].F_pcaFactors[index].t();
                     errors.ResidualSpectra = (originalConcentrations - models[i].C_RecreatedConcentrations[index].t()) * pinv(models[i].B_calibrationCofficients[index]) * pinv(temp);
                     errors.ResidualConcentration = ((errors.ResidualSpectra * models[i].F_pcaFactors[index].t()) * models[i].B_calibrationCofficients[index]).t();
                     cur_statistic.m_bestFitCalibration.push_back(errors);
                 }
             }
             models.clear();
             if(cur_statistic.m_bestFitCalibration.size() > 0)
               std::sort(cur_statistic.m_bestFitCalibration.begin(),cur_statistic.m_bestFitCalibration.end(),cur_statistic.m_bestFitCalibration[0]);
             printPCAModels(cur_statistic.m_bestFitCalibration);
             cout << "Finished Create K Fold Models = "   << endl;

         }



        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief CrossValidateKFolds
        /// \param cur_statistic
        /// \param calib_statistic
        /// \param calculateresidual
        /// \param kfolds
        ///
        void CrossValidateKFolds(Statistic &cur_statistic,  Statistic& calib_statistic,bool calculateresidual = false,int kfolds = -1,bool validation = true)
        {
              cout << "Start Cross K Fold Validation"  << endl;
              int nsamples = (int)cur_statistic.currentPopulationMatrix.n_rows;
              int delta = nsamples / kfolds;
              if(nsamples % kfolds != 0)
                  delta++;

              for(int i=0;i < kfolds;i++)
              {
                  int start = i * delta;
                  int end = min((int)cur_statistic.currentPopulationMatrix.n_rows , (i + 1) * delta);
                  mat Atest = cur_statistic.currentPopulationMatrix.rows(start,end-1);
                  mat A = cur_statistic.currentPopulationMatrix;
                  if(end <= (int)cur_statistic.currentPopulationMatrix.n_rows )
                  {
                     A = deleterows(cur_statistic.currentPopulationMatrix, start, end);

                     CrossValidateSample(cur_statistic, calib_statistic, A,Atest, i , start,  end, false);
                  }
              }

               cur_statistic.ClearStatistics(cur_statistic);
               for(auto v: cur_statistic.m_CrossValidation)
               {
                   cur_statistic.m_bestFitCalibration.push_back(v.ModelCrossValidation);
               }
               std::sort(cur_statistic.m_bestFitCalibration.begin(),cur_statistic.m_bestFitCalibration.end(),cur_statistic.m_bestFitCalibration[0]);
               //printBestCrossValidatedModels(cur_statistic);
               printPCAModels(cur_statistic.m_bestFitCalibration);
               cout << "Finished K Fold Cross Validation. Best PCA = "   << endl;

        }
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief ReportConcentrations
        /// \param cur_statistic
        /// \param calib_statistic
        /// \param delta
        /// \param kfolds
        ///
        void ReportConcentrations(Statistic &cur_statistic,const  Statistic & calib_statistic)
        {
            cur_statistic.CalibrationStat.clear();
            cur_statistic.C_RecreatedConcentrations.clear();
            cur_statistic.m_CrossValidation.clear();
            int bestmodel = -1;
            int kfolds = 1;//(int)calib_statistic.m_bestFitCalibration.size();
            for(int a = 0;a < kfolds ;a++)
            {
                if(a < kfolds)
                {
                    bestmodel = calib_statistic.m_bestFitCalibration[a].kfold;
                    cout << "Start report Concentrations. Best K Fold Number =  "<< calib_statistic.m_bestFitCalibration[a].kfold << endl;
                    if(bestmodel < 0 || bestmodel >= (int)calib_statistic.m_CrossValidation.size())
                    {
                        cout << "ERRROR exiting"<< endl;
                        return;
                    }
                }
                else
                {
                    return;
                }

                for(int i=0;i < (int)calib_statistic.m_CrossValidation.size();i++)
                {
                          int modelN;
                          mat error ;


                          modelN = calib_statistic.m_CrossValidation[bestmodel].ModelCrossValidation.getPCANumber();
                          error =  calib_statistic.m_CrossValidation[bestmodel].ModelCrossValidation.ResidualSpectra;

                          int start = calib_statistic.m_CrossValidation[i].ModelCrossValidation.start;
                          int end = min(calib_statistic.m_CrossValidation[i].ModelCrossValidation.end,(int)cur_statistic.currentPopulationMatrix.n_rows);

                          ReportConcentrations(cur_statistic,calib_statistic,bestmodel,start,end,modelN,error);
                 }
                 cout << "Finished report Concentrations Model K Fold = "<< calib_statistic.m_bestFitCalibration[a].kfold <<endl;

                }
                ReportConcentrations(cur_statistic);
                cout << "Finished report Concentrations "<< endl;
        }
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief ReportConcentrations
        /// \param cur_statistic
        /// \param kfold
        /// \param start
        /// \param end
        /// \param index
        ///
       void ReportConcentrations(Statistic &cur_statistic,const  Statistic & calib_statistic,int kfold, int start,int end,int index,mat error)

        {
            if( index < (int)cur_statistic.currentPopulationMatrix.n_cols)
            {
                mat originalConcentrations = cur_statistic.currentConcentrationMatrix.t();

                ValidationModel model = calib_statistic.m_CrossValidation[kfold];
                ValidationModel validatedmodel = model;
                mat factors = model.Factors.t();
                if(start >= 0 && start < end &&  (int)originalConcentrations.n_elem > 0 && end <= (int)originalConcentrations.n_rows)
                {
                    originalConcentrations = originalConcentrations.rows(start,end - 1);
                    mat A = cur_statistic.currentPopulationMatrix.rows(start,end - 1).cols(0,index) ;

                    mat recreatedcons = ((A * factors) * model.BCofficients).t();
                    cur_statistic.C_RecreatedConcentrations.push_back(recreatedcons );

                    Stat errors;
                    mat recreated = cur_statistic.C_RecreatedConcentrations[(int)cur_statistic.C_RecreatedConcentrations.size() - 1].t();

                    errors = errors.CalculateErrors
                    (
                                 recreated,
                                 originalConcentrations,
                                 index,index,
                                 kfold,start,end
                    );


                   // errors.ResidualSpectra = error;
                    errors.ResidualSpectra = (originalConcentrations - recreated) * pinv(model.BCofficients) * pinv(factors);
                    errors.ResidualConcentration = ((errors.ResidualSpectra * factors) * model.BCofficients).t();

                    validatedmodel.ModelCrossValidation = errors;
                    validatedmodel.PCANumber = model.ModelCrossValidation.getPCANumber();
                    cur_statistic.m_CrossValidation.push_back(validatedmodel);
                }
            }
        }
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief ReportConcentrations
        /// \param cur_statistic
        ///
        /*void ReportConcentrations(const Statistic &cur_statistic,const Statistic &calib_statistic,bool display)
        {

            for(int i =0;i < (int)cur_statistic.CalibrationStat.size();i++)
            {
                cur_statistic.CalibrationStat[i].print(true,true);
                //calib_statistic.CalibrationStat[i].print(true,false);
            }
        }*/
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief ReportConcentrations
        /// \param cur_statistic
        ///
        void ReportConcentrations(const Statistic &cur_statistic)
         {
             for(int i =0;i < (int)cur_statistic.m_CrossValidation.size();i++)
             {
                 cur_statistic.m_CrossValidation[i].ModelCrossValidation.print(true,true);
             }
         }

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief printBestCrossValidatedModels
        /// \param cur_statistic
        ///
        void printBestCrossValidatedModels(const Statistic &cur_statistic)
        {
             // cur_statistic.currentConcentrationMatrix.print("Full Concentrations =");

            for(int i=0;i < (int)cur_statistic.m_CrossValidation.size();i++)
            {
                 cur_statistic.m_CrossValidation[i].ModelCrossValidation.print(true,false);
            }
        }

       /* void CrossValidateBestCalinbrationModel( Statistic &cur_statistic, Statistic calib_statistic,bool calculateresidual = false)
        {

            Stat model = *(cur_statistic.m_bestFitCalibration.begin());
            model.print();
            cur_statistic.CalibrationStat.clear();
            cur_statistic.C_RecreatedConcentrations.clear();
           // mat originalConcentrations;
            int numRows = (int)cur_statistic.currentPopulationMatrix.n_rows;
            int numCols = (int)cur_statistic.Concentration_WithUnknown[0].n_rows;
            int numSlices = 1;
            mat originalConcentrations;
            cube recreatedConcentrations(numRows,numCols,numSlices);
            recreatedConcentrations.zeros();

            for(int i=0;i < (int)cur_statistic.currentPopulationMatrix.n_rows;i++)
            {
                int index = model.getIndex();
                originalConcentrations = cur_statistic.Concentration_WithUnknown[index].t();
                mat A  = cur_statistic.newcurrentPopulationMatrix[index].row(i);
               // A.print("A=");
               mat F = cur_statistic.F_pcaFactors[index ];
               mat E = A - (A * F.t() * F);

               //E.print("E=");
               mat concentration = ((A - E)* cur_statistic.F_pcaFactors[index ].t()) * cur_statistic.B_calibrationCofficients[index ] ;//+ Err;

               mat concentration1 =   ((A * calib_statistic.F_pcaFactors[index].t()) * calib_statistic.B_calibrationCofficients[index]).t();
              // concentration.print("C0=");
              // concentration1.print("C1=");
               int slice = 0;
               for(int b = 0;b < numCols;b++)
               {
                    recreatedConcentrations(i,b,slice) = concentration(b) ;
               }
               cur_statistic.C_RecreatedConcentrations.push_back(recreatedConcentrations.slice(slice));
               Stat errors;
               errors = errors.CalculateErrors(cur_statistic.C_RecreatedConcentrations[slice].t(),originalConcentrations,index,model.getPCANumber());
               cur_statistic.CalibrationStat.push_back(errors);

            }
             recreatedConcentrations.print("Recreated Concentrations = ");
             originalConcentrations.print("Original = ");

             cout << endl;
        }*/
       /* void CrossValidate( Statistic &cur_statistic, Statistic calib_statistic,bool calculateresidual = false)
        {
            cur_statistic.CalibrationStat.clear();
            cur_statistic.C_RecreatedConcentrations.clear();
           // mat originalConcentrations;
            int numRows = (int)cur_statistic.currentPopulationMatrix.n_rows;
            int numCols = (int)cur_statistic.Concentration_WithUnknown[0].n_rows;
            int numSlices = cur_statistic.numberOfPcaComponents;

            cube recreatedConcentrations(numRows,numCols,numSlices);
            recreatedConcentrations.zeros();

            for(int i=0;i < (int)cur_statistic.currentPopulationMatrix.n_rows;i++)
            {
                    for(auto model : cur_statistic.errrorsStat)
                    {
                        int index = model.getIndex() - 1;
                       // originalConcentrations = cur_statistic.Concentration_WithUnknown[index].t();
                        mat A  = cur_statistic.newcurrentPopulationMatrix[index].row(i);


                      // cur_statistic.B_calibrationCofficients[index].print("B");
                      // (A * cur_statistic.F_pcaFactors[index].t() ).print("A=");
                      // cur_statistic.S_pcaScores[index].print("NewA=");
                       mat F = cur_statistic.F_pcaFactors[index ];
                       mat E = A - (A * F.t() * F);
                       //cout <<"F.t() * F=" << F.t() * F << endl;
                       //E.print("E=");
                       mat concentration = ((A - E)* cur_statistic.F_pcaFactors[index ].t()) * cur_statistic.B_calibrationCofficients[index ] ;//+ Err;
                       //   A * calib_statistic.F_pcaFactors[index].t()) * calib_statistic.B_calibrationCofficients[index]).t()
                       //concentration.print("Recreated sample n = " + to_string(i) + " PCA Number = " + to_string(index));

                         for(int b = 0;b < numCols;b++)
                         {
                             // after the student test if needs recalculation it will come here
                             if(  (int)concentration.n_cols ==  2 * numCols)
                             {
                                 recreatedConcentrations(i,b,index) = concentration(b) - concentration(b + numCols);
                             }
                             else
                             {
                                  // first time it will come here
                                  recreatedConcentrations(i,b,index) = concentration(b) ;
                             }
                         }
                         if(index == (int)cur_statistic.errrorsStat.size() - 1)
                             break;
                    }
            }

           //recreatedConcentrations.print("R=");

           cout << "start next pcr " << endl;
            for(int a = 0;a < cur_statistic.numberOfPcaComponents;a++)
            {
                cout << "PCA Number = " + to_string(a) << endl;
                cout << "Recreated     " << " Original"<< endl;
                mat originalConcentrations = cur_statistic.Concentration_WithUnknown[a].t();
                mat cons = recreatedConcentrations.slice(a);
                mat error(size(cons));
                error.zeros();
                for(int b = 0;b < (int)cons.n_rows;b++)
                {
                    for(int c = 0;c<(int)cons.n_cols;c++)
                    {
                       error(b,c) = ((mat)cur_statistic.Concentration_WithUnknown[a].t())(b,c) - cons(b,c);
                      // cout <<"First = "<< originalConcentrations(b,c) - cons(b,c);
                       cout << "recreated = " << cons(b,c)<< "       original "<< ((mat)cur_statistic.Concentration_WithUnknown[a].t())(b,c)<< "  error = " << error(b,c) << endl;
                    }   
                }
                cur_statistic.Ev_validationError[a] = originalConcentrations - cons;
            }
           /* for(int s=0;s< cur_statistic.Ev_validationError.size();s++)
            {
                cur_statistic.Ev_validationError[s].print("EV= " + to_string(s));
            }*/
            //bool studentTest = true;
           /* cout << "start next pcr " << endl;


            if(calculateresidual)
            {
                //RecalculatePCRIncludeResidual(cur_statistic,recreatedConcentrations);
            }

        }*/
        /*void RecalculatePCRIncludeResidual(Statistic &cur_statistic,cube recreatedConcentrations)
        {

            for(auto model : cur_statistic.errrorsStat)
            {

                int index = model.getIndex() - 1;
               // (recreatedConcentrations.slice(index).t()).print("R=");

                cur_statistic.C_RecreatedConcentrations[index] = recreatedConcentrations.slice(index).t();
                cur_statistic.Ev_validationError[index] = cur_statistic.Concentration_WithUnknown[index].t() - cur_statistic.C_RecreatedConcentrations[index].t();

                //cur_statistic.Ev_validationError[index].print("ERR Validation =");
                //originalConcentrations = cur_statistic.Concentration_WithUnknown[index].t();

                Stat errors;

                errors = errors.CalculateErrors(cur_statistic.C_RecreatedConcentrations[index].t(),cur_statistic.Concentration_WithUnknown[index].t(),index,index);

                cur_statistic.CalibrationStat[index] = errors;
               // originalConcentrations.print("Original = ");
                //(cur_statistic.C_RecreatedConcentrations[index].t()).print("Recreated=");
               // cur_statistic.Ev_validationError[index].print("ECALIB=");
                //mat AResidual = cur_statistic.Ev_validationError[index] * pinv(cur_statistic.B_calibrationCofficients[index ]);
               // mat F = cur_statistic.F_pcaFactors[index ].t();
               mat AResidual = cur_statistic.Ev_validationError[index] * pinv(cur_statistic.B_calibrationCofficients[index ]) * pinv((mat)cur_statistic.F_pcaFactors[index ].t());
               AResidual.print("AR=");
               mat A = cur_statistic.newcurrentPopulationMatrix[index] + AResidual;
               mat concentration = (A * cur_statistic.F_pcaFactors[index ].t()) * cur_statistic.B_calibrationCofficients[index ] ;
               concentration.print(" PCA Number = " + to_string(index));
               cout << endl;
                /*studentTest =   studentTest && errors.StudentTest(  cur_statistic.Ev_validationError[index]  , cur_statistic.Concentration_WithUnknown[index].t() ) ;
                if( ! studentTest )
                {
                    cur_statistic.Concentration_WithUnknown[index].print("C before=");
                    int numCol = (int) cur_statistic.Concentration_WithUnknown[index].n_rows;
                    for(int numOfConstitutes = 0;numOfConstitutes < numCol; numOfConstitutes++)
                    {
                        addrow(cur_statistic.Concentration_WithUnknown[index], conv_to< rowvec >::from( cur_statistic.Ev_validationError[index].col(numOfConstitutes)));
                    }
                    cur_statistic.Concentration_WithUnknown[index].print("C after adding an error rows =");
                    // reacreated = Original - EC
                    cur_statistic.C_RecreatedConcentrations[index].print("Recreated = ");


                    cur_statistic.S_pcaScores[index].print("SCORE before=");
                    mat A = cur_statistic.currentPopulationMatrix.cols(0,index) ;
                    //cur_statistic.S_pcaScores[index] =  (A * cur_statistic.F_pcaFactors[index ].t());
                   // addcol(  cur_statistic.S_pcaScores[index],(  colvec(   (int)cur_statistic.S_pcaScores[index].n_rows).zeros())   );
                   // cur_statistic.S_pcaScores[index].print("SCORE after=");
                    //cur_statistic.newcurrentPopulationMatrix[index] = cur_statistic.S_pcaScores[index] *  cur_statistic.F_pcaFactors[index];
                    step2PCR(cur_statistic.B_calibrationCofficients[index],cur_statistic.S_pcaScores[index], cur_statistic.Concentration_WithUnknown[index]);

                }*/

                /*for(auto a: cur_statistic.Ev_validationError)
                {
                    a.print("EV=");
                }
                cout << endl;
                if( ! studentTest )
                {
                    CrossValidate( cur_statistic,  cur_statistic);
                }
            }
        }*/

        void printRecreatedConcentratios(const Statistic &cur_statistic,int firstN,vector<Stat> stat)
        {
            int len = min(firstN,(int)stat.size());

            for(int a = 0;a < len;a++)
            {
                int index = stat[a].getIndex();

                mat rec = cur_statistic.C_RecreatedConcentrations[index].rows(0,cur_statistic.currentConcentrationMatrix.n_rows - 1);
                mat orig = cur_statistic.currentConcentrationMatrix;
                cout << "Start PCA Number =" + to_string(index + 1) << endl;
                for(int i=0;i<(int)rec.n_rows;i++)
                {
                    for(int j=0;j<(int)orig.n_cols;j++)
                    {
                       cout <<  "Recreated = " << setw(3)  << rec(i,j) << "  Original = " << setw(3)  << orig(i,j) << endl;
                    }
                }
                cout << "Finish PCA Number =" + to_string(index + 1) << endl;
            }
        }

       /* void printCalibrationError()
        {
            int count = 0;
            for(auto EC : Ev_validationError)
            {
              EC.print("EC_calibrationError" + to_string(count + 1));
              //ConcentrationMatrixAfterPrediction[count].print("ConcentrationMatrixAfterPrediction=" + to_string(count + 1));
                 count++;
            }
        }*/
        void printCalibrationStatistics()
        {
            int count = 0;
            for(auto stat : CalibrationStat)
            {
                 stat.print();
                // ConcentrationMatrixAfterPrediction[count].print("ConcentrationMatrixAfterPrediction=" + to_string(count + 1));
                 count++;
            }

        }
        void RecalculatePcaEquations(Statistic &cur_statistic, const Statistic& calib_statistic)
        {

           cur_statistic = calib_statistic;

           for(int f =0; f < cur_statistic.numberOfPcaComponents;f++)
           {
               mat ZERO = mat(size(cur_statistic.Ea_error[f]));
               ZERO.zeros();
               bool same  = cur_statistic.errrorsStat[f].R2 >= 1;

              //printsomedata(cur_statistic,f,cur_statistic.currentPopulationMatrix);

              if(!same )
              {
                      cur_statistic.S_pcaScores[f] = calib_statistic.m_OptimizationParameters[f].scoreWithResidual;

                      // add unknown Concentration
                      if(cur_statistic.currentConcentrationMatrix.n_rows == cur_statistic.Concentration_WithUnknown[f].n_rows)
                      {
                          mat recalculateConcentration(cur_statistic.currentConcentrationMatrix.n_rows + 1,cur_statistic.currentConcentrationMatrix.n_cols);
                          recalculateConcentration.zeros();
                          recalculateConcentration.rows(0,cur_statistic.currentConcentrationMatrix.n_rows-1) = cur_statistic.currentConcentrationMatrix.rows(0,cur_statistic.currentConcentrationMatrix.n_rows - 1);
                          cur_statistic.Concentration_WithUnknown[f] = recalculateConcentration;
                      }
                      step2PCR(cur_statistic.B_calibrationCofficients[f],cur_statistic.S_pcaScores[f], cur_statistic.Concentration_WithUnknown[f]);

                      mat tempnew = mat(size(cur_statistic.S_pcaScores[f]));
                      tempnew.cols(0,cur_statistic.newcurrentPopulationMatrix[f].n_cols -1)= cur_statistic.newcurrentPopulationMatrix[f].cols(0,cur_statistic.newcurrentPopulationMatrix[f].n_cols-1);
                      tempnew.cols(tempnew.n_cols-1,tempnew.n_cols-1) = cur_statistic.S_pcaScores[f].cols(cur_statistic.S_pcaScores[f].n_cols-1,cur_statistic.S_pcaScores[f].n_cols-1);
                      cur_statistic.newcurrentPopulationMatrix[f] = tempnew;

                      try
                      {
                          cur_statistic.F_pcaFactors[f]=pinv( cur_statistic.S_pcaScores[f].t() * cur_statistic.S_pcaScores[f] ) * cur_statistic.S_pcaScores[f].t() * cur_statistic.newcurrentPopulationMatrix[f];

                          cur_statistic.F_pcaFactors[f] = cur_statistic.F_pcaFactors[f].t();

                          mat check =  cur_statistic.S_pcaScores[f] * cur_statistic.F_pcaFactors[f];

                         cur_statistic.Ea_error[f] = cur_statistic.S_pcaScores[f] * cur_statistic.F_pcaFactors[f];


                          Stat errors;
                         // errors = errors.CalculateErrors(  cur_statistic.S_pcaScores[f] * cur_statistic.F_pcaFactors[f],cur_statistic.newcurrentPopulationMatrix[f],cur_statistic.errrorsStat[f].getIndex(),cur_statistic.errrorsStat[f].getPCANumber()+1);
                          errors = errors.CalculateErrors(cur_statistic.newcurrentPopulationMatrix[f],cur_statistic.currentPopulationMatrix,cur_statistic.errrorsStat[f].getIndex(),cur_statistic.errrorsStat[f].getPCANumber()+1);
                          cur_statistic.errrorsStat[f] = errors;

                          //printsomedata(cur_statistic,f,cur_statistic.currentPopulationMatrix);

                      }
                      catch(std::exception)
                      {
                          cout << "Inverse matrix does not exist for number of samples = "<<(int)cur_statistic.currentPopulationMatrix.n_rows  << " < "<<
                               " number of variables = " <<  (int)cur_statistic.currentPopulationMatrix.n_cols << endl;
                          cout << "increase number Of Samples at least on << " << (int)cur_statistic.currentPopulationMatrix.n_rows - (int)cur_statistic.currentPopulationMatrix.n_cols;
                      }
                }
            }
        }

        void definePCAComponents(vector<Stat> models)
        {
            int numberOfSamples = (int)currentPopulationMatrix.n_rows;
            vector<vector<PCAComponent>>  Models;
            for(auto model : models)
            {
                int nVariablePCA =  model.getIndex() - 1;
                // ParamPrint(nVariablePCA,LIBPCA);

                 vector<PCAComponent> pcaComponentsSamples;

                for(int sample = 0;sample < numberOfSamples; sample++)
                {
                    PCAComponent currentPCAcomps;
                    currentPCAcomps.m_index = sample;
                    currentPCAcomps.m_modelNumber = nVariablePCA + 1;
                    currentPCAcomps.m_Sscore = S_pcaScores[nVariablePCA].row(sample);
                    currentPCAcomps.m_Feigenvector = F_pcaFactors[nVariablePCA].cols(0,nVariablePCA);
                    currentPCAcomps.m_Eerror = Ea_error[nVariablePCA].row(sample);
                    currentPCAcomps.m_Aintensity = currentPopulationMatrix.row(sample).cols(0,nVariablePCA);
                    currentPCAcomps.m_OriginalSpectra =  (currentPopulationMatrix.cols(0,nVariablePCA) * F_pcaFactors[nVariablePCA]);


                     currentPCAcomps.print();

                    currentPCAcomps.sumOfSpectraPCA = mat(currentPCAcomps.m_modelNumber,1);

                    for(int i = 0 ;i < (int)currentPCAcomps.m_Feigenvector.n_cols;i++)
                    {
                      currentPCAcomps.m_PrincipalComponents.push_back(currentPCAcomps.m_Aintensity % conv_to<rowvec>::from(currentPCAcomps.m_Feigenvector.col(i)));
                     // currentPCAcomps.sumOfSpectraPCA.row(i) = sum(currentPCAcomps.m_PrincipalComponents[i],0);

                    }

                    currentPCAcomps.print();

                    pcaComponentsSamples.push_back(currentPCAcomps);
                }
                Models.push_back(pcaComponentsSamples);
            }
           // printPCAComponents(Models);

        }
        void printPCAComponents( const vector<vector<PCAComponent>> & PCAModels)
         {
                        for(auto model: PCAModels)
                        {

                            for(auto sample: model)
                            {
                                   sample.print();

                            }
                             cout << endl;
                        }
              cout << endl;
        }
        ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
       /* void definePCAComponents(vector<Stat> models)
        {
            for(auto model : models)
            {
                int nVariablePCA =  model.getIndeex() - 1;
                //int nVariablePCA = 7;
                vector<vector<PCAComponent>> pcaComponentsOfSamples;
                for(int sample = 0;sample < NUMBER_OF_SAMPLES; sample++)
                {
                    vector<PCAComponent> pcaComponentsOfConstitues;
                    for(int nconstitutes = 0 ; nconstitutes < ConcentrationMatrixAfterPrediction[nVariablePCA].n_rows;nconstitutes++)
                    {
                         PCAComponent currentPCAcomp;

                         currentPCAcomp.m_name = Constituents(nconstitutes);
                         currentPCAcomp.m_index = sample;
                         currentPCAcomp.m_modelNumber = nVariablePCA + 1;
                         mat temp = S_pcaScores[nVariablePCA].t();
                         currentPCAcomp.m_Sscore = temp.col(sample);
                         S_pcaScores[nVariablePCA].print("SCORE=");
                         currentPCAcomp.m_Feigenvector = F_pcaFactors[nVariablePCA].col(nVariablePCA);

                         currentPCAcomp.m_Eerror = Ea_error[nVariablePCA].row(sample);
                         currentPCAcomp.eigvalues = eigenvectorValues[nVariablePCA];
                         currentPCAcomp.m_BconstituteCoefficient = B_calibrationCofficients[nVariablePCA].row(nconstitutes);
                         //          = m_BconstituteCoefficient[f x f] * (m_Aintensity[f x 1] * m_Feigenvector[1 x f]) = [f x f]

                         currentPCAcomp.m_Cconstitute = currentPCAcomp.m_BconstituteCoefficient * currentPCAcomp.m_Sscore;


                         currentPCAcomp.m_Aintensity =   currentPCAcomp.m_Cconstitute   * newcurrentPopulationMatrix[nVariablePCA].row(sample);// % currentPCAcomp.m_BconstituteCoefficient;
                         currentPCAcomp.m_PrincipalComponents =  currentPCAcomp.m_Sscore.t() % currentPCAcomp.m_Feigenvector.t();
                        //currentPCAcomp.m_PrincipalComponents =  S_pcaScores[nVariablePCA].row(sample) %  currentPCAcomp.m_Feigenvector.t();
                         (newcurrentPopulationMatrix[nVariablePCA].row(sample) ).print("NEW A");

                         currentPCAcomp.m_PrincipalComponents.print("R");
                         //((currentPCAcomp.m_Sscore.t() * currentPCAcomp.m_Sscore) * newcurrentPopulationMatrix[nVariablePCA].row(sample)).print("JJ");

                                  // [f x 1]                    =                  [1 x f]    * [f x f]
                                  // currentPCAcomp.m_Cconstitute = (currentPCAcomp.m_Aintensity * currentPCAcomp.m_BconstituteCoefficient).t() ;
                                  // currentPCAcomp.m_Cconstitute.print("C1=");
                                  // [f x 1]                    =   [1 x f]                                [1 x f]                          * [f x f]
                                  //currentPCAcomp.m_Cconstitute =   (currentPCAcomp.m_Aintensity  %  currentPCAcomp.m_Feigenvector  * currentPCAcomp.m_BconstituteCoefficient).t()  ;
                                  //currentPCAcomp.m_Cconstitute.print("C1=");
                          currentPCAcomp.m_OriginalConcentrations =  currentConcentrationMatrix.col(sample);
                          pcaComponentsOfConstitues.push_back(currentPCAcomp);

                    }


                    //(newcurrentPopulationMatrix[nVariablePCA](sample,pcaComponentsOfConstitues[0].m_modelNumber) - pcaComponentsOfConstitues[0].m_PrincipalComponents).print("ERROR");


                    pcaComponentsOfSamples.push_back(pcaComponentsOfConstitues);

                }
                pcaComponentsOfSamplesOfModels.push_back(pcaComponentsOfSamples);
                printPCAComponents(pcaComponentsOfSamplesOfModels);

                cout << endl;
            }
            FindResidualSpectra(pcaComponentsOfSamplesOfModels);
            cout << endl;
        }*/

        void printPCAComponents( const vector<vector<vector<PCAComponent>>> & PCAModels)
         {
                        for(auto model: PCAModels)
                        {

                            for(auto sample: model)
                            {
                                for(auto constitute: sample)
                                {
                                   constitute.print();
                                   cout << endl;
                                }

                            }

                        }
                        cout << endl;
        }

        void FindResidualSpectra(const vector<vector<vector<PCAComponent>>> & PCAModels)
        {

           /* for(auto model: PCAModels)
            {
                mat originalspectra = currentPopulationMatrix;
                int modelNumber =-1;
                for(auto samples: model)
                {
                        modelNumber = samples.m_modelNumber - 1;
                        originalspectra.row(samples.m_index) =  originalspectra.row(samples.m_index) - samples.m_PrincipalComponents.row(0);
                    cout << endl;
                }

                m_ResidualSpectra.push_back(originalspectra);
            }
            printResidualSpectra(m_ResidualSpectra);
            cout << endl;*/
        }
        void printResidualSpectra(vector<mat> residualspectra)
        {
            int count =0;
            for(auto spectra : residualspectra)
            {
                spectra.print("Residual Spectra for Model = " + to_string(count));
                count++;
            }
        }
        void CalculateTPV(Statistic &stat)
        {
            if((int)stat.m_OptimizationParameters.size() > 0)
            {
                double  sumOfEigValuesFortotalNumberOfFactors = stat.m_OptimizationParameters[stat.numberOfPcaComponents - 1].SumOfEigValues;

                for(int i =0; i < (int)stat.m_OptimizationParameters.size();i++)
                {

                    stat.m_OptimizationParameters[i].TPV = stat.m_OptimizationParameters[i].SumOfEigValues / sumOfEigValuesFortotalNumberOfFactors;

                }
            }

        }
        void CalculateMalinovskiIndicator(Statistic& stat)
        {
            if((int)stat.m_OptimizationParameters.size() > 0 && (int)stat.currentPopulationMatrix.n_rows > 0 && (int)stat.currentPopulationMatrix.n_cols > 0)
            {
                double d2 = max(stat.currentPopulationMatrix.n_rows,stat.currentPopulationMatrix.n_cols);
                stat.m_OptimizationParameters[0].MalinowskiIndicator_i = 1;
                for(int i = 1; i < (int)stat.m_OptimizationParameters.size();i++)
                {
                    stat.m_OptimizationParameters[i].MalinowskiIndicator_i = stat.m_OptimizationParameters[i - 1].RealErrorFunction_i/( pow((d2 - i),2));

                }
            }
        }
        void PrintOptimization(Statistic &stat)
        {
            for(auto opt :stat.m_OptimizationParameters )
            {
                opt.print();
            }
        }

        Optimization CalculateOptimizationParameters(Statistic stat,int npca)
        	{
                  Optimization result;
                  result.numberOfPCA = npca + 1;
                  result.index = npca + 1;
        		           mat ZERO = mat(size(stat.currentPopulationMatrix));
        		           ZERO.zeros();
        		           mat E = stat.Ea_error[npca] - ZERO;

        		           result.meani = mat((int)E.n_rows,1);

        		           for(int i=0; i < (int)E.n_rows ; ++i)
        		           {
        		              result.meani.row(i) = arma::mean(E.row(i));
        		           }

                           result.meanCentralResidual = mat((int)E.n_rows,1);
        		           for(int i=0;i < (int)E.n_rows;i++)
        		           {
        		                 double sumrowsresidual =0;
        		                  for(int j=0;j < (int)E.n_cols;j++)
        		                  {

        		                      sumrowsresidual = sumrowsresidual + pow(E(i,j),2);
        		                  }

        		                  result.meanCentralResidual.row(i) = result.meani(i,0) - (sumrowsresidual / (int)E.n_cols);
        		           }

        		           result.meanCentralResidualAverage = abs(arma::mean(conv_to<rowvec>::from( result.meanCentralResidual.cols(0,0))));

                           result.scoreWithResidual = mat(stat.S_pcaScores[npca].n_rows,stat.S_pcaScores[npca].n_cols + 1);
                           result.scoreWithResidual.zeros();
                           result.scoreWithResidual.cols(0,stat.S_pcaScores[npca].n_cols -1) = stat.S_pcaScores[npca].cols(0,stat.S_pcaScores[npca].n_cols - 1);
                           result.scoreWithResidual.cols(stat.S_pcaScores[npca].n_cols,stat.S_pcaScores[npca].n_cols)  = result.meanCentralResidual.cols(0,0);

                           result.mahalanobis = (result.scoreWithResidual.t() * result.scoreWithResidual) / (result.scoreWithResidual.n_rows -1);


                           try
                           {
                                result.Di2 = result.scoreWithResidual * pinv( result.mahalanobis) * result.scoreWithResidual.t();

                                mat sum = mat(result.Di2.n_rows,1);
                                for(int i=0;i<(int)result.Di2.n_rows;i++)
                                {
                                    for(int j=0;j<(int)result.Di2.n_cols;j++)
                                    {
                                          sum(i,0) = sum(i,0) + result.Di2(i,j);
                                    }
                                }

                                result.RMSG = sum / (result.scoreWithResidual.n_rows -1);

                           }
                           catch(std::exception)
                           {

                               result.RMSGAVERAGE = 100000000;
                               cout << "Inverse matrix does not exist for number of samples = "<<(int)stat.currentPopulationMatrix.n_rows  << " < "<<
                                    " number of variables = " <<  (int)stat.currentPopulationMatrix.n_cols << endl;
                               cout << "increase number Of Samples at least on << " << (int)stat.currentPopulationMatrix.n_rows - (int)stat.currentPopulationMatrix.n_cols;
                           }

                           result.CalculateOptimizationStatistic
                           (
                                       stat.eigenvectorValues[npca],
                                       stat.currentPopulationMatrix.n_rows,
                                       stat.currentPopulationMatrix.n_cols,
                                       npca,
                                       stat.Ea_error[npca]
                           );

        		           return result;
        	}

        void Clear()
        {
            //PCA parameters
            ClearStatistics(*this);


           // ConcentrationMatrixAfterPrediction.clear();
            currentPopulationOfConcentrations.reset();

            currentPopulationOfSamples.reset();
            currentPopulationMatrix.clear();
            currentConcentrationMatrix.clear();

             meanSpectrum.clear();
             meanConcentrations.clear();
             standardDeviationSpectrum.clear();
             correlationSpectrum.clear();
             covarienceMatrixSpectrum.clear();

        }

        //This matrix size is = (numberOfSamples x NumberOfwavelength = MAXIMUM_NUMBER_OF_POINTS)
        mat currentPopulationMatrix;
        // This matrix contains the responses from independent experiments
        //size of matrix = (numberOfSamples x NumberOfPCAComponents)
        mat currentConcentrationMatrix;

        running_stat_vec<rowvec> currentPopulationOfSamples;
        running_stat_vec<rowvec> currentPopulationOfConcentrations;
        mat meanSpectrum;
        mat meanConcentrations;
        mat standardDeviationSpectrum;
        mat correlationSpectrum;
        mat covarienceMatrixSpectrum;
        rowvec zeroTransmissionSpectra;
        //PCA parameters
        vector<mat> PCA;
        vector<mat> F_pcaFactors;
        vector<mat> S_pcaScores;
        vector<mat> Ea_error;
        //vector<mat> Ev_validationError;
        vector<mat> eigenvectorValues;
        vector<mat> newcurrentPopulationMatrix;
        vector<mat> B_calibrationCofficients;
        vector<mat> C_RecreatedConcentrations;

        vector<mat> Concentration_WithUnknown;
        //vector<mat> ConcentrationMatrixAfterPrediction;
        vector<Stat>  errrorsStat;
        vector<Stat>  CalibrationStat;

       // map<int,map<Constituents,mat>> SeperatedSpectra;
        map<Constituents,int> m_ConstituesIndexMap;
        int numberOfPcaComponents;

        //vector<vector<vector<PCAComponent>>> pcaComponentsOfSamplesOfModels; // vector of Samples [each vector has the pca components for the sample]
        vector<Optimization> m_OptimizationParameters;

        vector<Stat> m_bestFitCalibration;

        vector<ValidationModel> m_CrossValidation;
   };


} /* namespace NDUV */

#endif /* STATISTICS_H_ */

