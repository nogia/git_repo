#include "Test.h"
#include "TestTemplate.h"

using namespace NDUV;

void RunAllTests();

//test commit
/////////////////////////////////////////////////////////////     Calibration     ////////////////////////////////////////////////////
void testCalibration();
void testUnivariateCalibration();
void testMultivariateCalibration();

/////////////////////////////////////////////////////////////     Validation      ///////////////////////////////////////////////////
void testValidation();
void testCrossValidationAndPrediction();

void  testVariablesStatistics();
std::vector<Stat>  testFindVariablesRange();
std::vector<Stat> testFindVariablesRanges();
void  testGeneticAlgFindVariablesRange();
std::vector<Stat> getFakeVariablesRange();
/////////////////////////////////////////////////////////////     Correction      ////////////////////////////////////////////////////

void testBaseLineOffset();
void testBaseLineSelected2Points();
void testBaseLineMultiSelectedPoints();
void testInteractivePolinomialBaseline();
void testFunctionFitBaseline();
void testGIFTSBaseline();
/////////////////////////////////////////////////////////////     Data Smoothing  ///////////////////////////////////////////////////
void testDataSmoothingAlgorithms();
void testBinomialSmoothing();
void testSavGolaySmoothing();
////////////////////////////////////////////////////////////      Derivative      ///////////////////////////////////////////////////
void testDerivativeAlgorithms();
void testSimpleDifference();
void testGap();
void testSavGolayDerivative();

////////////////////////////////////////////////////////////      Mean Centering  ///////////////////////////////////////////////////
void testMeanCentering();

///////////////////////////////////////////////////////////       Preprocessing  ////////////////////////////////////////////////////
void testPreprocessing();

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void testSelectedTasks();


/// \brief selectNRandomPoints
/// \param nPoints
/// \param totalpoints
/// \return
///
static vector<int> selectNRandomPoints(int nPoints, int min,int max)
{

    vector<int> curPoints;
    vector<int> result ;
    if(max <= 0 || min < 0 || min > max ||  max - min < nPoints)
        return result;
    if(nPoints == 1)
    {
        result.push_back((max + min) / 2);
        return result;
    }
    //int end = std::min(max,nPoints);
    for(int i = min;i < max;i++)
    {
        curPoints.push_back(i);
    }
    int count = std::min((int)curPoints.size(),nPoints);
    for(int i =0;i < count;i++)
    {
        int len = (int)curPoints.size() ;
        int index =0;

        if( len > 0)
        {
            if((len - 1) != 0)
            {
                  index =  rand() % (len - 1);
            }

            result.push_back( curPoints[index]);

        }
        else
        {
            return result;
        }

        curPoints.erase (curPoints.begin()+index);
    }
    std::sort(result.begin(),result.end());
    return result;

}
static vector<int> selectPoints = {200,400};


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \brief RunAllTests
///
void RunAllTests()
{

     vector<std::function<void(void)>> vectorOfTests =
     {

          // testBaseLineOffset,
          // testBaseLineSelected2Points,
           //testBaseLineMultiSelectedPoints,
          // testInteractivePolinomialBaseline,
          // testFunctionFitBaseline,
          // testGIFTSBaseline,

           // testDataSmoothingAlgorithms,
           // testBinomialSmoothing,
            // testSavGolaySmoothing,

            //testDerivativeAlgorithms,
            //testSavGolayDerivative,
           // testSimpleDifference,
           // testGap

            //testCalibration,
           // testUnivariateCalibration,
            // testMultivariateCalibration,
            // testValidation,
            //testCrossValidationAndPrediction,

           // testPreprocessing,

           // testMeanCentering,

             //testVariablesStatistics,
             //testFindVariablesRanges,
             testGeneticAlgFindVariablesRange

      };
     for(auto test : vectorOfTests )
     {
         test();
     }

    cout << endl;
}

