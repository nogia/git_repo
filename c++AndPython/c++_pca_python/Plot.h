/*
 * Plot.h
 *
 *  Created on: Jun 23, 2016
 *      Author: inna
 */

#ifndef PLOT_H_
#define PLOT_H_


#include "TestOptions.h"
#include "Python.h"
#include "Statistics.h"

namespace NDUV
{

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \brief The Plot class
    ///
    class Plot
    {
        public:
            //////////////////////////////////////////////////////////////////////////////////////////////////////
            /// \brief Plot
            ///
            Plot();
            /////////////////////////////////////////////////////////////////////////////////////////////////////
            ~Plot();
            /////////////////////////////////////////////////////////////////////////////////////////////////////
            /// \brief EndPython
            ///
            void EndPython();
            ////////////////////////////////////////////////////////////////////////////////////////////////////
            /// \brief CreatePlot
            /// \param plotdata
            ///
            void CreatePlot( vector<std::tuple<string,string,string,vector<vector<vector<double>>>>> plotdata, vector<std::tuple<vector<int>,vector<double>,vector<string>>> titles);
            /////////////////////////////////////////////////////////////////////////////////////////////////////
            /// \brief DisplayPlot
            /// \param populationAndCorrection
            /// \param scaleY
            ///
            void DisplayPlot(vector<pair<mat,mat>> populationAndCorrection,double scaleY , vector<std::tuple<vector<int>,vector<double>,vector<string>>> titles);
            /////////////////////////////////////////////////////////////////////////////////////////////////////
            void DisplayPlots(vector<pair<mat,mat>> populationAndCorrection,double scaleY, vector<std::tuple<vector<int>,vector<double>,vector<string>>> titles );
            

            void ShowRecreatedConcentrations
            (
                    const mat &CCal=mat(0,0),const mat &CCalRec=mat(0,0), const mat &CTest=mat(0,0), const mat &CTestRec=mat(0,0),
                    const vector<mat> &CCalRecModels={}, const vector<mat> &CTestRecModels={},
                    int nPCAModel = -1,
                    const mat & populationMatrix= mat(0,0),
                    const vector<mat> &BCoeff = {},int minPCA = -1,int maxPCA = -1,
                    int option1 = -1,int option2 = -1,int option3 = -1,
                    Statistic  cur_stat = Statistic(),
                    TaskOptionsParameters  param = TaskOptionsParameters()
             );

            /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            /// \brief ShowAllRecreatedConcentrationsModels
            /// \param addToDisplay
            /// \param titles
            /// \param CCal
            /// \param CCalRec
            /// \param CTest
            /// \param CTestRec
            /// \param BCoeff
            /// \param minPCA
            /// \param maxPCA
            /// \param option
            ///
            void ShowAllRecreatedConcentrationsModels
            (
                    vector<pair<mat,mat>> &addToDisplay ,
                    vector<std::tuple<vector<int>,vector<double>,vector<string>>> &titles ,
                    const mat &CCal ,const vector<mat> &CCalRec ,
                    const mat & CTest, const vector<mat> & CTestRec,
                    const vector<mat> &BCoeff,int minPCA,int maxPCA,
                    int option,
                    const  Statistic &  cur_stat,
                    const TaskOptionsParameters  &param
            );
            void ShowPredictedConcentrations
            (
                const Statistic & validation,
                const  Statistic &  prediction,
                const TaskOptionsParameters  &param
            );
            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            /// \brief ShowPCAData
            /// \param addToDisplay
            /// \param titles
            /// \param populationMatrix
            /// \param NPCA
            ///
            void ShowPCAData
            (
                    vector<pair<mat,mat>> &addToDisplay,
                    vector<std::tuple<vector<int>,vector<double>,vector<string>>> &titles,
                    const mat & populationMatrix,
                    int NPCA,
                    const Statistic &cur_stat,
                    const TaskOptionsParameters  &param
            );
            void ShowCorrected( mat spectraBefore, mat spectraAfter,mat concentrationsBefore,mat concentrationsAfter,const TaskOptionsParameters  &param);
            void ShowCorrected( mat spectraBefore, mat spectraAfter,const TaskOptionsParameters  &param);
            void ShowFunction
            (
                    pair<  mat,mat > func,
                    const TaskOptionsParameters  &param,
                    vector<pair<mat,mat>> &populationAndCorrection,
                    vector<std::tuple<vector<int>,vector<double>,vector<string>>> &titles
            );
            void ShowFunction( vector<pair<  mat,mat >> func, const TaskOptionsParameters  &param);

            void ShowStatisticsGraphs( vector<ValidationModel> &validation,const TaskOptionsParameters  &param);

            bool Show;
        private:

            //path where python file located
            string dirpath; // /home/inna/Desktop/NDUV/HNDUV/src
            string env;
            PyObject *pName, *pModule, *pDict, *pValue, *pArgs, *pClass, *pInstance;


    };

} /* namespace NDUV */

#endif /* PLOT_H_ */
