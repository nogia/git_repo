<?php
/* 
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
//Array of the required searches
 //$SearchData[0]->searchParametersValues[0] = $_GET[$SearchData[0]->searchParameters];
   //echo $SearchData[0]->searchParametersValues[0];
$SearchData = Array();
$MAX_SIZE =501;
// Defenition required to serach Levy by Case
$SearchData[0] = new StdClass();
$SearchData[0]->root = 'casedata';
$SearchData[0]->id = 0;
$SearchData[0]->name = 'by_case';
$SearchData[0]->search_parameters = Array('casenum');
$SearchData[0]->db_names = Array('informix');
$SearchData[0]->table_names = Array('cislevextcnt','cislevhstcnt');
$SearchData[0]->fieldnames = Array('casenum','levy');

$SearchData[0]->search_parameter_values = Array();
//$SearchData[0]->search_parameter_values = Array("01004741CFW");
$SearchData[0]->data = Array();
$SearchData[0]->defenition = Array();
$SearchData[0]->json_array = null;
$SearchData[0]->number_of_rows = 0;
$SearchData[0]->sql_array = Array("SELECT  DISTINCT
                                        informix.cislevextcnt.casenum,
                                        informix.cislevhstcnt.levy
                          FROM
                                        informix.cislevhstcnt,
                                        informix.cislevextcnt
                          WHERE         informix.cislevhstcnt.levy = informix.cislevextcnt.levy AND (informix.cislevextcnt.casenum = '",$SearchData[0]->search_parameter_values[0] ,"')");
$SearchData[0]->sql_string = "";


// LEVY MASTER parameter selected levy = '3579541'
$SearchData[1] = new StdClass();
$SearchData[1]->root = 'levymasterdata';
$SearchData[1]->id = 1;
$SearchData[1]->name = 'levydata';
$SearchData[1]->search_parameters = Array('levymaster');
$SearchData[1]->db_names = Array('informix');
$SearchData[1]->table_names = Array('cislevextcnt','cislevhstcnt');
$SearchData[1]->fieldnames = Array('receipt','casenum','levy','name','payor','fhs_date','valid','amount','totaldue','totalpaid','balancedue');

$SearchData[1]->search_parameter_values = Array();
//$SearchData[1]->search_parameter_values = Array("3579541");  // to test set the desired parameter and uncomment
$SearchData[1]->data = Array();
$SearchData[1]->defenition = Array();
$SearchData[1]->json_array = null;
$SearchData[1]->number_of_rows = 0;
$SearchData[1]->sql_array = Array("SELECT
                                                        informix.cislevextcnt.casenum  ,
                                                        informix.cislevextcnt.count1,
                                                        informix.cislevextcnt.division,
                                                        informix.cislevextcnt.agency,
                                                        informix.cislevextcnt.ref_no,
                                                        informix.cislevextcnt.levy,
                                                        informix.cislevextcnt.outstanding_rcpt,
                                                        informix.cislevextcnt.department,
                                                        informix.cislevextcnt.name,
                                                        informix.cislevextcnt.addr1,
                                                        informix.cislevextcnt.addr2,
                                                        informix.cislevextcnt.payor,
                                                        informix.cislevextcnt.payor_addr1,
                                                        informix.cislevextcnt.payor_addr2,
                                                        informix.cislevextcnt.payor_addr3,
                                                        informix.cislevextcnt.payor_spn,
                                                        informix.cislevextcnt.assess_dt,
                                                        informix.cislevextcnt.status,
                                                        informix.cislevextcnt.stat_dt,
                                                        informix.cislevextcnt.tot_fin,
                                                        informix.cislevextcnt.fin_pd,
                                                        informix.cislevextcnt.fin_idx,
                                                        informix.cislevextcnt.lev_stat,
                                                        informix.cislevextcnt.disp_dt,
                                                        informix.cislevextcnt.note_sent,
                                                        informix.cislevextcnt.source
                                 FROM
                                            informix.cislevextcnt
                                 WHERE     (levy = '",
                                            $SearchData[1]->search_parameter_values[0] ,
                                             "')");
$SearchData[1]->sql_string = "";

//SELECT CASES WHEN NAME is SELECTED
$SearchData[2] = new StdClass();
$SearchData[2]->root = 'namedata';
$SearchData[2]->id = 2;
$SearchData[2]->name = 'namedata';
$SearchData[2]->search_parameters = Array('name');
$SearchData[2]->db_names = Array('informix');
$SearchData[2]->table_names = Array('cislevextcnt');
$SearchData[2]->fieldnames = Array('name','casenum','levy');

$SearchData[2]->search_parameter_values = Array();
//$SearchData[2]->search_parameter_values = Array("OLSON WINDIE M");
$SearchData[2]->data = Array();
$SearchData[2]->defenition = Array();
$SearchData[2]->json_array = null;
$SearchData[2]->number_of_rows = 0;
$SearchData[2]->sql_array = Array("SELECT
                                            casenum, levy, name
                                            FROM         informix.cislevextcnt
                                            WHERE     (name = '",
                                            $SearchData[2]->search_parameter_values[0] ,
                                            "')");
$SearchData[2]->sql_string = "";

//Levy accounts when levy is selected
$SearchData[3] = new StdClass();
$SearchData[3]->root = 'levyaccounts';
$SearchData[3]->id = 3;
$SearchData[3]->name = 'levyaccounts';
$SearchData[3]->search_parameters = Array('levyaccounts');
$SearchData[3]->db_names = Array('informix');
$SearchData[3]->table_names = Array('cislevarrcnt');
$SearchData[3]->fieldnames = Array( 'casenum', 'count1', 'division', 'agency', 'levynum', 'arr_idx', 'screen', 'level', 'fund', 'objt', 'org_amt', 'new_amt', 'pd_amt', 'source');

$SearchData[3]->search_parameter_values = Array();
//$SearchData[3]->search_parameter_values = Array("3579541");
$SearchData[3]->data = Array();
$SearchData[3]->defenition = Array();
$SearchData[3]->json_array = null;
$SearchData[3]->number_of_rows = 0;
$SearchData[3]->sql_array = Array("SELECT
                                           casenum, count1, division, agency, levynum, arr_idx, screen, level, fund, objt, org_amt, new_amt, pd_amt, source


                                   FROM         informix.cislevarrcnt
                                   WHERE     (levynum = '",
                                   $SearchData[3]->search_parameter_values[0] ,
                                   "')");
$SearchData[3]->sql_string = "";

//Levy History when levy is selected parameter levy = '3579541'
$SearchData[4] = new StdClass();
$SearchData[4]->root = 'levyhistorydata';
$SearchData[4]->id = 4;
$SearchData[4]->name = 'levyhistorydata';
$SearchData[4]->search_parameters = Array('levyhistory');
$SearchData[4]->db_names = Array('informix');
$SearchData[4]->table_names = Array('cislevhstcnt');
$SearchData[4]->fieldnames = Array('levy', 'receipt', 'valid', 'fhs_date', 'amount', 'source');
$SearchData[4]->search_parameter_values = Array();
//$SearchData[4]->search_parameter_values = Array("3579541");
$SearchData[4]->data = Array();
$SearchData[4]->defenition = Array();
$SearchData[4]->json_array = null;
$SearchData[4]->number_of_rows = 0;
$SearchData[4]->sql_array = Array("SELECT
                                             levy, receipt, valid, fhs_date, amount, source
                                  FROM
                                             informix.cislevhstcnt
                                  WHERE     (levy = '",
                                  $SearchData[4]->search_parameter_values[0] ,
                                  "')");
$SearchData[4]->sql_string = "";
//Receipt detail when levy is selected

$SearchData[5] = new StdClass();
$SearchData[5]->root = 'levydetaildata';
$SearchData[5]->id = 5;
$SearchData[5]->name = 'levydetail';
$SearchData[5]->search_parameters = Array('levydetail');
$SearchData[5]->db_names = Array('informix');
$SearchData[5]->table_names = Array('dlydet');
$SearchData[5]->fieldnames = Array( 'recpt', 'casenum', 'count1', 'scrn', 'fund', 'objt', 'amount', 'dat_src');

$SearchData[5]->search_parameter_values = Array();
//$SearchData[5]->search_parameter_values = Array("3579541");
$SearchData[5]->data = Array();
$SearchData[5]->defenition = Array();
$SearchData[5]->json_array = null;
$SearchData[5]->number_of_rows = 0;
$SearchData[5]->sql_array = Array("SELECT     
                                            recpt, casenum, count1, scrn, fund, objt, amount, dat_src
                                   FROM         informix.dlydet
                                   WHERE     (recpt IN
                                                (SELECT     receipt
                                                 FROM          informix.cislevhstcnt
                                                 WHERE      (levy = '",
                                                            $SearchData[5]->search_parameter_values[0],
                                                            "')))");

$SearchData[5]->sql_string = "";


//////  Levy History  parameter levy

$SearchData[7] = new StdClass();
$SearchData[7]->root = 'receipthistory';
$SearchData[7]->id = 7;
$SearchData[7]->name = 'receipthistory';
$SearchData[7]->search_parameters = Array('levyhistoryfinal');
$SearchData[7]->db_names = Array('informix');
$SearchData[7]->table_names = Array('cislevextcnt','cislevhstcnt');
$SearchData[7]->fieldnames = Array('levy','receipt','valid','fhs_date','amount','source');

$SearchData[7]->search_parameter_values = Array();
//$SearchData[7]->search_parameter_values = Array("3579541");

$SearchData[7]->data= Array();
$SearchData[7]->defenition = Array();
$SearchData[7]->json_array = null;
$SearchData[7]->number_of_rows = 0;
$SearchData[7]->sql_array = Array("SELECT
                                            levy,
                                            receipt,
                                            valid,
                                            fhs_date,
                                            amount,
                                            source
                                    FROM    cislevhstcnt
                                    WHERE   (levy = '",
                                             $SearchData[7]->search_parameter_values[0],
                                              "')");


$SearchData[7]->sql_string = "";
// Receipt Detail Section
//  parameter levy

$SearchData[8] = new StdClass();
$SearchData[8]->root = 'receiptdetailfinal';
$SearchData[8]->id = 8;
$SearchData[8]->name = 'receiptdetailfinal';
$SearchData[8]->search_parameters = Array('levydetailfinal');
$SearchData[8]->db_names = Array('informix');
$SearchData[8]->table_names = Array('dlydet');
$SearchData[8]->fieldnames = Array('recpt', 'casenum', 'count1', 'scrn', 'fund', 'objt', 'amount', 'dat_src');

$SearchData[8]->search_parameter_values = Array();
//$SearchData[8]->search_parameter_values = Array("3579542");

$SearchData[8]->data= Array();
$SearchData[8]->defenition = Array();
$SearchData[8]->json_array = null;
$SearchData[8]->number_of_rows = 0;
$SearchData[8]->sql_array = Array("SELECT     recpt, casenum, count1, scrn, fund, objt, amount, dat_src
                                   FROM         informix.dlydet
                                   WHERE     recpt IN
                                   ( SELECT     receipt
                                    FROM         informix.cislevhstcnt
                                    WHERE     (levy = '",
                                    $SearchData[8]->search_parameter_values[0],
                                              "'))");


$SearchData[8]->sql_string = "";
//
//search classes by 2 parameters  -> two way search
//Defenition required to serach Levy by  case after the levy has been selected
$SearchData[100] = new StdClass();
$SearchData[100]->root = 'casenumlevydata';
$SearchData[100]->id = 100;
$SearchData[100]->name = 'casenumlevydata';
$SearchData[100]->search_parameters = Array('nameid100','casenumid100');
$SearchData[100]->db_names = Array('informix');
$SearchData[100]->table_names = Array('cislevextcnt');
$SearchData[100]->fieldnames = Array('levy','casenum','name');

$SearchData[100]->search_parameter_values = Array();
//$SearchData[100]->search_parameter_values = Array("OLSON WINDIE M","01004741CFW" );
$SearchData[100]->data = Array();
$SearchData[100]->defenition = Array();
$SearchData[100]->json_array = null;
$SearchData[100]->number_of_rows = 0;
$SearchData[100]->sql_array = Array("SELECT
                                            levy, casenum,name
                                            FROM         informix.cislevextcnt
                                            WHERE     (name = '",
                                            $SearchData[100]->search_parameter_values[0],
                                            "') AND (casenum = '",
                                            $SearchData[100]->search_parameter_values[1],
                                            "')");
$SearchData[100]->sql_string = "";

//Defenition required to earch Levy by name after the levy selected

$SearchData[101] = new StdClass();
$SearchData[101]->root = 'namehistorydata';
$SearchData[101]->id = 101;
$SearchData[101]->name = 'namehistorydata';
$SearchData[101]->search_parameters = Array('levynumid101','nameid101');
$SearchData[101]->db_names = Array('informix');
$SearchData[101]->table_names = Array('cislevextcnt','cislevhstcnt');
$SearchData[101]->fieldnames = Array('levy','receipt','valid','fhs_date','amount','source');

$SearchData[101]->search_parameter_values = Array();
//$SearchData[101]->search_parameter_values = Array("3576355","FRYREAR JEFFREY" );
$SearchData[101]->data = Array();
$SearchData[101]->defenition = Array();
$SearchData[101]->json_array = null;
$SearchData[101]->number_of_rows = 0;
$SearchData[101]->sql_array = Array("SELECT
                                                informix.cislevhstcnt.levy, informix.cislevhstcnt.receipt, informix.cislevhstcnt.valid, informix.cislevhstcnt.fhs_date, informix.cislevhstcnt.amount,
                                                informix.cislevhstcnt.source
                                     FROM       informix.cislevhstcnt, informix.cislevextcnt
                                    WHERE       informix.cislevhstcnt.levy = informix.cislevextcnt.levy  AND
                                                (informix.cislevhstcnt.levy = '",
                                                $SearchData[101]->search_parameter_values[0],
                                                "') AND (informix.cislevextcnt.name = '",
                                                $SearchData[101]->search_parameter_values[1],
                                                "')");
$SearchData[101]->sql_string = "";

//Conversion Receipt Distribution query 1 -> parameters: {receipt range : receiptstart, receiptend}





//FINAL PAGE MASTER RECORD for receipt   2 parameters used to show master record -> receipt = '3579545',casenum = '01004741CFW'
$SearchData[104] = new StdClass();
$SearchData[104]->root = 'receiptmaster';
$SearchData[104]->id = 104;
$SearchData[104]->name = 'receiptmaster';
$SearchData[104]->search_parameters = Array('casenumbermasterfinal','levymasterfinal');
$SearchData[104]->db_names = Array('informix');
$SearchData[104]->table_names = Array('cislevextcnt','cislevhstcnt');
$SearchData[104]->fieldnames = Array('amount','count1','division','agency','ref_no','levy','outstanding_rcpt','department','name','addr1','addr2','payor','payor_addr1','payor_addr2','payor_addr3','payor_spn','assess_dt','status','stat_dt','tot_fin','fin_pd','fin_idx','lev_stat','disp_dt','note_sent','source');

$SearchData[104]->search_parameter_values = Array();
//$SearchData[104]->search_parameter_values = Array("01004741CFW","3579541",);

$SearchData[104]->data= Array();
$SearchData[104]->defenition = Array();
$SearchData[104]->json_array = null;
$SearchData[104]->number_of_rows = 0;
$SearchData[104]->sql_array = Array("SELECT 
                                                        informix.cislevextcnt.casenum,
                                                        informix.cislevextcnt.count1,
                                                        informix.cislevextcnt.division,
                                                        informix.cislevextcnt.agency,
                                                        informix.cislevextcnt.ref_no,
                                                        informix.cislevextcnt.levy,
                                                        informix.cislevextcnt.outstanding_rcpt,
                                                        informix.cislevextcnt.department,
                                                        informix.cislevextcnt.name,
                                                        informix.cislevextcnt.addr1,
                                                        informix.cislevextcnt.addr2,
                                                        informix.cislevextcnt.payor,
                                                        informix.cislevextcnt.payor_addr1,
                                                        informix.cislevextcnt.payor_addr2,
                                                        informix.cislevextcnt.payor_addr3,
                                                        informix.cislevextcnt.payor_spn,
                                                        informix.cislevextcnt.assess_dt,
                                                        informix.cislevextcnt.status,
                                                        informix.cislevextcnt.stat_dt,
                                                        informix.cislevextcnt.tot_fin,
                                                        informix.cislevextcnt.fin_pd,
                                                        informix.cislevextcnt.fin_idx,
                                                        informix.cislevextcnt.lev_stat,
                                                        informix.cislevextcnt.disp_dt,
                                                        informix.cislevextcnt.note_sent,
                                                        informix.cislevextcnt.source
                                        FROM
                                                        informix.cislevextcnt
                                                        
                                       WHERE
                                                        (casenum = '",
                                                        $SearchData[104]->search_parameter_values[0],
                                                                                                "') AND (levy = '",
                                                        $SearchData[104]->search_parameter_values[1],
                                                                                                "')");
$SearchData[104]->sql_string = "";

//////  Receipt Accounts

$SearchData[105] = new StdClass();
$SearchData[105]->root = 'receiptaccounts';
$SearchData[105]->id = 105;
$SearchData[105]->name = 'receipthistory';
$SearchData[105]->search_parameters = Array('caseaccountfinal','levyaccountsfinal');
$SearchData[105]->db_names = Array('informix');
$SearchData[105]->table_names = Array('cislevextcnt','cislevhstcnt');
$SearchData[105]->fieldnames = Array('casenum', 'count1', 'division', 'agency', 'levynum', 'arr_idx', 'screen', 'level', 'fund', 'objt', 'org_amt', 'new_amt', 'pd_amt', 'source');

$SearchData[105]->search_parameter_values = Array();
//$SearchData[105]->search_parameter_values = Array("01004741CFW","3579541");

$SearchData[105]->data= Array();
$SearchData[105]->defenition = Array();
$SearchData[105]->json_array = null;
$SearchData[105]->number_of_rows = 0;
$SearchData[105]->sql_array = Array("SELECT
                                              casenum, count1,division, agency, levynum, arr_idx, screen, level, fund, objt, org_amt, new_amt, pd_amt, source
                                     FROM     informix.cislevarrcnt
                                     WHERE    (casenum = '",
                                     $SearchData[105]->search_parameter_values[0],
                                     "') AND (levynum = '",
                                     $SearchData[105]->search_parameter_values[1],
                                     "')");
$SearchData[105]->sql_string = "";

// Conversion Receipt Distribution query 2 -> parameters { {receipt range: receiptstart,receiptend},accountnumber}
// 3 parameters queryes start from 200

$SearchData[200] = new StdClass();
$SearchData[200]->root = 'namemaster';
$SearchData[200]->id = 200;
$SearchData[200]->name = 'namemaster';
$SearchData[200]->search_parameters = Array('nameid200','casenumid200','levyid200');
$SearchData[200]->db_names = Array('informix');
$SearchData[200]->table_names = Array('cislevextcnt');
$SearchData[200]->fieldnames = Array('amount','count1','division','agency','ref_no','levy','outstanding_rcpt','department','name','addr1','addr2','payor','payor_addr1','payor_addr2','payor_addr3','payor_spn','assess_dt','status','stat_dt','tot_fin','fin_pd','fin_idx','lev_stat','disp_dt','note_sent','source');
$SearchData[200]->search_parameter_values = Array();
//$SearchData[200]->search_parameter_values = Array("OLSON WINDIE M","01004741CFW","3579542");
$SearchData[200]->data=Array();
$SearchData[200]->defenition = Array();
$SearchData[200]->json_array = null;
$SearchData[200]->number_of_rows = 0;
$SearchData[200]->sql_array = Array("SELECT
                                            casenum, count1, division, agency, ref_no, levy, outstanding_rcpt, department, name, addr1, addr2, payor, payor_addr1, payor_addr2, payor_addr3,
                                            payor_spn, assess_dt, status, stat_dt, tot_fin, fin_pd, fin_idx, lev_stat, disp_dt, note_sent, source
                                    FROM         informix.cislevextcnt
                                    WHERE     (name = '",
                                               $SearchData[200]->search_parameter_values[0] ,
                                                 "') AND (casenum = '",
                                                 $SearchData[200]->search_parameter_values[1],
                                                 "') AND (levy = '",
                                                 $SearchData[200]->search_parameter_values[2],
                                                 "')");
$SearchData[200]->sql_string = "";
//NAme detail data
$SearchData[201] = new StdClass();
$SearchData[201]->root = 'namedetaildata';
$SearchData[201]->id = 201;
$SearchData[201]->name = 'namedetaildata';
$SearchData[201]->search_parameters = Array('casenumid201','levyid201','nameid201');
$SearchData[201]->db_names = Array('informix');
$SearchData[201]->table_names = Array('dlydet');
$SearchData[201]->fieldnames = Array('recpt', 'casenum', 'count1', 'scrn', 'fund', 'objt', 'amount', 'dat_src');

$SearchData[201]->search_parameter_values = Array();
//$SearchData[201]->search_parameter_values = Array("01004741CFW","3579542","OLSON WINDIE M" );
$SearchData[201]->data = Array();
$SearchData[201]->defenition = Array();
$SearchData[201]->json_array = null;
$SearchData[201]->number_of_rows = 0;
$SearchData[201]->sql_array = Array("SELECT
                                                recpt, casenum, count1, scrn, fund, objt, amount, dat_src
                                     FROM       informix.dlydet
                                     WHERE     (recpt IN
                                                        (SELECT     informix.cislevhstcnt.receipt
                                                         FROM       informix.cislevhstcnt, informix.cislevextcnt
                                                         WHERE      informix.cislevhstcnt.levy = informix.cislevextcnt.levy AND (informix.cislevextcnt.casenum = '",
                                                                    $SearchData[201]->search_parameter_values[0],
                                                                    " ')AND (informix.cislevhstcnt.levy = '",
                                                                    $SearchData[201]->search_parameter_values[1],
                                                                    "') AND (informix.cislevextcnt.name = '",
                                                                    $SearchData[201]->search_parameter_values[2],
                                                                     "')))");

$SearchData[201]->sql_string = "";

// sql with 4 parameteres
/*$SearchData[300] = new StdClass();
$SearchData[300]->root = 'receiptaccount';
$SearchData[300]->id = 300;
$SearchData[300]->name = 'receiptaccount';
$SearchData[300]->search_parameters = Array('receiptaccountfinal','levyaccountfinal','casenumaccountfinal','objtaccountfinal');
$SearchData[300]->db_names = Array('informix');
$SearchData[300]->table_names = Array('dlydet','cislevarrcnt','cislevextcnt');
$SearchData[300]->fieldnames = Array('casenum','count1','division','agency','levynum','arr_idx','screen','level','fund','objt','org_amt','new_amt','pd_amt','source');

$SearchData[300]->search_parameter_values = Array();
//$SearchData[300]->search_parameter_values = Array("3579545","3579541","01004741CFW","208228");

$SearchData[300]->data=Array();
$SearchData[300]->defenition = Array();
$SearchData[300]->json_array = null;
$SearchData[300]->number_of_rows = 0;
$SearchData[300]->sql_array = Array("SELECT
                                            informix.dlydet.casenum,
                                            informix.dlydet.count1,
                                            informix.cislevarrcnt.division,
                                            informix.cislevarrcnt.agency,
                                            informix.cislevarrcnt.levynum,
                                            informix.cislevarrcnt.arr_idx,
                                            informix.cislevarrcnt.screen,
                                            informix.cislevarrcnt.level,
                                            informix.dlydet.fund, informix.dlydet.objt,
                                            informix.cislevarrcnt.org_amt,
                                            informix.cislevarrcnt.new_amt,
                                            informix.cislevarrcnt.pd_amt,
                                            informix.cislevarrcnt.source
                                    FROM
                                            informix.dlydet,
                                            informix.cislevarrcnt,
                                            informix.cislevextcnt
                                    WHERE
                                            informix.dlydet.objt = informix.cislevarrcnt.objt AND
                                            informix.cislevarrcnt.levynum = informix.cislevextcnt.levy AND
                                            informix.dlydet.casenum = informix.cislevextcnt.casenum AND (informix.dlydet.recpt = '",
                                                 $SearchData[300]->search_parameter_values[0] ,
                                                 "') AND (informix.dlydet.recpt IN
                                                                                (SELECT
                                                                                               receipt
                                                                                 FROM          informix.cislevhstcnt cislevhstcnt
                                                                                 WHERE          (levy = '",
                                                                                                $SearchData[300]->search_parameter_values[1],
                                                                                                "') AND (levy IN
                                                                                                        (SELECT DISTINCT
                                                                                                                            cislevhstcnt.levy
                                                                                                         FROM
                                                                                                                            informix.cislevhstcnt cislevhstcnt,
                                                                                                                            informix.cislevextcnt cislevextcnt_1
                                                                                                        WHERE
                                                                                                                            cislevhstcnt.levy = cislevextcnt_1.levy AND (cislevextcnt_1.casenum = '",
                                                                                                                            $SearchData[300]->search_parameter_values[2],
                                                                                                                            "'))))) AND (informix.dlydet.objt = '",
                                                                                                                            $SearchData[300]->search_parameter_values[3],
                                                                                                                            "')");
$SearchData[300]->sql_string = "";*/



?>
