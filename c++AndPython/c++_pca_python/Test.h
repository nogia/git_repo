/*
 * Test.h
 *
 *  Created on: May 13, 2016
 *      Author: inna
 */

#ifndef TEST_H_
#define TEST_H_

#include "Avs5216.h"
#include <dirent.h>
#include "TestTemplate.h"
#include "GeneticAlgorithm.h"

namespace NDUV
{
    typedef  void(*task)(TaskOptionsParameters&,Statistic &s);
    class Test;
    class Chromosome;
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \brief The InputVariables struct
    ///
    struct InputVariables
    {

        int numberOfSelectedVariables;
        int numberOfSelectedSamplesCalib;
        int numberOfSelectedSamplesTest;
        pair<int,int> selectXPoints;
        pair<int,int> selectCalibrationSamples;
        pair<int,int> selectTestSamples;
        int maxNumberOfPCA ;
        string errorMessage;
        int result;

        vector<int> selectedVariableIndex;
        vector<int> selectedSamplesCalibration;
        vector<int> selectedSamplesTest;
       // InputVariables(const InputVariables & value);
       // InputVariables& operator=(const InputVariables & value);
        int checkLimits(const vector<double> & waveLengthVariables ,int maxOfCalibrationSamples,int maxOfTestSamples, Test &instance);
        int checkLimits( pair<int,int> &selected, int minlimit,int maxlimit,int option,string &errorMessage);

