/*
 * TestTemplate.h
 *
 *  Created on: Aug 19, 2016
 *      Author: inna
 */

#ifndef TESTTEMPLATE_H_
#define TESTTEMPLATE_H_

#include "ProjConstants.h"

namespace NDUV
{
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \brief The TaskInputParam struct
    ///
    struct TaskInputParam
    {
        friend class TestFactory;

        TaskInputParam(FunctionName fname = NONE,int order = -1);
        virtual ~TaskInputParam();

         FunctionName m_name;
         int m_OrderIndex;
    };
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \brief The PreprocessingInputParam struct
    ///
    struct PreprocessingInputParam : public TaskInputParam
    {
        PreprocessingInputParam(FunctionName name= NONE,int order = -1,PreprocessingType preprocessing = NO_PREPROCESSING );
        ~PreprocessingInputParam();

        PreprocessingType m_Preprocessing;
    };
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \brief The MeanCenteringInputParam struct
    ///
    struct MeanCenteringInputParam : public TaskInputParam
    {
        MeanCenteringInputParam(FunctionName name= NONE,int order = -1,MeanCenteringMethodType meanCenteringType = NONE_CENTERING );
        ~MeanCenteringInputParam();

        MeanCenteringMethodType m_MeanCenteringType;
    };
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \brief The CalibrationInputParam struct
    ///
    struct CalibrationInputParam : public TaskInputParam
    {
        CalibrationInputParam(FunctionName name = NONE,int order = -1,CalibrationType calibrationType = NO_CALIBRATION_TYPE , AlgorithmType algorithmType = NO_ALGORITHM_TYPE);
        ~CalibrationInputParam();

        CalibrationType m_CalibrationType;
        AlgorithmType m_AlgorithmType;
    };
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \brief The ValidationInputParam struct
    ///
    struct ValidationInputParam : public TaskInputParam
    {
        ValidationInputParam(FunctionName name= NONE,int order = -1,ValidationType validationType = NO_VALIDATION,int foldrange = 1  );
         ~ValidationInputParam();
        ValidationType m_ValidationType;
        int m_foldrange;
        int m_NumberOfKFolds;


    };
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \brief The PredictionInputParam struct
    ///
    struct PredictionInputParam : public TaskInputParam
    {
        PredictionInputParam(FunctionName name= NONE,int order = -1,PredictionType predictionType = NO_PREDICTION  );
         ~PredictionInputParam();
        PredictionType m_PredictionType;
        int m_foldrange;
        int m_NumberOfKFolds;
    };

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \brief The BaselineInputParam struct
    ///
    struct BaselineInputParam : public TaskInputParam
    {
        BaselineInputParam
        (
              FunctionName name= NONE,int order = -1,
              pair<pair<BaseLineCorrectionType, FunctionTypes >,pair<vector<int>, int>  > baseLineParam  = { {NONE_CORRECTION,NOT_SET}, { {}, -1}}
        );

       ~BaselineInputParam();
        pair<pair<BaseLineCorrectionType, FunctionTypes >,pair<vector<int>, int>  > m_BaseLineParam;
    };
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \brief The DataSmootingInputParam struct
    ///
    struct DataSmootingInputParam : public TaskInputParam
    {
        DataSmootingInputParam
        (
             FunctionName name = NONE,int order = -1,
             pair<DataSmoothingType,vector<double>> dataSmoothingParam =  {  NONE_SMOOTHING, {-1.0,-1.0}}
        );

       ~DataSmootingInputParam();
        pair<DataSmoothingType,vector<double>> m_DataSmoothingParam;
    };
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \brief The DerivativeInputParam struct
    ///
    struct DerivativeInputParam : public TaskInputParam
    {
        DerivativeInputParam
        (
            FunctionName name = NONE,int order = -1,
            pair<pair<DerivativeSpectraType, DerivativeAlgorithmType>,vector<double>> derivativeParam =
            {  {NO_DERIVATIVE_TYPE, NO_DERIVATIVE_ALGORITHM}, {-1.0,-1.0,-1.0}    }
        );
          ~DerivativeInputParam();
           pair<pair<DerivativeSpectraType, DerivativeAlgorithmType>,vector<double>> m_DerivativeParam;
       };


} /* namespace NDUV */

#endif /* TESTTEMPLATE_H_ */
