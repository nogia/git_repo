/*
 * Avs5216.cpp
 *
 *  Created on: Apr 7, 2016
 *      Author: inna
 */

#include "Avs5216.h"

namespace NDUV
{
    //Statistic BaseFunction::m_statistic_Seperated_Spectra;

   // Statistic BaseFunction::m_statistic_with_unknown_interference;
    //Statistic BaseFunction::m_statistic_with_unknown_interference_SeperatedSpectra;

    Plot* BaseFunction::m_plot;

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \brief Avs::AddTask
    /// \param name
    /// \param taskname
    /// \param task
    ///
    void Avs::AddTask(FunctionName name,string taskname,TaskOptionsParameters  task)
    {
        if(m_tasks.size() > 0)
        {
            map< FunctionName,BaseFunction *>::iterator it = m_tasks.find(name);
            if(it != m_tasks.end())
            {
                m_tasks.erase (it);
            }
        }
        BaseFunction* currenttask = createTask(name,taskname,task);
        if(currenttask != nullptr)
        {
           m_tasks[name] = currenttask;
        }
        else
        {
            cout << "Can not add task. Error"<< endl;
        }

    }
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \brief Avs::deleteTask
    /// \param name
    ///
    void Avs::deleteTask(FunctionName name)
    {
        if(m_tasks.size() > 0)
        {
            map< FunctionName,BaseFunction *>::iterator it = m_tasks.find(name);
            if(it != m_tasks.end())
            {
                m_tasks.erase (it);
            }
        }
    }
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \brief Avs::GetFunction
    /// \param name
    /// \return
    ///
    BaseFunction * Avs::GetFunction(FunctionName name)
    {
         BaseFunction *  result;
         if( m_tasks.find(name) != m_tasks.end())
         {
             result = m_tasks[name];
         }
         return result;
    }
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \brief Avs::ClearTasks
    ///
    void  Avs::ClearTasks()
    {
         m_tasks.clear();
    }

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \brief Avs::ProcessSpectrum
    /// \param s
    ///
    void Avs::ProcessSpectrum(Statistic &s)
    {

        cout << "Start Processing" << endl;
        for(auto task : m_tasks)
        {
           ProcessSpectrum(task,s);
        }
        cout << "Finished Processing" << endl;
    }
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \brief Avs::ProcessSpectrum
    /// \param taskname
    /// \param s
    ///
     void  Avs::ProcessSpectrum(FunctionName taskname,Statistic &s)
     {
         if( m_tasks.find(taskname) != m_tasks.end())
         {
             cout << "#################################     Start Execution Step name = "<<  GET_FUNCTION_NAMES[taskname]  <<"        ######################################################################" << endl;
             BaseFunction * ptr = m_tasks[taskname];
             if(ptr != nullptr)
             {
                 ptr->Run(s);
             }
             else
             {
                 cout <<  GET_FUNCTION_NAMES[taskname] << " = " << ptr << endl;
             }
             //m_tasks[taskname]->Run(s);
             cout << "#################################     Finished Execution Step name = "<<  GET_FUNCTION_NAMES[taskname] << "     ######################################################################" << endl;
         }
         else
         {
             cout << "Function name = " << taskname << " does not exist   Type = "<< GET_FUNCTION_NAMES[taskname] << endl;
         }
     }

     ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
     /// \brief Avs::ProcessSpectrum
     /// \param task
     /// \param s
     ///
    void Avs::ProcessSpectrum(pair<FunctionName,BaseFunction *> task,Statistic &s)
    {

        if( m_tasks.find(task.first) != m_tasks.end())
        {
            cout << "#################################     Start Execution Step name = "<<  GET_FUNCTION_NAMES[task.first] <<   " ######################################################################" << endl;
            m_tasks[task.first]->Run(s);
            cout << "#################################     Finished Execution Step name = "<<  GET_FUNCTION_NAMES[task.first] << "     ######################################################################" << endl;
        }
        else
        {
            cout << "Function name = " << GET_FUNCTION_NAMES[task.first] << " does not exist"<< endl;
        }
    }
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \brief Avs::createTask
    /// \param name
    /// \param nametext
    /// \param task
    /// \return
    ///
    BaseFunction* Avs::createTask(FunctionName name,string nametext,TaskOptionsParameters task)
    {
        switch(name)
        {
            case NONE:
            break;

            case PREPROCESSING:
                 return new Preprocessing(task);
            break;
            case BASE_LINE_CORRECTION:

               switch(task.m_baseLineCorrection)
               {

                  case SIMPLE_OFFSET_CORRECTION:
                     return new SimpleOffsetCorrection(task);
                   break;

                  case TWO_POINT_BASE_LINE:
                    return new TwoPointBaseLineCorrection(task);
                   break;

                  case MULTI_POINT_BASE_LINE:
                     return new MultiPointBaseLineCorrection(task);
                   break;

                  case INTERACTIVE_POLINOMIAL_BASELINE:
                     return new InteractivePolinomialBaseLineCorrection(task);
                   break;

                  case FUNCTION_FIT_BASE_LINE:
                      return new FunctionFitBaseLineCorrection(task);
                   break;

                  case GIFTS:
                      return new GIFTSBaseLineCorrection(task);
                     break;
                  case NONE_CORRECTION:
                     break;

               };

            break;
            case DATA_SMOOTHING:

               switch(task.m_dataSmoothing)
               {
                    case BINOMIAL:
                        return new BinomialSmoothing(task);
                     break;

                     case SAVITZJY_GOLAY:
                        return new SavitzkyGolaySmoothing(task);
                     break;

                     case NONE_SMOOTHING:
                     break;
               };
            case DERIVATIVE_SPECTRA:
                    switch(task.m_derivativeSpectraType.first )
                    {
                         case FIRST_DERIVATIVE_OF_WAVELENGTH:
                              return new DerivativeSpectra(task);
                          break;

                         case SECOND_DERIVATIVE_OF_WAVELENGTH:
                              return new DerivativeSpectra(task);
                          break;

                          case ZERO_DERIVATIVE_SPECTRA:
                               return new DerivativeSpectra(task);
                          break;
                          case NO_DERIVATIVE_TYPE:
                          break;
                    };
            break;
            case MEAN_CENTERING_SPECTRA:
                   return new MeanCenteringMethod(task);
            break;
            case CALIBRATION:
                 switch(task.m_calibrationType)
                 {
                       case UNIVARIATE_CALIBRATION:
                            return new UnivariateCalibration(task);
                       break;
                       case MULTIVARIATE_CALIBRATION:
                            return new MultivariateCalibration(task);
                       break;
                       case NO_CALIBRATION_TYPE:
                       break;
                 };

            break;
            case VALIDATION:
                     return new Validation(task);
            break;
            case PREDICTION:
                    return new Prediction(task);
            break;
            case ALGORITHM:
            //case AK_COMMUNICATION:
            //case RECORD_KEEPING:
           // case REAL_TIME_POST_PROCESSING:
           // case NUMBER_OF_FUNCTIONS:
            break;
        };

         return nullptr;
    }


    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \brief BaseFunction::BaseFunction
    ///
    BaseFunction::BaseFunction()
    {
          m_plot = new Plot();
          m_plot->Show = false;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \brief BaseFunction::~BaseFunction
    ///
    BaseFunction::~BaseFunction()
    {

        // m_statistic_Seperated_Spectra.Clear();
        // m_statistic_with_unknown_interference.Clear();
        // m_statistic_with_unknown_interference_SeperatedSpectra.Clear();

         m_currentdata.clear();
         delete m_plot;

    }
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \brief BaseFunction::Run
    /// \param statistic
    ///
    void BaseFunction::Run (Statistic & statistic){}


    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \brief BaseFunction::DisplaySpectrumData
    /// \param value
    ///
    void  BaseFunction::DisplaySpectrumData(mat value)
    {
       cout <<"START    SPECTRUM     STEP = "<< m_currentdata.m_task_name <<"#########################################################################"<<endl;
       for(int a = 0; a < (int)value.n_rows; a++)
       {
           int j=0;
           for(int i=0;  i <  (int)value.n_cols; i++,j++)
           {
                if(j == 16)
                {
                    j=0;
                    cout << endl;
                }
                 cout<< setprecision(3)  << setw(8) << value(a,i)<< " ";
            }
            cout << endl;
       }
        cout <<"END    SPECTRUM     STEP = "<< m_currentdata.m_task_name <<"##########################################################################"<<endl;
        cout << endl;

    }
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \brief BaseFunction::setCurrentPopulationOfSamples
    /// \param statistic
    ///
    void BaseFunction::setCurrentPopulationOfSamples(Statistic & statistic)
    {
        rowvec currentsample(statistic.currentPopulationMatrix.n_cols);

        for(int i=0;  i <  (int)statistic.currentPopulationMatrix.n_rows; i++)
        {
            currentsample = statistic.currentPopulationMatrix.row(i);
            for(int j=0;  j <  (int)statistic.currentPopulationMatrix.n_cols; j++)
            {
                    currentsample(j) = statistic.currentPopulationMatrix(i,j);
            }
            statistic.currentPopulationOfSamples(currentsample);
         }

        for(int i =0;i < (int)statistic.currentConcentrationMatrix.n_cols;i++)
        {
            rowvec currentsample  = conv_to< rowvec >::from(statistic.currentConcentrationMatrix.col(i));

            statistic.currentPopulationOfConcentrations(currentsample);
        }
    }
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \brief Preprocessing::Preprocessing
    /// \param task
    ///
    Preprocessing::Preprocessing(TaskOptionsParameters task)
    {
         m_currentdata =  task;
         m_currentdata.m_task_name = "Preprocessing";
    }

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \brief Preprocessing::Run
    /// \param statistic
    ///
    void Preprocessing::Run(Statistic & statistic)
     {

          //DisplaySpectrumData(statistic.zeroTransmissionSpectra);
          //DisplaySpectrumData(statistic.currentPopulationMatrix);
         /////////////////////////////////////////////////////////////////////////////////////////////////////////
         if(statistic.currentPopulationMatrix.n_elem <= 0 || statistic.zeroTransmissionSpectra.n_elem <= 0)
         {
             return;
         }
         mat spectraBefore = statistic.currentPopulationMatrix;
         for(int i=0;  i <  (int)statistic.currentPopulationMatrix.n_rows; i++)
         {
             for(int j=0;  j <  (int)statistic.currentPopulationMatrix.n_cols; j++)
             {

                 if( m_currentdata.m_zeroTransmissionDatapoints(0,j) != 0)
                 {
                    statistic.currentPopulationMatrix(i,j)=  statistic.currentPopulationMatrix(i,j) /  statistic.zeroTransmissionSpectra(0,j);

                 }
                 else
                 {
                       statistic.currentPopulationMatrix(i,j) =  statistic.currentPopulationMatrix.max();
                 }
                 if(statistic.currentPopulationMatrix(i,j) > 0)
                 {
                     statistic.currentPopulationMatrix(i,j) = -log10(statistic.currentPopulationMatrix(i,j));
                 }
                 else if(statistic.currentPopulationMatrix(i,j) == 0)
                 {
                      statistic.currentPopulationMatrix(i,j) =  statistic.currentPopulationMatrix.min();
                 }
                 else
                 {
                      statistic.currentPopulationMatrix(i,j) =  10000 * statistic.currentPopulationMatrix.min();
                 }
             }
         }

          //DisplaySpectrumData(statistic.zeroTransmissionSpectra);
          //DisplaySpectrumData(statistic.currentPopulationMatrix);

          m_plot->ShowCorrected(spectraBefore, statistic.currentPopulationMatrix,m_currentdata);
     }
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \brief Preprocessing::CheckScale
    /// \return
    ///
    bool Preprocessing::CheckScale()
    {
        return true;
    }
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \brief BaseLineCorrection::BaseLineCorrection
    /// \param task
    ///
    BaseLineCorrection::BaseLineCorrection(TaskOptionsParameters task)
    {
         m_currentdata = task;
         m_currentdata.m_task_name = "Base Line Correction ";
    }
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \brief BaseLineCorrection::ApplyFunction
    /// \param f
    /// \param values
    /// \param offset
    ///  This function used for simple offset correction
    void  BaseLineCorrection::ApplyFunction
    (
            std::function<void(vector<double> &,double,int )> f,
            vector<double> & values,
            double offset,
            int option
    )
    {
           f(values,offset,option);
    };
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \brief BaseLineCorrection::ApplyFunction
    /// \param f
    /// \param values
    /// \param valuesOfX
    /// \param points
    ///  For two and multiple baseline correction
    ///  For Interactive baseline correction
    void BaseLineCorrection::ApplyFunction
    (
            std::function<void(TaskOptionsParameters&,vector<double> &  ,std::vector<NDUV::Point> ,int)> f,
            TaskOptionsParameters &param,
            vector<double> & values,
            std::vector<NDUV::Point> points,
            int option
    )
    {
         f(param,values,points,option);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \brief BaseLineCorrection::Run
    /// \param statistic
    ///
    void BaseLineCorrection::Run(Statistic &statistic)
    {
        sort(m_currentdata.m_fitParameters.m_Xpoints.begin(),m_currentdata.m_fitParameters.m_Xpoints.end());
          statistic.currentPopulationMatrix.print("mat=");
        ////////////////////////////////////////////////////////////////////////////////
        std::string functionname;
        if(FunctionTypesMap.find(m_currentdata.m_fitParameters.functionType) != FunctionTypesMap.end())
        {
             functionname = FunctionTypesMap.at(m_currentdata.m_fitParameters.functionType);
        }

        cout << "START Function Name = "<<  m_currentdata.m_task_name  << " Function = " << functionname << endl;
        std::vector<NDUV::Point> points;

        mat beforeCorrection = statistic.currentPopulationMatrix;
        statistic.zeroTransmissionSpectra = m_currentdata.m_zeroTransmissionDatapoints;
        rowvec zerobefore = statistic.zeroTransmissionSpectra;
        m_currentdata.m_CorrectionFunction.second.clear();
        if((int)statistic.currentPopulationMatrix.n_elem > 0)
        {
             vector<double> zerospectra = Statistic::convToStd(statistic.zeroTransmissionSpectra);
             for(int i =0;i < (int)statistic.currentPopulationMatrix.n_rows;i++)
             {
                 vector<double> sample =  Statistic::convToStd( statistic.currentPopulationMatrix.row(i));
                 // find m_points
                 switch(m_currentdata.m_baseLineCorrection)
                 {
                    case SIMPLE_OFFSET_CORRECTION: 
                       if(i == 0)
                       {
                               ApplyFunction( static_cast<SimpleOffsetCorrection*>(this)->FunctionSimpleCorrection, zerospectra,m_correction_value,3);
                               statistic.zeroTransmissionSpectra = rowvec(zerospectra);
                       }

                        ApplyFunction( static_cast<SimpleOffsetCorrection*>(this)->FunctionSimpleCorrection, sample,m_correction_value,3);

                    break;
                    case TWO_POINT_BASE_LINE:
                    case MULTI_POINT_BASE_LINE:
                        points = m_currentdata.selectNPoints( m_currentdata.m_fitParameters.m_Xpoints,i,statistic.currentPopulationMatrix,0,m_currentdata.m_fitParameters.functionType);
                        ApplyFunction(FunctionPointCorrection,m_currentdata,sample,points,3);
                     break;
                    case INTERACTIVE_POLINOMIAL_BASELINE:
                         points = m_currentdata.selectNPoints( m_currentdata.m_fitParameters.m_Xpoints,i,statistic.currentPopulationMatrix,0,m_currentdata.m_fitParameters.functionType);
                         ApplyFunction(FunctionFitCorrection,m_currentdata,sample,points,3);
                     break;
                    case FUNCTION_FIT_BASE_LINE:
                             points = m_currentdata.selectNPoints( m_currentdata.m_fitParameters.m_Xpoints,i,statistic.currentPopulationMatrix,0, m_currentdata.m_fitParameters.functionType);
                             ApplyFunction(FunctionFitCorrection,m_currentdata,sample,points,3);
                     break;

                     case NONE_CORRECTION:
                     case GIFTS:
                     break;

                 };
                 if(sample.size() > 0)
                 {
                        statistic.currentPopulationMatrix.row(i) = rowvec(sample);
                 }
                 else
                 {
                        rowvec zero = rowvec( (int)statistic.currentPopulationMatrix.row(i).n_cols);
                        zero.zeros();
                        statistic.currentPopulationMatrix.row(i) = zero;
                 }
             }


             //m_plot->ShowCorrected( zerobefore, statistic.zeroTransmissionSpectra,m_currentdata);
             m_plot->ShowCorrected(beforeCorrection, statistic.currentPopulationMatrix,m_currentdata);

        }

        cout << "FINISH Function Name = "<<  m_currentdata.m_task_name   << " Function = " << functionname << endl;
        points.clear();
    }


    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \brief SimpleOffsetCorrection::SimpleOffsetCorrection
    /// \param task
    ///
    SimpleOffsetCorrection::SimpleOffsetCorrection(TaskOptionsParameters task)
    {
        m_currentdata = task;
        m_currentdata.m_task_name = " Simple Offset Correction";
        m_correction_value = m_currentdata.m_currentPopulationMatrix.min();
    }
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \brief TwoPointBaseLineCorrection::TwoPointBaseLineCorrection
    /// \param task
    ///
    TwoPointBaseLineCorrection::TwoPointBaseLineCorrection(TaskOptionsParameters task)
    {
         m_currentdata = task;
         m_currentdata.m_task_name =   " Two PointBaseLine Correction";
    }
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \brief MultiPointBaseLineCorrection::MultiPointBaseLineCorrection
    /// \param task
    ///
     MultiPointBaseLineCorrection::MultiPointBaseLineCorrection(TaskOptionsParameters task )
     {
         m_currentdata = task;
         m_currentdata.m_task_name =  " Multi PointBaseLine Correction";
     }
     ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
     /// \brief FunctionFitBaseLineCorrection::FunctionFitBaseLineCorrection
     /// \param task
     ///
     FunctionFitBaseLineCorrection::FunctionFitBaseLineCorrection(TaskOptionsParameters task )
     {
         m_currentdata = task;
         m_currentdata.m_task_name =  " FunctionFit PointBaseLine Correction";

         if(m_currentdata.m_fitParameters.functionType == NOT_SET)
         {
              m_currentdata.m_fitParameters.functionType = POLYNOMIAL;
              m_currentdata.m_fitParameters.NumberOfCofficients = 3;
         }
     }

      //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      /// \brief InteractivePolinomialBaseLineCorrection::InteractivePolinomialBaseLineCorrection
      /// \param task
      ///
       InteractivePolinomialBaseLineCorrection::InteractivePolinomialBaseLineCorrection(TaskOptionsParameters task)
       {
           m_currentdata = task;
           m_currentdata.m_task_name = "InteractivePolinomial BaseLine Correction";          

       }
       ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
       /// \brief GIFTSBaseLineCorrection::GIFTSBaseLineCorrection
       /// \param task
       ///
       GIFTSBaseLineCorrection::GIFTSBaseLineCorrection(TaskOptionsParameters task)
       {
           m_currentdata = task;
           m_currentdata.m_task_name = "GIFT BaseLine Correction";
       }
       ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
       /// \brief GIFTSBaseLineCorrection::calculate
       /// \param param
       /// \param values
       /// \param currentPoints
       /// \param currentPointsBelow
       /// \param option
       /// \param CorrectionFunctions
       ///
       void  GIFTSBaseLineCorrection::calculate
       (
               TaskOptionsParameters & param,
               vector<double> & values,
               std::vector<NDUV::Point> currentPoints,
               std::vector<NDUV::Point> currentPointsBelow,
               int option,
               vector<pair<mat,double>> &CorrectionFunctions
       )
       {
            mat  CorrectionFunction;
            if(currentPointsBelow.size() > 2)
            {

                ApplyFunction(FunctionLeastSquareFitLine,param,values,currentPointsBelow,option);

                param.m_fitParameters.ai.print("GFTS current ai = ");
                int countabove = 0;
                int countbelow = 0;
                currentPoints = currentPointsBelow;
                currentPointsBelow.clear();
                for(int i = 0; i < (int)currentPoints.size() && i < (int)param.m_fitParameters.Yxi.size(); i++)
                {

                        if(currentPoints[i].y > param.m_fitParameters.Yxi[i])
                        {
                            countabove++;
                        }
                        else
                        {
                            currentPointsBelow.push_back(currentPoints[i]);
                            countbelow++;
                        }

                }

                double value = 1000000.0;
                if( countbelow != 0)
                {
                     value = (double)countabove / (double)countbelow;
                     cout << "coutabove = " << countabove << "   coutbelow = " <<countbelow << " value="<< value << endl;
                }
                if( countabove != 0 )
                {

                    CorrectionFunctions.push_back(pair<mat,double>(param.m_CorrectionFunction.second,value));
                    calculate(param,values,currentPoints, currentPointsBelow,option,CorrectionFunctions);
                }
            }
            else
            {
                       param.m_CorrectionFunction.first = mat(1,(int)currentPoints.size());
                       param.m_CorrectionFunction.first.zeros();
                       CorrectionFunction = mat(1,(int)currentPoints.size());
                       CorrectionFunction.zeros();

            }

             double min =-1.0;
             if(CorrectionFunctions.size()>0)
             {
                    min = CorrectionFunctions[0].second;
             }


             for_each(CorrectionFunctions.begin(),CorrectionFunctions.end(),
                        [&min,&CorrectionFunction](pair<mat,double> x)
             {
                    if(x.second <= min)
                    {
                        min = x.second;
                        CorrectionFunction = x.first;
                    }
             });

             param.m_CorrectionFunction.second = CorrectionFunction;
       }
       ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
       /// \brief GIFTSBaseLineCorrection::Run
       /// \param statistic
       ///
       void GIFTSBaseLineCorrection::Run(Statistic & statistic)
       {
           std::string functionname;
           if(FunctionTypesMap.find(m_currentdata.m_fitParameters.functionType) != FunctionTypesMap.end())
           {
                functionname = FunctionTypesMap.at(m_currentdata.m_fitParameters.functionType);
           }
           cout << "START Function Name = "<<  m_currentdata.m_task_name  << " Function = " << functionname << endl;
           std::vector<NDUV::Point> points;
           sort(m_currentdata.m_fitParameters.m_Xpoints.begin(),m_currentdata.m_fitParameters.m_Xpoints.end());

           mat CorrectionFunctions = mat((int)statistic.currentPopulationMatrix.n_rows,(int)m_currentdata.m_fitParameters.m_Xpoints.size());

           FitParameters currentfitParameters = m_currentdata.m_fitParameters;
           mat beforeCorrection = statistic.currentPopulationMatrix;

           if((int)statistic.currentPopulationMatrix.n_elem > 0)
           {
                 for(int i =0;i < (int)statistic.currentPopulationMatrix.n_rows;i++)
                 {
                      m_currentdata.m_CorrectionFunction = pair<mat,mat>(mat(0,0),mat(0,0));
                      m_currentdata.m_fitParameters = currentfitParameters;

                      vector<pair<mat,double>> CorrectionFunctionVec;
                      vector<double> sample =  Statistic::convToStd( statistic.currentPopulationMatrix.row(i));
                      points = m_currentdata.selectNPoints( m_currentdata.m_fitParameters.m_Xpoints,i,statistic.currentPopulationMatrix,0,m_currentdata.m_fitParameters.functionType);
                      vector<Point>  currentPoints = points;

                      calculate(m_currentdata,sample,points, currentPoints,1,CorrectionFunctionVec);
                      if((int)CorrectionFunctions.row(i).n_cols == (int)(rowvec(m_currentdata.m_CorrectionFunction.second).n_cols))
                         CorrectionFunctions.row(i) = rowvec(m_currentdata.m_CorrectionFunction.second);
                      else
                          break;

                      ApplyFunction(FunctionLeastSquareFitLine,m_currentdata,sample, points,2);

                      statistic.currentPopulationMatrix.row(i) = rowvec(sample);
                 }
                 m_currentdata.m_CorrectionFunction.second = CorrectionFunctions;

                 m_plot->Show = false;
                 m_plot->ShowCorrected(beforeCorrection, statistic.currentPopulationMatrix,m_currentdata);
                 m_plot->Show = false;
             }

             cout << "START Function Name = "<<  m_currentdata.m_task_name  << " Function = " << functionname << endl;
       }


       cx_vec DFT(colvec function)
       {
           double PI = 3.14159265;
           int N;
           N = (int)function.n_rows;
          vec ifftAR = vec(N/2);
          ifftAR.zeros();

          vec ifftAI = vec(N/2);
          ifftAI.zeros();

           for(int a=0;a< N/2;a++)
           {
                  for(int b=0;b< N - 1;b++)
                  {
                      ifftAR(a) = ifftAR(a) + (function(b) * cos(   (2 * PI * a * b)/N   ))  ;
                      ifftAI(a) = ifftAI(a) - (function(b) * sin(   (2 * PI * a * b)/N   ))  ;
                  }
           }

           ifftAR.print("R=");
           ifftAI.print("I=");
           return cx_vec(ifftAR,ifftAI);
       }
       colvec IDFT(vec ifftAR,vec ifftAI)
       {

           double PI = 3.14159265;
           int N= (int)ifftAR.n_rows * 2;

          colvec tempinv = colvec(N);
          tempinv.zeros();
           // Inverse
           for(int a=0;a< N/2;a++)
           {
                  for(int b=0;b< N - 1;b++)
                  {
                      tempinv(b) = tempinv(b) + (ifftAR(a) * cos(   (2 * PI * a * b)/N   ))  ;
                      tempinv(b) = tempinv(b) + (ifftAI(a) * sin(   (2 * PI * a * b)/N   ))  ;
                  }
           }
           tempinv.print("ROWINVErse= ");
           return tempinv;
       }
       //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
       /// \brief DataSmoothing::Run
       /// \param statistic
       ///
       void  DataSmoothing::Run(Statistic & statistic)
       {
            cout << "START Function Name = "<<  m_currentdata.m_task_name  << endl;

           if((int)statistic.currentPopulationMatrix.n_elem > 0)
           {
                 DisplaySpectrumData(statistic.currentPopulationMatrix);

                 mat beforeCorrection = statistic.currentPopulationMatrix;
                 for(int i =0;i < (int)statistic.currentPopulationMatrix.n_rows;i++)
                 {

                     m_currentdata.m_dataSmoothingParameters->inputSpectrum =  Statistic::convToStd( statistic.currentPopulationMatrix.row(i));
                     switch(m_currentdata.m_dataSmoothing)
                     {
                           case BINOMIAL:

                             if(i ==  0)
                             {
                                     ApplyFunction(static_cast<BinomialSmoothing*>(this)->BinomialSmoothingFunction,m_currentdata,1);
                             }
                             ApplyFunction(static_cast<BinomialSmoothing*>(this)->BinomialSmoothingFunction,m_currentdata,2);
                           break;
                           case SAVITZJY_GOLAY:
                             if(i ==  0)
                             {
                                  ApplyFunction(static_cast<SavitzkyGolaySmoothing*>(this)->SavitzkySmoothingFunction,m_currentdata,1);

                             }
                             ApplyFunction(static_cast<SavitzkyGolaySmoothing*>(this)->SavitzkySmoothingFunction,m_currentdata,2);
                           break;
                           case NONE_SMOOTHING:
                           break;
                     };

                     if((int)m_currentdata.m_dataSmoothingParameters->outputSpectrum.second.size() > 0)
                     {
                         statistic.currentPopulationMatrix.row(i).zeros();
                        ( statistic.currentPopulationMatrix.row(i)).cols(0,(int)m_currentdata.m_dataSmoothingParameters->outputSpectrum.second.size() - 1) = m_currentdata.m_dataSmoothingParameters->outputSpectrum.second;
                     }

                 }

                 if((int)m_currentdata.m_dataSmoothingParameters->outputSpectrum.second.size() > 0)
                 {
                      statistic.currentPopulationMatrix = (statistic.currentPopulationMatrix.rows(0,statistic.currentPopulationMatrix.n_rows - 1)).cols(0,(int)(int)m_currentdata.m_dataSmoothingParameters->outputSpectrum.second.size() - 1);
                 }
                 else
                 {
                     statistic.currentPopulationMatrix = mat(m_currentdata.numOfSamples,(int)m_currentdata.m_currentValuesOfX.size());
                     m_currentdata.m_dataSmoothingParameters->outputSpectrum.first = rowvec(m_currentdata.m_currentValuesOfX);
                     m_currentdata.m_dataSmoothingParameters->outputSpectrum.second = rowvec(m_currentdata.m_currentValuesOfX);

                     statistic.currentPopulationMatrix.zeros();
                     m_currentdata.m_dataSmoothingParameters->outputSpectrum.second.zeros();
                 }

                  DisplaySpectrumData(statistic.currentPopulationMatrix);
                  m_plot->ShowCorrected(beforeCorrection, statistic.currentPopulationMatrix,m_currentdata);


           }
           cout << "FINISH Function Name = "<<  m_currentdata.m_task_name  << endl;
       }

       ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
       /// \brief BinomialSmoothing::BinomialSmoothing
       /// \param task
       ///
       BinomialSmoothing::BinomialSmoothing(TaskOptionsParameters task)
       {
           m_currentdata = task;
           m_currentdata.m_task_name =  "BinomialSmoothing";

           if(m_currentdata.m_dataSmoothingParameters == nullptr)
           {
               m_currentdata.m_dataSmoothingParameters = new BinomialFit(*defaultParametersForBinomial);
           }
       }

       /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
       /// \brief SavitzkyGolaySmoothing::SavitzkyGolaySmoothing
       /// \param fit
       ///
       SavitzkyGolaySmoothing::SavitzkyGolaySmoothing(TaskOptionsParameters task)
       {
           m_currentdata = task;
           m_currentdata.m_task_name = "SavitzkyGolaySmoothing";

           if(m_currentdata.m_dataSmoothingParameters == nullptr)
           {
               m_currentdata.m_dataSmoothingParameters = new SavitzkyFit(*defaultParametersForSavitzkyGolaySmoothing);
           }
       }

       /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
       /// \brief DerivativeSpectra::DerivativeSpectra
       /// \param task
       ///
        DerivativeSpectra::DerivativeSpectra(TaskOptionsParameters task)
        {
             m_currentdata = task;
             m_currentdata.m_task_name = "Derivative Task";
        }

       //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
       /// \brief DerivativeSpectra::Run
       ///
       void DerivativeSpectra::Run(Statistic & statistic)
       {
           cout << "START Function Name = "<< m_currentdata.m_task_name  << " Derivative Order = " << ((SavitzkyFit*) m_currentdata.m_derivativeParameters)->derivativeOrder << endl;

           if((int)statistic.currentPopulationMatrix.n_elem > 0)
           {
                 mat beforeCorrection = statistic.currentPopulationMatrix;

                 for(int i =0;i < (int)statistic.currentPopulationMatrix.n_rows;i++)
                 {
                      m_currentdata.m_derivativeParameters->inputSpectrum =  Statistic::convToStd( statistic.currentPopulationMatrix.row(i));

                     ApplyFunction(DerivativeFunction ,m_currentdata);

                     if((int)m_currentdata.m_derivativeParameters->outputSpectrum.second.size() > 0)
                     {
                         statistic.currentPopulationMatrix.row(i).zeros();
                        ( statistic.currentPopulationMatrix.row(i)).cols(0,(int)m_currentdata.m_derivativeParameters->outputSpectrum.second.size() - 1) = m_currentdata.m_derivativeParameters->outputSpectrum.second;
                     }
                 }

                 if((int)m_currentdata.m_derivativeParameters->outputSpectrum.second.size() > 0)
                 {
                      statistic.currentPopulationMatrix = (statistic.currentPopulationMatrix.rows(0,statistic.currentPopulationMatrix.n_rows - 1)).cols(0,(int)(int)m_currentdata.m_derivativeParameters->outputSpectrum.second.size() - 1);
                 }
                 else
                 {
                     statistic.currentPopulationMatrix = mat(m_currentdata.numOfSamples,(int)m_currentdata.m_currentValuesOfX.size());
                     m_currentdata.m_derivativeParameters->outputSpectrum.first = rowvec(m_currentdata.m_currentValuesOfX);
                     m_currentdata.m_derivativeParameters->outputSpectrum.second = rowvec(m_currentdata.m_currentValuesOfX);

                     statistic.currentPopulationMatrix.zeros();
                     m_currentdata.m_derivativeParameters->outputSpectrum.second.zeros();
                 }

                 m_plot->ShowCorrected(beforeCorrection, statistic.currentPopulationMatrix,m_currentdata);

           }
           cout << "FINISH Function Name = "<< m_currentdata.m_task_name << " Derivative Order = " << ((SavitzkyFit*) m_currentdata.m_derivativeParameters)->derivativeOrder << endl;
       }
       ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
       MeanCenteringMethod::MeanCenteringMethod(TaskOptionsParameters task)
       {
          m_currentdata = task;
          m_currentdata.m_task_name =   "Mean Centering Method";
       }
       ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
       /// \brief MeanCenteringMethod::Run
       ///
       void MeanCenteringMethod::Run(Statistic & statistic)
       {
           cout << "Start Function Name = "<<  m_currentdata.m_task_name << endl;

           mat spectraBefore = statistic.currentPopulationMatrix;
           mat concentrationsBefore = statistic.currentConcentrationMatrix;

           setCurrentPopulationOfSamples( statistic);

          if(statistic.currentPopulationOfSamples.count() <=0)
          {
              cout << "Error "<< endl;
              return ;
          }

           pair<mat,mat> meanCenteredData;

           statistic.mean();
           statistic.stddev();
           statistic.corelationMatrix();
           statistic.covarienceMatrix();

           meanCenteredData = statistic.substractmean();
           statistic.currentPopulationMatrix = meanCenteredData.first;
           statistic.currentConcentrationMatrix = meanCenteredData.second;

           m_plot->Show = false;
           m_plot->ShowCorrected( spectraBefore, statistic.currentPopulationMatrix,concentrationsBefore,statistic.currentConcentrationMatrix,m_currentdata);

           cout << "Finish Function Name = "<< m_currentdata.m_task_name << endl;
       };

       ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
       /// \brief UnivariateCalibration::UnivariateCalibration
       /// \param task
       ///
       UnivariateCalibration::UnivariateCalibration(TaskOptionsParameters task)
       {
              m_currentdata = task;
              m_currentdata.m_task_name =  "Univariate Calibration";

       }
       void  UnivariateCalibration::testFilters2()
       {
           Filter filter;

           vector<FilterParameters> filterParameters =
           {
                {0,BPF,190,50,(int)m_currentdata.m_currentValuesOfX.size(),m_currentdata.m_currentValuesOfX[0],m_currentdata.m_currentValuesOfX[(int)m_currentdata.m_currentValuesOfX.size() - 1]},
                {1,BPF,230,20,(int)m_currentdata.m_currentValuesOfX.size(),m_currentdata.m_currentValuesOfX[0],m_currentdata.m_currentValuesOfX[(int)m_currentdata.m_currentValuesOfX.size() - 1]},
                {2,BPF,280,10,(int)m_currentdata.m_currentValuesOfX.size(),m_currentdata.m_currentValuesOfX[0],m_currentdata.m_currentValuesOfX[(int)m_currentdata.m_currentValuesOfX.size() - 1]},
                {3,BPF,340,10,(int)m_currentdata.m_currentValuesOfX.size(),m_currentdata.m_currentValuesOfX[0],m_currentdata.m_currentValuesOfX[(int)m_currentdata.m_currentValuesOfX.size() - 1]}
           };

           vector<pair<mat,mat>> populationAndCorrection;

           for(int i = 0;i<(int)filterParameters.size();i++)
           {

               pair<vector<double> ,vector<double>> sample = pair<vector<double> ,vector<double>>({},  Statistic::convToStd(m_currentdata.m_currentPopulationMatrix.row(1)));
               filter.DesignFilter(filterParameters[i],m_currentdata.m_currentValuesOfX);
               pair<mat,mat> rowfilter = filter.GetFilter();
               ApplyFunction(filter.Multiplysample ,sample, rowfilter,m_currentdata.m_currentValuesOfX,"");

               //uncomment to see each filter seperate
               populationAndCorrection.push_back(pair<mat,mat>( rowvec(m_currentdata.m_currentValuesOfX), m_currentdata.m_currentPopulationMatrix.row(1)));
               populationAndCorrection.push_back(pair<mat,mat>( rowvec(sample.first),rowvec(sample.second)));
               populationAndCorrection.push_back(pair<mat,mat>( rowfilter.first,  rowfilter.second));

               m_plot->DisplayPlot( populationAndCorrection,1,{std::make_tuple<vector<int>,vector<double>,vector<string>>({},{},{ m_currentdata.m_task_name})});
               populationAndCorrection.clear();
           }
       }

        void  UnivariateCalibration::testFilters1()
        {
            Filter filter;

            vector<FilterParameters> filterParameters =
            {
                 {0,BPF,190,50,(int)m_currentdata.m_currentValuesOfX.size(),m_currentdata.m_currentValuesOfX[0],m_currentdata.m_currentValuesOfX[(int)m_currentdata.m_currentValuesOfX.size() - 1]},
                 {1,BPF,230,20,(int)m_currentdata.m_currentValuesOfX.size(),m_currentdata.m_currentValuesOfX[0],m_currentdata.m_currentValuesOfX[(int)m_currentdata.m_currentValuesOfX.size() - 1]},
                 {2,BPF,280,15,(int)m_currentdata.m_currentValuesOfX.size(),m_currentdata.m_currentValuesOfX[0],m_currentdata.m_currentValuesOfX[(int)m_currentdata.m_currentValuesOfX.size() - 1]},
                 {3,BPF,340,10,(int)m_currentdata.m_currentValuesOfX.size(),m_currentdata.m_currentValuesOfX[0],m_currentdata.m_currentValuesOfX[(int)m_currentdata.m_currentValuesOfX.size() - 1]},
            };


            vector<pair<mat,mat>> populationAndCorrection;
            mat output = mat(1 + (int)filterParameters.size(),(int)m_currentdata.m_currentPopulationMatrix.n_cols);
            output.zeros();
            output.row(0) = m_currentdata.m_currentPopulationMatrix.row(1);
            pair<mat,mat> filterFrequencyResponse = pair<mat,mat>(mat(filterParameters.size(),(int)m_currentdata.m_currentValuesOfX.size()),mat(filterParameters.size(),(int)m_currentdata.m_currentValuesOfX.size()));

            for(int i = 0;i<(int)filterParameters.size();i++)
            {

                    pair<vector<double> ,vector<double>> sample = pair<vector<double> ,vector<double>>({},  Statistic::convToStd(m_currentdata.m_currentPopulationMatrix.row(1)));

                    filter.DesignFilter(filterParameters[i]);
                    pair<mat,mat> rowfilter = filter.GetFilter();
                    ApplyFunction(filter.Multiplysample ,sample, rowfilter,m_currentdata.m_currentValuesOfX,"");
                    output.row(i + 1) = rowvec(sample.second);
                    filterFrequencyResponse.first.row(i) = rowfilter.first;
                    filterFrequencyResponse.second.row(i) = rowfilter.second;
                    getResonanceFrequency(rowfilter);

                    //uncomment to see each filter seperate
                    populationAndCorrection.push_back(pair<mat,mat>( rowvec(m_currentdata.m_currentValuesOfX),output.row(0)));
                    populationAndCorrection.push_back(pair<mat,mat>( rowvec(m_currentdata.m_currentValuesOfX),output.rows(i+1,i+1)));
                    populationAndCorrection.push_back(pair<mat,mat>( rowfilter.first,  rowfilter.second));

                    m_plot->DisplayPlot( populationAndCorrection,1,{std::make_tuple<vector<int>,vector<double>,vector<string>>({},{},{ m_currentdata.m_task_name})});
                    populationAndCorrection.clear();

                // to see filter in one screen
            }

            populationAndCorrection.push_back(pair<mat,mat>( rowvec(m_currentdata.m_currentValuesOfX),output.row(0)));
            populationAndCorrection.push_back(pair<mat,mat>( rowvec(m_currentdata.m_currentValuesOfX),output));
            populationAndCorrection.push_back(pair<mat,mat>( filterFrequencyResponse.first.row(0),filterFrequencyResponse.second));

            m_plot->DisplayPlot( populationAndCorrection,1,{std::make_tuple<vector<int>,vector<double>,vector<string>>({},{},{ m_currentdata.m_task_name})});
            populationAndCorrection.clear();

        }
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief UnivariateCalibration::polinomialInterpolation
        ///
        void UnivariateCalibration::polinomialInterpolation(pair<rowvec,rowvec> sample,vector<int> polinomialDegrees)
        {
            pair<mat,mat> output = pair<mat,mat>(mat((int)polinomialDegrees.size() + 1 ,(int)sample.second.n_cols),mat((int)polinomialDegrees.size() +1 ,(int)sample.second.n_cols));
            output.first.zeros();
            output.second.zeros();
            output.second.row(0) = sample.second;
            std::pair<double,double> pointsRange;
            pointsRange.first = 0;//sample.first(0);
            pointsRange.second = sample.second.n_cols;//sample.first(sample.first.n_cols);
            for(int a = 0; a < (int)polinomialDegrees.size() + 1;a++)
            {
                for(int j = pointsRange.first; j < pointsRange.second;j++)
                {
                         output.first(a,j) = j;
                }
            }
            for(int a = 0; a < (int)polinomialDegrees.size();a++)
            {
                int polynomialDegree = polinomialDegrees[a];

                mat Vandermonde = mat( (pointsRange.second - pointsRange.first) ,polynomialDegree + 1);
                for(int j = pointsRange.first; j < pointsRange.second;j++)
                {
                         for(int i=0;i < polynomialDegree + 1;i++)
                         {
                             Vandermonde(j,i) = pow(j,i);
                         }
                 }

                 Vandermonde.print("V=");
                 if(polynomialDegree != 0)
                 {
                     mat curveFitCoefficients  = pinv(Vandermonde.t() * Vandermonde) * Vandermonde.t() * sample.second.t();
                     curveFitCoefficients = curveFitCoefficients.t();
                     //curveFitCoefficients.print("C=");

                      //output.first.row(a+1).print("X=");

                     /* for(int j = 0;j < (int)curveFitCoefficients.n_cols && j < (int)output.first.row(a+1).n_cols;j++)
                         {
                            cout << j << "="<< output.second.row(a+1)(j) + curveFitCoefficients(0,j) * pow(output.first.row(a+1)(j),j) << endl;
                            output.second.row(a+1)(j) =  output.second.row(a+1)(j) + curveFitCoefficients(0,j) * pow(output.first.row(a+1)(j),j);
                         }*/
                      for(int i = 0;i<(int)output.first.row(a+1).n_cols;i++)
                      {
                          for(int j = 0;j < (int)curveFitCoefficients.n_cols ;j++)
                          {
                               output.second.row(a+1)(i) =  output.second.row(a+1)(i) + curveFitCoefficients(0,j) * pow(output.first.row(a+1)(i),j);
                          }
                      }
                      //output.second.row(a+1).print("O=");
                 }
                 else
                 {
                     output.second.row(a) = sample.second;
                 }

            }
           // output.first.print("X=");
           // output.second.print("Y=");

             vector<pair<  mat,mat >> func;
             func.push_back(pair<mat,mat>( output.first.row(0),output.second.row(0)));
             func.push_back(pair<mat,mat>( output.first.row(0),output.second));
             m_plot->ShowFunction(func , m_currentdata);
             func.clear();
        }

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief UnivariateCalibration::getFilteredData
        /// \param statistic
        ///
        void UnivariateCalibration::getFilteredData(const Statistic & statistic)
        {
            // testFilters1();
            // testFilters2();
            vector<pair<  mat,mat >> func;
            for(auto m: m_currentdata.m_filterMap)
            {
                       vector<Filter> filters = m.second;
                       mat output = mat(1 + (int)filters.size(),(int)m_currentdata.m_currentPopulationMatrix.n_cols);
                       output.zeros();

                       pair<mat,mat> filterFrequencyResponse = pair<mat,mat>(mat(filters.size(),(int)m_currentdata.m_currentValuesOfX.size()),mat(filters.size(),(int)m_currentdata.m_currentValuesOfX.size()));

                       vector<vector<   pair<  vector<double>,vector<double> >   >  > filterRangeSpectra;
                       for(int j =0; j < (int)filters.size();j++)
                       {
                           vector<   pair<  vector<double>,vector<double> >   > constituteFilteredSpectra;
                           pair<mat,mat> rowfilter = filters[j].GetFilter();
                           for(int i = 0;i < (int)statistic.currentPopulationMatrix.n_rows;i++)
                           {
                               output.row(0) = m_currentdata.m_currentPopulationMatrix.row(i);
                               pair<vector<double> ,vector<double>> sample = pair<vector<double> ,vector<double>>({},  Statistic::convToStd(m_currentdata.m_currentPopulationMatrix.row(i)));  // change to row(i)
                               ApplyFunction(filters[j].Multiplysample ,sample, rowfilter,m_currentdata.m_currentValuesOfX,"");

                               output.row(j + 1) = rowvec(sample.second);
                               filterFrequencyResponse.first.row(j) = rowfilter.first;
                               filterFrequencyResponse.second.row(j) = rowfilter.second;

                                //uncomment to see each filter seperate
                               //func.push_back( rowvec(m_currentdata.m_currentValuesOfX),output.row(0));
                               //func.push_back(  rowvec(m_currentdata.m_currentValuesOfX),output.rows(j+1,j+1));
                              // func.push_back( rowfilter.first,  rowfilter.second);
                              // m_plot->ShowFunction(func , m_currentdata);
                              // func.clear();

                                ApplyFunction(filters[j].ScaleSample ,sample);

                                constituteFilteredSpectra.push_back(sample);
                           }
                           /*for(int h=0;h<1;h++)
                           {
                               cout << rowvec(constituteFilteredSpectra[h].first) << " ";
                           }
                           cout << endl;*/
                           filterRangeSpectra.push_back(constituteFilteredSpectra);
                       }
                       //func.push_back( rowvec(m_currentdata.m_currentValuesOfX), m_currentdata.m_currentPopulationMatrix.row(i));
                      // func.push_back(  rowvec(m_currentdata.m_currentValuesOfX),output.rows(1,output.n_rows - 1));
                      // func.push_back( pair<mat,mat>( filterFrequencyResponse.first.row(0),filterFrequencyResponse.second));
                      // m_plot->ShowFunction(func , m_currentdata);
                      // func.clear();
                       // Filtered data are now in m_filteredScaledSpectrum


                        vector<pair<mat,mat> > constituteFilteredData;
                        for(int x = 0; x < (int)filterRangeSpectra.size(); x++)
                        {
                            pair<mat,mat> rangespectra( rowvec(filterRangeSpectra[x][0].first), mat( (int)filterRangeSpectra[x].size(),(int)filterRangeSpectra[x][0].first.size() )  );
                            rangespectra.second.zeros();

                            for(int a = 0;a < (int)filterRangeSpectra[x].size();a++)
                            {
                                int min = std::min((int)rangespectra.second.row(a).n_cols - 1,(int)filterRangeSpectra[x][a].second.size() - 1);
                                rangespectra.second.row(a).cols(0,min) = (rowvec(filterRangeSpectra[x][a].second)).cols(0,min);
                            }
                            constituteFilteredData.push_back(rangespectra);
                        }
                        m_filteredScaledSpectrum[m.first] = constituteFilteredData;
                   }
                    // To display filtered data uncomment

                    for(auto constitute : m_filteredScaledSpectrum)
                    {
                        for(auto filter: constitute.second)
                        {
                           
                             func.push_back(pair<mat,mat>( filter.first,filter.second));
                        }
                    }
                    m_plot->ShowFunction(func , m_currentdata);
                   func.clear();
        }
       ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
       /// \brief UnivariateCalibration::Run
       ///
       void UnivariateCalibration::Run(Statistic & statistic)
       {
          cout << "Start Function Name = "<< m_currentdata.m_task_name << endl;

          vector<int> polynomialDegrees = {1,2,3,4,5};

          if((int)statistic.currentPopulationMatrix.n_elem > 0)
          {
                    mat spectraBefore = statistic.currentPopulationMatrix;
                    getFilteredData(statistic);
                    vector<pair<  mat,mat >> func;
                    for(auto constitute : m_filteredScaledSpectrum)
                    {
                         for(auto filter: constitute.second)
                         {
                             for(int  i = 0 ;i < (int)filter.second.n_rows; i++)
                             {
                                   func.push_back(pair<rowvec,rowvec>( filter.first,filter.second.row(i)));
                                   //populationAndCorrection.push_back(pair<rowvec,rowvec>( filter.first,filter.second.row(i)));
                                  // m_plot->DisplayPlots( populationAndCorrection,1,std::make_tuple<vector<int>,vector<double>,vector<string>>({},{},{ m_currentdata.m_task_name}));
                                  // populationAndCorrection.clear();
                                   polinomialInterpolation(pair<rowvec,rowvec>(filter.first,filter.second.row(i)),polynomialDegrees);

                             }
                         }
                    }
                    m_plot->ShowFunction(func , m_currentdata);
          }

          vector<Stat> bestFitCalibrationRecalculated;
          vector<Optimization> bestFitDecompozition;

           switch(m_currentdata.m_algorithmType)
           {
               case NIPALS_ALGORITHM:

                   ApplyFunction(statistic.NipalsFunction,statistic,statistic);
                   //statistic.ParamPrint( statistic.numberOfPcaComponents,NIPALS_ALGORITHM);
                   break;
                case DECOMPOSITION_ALGORITHM:

                   ApplyFunction(statistic.DecompozitionOfVarCovMatAlgorithm,statistic,statistic);
                   //statistic.ParamPrint( statistic.numberOfPcaComponents,DECOMPOSITION_ALGORITHM);

                  break;
                case LIBPCA:
                      ApplyFunction(statistic.LibpcaAlgorithm,statistic,statistic);
                      //statistic.ParamPrint(  statistic.numberOfPcaComponents,LIBPCA);
                   break;
                default:
                      ApplyFunction(statistic.LibpcaAlgorithm,statistic,statistic);
                   break;

           };

           bestFitDecompozition = statistic.EvaluatePCADecompozitionModels(statistic.m_OptimizationParameters);
           statistic.PrintEvaluatedPCADecompozitionModels(bestFitDecompozition);

           statistic.step2PCR(statistic.errrorsStat,statistic);

           statistic.Validate(  statistic,statistic);
           statistic.m_bestFitCalibration = statistic.sortCalibrationModels(statistic.CalibrationStat);
           statistic.printPCAModels( statistic.m_bestFitCalibration);
           statistic.printRecreatedConcentratios(statistic,1,statistic.m_bestFitCalibration);
           cout << endl;


            m_plot->ShowRecreatedConcentrations
           (
                   statistic.currentConcentrationMatrix,
                   statistic.C_RecreatedConcentrations[statistic.m_bestFitCalibration[0].getIndex()],
                   mat(0,0),
                   mat(0,0),
                   statistic.C_RecreatedConcentrations,
                   {},
                   statistic.m_bestFitCalibration[0].getIndex(),
                   statistic.currentPopulationMatrix,
                   statistic.B_calibrationCofficients,0,statistic.numberOfPcaComponents,
                   //options 0 will not display anything
                   2,1,1,
                   statistic,
                   m_currentdata

           );

             cout << "Finish Function Name = "<< m_currentdata.m_task_name  << endl;

       }
       //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
       /// \brief MultivariateCalibration::MultivariateCalibration
       /// \param task
       ///
       MultivariateCalibration::MultivariateCalibration(TaskOptionsParameters task)
       {
              m_currentdata = task;
              m_currentdata.m_task_name = " Multivariate Calibration";
       }
       //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
       /// \brief MultivariateCalibration::Run
       ///
       void MultivariateCalibration::Run(Statistic & statistic)
       {
           if( statistic.currentConcentrationMatrix.n_elem == 0 ||  statistic.currentPopulationMatrix.n_elem == 0)
           {
               cout << "Error PopulationMatrix Or Concentration Matrix are empty exiting the program."<<endl;
               return;
           }
           cout << "Start Function Name = "<<   m_currentdata.m_task_name  << endl;

           vector<Stat> bestFitCalibrationRecalculated;
           vector<Optimization> bestFitDecompozition;
           switch(m_currentdata.m_algorithmType)
           {
                case NIPALS_ALGORITHM:

               ApplyFunction(statistic.NipalsFunction,statistic,statistic);

               //statistic.ParamPrint( statistic.numberOfPcaComponents,NIPALS_ALGORITHM);
               break;
            case DECOMPOSITION_ALGORITHM:

               ApplyFunction(statistic.DecompozitionOfVarCovMatAlgorithm,statistic,statistic);
               //statistic.ParamPrint( statistic.numberOfPcaComponents,DECOMPOSITION_ALGORITHM);

              break;
            case LIBPCA:
                  ApplyFunction(statistic.LibpcaAlgorithm,statistic,statistic);
                  //statistic.ParamPrint(  statistic.numberOfPcaComponents,LIBPCA);
               break;
            default:
                  ApplyFunction(statistic.LibpcaAlgorithm,statistic,statistic);
               break;
           };

       //bestFitDecompozition = statistic.EvaluatePCADecompozitionModels(statistic.m_OptimizationParameters);
       //statistic.PrintEvaluatedPCADecompozitionModels(bestFitDecompozition);

       statistic.step2PCR(statistic.errrorsStat,statistic);
       //statistic.ReconstituteSPectrum(statistic);
       statistic.Validate(  statistic,statistic);
       statistic.m_bestFitCalibration = statistic.sortCalibrationModels(statistic.CalibrationStat);
       statistic.printPCAModels( statistic.m_bestFitCalibration);
       //statistic.printRecreatedConcentratios(statistic,1,statistic.m_bestFitCalibration);

       cout << "###########################################################################################################################"<<endl;

       if(statistic.m_bestFitCalibration[0].RMSEAVERAGE <= 1.79)
       {
         m_plot->Show = true;
         m_plot->ShowFunction({{rowvec(m_currentdata.m_currentValuesOfX),m_currentdata.m_currentPopulationMatrix }}, m_currentdata);
       }
       m_plot->Show = false;

       m_plot->ShowRecreatedConcentrations
           (
                   statistic.currentConcentrationMatrix,
                   statistic.C_RecreatedConcentrations[statistic.m_bestFitCalibration[0].getIndex()],
                   mat(0,0),
                   mat(0,0),
                   statistic.C_RecreatedConcentrations,
                   {},
                   statistic.m_bestFitCalibration[0].getIndex(),
                   statistic.currentPopulationMatrix,
                   statistic.B_calibrationCofficients,0,statistic.numberOfPcaComponents,
                   //options 0 will not display anything
                   2,1,1,
                   statistic,
                   m_currentdata
           );
           cout << "Finish Function Name = "<< m_currentdata.m_task_name  << endl;
       }

       ///////////////////////////////////////////////////////////////////////////////////////////////////////////////
       /// \brief Validation::Validation
       /// \param valtype
       ///
        Validation::Validation(TaskOptionsParameters task)
        {
             m_currentdata = task;
             m_currentdata.m_task_name = "Validation";
        }

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Validation::Run
        /// \param statistic
        ///
       void  Validation::Run(Statistic & statistic)
        {
           if( statistic.currentConcentrationMatrix.n_elem == 0 ||  statistic.currentPopulationMatrix.n_elem == 0 || m_currentdata.m_saved_model.B_calibrationCofficients.size() <= 0)
           {
               cout << "Error PopulationMatrix Or Concentration Matrix are empty exiting the program."<<endl;
               return;
           }
           cout << "Start Function Name = "<< m_currentdata.m_task_name << endl;
           if( m_currentdata.m_algorithmType == NO_ALGORITHM_TYPE)
           {
               cout << "There was no calibration performed fot validation "<< endl;
               return;
           }


            vector<Stat> bestFitValidation;
            vector<Stat> bestFitValidationRecalculated;

            statistic.B_calibrationCofficients = m_currentdata.m_saved_model.B_calibrationCofficients;
            statistic.F_pcaFactors = m_currentdata.m_saved_model.F_pcaFactors;
            statistic.numberOfPcaComponents = m_currentdata.m_saved_model.numberOfPcaComponents;
            statistic.errrorsStat = m_currentdata.m_saved_model.errrorsStat;
            statistic.Concentration_WithUnknown = vector<mat>((int)statistic.numberOfPcaComponents,statistic.currentConcentrationMatrix);
            statistic.C_RecreatedConcentrations = vector<mat>((int)statistic.numberOfPcaComponents,mat(0,0));

            statistic.newcurrentPopulationMatrix.clear();
            for(int a = 0;a < (int)statistic.numberOfPcaComponents;a++)
            {

                 statistic.newcurrentPopulationMatrix.push_back(statistic.currentPopulationMatrix.cols(0,a));

                 statistic.S_pcaScores.push_back(statistic.newcurrentPopulationMatrix[a] * statistic.F_pcaFactors[a].t());
                 statistic.CalibrationStat.push_back(Stat());
            }

            int nsamples = (int)statistic.currentPopulationMatrix.n_rows;
            if(m_currentdata.m_kfolds <= 0)
                  m_currentdata.m_kfolds = 1;
            int delta = m_currentdata.m_kfolds;

            if(delta <= nsamples)
            {
                m_currentdata.m_kfolds = nsamples / delta;
                if(nsamples % delta > 0)
                {
                   m_currentdata.m_kfolds++;
                }
            }
            else
            {
                delta = nsamples;
            }

            switch(m_currentdata.m_validationType)
            {
                case TESTINGSET:
                    m_currentdata.m_task_name = m_currentdata.m_task_name + " : Testing Set Cross Validation";
                    cout << "Testing Set Validation " << endl;
                    statistic.Validate( statistic,m_currentdata.m_saved_model);
                    bestFitValidation = statistic.sortCalibrationModels(statistic.CalibrationStat);
                    statistic.printPCAModels( bestFitValidation);
                    statistic.printRecreatedConcentratios(statistic,1,bestFitValidation);
                    cout << "####################################################################################################################################"<<endl;
                break;
                case CROSS_VALIDATION_LEAVEOUT:
                case  KFOLDCROSSVALIDATION :
                    if(delta == 1)
                    {
                        cout << "Leave One out Cross Validation. Number Of K Folds =  "<< m_currentdata.m_kfolds << endl;
                    }
                    else
                    {
                        cout << "K Fold  Cross Validation. Number Of K Folds = "<< m_currentdata.m_kfolds << endl;
                    }
                     m_currentdata.m_task_name = m_currentdata.m_task_name + " : K Fold Prediction Cross Validation";
                     statistic.m_CrossValidation = vector<ValidationModel>(m_currentdata.m_kfolds,ValidationModel());
                     statistic.CrossValidateKFolds(statistic,m_currentdata.m_saved_model,false,m_currentdata.m_kfolds);
                    // statistic.CreateKFoldPCAModels(statistic,m_currentdata.m_saved_model,false,m_currentdata.m_kfolds);
                    break;
                case NO_VALIDATION:

                break;
            };
            if(bestFitValidation.size() > 0)
            {
                m_plot->ShowRecreatedConcentrations
                (
                            m_currentdata.m_saved_model.currentConcentrationMatrix,
                            m_currentdata.m_saved_model.C_RecreatedConcentrations[bestFitValidation[0].getIndex()],
                            statistic.currentConcentrationMatrix,
                            statistic.C_RecreatedConcentrations[bestFitValidation[0].getIndex()],
                            m_currentdata.m_saved_model.C_RecreatedConcentrations,
                            statistic.C_RecreatedConcentrations,
                            bestFitValidation[0].getIndex(),
                            statistic.currentPopulationMatrix,
                            m_currentdata.m_saved_model.B_calibrationCofficients,0,m_currentdata.m_saved_model.numberOfPcaComponents,
                            //options 0 will not display anything
                            5,3,1,
                            m_currentdata.m_saved_model,
                            m_currentdata
                );
            }
            cout << "Finish Function Name = "<< m_currentdata.m_task_name << endl;
        }
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Prediction::Prediction
        /// \param task
        ///
        Prediction::Prediction(TaskOptionsParameters task)
        {
            m_currentdata = task;
            m_currentdata.m_task_name = "Prediction";
        }
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Prediction::Run
        /// \param statistic
        ///
        void Prediction::Run(Statistic & statistic)
        {
            if( statistic.currentConcentrationMatrix.n_elem == 0 ||  statistic.currentPopulationMatrix.n_elem == 0 )
            {
                cout << "Error PopulationMatrix Or Concentration Matrix are empty exiting the program."<<endl;
                return;
            }
            cout << "Start Function Name = "<< m_currentdata.m_task_name <<  " Start Testing Prediction " <<endl;

           // statistic.B_calibrationCofficients = m_currentdata.m_saved_model.B_calibrationCofficients;
           // statistic.F_pcaFactors = m_currentdata.m_saved_model.F_pcaFactors;
           // statistic.numberOfPcaComponents = m_currentdata.m_saved_model.numberOfPcaComponents;
            //statistic.Concentration_WithUnknown = vector<mat>((int)statistic.numberOfPcaComponents,statistic.currentConcentrationMatrix);

            ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            switch(m_currentdata.m_predictionType)
            {
               case NO_PREDICTION:
                break;
               case TESTINGSETPREDICTION:
                    m_currentdata.m_task_name = m_currentdata.m_task_name + " : Testing Set Prediction.";
                break;
               case LEAVEOUTPREDICTION:
               case KFOLDPREDICTION:
                if((int)statistic.currentPopulationMatrix.n_rows == (int)m_currentdata.m_saved_model.m_CrossValidation.size()  )
                {
                    cout << "Leave One out Cross Validation. Number Of Fold = "<<  (int)statistic.currentPopulationMatrix.n_rows << endl;
                }
                else
                {
                    cout << "K Fold  Cross Validation. Number Of Fold = "<<
                            (int)((bool)((int)statistic.currentPopulationMatrix.n_rows % (m_currentdata.m_saved_model.m_CrossValidation.size())))
                    << endl;
                }
                m_currentdata.m_task_name = m_currentdata.m_task_name + " : K Fold Prediction.";
                if(m_currentdata.m_saved_model.m_CrossValidation.size() > 0)
                {
                        statistic.ReportConcentrations
                        (
                                    statistic,m_currentdata.m_saved_model
                                   // (int)statistic.currentPopulationMatrix.n_rows / (m_currentdata.m_saved_model.m_CrossValidation.size()) +
                                   // (int)((bool)((int)statistic.currentPopulationMatrix.n_rows % (m_currentdata.m_saved_model.m_CrossValidation.size()))),
                                   // m_currentdata.m_saved_model.m_CrossValidation.size(),
                                    //false // not validation

                        );
                 }

                 break;
            };
            ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            vector<pair<mat,mat>> addToDisplay;
            vector<std::tuple<vector<int>,vector<double>,vector<string>>> titles;
            m_plot->Show = true;

            m_plot->ShowPredictedConcentrations
            (
                m_currentdata.m_saved_model,
                statistic,
                m_currentdata
            );
            cout << "Finished Testing Prediction " << endl;
        }
       ////////////////////////////////////////////////////////////////////////////////mean/////////////////////////////////////////////////////////////
       /// \brief getResonanceFrequency
       /// \param filter
       /// \return
       ///
       vector<double> BaseFunction::getResonanceFrequency(pair<rowvec,rowvec> filter)
       {
           double maxA =filter.second(0);
           vector<double> result;

           for(int i = 0;i< (int)filter.second.n_cols;i++)
           {
               if(filter.second(i) > maxA)
               {
                   maxA = filter.second(i);

               }
           }
           for(int i = 0;i< (int)filter.second.n_cols;i++)
           {
               if(filter.second(i) == maxA)
               {
                    result.push_back(filter.first(i));
               }
           }
           cout << "Resonance  Frequency = " << endl;
           for(auto i:result)
           {
               cout << i << " ";
           }
           cout <<endl;
           int i =0;
           for(i=0;i< (int)filter.second.n_cols;i++)
           {
               if(filter.second(i) != 0)
               {
                 // cout << filter.first(i) << " ";
                  break;
               }
           }
           for(;i< (int)filter.second.n_cols;i++)
           {
               if(filter.second(i) == 0)
               {
                  //cout << filter.first(i) << " ";
                  break;
               }
           }
            cout <<endl;
           return result;
       }

     ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
} /* namespace NDUV */
