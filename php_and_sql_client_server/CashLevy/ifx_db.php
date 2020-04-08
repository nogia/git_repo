<?php
require("classes.php");
class IfxDB {

    public $conn;
    public $lastError;
    public $database = "cash@alpha25soc";
    public $username = "pubcash";
    public $password = "Pubcash";

    public function __construct($db=null, $uname=null, $pword=null) {
        if (!is_null($db)) $this->database = $db;
        if (!is_null($uname)) $this->username = $uname;
        if (!is_null($pword)) $this->password = $pword;
    }

    public function runQuery($query) {
        if ($this->conn)
            return ifx_query($query, $this->conn);   
        else
           return null;
    }
    public function getListOfRecords($query)
    {
      $rows=0;
      if($this->conn)
      {
         $queryResult= ifx_query($query,$this->conn);
        while($fetch = ifx_fetch_row($queryResult))
        {
            $arr[] = $fetch;
            $rows  = ifx_num_rows($queryResult);
        }
      }
       return $arr;
    }
      
    public function rows($query) {
      $rows=0;

      if($this->conn)
      {
         $queryResult= ifx_query($query,$this->conn);
        do
        {
            $fetch = ifx_fetch_row($queryResult);
            $rows  = ifx_num_rows($queryResult);
        }while($fetch);
      }
      return $rows;
    }
    public function columns($query) {
      $cols=0;

      if($this->conn)
      {
        $queryResult= ifx_query($query,$this->conn);
        do
        {
            $fetch = ifx_fetch_row($queryResult);
            $colss  =  ifx_num_fields($queryResult);
        }while($fetch);
      }
      return $colss;
    }
   //tested
    public function execScalar($query) {
       
        if ($this->conn)
        {
            $result = ifx_query($query, $this->conn);
            $colss  =  ifx_num_fields($result);
           //ifx_htmltbl_result( $queryResult,"border=\"1\"");
           while($fetch = ifx_fetch_row($result))
           {

               $arr[] = $fetch;
               $rows  = ifx_num_rows($$result);
               //$fetch = ifx_fetch_row($queryResult);
            }
        }
         //ifx_htmltbl_result( $arr,"border=\"1\"");
        return $arr;
    }

    public function execNonQuery($query) {
        $ret = 0;
        if ($this->conn)
        {
            $res = ifx_query($query, $this->conn);
            $ret = ifx_affected_rows($res);
            ifx_free_result($res);
        } else {
            $this->lastError = "No database connection.";
        }
        return $ret;
    }
   
    //tested
       public function getRecordCount($table, $wherecond) {
        $ret = 0;
        $q="SELECT     COUNT(*) AS total FROM  "  .  " " . $table . " " . $wherecond;
        if ($this->conn)
        {
            $this->execScalar($q,&$ret);
             
        } else {
            $this->lastError = "No database connection.";
        }
        return $ret;
    }
    public function sanitizeText($val) {
        return str_replace("'", "''", str_replace("%", "%%", $val));
    }
    //tested
    public function connectDb() {
        $this->conn = ifx_connect($this->database, $this->username, $this->password);
        if ($this->conn == false)
        {
            $this->lastError = ifx_errormsg($this->conn);
            return false;
        } else {
            return true;
        }
    }
   //tested
    public function reconnectDb() {
        if($this)
          $this->dispose();
       return  $this->connectDb();
    }
    //tested
    public function dispose() {
        ifx_close($this->conn);
        $this->conn = null;
    }
}
class IfxQueryResult {
    public $queryResult;
    public function __construct($query_result) {
        $this->queryResult = $query_result;
      
    }
    public function read() {
        if ($this->queryResult)
        {
            return ifx_fetch_row($this->queryResult, "NEXT");
        }
        return false;
    }
    public function advance($offset) {
        while ($offset > 0)
        {
            $this->read();
            $offset--;
        }
    }
    public function dispose($ptr) {
        ifx_free_result($ptr);
    }
}

?>