////////////////////////////////////////////////////////////     Run All Test      /////////////////////////////////////////////////
/// \brief main
/// \return
///
int main()
{
    std::cout << "Minimum value for long long: " << std::numeric_limits<unsigned long long>::min() << '\n';
    std::cout << "Maximum value for long long: " << std::numeric_limits<unsigned long long>::max() << '\n';


    RunAllTests();

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \brief testBaseLineOffset
///
void testBaseLineOffset()
{

  Statistic statistic;

  Test test
  (
     statistic,0,
     {1076,400,400,{0,1076},{0,300},{0,329},50,"",-1},
     {
       new BaselineInputParam( BASE_LINE_CORRECTION,0,{{SIMPLE_OFFSET_CORRECTION,NOT_SET},{{},-1}}),
     }
  );

  test.Run(statistic,1);
  cout << endl;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \brief testBaseLineSelected2Points
///
void testBaseLineSelected2Points()
{
    Statistic statistic;
    // Run with Calibration files
    Test test
    (
        {1076,2,3,{0,1076},{200,300},{0,329},50,"",-1}
    );
    test.Run
    (
      statistic,0,
      {
        new BaselineInputParam
            (
                    BASE_LINE_CORRECTION,0,
                    {
                        {TWO_POINT_BASE_LINE ,NOT_SET},
                        {selectNRandomPoints(2,0, test.getInputVariable().numberOfSelectedVariables),-1}
                    }
            )
      }
    );
    // Run with Test files
    statistic.Clear();
    test.Run(statistic,1);
    cout << endl;
}

 /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 /// \brief testBaseLineSelected2Points
 ///
 void testBaseLineMultiSelectedPoints()
 {
     Statistic statistic;
     // Run with Calibration files
     Test test
     (
         {1076,1,1,{0,1076},{200,300},{0,329},50,"",-1}
     );
     int minL = 0;
     int maxH = 1076;
     test.Run
     (
       statistic,0,
       {
         new BaselineInputParam
             (
                     BASE_LINE_CORRECTION,0,
                     {
                         {MULTI_POINT_BASE_LINE ,NOT_SET},
                         {selectNRandomPoints(10,max(0,minL), min(maxH,test.getInputVariable().numberOfSelectedVariables)),-1}
                     }
             )
       }
     );
     // Run with Test files
     statistic.Clear();
     test.Run(statistic,1);
     cout << endl;
 }
 ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 /// \brief testInteractivePolinomialBaseline
 ///
 void testInteractivePolinomialBaseline()
 {
     Statistic statistic;
     // Run with Calibration files
     Test test
     (
         { 1076,1,1,{0,1076},{0,330},{0,329},50,"",-1}
     );
     int minL = 0;
     int maxH = test.getInputVariable().numberOfSelectedVariables;
     int NumberOfAjustedPoints = 1;// always 1
     int NumberOfCoefficients = 4; // => Degree of polinomial + 1 ; Degree of Polinomial for Interactive Baseline = 3
     test.Run
     (
       statistic,0, // 0 -> Calibration Set used
       {
         new BaselineInputParam
             (
                     BASE_LINE_CORRECTION,0,
                     {
                        { INTERACTIVE_POLINOMIAL_BASELINE ,POLYNOMIAL}, // 0 - > Order of the task
                        {selectNRandomPoints(NumberOfAjustedPoints,max(0,minL), min(maxH,test.getInputVariable().numberOfSelectedVariables)),NumberOfCoefficients}
                     }
             )
       }
     );
     // Run with Test files
     statistic.Clear();
     test.Run(statistic,1); // 1 -> Testing Set is used
     cout << endl;
 }
 void testFunctionFitBaseline()
 {
     Statistic statistic,copystatisticCalib,copystatisticTest;
     // Run with Calibration files
     // Run first Simple Ofset to get gid of negative values to test the functions that require taking the log( log must be > 0)
     Test test
     (
        statistic,0,
        {1076,400,400,{0,1076},{200,300},{0,329},50,"",-1},
        {
          new BaselineInputParam( BASE_LINE_CORRECTION,0,{{SIMPLE_OFFSET_CORRECTION,NOT_SET},{ {},-1 }}),
        }
     );

     copystatisticCalib.currentPopulationMatrix = statistic.currentPopulationMatrix;
     copystatisticTest.currentPopulationMatrix = (test.getTaskOptionParam()).m_testingPopulationMatrix;
     copystatisticTest.currentConcentrationMatrix = (test.getTaskOptionParam()).m_testing_concentrations;
     statistic.Clear();

     test.setTaskOptionParam(copystatisticTest.currentPopulationMatrix ,copystatisticTest.currentConcentrationMatrix,1);
     test.Run(statistic,1); // 1 -> Testing Set is used
     copystatisticTest = statistic;

     vector<int> NumberOfSelectedPoints = {3};//{1,2,3,4};
      // => Degree of polinomial + 1 ;
     vector<int>  NumberOfCoefficients = {3};//,4,5,6}; // always = 2 for Exp, Log and Power functions

     // Run Test for different Functions Log, Exp,Power, Polynomial
     vector<FunctionTypes>   functions = {EXPONENTIAL,POWER,LOGARITHMIC,POLYNOMIAL};
     for(auto point: NumberOfSelectedPoints)
     {
         for(auto coefficient: NumberOfCoefficients)
         {
             for(auto func : functions)
             {
                 test.setTaskOptionParam(copystatisticCalib.currentPopulationMatrix,copystatisticCalib.currentConcentrationMatrix,0 );
                 statistic.Clear();
                 test.Run
                 (
                   statistic,0, // 0 -> Calibration Set used
                   {
                     new BaselineInputParam
                         (
                            BASE_LINE_CORRECTION,0,
                            {
                              {FUNCTION_FIT_BASE_LINE,func},{selectNRandomPoints(point,0, test.getInputVariable().numberOfSelectedVariables),coefficient}
                            }
                         )
                   }

                 );

                 // Run with Test files
                 test.setTaskOptionParam(copystatisticTest.currentPopulationMatrix ,copystatisticTest.currentConcentrationMatrix,1);
                 statistic.Clear();
                 test.Run(statistic,1); // 1 -> Testing Set is used
             }
         }
     }

 }
 ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 /// \brief testGIFTSBaseline
 ///
 void testGIFTSBaseline()
 {
     Statistic statistic;
     // Run with Calibration files
     Test test
     (
         {10,400,400,{0,1076},{0,330},{0,329},50,"",-1}
     );

     test.Run
     (
       statistic,0,
       {
         new BaselineInputParam
             (
                     BASE_LINE_CORRECTION,0,
                     {
                        {GIFTS ,NOT_SET},
                        {selectNRandomPoints(test.getInputVariable().numberOfSelectedVariables,0, test.getInputVariable().numberOfSelectedVariables),-1},
                     }
             )
       }
     );
     // Run with Test files
     statistic.Clear();
     test.Run(statistic,1);
     cout << endl;
 }

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \brief testDataSmoothingAlgorithms
///
void testDataSmoothingAlgorithms()
{
    Statistic statistic;
    // Run with Calibration files
    Test test(  {1076,1,1,{0,1076},{100,250},{100,250},50,"",-1}  );

    vector<pair<DataSmoothingType,vector<double>>> smoothingAlg ={   {  BINOMIAL, {4.0,0.0}  } , {  SAVITZJY_GOLAY, {7.0,3.0} }   };

    for(auto alg: smoothingAlg)
    {
        statistic.Clear();
        test.Run(statistic,0,{new DataSmootingInputParam(DATA_SMOOTHING,0 ,alg)});

       // Run with Test files
        statistic.Clear();
        test.Run(statistic,1);
    }
    cout << endl;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \brief testBinomialSmoothing
///
void testBinomialSmoothing()
{
    Statistic statistic;

    Test test({1076,1,1,{0,1076},{100,250},{100,250},50,"",-1});
    vector<double> valueOfS = {1,2,3,4,5,10};

    for(auto valueS: valueOfS)
    {
        // Test Calibration Set
        statistic.Clear();
        test.Run(statistic,0,{new DataSmootingInputParam(DATA_SMOOTHING,0 , {   BINOMIAL, {valueS,0.0} }  )});

        // Run with Test files
        statistic.Clear();
        test.Run(statistic,1);
    }
    cout << endl;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \brief testSavGolaySmoothing
///
void testSavGolaySmoothing()
{
     Statistic statistic;
     // Run with Calibration files
     Test test({10,10,10,{0,1076},{100,250},{100,250},50,"",-1});

    vector<double> valueOfS = {5,7,11,23,53};
    vector<double> polinomialDegrees = {3,2};

    for(auto valueS: valueOfS)
    {
        for(auto polinomialDegree: polinomialDegrees)
        {
            // Test Calibration Set
            statistic.Clear();
            test.Run(statistic,0,{new DataSmootingInputParam(DATA_SMOOTHING,0 , {   SAVITZJY_GOLAY, {valueS, polinomialDegree} }  )});

            // Run with Test files
            statistic.Clear();
            test.Run(statistic,1);
        }
    }
    cout << endl;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \brief testDerivativeAlgorithms
///
void testDerivativeAlgorithms()
{
     Statistic statistic;

      Test test({1076,1,1,{0,1076},{100,250},{100,250},50,"",-1});

      vector<pair<pair<DerivativeSpectraType, DerivativeAlgorithmType>,vector<double>>> derivativeparams =
      {
           {  {FIRST_DERIVATIVE_OF_WAVELENGTH  , SAVITZJY_GOLAY_ALGORITHM }, {5.0, 3.0, 1.0}  } ,
           {  {FIRST_DERIVATIVE_OF_WAVELENGTH  , SIMPLE_DIFFERENCE        }, {8.0, 4.0, 1.0}  } ,
           {  {FIRST_DERIVATIVE_OF_WAVELENGTH  , GAP                      }, {8.0, 4.0, 1.0}  } ,
           {  {SECOND_DERIVATIVE_OF_WAVELENGTH , SAVITZJY_GOLAY_ALGORITHM }, {7.0, 6.0, 2.0}  } ,
           {  {SECOND_DERIVATIVE_OF_WAVELENGTH , GAP                      }, {7.0, 6.0, 2.0}  }
      };

      for(auto derivativeparam : derivativeparams)
      {
            // Test Calibration Set
            statistic.Clear();
            test.Run(statistic,0,{new  DerivativeInputParam(DERIVATIVE_SPECTRA,0 ,  derivativeparam )});

            // Run with Test files
            statistic.Clear();
            test.Run(statistic,1);
      }

    cout << endl;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \brief testSavGolayDerivative
///
void testSavGolayDerivative()
{
     Statistic statistic;

      Test test({ 1076,1,1,{0,1076},{100,250},{100,250},50,"",-1});

      vector<pair<pair<DerivativeSpectraType, DerivativeAlgorithmType>,vector<double>>> derivativeparams =
      {
           {  {ZERO_DERIVATIVE_SPECTRA         , SAVITZJY_GOLAY_ALGORITHM }, {5.0, 10.0, 0.0}  } ,
           {  {FIRST_DERIVATIVE_OF_WAVELENGTH  , SAVITZJY_GOLAY_ALGORITHM }, {5.0, 3.0, 1.0 }  } ,
           {  {SECOND_DERIVATIVE_OF_WAVELENGTH , SAVITZJY_GOLAY_ALGORITHM }, {5.0, 3.0, 1.0 }  } ,
           {  {ZERO_DERIVATIVE_SPECTRA         , SAVITZJY_GOLAY_ALGORITHM }, {5.0, 10.0,10.0}  } , // 10th derivative
      };

      for(auto derivativeparam : derivativeparams)
      {
            // Test Calibration Set
            statistic.Clear();
            test.Run(statistic,0,{new  DerivativeInputParam(DERIVATIVE_SPECTRA,0 ,  derivativeparam )});

            // Run with Test files
            statistic.Clear();
            test.Run(statistic,1);
      }
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \brief testSimpleDifference
/// Used only to find first derivative
void testSimpleDifference()
{
     Statistic statistic;

      Test test({ 1076,1,1,{0,1076},{100,250},{100,250},50,"",-1});
      // Test Calibration Set
      statistic.Clear();
      test.Run(statistic,0,{new  DerivativeInputParam(DERIVATIVE_SPECTRA,0 ,{  {FIRST_DERIVATIVE_OF_WAVELENGTH  , SIMPLE_DIFFERENCE }, {0.0, 0.0, 1.0 }  } )});
      // Run with Test files
       statistic.Clear();
       test.Run(statistic,1);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \brief testGap
///
void testGap()
{
     Statistic statistic;

     Test test({ 1076,1,1,{0,1076},{100,250},{100,250},50,"",-1});

     vector<pair<pair<DerivativeSpectraType, DerivativeAlgorithmType>,vector<double>>> derivativeparams =
     {
          {  {FIRST_DERIVATIVE_OF_WAVELENGTH  , GAP }, { 3.0, 0.0, 1.0 }  } ,
          {  {SECOND_DERIVATIVE_OF_WAVELENGTH , GAP }, { 3.0, 0.0, 2.0 }  } ,
     };

     for(auto derivativeparam : derivativeparams)
     {
           // Test Calibration Set
           statistic.Clear();
           test.Run(statistic,0,{new  DerivativeInputParam(DERIVATIVE_SPECTRA,0 ,  derivativeparam )});

           // Run with Test files
           statistic.Clear();
           test.Run(statistic,1);
     }
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \brief testMeanCentering
///
void testMeanCentering()
{
     Statistic statistic;
     vector<int> selectedSamples = {400,100,10,1};

     for(auto selectedSample: selectedSamples)
     {
           Test test({ 1076,selectedSample,selectedSample,{0,1076},{0,330},{0,329},50,"",-1});
           // Test Calibration Set
           statistic.Clear();
           test.Run(statistic,0,{new   MeanCenteringInputParam(MEAN_CENTERING_SPECTRA,0 , COMPUTE_MEAN_SPECTRUM )});

           // Run with Test files
           statistic.Clear();
           test.Run(statistic,1);
     }
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \brief testPreprocessing
///
void testPreprocessing()
{
  Statistic statistic;
 // run test with calibration set
  Test test
 (
     statistic,0,
     {1076,400,400,{0,1076},{0,300},{0,329},50,"",-1},
     {
       new BaselineInputParam( BASE_LINE_CORRECTION,0,{{SIMPLE_OFFSET_CORRECTION,NOT_SET},{{},-1}}),
       new PreprocessingInputParam(PREPROCESSING,1,BASE_PREPROCESSING)
     }
  );

  // run test with test set
  test.Run(statistic,1);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \brief testCalibration
///
void testCalibration( )
{
  Statistic statistic;
  vector<CalibrationType> calibrations = {MULTIVARIATE_CALIBRATION,UNIVARIATE_CALIBRATION };
  vector<AlgorithmType> algorithms   = {NIPALS_ALGORITHM,LIBPCA};

  Test test({ 1076,400,400,{0,1076},{0,330},{0,329},50,"",-1});

  for(auto calibration : calibrations)
  {
      for(auto algorithm: algorithms)
      {
         // run test with calibration set
         test.Run
         (
             statistic,0,
             {
                 //new BaselineInputParam( BASE_LINE_CORRECTION,0,{{SIMPLE_OFFSET_CORRECTION,NOT_SET},{{},-1}}),
                 new   MeanCenteringInputParam(MEAN_CENTERING_SPECTRA,0 , COMPUTE_MEAN_SPECTRUM ),
                 new   BaselineInputParam
                 (
                       BASE_LINE_CORRECTION,1,
                       {
                         {GIFTS ,NOT_SET},
                         {selectNRandomPoints(test.getInputVariable().numberOfSelectedVariables,0, test.getInputVariable().numberOfSelectedVariables),-1},
                       }
                 ),
                 new   CalibrationInputParam(CALIBRATION,2,calibration, algorithm)
             }
          );

          // run test with test set
          test.Run(statistic,1);
      }
  }
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \brief testCalibration
///
void testUnivariateCalibration()
{
  Statistic statistic;
  vector<CalibrationType> calibrations = {UNIVARIATE_CALIBRATION };
  vector<AlgorithmType> algorithms   = {NIPALS_ALGORITHM,LIBPCA};

  Test test({ 1076,400,400,{0,1076},{0,330},{0,329},50,"",-1});

  for(auto calibration : calibrations)
  {
      for(auto algorithm: algorithms)
      {
         // run test with calibration set
         test.Run
         (
             statistic,0,
             {
                 //new BaselineInputParam( BASE_LINE_CORRECTION,0,{{SIMPLE_OFFSET_CORRECTION,NOT_SET},{{},-1}}),
                 new   MeanCenteringInputParam(MEAN_CENTERING_SPECTRA,0 , COMPUTE_MEAN_SPECTRUM ),
                 new   BaselineInputParam
                 (
                       BASE_LINE_CORRECTION,1,
                       {
                         {GIFTS ,NOT_SET},
                         {selectNRandomPoints(test.getInputVariable().numberOfSelectedVariables,0, test.getInputVariable().numberOfSelectedVariables),-1},
                       }
                 ),
                 new   CalibrationInputParam(CALIBRATION,2,calibration, algorithm)
             }
          );

          // run test with test set
          test.Run(statistic,1);
      }
  }
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \brief testMultivariateCalibration
///
void testMultivariateCalibration()
{
  Statistic statistic;
  vector<CalibrationType> calibrations = {MULTIVARIATE_CALIBRATION };
  vector<AlgorithmType> algorithms   = {NIPALS_ALGORITHM,LIBPCA};

  Test test({ 1076,400,400,{0,1076},{0,330},{0,329},50,"",-1});

  for(auto calibration : calibrations)
  {
      for(auto algorithm: algorithms)
      {
         // run test with calibration set
         test.Run
         (
             statistic,0,
             {
                 //new BaselineInputParam( BASE_LINE_CORRECTION,0,{{SIMPLE_OFFSET_CORRECTION,NOT_SET},{{},-1}}),
                 new   MeanCenteringInputParam(MEAN_CENTERING_SPECTRA,0 , COMPUTE_MEAN_SPECTRUM ),
                 new   BaselineInputParam
                 (
                       BASE_LINE_CORRECTION,1,
                       {
                         {GIFTS ,NOT_SET},
                         {selectNRandomPoints(test.getInputVariable().numberOfSelectedVariables,0, test.getInputVariable().numberOfSelectedVariables),-1},
                       }
                 ),
                 new   CalibrationInputParam(CALIBRATION,2,calibration, algorithm)
             }
          );

          // run test with test set
          test.Run(statistic,1);
      }
  }
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \brief testValidation
///
void testValidation()
{
  Statistic statistic;
  vector<CalibrationType> calibrations = {MULTIVARIATE_CALIBRATION };
  vector<AlgorithmType> algorithms   = {NIPALS_ALGORITHM,LIBPCA};

  Test test({ 1076,400,50,{0,1076},{0,330},{0,329},50,"",-1});

  for(auto calibration : calibrations)
  {
      for(auto algorithm: algorithms)
      {
         // run test with calibration set
         test.Run
         (
             statistic,0,
             {
                 //new BaselineInputParam( BASE_LINE_CORRECTION,0,{{SIMPLE_OFFSET_CORRECTION,NOT_SET},{{},-1}}),
                 new   MeanCenteringInputParam(MEAN_CENTERING_SPECTRA,0 , COMPUTE_MEAN_SPECTRUM ),
                 new   BaselineInputParam
                 (
                       BASE_LINE_CORRECTION,1,
                       {
                         {GIFTS ,NOT_SET},
                         {selectNRandomPoints(test.getInputVariable().numberOfSelectedVariables,0, test.getInputVariable().numberOfSelectedVariables),-1},
                       }
                 ),
                 new   CalibrationInputParam(CALIBRATION,2,calibration, algorithm)
             }
          );
           statistic.Clear();
          // run test with test set
          test.Run
          (
                statistic,1,
                {
                      new   MeanCenteringInputParam(MEAN_CENTERING_SPECTRA,0 , COMPUTE_MEAN_SPECTRUM ),
                      new   BaselineInputParam
                      (
                            BASE_LINE_CORRECTION,1,
                            {
                              {GIFTS ,NOT_SET},
                              {selectNRandomPoints(test.getInputVariable().numberOfSelectedVariables,0, test.getInputVariable().numberOfSelectedVariables),-1},
                            }
                      ),
                      // new  CalibrationInputParam(CALIBRATION,2,NO_CALIBRATION_TYPE, algorithm),
                      new   ValidationInputParam(VALIDATION,2,TESTINGSET)
               }
          );
      }
  }
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \brief testGeneticAlgFindVariablesRange
/// \return
///
void testGeneticAlgFindVariablesRange()
{
    ///////////////////////////////////////   Pick Variables Genetic Algorithm /////////////////////////////////////////////////////////////////////////////////////////////

   /* std::vector<Stat> bestVariablesRanges = testFindVariablesRanges();
    for(auto b: bestVariablesRanges)
    {
        b.printToFile("VariableSelection.txt");
    }*/

   int NumberOfPCA = 2;

    Test testtry({ -1,-1,-1,{-1,-1},{-1,-1},{-1,-1},NumberOfPCA,"",-1});

    InputVariables inputtry = testtry.getInputVariable();
    Stat best; 
    int numberOfVariables = inputtry.numberOfSelectedVariables;

    vector<int> selectedForGA = {};

    int varstart  = 0;
    int varend = numberOfVariables;
    int populationSize = 128;
    int blocksize = std::ceil((varend-varstart) / log2((double)128));
    pair<double,double> fitnessLimits(0.05,7.0);
    double currentFitness = 100;
    double minFitness = currentFitness;
    int NumberOfGenerations  = 5;
    string file_in_out = "Variables10.txt";
    string file_in_out_min = "VariablesMin.txt";
    int Rank = -1;
    int count = 0;
    do
    {

      testtry.GetSetVariavleIndexFromTheFile(file_in_out,selectedForGA,false);

      if(selectedForGA.size() > 0)
      {
          for(auto var: selectedForGA)
          {
                cout << var<< " ";
          }
          cout << endl << "Number Of Selected Variables = "<< selectedForGA.size()<< " Round = " << count << endl;
          varstart  = 0;                  // or could be  = selectedForGA[0]
          varend = selectedForGA.size();  //              = selectedForGA[selectedForGA.size() - 1]
          blocksize = std::ceil((varend-varstart) / log2((double)128));
      }
      testtry.PickVariables
      (
                  selectedForGA,numberOfVariables,populationSize,varstart,varend,
                  fitnessLimits,Rank,currentFitness,
                  blocksize,NumberOfGenerations,file_in_out
      );
      if(currentFitness < minFitness )
      {
          minFitness = currentFitness;
          testtry.GetSetVariavleIndexFromTheFile(file_in_out,selectedForGA,false);
          testtry.GetSetVariavleIndexFromTheFile(file_in_out_min,selectedForGA,true);
      }
      cout << "Current Rank = "<< Rank << " RMS Value = " << currentFitness << " Min fitness = " << minFitness << " Count = " << count << endl;

      bool exit = (Rank == 0) || (Rank == 1 && count == 10) || (Rank == 2 && count == 15) || (Rank == 3 && count == 20);
      if(exit)
      {
          break;
      }
       count++;
    }
    while(1);

}

void testVariablesStatistics()
{
    vector<Stat> varStat;
    vector<Stat> varStatWithOneMissing;
    vector<int> selectedForGA;
    int NumberOfPCA = 2;

    Test testtry({ -1,-1,-1,{-1,-1},{-1,-1},{-1,-1},NumberOfPCA,"",-1});

    InputVariables inputtry = testtry.getInputVariable();

    int size = inputtry.numberOfSelectedVariables;

     vector<vector<int>> limits;
     vector<vector<int>> limitWithOneMissing;
     vector<double> rmse;
     vector<double> rmseWithOneMissing;
     vector<double> varIndex;
     vector<double> varIndexWithOneMissing;
     for(int i =0;i < size;i++)
     {
         vector<int> l = {i};
         limits.push_back(l);

     }
     for(int i =0;i < size;i++)
     {
         vector<int> l;
         for(int j =0;j< size;j++)
         {
             if(i != j)
               l.push_back(j);
         }
         limitWithOneMissing.push_back(l);

     }
     for(int i =324;i < ( int)limitWithOneMissing.size();i++)
     {
        varStatWithOneMissing.push_back(testtry.testVariables( testtry,  limitWithOneMissing[i]));
        rmseWithOneMissing.push_back(varStatWithOneMissing[varStatWithOneMissing.size() - 1].RMSEAVERAGE);
        varIndexWithOneMissing.push_back((double)i);
       varStatWithOneMissing[varStatWithOneMissing.size() -1].printToFile("EachVarStatAllWithOneMissing.txt",i);
     }
     if((int)varStatWithOneMissing.size() > 0)
     {
        std::sort(varStatWithOneMissing.begin (),varStatWithOneMissing.end(),varStatWithOneMissing[0]);
        for(auto b: varStatWithOneMissing)
        {
            b.printToFile("EachVarStatAllWithOneMissing.txt");
        }
     }
     BaseFunction::m_plot->Show = true;
     TaskOptionsParameters t = testtry.getTaskOptionParam();
     BaseFunction::m_plot->ShowFunction({{rowvec(varIndexWithOneMissing),rowvec(rmseWithOneMissing) }}, t);
     /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
     for(int i =0;i < ( int)limits.size();i++)
     {
        varStat.push_back(testtry.testVariables( testtry,  limits[i]));
        rmse.push_back(varStat[varStat.size() - 1].RMSEAVERAGE);
        varIndex.push_back((double)i);
     }

     if((int)varStat.size() > 0)
     {
        std::sort(varStat.begin (),varStat.end(),varStat[0]);
        for(auto b: varStat)
        {
            b.printToFile("EachVarStatAll.txt");
        }
     }

      t = testtry.getTaskOptionParam();
      BaseFunction::m_plot->ShowFunction({{rowvec(varIndex),rowvec(rmse) }}, t);
     // BaseFunction::m_plot->ShowFunction({{t.m_currentValuesOfX,t.m_currentPopulationMatrix }}, t);
    limits.clear();
    vector<int> limit ;

    vector<int> deltas= {12,13,14,16,17,18,19,20,21,23,25,26,430,32,35,36,38,39,41,43,46,48,57,59,62,64,65,66,67,73,78,80,82};
    vector<Stat> bests;
    for(int a = 0;a < (int)deltas.size();a++)
    {
        limit.clear();
        for(int i =0;i < (int)varStat.size();i++)
        {
            if(varStat[i].RMSEAVERAGE < deltas[a])
            {
                limit.push_back(varStat[i].variableStart);
            }

        }
        std::sort(limit.begin(),limit.end());
        bests.push_back(testtry.testVariables( testtry,  limit));
        if(deltas[a] == 20)
        {
            selectedForGA = limit;
        }
    }
    if(bests.size() > 0 )
    {
        std::sort(bests.begin(),bests.end(),bests[0]);
        for(int a;a < (int)deltas.size();a++)
        {
            bests[a].printToFile("EachVarStatSelected.txt",deltas[a],-1,-1,-1,true);
        }
    }
    pair<double,double> fitnessLimits(0.001,7.5);
    double currentFitness = 100.00;
    selectedForGA = {88,126};//{5,23,54,88,126};
    int maxNumberOfGenerations = 5;
    int blocksize = 1;
    int Rank = -1;
    string file_in_out = "Variables12.txt";
    if(selectedForGA.size() > 0)
    {
      testtry.PickVariables
      (
                  selectedForGA,size,min(200,  (int) pow(2,(double)selectedForGA.size()) - 1  ),
                  -1,-1,fitnessLimits,Rank,currentFitness, blocksize,maxNumberOfGenerations,file_in_out
      );
    }
  }
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \brief testFindVariablesRanges
///
std::vector<Stat> testFindVariablesRanges()
{
    ///////////////////////////////////////   Pick Variables  /////////////////////////////////////////////////////////////////////////////////////////////

    std::vector<Stat> bestVariablesRanges;
    int NumberOfPCA = 2;

    Test testtry({ -1,-1,-1,{-1,-1},{-1,-1},{-1,-1},NumberOfPCA,"",-1});

    InputVariables inputtry = testtry.getInputVariable();
    Stat best;
    int size = inputtry.numberOfSelectedVariables;
    int startpercent = 75;
    int endpercent = 5;
    double startError = 100.0;
    double endError = 15.0;
    int percentdecrement = 50;
    int count= 1;
    int alg = 1;
     /*int startpercent = 50;
     int endpercent = 24;
     double startError = 50.0;
     double endError = 15.0;
     int percentdecrement = 50;
     int count= 1;
     int alg = 0;*/
    testtry.SelectGARange
    (
                size,startpercent,endpercent, percentdecrement,startError,endError,
                bestVariablesRanges,
                alg,count
    );

    for(auto b: bestVariablesRanges)
    {
        b.printToFile("VariableSelection.txt",-1,-1,-1,count,true);
    }
    return bestVariablesRanges;
}
std::vector<Stat>  testFindVariablesRange()
{
    ///////////////////////////////////////   Pick Variables  /////////////////////////////////////////////////////////////////////////////////////////////
    std::vector<Stat> bestVariablesRange;

    int NumberOfPCA = 2;

    Test testtry({ -1,-1,-1,{-1,-1},{-1,-1},{-1,-1},NumberOfPCA,"",-1});

    InputVariables inputtry = testtry.getInputVariable();
    Stat best;
    int size = inputtry.numberOfSelectedVariables;
    int startpercent = 50;
    int endpercent = 13;
    double startError = 50.0;
    double endError = 3.0;
    int percentdecrement = 50;
    int count= 1;

    testtry.PickVariables(size,startpercent,endpercent, percentdecrement,startError,endError,bestVariablesRange,count);

    for(auto b: bestVariablesRange)
    {
        b.printToFile("VariableSelection.txt");
    }
    return  bestVariablesRange;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \brief getFakeVariablesRange
/// \return
///
std::vector<Stat>  getFakeVariablesRange()
{
     std::vector<Stat> bestVariablesRange;
     vector<pair<int,int>> limits = {{122,129},{123,125}};

     for(auto l: limits)
     {
         Stat s;
         s.variableStart = l.first;
         s.variableEnd = l.second;
         bestVariablesRange.push_back(s);
     }
     return bestVariablesRange;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \brief testCrossValidation
///
void testCrossValidationAndPrediction()
{
    ///////////////////////////////////////   Pick Variables  /////////////////////////////////////////////////////////////////////////////////////////////
  // std::vector<Stat> bestVariablesRange = testFindVariablesRange();

    int NumberOfPCA = 2;

    Test testtry({ -1,-1,-1,{-1,-1},{-1,-1},{-1,-1},NumberOfPCA,"",-1});

    InputVariables inputtry = testtry.getInputVariable();
    string file_in = "VariablesMin.txt";
    testtry.GetSetVariavleIndexFromTheFile(file_in,inputtry.selectedVariableIndex,false);
    if(inputtry.selectedVariableIndex.size() > 0)
    {
        inputtry.selectXPoints = {inputtry.selectedVariableIndex[0],inputtry.selectedVariableIndex[inputtry.selectedVariableIndex.size() - 1]};
    }

    inputtry.maxNumberOfPCA = 2;

    Stat best;
    ////////////////////////////////////////////////////////////////////////////// Start Test ////////////////////////////////////////////////////////////////
    Statistic statistic;
    vector<CalibrationType> calibrations = {MULTIVARIATE_CALIBRATION };
      vector<AlgorithmType> algorithms   = {NIPALS_ALGORITHM};
      // 123-159,  125-229, 123-174,123-162

      Test test = testtry;
      test.setVariablesLimits(inputtry);

          vector<pair<int,int>> setoptions = {{0,1}};//,{1,0}};


          if(inputtry.numberOfSelectedSamplesTest <=0 || inputtry.numberOfSelectedSamplesCalib <= 0)
              return;
          vector<double> percentage = {0.31};//0.31,3.10,30.40,100};
          vector<int> kfoldrangepair1;
          vector<int> kfoldrangepair2;

          vector< vector<int> > kfoldrange = vector< vector<int> >(2);
          for(int i=0;i< (int)percentage.size();i++)
          {
              kfoldrangepair1.push_back((int)(percentage[i] * inputtry.numberOfSelectedSamplesCalib / 100));
              kfoldrangepair2.push_back((int)(percentage[i] * inputtry.numberOfSelectedSamplesTest / 100));
          }
          kfoldrange = {kfoldrangepair1,kfoldrangepair2};

          for(auto calibration : calibrations)
          {
              for(auto algorithm: algorithms)
              {
                   int opt = 0;

                   for(auto option: setoptions)
                   {
                         for(int i = 0;i < (int)kfoldrange[opt].size();i++)
                         {
                             // run test with calibration set
                             test.Run
                             (
                                 statistic,option.first,
                                 {
                                     //new BaselineInputParam( BASE_LINE_CORRECTION,0,{{SIMPLE_OFFSET_CORRECTION,NOT_SET},{{},-1}}),
                                     //new   MeanCenteringInputParam(MEAN_CENTERING_SPECTRA,1 , COMPUTE_MEAN_SPECTRUM ),
                                     new   BaselineInputParam
                                     (
                                           BASE_LINE_CORRECTION,0,
                                           {
                                             {GIFTS ,NOT_SET},
                                             {selectNRandomPoints(inputtry.numberOfSelectedVariables,0, inputtry.numberOfSelectedVariables),-1},
                                           }
                                     ),
                                     new   CalibrationInputParam(CALIBRATION,2,calibration, algorithm),
                                     new   ValidationInputParam(VALIDATION,3,KFOLDCROSSVALIDATION, kfoldrange[opt][i] )
                                 }
                              );
                              best = statistic.m_bestFitCalibration[0];
                              statistic.Clear();
                              // run test with test set
                              test.Run
                              (
                                    statistic,option.second,
                                    {
                                          new   MeanCenteringInputParam(MEAN_CENTERING_SPECTRA,1 , COMPUTE_MEAN_SPECTRUM ),
                                          new   BaselineInputParam
                                          (
                                                BASE_LINE_CORRECTION,0,
                                                {
                                                  {GIFTS ,NOT_SET},
                                                  {selectNRandomPoints(inputtry.numberOfSelectedVariables,0, inputtry.numberOfSelectedVariables),-1},
                                                }
                                          ),

                                          new   PredictionInputParam(PREDICTION,2,KFOLDPREDICTION )
                                   }
                              );

                              statistic.Clear();

                          }
                     }
                     opt++;
                 }
            }
}
