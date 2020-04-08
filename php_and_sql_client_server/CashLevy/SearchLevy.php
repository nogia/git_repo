<?php

   require("ifx_db.php");
   require("classes.php");

        $db = new IfxDB();
        $x=$db->connectDb();
  
        $storeLevy = null;
        $queryID  = -1;
        
       for($i=0;$i<$MAX_SIZE;$i++)
        {
            switch($i)
            {
                //each case represent the single query that has to be run to get the result 
                //to add more queries go into classes.php and add new query
                //to add query that receives one parameter add the query as shown in cases 0-8
                //to add query that receives 2 parameters add the query as shown in cases 100 - 105
                //to add query that receives 3 parameters add the query as shown in cases 200,201
                //after query created in classes.php add case to this file 
                //$SearchData[N]->search_parameters must be different for each defined case
                //to test query uncomment $SearchData[N]->search_parameter_values = Array(...   ...); in classes.php
                //   comment:  if($_GET[$SearchData[$i]->search_parameters[$k]])                        in SearchLevy.php
                //   comment             $SearchData[$i]->search_parameter_values[$k] = $_GET[$SearchData[$i]->search_parameters[$k]];  in SearchLevy.php
                //   uncomment      echo $SearchData[$i]->search_parameter_values[$k]. "<br />";  in SearchLevy.php
                //set the parameters array and run the query
                //
                //to set the path to run the php file :
                //run->set project configurations -> customize ->
                //in Project URL set the path, in this case the path = http://localhost:8080/CashLevy/
                //in Index File set the file name to run, in this case SearchLevy.php
                //one parameter cases
                case 0:
                case 1:
                case 2:
                case 3:
                case 4:
                case 5:
                case 7:
                case 8:
                //two parameter  cases
                case 100:
                case 101:
                case 104:
                case 105:
                //three parameter cases
                case 200:
                case 201:
              
                     $count =1;
                      for($k=0 ;$k < sizeof($SearchData[$i]->search_parameters);$k++)
                      {
                         if($_GET[$SearchData[$i]->search_parameters[$k]])                                                      //to test comment
                                 $SearchData[$i]->search_parameter_values[$k] = $_GET[$SearchData[$i]->search_parameters[$k]];  // to test comment
                          //echo $SearchData[$i]->search_parameter_values[$k]. "<br />";  //to test uncomment
                      }
                     //echo sizeof($SearchData[$i]->search_parameter_values) . "     " . $countvaluesreceive. "<br />";
                     for($j=0 ;$j < sizeof($SearchData[$i]->search_parameter_values);$j++)
                     {
                        //if($SearchData[$i]->sql_array[$count])
                            $SearchData[$i]->sql_array[$count]= $SearchData[$i]->search_parameter_values[$j];
                        $count = $count + 2;
                     }
                     //echo " S=   " . sizeof($SearchData[$i]->search_parameter_values) . "    " . sizeof($SearchData[$i]->search_parameters) . "<br />";
                     //echo $SearchData[$i]->search_parameter_values[j];
                     if(     sizeof($SearchData[$i]->search_parameter_values) == sizeof($SearchData[$i]->search_parameters)   )
                      {
                        for($j=0;$j<sizeof($SearchData[$i]->sql_array);$j++)
                            $SearchData[$i]->sql_string = $SearchData[$i]->sql_string . $SearchData[$i]->sql_array[$j];
                       //echo $SearchData[$i]->sql_string;

                        $SearchData[$i]->number_of_rows = $db->rows($SearchData[$i]->sql_string);
                        //echo "r=" . $SearchData[$i]->number_of_rows;
                        $SearchData[$i]->data =$db->getListOfRecords($SearchData[$i]->sql_string);
                        $SearchData[$i]->defenition = Array(id => $SearchData[$i]->id,root => $SearchData[$i]->root,name => $SearchData[$i]->name,fieldnames => $SearchData[$i]->fieldnames,data => $SearchData[$i]->data);
                        $storeLevy = $SearchData[$i]->defenition;
                        //echo "i=" . $i;
                        $queryexecuted = true;
                        $SearchData[i]->search_parameter_values = null;
                      }
                    break;
            };  
        }
        $createData = Array(levy_data => $storeLevy);
        $outputLevyJSON = json_encode($createData);
        echo $outputLevyJSON;
?>
