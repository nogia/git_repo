/*
 * ProjConstants.h
 *
 *  Created on: Apr 7, 2016
 *      Author: inna
 */

#ifndef PROJCONSTANTS_H_
#define PROJCONSTANTS_H_

#include "NduvHeader.h"

namespace NDUV
{
    enum filterType {LPF, HPF, BPF,STOPBANDF};
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \brief The FunctionName enum
    ///
    enum FunctionName
    {
        NONE,
        PREPROCESSING,
        BASE_LINE_CORRECTION,
        DATA_SMOOTHING,
        DERIVATIVE_SPECTRA,
        MEAN_CENTERING_SPECTRA,
        CALIBRATION,
        ALGORITHM,
        VALIDATION,
        PREDICTION

       // REAL_TIME_POST_PROCESSING,
       // AK_COMMUNICATION,
       // RECORD_KEEPING,
       // NUMBER_OF_FUNCTIONS

    };
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \brief The ConstituteFilterTypes enum
    ///
    enum ConstituteFilterTypes
       {
           NOLow,
           NOHigh,
           NO2Low,
           NO2High
       };


    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \brief The NoTask enum
    ///
    enum NoTask
    {
        NO_TASKT = 0,
    };
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \brief The PreprocessingType enum
    ///
    enum PreprocessingType
    {
        NO_PREPROCESSING   = 1,
        BASE_PREPROCESSING = 2,
    };
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \brief The BaseLineCorrectionType enum
    ///
    enum BaseLineCorrectionType
    {
       NONE_CORRECTION                 = 3,
       SIMPLE_OFFSET_CORRECTION        = 4,
       TWO_POINT_BASE_LINE             = 5,
       MULTI_POINT_BASE_LINE           = 6,
       INTERACTIVE_POLINOMIAL_BASELINE = 7,
       FUNCTION_FIT_BASE_LINE          = 8,
       GIFTS                           = 9

    };
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \brief The DataSmoothingType enum
    ///
    enum DataSmoothingType
    {
        NONE_SMOOTHING = 10,
        BINOMIAL       = 12,
        SAVITZJY_GOLAY = 13
    };
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \brief The DerivativeSpectraType enum
    ///
    enum DerivativeSpectraType
    {
        NO_DERIVATIVE_TYPE             = 14,
        ZERO_DERIVATIVE_SPECTRA        = 15,
        FIRST_DERIVATIVE_OF_WAVELENGTH = 16,
        SECOND_DERIVATIVE_OF_WAVELENGTH= 17,
    };
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \brief The DerivativeAlgorithmType enum
    ///
    enum DerivativeAlgorithmType
    {
        NO_DERIVATIVE_ALGORITHM,
        // Only First Derivative
        SIMPLE_DIFFERENCE,
        SAVITZJY_GOLAY_ALGORITHM,
        // Only first and second
        GAP
    };
    const map<DerivativeAlgorithmType,string> DerivativeAlgorithmTypeTextMap
    {
        {NO_DERIVATIVE_ALGORITHM ,"No Derivative Algorithm Type"               },
        {SIMPLE_DIFFERENCE       ,"Simple Difference Derivative Algorithm Type"},
        {SAVITZJY_GOLAY_ALGORITHM,"Savitzky Goley Derivative Algorithm Type"   },
        {GAP                     , "Gap Derivative Algorithm Type"             }
    };
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \brief The MeanCenteringMethodType enum
    ///
    enum MeanCenteringMethodType
    {
       NONE_CENTERING                  = 18,
       COMPUTE_MEAN_SPECTRUM           = 19,

    };
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \brief The CalibrationType enum
    ///
    enum CalibrationType
    {
        NO_CALIBRATION_TYPE            = 21,
        UNIVARIATE_CALIBRATION         = 22,
        MULTIVARIATE_CALIBRATION       = 23
    };
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \brief The AlgorithmType enum
    ///
    enum AlgorithmType
    {
        NO_ALGORITHM_TYPE             = 24,
        NIPALS_ALGORITHM              = 25,
        LIBPCA                        = 26,
        DECOMPOSITION_ALGORITHM       = 27,

    };
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \brief The ValidationType enum
    ///
    enum ValidationType
    {
        NO_VALIDATION                 = 28,
        CROSS_VALIDATION_LEAVEOUT     = 29,
        TESTINGSET                    = 30,
        KFOLDCROSSVALIDATION          = 31
    };
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \brief The PredictionType enum
    ///
    enum PredictionType
    {
        NO_PREDICTION                     = 50,
        TESTINGSETPREDICTION              = 51,
        LEAVEOUTPREDICTION                = 52,
        KFOLDPREDICTION                   = 53
    };
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \brief The TaskT struct
    ///
    struct TaskT
    {
          TaskT(std::pair<NoTask,int> task = std::pair<NoTask,int>(NO_TASKT,0)) : taskT(task){};
          std::pair<NoTask,int> taskT;
    };
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \brief The PreprocessingTaskT struct
    ///
    struct PreprocessingTaskT : public TaskT
    {
         PreprocessingTaskT(std::pair<PreprocessingType,int> task = std::pair<PreprocessingType,int>(NO_PREPROCESSING,1)) : preprocessing(task)
         {

         };
         std::pair<PreprocessingType,int> preprocessing;
    };
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \brief The BaseLineCorrectionTaskT struct
    ///
    struct BaseLineCorrectionTaskT : public TaskT
    {
        BaseLineCorrectionTaskT(std::pair<BaseLineCorrectionType,int> task = std::pair<BaseLineCorrectionType,int>(NONE_CORRECTION,3)) : baselineCorrection(task)
        {

        };
        std::pair<BaseLineCorrectionType,int> baselineCorrection;
    };
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \brief The DataSmoothingTaskT struct
    ///
    struct DataSmoothingTaskT : public TaskT
    {
          DataSmoothingTaskT(std::pair<DataSmoothingType,int> task = std::pair<DataSmoothingType,int>(NONE_SMOOTHING,10)) : dataSmooting(task){};
          std::pair<DataSmoothingType,int>  dataSmooting;
    };
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \brief The DerivativeSpectraTaskT struct
    ///
    struct DerivativeSpectraTaskT : public TaskT
    {
          DerivativeSpectraTaskT(std::pair<DerivativeSpectraType,int> task = std::pair<DerivativeSpectraType,int>(NO_DERIVATIVE_TYPE,14)) : derivative(task){};
          std::pair<DerivativeSpectraType,int> derivative ;
    };
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \brief The MeanCenteringMethodTaskT struct
    ///
    struct MeanCenteringMethodTaskT : public TaskT
    {
          MeanCenteringMethodTaskT(std::pair<MeanCenteringMethodType,int> task = std::pair<MeanCenteringMethodType,int>(NONE_CENTERING,18)) : meanCentering(task){};
          std::pair<MeanCenteringMethodType,int> meanCentering ;
    };
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \brief The CalibrationTaskT struct
    ///
    struct CalibrationTaskT : public TaskT
    {
         CalibrationTaskT( std::pair<CalibrationType,int> task =  std::pair<CalibrationType,int>(NO_CALIBRATION_TYPE,21)) : calibrationType(task){};
         std::pair<CalibrationType,int>   calibrationType ;
    };
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \brief The AlgorithmTaskT struct
    ///
    struct AlgorithmTaskT : public TaskT
    {
        AlgorithmTaskT( std::pair< AlgorithmType,int> task =  std::pair< AlgorithmType,int>(NO_ALGORITHM_TYPE,24)) : algorithmType(task){};
        std::pair<AlgorithmType,int>  algorithmType ;
    };
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \brief The ValidationTaskT struct
    ///
    struct ValidationTaskT : public TaskT
    {
        ValidationTaskT( std::pair<ValidationType,int> task =  std::pair<ValidationType,int>(NO_VALIDATION,28)) : validationType(task){};
        std::pair<ValidationType,int>  validationType ;
    };
    struct PredictionTaskT : public TaskT
    {
        PredictionTaskT( std::pair<PredictionType,int> task =  std::pair<PredictionType,int>(NO_PREDICTION,50)) : predictionType(task){};
        std::pair<PredictionType,int>  predictionType ;
    };
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \brief The PredictionTaskT struct
    ///
   /* struct PredictionTaskT : public TaskT
    {
        PredictionTaskT( std::pair<PredictionType,int> task =  std::pair<PredictionType,int>(NO_PREDICTION,50)) : predictionType(task){};
        std::pair<PredictionType,int>  predictionType ;
    };*/
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    static const map<int,TaskT*> TypeTmap =
    {
       {(new TaskT())->taskT.second                                                                                                          ,new TaskT()                                                                                           },

       {(new PreprocessingTaskT())->preprocessing.second                                                                                     ,new PreprocessingTaskT()                          },
       {(new PreprocessingTaskT(std::pair<PreprocessingType,int>(BASE_PREPROCESSING,2)))->preprocessing.second                               ,new PreprocessingTaskT(std::pair<PreprocessingType,int>(BASE_PREPROCESSING,2))                        },

       {(new BaseLineCorrectionTaskT() )->baselineCorrection.second                                                                          ,new BaseLineCorrectionTaskT()                                                                         },
       {(new BaseLineCorrectionTaskT(std::pair<BaseLineCorrectionType,int>(SIMPLE_OFFSET_CORRECTION,4)))->baselineCorrection.second          ,new BaseLineCorrectionTaskT(std::pair<BaseLineCorrectionType,int>(SIMPLE_OFFSET_CORRECTION,4))        },
       {(new BaseLineCorrectionTaskT(std::pair<BaseLineCorrectionType,int>(TWO_POINT_BASE_LINE,5)))->baselineCorrection.second               ,new BaseLineCorrectionTaskT(std::pair<BaseLineCorrectionType,int>(TWO_POINT_BASE_LINE,5))             },
       {(new BaseLineCorrectionTaskT(std::pair<BaseLineCorrectionType,int>(MULTI_POINT_BASE_LINE,6)))->baselineCorrection.second             ,new BaseLineCorrectionTaskT(std::pair<BaseLineCorrectionType,int>(MULTI_POINT_BASE_LINE,6))           },
       {(new BaseLineCorrectionTaskT(std::pair<BaseLineCorrectionType,int>(INTERACTIVE_POLINOMIAL_BASELINE,7)))->baselineCorrection.second   ,new BaseLineCorrectionTaskT(std::pair<BaseLineCorrectionType,int>(INTERACTIVE_POLINOMIAL_BASELINE,7)) },
       {(new BaseLineCorrectionTaskT(std::pair<BaseLineCorrectionType,int>(FUNCTION_FIT_BASE_LINE,8)))->baselineCorrection.second            ,new BaseLineCorrectionTaskT(std::pair<BaseLineCorrectionType,int>(FUNCTION_FIT_BASE_LINE,8))          },
       {(new BaseLineCorrectionTaskT(std::pair<BaseLineCorrectionType,int>(GIFTS,9)))->baselineCorrection.second                             ,new BaseLineCorrectionTaskT(std::pair<BaseLineCorrectionType,int>(GIFTS,9))                           },

       {(new DataSmoothingTaskT() )->dataSmooting.second                                                                                    ,new DataSmoothingTaskT()                                                                               },

       {(new DataSmoothingTaskT(std::pair<DataSmoothingType,int>(BINOMIAL,12)))->dataSmooting.second                                        ,new DataSmoothingTaskT(std::pair<DataSmoothingType,int>(BINOMIAL,12))                                  },
       {(new DataSmoothingTaskT(std::pair<DataSmoothingType,int>(SAVITZJY_GOLAY,13)))->dataSmooting.second                                  ,new DataSmoothingTaskT(std::pair<DataSmoothingType,int>(SAVITZJY_GOLAY,13))                            },

       {(new DerivativeSpectraTaskT() )->derivative.second                                                                                  ,new DerivativeSpectraTaskT()                                                                           },
       {(new DerivativeSpectraTaskT(std::pair<DerivativeSpectraType,int>(ZERO_DERIVATIVE_SPECTRA,15)))->derivative.second                   ,new DerivativeSpectraTaskT(std::pair<DerivativeSpectraType,int>(ZERO_DERIVATIVE_SPECTRA,15))           },
       {(new DerivativeSpectraTaskT(std::pair<DerivativeSpectraType,int>(FIRST_DERIVATIVE_OF_WAVELENGTH,16)))->derivative.second            ,new DerivativeSpectraTaskT(std::pair<DerivativeSpectraType,int>(FIRST_DERIVATIVE_OF_WAVELENGTH,16))    },
       {(new DerivativeSpectraTaskT(std::pair<DerivativeSpectraType,int>(SECOND_DERIVATIVE_OF_WAVELENGTH,17)))->derivative.second           ,new DerivativeSpectraTaskT(std::pair<DerivativeSpectraType,int>(SECOND_DERIVATIVE_OF_WAVELENGTH,17))   },

       {(new MeanCenteringMethodTaskT() )->meanCentering.second                                                                             ,new MeanCenteringMethodTaskT()                                                                         },
       {(new MeanCenteringMethodTaskT(std::pair<MeanCenteringMethodType,int>(COMPUTE_MEAN_SPECTRUM ,19)))->meanCentering.second             ,new MeanCenteringMethodTaskT(std::pair<MeanCenteringMethodType,int>(COMPUTE_MEAN_SPECTRUM ,19))        },


       {(new CalibrationTaskT() )->calibrationType.second                                                                                   ,new CalibrationTaskT()                                                                                 },
       {(new CalibrationTaskT(std::pair<CalibrationType,int>(UNIVARIATE_CALIBRATION,22)))->calibrationType.second                           ,new CalibrationTaskT(std::pair<CalibrationType,int>(UNIVARIATE_CALIBRATION,22))                        },
       {(new CalibrationTaskT(std::pair<CalibrationType,int>(MULTIVARIATE_CALIBRATION,23)))->calibrationType.second                         ,new CalibrationTaskT(std::pair<CalibrationType,int>(MULTIVARIATE_CALIBRATION,23))                      },

       {(new AlgorithmTaskT() )->algorithmType.second                                                                                       ,new AlgorithmTaskT()                                                                                   },
       {(new AlgorithmTaskT(std::pair< AlgorithmType,int>(NIPALS_ALGORITHM,25)))->algorithmType.second                                      ,new AlgorithmTaskT(std::pair< AlgorithmType,int>(NIPALS_ALGORITHM,25))                                 },
       {(new AlgorithmTaskT(std::pair< AlgorithmType,int>(LIBPCA,26)))->algorithmType.second                                                ,new AlgorithmTaskT(std::pair< AlgorithmType,int>(LIBPCA,26))                                           },
       {(new AlgorithmTaskT(std::pair< AlgorithmType,int>(DECOMPOSITION_ALGORITHM,27)))->algorithmType.second                               ,new AlgorithmTaskT(std::pair< AlgorithmType,int>(DECOMPOSITION_ALGORITHM,27))                          },

       {(new ValidationTaskT() )->validationType.second                                                                                     ,new ValidationTaskT()                                                                                  },
       {(new ValidationTaskT(std::pair<ValidationType,int>(CROSS_VALIDATION_LEAVEOUT ,29)))->validationType.second                          ,new ValidationTaskT(std::pair<ValidationType,int>(CROSS_VALIDATION_LEAVEOUT ,29))                      },
       {(new ValidationTaskT(std::pair<ValidationType,int>(TESTINGSET,30)))->validationType.second                                          ,new ValidationTaskT(std::pair<ValidationType,int>(TESTINGSET,30))                                      },
       {(new ValidationTaskT(std::pair<ValidationType,int>( KFOLDCROSSVALIDATION,31)))->validationType.second                               ,new ValidationTaskT(std::pair<ValidationType,int>( KFOLDCROSSVALIDATION,31))                                      },

       {(new PredictionTaskT() )->predictionType.second                                                                                     ,new PredictionTaskT()                                                                                  },
       {(new PredictionTaskT(std::pair<PredictionType,int>(TESTINGSETPREDICTION,51)))->predictionType.second                               ,new PredictionTaskT(std::pair<PredictionType,int>(TESTINGSETPREDICTION,51))                           },
       {(new PredictionTaskT(std::pair<PredictionType,int>(LEAVEOUTPREDICTION,52)))->predictionType.second                                 ,new PredictionTaskT(std::pair<PredictionType,int>(LEAVEOUTPREDICTION,52))                             },
       {(new PredictionTaskT(std::pair<PredictionType,int>(KFOLDPREDICTION ,53)))->predictionType.second                                   ,new PredictionTaskT(std::pair<PredictionType,int>(KFOLDPREDICTION  ,53))                              },
    };

