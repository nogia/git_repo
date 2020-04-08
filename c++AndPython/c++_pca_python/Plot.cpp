/*
 * Plot.cpp
 *
 *  Created on: Jun 23, 2016
 *      Author: inna
 */

#include "Plot.h"

namespace NDUV {

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \brief Plot::Plot
    ///
    Plot::Plot()
    {
        // TODO Auto-generated constructor stub
        env = string(std::getenv("PWD"));

         dirpath = "sys.path.append(\"" + env + "/../src" + "\")";
         Py_Initialize();
         PyRun_SimpleString("import sys\n");
         PyRun_SimpleString(dirpath.c_str());
         Show = false;

    }
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \brief Plot::~Plot
    ///
    Plot::~Plot()
    {
          EndPython();
    }
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \brief Plot::EndPython
    ///
    void Plot::EndPython()
       {
                 if(pInstance != nullptr)
                       Py_XDECREF(pInstance);
                  if(pValue != nullptr)
                       Py_XDECREF(pValue);
                  if(pModule != nullptr)
                       Py_XDECREF(pModule);
                  if(pName != nullptr)
                       Py_XDECREF(pName);
                  if(pDict != nullptr)
                       Py_XDECREF(pDict);
                  if(pArgs != nullptr)
                      Py_XDECREF(pArgs);
                  if(pClass != nullptr)
                       Py_XDECREF(pClass);

                    Py_Finalize() ;



       }
      ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      /// \brief Plot::CreatePlot
      /// \param plotdata
      ///
      void Plot::CreatePlot
      (
              vector<std::tuple<string,string,string,vector<vector<vector<double>>>>> plotdata,
              vector<std::tuple<vector<int>,vector<double>,vector<string>>> titles
      )
      {

              if((int)plotdata.size() > 0)
              {
                  pName = PyString_FromString(get<0>(plotdata[0]).c_str());
                  pModule = PyImport_Import(pName);

                 if(pModule==NULL)
                 {
                         return EndPython(); //no module found or there was an error when compiling python code
                 }

                 pDict = PyModule_GetDict(pModule);//borowed reference so no DECREF
              }

             PyObject * graphs = PyList_New((int)plotdata.size() );

             for(int g = 0;g < (int)plotdata.size() ;g++)
             {
                // drawSamples([ [ [1,2,3,4]  ],[[1,4,9,16],[3,2,13,10] ,[1,17,5,19],[5,5,5,5]],[[0, 6, 0, 20] ]])
                 vector<vector<vector<double>>> listd = get<3>(plotdata[g]);

                 //Create list = [[[lista]],[[listb0],[listb1],[]listbN],[ [listc]]] to pass to Python list to function drawSamples
                 PyObject *lst = PyList_New(listd.size() + 1);

                     if (!lst)
                         return ;
                     int k=0;
                     for (k = 0; k < (int)listd.size(); k++)
                     {
                         PyObject *lstv = PyList_New(listd[k].size());

                         for (int i = 0; i < (int)listd[k].size(); i++)
                         {
                             if (!lstv)
                                 return ;
                             PyObject *lstn = PyList_New(listd[k][i].size());

                             for (int j = 0; j < (int)listd[k][i].size(); j++)
                             {
                                 if (!lstn)
                                     return ;
                                 PyObject *num = PyFloat_FromDouble(listd[k][i][j]);
                                 if (!num) {
                                     Py_DECREF(lstn);
                                     return ;
                                 }
                                 PyList_SET_ITEM(lstn, j, num);
                             }
                             PyList_SET_ITEM(lstv, i,lstn);
                         }
                          PyList_SET_ITEM(lst, k,lstv);
                     }

                     /*vector<std::string> titles = {"Title 1","Title 2","Titele 3"};
                     PyObject *lstTitles = PyList_New((int)titles.size() );

                     for(int i =0;i< (int)titles.size();i++)
                     {
                          PyObject* title = PyString_FromString(titles[i].c_str());

                          PyList_SET_ITEM(lstTitles, i, title);
                     }
                      PyList_SET_ITEM(lst,(int)listd.size(),lstTitles);
                    */
                    // std::tuple<vector<int>,vector<double>,vector<string>> titles = std::make_tuple<vector<int>,vector<double>,vector<string>>({25,26},{45.00,48.00},{"title 1","title 2"});
                     PyObject *lstListTitles = PyList_New(titles.size() );

                     for(int a =0;a < (int)titles.size();a++)
                     {
                         std::tuple<vector<int>,vector<double>,vector<string>> title = titles[a];
                         PyObject *lstTitles = PyTuple_New(std::tuple_size<decltype(title)>::value);

                         for(int i = 0;i < (int)std::tuple_size<decltype(title)>::value;i++)
                         {
                             if(i == 0)
                             {
                                 vector<int> lst = get<0>(title);
                                 PyObject *lstn = PyList_New(lst.size());

                                 for (int j = 0; j < (int)lst.size(); j++)
                                 {
                                     if (!lstn)
                                         return ;
                                     PyObject *num = PyInt_FromLong(lst[j]);
                                     if (!num) {
                                         Py_DECREF(lstn);
                                         return ;
                                     }
                                     PyList_SET_ITEM(lstn, j, num);
                                 }
                                 PyTuple_SetItem(lstTitles, i, lstn);
                                //PyTuple_SetItem(lstTitles, 0, PyInt_FromLong(get<0>(titles)));
                             }
                             else if (i == 1)
                             {
                                 vector<double> lst = get<1>(title);
                                 PyObject *lstn = PyList_New(lst.size());

                                 for (int j = 0; j < (int)lst.size(); j++)
                                 {
                                     if (!lstn)
                                         return ;
                                     PyObject *num = PyFloat_FromDouble(lst[j]);
                                     if (!num) {
                                         Py_DECREF(lstn);
                                         return ;
                                     }
                                     PyList_SET_ITEM(lstn, j, num);
                                 }
                                 PyTuple_SetItem(lstTitles, i, lstn);
                                //PyTuple_SetItem(lstTitles, 1, PyFloat_FromDouble(get<1>(titles)));
                             }
                             else if(i == 2)
                             {
                                 vector<string> lst = get<2>(title);
                                 PyObject *lstn = PyList_New(lst.size());

                                 for (int j = 0; j < (int)lst.size(); j++)
                                 {
                                     if (!lstn)
                                         return ;
                                     PyObject *num =  PyString_FromString(lst[j].c_str());
                                     if (!num) {
                                         Py_DECREF(lstn);
                                         return ;
                                     }
                                     PyList_SET_ITEM(lstn, j, num);
                                 }
                                 PyTuple_SetItem(lstTitles, i, lstn);
                                //PyTuple_SetItem(lstTitles, i, PyString_FromString((get<2>(titles)).c_str()));
                             }
                            // else if(i == 3)
                               // PyTuple_SetItem(lstTitles, i, PyString_FromString((get<3>(titles)).c_str()));
                         }
                         PyList_SET_ITEM(lstListTitles,a,lstTitles);
                     }

                     PyList_SET_ITEM(lst,(int)listd.size(),lstListTitles);

                     PyList_SET_ITEM(graphs,g,lst);

             }

             if(plotdata.size()  > 0 && graphs)
             {
                 pClass = PyDict_GetItemString(pDict, get<1>(plotdata[0]).c_str());//geting the class. boroved reference
                 if (PyCallable_Check(pClass))
                 {//no such class or class not callable
                     pInstance = PyObject_CallObject(pClass, NULL);//geting an instance. new reference. Arguents for the constructor are NULL
                 }
                 else
                 {
                      EndPython( );
                      return;
                 }

                  pValue = PyObject_CallMethod(pInstance, (char*)get<2>(plotdata[0]).c_str(), (char *)"N", graphs); //call method setAB with argiments int int "(ii)" 12,11

          }
      }
      ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      /// \brief Plot::DisplayPlots
      /// \param populationAndCorrection
      /// \param scaleY
      ///
      void Plot::DisplayPlots(vector<pair<mat,mat>> populations,double scaleY, vector<std::tuple<vector<int>,vector<double>,vector<string>>> titles )
      {
          vector<mat> populationAndCorrection;
          vector<mat> valuesOfX;
          for(auto population :populations)
          {
              populationAndCorrection.push_back(population.second);
              valuesOfX.push_back(population.first);
          }
          vector<vector<vector<double>>>  graphs;
         // Last matrix in populationAndCorrection is a Correction function
         // First matrix = original slectra
         // Second matrix = corrected spectra
          int numberOfGraphs = (int)populationAndCorrection.size();

          for(int g = 0;g < numberOfGraphs;g++)
          {
              vector<vector<double>> samplegraphs;
              if((int)populationAndCorrection[g].n_elem > 0)
              {
                  for(int i =0;i < (int)populationAndCorrection[g].n_rows;i++)
                  {
                      vector<double> samplegraph;
                      rowvec temp = populationAndCorrection[g].row(i);
                      for(int j =0;j < (int)temp.n_cols;j++)
                      {
                          samplegraph.push_back(temp(j));
                      }
                      samplegraphs.push_back(samplegraph);
                  }
              }
              graphs.push_back(samplegraphs);
          }
          vector<std::tuple<string,string,string,vector<vector<vector<double>>>> > plotdata;

          double minX =  0;
          double maxX =  0;
          if((int)valuesOfX.size() > 0)
          {
              if((int)valuesOfX[0].size() > 0)
              {
                  minX =  valuesOfX[0].min();
                  maxX =  valuesOfX[0].max();
              }
          }
          for(int g=0;g < (int)graphs.size();g++)
          {
              vector<vector<double>> a;
              vector<vector<double>> c;
              double minY =  0;
              double maxY =  0;

              if((int)graphs[g].size() > 0)
              {
                  if((int)graphs[g][0].size() > 0)
                  {
                      minY =  graphs[g][0][0];
                      maxY =  graphs[g][0][0];
                  }
              }

              for(int i =0;i<(int)graphs[g].size();i++)
              {
                 double min = *std::min_element(graphs[g][i].begin(), graphs[g][i].end());
                 double max = *std::max_element(graphs[g][i].begin(), graphs[g][i].end());
                 if( min  < minY)
                 {
                     minY = min;
                 }
                 if(max > maxY)
                 {
                     maxY = max;
                 }
              }

              /*if(valuesOfX[g].min() < minX)
              {
                  minX = valuesOfX[g].min();
              }
              if(valuesOfX[g].max() > maxX)
              {
                  maxX = valuesOfX[g].max();
              }*/
                 if(scaleY <=0 )
                     scaleY = 1;

                 for(int i =0;i<(int)graphs[g] .size();i++)
                 {
                      for(int j =0;j< (int)graphs[g][i].size();j++)
                      {
                          graphs[g][i][j] = graphs[g][i][j]  * scaleY;
                      }
                  }

                   vector<double> x;
                   for(int kx = 0;kx < (int)valuesOfX[g].n_cols;kx++)
                   {
                       x.push_back(valuesOfX[g](0,kx));
                   }
                   a= {{x}};


                   minX = valuesOfX[g].min();
                   maxX = valuesOfX[g].max();


                  c = {{minX,maxX,minY,maxY}};
                  if((int)a.size()>0 && (int)graphs[g].size()>0 && (int)c.size() > 0)
                  {
                      vector<vector<vector<double>>> list = {a,graphs[g],c};

                      plotdata.push_back(std::make_tuple("plot","PlotObject","drawFilteredSPectra",list));

                      a.clear();
                      graphs[g].clear();
                      c.clear();
                      list.clear();
                  }
          }


          if((int)plotdata.size() > 0)
          {
              CreatePlot(plotdata,titles);

              plotdata.clear();
          }

      }
      ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      /// \brief Plot::DisplayPlot
      /// \param populations
      /// \param scaleY
      ///
      void Plot::DisplayPlot(vector<pair<mat,mat>> populations,double scaleY, vector<std::tuple<vector<int>,vector<double>,vector<string>>> titles )
       {
           vector<mat> populationAndCorrection;
           vector<mat> valuesOfX;
           for(auto population :populations)
           {
               populationAndCorrection.push_back(population.second);
               valuesOfX.push_back(population.first);
           }
           vector<vector<vector<double>>>  graphs;
          // Last matrix in populationAndCorrection is a Correction function
          // First matrix = original slectra
          // Second matrix = corrected spectra
           int numberOfGraphs = (int)populationAndCorrection.size();

           for(int g = 0;g < numberOfGraphs;g++)
           {
               vector<vector<double>> samplegraphs;
               if((int)populationAndCorrection[g].n_elem > 0)
               {
                   for(int i =0;i < (int)populationAndCorrection[g].n_rows;i++)
                   {
                       vector<double> samplegraph;
                       rowvec temp = populationAndCorrection[g].row(i);
                       for(int j =0;j < (int)temp.n_cols;j++)
                       {
                           samplegraph.push_back(temp(j));
                       }
                       samplegraphs.push_back(samplegraph);
                   }
               }
               graphs.push_back(samplegraphs);
           }

           int count = (int)graphs.size();
           vector<vector<double>> corrections;
           if(count > 0)
           {
                corrections  = graphs[(int)graphs.size() - 1];
                 graphs.pop_back();
           }
           count = (int)graphs.size();
           for(int g = 0;g < count;g++)
           {
               graphs.push_back(graphs[g]);
           }

           for(int g = count;g < (int)graphs.size();g++)
           {
                   for(int c = 0;c<(int)corrections.size();c++)
                   {
                       graphs[g].push_back(corrections[c]);
                   }
           }
           graphs.push_back(corrections);


           int countX = (int)valuesOfX.size();
            mat valuex;
           if(countX > 0)
           {
               valuex= valuesOfX[(int)valuesOfX.size() - 1];
               valuesOfX.pop_back();
           }
           countX = (int)valuesOfX.size();
           for(int g = 0;g < countX;g++)
           {
               valuesOfX.push_back(valuesOfX[g]);
           }
           valuesOfX.push_back(valuex);

           vector<std::tuple<string,string,string,vector<vector<vector<double>>>> > plotdata;

           double minX =  0;
           double maxX =  0;
           if((int)valuesOfX.size() > 0)
           {
               if((int)valuesOfX[0].size() > 0)
               {
                   minX =  valuesOfX[0].min();
                   maxX =  valuesOfX[0].max();
               }
           }
           for(int g=0;g < (int)graphs.size();g++)
           {
               vector<vector<double>> a;
               vector<vector<double>> c;
               double minY =  0;
               double maxY =  0;

               if((int)graphs[g].size() > 0)
               {
                   if((int)graphs[g][0].size() > 0)
                   {
                       minY =  graphs[g][0][0];
                       maxY =  graphs[g][0][0];
                   }
               }

               for(int i =0;i<(int)graphs[g].size();i++)
               {
                  double min = *std::min_element(graphs[g][i].begin(), graphs[g][i].end());
                  double max = *std::max_element(graphs[g][i].begin(), graphs[g][i].end());
                  if( min  < minY)
                  {
                      minY = min;
                  }
                  if(max > maxY)
                  {
                      maxY = max;
                  }
               }

               if(valuesOfX[g].min() < minX)
               {
                   minX = valuesOfX[g].min();
               }
               if(valuesOfX[g].max() > maxX)
               {
                   maxX = valuesOfX[g].max();
               }
                  if(scaleY <=0 )
                      scaleY = 1;

                  for(int i =0;i<(int)graphs[g] .size();i++)
                  {
                       for(int j =0;j< (int)graphs[g][i].size();j++)
                       {
                           graphs[g][i][j] = graphs[g][i][j]  * scaleY;
                       }
                   }

                    vector<double> x;
                    for(int kx = 0;kx < (int)valuesOfX[g].n_cols;kx++)
                    {
                        x.push_back(valuesOfX[g](0,kx));
                    }
                    a= {{x}};

                    if(g == (int)valuesOfX.size() - 1 || graphs[g].size() == 1)
                    {
                        minX = valuesOfX[g].min();
                        maxX = valuesOfX[g].max();
                    }

                   c = {{minX,maxX,minY,maxY}};
                   if((int)a.size()>0 && (int)graphs[g].size()>0 && (int)c.size() > 0)
                   {
                       vector<vector<vector<double>>> list = {a,graphs[g],c};

                       plotdata.push_back(std::make_tuple("plot","PlotObject","drawSamples",list));

                       a.clear();
                       graphs[g].clear();
                       c.clear();
                       list.clear();
                   }
           }


           if((int)plotdata.size() > 0)
           {

               CreatePlot(plotdata,titles);

               plotdata.clear();
           }
       }

