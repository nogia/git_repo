/*
 * TestOptions.h
 *
 *  Created on: May 13, 2016
 *      Author: inna
 */

#ifndef TESTOPTIONS_H_
#define TESTOPTIONS_H_

#include "Statistics.h"
#include "Filter.h"

namespace NDUV
{

            class Statistic;
            class Filter;
            /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            /// \brief The SelectedOptions struct
            ///
            struct SelectedOptions
            {
                int m_NumberOfSamplesCalib;
                int m_NumberOfSamplesTest;
                int m_NumberOfVariables;

                vector<int> m_VariableIndex;
                vector<int> m_SampleIndexCalib;
                vector<int> m_SampleIndexTest;
                int m_totalNPOINTS;
                int m_totalSamplesCalib;
                int m_totalSamplesTest;
                void Clear()
                {
                     m_VariableIndex.clear();
                     m_SampleIndexCalib.clear();
                     m_SampleIndexTest.clear();
                }
                ~SelectedOptions()
                {
                    Clear();
                }
            };
            ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            /// \brief The TaskOptionsParameters struct
            ///
            struct TaskOptionsParameters
             {
                   string m_task_name;

                   PreprocessingType      m_preprocessingType;
                   BaseLineCorrectionType m_baseLineCorrection;
                   DataSmoothingType m_dataSmoothing;
                   pair<DerivativeSpectraType,DerivativeAlgorithmType>  m_derivativeSpectraType;
                   MeanCenteringMethodType m_meanCenteringMethodType;
                   CalibrationType m_calibrationType;
                   AlgorithmType m_algorithmType;
                   ValidationType m_validationType;
                   PredictionType m_predictionType;
                   // Parameters for Baseline Corrections
                   FitParameters m_fitParameters;
                   // Parameters for Data Smoothing
                   Fit * m_dataSmoothingParameters;
                   Fit * m_derivativeParameters;
                   // Parameters for Univariate Calibration
                   Filter::FilterMap m_filterMap;
                   // Parameters for the list of tasks on the same spectra
                   map<int,TaskT*> m_tasksType;
                   // Validation Parameter
                   int m_kfolds;
                   int numOfSamples;
                   int numOfDataPoints;
                   int numOfPCA;

                   int m_numOfSamplesInTestingSet;
                   int m_numOfDataPointsInTestingSet;
                   int m_numOfPCAInTestingSet;
                   int m_currentSet; // 0 -> current set =  CalibrationSet, 1 -> current set =  TestingSet;

                   map<Constituents,string> m_constituents;
                   map<Constituents,int> m_ConstituesIndexMap;

                   vector<mat> m_testingConsSets;

                   mat m_currentPopulationMatrix;
                   mat m_concentrations;
                   mat m_testingPopulationMatrix;
                   mat m_testing_concentrations;

                   mat m_MeanSpectraMatrix;
                   mat m_MeanConcentrationMatrix;


                   pair<mat,mat> m_CorrectionFunction;
                   rowvec m_zeroTransmissionDatapoints;
                   vector<double> m_currentValuesOfX;
                   SelectedOptions m_selectedData;

                   Statistic m_saved_model;
                   Statistic m_saved_Seperated_Spectra_model;

                   Statistic m_saved_recalculated_model;
                   Statistic m_saved_recalculated_with_Seperated_spectra_model;

