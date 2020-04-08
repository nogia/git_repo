/*
 * TestOptions.cpp
 *
 *  Created on: May 13, 2016
 *      Author: inna
 */

#include "TestOptions.h"

namespace NDUV
{
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \brief TaskOptionsParameters::TaskOptionsParameters
/// \param itask_name
/// \param preprocessingType
/// \param baseLineCorrection
/// \param dataSmoothing
/// \param derivativeSpectraType
/// \param meanCenteringMethodType
/// \param calibrationType
/// \param algorithmType
/// \param validationType
/// \param fitParameters
/// \param dataSmoothingParameters
/// \param derivativeParameters
/// \param filterMap
/// \param tasksType
/// \param inumOfSamples
/// \param inumOfDataPoints
/// \param inumOfPCA
/// \param numOfSamplesInTestingSet
/// \param numOfDataPointsInTestingSet
/// \param numOfPCAInTestingSet
/// \param currentSet
/// \param constituents
/// \param constituesIndexMap
/// \param testingConsSets
/// \param currentPopulationMatrix
/// \param meanSpectraMatrix
/// \param testingPopulationMatrix
/// \param concentrations
/// \param meanConcentrationMatrix
/// \param testing_concentrations
/// \param correctionFunction
/// \param izeroTransmissionDatapoints
/// \param icurrentValuesOfX
///
    TaskOptionsParameters::TaskOptionsParameters
    (
                           string itask_name                                       ,
                           PreprocessingType      preprocessingType                ,
                           BaseLineCorrectionType baseLineCorrection               ,
                           DataSmoothingType dataSmoothing                         ,
                           pair<DerivativeSpectraType,DerivativeAlgorithmType> derivativeSpectraType             ,
                           MeanCenteringMethodType meanCenteringMethodType         ,
                           CalibrationType calibrationType                         ,
                           AlgorithmType algorithmType                             ,
                           ValidationType validationType                           ,
                           PredictionType predictionType                           ,
                           FitParameters  fitParameters                            ,
                           Fit * dataSmoothingParameters                           ,
                           Fit * derivativeParameters                              ,
                           Filter::FilterMap filterMap                                     ,
                           map<int,TaskT*> tasksType                               ,

                           int inumOfSamples                                       ,
                           int inumOfDataPoints                                    ,
                           int inumOfPCA                                           ,

                           int kfolds                                              ,
                           int numOfSamplesInTestingSet                            ,
                           int numOfDataPointsInTestingSet                         ,
                           int numOfPCAInTestingSet                                ,
                           int currentSet                                          ,

                           map<Constituents,string> constituents                   ,
                           map<Constituents,int>    constituesIndexMap             ,

                           vector<mat> testingConsSets                             ,
                           mat currentPopulationMatrix                             ,
                           mat concentrations                                      ,
                           mat testingPopulationMatrix                             ,
                           mat testingconcentrations                              ,
                           mat meanSpectraMatrix                                   ,
                           mat meanConcentrationMatrix                             ,

                           pair<mat,mat> correctionFunction                        ,
                           vector<double> izeroTransmissionDatapoints              ,
                           vector<double> icurrentValuesOfX
    )
          :
                           m_task_name(itask_name)                                   ,
                           m_preprocessingType(preprocessingType)                    ,
                           m_baseLineCorrection(baseLineCorrection)                  ,
                           m_dataSmoothing(dataSmoothing)                            ,
                           m_derivativeSpectraType(derivativeSpectraType)            ,
                           m_meanCenteringMethodType(meanCenteringMethodType)        ,
                           m_calibrationType(calibrationType)                        ,
                           m_algorithmType(algorithmType  )                          ,
                           m_validationType(validationType)                          ,
                           m_predictionType(predictionType)                          ,
                           m_fitParameters(fitParameters )                           ,
                           m_dataSmoothingParameters(dataSmoothingParameters)        ,
                           m_derivativeParameters(derivativeParameters)              ,
                           m_filterMap( filterMap)                                   ,
                           m_tasksType(tasksType)                                    ,

                           m_kfolds(kfolds)                                          ,
                           numOfSamples(inumOfSamples  )                             ,
                           numOfDataPoints(inumOfDataPoints)                         ,
                           numOfPCA(inumOfPCA )                                      ,
                           m_numOfSamplesInTestingSet(numOfSamplesInTestingSet)      ,
                           m_numOfDataPointsInTestingSet(numOfDataPointsInTestingSet),
                           m_numOfPCAInTestingSet(numOfPCAInTestingSet)              ,
                           m_currentSet(currentSet)                                  ,
                           m_constituents(constituents)                              ,
                           m_ConstituesIndexMap(constituesIndexMap)                  ,
                           m_testingConsSets(testingConsSets)                        ,