      //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      /// \brief BaseFunction::ShowRecreatedConcentrations
      /// \param CCal
      /// \param CCalRec
      /// \param CTest
      /// \param CTestRec
      /// \param CCalRecModels
      /// \param CTestRecModels
      /// \param nPCAModel
      /// \param s
      /// \param option1
      /// \param option2
      /// \param option3
      ///

       void Plot::ShowRecreatedConcentrations
       (
               const mat &CCal,const mat &CCalRec, const mat &CTest, const mat &CTestRec,
               const vector<mat> &CCalRecModels, const vector<mat> &CTestRecModels,
               int nPCAModel,
               const mat & populationMatrix,
               const vector<mat> &BCoeff,int minPCA,int maxPCA,
               int option1,int option2,int option3,
               Statistic cur_stat,
               TaskOptionsParameters  param

       )
       {
           if(!Show)
           {
               return;
           }
           if(CCal.n_elem > 0 && CCalRec.n_elem > 0  )
           {
               if( CCal.n_rows == CCalRec.n_rows )
               {
                       vector<std::tuple<vector<int>,vector<double>,vector<string>>> titles;

                       vector<pair<mat,mat>> populationAndCorrection;
                       int rows = (int)CCal.n_rows;
                       vector<double> valueXConcentrationMin;
                       vector<double> valueXConcentrationMax;


                       for(int i =0; i < (int)param.m_selectedData.m_SampleIndexTest.size();i++)
                       {
                          valueXConcentrationMin.push_back(2 * param.m_selectedData.m_SampleIndexTest[i] + 1);
                       }
                       for(int i =0; i < (int)param.m_selectedData.m_SampleIndexCalib.size();i++)
                       {
                          valueXConcentrationMax.push_back(2 * param.m_selectedData.m_SampleIndexCalib[i]);
                       }
                       std::vector<double>::iterator result1 = std::min_element(std::begin(valueXConcentrationMin), std::end(valueXConcentrationMin));
                       std::vector<double>::iterator result2 = std::min_element(std::begin(valueXConcentrationMax), std::end(valueXConcentrationMax));
                       std::vector<double>::iterator result3 = std::max_element(std::begin(valueXConcentrationMin), std::end(valueXConcentrationMin));
                       std::vector<double>::iterator result4 = std::max_element(std::begin(valueXConcentrationMax), std::end(valueXConcentrationMax));


                       int min1 = valueXConcentrationMin[distance(begin(valueXConcentrationMin),result1)];
                       int max1 = valueXConcentrationMin[distance(begin(valueXConcentrationMin),result3)];
                       int min2 = valueXConcentrationMax[distance(begin(valueXConcentrationMax),result2)];
                       int max2 = valueXConcentrationMax[distance(begin(valueXConcentrationMax),result4)];
                       vector<double> valueXConcentration1;
                       for(int i =min1; i < max1;i++)
                       {
                          valueXConcentration1.push_back(i);
                       }
                       vector<double> valueXConcentration2;
                       for(int i =min2; i < max2;i++)
                       {
                          valueXConcentration2.push_back(i);
                       }
                       mat tMin,tMin2,tMax,tMax2 ;
                       int count=0;
                       if( CTest.n_elem > 0 && CTestRec.n_elem > 0 )
                       {
                           if(CTest.n_rows == CTestRec.n_rows)
                           {
                               tMin = mat(rows,max1 - min1);
                               tMin2 = mat(rows,max1-min1);
                               tMax = mat(rows,max1 - min1);
                               tMax2 = mat(rows,max1-min1);

                               tMin.zeros();
                               tMin2.zeros();
                               tMax.zeros();
                               tMax2.zeros();
                               for(int b =0;b < rows;b++)
                               {
                                    count = 0;
                                   for(int i =0,j=0;i < (int)valueXConcentrationMin.size() ;i++)
                                   {

                                           for(int c = valueXConcentrationMin[i];c < valueXConcentrationMin[i + 1] && count < (int)tMin.n_cols;c++,count++)
                                           {
                                              tMin(b,count) = CTest(b,i);
                                              tMin2(b,count) = CTestRec(b,i);
                                              if(j < (int)valueXConcentrationMax.size())
                                              {
                                                  while(valueXConcentrationMax[j] < c )
                                                      j++;
                                                  if(j < (int)CCal.n_cols && count < (int)tMax.n_cols)
                                                  {
                                                      tMax(b,count) = CCal(b,j);
                                                      tMax2(b,count) = CCalRec(b,j);
                                                  }
                                              }

                                           }

                                    }

                               }
                           }

                           tMin = join_cols(tMin, tMin2);
                           if(option1 == 1 || option1 == 5)
                           {
                               titles.push_back
                                       (
                                           std::make_tuple<vector<int>,vector<double>,vector<string>>(
                                             {nPCAModel},{(double)min1,(double)max1},
                                             {
                                                  param.m_task_name,
                                                   "Test Concentration and Recreated Concentration",
                                                   "Number Of Sample File",
                                                   "Concentration Of the best Model"
                                              })
                                        );
                               populationAndCorrection.push_back(pair<mat,mat>( rowvec( valueXConcentration1),tMin));
                           }

                           tMin = join_cols(tMin, tMax);
                           tMin = join_cols(tMin, tMax2);
                       }


                       mat tMin1,tMin12,tMax1,tMax12 ;
                       tMin1 = mat(rows,max2 - min2);
                       tMin12 = mat(rows,max2-min2);
                       tMax1 = mat(rows,max2 - min2);
                       tMax12 = mat(rows,max2-min2);

                       tMin1.zeros();
                       tMin12.zeros();
                       tMax1.zeros();
                       tMax12.zeros();
                       for(int b =0;b < rows;b++)
                       {
                            count = 0;
                           for(int i =0,j=0;i < (int)valueXConcentrationMax.size()  ;i++)
                           {

                                   for(int c = valueXConcentrationMax[i];c < valueXConcentrationMax[i + 1] && count < (int)tMin1.n_cols;c++,count++)
                                   {
                                      tMin1(b,count) = CCal(b,i);
                                      tMin12(b,count) = CCalRec(b,i);


                                      if(CTest.n_elem > 0 && CTestRec.n_elem > 0 && j < (int)valueXConcentrationMin.size())
                                      {
                                          while(valueXConcentrationMin[j] < c )
                                              j++;
                                          if( j <(int) CTest.n_cols && count < (int)tMax1.n_cols)
                                          {
                                              tMax1(b,count) = CTest(b,j);
                                              tMax12(b,count) = CTestRec(b,j);
                                          }
                                      }

                                   }
                            }

                       }
                       cout << endl;
                       tMin1 = join_cols(tMin1, tMin12);
                       if(option1 == 2 || option1 == 5)
                       {
                            titles.push_back
                            (
                                         std::make_tuple<vector<int>,vector<double>,vector<string>>(
                                         {nPCAModel},{(double)min1,(double)max1},
                                         {
                                                param.m_task_name,
                                                "Calibration Concentration and Created  Concentration Model",
                                                "Number Of Sample File",
                                                "Concentration Of the best Model"
                                          })
                            );
                            populationAndCorrection.push_back(pair<mat,mat>( rowvec( valueXConcentration2),tMin1));
                       }
                       tMin1 = join_cols(tMin1, tMax1);
                       tMin1 = join_cols(tMin1, tMax12);

                        if(option1 == 3 || option1 == 5)
                        {
                           titles.push_back
                                   (
                                       std::make_tuple<vector<int>,vector<double>,vector<string>>(
                                            {nPCAModel},{(double)min2,(double)max2},
                                            {
                                               param.m_task_name,
                                               "Calibration Concentration and Test Concentrations on Scale of Test",
                                               "Number Of Sample File",
                                               "Concentration Of the best Model"
                                             })
                                    );
                           populationAndCorrection.push_back(pair<mat,mat>( rowvec( valueXConcentration1),tMin));
                        }
                        if(option1 == 4 || option1 == 5)
                        {
                          titles.push_back
                                  (
                                      std::make_tuple<vector<int>,vector<double>,vector<string>>(
                                           {nPCAModel},{(double)min2,(double)max2},
                                           {
                                               param.m_task_name,
                                              "Calibration Concentration and Test Concentrations on Scale of Calibration",
                                              "Number Of Sample File","Concentration Of the best Model"
                                           })
                                   );
                          populationAndCorrection.push_back(pair<mat,mat>( rowvec( valueXConcentration2),tMin1));
                        }
                        if(option2 > 0)
                        {
                            ShowAllRecreatedConcentrationsModels
                            (
                                        populationAndCorrection,
                                        titles,
                                        CCal,CCalRecModels,
                                        CTest,CTestRecModels,
                                        BCoeff, minPCA, maxPCA,
                                        option2,
                                        cur_stat,
                                        param

                            );
                        }

                        if(option3 > 0)
                        {
                            ShowPCAData(populationAndCorrection,titles,populationMatrix,nPCAModel,cur_stat,param);
                        }
                        DisplayPlots( populationAndCorrection,1,titles );
                        populationAndCorrection.clear();
              }
           }
       }
       /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
       /// \brief BaseFunction::ShowAllRecreatedConcentrationsModels
       /// \param addToDisplay
       /// \param CCal
       /// \param CCalRec
       /// \param CTest
       /// \param CTestRec
       /// \param option
       ///
       void Plot::ShowAllRecreatedConcentrationsModels
       (
               vector<pair<mat,mat>> &addToDisplay,
               vector<std::tuple<vector<int>,vector<double>,vector<string>>> &titles,
               const mat &CCal,const vector<mat> &CCalRec,
               const mat & CTest, const vector<mat> & CTestRec,
               const vector<mat> &BCoeff,int minPCA,int maxPCA,
               int option,
               const  Statistic &  cur_stat,
               const TaskOptionsParameters  &param
       )
       {
           if(!Show)
           {
               return;
           }
           mat CC = CCal,CT = CTest,B ;

           for(int i =0;i< (int)CCalRec.size();i++)
           {
                 CC = join_cols(CC, CCalRec[i]);
           }
           for(int i =0;i< (int)CTestRec.size();i++)
           {
                 CT = join_cols(CT, CTestRec[i]);
           }
           if(minPCA < 0)
           {
               minPCA =0;
           }
           if(maxPCA >  cur_stat.numberOfPcaComponents)
           {
              maxPCA = min(cur_stat.numberOfPcaComponents,(int)BCoeff.size());
           }

           int maxCol = (int)BCoeff[(int)BCoeff.size() - 1].n_rows;
           int maxRow = (int)BCoeff[(int)BCoeff.size() - 1].n_cols;

           vector<mat> ConstituentsCoefficients((int)BCoeff[0].n_cols,mat(0,0));

           for(int c = 0;c <(int)ConstituentsCoefficients.size();c++)
           {
               B = mat(0,0);
               for(int i =minPCA;i < maxPCA;i++)
               {
                   mat btemp = mat(maxRow,maxCol);
                   btemp.zeros();
                   btemp.cols(0,i) = BCoeff[i].t();
                   B = join_cols(B, btemp);
               }
               ConstituentsCoefficients[c] = B;
           }
           vector<double> valueXConcentrationMin;
           vector<double> valueXConcentrationMax;


           for(int i =0; i < (int)param.m_selectedData.m_SampleIndexTest.size();i++)
           {
              valueXConcentrationMin.push_back(2 * param.m_selectedData.m_SampleIndexTest[i]);
           }
           for(int i =0; i < (int)param.m_selectedData.m_SampleIndexCalib.size();i++)
           {
              valueXConcentrationMax.push_back(2 * param.m_selectedData.m_SampleIndexCalib[i] + 1);
           }
           rowvec pcaX(maxCol);
           for(int i=0;i < maxCol;i++)
           {
               pcaX(i) = i ;
           }
           std::vector<double>::iterator result1 = std::min_element(std::begin(valueXConcentrationMin), std::end(valueXConcentrationMin));
           std::vector<double>::iterator result2 = std::min_element(std::begin(valueXConcentrationMax), std::end(valueXConcentrationMax));
           std::vector<double>::iterator result3 = std::max_element(std::begin(valueXConcentrationMin), std::end(valueXConcentrationMin));
           std::vector<double>::iterator result4 = std::max_element(std::begin(valueXConcentrationMax), std::end(valueXConcentrationMax));


           int min1 = valueXConcentrationMin[distance(begin(valueXConcentrationMin),result1)];
           int max1 = valueXConcentrationMin[distance(begin(valueXConcentrationMin),result3)];
           int min2 = valueXConcentrationMax[distance(begin(valueXConcentrationMax),result2)];
           int max2 = valueXConcentrationMax[distance(begin(valueXConcentrationMax),result4)];
           vector<double> valueXConcentration1;
           for(int i =min1; i < max1;i++)
           {
              valueXConcentration1.push_back(i);
           }
           vector<double> valueXConcentration2;
           for(int i =min2; i < max2;i++)
           {
              valueXConcentration2.push_back(i);
           }

           mat CCScaled= mat((int)CC.n_rows,max1 - min1),CTScaled = mat((int)CT.n_rows,max2 - min2);
           int count =0;
           int rows = 0;
           if(CCScaled.n_elem > 0 && CTScaled.n_elem > 0)
              rows = min((int)CCScaled.n_rows,(int)CTScaled.n_rows);
           else if(CCScaled.n_elem > 0 && CTScaled.n_elem <= 0)
               rows = (int)(int)CCScaled.n_rows;
           else if(CCScaled.n_elem <= 0 && CTScaled.n_elem > 0)
               rows = (int)CTScaled.n_rows;
           for(int b =0;b < rows;b++)
           {

                   count = 0;
                   for(int i =0;i < (int)valueXConcentrationMax.size()-1 && b < (int)CCScaled.n_rows && b < (int)CC.n_rows;i++)
                   {
                           for(int c = valueXConcentrationMax[i];c < valueXConcentrationMax[i + 1] && count < (int) CCScaled.n_cols;c++,count++)
                           {
                              CCScaled(b,count) = CC(b,i);
                           }
                   }

                   count = 0;
                  for(int i =0;i < (int)valueXConcentrationMin.size()-1 && b < (int)CTScaled.n_rows && b < (int)CT.n_rows;i++)
                  {
                          for(int c = valueXConcentrationMin[i];c < valueXConcentrationMin[i + 1]  && count < (int) CTScaled.n_cols;c++,count++)
                          {
                             CTScaled(b,count) = CT(b,i);
                          }
                   }
           }
           string  titleStart;
           if(param.m_currentSet == 0)
           {
               titleStart = " Calibration Set : Number Of Samples = " + to_string((int)param.m_currentPopulationMatrix.n_rows) +
                            " Number Of Selected Variables = " + to_string((int)param.m_currentPopulationMatrix.n_cols) + " ";

           }
           else if(param.m_currentSet == 1)
           {
               titleStart = " Testing  Set : Number Of Samples = " + to_string((int)param.m_testingPopulationMatrix.n_rows) +
                       " Number Of Selected Variables = " + to_string((int)param.m_testingPopulationMatrix.n_cols) + " ";

           }
           if(option == 1)
           {
                     titles.push_back
                             (
                                 std::make_tuple<vector<int>,vector<double>,vector<string>>(
                                    {1,(int)CCalRec.size()},{(double)min1,(double)max1},
                                    {
                                         param.m_task_name,
                                         titleStart + " Calibration Concentration For different Number Of PCA ",
                                         "Number Of Sample File",
                                         "Concentration"
                                     })
                              );
                     addToDisplay.push_back(pair<mat,mat>( rowvec( valueXConcentration1),CCScaled));

           }
           else if(option == 2)
           {
                     titles.push_back
                             (
                                 std::make_tuple<vector<int>,vector<double>,vector<string>>(
                                   {1,(int)CTestRec.size()},{(double)min2,(double)max2},
                                   {
                                         param.m_task_name,
                                         titleStart + " Test Concentration For different Number Of PCA ",
                                         "Number Of Sample File",
                                         "Concentration"
                                    })
                             );
                     addToDisplay.push_back(   pair<mat,mat>( rowvec( valueXConcentration2),CTScaled   )    );
           }
           else if(option == 3)
           {
                    titles.push_back
                            (
                                std::make_tuple<vector<int>,vector<double>,vector<string>>(
                                     {1,(int)CCalRec.size()},{(double)min1,(double)max1},
                                     {
                                        param.m_task_name,
                                        titleStart + " Calibration Concentration For different Number Of PCA ",
                                        "Number Of Sample File",
                                        "Concentrtion"
                                     })
                            );
                    addToDisplay.push_back(pair<mat,mat>( rowvec( valueXConcentration1),CCScaled));

                    titles.push_back
                            (
                                std::make_tuple<vector<int>,vector<double>,vector<string>>(
                                     {1,(int)CTestRec.size()},{(double)min2,(double)max2},
                                     {
                                        param.m_task_name,
                                        titleStart + " Test Concentration For different Number Of PCA ",
                                        "Number Of Sample File",
                                        "Concentration"
                                     })
                            );
                    addToDisplay.push_back(pair<mat,mat>( rowvec( valueXConcentration2),CTScaled));
           }
           for(int c = 0;c < (int)ConstituentsCoefficients.size();c++)
           {
               titles.push_back
                       (
                           std::make_tuple<vector<int>,vector<double>,vector<string>>(
                              {1,(int)pcaX.size()},{(double)c },
                              {
                                   param.m_task_name,
                                   titleStart + " Calibration Coefficients For different Number Of PCA Constituent Name = "+ ConstituentsName.at(Constituents(c)),
                                   "Number Of PCA",
                                   "Calibration Coefficient"
                               })
                        );
               addToDisplay.push_back(pair<mat,mat>( pcaX,B));
           }
       }
       //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
       /// \brief BaseFunction::ShowPCAData
       /// \param addToDisplay
       /// \param statistic
       /// \param NPCA
       ///
       void Plot::ShowPCAData
       (
               vector<pair<mat,mat>> &addToDisplay,
               vector<std::tuple<vector<int>,vector<double>,vector<string>>> &titles,
               const mat & populationMatrix,int NPCA,  const Statistic &cur_stat, const TaskOptionsParameters  &param
       )
       {

           if(!Show)
           {
               return;
           }
           rowvec pcaX(cur_stat.numberOfPcaComponents);
           for(int i = 0;i < cur_stat.numberOfPcaComponents;i++)
           {
               pcaX(i) = i ;
           }

           //join testing and calibration Matrixes to view
           mat A = (join_cols(cur_stat.currentPopulationMatrix,populationMatrix));
           string  titleStart;
           if(param.m_currentSet == 0)
           {
               titleStart = " Calibration Set : Number Of Samples = " + to_string((int)param.m_currentPopulationMatrix.n_rows) +
                            " Number Of Selected Variables = " + to_string((int)param.m_currentPopulationMatrix.n_cols) + " ";

           }
           else if(param.m_currentSet == 1)
           {
               titleStart = " Testing  Set : Number Of Samples = " + to_string((int)param.m_testingPopulationMatrix.n_rows) +
                       " Number Of Selected Variables = " + to_string((int)param.m_testingPopulationMatrix.n_cols) + " ";

           }
           string title0 = titleStart + " Calibration And Testing Matrixes\n";
           title0 = title0 + " Samples Selected For Calibration And Test\n ";

           titles.push_back
                   (
                       std::make_tuple<vector<int>,vector<double>,vector<string>>(
                         {0,(int)cur_stat.currentPopulationMatrix.n_rows},{param.m_currentValuesOfX},
                         {
                               param.m_task_name,
                               title0,
                               "Wavelength (nm) ",
                               "Spectra"
                          })
                    );
           addToDisplay.push_back(pair<mat,mat>( rowvec(param.m_currentValuesOfX).cols(0,(int)A.n_cols - 1),A));
           if(NPCA <(int) cur_stat.F_pcaFactors.size())
           {
               // (m_currentdata.m_saved_model.currentPopulationMatrix.cols(0, NPCA) * m_currentdata.m_saved_model.F_pcaFactors[ NPCA].t()).print("A * F.t()=");
               //(m_currentdata.m_saved_model.S_pcaScores[ NPCA]).print("S =");
               //(m_currentdata.m_saved_model.S_pcaScores[ NPCA] * m_currentdata.m_saved_model.F_pcaFactors[ NPCA]).print("A = S * F = ");
               titles.push_back
                       (
                           std::make_tuple<vector<int>,vector<double>,vector<string>>(
                             {1,NPCA},{},
                             {
                                   param.m_task_name,
                                   titleStart + " EigenVectors Best Model With Number Of PCA = [" +  to_string(NPCA) + "] out of maxPCA number = "+ to_string(cur_stat.numberOfPcaComponents) ,
                                   "Number Of PCA Components",
                                   "Eigenvector Value"
                             })
                       );
               addToDisplay.push_back(pair<mat,mat>(  pcaX.cols(0, NPCA),cur_stat.F_pcaFactors[ NPCA]  )  ); // Displays EigenVectors

               titles.push_back
                       (
                           std::make_tuple<vector<int>,vector<double>,vector<string>>(
                              {1,NPCA},{},
                              {
                                   param.m_task_name,
                                   titleStart + " Principal Components Best Model With Number Of PCA = [" +  to_string(NPCA) + "] out of maxPCA number = "+ to_string(cur_stat.numberOfPcaComponents),
                                   "Number Of PCA Components",
                                   "PCA Spectra Value"
                              })
                       );
               addToDisplay.push_back(pair<mat,mat>(  pcaX.cols(0, NPCA),cur_stat.PCA[NPCA]   )  );          // Displays Principal Components

               titles.push_back
                       (
                                   std::make_tuple<vector<int>,vector<double>,vector<string>>(
                                  {1,NPCA},{},
                                  {
                                     param.m_task_name,
                                    titleStart + " Calibration Coefficients Best Model With Number Of PCA = [" +  to_string(NPCA) + "] out of maxPCA number = "+ to_string(cur_stat.numberOfPcaComponents),
                                    "Number Of PCA Components",
                                    "Calibration Coefficient Value"
                                  })
                       );
               addToDisplay.push_back(pair<mat,mat>(  pcaX.cols(0, NPCA),cur_stat.B_calibrationCofficients[ NPCA].t())     );  //populationAndCorrection.push_back(pair<mat,mat>( rowvec(valueXConcentration),join_cols( statistic.C_RecreatedConcentrations[0],statistic.currentConcentrationMatrix)));
           }
        }
       //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
       /// \brief Plot::ShowCorrected
       /// \param before
       /// \param after
       /// \param param
       ///
        void Plot::ShowCorrected(mat spectraBefore, mat spectraAfter,const TaskOptionsParameters  &param)
        {
            if(!Show)
            {
                return;
            }
            vector<pair<mat,mat>> populationAndCorrection;
            vector<std::tuple<vector<int>,vector<double>,vector<string>>> titles;

            vector<double> selectedPoints;

            mat selectedFunctionPoints = mat((int)param.m_CorrectionFunction.second.n_rows, param.m_fitParameters.m_Xpoints.size() + 2);
            selectedFunctionPoints.zeros();
            selectedPoints.push_back(param.m_currentValuesOfX[0]);
            for(int i = 0;i < (int)param.m_fitParameters.m_Xpoints.size();i++)
            {
                selectedPoints.push_back(param.m_currentValuesOfX[param.m_fitParameters.m_Xpoints[i]]);
            }

            selectedPoints.push_back(param.m_currentValuesOfX[param.m_currentValuesOfX.size() -1]);

            for(int a =0;a < (int)param.m_CorrectionFunction.second.n_rows;a++)
            {
                if(param.m_fitParameters.m_Xpoints.size() > 0 && param.m_fitParameters.m_Xpoints[0] != 0)
                {
                  selectedFunctionPoints(a,0) = param.m_CorrectionFunction.second(a,0);
                }
                for(int i = 0;i < (int)param.m_fitParameters.m_Xpoints.size();i++)
                {
                    selectedFunctionPoints(a,i+1) = param.m_CorrectionFunction.second(a,param.m_fitParameters.m_Xpoints[i]);
                   // cout << selectedPoints[i+ 1] << " "<<selectedFunctionPoints(a,i+1) << "  "<<param.m_CorrectionFunction.second(a,param.m_fitParameters.m_Xpoints[i]) << endl;
                   // cout << endl;
                }

                if(param.m_fitParameters.m_Xpoints.size() > 0 &&
                        param.m_fitParameters.m_Xpoints[param.m_fitParameters.m_Xpoints.size() - 1] != param.numOfDataPoints - 1)
                {
                    selectedFunctionPoints(a,selectedPoints.size() -1) = param.m_CorrectionFunction.second(a,selectedPoints.size() -1);
                }
            }
            string titleStart;
            if(param.m_currentSet == 0)
            {
                titleStart = " Calibration Set : Number Of Samples = " + to_string((int)param.m_currentPopulationMatrix.n_rows) +
                             " Number Of Selected Variables = " + to_string((int)param.m_currentPopulationMatrix.n_cols) + " ";
                for(int i =0; i < (int)param.m_selectedData.m_SampleIndexCalib.size();i++)
                {
                   selectedPoints.push_back(2 * param.m_selectedData.m_SampleIndexCalib[i]);
                }
            }
            else if(param.m_currentSet == 1)
            {
                titleStart = " Testing  Set : Number Of Samples = " + to_string((int)param.m_testingPopulationMatrix.n_rows) +
                        " Number Of Selected Variables = " + to_string((int)param.m_testingPopulationMatrix.n_cols) + " ";
                for(int i =0; i < (int)param.m_selectedData.m_SampleIndexTest.size();i++)
                {
                   selectedPoints.push_back(2 * param.m_selectedData.m_SampleIndexCalib[i] + 1);
                }
            }
            if((int)param.m_currentValuesOfX.size() > 0 && (int)param.m_CorrectionFunction.second.n_elem > 0
                    && (int)param.m_currentValuesOfX.size() == (int)param.m_CorrectionFunction.second.n_cols)
            {
                titles.push_back
                                (
                                            std::make_tuple<vector<int>,vector<double>,vector<string>>(
                                           {param.m_fitParameters.m_Xpoints},{selectedPoints},
                                           {
                                              param.m_task_name,
                                             titleStart + " Correction Function Full",
                                             "Wavelength (nm)",
                                             "Spectra",
                                             "p"

                                           })
                                );
                populationAndCorrection.push_back(pair<mat,mat>( rowvec(param.m_currentValuesOfX), param.m_CorrectionFunction.second));
            }
            // Display Correction For Smoothing
            if
            (
                     param.m_dataSmoothingParameters != nullptr && (int)param.m_CorrectionFunction.first.n_elem > 0 &&
                     (int)param.m_CorrectionFunction.second.n_elem > 0
            )
            {
                    if( (int)param.m_CorrectionFunction.first.n_cols == (int)param.m_CorrectionFunction.second.n_cols)
                    {
                        string title = titleStart + " Correction Function: [Number Of Points Selected for fit = " + to_string(param.m_dataSmoothingParameters->numberOfPoints)
                                + "] [Polinomial Degree = " + to_string(param.m_dataSmoothingParameters->polinomialDegree) + "] ";
                        if(param.m_dataSmoothing == BINOMIAL)
                        {
                           title = title + " [Binomial SMoothing] ";
                        }
                        else if(param.m_dataSmoothing == SAVITZJY_GOLAY)
                        {
                             title = title + " [Savitzky Golay Smoothing] ";
                        }
                        titles.push_back
                                        (
                                                   std::make_tuple<vector<int>,vector<double>,vector<string>>(
                                                   {param.m_dataSmoothingParameters->polinomialDegree},{},
                                                   {
                                                      param.m_task_name,
                                                      title,
                                                     "Number Of Points",
                                                     "Correction Function Value",

                                                   })
                                        );
                        populationAndCorrection.push_back(pair<mat,mat>( param.m_CorrectionFunction.first, param.m_CorrectionFunction.second));
                    }
            }
            // Display Corrections for Derivative
            if
            (
                    param.m_derivativeParameters != nullptr &&
                    (int)param.m_derivativeParameters->outputSpectrum.first.n_cols == (int)(int)param.m_derivativeParameters->outputSpectrum.second.n_cols
            )
            {
                string alg;
                if(DerivativeAlgorithmTypeTextMap.find(param.m_derivativeSpectraType.second) != DerivativeAlgorithmTypeTextMap.end())
                {
                    alg = DerivativeAlgorithmTypeTextMap.at(param.m_derivativeSpectraType.second);
                }
                if(param.m_CorrectionFunction.second.n_elem > 0 && param.m_CorrectionFunction.first.n_elem > 0 &&
                        param.m_CorrectionFunction.second.n_cols == param.m_CorrectionFunction.first.n_cols)
                {
                    string title = titleStart + " Algorithm type = " +  alg +
                                   " Derivative Order = " +   to_string( ((SavitzkyFit*)param.m_derivativeParameters)->derivativeOrder) +
                                   " Vandermonde Matrix  of Tj Matrix of the Polinomial Degree = " + to_string(param.m_derivativeParameters->polinomialDegree) +
                                   " Number Of Points = " + to_string(param.m_derivativeParameters->numberOfPoints) + "  \n";

                    for(int i=0;i< (int)param.m_derivativeParameters->leastSquareFit.n_rows;i++)
                    {
                        string dblstr;
                        for(int j=0;j < (int)param.m_derivativeParameters->leastSquareFit.n_cols;j++)
                        {
                            std::ostringstream strs;
                            strs << param.m_derivativeParameters->leastSquareFit(i,j);

                            dblstr =  dblstr + " " + strs.str();
                        }
                        title = title + dblstr + "\n";
                    }

                    titles.push_back
                                    (
                                                std::make_tuple<vector<int>,vector<double>,vector<string>>(
                                               {(int)param.m_derivativeParameters->leastSquareFit.n_rows,(int)param.m_derivativeParameters->leastSquareFit.n_cols},{},
                                               {
                                                  param.m_task_name,
                                                  title,
                                                 " Number Of Points in Vandermonde Matrix",
                                                 " Tj matrix row number (derivative order) " + to_string( ((SavitzkyFit*)param.m_derivativeParameters)->derivativeOrder),

                                               })
                                    );
                    populationAndCorrection.push_back(pair<mat,mat>( rowvec( param.m_CorrectionFunction.first), param.m_CorrectionFunction.second));
                }

                // Display Derivative Spectra
                if((int)spectraAfter.n_elem > 0 && (int)param.m_derivativeParameters->outputSpectrum.first.n_elem > 0 &&
                        (int)spectraAfter.n_cols ==  (int)param.m_derivativeParameters->outputSpectrum.first.n_cols)
                {
                    string npoints;
                    if(param.m_derivativeSpectraType.second == GAP || param.m_derivativeSpectraType.second == SIMPLE_DIFFERENCE)
                    {
                        npoints =  " Gap = " + to_string(param.m_derivativeParameters->numberOfPoints) + "  \n";
                    }
                    else
                    {
                        npoints =  " Number Of Points = " + to_string(param.m_derivativeParameters->numberOfPoints) + "  \n";
                    }
                    titles.push_back
                                    (
                                               std::make_tuple<vector<int>,vector<double>,vector<string>>(
                                               {(int)param.m_derivativeParameters->leastSquareFit.n_rows,(int)param.m_derivativeParameters->leastSquareFit.n_cols},{},
                                               {
                                                  param.m_task_name,
                                                  titleStart + " Derivative After Function of " + to_string( ((SavitzkyFit*)param.m_derivativeParameters)->derivativeOrder) + "  \n" +
                                                  " Derivative Order of the Spectra. "  +
                                                  " " + alg + "  \n" +
                                                  " Polinomial Degree = " + to_string(param.m_derivativeParameters->polinomialDegree) + "  \n" +
                                                  npoints,
                                                 "Wavelength (nm)",
                                                 "Derivative Spectra Derivative Order = " + to_string( ((SavitzkyFit*)param.m_derivativeParameters)->derivativeOrder),


                                               })
                                    );
                    populationAndCorrection.push_back(pair<mat,mat>( rowvec( param.m_derivativeParameters->outputSpectrum.first), spectraAfter));
                }
            }
           // Display Spectra before the transformations
            mat A;
            if((int)spectraBefore.n_elem > 0 && param.m_currentValuesOfX.size() > 0)
            {
                string title ;
                if((int)param.m_CorrectionFunction.second.n_elem > 0 &&
                        (int)spectraBefore.n_cols == (int)param.m_CorrectionFunction.second.n_cols  &&
                        (int)spectraBefore.n_cols == (int)param.m_currentValuesOfX.size() &&
                        (int)spectraBefore.n_rows < 10
                )
                {
                     A = (join_cols(spectraBefore,param.m_CorrectionFunction.second));
                     title =  " Spectra  Before Correction and Correction Function";
                }
                else
                {
                       A = spectraBefore;
                      title =  " Spectra  Before Applying Correction or and Original Spectra";
                }
                if((int)param.m_currentValuesOfX.size() == (int)A.n_cols)
                {
                    titles.push_back
                    (
                       std::make_tuple<vector<int>,vector<double>,vector<string>>(
                       {},{},
                       {
                           param.m_task_name,
                           titleStart + title,
                           "Wavelength (nm)",
                           "Spectra"
                       })
                   );
                    populationAndCorrection.push_back(pair<mat,mat>( rowvec(param.m_currentValuesOfX),A));
                }
            }

            if((int)spectraAfter.n_elem > 0  && param.m_currentValuesOfX.size() > 0)
            {

                 string title ;
                 if((int)param.m_CorrectionFunction.second.n_elem > 0 &&
                            (int)spectraAfter.n_cols == (int)param.m_CorrectionFunction.second.n_cols   &&
                            (int)spectraAfter.n_cols == (int)param.m_currentValuesOfX.size() &&
                            (int)spectraAfter.n_rows < 10
                 )
                 {
                         A = (join_cols(spectraAfter,param.m_CorrectionFunction.second));
                         title =  " Spectra  After Correction and Correction Function";
                 }
                 else
                 {
                         A = spectraAfter;
                         title =  " Spectra  After Applying Correction.";
                 }

                 if((int)param.m_currentValuesOfX.size() == (int)A.n_cols)
                 {
                     titles.push_back
                     (
                                                        std::make_tuple<vector<int>,vector<double>,vector<string>>(
                                                       {},{},
                                                       {
                                                          param.m_task_name,
                                                          titleStart + title,
                                                         "Wavelength (nm)",
                                                         "Spectra"
                                                       })
                      );

                      populationAndCorrection.push_back(pair<mat,mat>( rowvec(param.m_currentValuesOfX),A));
                   }

            }

             // This will display the correction function and the result of applying the correction to the spectra

            DisplayPlots( populationAndCorrection,1,titles );
            populationAndCorrection.clear();
        }
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Plot::ShowCorrected
        /// \param spectraBefore
        /// \param spectraAfter
        /// \param concentrationsBefore
        /// \param concentrationsAfter
        /// \param param
        ///
          void Plot::ShowCorrected( mat spectraBefore, mat spectraAfter,mat concentrationsBefore,mat concentrationsAfter,const TaskOptionsParameters  &param)
          {
              if(!Show)
              {
                  return;
              }
              vector<pair<mat,mat>> populationAndCorrection;
              vector<double> selectedPoints;
              vector<std::tuple<vector<int>,vector<double>,vector<string>>> titles;
              string titleStart;

              string title ;

              if(param.m_currentSet == 0)
              {
                  titleStart = " Calibration Set : Number Of Samples = " + to_string((int)param.m_currentPopulationMatrix.n_rows) +
                               " Number Of Selected Variables = " + to_string((int)param.m_currentPopulationMatrix.n_cols) + " ";
                  for(int i =0; i < (int)param.m_selectedData.m_SampleIndexCalib.size();i++)
                  {
                     selectedPoints.push_back(2 * param.m_selectedData.m_SampleIndexCalib[i]);
                  }
              }
              else if(param.m_currentSet == 1)
              {
                  titleStart = " Testing  Set : Number Of Samples = " + to_string((int)param.m_testingPopulationMatrix.n_rows) +
                          " Number Of Selected Variables = " + to_string((int)param.m_testingPopulationMatrix.n_cols) + " ";
                  for(int i =0; i < (int)param.m_selectedData.m_SampleIndexTest.size();i++)
                  {
                     selectedPoints.push_back(2 * param.m_selectedData.m_SampleIndexCalib[i] + 1);
                  }
              }
              mat A;

              if((int)spectraBefore.n_elem > 0 && (int)spectraBefore.n_rows == 1)
              {
                  if((int)spectraBefore.n_cols == (int)param.m_currentValuesOfX.size())
                  {

                      if((int)spectraAfter.n_elem > 0 &&   (int)spectraBefore.n_cols == (int)spectraAfter.n_cols   )
                      {
                           A = (join_cols(spectraBefore,spectraAfter));
                           title =  titleStart + " Spectra  Before Correction and Spectra After Correction";
                      }
                      else
                      {
                             A = spectraBefore;
                             title =  titleStart + " Spectra  Before Applying Correction or and Original Spectra";
                      }
                      titles.push_back
                                      (
                                                 std::make_tuple<vector<int>,vector<double>,vector<string>>(
                                                 {},{},
                                                 {
                                                    param.m_task_name,
                                                    title,
                                                   "Wavelength (nm)",
                                                   "Spectra"
                                                 })
                                      );
                      populationAndCorrection.push_back(pair<mat,mat>( rowvec(param.m_currentValuesOfX),A));
                  }
              }
              else
              {
                  if((int)spectraBefore.n_cols == (int)param.m_currentValuesOfX.size())
                  {
                      A = spectraBefore;
                      title =  titleStart + " Spectra  Before Applying Correction or and Original Spectra";
                      titles.push_back
                                      (
                                                 std::make_tuple<vector<int>,vector<double>,vector<string>>(
                                                 {},{},
                                                 {
                                                    param.m_task_name,
                                                    title,
                                                   "Wavelength (nm)",
                                                   "Spectra"
                                                 })
                                      );
                      populationAndCorrection.push_back(pair<mat,mat>( rowvec(param.m_currentValuesOfX),A));
                  }
                  if((int)spectraAfter.n_elem > 0 && (int)spectraAfter.n_cols == (int)param.m_currentValuesOfX.size())
                  {
                      A = spectraAfter;
                      title =  titleStart + " Spectra  After Applying Correction or and Original Spectra";
                      titles.push_back
                                      (
                                                 std::make_tuple<vector<int>,vector<double>,vector<string>>(
                                                 {},{},
                                                 {
                                                    param.m_task_name,
                                                    title,
                                                   "Wavelength (nm)",
                                                   "Spectra"
                                                 })
                                      );
                      populationAndCorrection.push_back(pair<mat,mat>( rowvec(param.m_currentValuesOfX),A));
                  }
              }
              ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

              if((int)concentrationsBefore.n_elem > 0 )
              {
                  if((int)concentrationsBefore.n_cols == (int) selectedPoints.size())
                  {
                      string title ;
                      if((int)concentrationsAfter.n_elem > 0 &&   (int)concentrationsBefore.n_cols == (int)concentrationsAfter.n_cols   )
                      {
                           A = (join_cols(concentrationsBefore,concentrationsAfter));
                           title =  titleStart + "Concentration  Before Correction and Concentration After Correction";
                      }
                      else
                      {

                             A = concentrationsBefore;
                             title =  titleStart + " Concentration  Before Applying Correction or and Original Spectra";
                      }
                      titles.push_back
                                      (
                                                 std::make_tuple<vector<int>,vector<double>,vector<string>>(
                                                 {},{},
                                                 {
                                                    param.m_task_name,
                                                    title,
                                                   "Sample Number",
                                                   "Concentration"
                                                 })
                                      );
                      populationAndCorrection.push_back(pair<mat,mat>( rowvec( selectedPoints),A));
                  }
              }

              DisplayPlots( populationAndCorrection,1,titles );
              populationAndCorrection.clear();

          }
          ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
          /// \brief Plot::ShowFunction
          /// \param func
          /// \param param
          /// \param populationAndCorrection
          /// \param titles
          ///
          void Plot::ShowFunction
          (
                  pair<  mat,mat > func,
                  const TaskOptionsParameters  &param,
                  vector<pair<mat,mat>> &populationAndCorrection,
                  vector<std::tuple<vector<int>,vector<double>,vector<string>>>  &titles
          )
          {
              if(!Show)
              {
                  return;
              }
              string titleStart;

              if(param.m_currentSet == 0)
              {
                  titleStart = " Calibration Set : Number Of Samples = " + to_string((int)param.m_currentPopulationMatrix.n_rows) +
                               " Number Of Selected Variables = " + to_string((int)param.m_currentPopulationMatrix.n_cols) + " ";

              }
              else if(param.m_currentSet == 1)
              {
                  titleStart = " Testing  Set : Number Of Samples = " + to_string((int)param.m_testingPopulationMatrix.n_rows) +
                          " Number Of Selected Variables = " + to_string((int)param.m_testingPopulationMatrix.n_cols) + " ";

              }
              if((int)func.first.n_elem > 0 && (int)func.second.n_elem > 0)
              {
                  if((int)func.first.n_cols == (int)func.second.n_cols)
                  {
                      titles.push_back
                                      (
                                                 std::make_tuple<vector<int>,vector<double>,vector<string>>(
                                                 {},{},
                                                 {
                                                    param.m_task_name,
                                                    titleStart,
                                                   "Function X",
                                                   "Function Y"
                                                 })
                                      );
                      populationAndCorrection.push_back(pair<mat,mat>( func.first,func.second));
                  }

              }

          }
          /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
          /// \brief Plot::ShowFunction
          /// \param func
          /// \param param
          ///
          void Plot::ShowFunction( vector<pair<  mat,mat >> func, const TaskOptionsParameters  &param)
          {
              if(!Show)
              {
                  return;
              }
              vector<pair<mat,mat>> populationAndCorrection;
              vector<std::tuple<vector<int>,vector<double>,vector<string>>> titles;
               for(auto f: func)
               {
                   ShowFunction( f, param,populationAndCorrection,titles);
               }

               DisplayPlots( populationAndCorrection,1,titles );
               populationAndCorrection.clear();
          }