                   TaskOptionsParameters
                   (
                           string task_name                                  = "NONE",
                           PreprocessingType      preprocessingType        = NO_PREPROCESSING,
                           BaseLineCorrectionType baseLineCorrection       = NONE_CORRECTION,
                           DataSmoothingType dataSmoothing                 = NONE_SMOOTHING,
                           pair<DerivativeSpectraType,DerivativeAlgorithmType> m_derivativeSpectraType     = {NO_DERIVATIVE_TYPE,NO_DERIVATIVE_ALGORITHM},
                           MeanCenteringMethodType meanCenteringMethodType = NONE_CENTERING,
                           CalibrationType calibrationType                 = NO_CALIBRATION_TYPE,
                           AlgorithmType algorithmType                     = NO_ALGORITHM_TYPE,
                           ValidationType validationType                   = NO_VALIDATION,
                           PredictionType prediction                       = NO_PREDICTION,
                           // FitParameters is parameters for BaseLine Correction
                           FitParameters  fitParameters                    = {NOT_SET,-1, {0,0}},
                           Fit * dataSmoothingParameters                   = nullptr,
                           Fit * derivativeParameters                      = nullptr,
                           Filter::FilterMap filterMap                               = {},
                           // DataSmoothing parameters

                           map<int,TaskT*> m_tasksType    = {},
                           int kfolds                                        = -1,
                           int numOfSamples                                  = -1,
                           int numOfDataPoints                               = -1,
                           int numOfPCA                                      = -1,

                           int numOfSamplesInTestingSet                    = -1,
                           int numOfDataPointsInTestingSet                 = -1,
                           int numOfPCAInTestingSet                        = -1,
                           int currentSet                                  = 0,
                           map<Constituents,string> constituents             = ConstituentsName,
                           map<Constituents,int>    constituesIndexMap       =  {}             ,
                           vector<mat> testingConsSets                       =  {}             ,
                           mat currentPopulationMatrix                       = mat(0,0),
                           mat concentrations                                = mat(0,0),
                           mat testingPopulationMatrix                       = mat(0,0),
                           mat testing_concentrations                        = mat(0,0),
                           mat meanSpectraMatrix                             = mat(0,0),
                           mat meanConcentrations                            = mat(0,0),

                           pair<mat,mat> correctionFunction                  = pair<mat,mat>(mat(0,0),mat(0,0)),

                           vector<double> izeroTransmissionDatapoints         = {},
                           vector<double> icurrentValuesOfX                   = {}

                   );
                   ~TaskOptionsParameters();
                   TaskOptionsParameters(const TaskOptionsParameters & taskoptions);
                   TaskOptionsParameters& operator=(const TaskOptionsParameters & taskoptions);

                   TaskOptionsParameters(TaskOptionsParameters && taskoptions);
                   TaskOptionsParameters& operator=(TaskOptionsParameters && taskoptions);

                   void clear();
                   bool operator()(const  TaskOptionsParameters a,const  TaskOptionsParameters b)const;

                   bool operator<(const TaskOptionsParameters& x) const;

                   bool operator==(const TaskOptionsParameters& x) const;

                   TaskOptionsParameters getTestParameters();
                   void setTestParameters(TaskOptionsParameters param);
                   vector<Point> selectNPoints( vector<int> curPoints,int sampleNumber ,mat & cur_matrix,int option,FunctionTypes ftype);

                   map<BaseLineCorrectionType,vector<FitParameters>> CreateBaselineParameters(  map<BaseLineCorrectionType, tuple< vector<FunctionTypes>,vector<int>,int>> baselines);
                   FitParameters  CreateBaselineTemplateParameter(tuple< FunctionTypes,vector<int>,int> );
                   pair<BaseLineCorrectionType,vector<FitParameters>>  CreateBaselineTemplateParameter(pair<BaseLineCorrectionType, tuple< vector<FunctionTypes>,vector<int>,int >> baseline);
                   FitParameters CreateBaselineTemplateParameter(pair<BaseLineCorrectionType, tuple< FunctionTypes,vector<int>,int >> baseline);
                   vector<int> getEvenlySpacedPoints(int nPoints,int min,int max,vector<int> excludepoints);

                   map<DataSmoothingType,Fit *> CreateDataSmoothingParameters(  map<DataSmoothingType, tuple< double,double,double>> );
                   Fit *  CreateDataSmoothingParameter(DataSmoothingType,tuple< double,double,double>);

                   map<DerivativeSpectraType,map<DerivativeAlgorithmType,Fit *>> CreateDataDerivativeParameters(  map<DerivativeSpectraType, vector<tuple< DerivativeAlgorithmType,double,double,double>>> );
                   pair<DerivativeAlgorithmType,Fit *>  CreateDataDerivativeParameter(DerivativeSpectraType,tuple< DerivativeAlgorithmType,double,double,double>);
                   void DisplayTestOptions();

                   Filter::FilterMap setFilterMap(vector<pair<ConstituteFilterTypes,int>> constitutes,const mat &,filterType);
                   vector<Filter> getFilterMap(int,const mat &,int,filterType );

               };



} /* namespace NDUV */

#endif /* TESTOPTIONS_H_ */