                           m_currentPopulationMatrix(currentPopulationMatrix)        ,
                           m_concentrations(concentrations)                          ,
                           m_testingPopulationMatrix(testingPopulationMatrix)        ,
                           m_testing_concentrations(testingconcentrations)          ,
                           m_MeanSpectraMatrix(meanSpectraMatrix)                    ,
                           m_MeanConcentrationMatrix(meanConcentrationMatrix)        ,


                           m_CorrectionFunction(correctionFunction)                  ,
                           m_zeroTransmissionDatapoints(izeroTransmissionDatapoints) ,
                           m_currentValuesOfX(icurrentValuesOfX)



    {
    }
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \brief TaskOptionsParameters::DisplayTestOptions
    ///
    void TaskOptionsParameters::DisplayTestOptions()
    {
           cout << "m_calibrationType = [" << m_calibrationType << " ] m_algorithmType              =  [" << m_algorithmType << " ]" <<endl;
           cout << "#######################################################################################################################"<< endl;
    }
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \brief TaskOptionsParameters::~TaskOptionsParameters
    ///
    TaskOptionsParameters::~TaskOptionsParameters()
    {
        clear();
    }
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \brief TaskOptionsParameters::TaskOptionsParameters
    /// \param taskoptions
    ///
    TaskOptionsParameters::TaskOptionsParameters(const TaskOptionsParameters & taskoptions)
    {
                m_preprocessingType              = taskoptions.m_preprocessingType;
                m_baseLineCorrection             = taskoptions.m_baseLineCorrection;
                m_dataSmoothing                  = taskoptions.m_dataSmoothing;
                m_derivativeSpectraType          = taskoptions.m_derivativeSpectraType;
                m_meanCenteringMethodType        = taskoptions.m_meanCenteringMethodType;
                m_calibrationType                = taskoptions.m_calibrationType;
                m_algorithmType                  = taskoptions.m_algorithmType;
                m_validationType                 = taskoptions.m_validationType;
                m_predictionType                 = taskoptions.m_predictionType;
                // BaselineCorrection Parameters
                m_fitParameters                  = taskoptions.m_fitParameters;
                // Data smoothing parameters
                m_dataSmoothingParameters        = taskoptions.m_dataSmoothingParameters;
                //Derivative parameters
                m_derivativeParameters           = taskoptions.m_derivativeParameters;
                m_filterMap                      = taskoptions.m_filterMap;
                m_tasksType                      = taskoptions.m_tasksType;

                m_kfolds                         = taskoptions.m_kfolds;
                numOfSamples                     = taskoptions.numOfSamples;
                numOfDataPoints                  = taskoptions.numOfDataPoints;
                numOfPCA                         = taskoptions.numOfPCA;

                m_numOfSamplesInTestingSet       = taskoptions.m_numOfSamplesInTestingSet;
                m_numOfDataPointsInTestingSet    = taskoptions.m_numOfDataPointsInTestingSet;
                m_numOfPCAInTestingSet           = taskoptions.m_numOfPCAInTestingSet;
                m_currentSet                     = taskoptions.m_currentSet;
                m_constituents                   = taskoptions.m_constituents;
                m_ConstituesIndexMap             = taskoptions.m_ConstituesIndexMap;
                m_testingConsSets                = taskoptions.m_testingConsSets;
                m_zeroTransmissionDatapoints     = taskoptions.m_zeroTransmissionDatapoints;
                m_currentPopulationMatrix        = taskoptions.m_currentPopulationMatrix;
                m_MeanSpectraMatrix              = taskoptions.m_MeanSpectraMatrix;
                m_testingPopulationMatrix        = taskoptions.m_testingPopulationMatrix;
                m_currentValuesOfX               = taskoptions.m_currentValuesOfX;
                m_concentrations                 = taskoptions.m_concentrations;
                m_MeanConcentrationMatrix        = taskoptions.m_MeanConcentrationMatrix;
                m_testing_concentrations         = taskoptions.m_testing_concentrations;
                m_CorrectionFunction             = taskoptions.m_CorrectionFunction;
                m_saved_model                    = taskoptions.m_saved_model;
                m_saved_Seperated_Spectra_model  = taskoptions.m_saved_Seperated_Spectra_model;
                m_saved_recalculated_model       = taskoptions.m_saved_recalculated_model;
                m_saved_recalculated_with_Seperated_spectra_model = taskoptions.m_saved_recalculated_with_Seperated_spectra_model;
                m_selectedData                   = taskoptions.m_selectedData;

    }
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \brief TaskOptionsParameters::operator =
    /// \param taskoptions
    /// \return
    ///
    TaskOptionsParameters& TaskOptionsParameters::operator=(const TaskOptionsParameters & taskoptions)
    {
        if(this != &taskoptions)
            {
                clear();

                m_preprocessingType                               = taskoptions.m_preprocessingType;
                m_baseLineCorrection                              = taskoptions.m_baseLineCorrection;
                m_dataSmoothing                                   = taskoptions.m_dataSmoothing;
                m_derivativeSpectraType                           = taskoptions.m_derivativeSpectraType;
                m_meanCenteringMethodType                         = taskoptions.m_meanCenteringMethodType;
                m_calibrationType                                 = taskoptions.m_calibrationType;
                m_algorithmType                                   = taskoptions.m_algorithmType;
                m_validationType                                  = taskoptions.m_validationType;
                m_predictionType                                  = taskoptions.m_predictionType;
                m_fitParameters                                   = taskoptions.m_fitParameters;
                m_dataSmoothingParameters                         = taskoptions.m_dataSmoothingParameters;
                m_derivativeParameters                            = taskoptions.m_derivativeParameters;
                m_filterMap                                       = taskoptions.m_filterMap;
                m_tasksType                                       = taskoptions.m_tasksType;

                m_kfolds                                          = taskoptions.m_kfolds;
                numOfSamples                                      = taskoptions.numOfSamples;
                numOfDataPoints                                   = taskoptions.numOfDataPoints;
                numOfPCA                                          = taskoptions.numOfPCA;

                m_numOfSamplesInTestingSet                        = taskoptions.m_numOfSamplesInTestingSet;
                m_numOfDataPointsInTestingSet                     = taskoptions.m_numOfDataPointsInTestingSet;
                m_numOfPCAInTestingSet                            = taskoptions.m_numOfPCAInTestingSet;
                m_currentSet                                      = taskoptions.m_currentSet;

                m_constituents                                    = taskoptions.m_constituents;
                m_ConstituesIndexMap                              = taskoptions.m_ConstituesIndexMap;
                m_testingConsSets                                 = taskoptions.m_testingConsSets;
                m_zeroTransmissionDatapoints                      = taskoptions.m_zeroTransmissionDatapoints;
                m_currentPopulationMatrix                         = taskoptions.m_currentPopulationMatrix;
                m_MeanSpectraMatrix                               = taskoptions.m_MeanSpectraMatrix;
                m_testingPopulationMatrix                         = taskoptions.m_testingPopulationMatrix;
                m_currentValuesOfX                                = taskoptions.m_currentValuesOfX;
                m_concentrations                                  = taskoptions.m_concentrations;
                m_MeanConcentrationMatrix                         = taskoptions.m_MeanConcentrationMatrix;
                m_testing_concentrations                          = taskoptions.m_testing_concentrations;
                m_CorrectionFunction                              = taskoptions.m_CorrectionFunction;
                m_saved_model                                     = taskoptions.m_saved_model;
                m_saved_Seperated_Spectra_model                   = taskoptions.m_saved_Seperated_Spectra_model;
                m_saved_recalculated_model                        = taskoptions.m_saved_recalculated_model;
                m_saved_recalculated_with_Seperated_spectra_model = taskoptions.m_saved_recalculated_with_Seperated_spectra_model;
                m_selectedData                                    = taskoptions.m_selectedData;
            }
            return *this;
    }
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \brief TaskOptionsParameters::TaskOptionsParameters
    /// \param taskoptions
    ///
    TaskOptionsParameters::TaskOptionsParameters(TaskOptionsParameters && taskoptions)
    {
                m_preprocessingType                               = taskoptions.m_preprocessingType;
                m_baseLineCorrection                              = taskoptions.m_baseLineCorrection;
                m_dataSmoothing                                   = taskoptions.m_dataSmoothing;
                m_derivativeSpectraType                           = taskoptions.m_derivativeSpectraType;
                m_meanCenteringMethodType                         = taskoptions.m_meanCenteringMethodType;
                m_calibrationType                                 = taskoptions.m_calibrationType;
                m_algorithmType                                   = taskoptions.m_algorithmType;
                m_validationType                                  = taskoptions.m_validationType;
                m_predictionType                                  = taskoptions.m_predictionType;
                m_fitParameters                                   = taskoptions.m_fitParameters;
                m_dataSmoothingParameters                         = taskoptions.m_dataSmoothingParameters;
                m_derivativeParameters                            = taskoptions.m_derivativeParameters;
                m_filterMap                                       = taskoptions.m_filterMap;
                m_tasksType                                       = taskoptions.m_tasksType;

                m_kfolds                                          = taskoptions.m_kfolds;
                numOfSamples                                      = taskoptions.numOfSamples;
                numOfDataPoints                                   = taskoptions.numOfDataPoints;
                numOfPCA                                          = taskoptions.numOfPCA;

                m_numOfSamplesInTestingSet                        = taskoptions.m_numOfSamplesInTestingSet;
                m_numOfDataPointsInTestingSet                     = taskoptions.m_numOfDataPointsInTestingSet;
                m_numOfPCAInTestingSet                            = taskoptions.m_numOfPCAInTestingSet;
                m_currentSet                                      = taskoptions.m_currentSet;

                m_constituents                                    = taskoptions.m_constituents;
                m_ConstituesIndexMap                              = taskoptions.m_ConstituesIndexMap;
                m_testingConsSets                                 = taskoptions.m_testingConsSets;
                m_zeroTransmissionDatapoints                      = taskoptions.m_zeroTransmissionDatapoints;
                m_currentPopulationMatrix                         = taskoptions.m_currentPopulationMatrix;
                m_MeanSpectraMatrix                               = taskoptions.m_MeanSpectraMatrix;
                m_testingPopulationMatrix                         = taskoptions.m_testingPopulationMatrix;
                m_currentValuesOfX                                = taskoptions.m_currentValuesOfX;
                m_concentrations                                  = taskoptions.m_concentrations;
                m_MeanConcentrationMatrix                         = taskoptions.m_MeanConcentrationMatrix;
                m_testing_concentrations                          = taskoptions.m_testing_concentrations;
                m_CorrectionFunction                              = taskoptions.m_CorrectionFunction;
                m_saved_model                                     = taskoptions.m_saved_model;
                m_saved_Seperated_Spectra_model                   = taskoptions.m_saved_Seperated_Spectra_model;
                m_saved_recalculated_model                        = taskoptions.m_saved_recalculated_model;
                m_saved_recalculated_with_Seperated_spectra_model = taskoptions.m_saved_recalculated_with_Seperated_spectra_model;
                m_selectedData                                    = taskoptions.m_selectedData;

                taskoptions.clear();
    };
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \brief TaskOptionsParameters::operator =
    /// \param taskoptions
    /// \return
    ///
    TaskOptionsParameters& TaskOptionsParameters::operator=(TaskOptionsParameters && taskoptions)
    {
        if(this != &taskoptions)
        {
            clear();

            m_preprocessingType                               = taskoptions.m_preprocessingType;
            m_baseLineCorrection                              = taskoptions.m_baseLineCorrection;
            m_dataSmoothing                                   = taskoptions.m_dataSmoothing;
            m_derivativeSpectraType                           = taskoptions.m_derivativeSpectraType;
            m_meanCenteringMethodType                         = taskoptions.m_meanCenteringMethodType;
            m_calibrationType                                 = taskoptions.m_calibrationType;
            m_algorithmType                                   = taskoptions.m_algorithmType;
            m_validationType                                  = taskoptions.m_validationType;
            m_predictionType                                  = taskoptions.m_predictionType;
            m_fitParameters                                   = taskoptions.m_fitParameters;
            m_dataSmoothingParameters                         = taskoptions.m_dataSmoothingParameters;
            m_derivativeParameters                            = taskoptions.m_derivativeParameters;
            m_filterMap                                       = taskoptions.m_filterMap;
            m_tasksType                                       = taskoptions.m_tasksType;

            m_kfolds                                          = taskoptions.m_kfolds;
            numOfSamples                                      = taskoptions.numOfSamples;
            numOfDataPoints                                   = taskoptions.numOfDataPoints;
            numOfPCA                                          = taskoptions.numOfPCA;

            m_numOfSamplesInTestingSet                        = taskoptions.m_numOfSamplesInTestingSet;
            m_numOfDataPointsInTestingSet                     = taskoptions.m_numOfDataPointsInTestingSet;
            m_numOfPCAInTestingSet                            = taskoptions.m_numOfPCAInTestingSet;
            m_currentSet                                      = taskoptions.m_currentSet;
            m_constituents                                    = taskoptions.m_constituents;
            m_ConstituesIndexMap                              = taskoptions.m_ConstituesIndexMap;
            m_testingConsSets                                 = taskoptions.m_testingConsSets;
            m_zeroTransmissionDatapoints                      = taskoptions.m_zeroTransmissionDatapoints;
            m_currentPopulationMatrix                         = taskoptions.m_currentPopulationMatrix;
            m_MeanSpectraMatrix                               = taskoptions.m_MeanSpectraMatrix;
            m_testingPopulationMatrix                         = taskoptions.m_testingPopulationMatrix;
            m_currentValuesOfX                                = taskoptions.m_currentValuesOfX;
            m_concentrations                                  = taskoptions.m_concentrations;
            m_MeanConcentrationMatrix                         = taskoptions.m_MeanConcentrationMatrix;
            m_testing_concentrations                          = taskoptions.m_testing_concentrations;
            m_CorrectionFunction                              = taskoptions.m_CorrectionFunction;
            m_saved_model                                     = taskoptions.m_saved_model;
            m_saved_Seperated_Spectra_model                   = taskoptions.m_saved_Seperated_Spectra_model;
            m_saved_recalculated_model                        = taskoptions.m_saved_recalculated_model;
            m_saved_recalculated_with_Seperated_spectra_model = taskoptions.m_saved_recalculated_with_Seperated_spectra_model;
            m_selectedData                                    = taskoptions.m_selectedData;
            taskoptions.clear();
        }
        return *this;

    }
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \brief TaskOptionsParameters::clear
    ///
    void TaskOptionsParameters::clear()
    {
                m_constituents.clear();
                m_ConstituesIndexMap.clear();
                 for(auto t: m_testingConsSets)
                    t.clear();
                 m_testingConsSets.clear();
                 m_zeroTransmissionDatapoints.clear();
                 m_currentPopulationMatrix.clear();
                 m_MeanSpectraMatrix.clear();
                 m_testingPopulationMatrix.clear();
                 m_currentValuesOfX.clear();
                 m_concentrations.clear();
                 m_MeanConcentrationMatrix.clear();
                 m_testing_concentrations.clear();
                 m_CorrectionFunction.first.clear();
                 m_CorrectionFunction.second.clear();

                 m_preprocessingType          = NO_PREPROCESSING;
                 m_baseLineCorrection         = NONE_CORRECTION;
                 m_dataSmoothing              = NONE_SMOOTHING;
                 m_derivativeSpectraType      = {NO_DERIVATIVE_TYPE,NO_DERIVATIVE_ALGORITHM};
                 m_meanCenteringMethodType    = NONE_CENTERING;
                 m_calibrationType            = NO_CALIBRATION_TYPE;
                 m_algorithmType              = NO_ALGORITHM_TYPE;
                 m_validationType             = NO_VALIDATION;
                 m_predictionType             = NO_PREDICTION;
                 m_fitParameters              = {NOT_SET,-1, {0,0}},
                 m_dataSmoothingParameters    = nullptr,
                 m_derivativeParameters       = nullptr,
                 m_filterMap                  = {},
                 m_tasksType                  = {};

                 m_kfolds                     = -1;
                 numOfSamples                 = -1;
                 numOfDataPoints              = -1;
                 numOfPCA                     = -1;
                 m_numOfSamplesInTestingSet   = -1;
                 m_numOfDataPointsInTestingSet= -1;
                 m_numOfPCAInTestingSet       = -1;
                 m_currentSet                 = 0;


    }
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \brief TaskOptionsParameters::getTestParameters
    /// \return
    ///
    TaskOptionsParameters TaskOptionsParameters::getTestParameters()
    {
        return *this;
    }
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \brief TaskOptionsParameters::setTestParameters
    /// \param param
    ///
    void TaskOptionsParameters::setTestParameters(TaskOptionsParameters param)
    {
        *this = param;
    }
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \brief TaskOptionsParameters::operator ()
    /// \param a
    /// \param b
    /// \return
    ///
    bool TaskOptionsParameters::operator()(const  TaskOptionsParameters a,const  TaskOptionsParameters b)const
    {
             return a.numOfPCA  == b.numOfPCA ;
    }
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \brief TaskOptionsParameters::operator <
    /// \param x
    /// \return
    ///
    bool TaskOptionsParameters::operator<(const TaskOptionsParameters& x) const
    {

        bool result = false;
        if
        (
             m_calibrationType            != x.m_calibrationType    ||
             m_algorithmType              != x.m_algorithmType
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
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \brief TaskOptionsParameters::operator ==
    /// \param x
    /// \return
    ///
    bool TaskOptionsParameters::operator==(const TaskOptionsParameters& x) const
    {
          bool  result = true;

          if
          (
               m_task_name                  == x.m_task_name                   &&
               m_preprocessingType          == x.m_preprocessingType           &&
               m_baseLineCorrection         == x.m_baseLineCorrection          &&
               m_dataSmoothing              == x.m_dataSmoothing               &&
               m_derivativeSpectraType      == x.m_derivativeSpectraType       &&
               m_meanCenteringMethodType    == x.m_meanCenteringMethodType     &&
               m_calibrationType            == x.m_calibrationType             &&
               m_algorithmType              == x.m_algorithmType               &&
               m_validationType             == x.m_validationType              &&
               m_predictionType             == x.m_predictionType              &&
               m_fitParameters              == x.m_fitParameters               &&
               m_dataSmoothingParameters    == x.m_dataSmoothingParameters     &&
               m_derivativeParameters       == x.m_derivativeParameters        &&

               m_tasksType                  == x.m_tasksType                   &&

               m_kfolds                     == x.m_kfolds                      &&
               numOfSamples                 == x.numOfSamples                  &&
               numOfDataPoints              == x.numOfDataPoints               &&
               numOfPCA                     == x.numOfPCA                      &&
               m_numOfSamplesInTestingSet   == x.m_numOfSamplesInTestingSet    &&
               m_numOfDataPointsInTestingSet== x.m_numOfDataPointsInTestingSet &&
               m_numOfPCAInTestingSet       == x.m_numOfPCAInTestingSet        &&
               m_currentSet                 == x.m_currentSet                  &&
               m_currentValuesOfX           == x.m_currentValuesOfX

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
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \brief TaskOptionsParameters::CreateBaselineTemplateParameter
    /// \param param
    /// \return
    ///
    FitParameters  TaskOptionsParameters::CreateBaselineTemplateParameter(tuple< FunctionTypes,vector<int>,int> param)
    {
        return {get<0>(param) ,get<2>(param),get<1>(param)};
    }
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \brief TaskOptionsParameters::CreateBaselineTemplateParameter
    /// \param baseline
    /// \return
    ///
    FitParameters TaskOptionsParameters::CreateBaselineTemplateParameter(pair<BaseLineCorrectionType, tuple< FunctionTypes,vector<int>,int >> baseline)
    {
            FunctionTypes function = get<0>(baseline.second);

            vector<int> points = get<1>(baseline.second);
            int  NumberOfCoefficients = get<2>(baseline.second);
            if(baseline.first == INTERACTIVE_POLINOMIAL_BASELINE)
            {
                points = getEvenlySpacedPoints(4,0,m_currentValuesOfX.size(),points);
            }
             switch(function)
             {
                 case POWER:
                 case EXPONENTIAL:
                 case LOGARITHMIC:
                       NumberOfCoefficients = 2;
                    break;
                 case POLYNOMIAL:
                 case NOT_SET:
                    break;
             };
             FitParameters f = f.setFitParameters(function ,NumberOfCoefficients,points);
             return f;
    }
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \brief TaskOptionsParameters::CreateBaselineTemplateParameter
    /// \param baseline
    /// \return
    ///
    pair<BaseLineCorrectionType,vector<FitParameters>>  TaskOptionsParameters::CreateBaselineTemplateParameter(pair<BaseLineCorrectionType, tuple< vector<FunctionTypes>,vector<int>,int >> baseline)
    {

        vector<FitParameters> fparam;

        vector<FunctionTypes> functions = get<0>(baseline.second);
        for(auto function : functions)
        {
            vector<int> points = get<1>(baseline.second);
            int  NumberOfCoefficients = get<2>(baseline.second);
            if(baseline.first == INTERACTIVE_POLINOMIAL_BASELINE)
            {
                points = getEvenlySpacedPoints(4,0,m_currentValuesOfX.size(),points);
            }
             switch(function)
             {
                 case POWER:
                 case EXPONENTIAL:
                 case LOGARITHMIC:
                       NumberOfCoefficients = 2;
                    break;
                 case POLYNOMIAL:
                 case NOT_SET:
                    break;
             };
             FitParameters f = f.setFitParameters(function ,NumberOfCoefficients,points);
             fparam.push_back(f);
        }
        return {baseline.first,fparam};
    }

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \brief TaskOptionsParameters::CreateBaselineTemplateParameters
    /// \param baselines
    /// \return
    ///
    map<BaseLineCorrectionType,vector<FitParameters>> TaskOptionsParameters::CreateBaselineParameters(  map<BaseLineCorrectionType, tuple< vector<FunctionTypes>,vector<int>,int >> baselines)
    {

         map<BaseLineCorrectionType,vector<FitParameters>>  param;

         for(auto baseline: baselines)
         {
             param.insert(CreateBaselineTemplateParameter(baseline));
         }
          return param;

    }
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \brief TaskOptionsParameters::getEvenlySpacedPoints
    /// \param nPoints
    /// \param min
    /// \param max
    /// \param excludepoints
    /// \return
    ///
    vector<int> TaskOptionsParameters::getEvenlySpacedPoints(int nPoints,int min,int max,vector<int> excludepoints)
    {
         vector<int> result;
         int delta = (max - min) /( nPoints - 1);

         for(int i=0;i < nPoints * delta;i = i + delta)
         {
             for(int j=0;j < (int)excludepoints.size();j++)
             {
                 if(i >= (int)m_currentValuesOfX.size())
                     i = (int)m_currentValuesOfX.size() - 1;
                 if(excludepoints[j] != i)
                 {
                    result.push_back(i);
                 }
                 else
                 {
                     int index = i;

                     if(index != (int)m_currentValuesOfX.size() )
                     {
                         while(excludepoints[j] == index && index != (int)m_currentValuesOfX.size())
                         {
                            index++;
                         }
                         if(excludepoints[j] != index)
                         {
                            result.push_back(index);
                         }
                     }

                 }
             }
             if(nPoints == (int)result.size() || (int)result.size() == (max - (int)excludepoints.size()))
             {
                 break;
             }
             cout << endl;
         }
         for(int j=0;j < (int)excludepoints.size();j++)
         {
            result.push_back(excludepoints[j]);
         }
         std::sort(result.begin(),result.end());
         return result;
    }
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \brief TaskOptionsParameters::CreateDataSmoothingParameter
    /// \param type
    /// \param param
    /// \return
    ///

    Fit *  TaskOptionsParameters::CreateDataSmoothingParameter(DataSmoothingType type,tuple< double,double,double> param)
    {
        std::tuple<double, double,double> * data = createTuple( get<0>(param),get<1>(param), get<2>(param) );
        Fit * result = nullptr;
        switch(type)
        {
             case BINOMIAL:
               result  = new BinomialFit(*data);
               break;
             case SAVITZJY_GOLAY:
               result  = new SavitzkyFit(*data);
               break;
             case NONE_SMOOTHING:
               break;

        };

        return  result;
    }
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \brief TaskOptionsParameters::CreateBaselineTemplateParameters
    /// \return
    ///
    map<DataSmoothingType,Fit *> TaskOptionsParameters::CreateDataSmoothingParameters(  map<DataSmoothingType, tuple< double,double,double>> params)
    {
        map<DataSmoothingType,Fit *>  result;

        for(auto param: params)
        {
             result.insert(pair<DataSmoothingType,Fit *>(param.first,CreateDataSmoothingParameter(param.first,param.second)));
        }
        return result;
    }
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \brief TaskOptionsParameters::CreateDataDerivativeParameters
    /// \param params
    /// \return
    ///
     map<DerivativeSpectraType,map<DerivativeAlgorithmType,Fit *>> TaskOptionsParameters::CreateDataDerivativeParameters(  map<DerivativeSpectraType, vector<tuple< DerivativeAlgorithmType,double,double,double>>> params)
    {
        map<DerivativeSpectraType,map<DerivativeAlgorithmType,Fit *>>  result;

        for(auto param: params)
        {
             map<DerivativeAlgorithmType,Fit *> algorithmData;
            for(auto algorithm: param.second)
            {
                algorithmData.insert(CreateDataDerivativeParameter(param.first,algorithm));

            }
            result.insert(pair<DerivativeSpectraType,map<DerivativeAlgorithmType,Fit *>>(param.first,algorithmData));
        }
        return result;
    }

    pair<DerivativeAlgorithmType,Fit *> TaskOptionsParameters::CreateDataDerivativeParameter(DerivativeSpectraType,tuple< DerivativeAlgorithmType,double,double,double> param)
    {
        double numberOfPoints = (int)std::get<1>(param);
        double polinomialDegree = (int)std::get<2>(param);
        double derivativeOrder = (int)std::get<3>(param);
        DerivativeAlgorithmType alg = get<0>(param);
        switch(alg)
        {
            case SIMPLE_DIFFERENCE:
               numberOfPoints = 0;
               derivativeOrder = 1;
            break;
            case GAP:
                if(derivativeOrder > 2)
                    derivativeOrder = 2;
            break;
            case SAVITZJY_GOLAY_ALGORITHM:
            case NO_DERIVATIVE_ALGORITHM:
            break;
        }

        std::tuple<double, double,double> * data = createTuple(numberOfPoints,polinomialDegree, derivativeOrder );
        return pair<DerivativeAlgorithmType,Fit *>(alg,new SavitzkyFit(*data));
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \brief TaskOptionsParameters::selectNPoints
    /// \param curPoints
    /// \param sampleNumber
    /// \return
    ///
    vector<Point> TaskOptionsParameters::selectNPoints( vector<int> curPoints,int sampleNumber, mat & cur_matrix,int option,FunctionTypes ftype)
    {
        vector<Point> result ;

        if(option == 0)
        {
            for(int i =0;i < (int)curPoints.size();i++)
            {
                if(curPoints[i] < m_currentValuesOfX.size() && sampleNumber < (int)cur_matrix.n_rows && curPoints[i] < (int)cur_matrix.n_cols)
                {
                   result.push_back( Point(m_currentValuesOfX[curPoints[i]],cur_matrix(sampleNumber,curPoints[i])));
                }
                else
                {
                    return result;
                }

            }
        }
        else if(option == 1)
        {
            vector<double> curPointsY;

            double scale = 1;
            switch(ftype)
            {
                case POLYNOMIAL:
                case NOT_SET:
                   break;
                case EXPONENTIAL:
                case POWER:
                case LOGARITHMIC:

                     break;
            }

            for(int i = 0;i < (int)curPoints.size() ;i++)
            {
                curPointsY.push_back((i+1) * scale);
            }

            int count = (int)curPointsY.size();
            for(int i =0;i < count;i++)
            {
                int len = (int)curPointsY.size() ;
                int index =0;

                if( len > 0)
                {
                    if((len - 1) != 0)
                    {
                          index =  rand() % (len - 1);
                    }

                    result.push_back( Point(m_currentValuesOfX[curPoints[i]],curPointsY[index]));
                }
                else
                {
                    return result;
                }

                curPointsY.erase (curPointsY.begin()+index);
            }
        }
        else if(option == 2)
        {
            result =
            {
                Point(188.55,-0.020),
                Point(194.53,-0.025),
                Point(196.62,-0.028),
                Point(203.49,-0.025),
                Point(208.57,-0.027),
                Point(215.43,-0.023),
                Point(220.49,-0.027),
                Point(225.55,-0.023),
                Point(300.54,-0.010),
                Point(400.49,-0.010),
                Point(450.56,-0.005),
                Point(499.94,-0.001)

            };

        }
        return result;
    }
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \brief TaskOptionsParameters::setFilterMap
    /// \param constitutes
    /// \param xPoints
    /// \param type
    /// \return
    ///
    Filter::FilterMap TaskOptionsParameters::setFilterMap(vector<pair<ConstituteFilterTypes,int>> constitutes,const mat &xPoints,filterType type)
    {
         Filter::FilterMap filters;
         if((int)xPoints.n_elem > 0)
         {
             for(auto filter: constitutes)
             {
                 int curconst = 0;
                 if(filter.first == NOHigh || filter.first == NO2High) // if filter is High then set curconst = 1
                     curconst = 1;
                 filters[filter.first] = getFilterMap(filter.second,xPoints, curconst,type);
             }
         }
         return filters;
    }
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \brief TaskOptionsParameters::getFilterMap
    /// \param NumberOfFilters
    /// \param xPoints
    /// \param lowOrHigh
    /// \param type
    /// \return
    ///
    vector<Filter> TaskOptionsParameters::getFilterMap(int NumberOfFilters,const mat & xPoints,int lowOrHigh,filterType type) // 0 ->Low, 1->High
    {
        vector<Filter> result;
        if((int)xPoints.n_elem > 0)
        {
            double diapazonmin;
            double diapazonmax;
            if(lowOrHigh)
            {

                diapazonmin = ((xPoints[xPoints.n_cols - 1] + xPoints[0]) / 2) + 1;
                diapazonmax =  xPoints[xPoints.n_cols - 1];
            }
            else
            {
                diapazonmin = xPoints[0];
                diapazonmax = ((xPoints[xPoints.n_cols - 1] + xPoints[0]) / 2);
            }


            double bw =  (diapazonmax -  diapazonmin) / (NumberOfFilters);

            double lambdamin = diapazonmin;
            double lambdamax = lambdamin + bw;

            double cwl = (lambdamax + lambdamin) / 2;
            Filter filter;
            vector<double> x =  Statistic::convToStd(xPoints);
            for(int i=0;i < NumberOfFilters  ;i++)
            {

                //cout << cwl - (bw/2) << " "<<cwl << " "<< cwl + (bw/2) << endl;
                FilterParameters filterParameters(i,type,cwl,bw,(int)x.size(),x[0],x[(int)x.size() - 1]);
                filter.DesignFilter(filterParameters);
                result.push_back(filter);
                 cwl =  cwl + bw;

            }

        }
        return result;

    }
} /* namespace NDUV */