           void Plot::ShowStatisticsGraphs( vector<ValidationModel> &validation,const TaskOptionsParameters  &param)
          {
              if(!Show)
              {
                  return;
              }
              vector<pair<mat,mat>> populationAndCorrection;
              vector<std::tuple<vector<int>,vector<double>,vector<string>>> titles;

              std::sort(validation.begin(),validation.end(),validation[0]);
              vector<double> press;
              vector<double> pcanumber;
              for(auto v: validation)
              {
                   pcanumber.push_back(v.PCANumber + 1);
                   press.push_back(v.ModelCrossValidation.PRESSAVERAGE);
              }


              if((int)pcanumber.size() == (int)press.size())
              {
                  titles.push_back
                                  (
                                             std::make_tuple<vector<int>,vector<double>,vector<string>>(
                                             {},{},
                                             {
                                                param.m_task_name,
                                                "Statistic  Values",
                                               "PCA Number",
                                               "Press Value",
                                                "p"

                                             })
                                  );
                  populationAndCorrection.push_back(pair<mat,mat>(rowvec(pcanumber),rowvec(press)));
              }

              DisplayPlots( populationAndCorrection,1,titles );
              populationAndCorrection.clear();
          }
           /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
           void Plot::ShowPredictedConcentrations
           (
                   const Statistic & validation,
                   const  Statistic &  prediction,
                   const TaskOptionsParameters  &param
           )
           {

               if(!Show)
               {
                   return;
               }
               vector<pair<mat,mat>> populationAndCorrection;
               vector<std::tuple<vector<int>,vector<double>,vector<string>>> titles;


               mat A;// = validation.CalibrationStat[0].RecreatedConcentrations;
               mat B;// = prediction.CalibrationStat[0].RecreatedConcentrations;
               mat C;// = validation.CalibrationStat[0].OriginalConcentrations;
               mat D ;//= prediction.CalibrationStat[0].OriginalConcentrations;
               mat E,A1,B1,C1,D1;
               string a,b,c,d;
               vector<int> aa;
               vector<double> aa1;
               vector<int> bb;
               vector<double> bb1;

               vector<double> valueXConcentrationTest;
               vector<double> valueXConcentrationValidation;
               vector<double> valueXConcentrationTest1;
               vector<double> valueXConcentrationValidation1;
               vector<double> sampleValidationX;
               vector<double> sampleX;
               int ii = param.m_currentSet;
               if(param.m_currentSet == 1)
               {
                   for(int i =0; i < (int)param.m_selectedData.m_SampleIndexTest.size();i++)
                   {
                      valueXConcentrationTest.push_back(2 * param.m_selectedData.m_SampleIndexTest[i] + 1);
                      valueXConcentrationTest1.push_back(param.m_selectedData.m_SampleIndexTest[i]);
                   }
                   for(int i =0; i < (int)param.m_selectedData.m_SampleIndexCalib.size();i++)
                   {
                      valueXConcentrationValidation.push_back(2 * param.m_selectedData.m_SampleIndexCalib[i]);
                      valueXConcentrationValidation1.push_back(param.m_selectedData.m_SampleIndexCalib[i]);
                   }
               }
               else if(param.m_currentSet == 0)
               {
                   for(int i =0; i < (int)param.m_selectedData.m_SampleIndexTest.size();i++)
                   {
                      valueXConcentrationValidation.push_back(2 * param.m_selectedData.m_SampleIndexTest[i] + 1);
                   }
                   for(int i =0; i < (int)param.m_selectedData.m_SampleIndexCalib.size();i++)
                   {
                     valueXConcentrationTest.push_back(2 * param.m_selectedData.m_SampleIndexCalib[i]);
                   }
               }
               int len = max((int)validation.m_CrossValidation.size(),(int)prediction.m_CrossValidation.size());

               std::set_union
               (

                        valueXConcentrationValidation.begin(),valueXConcentrationValidation.end(),
                        valueXConcentrationTest.begin(),valueXConcentrationTest.end(),
                        back_inserter(sampleValidationX)
               );

               //sampleX = vector<double>(sampleValidationX[sampleValidationX.size() - 1] - sampleValidationX[0],0.0);
               for(int i = sampleValidationX[0];i < sampleValidationX[sampleValidationX.size() - 1] + 1;i++)
               {
                   sampleX.push_back(i);
               }

               a = "[";
               b = "[";

               for(int i=0;i < len;i++)
               {
                   if(i < (int)validation.m_CrossValidation.size())
                   {
                       A1 = validation.m_CrossValidation[i].ModelCrossValidation.RecreatedConcentrations;

                       for(int j =0;j < (int)validation.m_CrossValidation[i].ModelCrossValidation.RecreatedConcentrations.n_rows;j++)
                       {
                              mat AA = validation.m_CrossValidation[i].ModelCrossValidation.RecreatedConcentrations.row(j);
                              A = (join_rows(A,AA));
                       }
                       C1 = validation.m_CrossValidation[i].ModelCrossValidation.OriginalConcentrations;

                       for(int j =0;j < (int)validation.m_CrossValidation[i].ModelCrossValidation.OriginalConcentrations.n_rows;j++)
                       {
                              mat CC = validation.m_CrossValidation[i].ModelCrossValidation.OriginalConcentrations.row(j);
                              C = (join_rows(C,CC));
                       }

                      a = a +  to_string(validation.m_CrossValidation[i].ModelCrossValidation.numberOfPCA + 1) + ",";
                      aa.push_back(i);
                      aa1.push_back(validation.m_CrossValidation[i].ModelCrossValidation.numberOfPCA + 1);
                   }

                   if(i < (int)prediction.m_CrossValidation.size())
                   {
                       B1 = prediction.m_CrossValidation[i].ModelCrossValidation.RecreatedConcentrations;

                       for(int j =0;j < (int)prediction.m_CrossValidation[i].ModelCrossValidation.RecreatedConcentrations.n_rows;j++)
                       {
                              mat BB = prediction.m_CrossValidation[i].ModelCrossValidation.RecreatedConcentrations.row(j);
                              B = (join_rows(B,BB));
                       }
                       D1 = prediction.m_CrossValidation[i].ModelCrossValidation.OriginalConcentrations;

                       for(int j =0;j < (int)prediction.m_CrossValidation[i].ModelCrossValidation.OriginalConcentrations.n_rows;j++)
                       {
                              mat DD = prediction.m_CrossValidation[i].ModelCrossValidation.OriginalConcentrations.row(j);
                              D = (join_rows(D,DD));
                       }

                       b = b +  to_string(prediction.m_CrossValidation[i].ModelCrossValidation.numberOfPCA + 1) +",";
                       bb.push_back(i);
                       bb1.push_back(prediction.m_CrossValidation[i].ModelCrossValidation.numberOfPCA + 1);
                       cout << endl;
                   }
               }
               a = a + "]";
               b = b + "]";

               mat EAC = join_cols(A,C);
               mat EBD = join_cols(B,D);

               E = mat(A.n_rows,(int)sampleX.size());
               E.zeros();

               for(int i = 0,j=0;i < (int)valueXConcentrationValidation.size() && j < (int)A.n_cols;i++,j++)
               {
                   E.col(valueXConcentrationValidation[i] - sampleX[0]) = A.col(j);
               }
               mat E1 = mat(A.n_rows,(int)sampleX.size());
               E1.zeros();
               for(int i = 0,j=0;i < (int)valueXConcentrationTest.size() && j < (int)B.n_cols;i++,j++)
               {
                   E1.col(valueXConcentrationTest[i] - sampleX[0]) = B.col(j);
               }

               vector<string> title =
               {
                   " Predicted Concentrations in Validated Model.",
                   " Predicted Concentrations in Predicted Model.",
                   " Predicted and Original Concentrations in Predicted  Model.",
                   " Validated and Original Concentrations in Validated Model.",
                   " Original Concentrations in Validated  Model.",
                   " Original Concentrations in Predicted Model."
               };

               string titleStart;
               if(param.m_currentSet == 1)
               {
                   titleStart = " Calibration Set : Number Of Samples = " + to_string((int)param.m_currentPopulationMatrix.n_rows) +
                                " Number Of Selected Variables = " + to_string((int)param.m_currentPopulationMatrix.n_cols) + " ";

               }
               else if(param.m_currentSet == 0)
               {
                   titleStart = " Testing  Set : Number Of Samples = " + to_string((int)param.m_testingPopulationMatrix.n_rows) +
                           " Number Of Selected Variables = " + to_string((int)param.m_testingPopulationMatrix.n_cols) + " ";
               }

               while(sampleValidationX.size() > E.n_cols)
               {
                   sampleValidationX.pop_back();
               }
               titles.push_back
                               (
                                          std::make_tuple<vector<int>,vector<double>,vector<string>>(
                                          {},{},
                                          {
                                             param.m_task_name,
                                             titleStart + title[0],
                                             "Number Of Sample\n" + a + " \n",
                                             "Concentration"
                                          })
                               );
               populationAndCorrection.push_back(pair<mat,mat>(rowvec(sampleX),E));
               titles.push_back
                               (
                                          std::make_tuple<vector<int>,vector<double>,vector<string>>(
                                          {},{},
                                          {
                                             param.m_task_name,
                                             titleStart + title[1],
                                             "Number Of Sample\n" + a + " \n",
                                             "Concentration"
                                          })
                               );
               populationAndCorrection.push_back(pair<mat,mat>(rowvec(sampleX),E1));

               titles.push_back
                               (
                                          std::make_tuple<vector<int>,vector<double>,vector<string>>(
                                          {},{},
                                          {
                                             param.m_task_name,
                                             titleStart + title[2],
                                             "Number Of Sample\n" + b + "\n",
                                             "Concentration"
                                          })
                               );


               populationAndCorrection.push_back(pair<mat,mat>(rowvec(valueXConcentrationTest1),EBD));
               titles.push_back
                               (
                                          std::make_tuple<vector<int>,vector<double>,vector<string>>(
                                          {},{},
                                          {
                                             param.m_task_name,
                                             titleStart + title[3],
                                             "Number Of Sample\n" + a + "\n",
                                             "Concentration"
                                          })
                               );
               populationAndCorrection.push_back(pair<mat,mat>(rowvec(valueXConcentrationValidation1),EAC));

               E = mat(C.n_rows,(int)sampleX.size());
               E.zeros();
               for(int i = 0,j=0;i < (int)valueXConcentrationValidation.size() && j < (int)C.n_cols;i++,j++)
               {
                   E.col(valueXConcentrationValidation[i] - sampleX[0]) = C.col(j);
               }
               E1 = mat(C.n_rows,(int)sampleX.size());
               E1.zeros();
               for(int i = 0,j=0;i < (int)valueXConcentrationTest.size() && j < (int)D.n_cols;i++,j++)
               {
                   E1.col(valueXConcentrationTest[i] - sampleX[0]) = D.col(j);
               }

               titles.push_back
                               (
                                          std::make_tuple<vector<int>,vector<double>,vector<string>>(
                                          {},{},
                                          {
                                             param.m_task_name,
                                             titleStart + title[4],
                                             "Number Of Sample\n"  + b + "\n",
                                             "Concentration"
                                          })
                               );
               populationAndCorrection.push_back(pair<mat,mat>(rowvec(sampleX),E));
               titles.push_back
                               (
                                          std::make_tuple<vector<int>,vector<double>,vector<string>>(
                                          {},{},
                                          {
                                             param.m_task_name,
                                             titleStart + title[5],
                                             "Number Of Sample\n"  + b + "\n",
                                             "Concentration"
                                          })
                               );
               populationAndCorrection.push_back(pair<mat,mat>(rowvec(sampleX),E1));
               DisplayPlots( populationAndCorrection,1,titles );
               populationAndCorrection.clear();
           }
} /* namespace NDUV */
