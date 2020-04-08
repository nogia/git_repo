/*
 * TestTemplate.cpp
 *
 *  Created on: Aug 19, 2016
 *      Author: inna
 */

#include "TestTemplate.h"

namespace NDUV
{
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \brief TaskInputParam::TaskInputParam
    /// \param fname
    /// \param order
    ///
    TaskInputParam:: TaskInputParam(FunctionName fname ,int order ) : m_name(fname), m_OrderIndex(order)
    {

    }
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \brief TaskInputParam::~TaskInputParam
    ///
    TaskInputParam::~TaskInputParam()
    {

    }
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \brief PreprocessingInputParam::PreprocessingInputParam
    /// \param name
    /// \param order
    /// \param preprocessing
    ///
    PreprocessingInputParam::PreprocessingInputParam(FunctionName name,int order,PreprocessingType preprocessing ) : m_Preprocessing(preprocessing)
    {
        m_name = name;
        m_OrderIndex = order;
    }
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \brief PreprocessingInputParam::~PreprocessingInputParam
    ///
    PreprocessingInputParam::~PreprocessingInputParam()
    {

    }
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \brief MeanCenteringInputParam::MeanCenteringInputParam
    /// \param name
    /// \param order
    /// \param meanCenteringType
    ///
    MeanCenteringInputParam::MeanCenteringInputParam(FunctionName name,int order,MeanCenteringMethodType meanCenteringType  ) : m_MeanCenteringType(meanCenteringType)
    {
        m_name = name;
        m_OrderIndex = order;
    }
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \brief MeanCenteringInputParam::~MeanCenteringInputParam
    ///
    MeanCenteringInputParam::~MeanCenteringInputParam()
    {

    }
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \brief CalibrationInputParam::CalibrationInputParam
    /// \param name
    /// \param order
    /// \param calibrationType
    /// \param algorithmType
    ///
    CalibrationInputParam::CalibrationInputParam(FunctionName name,int order,CalibrationType calibrationType, AlgorithmType algorithmType) :
                          m_CalibrationType(calibrationType), m_AlgorithmType(algorithmType)
    {
        m_name = name;
        m_OrderIndex = order;
    }
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \brief ~CalibrationInputParam
    /// \return
    ///
    CalibrationInputParam::~CalibrationInputParam()
    {

    }
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \brief ValidationInputParam::ValidationInputParam
    /// \param name
    /// \param order
    /// \param validationType
    ///
    ValidationInputParam::ValidationInputParam(FunctionName name,int order,ValidationType validationType,int foldrange ) : m_ValidationType(validationType),m_foldrange(foldrange)
    {
        m_name = name;
        m_OrderIndex = order;
    }
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \brief ValidationInputParam::~ValidationInputParam
    ///
    ValidationInputParam::~ValidationInputParam()
    {

    }
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \brief PredictionInputParam::PredictionInputParam
    /// \param name
    /// \param order
    /// \param predictionType
    ///
    PredictionInputParam::PredictionInputParam(FunctionName name,int order,PredictionType predictionType  ) : m_PredictionType(predictionType)
    {
        m_name = name;
        m_OrderIndex = order;
    }
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \brief PredictionInputParam::~PredictionInputParam
    ///
    PredictionInputParam::~PredictionInputParam()
    {

    }
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \brief BaselineInputParam::BaselineInputParam
    /// \param name
    /// \param order
    /// \param funcType
    /// \param algType
    /// \param selectedPoints
    /// \param NumberOfCoefficients
    ///
    BaselineInputParam::BaselineInputParam
    (
         FunctionName name,int order,
         pair<pair<BaseLineCorrectionType, FunctionTypes >,pair<vector<int>, int>  > baseLineParam
    ) : m_BaseLineParam(baseLineParam)
    {
           m_name = name;
           m_OrderIndex = order;
    }
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \brief ~BaselineInputParam
    /// \return
    ///
    BaselineInputParam::~BaselineInputParam()
    {
        m_BaseLineParam.second.first.clear();
    }
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \brief DataSmootingInputParam::DataSmootingInputParam
    /// \param name
    /// \param order
    /// \param funcType
    /// \param numberOfPoints
    /// \param polinomialDegree
    /// \param derivativeOrder
    ///
    DataSmootingInputParam::DataSmootingInputParam
    (
            FunctionName name ,int order,
            pair<DataSmoothingType,vector<double>> dataSmoothingParam
    ) :
         m_DataSmoothingParam(dataSmoothingParam)
    {
           m_name = name;
           m_OrderIndex = order;
    }
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \brief DataSmootingInputParam::~DataSmootingInputParam
    ///
    DataSmootingInputParam::~DataSmootingInputParam()
    {
        m_DataSmoothingParam.second.clear();
    }
    DerivativeInputParam::DerivativeInputParam
    (
         FunctionName name,int order,
        pair<pair<DerivativeSpectraType, DerivativeAlgorithmType>,vector<double>> derivativeParam
    ) :
         m_DerivativeParam(derivativeParam)
    {
           m_name = name;
           m_OrderIndex = order;
    }

    DerivativeInputParam::~DerivativeInputParam()
    {
      m_DerivativeParam.second.clear();
    }
} /* namespace NDUV */