    static const map<TaskT*,int> TypeTmapInverse =
    {
       {new TaskT()                                                                                           ,0  },

       {new PreprocessingTaskT()                                                                              ,1  },
       {new PreprocessingTaskT(std::pair<PreprocessingType,int>(BASE_PREPROCESSING,2))                        ,2  },

       {new BaseLineCorrectionTaskT()                                                                         ,3  },
       {new BaseLineCorrectionTaskT(std::pair<BaseLineCorrectionType,int>(SIMPLE_OFFSET_CORRECTION,4))        ,4  },
       {new BaseLineCorrectionTaskT(std::pair<BaseLineCorrectionType,int>(TWO_POINT_BASE_LINE,5))             ,5  },
       {new BaseLineCorrectionTaskT(std::pair<BaseLineCorrectionType,int>(MULTI_POINT_BASE_LINE,6))           ,6  },
       {new BaseLineCorrectionTaskT(std::pair<BaseLineCorrectionType,int>(INTERACTIVE_POLINOMIAL_BASELINE,7)) ,7  },
       {new BaseLineCorrectionTaskT(std::pair<BaseLineCorrectionType,int>(FUNCTION_FIT_BASE_LINE,8))          ,8  },
       {new BaseLineCorrectionTaskT(std::pair<BaseLineCorrectionType,int>(GIFTS,9))                           ,9  },

       {new DataSmoothingTaskT()                                                                              ,10 },

       {new DataSmoothingTaskT(std::pair<DataSmoothingType,int>(BINOMIAL,12))                                 ,12 },
       {new DataSmoothingTaskT(std::pair<DataSmoothingType,int>(SAVITZJY_GOLAY,13))                           ,13 },

       {new DerivativeSpectraTaskT()                                                                          ,14 },
       {new DerivativeSpectraTaskT(std::pair<DerivativeSpectraType,int>(ZERO_DERIVATIVE_SPECTRA,15))          ,15 },
       {new DerivativeSpectraTaskT(std::pair<DerivativeSpectraType,int>(FIRST_DERIVATIVE_OF_WAVELENGTH,16))   ,16 },
       {new DerivativeSpectraTaskT(std::pair<DerivativeSpectraType,int>(SECOND_DERIVATIVE_OF_WAVELENGTH,17))  ,17 },

       {new MeanCenteringMethodTaskT()                                                                        ,18 },
       {new MeanCenteringMethodTaskT(std::pair<MeanCenteringMethodType,int>(COMPUTE_MEAN_SPECTRUM ,19))       ,19 },


       {new CalibrationTaskT()                                                                                ,21 },
       {new CalibrationTaskT(std::pair<CalibrationType,int>(UNIVARIATE_CALIBRATION,22))                       ,22 },
       {new CalibrationTaskT(std::pair<CalibrationType,int>(MULTIVARIATE_CALIBRATION,23))                     ,23 },

       {new AlgorithmTaskT()                                                                                  ,24 },
       {new AlgorithmTaskT(std::pair< AlgorithmType,int>(NIPALS_ALGORITHM,25))                                ,25 },
       {new AlgorithmTaskT(std::pair< AlgorithmType,int>(LIBPCA,26))                                          ,26 },
       {new AlgorithmTaskT(std::pair< AlgorithmType,int>(DECOMPOSITION_ALGORITHM,27))                         ,27 },

       {new ValidationTaskT()                                                                                 ,28 },
       {new ValidationTaskT(std::pair<ValidationType,int>(CROSS_VALIDATION_LEAVEOUT ,29))                     ,29 },
       {new ValidationTaskT(std::pair<ValidationType,int>(TESTINGSET,30))                                     ,30 },
       {new ValidationTaskT(std::pair<ValidationType,int>(KFOLDCROSSVALIDATION,31))                           ,31 },

       {new PredictionTaskT()                                                                                 ,50 },
       {new PredictionTaskT(std::pair<PredictionType,int>(TESTINGSETPREDICTION,51))                           ,51 },
       {new PredictionTaskT(std::pair<PredictionType,int>(LEAVEOUTPREDICTION,52))                             ,52 },
       {new PredictionTaskT(std::pair<PredictionType,int>(KFOLDPREDICTION ,53))                               ,53 },
    };

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \brief The Constituents enum
    ///
    enum Constituents
    {
        HC  = 2,
        NO  = 0,
        NO2 = 1,
        N2O = 3,
        NH3 = 4,
        SO2 = 5,
        O3  = 6,
        UNKNOWN = 7,
    };
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    const map<Constituents,string> ConstituentsName
    {
        {NO, "NO"  },
        {NO2,"NO2" },
        {HC, "HC"  },
        {N2O,"N2O" },
        {NH3,"NH3" },
        {SO2,"SO2" },
        {O3, "SO3" },
        {UNKNOWN,"Unknown"}

    };
    const map<string,Constituents> ConstituentsNameInverted
    {
        { "HC" ,HC },
        { "NO" ,NO  },
        { "NO2",NO2 },
        { "N2O",N2O },
        { "NH3",NH3 },
        { "SO2",SO2 },
        { "O3", O3 },
        { "Unknown",UNKNOWN}

    };
    static int factorial(int n)
    {
      return (n == 1 || n == 0) ? 1 : factorial(n - 1) * n;
    }

