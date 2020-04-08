/*
 * Test.cpp
 *
 *  Created on: May 13, 2016
 *      Author: inna
 */

#include "Test.h"

namespace NDUV
{
        Avs Test::m_avs;
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Test::Test
        /// \param s
        /// \param currentSet
        /// \param testInput
        /// \param tasksInputParameters
        ///
        Test::Test(Statistic &s, int currentSet,InputVariables testInput,const vector<TaskInputParam*> &tasksInputParameters)
        {
             Init();
             m_InputVar = testInput;
             int result = m_InputVar.checkLimits(Statistic::convToStd( mFullXPoints),(int)m_FullCalibrationMatrix.n_rows,(int)m_FullTestMatrix.n_rows,*this);
             if(result != 0 )
             {
                cout << testInput.errorMessage << endl;
                return;
             }
             Run(s,currentSet,tasksInputParameters);
        }
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Test::Test
        /// \param testInput
        ///
         Test::Test(InputVariables testInput)
         {
              Init();
              m_InputVar = testInput;
              m_InputVar.result = m_InputVar.checkLimits(Statistic::convToStd( mFullXPoints),(int)m_FullCalibrationMatrix.n_rows,(int)m_FullTestMatrix.n_rows,*this);
              if(m_InputVar.result != 0 )
              {
                 cout << testInput.errorMessage << endl;
                 return;
              }
         }
         ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
         /// \brief Test::~Test
         ///
        Test::~Test()
        {
            m_TasksMap.clear();
            m_CurrentTests.clear();
        }
        InputVariables Test::getInputVariable()
        {
             return m_InputVar;
        }
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Test::setVariablesLimits
        /// \param testInput
        ///
        void Test::setVariablesLimits(InputVariables testInput)
        {
            m_InputVar = testInput;
            m_InputVar.result = m_InputVar.checkLimits(Statistic::convToStd( mFullXPoints),(int)m_FullCalibrationMatrix.n_rows,(int)m_FullTestMatrix.n_rows,*this);
            if(m_InputVar.result != 0 )
            {
               cout << testInput.errorMessage << endl;
               return;
            }
        }
        ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Test::GetVariavleIndexFromTheFile
        /// \param filename
        /// \return
        ///
        void Test::GetSetVariavleIndexFromTheFile(string filename,vector<int> &vars ,bool set)
        {
            std::fstream fs;
            string line;
            if(set)
            {
                    fs.open (filename,  std::fstream::out  | std::fstream::trunc);
                    if (fs.is_open())
                    {
                        for(auto var: vars)
                        {
                           fs << var << " ";
                        }
                    }
                    else
                    {
                        cout << "Unable to open " + filename  + " for output" << endl;
                    }
             }
             else
             {
                    fs.open (filename, std::fstream::in );
                    if (fs.is_open())
                    {
                        vars.clear();
                        while (!fs.eof() )
                        {
                            line = "";
                            fs >> line;
                            if(line == "")
                                break;
                            std::string::size_type sz;
                            vars.push_back (std::stoi (line,&sz));
                        }
                    }
                    else
                    {
                        cout << "Unable to open " + filename  + " for input" << endl;
                    }
              }
              fs.close();

        }
        ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Test::SelectCalibAndTestData
        /// \param selectedVariables
        /// \param SelectedSamplesCalib
        /// \param SelectedSamplesTest
        ///
        void Test::SelectCalibAndTestData(vector<int> selectedVariables,vector<int> SelectedSamplesCalib ,vector<int> SelectedSamplesTest )
        {
             m_selectedData.m_totalNPOINTS = 0;
             m_selectedData.m_NumberOfVariables = (int)selectedVariables.size();
             m_selectedData.m_NumberOfSamplesCalib   = (int)SelectedSamplesCalib.size();
             m_selectedData.m_NumberOfSamplesTest    = (int)SelectedSamplesTest.size();
             m_selectedData.m_VariableIndex = selectedVariables;
             m_selectedData.m_SampleIndexCalib = SelectedSamplesCalib;
             m_selectedData.m_SampleIndexTest = SelectedSamplesTest;

             SelectXPoints(m_selectedData);
             //printDataMaps();
        }

        ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Test::Init
        ///
        void Test::Init()
        {
            path = PATH;
            directory = DIRECTORY_NAME_TESTFILES;
            ProcessDirectory(directory);
            m_InitialiedParameters = false;
            m_InitialiedTasks = false;
        }
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Test::getMapKey
        /// \return
        ///
        vector<int> Test::getMapKey( )
        {
             vector<int> result;
             for(auto m: m_TasksMap)
              {
                 result.push_back(m.first);
              }
              return result;
        }
        ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Tests::DeleteTest
        /// \param parameters
        ///
        void Test::DeleteTask(int index)
        {
            map<int,task>::iterator it = m_TasksMap.find(index);
            if( it != m_TasksMap.end())
            {
                m_TasksMap.erase(it);
            }
        }
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Test::ProcessDirectory
        /// \param directory
        ///
        void Test::ProcessDirectory(std::string directory)
        {
            std::string dirToOpen = path + directory;
               auto dir = opendir(dirToOpen.c_str());

               //set the new path for the content of the directory
               path = dirToOpen + "/";

               std::cout << "Process directory: " << dirToOpen.c_str() << std::endl;

               if(NULL == dir)
               {
                   std::cout << "could not open directory: " << dirToOpen.c_str() << std::endl;
                   return;
               }

               auto entity = readdir(dir);

               while(entity != NULL)
               {
                   pair<int,tuple<Constituents,double,map<int,Point>,int,Point,Point>> spectradata = ProcessEntity(path,entity);
                   m_SpectraDataMap[spectradata.first] = spectradata.second;

                   entity = readdir(dir);
               }

               //we finished with the directory so remove it from the path
               path.resize(path.length() - 1 - directory.length());
               closedir(dir);

               CreateMatrixData(m_SpectraDataMap);
               setfilesData();
               m_FullCalibrationMatrix = m_CalibrationDataMap;
               m_FullTestMatrix = m_TestDataMap;
               m_FullCalibConcentrationMatrix =  m_CalibConcentrationMap;
               m_FullTestConcentrationMatrix = m_TestConcentrationMap;
               mFullXPoints = mXPoints;
               m_FullzeroTransmissionSpectra =  m_zeroTransmissionSpectra;
               //SelectXPoints(m_selectedData);
               //printDataMaps();
        }
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Test::setfilesData
        ///
         void Test::setfilesData()
         {
             m_CalibRows.first = 0;
             m_CalibRows.second = m_CalibrationDataMap.n_rows -1;

             m_TestRows.first  = 0;
             m_TestRows.second = m_TestDataMap.n_rows - 1;

             m_filesCalib.first = 0;
             m_filesCalib.second = m_CalibRows.second;
             m_filesTest.first = m_CalibRows.second + 1;
             m_filesTest.second = m_CalibRows.second  + m_TestDataMap.n_rows;

         }
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Test::printDataMaps
        ///
         void Test::printDataMaps()
         {
             cout << "Results = "<< endl;
             cout <<"m_CalibrationDataMap  = " << endl;
             cout << setw(2) << "[" <<
                      0  <<
                     "]" ;
             for(auto v: m_selectedData.m_VariableIndex)
             {
                 cout << setw(4) << "[" <<
                          v  <<
                         "]" ;


             }
              cout << endl;

              for(int i = 0;i < (int)m_selectedData.m_SampleIndexCalib.size();i++)
              {

                  cout << setw(3) << 2 * m_selectedData.m_SampleIndexCalib[i];
                  for(int j =0;j < (int)m_selectedData.m_VariableIndex.size();j++)
                  {
                       cout << setw(8) << setprecision(4) << m_CalibrationDataMap(i,j);
                  }
                  cout << endl;
              }

              cout << "m_TestDataMap  = " << endl;
              cout << setw(2) << "[" <<
                       0  <<
                      "]" ;
              for(auto v: m_selectedData.m_VariableIndex)
              {
                  cout << setw(4) << "[" <<
                           v  <<
                          "]" ;
              }
               cout << endl;
              for(int i = 0;i < (int)m_selectedData.m_SampleIndexTest.size();i++)
              {

                  cout << setw(3) <<  2 * m_selectedData.m_SampleIndexTest[i] + 1;
                  for(int j =0;j < (int)m_selectedData.m_VariableIndex.size();j++)
                  {
                       cout << setw(8) << setprecision(4) <<  m_TestDataMap(i,j);
                  }
                  cout << endl;
              }

             mXPoints.print("mXPoints = ");

             cout << "m_CalibConcentrationMap = " << endl;

             for(int i = 0;i < (int)m_selectedData.m_SampleIndexCalib.size();i++)
             {

                 cout << setw(3) <<  2 * m_selectedData.m_SampleIndexCalib[i];
                 for(int j =0;j < (int)m_CalibConcentrationMap.n_cols;j++)
                 {
                      cout << setw(8) << setprecision(4) <<  m_CalibConcentrationMap(i,j);
                 }
                 cout << endl;
             }

             cout << "m_TestConcentrationMap = " << endl;

             for(int i = 0;i < (int)m_selectedData.m_SampleIndexTest.size();i++)
             {
                 cout << setw(3) <<   2 * m_selectedData.m_SampleIndexTest[i] + 1;
                 for(int j =0;j < (int)m_TestConcentrationMap.n_cols;j++)
                 {
                      cout << setw(8) << setprecision(4) <<  m_TestConcentrationMap(i,j);
                 }
                 cout << endl;
             }
             cout << endl;
         }
             //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
             /// \brief Test::SelectXPoints
             /// \param numberOfPoints
             /// \return
             ///
              void Test::SelectXPoints(SelectedData &selectdata)
              {
                   selectdata.m_totalSamplesCalib = (int)m_CalibrationDataMap.n_rows;
                   selectdata.m_totalSamplesTest = (int)m_TestDataMap.n_rows;
                   selectdata.m_totalNPOINTS = mXPoints.n_cols;

                   int NumberOfVariables = min(selectdata.m_NumberOfVariables,selectdata.m_totalNPOINTS);
                   cout << "Maximum number Of selected variables = " << NumberOfVariables << endl;
                   if(selectdata.m_VariableIndex.size() <= 0)
                   {
                        selectdata.m_VariableIndex = getSelectedIndex(m_selectedData.m_totalNPOINTS,NumberOfVariables);
                   }

                   int NumberOfSamplesCalib = min(selectdata.m_totalSamplesCalib,selectdata.m_NumberOfSamplesCalib);
                   cout << "Maximum number Of selected calibration samples = " << NumberOfSamplesCalib << endl;
                   if(selectdata.m_SampleIndexCalib.size() <= 0)
                   {
                        selectdata.m_SampleIndexCalib = getSelectedIndex(selectdata.m_totalSamplesCalib,NumberOfSamplesCalib);
                   }

                   int NumberOfSamplesTest = min(selectdata.m_totalSamplesTest,selectdata.m_NumberOfSamplesTest);
                   cout << "Maximum number Of selected test samples = " << NumberOfSamplesTest << endl;
                   if(selectdata.m_SampleIndexTest.size() <= 0)
                   {
                        selectdata.m_SampleIndexTest = getSelectedIndex(selectdata.m_totalSamplesTest,NumberOfSamplesTest);
                   }

                   m_CalibrationDataMap = getSelectedMatrix(m_FullCalibrationMatrix,selectdata.m_SampleIndexCalib,selectdata.m_VariableIndex);

                   m_TestDataMap = getSelectedMatrix(m_FullTestMatrix,selectdata.m_SampleIndexTest,selectdata.m_VariableIndex);

                   m_CalibConcentrationMap = getSelectedMatrix(m_FullCalibConcentrationMatrix,selectdata.m_SampleIndexCalib);
                   m_TestConcentrationMap = getSelectedMatrix(m_FullTestConcentrationMatrix,selectdata.m_SampleIndexTest);
                   vector<int> row = {0};
                   mXPoints = getSelectedMatrix(mFullXPoints,row,selectdata.m_VariableIndex);

                   row = vector<int>(m_zeroTransmissionSpectra.n_rows,0);
                   for(int i=0;i < (int)m_zeroTransmissionSpectra.n_rows;i++)
                   {
                       row[i] = i;
                   }
                   m_zeroTransmissionSpectra = getSelectedMatrix(m_FullzeroTransmissionSpectra,row,selectdata.m_VariableIndex);
              }
              //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
              /// \brief Test::getSelectedMatrix
              /// \param matrix
              /// \param rowindex
              /// \param columnIndex
              /// \return
              ///
              mat Test::getSelectedMatrix(const mat& matrix,const vector<int> & rowindex,const vector<int> & columnIndex)
              {
                      mat result;

                      int numcols = 0;
                      if(columnIndex.size()==0)
                         numcols = (int)matrix.n_cols;
                      else
                         numcols = (int )columnIndex.size();
                      result = mat((int)rowindex.size(),numcols);
                      for(int i = 0;i < (int)rowindex.size();i++)
                          {
                              for(int j=0; j <  numcols;j++)
                              {
                                   int colvalue;
                                   if(columnIndex.size() == 0)
                                       colvalue = j;
                                   else
                                       colvalue = columnIndex[j];
                                   if(rowindex[i] < (int)matrix.n_rows && (int)colvalue < (int)matrix.n_cols)
                                       result(i,j) = matrix(rowindex[i],colvalue);

                                 // cout << rowindex[i]<<" "<< result(i,j);
                                 // cout << endl;
                              }
                          }

                      return result;
                  }
                  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                  /// \brief Test::getSelectedIndex
                  /// \param total
                  /// \param selected
                  /// \return
                  ///
                  vector<int> Test::getSelectedIndex(int total,int selected)
                  {
                          vector<int> result;

                          double distance;

                          if(selected != 0)
                              distance = total / selected;
                          else
                              return result;

                          for(double i=0.0;i < (double)  total; i = i + distance)
                          {
                             result.push_back(i);
                             if((int)result.size() == selected - 1)
                                 break;
                          }
                          result.push_back(total - 1);

                          return result;
                  }

                  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                  /// \brief Test::ProcessFile
                  /// \param dirpath
                  /// \param file
                  /// \return
                  ///
                  map<int,Point> Test::ProcessFile(std::string dirpath,std::string file)
                  {
                        //std::cout << "Process file     : " << file.c_str() << std::endl;
                        string fileName = file.c_str();

                        map<int,Point> result;

                        ifstream currentfile(dirpath + fileName);
                        if (!currentfile)
                        {
                                   cout << "ERROR: appendEntriesFromMovieFile: couldn't open " << currentfile << endl;
                                   exit(1);
                         }

                         string line;
                         m_selectedData.m_totalNPOINTS = 0;
                         m_Factor.x = -1;
                         m_Factor.y = -1;
                         m_MinMax.x = -1;
                         m_MinMax.y = -1;
                         for(int i=0;i< HEADER_LINES;i++)
                         {
                             getline(currentfile, line);
                             vector<string> parameters = {"NPOINTS=","FIRSTX=","LASTX=","XFACTOR=","YFACTOR="};

                             for(int a=0;a < (int)parameters.size();a++)
                             {
                                 string::size_type param = line.find(parameters[a]);
                                 if (param != string::npos)
                                 {
                                     double value = stod(line.substr(param + parameters[a].size(),line.size()-1 - param - parameters[a].size()));
                                     switch(a)
                                     {
                                           case 0:
                                               m_selectedData.m_totalNPOINTS = (int)value;
                                           break;
                                          case 1:
                                             m_MinMax.x = value;
                                           break;
                                          case 2:
                                             m_MinMax.y = value;
                                           break;
                                          case 3:
                                             m_Factor.x = value;
                                           break;
                                           case 4:
                                             m_Factor.y = value;
                                           break;

                                     };
                                 }
                             }

                         }
                         int count=0;
                         while (!currentfile.eof())
                         {
                                getline(currentfile, line);
                                if(line.find("END") != string::npos || count ==  m_selectedData.m_totalNPOINTS)
                                    break;
                                Point point = parseRatingLine(line);

                                result.insert(pair<int,Point>(count,point));

                                count++;
                         }

                         return result;
                    }
                    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                    /// \brief Test::parseRatingLine
                    /// \param line
                    /// \return
                    ///
                    Point Test::parseRatingLine(string line)
                    {
                        Point result ;
                        std::string::size_type sz;     // alias of size_t
                        string::size_type firstComma = line.find(",");
                        string::size_type endof = line.find("##END");
                        if (firstComma != string::npos)
                        {
                             result.x = std::stod (line.substr(0, firstComma),&sz);
                             result.y = std::stod (line.substr(firstComma+1, line.length()));
                        }
                        else if(endof != string::npos)
                        {
                               ;
                        }
                        else
                        {
                             cout << "parseRatingLine: Didn't find first comma in line: " << line << endl;
                        }
                        return result;
                    }
                    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                    /// \brief Test::ProcessEntity
                    /// \param dirpath
                    /// \param entity
                    /// \return
                    ///
                     pair<int,tuple<Constituents,double,map<int,Point>,int,Point,Point>> Test::ProcessEntity(std::string dirpath,struct dirent* entity)
                    {
                         pair<int,tuple<Constituents,double,map<int,Point>,int,Point,Point>> result;
                        //find entity type
                            if(entity->d_type == DT_DIR)
                            {//it's an direcotry
                                //don't process the  '..' and the '.' directories
                                if(entity->d_name[0] == '.')
                                {
                                    return result;
                                }

                                //it's an directory so process it
                                ProcessDirectory(std::string(entity->d_name));
                                return result;
                            }

                            if(entity->d_type == DT_REG)
                            {//regular file
                               std::string fname = std::string(entity->d_name);
                               m_currentSpectraPoints.clear();
                               m_currentSpectraPoints = ProcessFile(dirpath,fname);

                               string::size_type start = (string("Spectrum")).size() ;

                                   string::size_type firstUndescore = fname.find("_");
                                   if (firstUndescore != string::npos)
                                   {
                                        std::string fntext = fname.substr(start, firstUndescore - start);
                                        if(fntext != "")
                                        {
                                             result.first = std::stoi(fname.substr(start, firstUndescore));
                                        }
                                        else
                                        {
                                             result.first = 0;
                                        }
                                        string::size_type secondUndescore = fname.find("_",firstUndescore + 1);
                                        if( secondUndescore != string::npos)
                                        {
                                            std::string textconst = fname.substr(firstUndescore + 1, secondUndescore - firstUndescore - 1);
                                            if(ConstituentsNameInverted.find(textconst) != ConstituentsNameInverted.end())
                                            {
                                                Constituents constituent =  ConstituentsNameInverted.at(textconst);

                                                string::size_type thirdUndescore = fname.find("_",secondUndescore + 1);
                                                if( thirdUndescore != string::npos)
                                                {
                                                    double value = std::stod(fname.substr(secondUndescore + 1, thirdUndescore - secondUndescore - 1));
                                                    result.second = std::make_tuple(constituent,value,m_currentSpectraPoints, m_selectedData.m_totalNPOINTS,m_Factor,m_MinMax);
                                                }
                                            }
                                        }
                                   }


                                return result;
                            }

                            //there are some other types
                            //read here http://linux.die.net/man/3/readdir
                            std::cout << "Not a file or directory: " << entity->d_name << std::endl;
                            return result;
                     }
                    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                    /// \brief Test::CreateMatrixData
                    /// \param smap
                    ///
                     void Test::CreateMatrixData(const SpectraMap & smap)
                     {
                           //  map<int,tuple<Constituents,double,map<int,Point>,int,Point,Point>>
                           int nsamples = (int)smap.size();
                           int min = (int)(smap.begin())->first;
                           int max = (int)((smap.end())--)->first;
                           int nsamplesCalibration = (max - min + 1) / 2;
                           int nsamplesTest = nsamples - nsamplesCalibration;

                           int numberOfDataPoints = std::get<3>((smap.begin())->second);

                           m_CalibrationDataMap = mat (nsamplesCalibration,numberOfDataPoints);
                           m_TestDataMap = mat(nsamplesTest,numberOfDataPoints);
                           mXPoints = mat(1,numberOfDataPoints);
                           map<Constituents,vector<double>> currentConcentrations;
                           vector<rowvec> zerospectra;
                           int ncons=0;
                           for(auto m: smap)
                           {
                               Constituents c =  std::get<0>(m.second);

                               if(ConstituentsName.find( c) != ConstituentsName.end())
                               {
                                   if( m_ConstituesIndexMap.find(c) == m_ConstituesIndexMap.end())
                                   {
                                         m_ConstituesIndexMap[c] = ncons;
                                         ncons++;
                                   }
                               }

                               double concentrationValue =  std::get<1>(m.second);

                               if(concentrationValue == 0.0)
                               {
                                   map<int,Point> zeroSpectra =  std::get<2>(m.second);
                                   vector<double> spectra = mapGetValues(zeroSpectra);
                                   zerospectra.push_back(spectra);
                               }

                           }

                           m_zeroTransmissionSpectra = mat((int)zerospectra.size(),numberOfDataPoints);
                           for(int i  =0;i< (int)zerospectra.size();i++)
                           {
                               m_zeroTransmissionSpectra.row(i) = rowvec(zerospectra[i]);
                           }

                           int numberOfConstituents = m_ConstituesIndexMap.size();
                           m_CalibConcentrationMap = mat(nsamplesCalibration,numberOfConstituents);
                           m_TestConcentrationMap = mat(nsamplesTest,numberOfConstituents);

                           //  map<int,tuple<Constituents,double,map<int,Point>>>
                           // get spectrum

                           int i =0;
                           for(auto m: smap)
                           {
                              mat *cmap,*kmap;
                             if(i % 2 == 0)
                             {
                                 cmap = &m_CalibrationDataMap;
                                 kmap = &m_CalibConcentrationMap;
                             }
                             else
                             {
                                 cmap = &m_TestDataMap;
                                 kmap = &m_TestConcentrationMap;
                             }
                             Constituents c =  std::get<0>(m.second);
                              int consIndex = m_ConstituesIndexMap.at(c);
                              double concentration = std::get<1>(m.second);

                               (*kmap)(i/2,consIndex) = concentration;
                               map<int,Point> spectra = std::get<2>(m.second);
                               int npoint = 0;
                               for(auto s: spectra)
                               {
                                      (*cmap)(i / 2,npoint) = s.second.y;

                                      if(i == 0)
                                      {
                                            mXPoints(0,npoint) = s.second.x;
                                      }
                                      npoint++;
                               }
                              i++;
                           }
                           mXPoints =  mXPoints / m_Factor.x;
                           m_CalibrationDataMap = m_CalibrationDataMap / m_Factor.y;
                           m_TestDataMap =m_TestDataMap / m_Factor.y;
                     }
                     //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                     /// \brief Test::Run
                     /// \param s
                     /// \param currentSet
                     /// \param tasksInputParameters
                     ///
                     void Test::Run(Statistic &s,int currentSet,vector<TaskInputParam*> tasksInputParameters)
                     {
                         if(tasksInputParameters.size() > 0)
                         {
                             m_InitialiedTasks = false;
                         }
                          if(!m_InitialiedParameters)
                          {
                              m_param = GetTemplateParameterFromFiles();
                              resetTaskMap( m_param.m_tasksType);
                              m_OrderIndex = vector<int>(9,8);
                              m_InitialiedParameters = true;
                          }
                          if(!m_InitialiedTasks)
                          {
                                  resetTaskMap( m_param.m_tasksType);
                                  m_OrderIndex = vector<int>(9,8);
                                  for(auto in: tasksInputParameters )
                                  {
                                      if(  TasksIndex.find( in->m_name) != TasksIndex.end() )
                                      {
                                          int index = TasksIndex.at( in->m_name) ;
                                          if(in->m_OrderIndex >= 0 && in->m_OrderIndex <= 8)
                                          {
                                              if(in->m_name ==  CALIBRATION)
                                              {
                                                  m_OrderIndex[index] = in->m_OrderIndex;
                                                  index = TasksIndex.at(ALGORITHM);
                                                  m_OrderIndex[index] = in->m_OrderIndex + 1;
                                              }
                                              else
                                              {
                                                   m_OrderIndex[index] = in->m_OrderIndex;
                                              }
                                          }
                                          else
                                          {
                                              cout <<"Task is not in task range. The range is [ " << 0 << " - "  << 7 << "]";
                                          }
                                      }

                                      if(TasksIndex.find( in->m_name) != TasksIndex.end() )
                                      {
                                          switch(in->m_name)
                                          {
                                                  case PREPROCESSING:
                                                      if(TypeTmap.find(((PreprocessingInputParam*)in)->m_Preprocessing) != TypeTmap.end() )
                                                      {
                                                            m_param.m_tasksType.at(TasksIndex.at( in->m_name)) = TypeTmap.at(((PreprocessingInputParam*)in)->m_Preprocessing);
                                                      }
                                                  break;

                                                  case BASE_LINE_CORRECTION:
                                                      if(TypeTmap.find(((BaselineInputParam*)in)->m_BaseLineParam.first.first) != TypeTmap.end() )
                                                      {
                                                          m_param.m_tasksType.at( TasksIndex.at(in->m_name)) = TypeTmap.at(((BaselineInputParam *)in)->m_BaseLineParam.first.first);

                                                          m_param.m_fitParameters =  m_param.CreateBaselineTemplateParameter
                                                                  (
                                                                    {
                                                                      ((BaselineInputParam *)in)->m_BaseLineParam.first.first,
                                                                      make_tuple
                                                                      (
                                                                         ((BaselineInputParam *)in)->m_BaseLineParam.first.second ,
                                                                         ((BaselineInputParam *)in)->m_BaseLineParam.second.first,
                                                                         ((BaselineInputParam *)in)->m_BaseLineParam.second.second
                                                                      )
                                                                    }

                                                                  );
                                                      }
                                                  break;
                                                  case DATA_SMOOTHING:
                                                      if(TypeTmap.find(((DataSmootingInputParam*)in)->m_DataSmoothingParam.first) != TypeTmap.end() )
                                                      {
                                                          m_param.m_tasksType.at( TasksIndex.at(in->m_name)) = TypeTmap.at(((DataSmootingInputParam*)in)->m_DataSmoothingParam.first );
                                                          if( ((DataSmootingInputParam *)in)->m_DataSmoothingParam.second.size() == 2)
                                                          {
                                                              m_param.m_dataSmoothingParameters = m_param.CreateDataSmoothingParameter
                                                                      (
                                                                          ((DataSmootingInputParam *)in)->m_DataSmoothingParam.first, // Algorithm type [BINOMIAL , SAVITZKI GOLEY]
                                                                          make_tuple
                                                                          (
                                                                               ((DataSmootingInputParam *)in)->m_DataSmoothingParam.second[0], // numberOfPoints
                                                                               ((DataSmootingInputParam *)in)->m_DataSmoothingParam.second[1], // Polinomial Degree
                                                                               0                                                               // derivative order = 0 for data smoothing
                                                                          )
                                                                      );
                                                          }
                                                          else
                                                          {
                                                              cout << "Number Of SMoothing parameters must be 2: [ number Of Points and  Polinimial Degree ] " << endl;
                                                              return;
                                                          }
                                                      }
                                                  break;
                                                  case DERIVATIVE_SPECTRA:
                                                      if(TypeTmap.find(((DerivativeInputParam*)in)->m_DerivativeParam.first.first) != TypeTmap.end() )
                                                      {
                                                         m_param.m_tasksType.at( TasksIndex.at( in->m_name)) = TypeTmap.at(((DerivativeInputParam*)in)->m_DerivativeParam.first.first );
                                                         if(((DerivativeInputParam *)in)->m_DerivativeParam.second.size() == 3)
                                                         {
                                                             m_param.m_derivativeParameters = (m_param.CreateDataDerivativeParameter
                                                                     (
                                                                         ((DerivativeInputParam *)in)->m_DerivativeParam.first.first         ,// [ZERO, FIRST,SECOND, ... N th DERIVATIVE]
                                                                         make_tuple
                                                                         (
                                                                            ((DerivativeInputParam *)in)->m_DerivativeParam.first.second     ,// [SAVOTZKI GOLEY, SIMPLE_DIFFERENCE,GAP,]
                                                                            ((DerivativeInputParam *)in)->m_DerivativeParam.second[0]        ,// number Of Points
                                                                            ((DerivativeInputParam *)in)->m_DerivativeParam.second[1]        ,// polynomial degree
                                                                            ((DerivativeInputParam *)in)->m_DerivativeParam.second[2]         // Derivative Order
                                                                         )
                                                                     )).second;
                                                              m_param.m_derivativeSpectraType.first = ((DerivativeInputParam *)in)->m_DerivativeParam.first.first ;  // [ZERO, FIRST,SECOND, ... N th DERIVATIVE]
                                                              m_param.m_derivativeSpectraType.second = ((DerivativeInputParam *)in)->m_DerivativeParam.first.second ;// [SAVOTZKI GOLEY, SIMPLE_DIFFERENCE,GAP,]
                                                         }
                                                         else
                                                         {
                                                             cout << "Number Of Derivative parameters must be 3: [ number Of Points ,  Polinimial Degree , Derivative Order] " << endl;
                                                             return;
                                                         }
                                                     }
                                                  break;
                                                 case MEAN_CENTERING_SPECTRA:
                                                      if(TypeTmap.find(((MeanCenteringInputParam*)in)->m_MeanCenteringType) != TypeTmap.end() )
                                                      {
                                                        m_param.m_tasksType.at(TasksIndex.at( in->m_name)) = TypeTmap.at(((MeanCenteringInputParam*)in)->m_MeanCenteringType);
                                                      }
                                                  break;
                                                  case CALIBRATION:
                                                      if(TypeTmap.find(((CalibrationInputParam*)in)->m_CalibrationType) != TypeTmap.end() &&
                                                         TypeTmap.find(((CalibrationInputParam*)in)->m_AlgorithmType) != TypeTmap.end()
                                                        )
                                                      {
                                                        m_param.m_tasksType.at( TasksIndex.at(in->m_name)) = TypeTmap.at(((CalibrationInputParam*)in)->m_CalibrationType);
                                                        m_param.m_tasksType.at( TasksIndex.at(ALGORITHM)) = TypeTmap.at(((CalibrationInputParam*)in)->m_AlgorithmType);
                                                      }
                                                 break;
                                                 case VALIDATION:
                                                      if(
                                                         TypeTmap.find(((ValidationInputParam*)in)->m_ValidationType) != TypeTmap.end()
                                                        )
                                                      {
                                                        m_param.m_kfolds = ((ValidationInputParam*)in)->m_foldrange;

                                                        m_param.m_tasksType.at( TasksIndex.at(in->m_name)) = TypeTmap.at(((ValidationInputParam*)in)->m_ValidationType);
                                                      }
                                                  break;
                                                  case PREDICTION:
                                                      if(TypeTmap.find(NO_CALIBRATION_TYPE) != TypeTmap.end() &&
                                                         TypeTmap.find(((PredictionInputParam*)in)->m_PredictionType) != TypeTmap.end()
                                                        )
                                                      {
                                                        m_param.m_tasksType.at( TasksIndex.at(CALIBRATION)) = TypeTmap.at(NO_CALIBRATION_TYPE);
                                                        m_param.m_tasksType.at( TasksIndex.at(in->m_name)) = TypeTmap.at(((PredictionInputParam*)in)->m_PredictionType);
                                                      }
                                                  break;
                                                  case NONE:
                                                  case ALGORITHM:
                                                  break;
                                              }
                                          };
                                      }
                                      s.zeroTransmissionSpectra = m_param.m_zeroTransmissionDatapoints;
                                      m_InitialiedTasks = true;
                              }

                              m_param.m_currentSet = currentSet;
                              if(m_param.m_currentSet == 0)
                              {
                                     s.currentPopulationMatrix = m_param.m_currentPopulationMatrix;
                                     s.currentConcentrationMatrix = m_param.m_concentrations;

                              }
                              else if(m_param.m_currentSet == 1)
                              {
                                     s.currentPopulationMatrix = m_param.m_testingPopulationMatrix;
                                     s.currentConcentrationMatrix = m_param.m_testing_concentrations;
                              }

                              s.numberOfPcaComponents = min(m_InputVar.maxNumberOfPCA,m_param.numOfPCA);
                              s.numberOfPcaComponents = min( s.numberOfPcaComponents,m_param.numOfPCA);
                              s.m_ConstituesIndexMap = m_param.m_ConstituesIndexMap;



                              s = RunTest(s);

                     }
                     ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                     /// \brief Test::AddAndRunFunction
                     /// \param s
                     ///
                     void Test::AddAndRunTasks( Statistic &s )
                     {
                         //Create Tasks
                         //printTasks(m_param);
                         m_param.m_preprocessingType  = ((PreprocessingTaskT*)m_param.m_tasksType.at(TasksIndex.at(PREPROCESSING )))->preprocessing.first;
                         m_param.m_baseLineCorrection =  ((BaseLineCorrectionTaskT*)m_param.m_tasksType.at(TasksIndex.at(BASE_LINE_CORRECTION)))->baselineCorrection.first;
                         m_param.m_dataSmoothing = ((DataSmoothingTaskT *)m_param.m_tasksType.at(TasksIndex.at(DATA_SMOOTHING )))->dataSmooting.first;
                         m_param.m_derivativeSpectraType.first = ((DerivativeSpectraTaskT*)m_param.m_tasksType.at(TasksIndex.at(DERIVATIVE_SPECTRA )))->derivative.first;
                         m_param.m_meanCenteringMethodType = ((MeanCenteringMethodTaskT*)m_param.m_tasksType.at(TasksIndex.at(MEAN_CENTERING_SPECTRA )))->meanCentering.first;
                         m_param.m_calibrationType = ((CalibrationTaskT*)m_param.m_tasksType.at(TasksIndex.at(CALIBRATION )))->calibrationType.first;
                         m_param.m_algorithmType = ((AlgorithmTaskT*)m_param.m_tasksType.at(TasksIndex.at(ALGORITHM   )))->algorithmType.first;
                         m_param.m_validationType = ((ValidationTaskT*)m_param.m_tasksType.at(TasksIndex.at(VALIDATION  )))->validationType.first;
                         m_param.m_predictionType = ((PredictionTaskT*)m_param.m_tasksType.at(TasksIndex.at(PREDICTION  )))->predictionType.first;

                         //printTasks(m_param);

                         vector< map<int,task>::iterator> tests;


                        tests.push_back( m_CurrentTests.find(((PreprocessingTaskT*)m_param.m_tasksType.at(TasksIndex.at(PREPROCESSING )))->preprocessing.second));
                        tests.push_back( m_CurrentTests.find(((MeanCenteringMethodTaskT*)m_param.m_tasksType.at(TasksIndex.at(MEAN_CENTERING_SPECTRA )))->meanCentering.second));
                        tests.push_back( m_CurrentTests.find(((BaseLineCorrectionTaskT*)m_param.m_tasksType.at(TasksIndex.at(BASE_LINE_CORRECTION)))->baselineCorrection.second));
                        tests.push_back( m_CurrentTests.find(((DataSmoothingTaskT *)m_param.m_tasksType.at(TasksIndex.at(DATA_SMOOTHING )))->dataSmooting.second));
                        tests.push_back( m_CurrentTests.find(((DerivativeSpectraTaskT*)m_param.m_tasksType.at(TasksIndex.at(DERIVATIVE_SPECTRA )))->derivative.second));

                        tests.push_back( m_CurrentTests.find(((CalibrationTaskT*)m_param.m_tasksType.at(TasksIndex.at(CALIBRATION )))->calibrationType.second));
                        tests.push_back( m_CurrentTests.find(((ValidationTaskT*)m_param.m_tasksType.at(TasksIndex.at(VALIDATION  )))->validationType.second));
                        tests.push_back( m_CurrentTests.find(((PredictionTaskT*)m_param.m_tasksType.at(TasksIndex.at(PREDICTION  )))->predictionType.second));


                        // Add Tasks
                        for(int i =0;i < (int)tests.size();i++)
                        {
                           if(tests[i] != m_CurrentTests.end())
                           {
                               map<int,task>::iterator it =  m_TasksMap.find(m_OrderIndex[i]);

                               if(it == m_TasksMap.end())
                               {
                                   m_TasksMap[m_OrderIndex[i]] = tests[i]->second;
                               }

                           }
                        }
                        // Run Tasks
                        vector<int> testindex = getMapKey();

                        for(auto index: testindex)
                        {
                             map<int,task>::iterator currenttest = m_TasksMap.find(index);
                             if(currenttest != m_TasksMap.end())
                             {
                                          currenttest->second(m_param,s);
                             }

                             DeleteTask(index);
                        }
                     }
                    //////////////////////////////////////////5////////////////////////////////////////////////////////////////////////////////////////////
                    /// \brief taskCalibration
                    ///
                    void Test::taskCalibration(TaskOptionsParameters  &parameters,Statistic &s)
                    {

                        if(parameters.m_calibrationType != NO_CALIBRATION_TYPE)
                        {
                            m_avs.AddTask(CALIBRATION,"Calibration",parameters);
                            m_avs.ProcessSpectrum(CALIBRATION,s);

                            BaseFunction * ptr = m_avs.GetFunction(CALIBRATION);

                            parameters.m_saved_model = s;


                        }
                    }
                    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                    /// \brief Test::taskValidation
                    /// \param parameters
                    /// \param s
                    ///
                    void Test::taskValidation(TaskOptionsParameters  &parameters,Statistic &s)
                    {
                        if(parameters.m_validationType != NO_VALIDATION )
                        {
                            m_avs.AddTask(VALIDATION,"Validation",parameters);
                            m_avs.ProcessSpectrum(VALIDATION,s);
                            BaseFunction * ptr = m_avs.GetFunction(CALIBRATION);

                            parameters.m_saved_model = s;
                        }
                    }
                    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                    /// \brief Test::taskPrediction
                    /// \param parameters
                    /// \param s
                    ///
                    void Test::taskPrediction(TaskOptionsParameters& parameters,Statistic &s)
                    {
                        if(parameters.m_predictionType != NO_PREDICTION )
                        {
                            m_avs.AddTask(PREDICTION,"Prediction",parameters);
                            m_avs.ProcessSpectrum(PREDICTION,s);
                        }
                    }

                    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                    /// \brief Test::taskBaseLineCorrection
                    /// \param parameters
                    /// \param s
                    ///
                    void Test::taskBaseLineCorrection(TaskOptionsParameters & parameters,Statistic &s)
                    {
                         if(parameters.m_baseLineCorrection != NONE_CORRECTION)
                         {
                             m_avs.AddTask(BASE_LINE_CORRECTION,"Baseline Correction",parameters);
                             m_avs.ProcessSpectrum(BASE_LINE_CORRECTION,s);
                         }
                    }
                    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                    /// \brief Test::taskDataSmoothing
                    /// \param parameters
                    /// \param s
                    ///
                    void Test::taskDataSmoothing(TaskOptionsParameters& parameters,Statistic &s)
                    {
                        if(parameters.m_dataSmoothing != NONE_SMOOTHING)
                        {
                            m_avs.AddTask(DATA_SMOOTHING,"Data Smoothing",parameters);
                            m_avs.ProcessSpectrum(DATA_SMOOTHING,s);
                        }
                    }
                    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                    /// \brief Test::taskDerivative
                    /// \param parameters
                    /// \param s
                    ///
                    void Test::taskDerivative(TaskOptionsParameters& parameters,Statistic &s)
                    {
                        if(parameters.m_derivativeSpectraType.first != NO_DERIVATIVE_TYPE   && parameters.m_derivativeSpectraType.second != NO_DERIVATIVE_ALGORITHM)
                        {
                            m_avs.AddTask(DERIVATIVE_SPECTRA,"Derivative",parameters);
                            m_avs.ProcessSpectrum(DERIVATIVE_SPECTRA,s);
                        }
                    }
                    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                    /// \brief Test::taskMeanCentering
                    /// \param parameters
                    /// \param s
                    ///
                    void Test::taskMeanCentering(TaskOptionsParameters& parameters,Statistic &s)
                    {
                        if(parameters.m_meanCenteringMethodType != NONE_CENTERING  )
                        {
                            m_avs.AddTask( MEAN_CENTERING_SPECTRA,"Meancentering ",parameters);

                            m_avs.ProcessSpectrum(MEAN_CENTERING_SPECTRA,s);
                        }
                    }
                    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                    /// \brief Test::taskPreprocessing
                    /// \param parameters
                    /// \param s
                    ///
                    void Test::taskPreprocessing(TaskOptionsParameters& parameters,Statistic &s)
                    {
                        if(parameters.m_preprocessingType != NO_PREPROCESSING  )
                        {
                            m_avs.AddTask( PREPROCESSING,"Preprocessing ",parameters);

                            m_avs.ProcessSpectrum(PREPROCESSING,s);
                        }
                    }
                    ////////////////////////////////////////////////////////////////////////////////////////////////////////
                    /// \brief Test::RunTest
                    /// \param inputStatistic
                    /// \return
                    ///
                    Statistic  Test::RunTest(const Statistic & inputStatistic)
                    {
                        Statistic result = inputStatistic;
                        AddAndRunTasks(result);

                        return result;
                    }
                    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                    /// \brief Test::selectNRandomPoints
                    /// \param nPoints
                    /// \param min
                    /// \param max
                    /// \return
                    ///
                    vector<int> Test::selectNRandomPoints(int nPoints, int min,int max)
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
                    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                    /// \brief Test::GetTemplateParameterFromFiles
                    /// \return
                    ///
                    TaskOptionsParameters Test::GetTemplateParameterFromFiles( )
                    {
                            Test  calibrationtests = *this;
                            TaskOptionsParameters parameter;
                            parameter.m_task_name = "";
                            resetTaskMap( parameter.m_tasksType);

                            parameter.m_constituents.clear();
                            int count = 0;

                            for(auto constitute : calibrationtests.m_ConstituesIndexMap)
                            {
                                if(ConstituentsName.find(constitute.first) != ConstituentsName.end())
                                {
                                   parameter.m_constituents.insert(pair<Constituents,string>(constitute.first,ConstituentsName.at(constitute.first)));
                                }
                                else
                                {
                                    parameter.m_constituents.insert(pair<Constituents,string>(constitute.first,"UNKNOWN  " + to_string(count + 1)));
                                    count++;
                                }
                            }
                            parameter.m_ConstituesIndexMap = calibrationtests.m_ConstituesIndexMap;
                            parameter.m_ConstituesIndexMap.insert(pair<Constituents,int>(UNKNOWN,parameter.m_ConstituesIndexMap.size() - 1));
                            parameter.m_concentrations =  calibrationtests.m_CalibConcentrationMap.t();
                            int newnumberofsamples_calib = min((int)parameter.m_concentrations.n_cols - 1,calibrationtests.m_selectedData.m_NumberOfSamplesCalib -1);
                            parameter.m_concentrations = parameter.m_concentrations.cols(0,newnumberofsamples_calib);

                            parameter.m_testing_concentrations = calibrationtests.m_TestConcentrationMap.t();
                            parameter.m_CorrectionFunction =pair<mat,mat>( mat(0,0),mat(0,0) );
                            int newnumberofsamples_test =min((int)parameter.m_testing_concentrations.n_cols - 1,calibrationtests.m_selectedData.m_NumberOfSamplesTest-1);
                            parameter.m_testing_concentrations = parameter.m_testing_concentrations.cols(0,newnumberofsamples_test);


                            parameter.m_currentPopulationMatrix = mat(newnumberofsamples_calib,calibrationtests.m_selectedData.m_NumberOfVariables);
                            parameter.m_currentPopulationMatrix.zeros();

                            mat calibrationdata = calibrationtests.m_CalibrationDataMap;
                            int newnumberOfPoints_cal = min(calibrationtests.m_selectedData.m_NumberOfVariables-1,(int)calibrationdata.n_cols - 1);

                            parameter.m_currentPopulationMatrix = (calibrationdata.cols(0,newnumberOfPoints_cal)).rows(0,newnumberofsamples_calib );

                           // parameter.m_currentPopulationMatrix.print("m_currentPopulationMatrix=");
                            parameter.m_testingPopulationMatrix = mat(newnumberofsamples_test,calibrationtests.m_selectedData.m_NumberOfVariables);
                            parameter.m_testingPopulationMatrix.zeros();

                            calibrationdata = calibrationtests.m_TestDataMap;
                            int newnumberOfPoints_test = min(calibrationtests.m_selectedData.m_NumberOfVariables-1,(int)calibrationdata.n_cols - 1);


                            parameter.m_testingPopulationMatrix = (calibrationdata.cols(0,newnumberOfPoints_test)).rows(0,newnumberofsamples_test);
                            //parameter.m_testingPopulationMatrix.print("m_testingPopulationMatrix=");

                            for(int i =0;i< calibrationtests.m_selectedData.m_NumberOfVariables;i++)
                            {
                                parameter.m_currentValuesOfX.push_back( calibrationtests.mXPoints(0,i));
                            }

                             // find average for zero transmission spectra
                             parameter.m_zeroTransmissionDatapoints=   parameter.m_currentPopulationMatrix.rows(0,0);

                             for(int i = 0;i < (int)calibrationtests.m_zeroTransmissionSpectra.n_cols && i < (int)parameter.m_zeroTransmissionDatapoints.n_cols;i++)
                             {
                                 parameter.m_zeroTransmissionDatapoints(i) = arma::mean(calibrationtests.m_zeroTransmissionSpectra.col(i));
                             }

                            parameter.m_testingConsSets.clear();
                            parameter.numOfSamples = parameter.m_concentrations.n_rows;
                            parameter.numOfDataPoints = parameter.m_currentPopulationMatrix.n_cols;
                            parameter.numOfPCA = calibrationtests.m_selectedData.m_NumberOfVariables;

                            parameter.m_numOfSamplesInTestingSet = parameter.m_testingPopulationMatrix.n_rows;
                            parameter.m_numOfDataPointsInTestingSet = parameter.numOfDataPoints;
                            parameter.m_numOfPCAInTestingSet =  parameter.m_numOfDataPointsInTestingSet;

                            vector<pair<ConstituteFilterTypes,int>> constituteFilters =
                            {
                                {NOLow,5},
                                {NOHigh,10},
                                //{NO2Low,2},
                                //{NO2High,2}
                            };

                            parameter.m_filterMap =  parameter.setFilterMap(constituteFilters,calibrationtests.mXPoints,BPF);

                            parameter.m_selectedData = *(reinterpret_cast<SelectedOptions*>(&calibrationtests.m_selectedData));
                            return parameter;
                    }
                    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                    /// \brief Test::resetTaskMap
                    /// \param m_tasksType
                    ///
                    void Test::resetTaskMap( map<int,TaskT*> &tasksType)
                    {
                        // task array
                        // taskarrayindex = 0 => Preprocessing
                        // taskarrayindex = 1 => BaselineCorrection Algorithm {Simple, 2 point, Multipoint, Interactive, ...}
                        // taskarrayindex = 2 => DataSmoothing Algorithm { Fourier, Binomial, Savitzky Golay}
                        // taskarrayindex = 3 => Derivative {0,1,2   ... N } derivative
                        // taskarrayindex = 4 => MeanCentering
                        // taskarrayindex = 5 => Calibration Type{Univariate , Multivariate}
                        // taskarrayindex = 6 => Calibfration Algorithm { Nipals, LibPCA }
                        // taskarrayindex = 7 => Validation Algorithm {TestingSet, Cross Validation }
                        // taskarrayindex = 8 => Prediction Algorithm {TestingSet, Cross Validation }
                        tasksType.clear();
                        vector<int> taskarray =
                        {
                            // Set Tasks to none defined 1,3,10,14,18,21,24,28
                          ((PreprocessingTaskT*)TypeTmap.at(NO_PREPROCESSING ))->preprocessing.second    ,  // => 1
                          ((BaseLineCorrectionTaskT*)TypeTmap.at(NONE_CORRECTION ))->baselineCorrection.second     ,  // => 3
                          ((DataSmoothingTaskT*)TypeTmap.at(NONE_SMOOTHING ))->dataSmooting.second     ,  // => 10
                          ((DerivativeSpectraTaskT*)TypeTmap.at(NO_DERIVATIVE_TYPE ))->derivative.second  ,  // => 14
                          ((MeanCenteringMethodTaskT*)TypeTmap.at(NONE_CENTERING))->meanCentering.second       ,  // => 18
                          ((CalibrationTaskT*)TypeTmap.at(NO_CALIBRATION_TYPE))->calibrationType.second  ,  // => 21
                          ((AlgorithmTaskT*)TypeTmap.at(NO_ALGORITHM_TYPE))->algorithmType.second   ,  // => 24
                          ((ValidationTaskT*)TypeTmap.at(NO_VALIDATION))->validationType.second        ,  // => 28
                          ((PredictionTaskT*)TypeTmap.at(NO_PREDICTION))->predictionType.second        ,  // => 50
                        };


                        int counttask =0;
                        for(auto m: TypeTmap)
                        {
                            for(auto task :taskarray)
                            {
                               if(m.first == task)
                               {
                                  tasksType.insert(pair<int,TaskT*>(counttask,m.second));
                                  counttask++;
                               }
                            }
                        }
                    }

                    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                    /// \brief Test::setTaskOptionParam
                    /// \param m1
                    /// \param m2
                    /// \param opt
                    ///
                    void Test::setTaskOptionParam(mat  &m1,mat &m2,int opt )
                    {
                        if(opt == 0)
                        {
                            m_param.m_currentPopulationMatrix = m1;
                            m_param.m_concentrations = m2;
                        }
                        else if(opt == 1)
                        {
                            m_param.m_testingPopulationMatrix = m1;
                            m_param.m_testing_concentrations = m2;
                        }
                    }
                    //////////////////////////////////////////////////////////////////////////////////////////////////////////////
                    /// \brief Test::getTaskOptionParam
                    /// \return
                    ///
                    TaskOptionsParameters  Test::getTaskOptionParam()
                    {
                        return m_param;
                    }
                   /* InputVariables::InputVariables(const InputVariables & value)
                    {

                    }

                    InputVariables& InputVariables::operator=(const InputVariables & value)
                    {
                        if(this != value)
                        {

                        }
                        return *this;
                    }*/

                    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                    /// \brief InputVariables::checkLimits
                    /// \param selectXPoints
                    /// \param selectCalibrationSamples
                    /// \param selectTestSamples
                    /// \param numberOfSelectedVariables
                    /// \param numberOfSelectedSamplesCalib
                    /// \param numberOfSelectedSamplesTest
                    /// \param errorMessage
                    /// \return
                    ///
                    int InputVariables::checkLimits(const vector<double> & waveLengthVariables ,int maxOfCalibrationSamples,int maxOfTestSamples, Test &instance)
                    {
                       if(numberOfSelectedVariables < 1)
                           numberOfSelectedVariables = (int)waveLengthVariables.size();
                       if( numberOfSelectedSamplesCalib < 1)
                           numberOfSelectedSamplesCalib = maxOfCalibrationSamples;
                       if(numberOfSelectedSamplesTest < 1)
                           numberOfSelectedSamplesTest = maxOfTestSamples;
                       numberOfSelectedVariables = min(numberOfSelectedVariables,(int)waveLengthVariables.size());
                       numberOfSelectedSamplesCalib = min(numberOfSelectedSamplesCalib,maxOfCalibrationSamples);
                       numberOfSelectedSamplesTest = min(numberOfSelectedSamplesTest,maxOfTestSamples);
                       int status;

                       status = checkLimits(selectXPoints,0,(int)waveLengthVariables.size(),0,errorMessage);
                       if(status != 0)
                           return status;

                       status = checkLimits(selectCalibrationSamples,0,maxOfCalibrationSamples,1,errorMessage);
                       if(status != 0)
                           return status;

                       status = checkLimits(selectTestSamples,0,maxOfTestSamples,2,errorMessage);
                       if(status != 0)
                           return status;

                       numberOfSelectedVariables = min(numberOfSelectedVariables,selectXPoints.second - selectXPoints.first);
                       numberOfSelectedSamplesCalib = min(numberOfSelectedSamplesCalib,selectCalibrationSamples.second - selectCalibrationSamples.first);
                       numberOfSelectedSamplesTest = min(numberOfSelectedSamplesTest,selectTestSamples.second - selectTestSamples.first);

                       maxNumberOfPCA = min(maxNumberOfPCA,numberOfSelectedVariables);
                       if(maxNumberOfPCA < 1 && numberOfSelectedVariables > 0)
                           maxNumberOfPCA = 1;

                       if(selectedVariableIndex.size() <= 0)
                       {
                           selectedVariableIndex = instance.selectNRandomPoints(  numberOfSelectedVariables,  selectXPoints.first,selectXPoints.second);
                       }
                       if(selectedSamplesCalibration.size() <= 0)
                       {
                           selectedSamplesCalibration = instance.selectNRandomPoints(  numberOfSelectedSamplesCalib, selectCalibrationSamples.first,selectCalibrationSamples.second);
                       }
                       if(selectedSamplesTest.size() <= 0)
                       {
                           selectedSamplesTest = instance.selectNRandomPoints(numberOfSelectedSamplesTest, selectTestSamples.first,selectTestSamples.second);
                       }
                       cout << "Selected wavelength = "<< (int)selectedVariableIndex.size()<< endl;
                       cout << "[ ";
                       for(auto lambda: selectedVariableIndex)
                       {
                           cout << waveLengthVariables[lambda] <<" ";
                       }
                       cout << " ]"<< endl;
                       cout << "Selected file numbers for Calibration = " << (int)selectedSamplesCalibration.size() << endl;
                       cout << " ["<< endl;
                       for(auto calibFileNumber: selectedSamplesCalibration)
                       {
                           cout << 2 * calibFileNumber <<" ";
                       }
                       cout << " ]"<< endl;
                       cout << "Selected file numbers for Test = " << (int)selectedSamplesTest.size() << endl;
                       cout << " ["<< endl;
                       for(auto testFileNumber: selectedSamplesTest)
                       {
                           cout << 2 * testFileNumber + 1 <<" ";
                       }
                       cout << " ]"<< endl;
                       if(selectedVariableIndex.size() <=0 || selectedSamplesCalibration.size() <= 0 || selectedSamplesTest.size() <= 0)
                       {
                           cout << "Selected Data are not valid "<< endl;
                           return -6;
                       }
                       instance.SelectCalibAndTestData(selectedVariableIndex,selectedSamplesCalibration ,selectedSamplesTest );
                       return 0;
                    }
                    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                    /// \brief Test::checkLimits
                    /// \param selected
                    /// \param minlimit
                    /// \param maxlimit
                    /// \param option
                    /// \param errorMessage
                    /// \return
                    ///
                    int InputVariables::checkLimits( pair<int,int> &selected, int minlimit,int maxlimit,int option,string &errorMessage)
                    {

                        int result = 0;
                        string limitsSelected;
                        set<int> removeDuplicates;
                        if(option == 0)
                        {
                            limitsSelected = " Variables ";
                            if(selectedVariableIndex.size() > 0)
                            {
                               std::sort(selectedVariableIndex.begin(),selectedVariableIndex.end());
                               removeDuplicates.clear();
                               for(auto v: selectedVariableIndex)
                                   removeDuplicates.insert(v);
                               selectedVariableIndex.clear();
                               for(auto v: removeDuplicates)
                                   selectedVariableIndex.push_back(v);

                               minlimit = selectedVariableIndex[0];
                               maxlimit = selectedVariableIndex[selectedVariableIndex.size() - 1 ];
                               numberOfSelectedVariables = selectedVariableIndex.size();
                            }
                        }
                        else if(option == 1)
                        {
                            limitsSelected = " Calibration Samples ";
                            if(selectedSamplesCalibration.size() > 0)
                            {
                               std::sort(selectedSamplesCalibration.begin(),selectedSamplesCalibration.end());
                               removeDuplicates.clear();
                               for(auto v: selectedSamplesCalibration)
                                   removeDuplicates.insert(v);
                               selectedSamplesCalibration.clear();
                               for(auto v: removeDuplicates)
                                   selectedSamplesCalibration.push_back(v);

                                minlimit = selectedSamplesCalibration[0];
                                maxlimit = selectedSamplesCalibration[selectedSamplesCalibration.size() - 1 ];
                            }
                        }
                        else if(option == 2)
                        {
                             limitsSelected = " Test Samples ";
                             if(selectedSamplesTest.size() > 0)
                             {
                                std::sort(selectedSamplesTest.begin(),selectedSamplesTest.end());
                                removeDuplicates.clear();
                                for(auto v: selectedSamplesTest)
                                    removeDuplicates.insert(v);
                                selectedSamplesTest.clear();
                                for(auto v: removeDuplicates)
                                    selectedSamplesTest.push_back(v);

                                minlimit = selectedSamplesTest[0];
                                maxlimit = selectedSamplesTest[selectedSamplesTest.size() - 1 ];
                             }
                        }
                        cout << "****************************************************************************************************************************"<< endl;
                        cout << "Minimum number of selected "<< limitsSelected << " = " << selected.first << "          Maximum number of selected "<< limitsSelected << " = " << selected.second << endl;
                        cout << "Validating limits"<< endl;
                        try
                        {
                            if(selected.first < 0)
                            {
                                cout << "Selected low limit = " << selected.first << " is not valid. Reseting low limit to min valid value = "<< minlimit<<endl;
                                selected.first = 0;
                            }
                            if(selected.first > maxlimit)
                            {
                                 cout << "Selected low limit = " << selected.first << " is not valid. Reseting low limit to max valid value = "<< maxlimit<< endl;
                                selected.first = maxlimit;
                            }
                            if(selected.second < 0)
                            {
                                cout << "Selected high limit = " << selected.second << " is not valid. Reseting high limit to min valid value = "<< minlimit<< endl;
                                selected.second = 0;

                            }

                            if(selected.second > maxlimit)
                            {
                                cout << "Selected high limit = " << selected.second << " is not valid. Reseting high limit to max valid value = "<< maxlimit<< endl;
                                selected.second = maxlimit;

                            }
                            if(selected.first == selected.second )
                            {
                                if(selected.second <= 0)
                                {
                                  cout << "Selected high limit = " << selected.second << " is not valid. Reseting high limit to max valid value = "<< maxlimit<< endl;
                                  selected.second = maxlimit;
                                }
                                if(selected.first >= maxlimit )
                                {
                                     cout << "Selected low limit = " << selected.first << " is not valid. Reseting low limit to min valid value = "<< minlimit<< endl;
                                     selected.first = minlimit;
                                }
                            }
                            if(selected.first > selected.second)
                            {
                                cout << "Low limit is higher then high limit. Switching low and high limit "<< endl;
                               int temp =  selected.first;
                               selected.first = selected.second;
                               selected.second = temp;
                            }
                            if(maxlimit < selected.second - selected.first)
                            {
                                string out;
                                if(option == 0)
                                {
                                    out = "Selected number Of Variables =  ";
                                    errorMessage = "Variables selection limits are not valid ";
                                    result = -1;
                                }
                                else if(option == 1)
                                {
                                    out = "Selected number Of Calibration Samples =  ";
                                    errorMessage = "Calibration samples selection limits are not valid ";
                                    result = -2;
                                }
                                else if(option == 2)
                                {
                                    out = "Selected number Of Test Samples =  ";
                                    errorMessage = "Test samples selection limits are not valid ";
                                    result = -3;
                                }
                                cout << out << maxlimit << " Range = " << selected.second - selected.first << " Exiting the program"<< endl;

                            }
                            if(selected.second - selected.first <= 0)
                            {
                                cout << "Selected range is zero or not valid "<< endl;
                                result = -1;
                            }
                        }
                        catch(std::exception & e)
                        {
                            errorMessage = "Error . Check Limits";
                            result = -6;
                        }


                        cout << "Validated " << limitsSelected << " limits :"<< endl;
                        cout << "Minimum number of selected "<< limitsSelected << " = " << selected.first << "          Minimum number of selected "<< limitsSelected << " = " << selected.second << endl;
                        cout << "****************************************************************************************************************************"<< endl;
                       return result;
                    }
                    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                    /// \brief mapGetValues
                    /// \param pointsmap
                    /// \return
                    ///
                    vector<double> Test::mapGetValues(map<int,Point> pointsmap)
                    {
                        std::vector<double> list;
                        std::for_each(pointsmap.begin(), pointsmap.end(), [&](const std::pair<const int, Point> & ref)
                        {
                            list.push_back(ref.second.y);
                        });

                        return list;
                    }

                    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                    /// \brief Test::PickVariables
                    /// \param length
                    /// \param populationsize
                    /// \param fitness
                    /// \param maxcount
                    ///
                    void Test::PickVariables
                    (
                            vector<int> variables,int length,int populationsize,int start,int end,
                            pair<double,double> fitness,int & fitnessRank,double & currentFitness,
                            int blocksize,int maxNumberOfGenerations,string filename
                    )
                    {
                            GeneticAlgorithm alg = {variables,length,populationsize,start,end,fitness,blocksize, maxNumberOfGenerations};

                            alg.RunGA(*this);

                            for(int i =0;i < (int)alg.m_bestFit.size();i++)
                            {
                                if(alg.m_bestFit[i].size() > 0)
                                {
                                       GetSetVariavleIndexFromTheFile(filename,alg.m_bestFit[i][0].stat.variables,true);
                                       currentFitness = alg.m_bestFit[i][0].stat.RMSEAVERAGE;
                                       fitnessRank = i;
                                       break;
                                }
                            }



                    }
                    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                    /// \brief Test::testVariables
                    /// \param test
                    /// \param limits
                    /// \return
                    ///
                    Stat Test::testVariables(const Test& test, vector< int> limits)
                    {
                        Test cur_test = test;
                        Chromosome chrom;
                        chrom.sequence = limits;
                        cur_test.testVariablesPick(cur_test,chrom,0);

                        return chrom.stat;
                    }
                    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                    /// \brief Test::SelectGARange
                    /// \param size
                    /// \param startpercent
                    /// \param endpercent
                    /// \param percentdecrement
                    /// \param maxRmsAverage
                    /// \param minRms
                    /// \param bestVariablesRanges
                    /// \param alg
                    /// \param numberFound
                    ///
                    void Test::SelectGARange
                    (
                            int size,int startpercent,int  endpercent,int percentdecrement,double  currentrms,double minRms,
                            std::vector<Stat> &bestVariablesRanges,
                            int alg,int &numberFound
                    )
                    {
                        ///////////////////////////////////////   Pick Variables  /////////////////////////////////////////////////////////////////////////////////////////////

                        if(startpercent < endpercent)
                            return;
                        int count ;
                        Stat best;
                        if(bestVariablesRanges.size() > 0)
                        {
                            best = bestVariablesRanges[0];
                        }
                        vector<pair<int,int>> limits;
                        int minDelta = size * startpercent / 100 +  (int)((bool)(size * startpercent % 100));
                        count = size / minDelta + (int)((bool)(size % minDelta ));
                        for(int i = 0;i<count;i++)
                        {
                                for(int j = i+1;j < count + 1 ;j++)
                                  limits.push_back({i * minDelta,min(j * minDelta,size)});
                        }

                        if(alg == 0 || alg == 2)
                        {
                            currentrms = minRms;
                        }
                        std::vector<Stat> bestVariablesRange;
                        while((int)limits.size() > 0)
                        {
                                int i = rand()%(limits.size());

                                testVariablesPick(*this,limits[i].first, limits[i].second,bestVariablesRange,currentrms,alg);
                                limits.erase(limits.begin() + i,limits.begin() + i + 1);
                                if(bestVariablesRange.size() > 0 && bestVariablesRange[0] > best && alg == 1)
                                {
                                       best = bestVariablesRange[0];
                                       currentrms = best.RMSEAVERAGE;
                                }
                        }
                        if(alg != 4)
                        {
                            if((int)bestVariablesRange.size() > 0 )
                            {
                                 std::sort(bestVariablesRange.begin(),bestVariablesRange.end(),bestVariablesRange[0]);
                                 for(auto b : bestVariablesRange)
                                 {
                                      vector<Stat>::iterator it = std::find(bestVariablesRanges.begin(),bestVariablesRanges.end(),b);
                                      if(it == bestVariablesRanges.end() && b.RMSEAVERAGE <  bestVariablesRange[0].RMSEAVERAGE * 2.0)
                                      {
                                            bestVariablesRanges.push_back(b);
                                            numberFound++;

                                      }
                                 }

                                 bestVariablesRange.clear();

                            }
                            if(bestVariablesRanges.size() > 0)
                            {
                               std::sort(bestVariablesRanges.begin(),bestVariablesRanges.end(),bestVariablesRanges[0]);
                               bestVariablesRanges[0].printToFile("VariableSelectionAlg" + to_string(alg) + ".txt",startpercent,-1,-1,count,false);
                            }
                        }
                        if(currentrms > minRms)
                        {
                           startpercent = std::ceil(startpercent - (startpercent * (double)percentdecrement ) / 100);
                           SelectGARange(size,startpercent,endpercent,percentdecrement,currentrms,minRms,bestVariablesRanges,alg,numberFound);
                        }
                    }

                    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                    /// \brief Test::PickVariables
                    /// \param percent
                    /// \param maxRmsAverage
                    ///
                    void Test::PickVariables
                    (
                            int size,int startpercent,int  endpercent,int percentdecrement,double  maxRmsAverage,double minRms,
                            std::vector<Stat> &bestVariablesRange,
                            int & numberFound
                    )
                    {
                        ///////////////////////////////////////   Pick Variables  /////////////////////////////////////////////////////////////////////////////////////////////
                        if(startpercent < endpercent)
                            return;
                        Stat best;
                        vector<pair<int,int>> limits;
                        int minDelta = size * startpercent / 100 +  (int)((bool)(size * startpercent % 100));
                        int count = size / minDelta + (int)((bool)(size % minDelta ));
                        for(int i = 0;i<count;i++)
                        {
                                for(int j = i+1;j < count + 1 ;j++)
                                  limits.push_back({i * minDelta,min(j * minDelta,size)});
                        }
                        int sizebefore = (int)bestVariablesRange.size();
                        while((int)limits.size() > 0)
                        {
                                int i = rand()%(limits.size());

                                testVariablesPick(*this,limits[i].first, limits[i].second,bestVariablesRange,maxRmsAverage,1);
                                limits.erase(limits.begin() + i,limits.begin() + i + 1);
                                if(bestVariablesRange.size() > 0 && bestVariablesRange[0] > best)
                                {
                                       best = bestVariablesRange[0];
                                       maxRmsAverage = best.RMSEAVERAGE;
                                }
                        }

                        if((int)bestVariablesRange.size() > sizebefore)
                             numberFound++;
                        if(bestVariablesRange.size() > 0 )
                        {

                           std::sort(bestVariablesRange.begin(),bestVariablesRange.end(),bestVariablesRange[0]);
                           while((int)bestVariablesRange.size() > sizebefore  && bestVariablesRange[(int)bestVariablesRange.size() -1].RMSEAVERAGE > maxRmsAverage * 1.1 )
                           {

                                bestVariablesRange.pop_back();
                           }
                           vector<Stat> ss;
                           for(auto b: bestVariablesRange)
                           {
                                vector<Stat>::iterator it = std::find(ss.begin(),ss.end(),b);
                                if(it == ss.end() )
                                      ss.push_back(b);
                           }
                           bestVariablesRange = ss;
                           for(auto b: bestVariablesRange)
                           {
                               b.printToFile("VariableSelection1.txt",startpercent);
                           }
                           if(bestVariablesRange[0].RMSEAVERAGE <= minRms)
                           {
                               return;
                           }

                        }

                        startpercent = std::ceil(startpercent - (startpercent * (double)percentdecrement ) / 100);
                        PickVariables(size,startpercent,endpercent,percentdecrement,maxRmsAverage,minRms,bestVariablesRange,numberFound);

                    }
                    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                    /// \brief Test::testVariablesPick
                    /// \param test
                    /// \param variables
                    /// \param bests
                    /// \param rms
                    /// \param algorithm
                    ///
                    void Test::testVariablesPick( Test& test,Chromosome &chrom,double rms)
                    {
                          InputVariables input = test.getInputVariable();
                          input.selectedVariableIndex = chrom.sequence;

                          test.setVariablesLimits(input);
                          chrom.stat = testPick(test);


                          if(input.selectedVariableIndex.size() > 0)
                          {
                              chrom.stat.variableStart = input.selectedVariableIndex[0];
                              chrom.stat.variableEnd = input.selectedVariableIndex[input.selectedVariableIndex.size() - 1];
                              chrom.stat.variables = input.selectedVariableIndex;
                          }
                    }

                    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                    /// \brief testVariablesPick
                    /// \param start
                    /// \param end
                    /// \param bests
                    /// \param option
                    ///
                    void Test::testVariablesPick(Test test,int start, int end,vector<Stat> &bests,double rms,int algorithm)
                    {
                        vector<InputVariables> input = {test.getInputVariable(),test.getInputVariable()};
                        int fitnessRank = -1;
                        int bestcount = 0;
                        Stat ss;
                        vector<Stat> s = {ss,ss};
                        int mid;
                        int mid1;
                        int mid2;
                        vector<Stat>::iterator it;
                        vector<Test> cur_test = {test,test};
                        int maxRange = 1076 / 8;
                        switch(algorithm)
                        {
                            case 0:
                                if(end - start < maxRange)
                                    return;

                                input[0].selectXPoints = {start,end};
                                input[0].selectedVariableIndex.clear();
                                cur_test[0].setVariablesLimits(input[0]);

                                s[0] = testPick(cur_test[0]);
                                s[0].variableStart = input[0].selectXPoints.first;
                                s[0].variableEnd = input[0].selectXPoints.second;
                                s[0].variables =  input[0].selectedVariableIndex;

                                it = std::find(bests.begin(),bests.end(),s[0]);
                                if(it == bests.end() && s[0].RMSEAVERAGE < rms)
                                        bests.push_back(s[0]);
                               std::sort(bests.begin(),bests.end(),s[0]);


                                if(end-start - 1 > 0)
                                {
                                    mid = (start + end ) / 2;
                                    testVariablesPick(test,start,mid,bests,rms,algorithm);
                                    testVariablesPick(test,mid ,end,bests,rms,algorithm);

                                    if(mid-start - 1 > 0 && end-mid - 1 > 0)
                                    {
                                           mid1 = (start + mid) / 2;
                                           mid2 = (mid + end) / 2;
                                           testVariablesPick(test,mid1,mid2,bests,rms,algorithm );
                                    }
                                }

                           break;

                           case 1:
                           case 2:
                           case 3:
                                while(end - start - 1 >= 0)
                                {
                                   s[0]=ss;   s[1]=ss;
                                   if(end - start - 1 == 0)
                                   {
                                       mid = end;
                                   }
                                   else
                                   {
                                     mid = (start + end ) / 2;
                                   }


                                    input[0].selectXPoints = {start,mid};   input[1].selectXPoints = {mid , end};
                                    input[0].selectedVariableIndex.clear(); input[1].selectedVariableIndex.clear();
                                    for(int x = 0;x < (int)cur_test.size();x++)
                                    {
                                        if(input[x].selectXPoints.first < input[x].selectXPoints.second )
                                        {
                                            cur_test[x].setVariablesLimits(input[x]);

                                            s[x] = testPick(cur_test[x]);
                                            s[x].variableStart = input[x].selectXPoints.first;
                                            s[x].variableEnd = input[x].selectXPoints.second;
                                            s[x].variables =  input[x].selectedVariableIndex;
                                            if(algorithm == 1)
                                            {
                                                it = std::find(bests.begin(),bests.end(),s[x]);
                                                if(it == bests.end())
                                                        bests.push_back(s[x]);
                                                 std::sort(bests.begin(),bests.end(),ss);
                                                 while(bests.size() > 1  &&   abs(bests[bests.size() - 1].RMSEAVERAGE) >= rms * 1.15  )
                                                 {
                                                            bests.pop_back();
                                                 }
                                            }
                                            else if(algorithm == 2)
                                            {
                                                it = std::find(bests.begin(),bests.end(),s[x]);
                                                if(it == bests.end() && s[x].RMSEAVERAGE <= rms)
                                                        bests.push_back(s[x]);
                                                std::sort(bests.begin(),bests.end(),s[x]);

                                            }
                                            else
                                            {
                                                  bests.push_back(s[0]);
                                                  return;
                                            }
                                        }
                                    }

                                    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                                    if(s[0] > s[1])
                                    {
                                            if(end == mid)
                                                return;
                                            end = mid;
                                    }
                                    else
                                    {
                                        if(start == mid )
                                            return;
                                           start = mid;
                                    }

                                }

                                break;

                        case 4:

                            test.PickVariables
                             (
                                     {},test.getInputVariable().numberOfSelectedVariables,
                                     std::min(50.0, pow(2,double(end-start)) - 1),start,end,
                                     {0.001,7.5},fitnessRank,rms
                             );

                            break;
                        };

                    }
                    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                    /// \brief testPick
                    /// \param start
                    /// \param end
                    /// \return
                    ///
                    Stat Test::testPick(Test test)
                    {

                          Statistic statistic;
                          CalibrationType calibration = MULTIVARIATE_CALIBRATION ;
                          AlgorithmType algorithm   = NIPALS_ALGORITHM;


                          pair<int,int> option = {0,1};

                          InputVariables input = test.getInputVariable();
                          //int  kfoldrange = input.numberOfSelectedSamplesCalib * 0.31 / 100;
                          Stat result;
                          if(input.numberOfSelectedSamplesTest <=0 || input.numberOfSelectedSamplesCalib <= 0)
                              return result;
                           test.Run
                           (
                                  statistic,option.first,
                                  {

                                                     new   MeanCenteringInputParam(MEAN_CENTERING_SPECTRA,1 , COMPUTE_MEAN_SPECTRUM ),
                                                     new   BaselineInputParam
                                                     (
                                                           BASE_LINE_CORRECTION,0,
                                                           {
                                                             {GIFTS ,NOT_SET},
                                                             {selectNRandomPoints(input.numberOfSelectedVariables,0, input.numberOfSelectedVariables),-1},
                                                           }
                                                     ),
                                                     new   CalibrationInputParam(CALIBRATION,2,calibration, algorithm),
                                                     //new   ValidationInputParam(VALIDATION,3,KFOLDCROSSVALIDATION, kfoldrange )
                                  }
                            );

                            return statistic.m_bestFitCalibration[0];
                    }



} /* namespace NDUV */