       private:

    };
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \brief SpectraMap
    ///
    typedef  map<int,tuple<Constituents,double,map<int,Point>,int,Point,Point>> SpectraMap;
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \brief The SelectedData struct
    ///
    struct SelectedData
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
        ~SelectedData()
        {
            Clear();
        }
    };
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \brief The Test class
    ///
    class Test
      {
        friend class ParametersFactory;
        friend class InputVariables;
        private:
          // Reading input fules parameters
          std::string path;
          std::string directory;
          map<int,task> m_TasksMap;
          vector<int> m_OrderIndex;
          map<int,Point> m_currentSpectraPoints;
          SpectraMap m_SpectraDataMap;

          mat m_CalibrationDataMap;
          mat m_TestDataMap;
          mat m_FullCalibrationMatrix;
          mat m_FullTestMatrix;
          mat m_zeroTransmissionSpectra;
          mat m_FullzeroTransmissionSpectra;
          mat mXPoints;
          mat mFullXPoints;
          mat m_CalibConcentrationMap;
          mat m_TestConcentrationMap;
          mat m_FullCalibConcentrationMatrix;
          mat m_FullTestConcentrationMatrix;

          map<Constituents,int> m_ConstituesIndexMap;

          Point m_Factor;
          Point m_MinMax;

          pair<int,int> m_filesCalib,m_filesTest;
          pair<int,int> m_CalibRows,m_TestRows;

          // Parameters of the tests
          // Selected Data selects points and samples from Test and Calibration set
          SelectedData m_selectedData;
          // Inputs number of variables, calibration samples testing samples, their limits and validate them
          InputVariables m_InputVar;
          // Holds the parameters for the set of task created
          TaskOptionsParameters m_param;

          bool m_InitialiedParameters;
          bool m_InitialiedTasks;
          static Avs m_avs;
          // Tasks
          static void taskCalibration(TaskOptionsParameters & parameters,Statistic &s);
          static void taskValidation(TaskOptionsParameters& parameters,Statistic &s);
          static void taskPrediction(TaskOptionsParameters& parameters,Statistic &s);
          static void taskBaseLineCorrection(TaskOptionsParameters& parameters,Statistic &s);
          static void taskDataSmoothing(TaskOptionsParameters& parameters,Statistic &s);
          static void taskDerivative(TaskOptionsParameters& parameters,Statistic &s);
          static void taskMeanCentering(TaskOptionsParameters& parameters,Statistic &s);
          static void taskPreprocessing(TaskOptionsParameters& parameters,Statistic &s);

          // Algorithms

          //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

           map<int,task> m_CurrentTests =
          {
              {(int)BASE_PREPROCESSING                       , &taskPreprocessing               },

              {(int)SIMPLE_OFFSET_CORRECTION                 , &taskBaseLineCorrection          },
              {(int)TWO_POINT_BASE_LINE                      , &taskBaseLineCorrection          },
              {(int)MULTI_POINT_BASE_LINE                    , &taskBaseLineCorrection          },
              {(int)INTERACTIVE_POLINOMIAL_BASELINE          , &taskBaseLineCorrection          },
              {(int)FUNCTION_FIT_BASE_LINE                   , &taskBaseLineCorrection          },
              {(int)GIFTS                                    , &taskBaseLineCorrection          },


              {(int)BINOMIAL                                 , &taskDataSmoothing               },
              {(int)SAVITZJY_GOLAY                           , &taskDataSmoothing               },

              {(int)ZERO_DERIVATIVE_SPECTRA                  , &taskDerivative                  },
              {(int)FIRST_DERIVATIVE_OF_WAVELENGTH           , &taskDerivative                  },
              {(int)SECOND_DERIVATIVE_OF_WAVELENGTH          , &taskDerivative                  },

              {(int)COMPUTE_MEAN_SPECTRUM                    , &taskMeanCentering               },

              {(int)UNIVARIATE_CALIBRATION                   , &taskCalibration                 },
              {(int)MULTIVARIATE_CALIBRATION                 , &taskCalibration                 },

              {(int)CROSS_VALIDATION_LEAVEOUT                , &taskValidation                  },
              {(int)TESTINGSET                               , &taskValidation                  },
              {(int)KFOLDCROSSVALIDATION                     , &taskValidation                  },

              {(int)TESTINGSETPREDICTION                     , &taskPrediction                  },
              {(int)LEAVEOUTPREDICTION                       , &taskPrediction                  },
              {(int) KFOLDPREDICTION                         , &taskPrediction                  },

          };

          const map<FunctionName,int> TasksIndex =
          {
             { PREPROCESSING         ,0},
             { MEAN_CENTERING_SPECTRA,1},
             { BASE_LINE_CORRECTION  ,2},
             { DATA_SMOOTHING        ,3},
             { DERIVATIVE_SPECTRA    ,4},
             { CALIBRATION           ,5},
             { ALGORITHM             ,6},
             { VALIDATION            ,7},
             { PREDICTION            ,8},

          };
          // Functions to read and create maps data
          void Init();
          void ProcessDirectory(std::string directory);
          map<int,Point> ProcessFile(std::string dirpath,std::string file);
          void CreateMatrixData(const SpectraMap & smap);
          pair<int,tuple<Constituents,double,map<int,Point>,int,Point,Point>> ProcessEntity(std::string dirpath,struct dirent* entity);
          Point parseRatingLine(string line);
          void setfilesData();
          void printDataMaps();
          void  SelectXPoints(SelectedData &selectedata);
          void SelectCalibAndTestData(vector<int> selectedVariables={},vector<int> SelectedSamplesCalib={} ,vector<int> SelectedSamplesTest={} );
          vector<int> getSelectedIndex(int total = 0,int selected = 0);
          mat getSelectedMatrix(const mat& matrix,const vector<int> & rowindex,const vector<int> & columnIndex = {});


          static vector<int> selectNRandomPoints( int nPoints,  int min, int max);
          vector<int> getMapKey();
          TaskOptionsParameters GetTemplateParameterFromFiles();
          // Functions to create and add taks
          void AddAndRunTasks(  Statistic &s );
          void DeleteTask(int index);
          Statistic  RunTest(const Statistic & inputStatistic);
          void resetTaskMap( map<int,TaskT*> &tasksType);
          ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
          /// \brief mapGetValues
          /// \param pointsmap
          /// \return
          ///
          static vector<double> mapGetValues(map<int,Point> pointsmap);



          Stat testPick(Test test);
          //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

          public:
          //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

          Test(InputVariables testInput = {} );
           //if currentSet = 0 the calibration set will be used, if currentSet = 1 the test set will be used
          Test(Statistic &s, int currentSet,InputVariables testInput,const vector<TaskInputParam*> &tasksInputParameters);
          ~Test();
          InputVariables getInputVariable();

          void GetSetVariavleIndexFromTheFile(string filename,vector<int> &var,bool set = true);
          void setVariablesLimits(InputVariables testInput = {});


          void testVariablesPick(Test test,int start, int end,vector<Stat> &bests,double rms,int algorithm);
          void testVariablesPick( Test& test,Chromosome &chrom,double rms);
          Stat testVariables(const Test& test, vector< int> limits);

          void PickVariables
          (
                  vector<int> variables, int length,int size,int start,int end,
                  pair<double,double> fitness,int & fitnessRank,double & currentFitness ,
                  int blocksize = 1,int maxNumberOfGenerations = 7,string filename = "Variables.txt"
          );

          void PickVariables
          (
                  int size,int startpercent,int  endpercent,int percentdecrement,double  maxRmsAverage,double minRms,
                  std::vector<Stat> &bestVariablesRange,
                  int &numberFound
          );
          void SelectGARange
          (
                  int size,int startpercent,int  endpercent,int percentdecrement,double  maxRmsAverage,double minRms,
                  std::vector<Stat> &bestVariablesRanges,
                  int alg,int &numberFound
          );

          void Run(Statistic &s,int currentSet=0,vector<TaskInputParam*> tasksInputParameters ={});
          void setTaskOptionParam(mat  &m1,mat &m2,int opt );
          TaskOptionsParameters  getTaskOptionParam();
      };
}
#endif /* TEST_H_ */