    static std::map<FunctionName,std::string> GET_FUNCTION_NAMES =
           {
                {NONE,"None"},
                {PREPROCESSING,"Preprocessing"},
                {BASE_LINE_CORRECTION,"Base Line Correction"},
                {DATA_SMOOTHING,"Data Smoothing"},
                {DERIVATIVE_SPECTRA,"Derivative Spectra"},
                {MEAN_CENTERING_SPECTRA,"Mean Centering Spectra"},
                {CALIBRATION,"Calibration"},
                {VALIDATION, "Validation" },

           };
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \brief The CreateCycle struct
    ///
    struct CreateCycle
    {
        BaseLineCorrectionType m_baseLineCorrection;
        DataSmoothingType m_dataSmoothing;
        DerivativeSpectraType m_derivativeSpectraType;
        MeanCenteringMethodType m_meanCenteringMethodType;
        CalibrationType m_calibrationType;
        AlgorithmType m_algorithmType;

    };
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \brief The FunctionTypes enum
    ///
    enum FunctionTypes
    {
        NOT_SET,
        POLYNOMIAL,
        EXPONENTIAL,
        LOGARITHMIC,
        POWER
    };
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    static const map<FunctionTypes,string> FunctionTypesMap =
    {
        {NOT_SET    ,"Not Set"    },
        {POLYNOMIAL ,"Polynomial" },
        {EXPONENTIAL,"Exponential"},
        {LOGARITHMIC,"Logarithmic"},
        {POWER      ,"Power"      }
    };
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \brief The Point struct
    ///
    struct Point
     {
         Point(double ix=-1,double iy = -1) : x(ix),y(iy){}
         double x;
         double y;
         bool operator()(const Point a,const Point b) const
         {
             return a.x < b.x;
         }
         bool operator==(const Point& z) const
         {
             return (x == z.x && y == z.y );
         }
         void print()
         {
             cout << "x = "<< x << "  y = "<< y << endl;
         }
     };
     //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
       const long long INFINITY0 = 1000000000000000000;
       const std::string PATH = "../";
       const int HEADER_LINES = 12;
       const std::string DIRECTORY_NAME_TESTFILES = "testfiles";
       const double CONVERGENCE_DISTANCE = 0.00001;
       const int MAX_LOOP_VALUE = 100;
       const double STUDENTTEST_SRESHOLD = 0.005;
       static const double PI = 3.14159265;
       //////// default data
       static std::vector<int> defaultTwoBaselinepoints ={ 1,4};
       static std::vector<int> defaultMultipleBaselineXpoints = {1,2,3,4};
       static std::vector<int> defaultCurrentlyAdjustedPoint = {3};

      static vector<int> defaultseq = {1,2,3};

} /* namespace NDUV */

#endif /* PROJCONSTANTS_H_ */
