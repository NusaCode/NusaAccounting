<?php
//--Created By : Dimas Ardi N
//--Created On : July 2013

userelation("atkManyToOneTreeRelation");

class coa_org extends atkTreeNode
{
  var $_module  = "quick_setup";
  var $_node    = "coa_org";
  var $_table   = "coa";


    function coa_org()
    {
      $this->atkTreeNode($this->_node, NF_ADD_LINK | NF_MRA | NF_IMPORT | NF_LOCK | NF_TRACK_CHANGES | NF_IMPORT);
  
      $action = array("genCoaStandart");
      $this->addAllowedAction($action); 
      $this->add(new atkAttribute("coa_code", AF_OBLIGATORY | AF_PRIMARY));
    
      $user = getUser();
      $coa_par = $this->add(new atkManyToOneTreeRelation("coa_parent", "quick_setup.coa_org", AF_PARENT | AF_CASCADE_DELETE ));

      $this->add(new atkAttribute("coa_name"));

      $this->add(new atkListAttribute("coa_jenis", array("Asset", "Liabilities", "Owner Equities", "Revenue", "COGS", "Expense"), array("a", "l", "o", "r", "c", "e"),  AF_LIST_NO_NULL_ITEM | AF_HIDE_LIST));

      $this->add(new atkListAttribute("balance",array("Debet","Kredit"), array("0","1"),  AF_LIST_NO_NULL_ITEM | AF_HIDE_LIST));   

      $this->add(new atkCurrencyAttribute("opening_balance"));

      $this->add(new atkDateAttribute("date_ob",  "Y M d", "Y M d", 0, 0, AF_HIDE_LIST, 30));      

      $this->add(new atkTextAttribute("desc", AF_HIDE_LIST));

      $this->add(new atkdummyattribute("jarak_atas","<br>", AF_HIDE_LIST));

      $this->add(new atkdummyattribute("garis","<hr>", AF_HIDE_LIST));

      $this->add(new atkCreatedByAttribute("created_by", AF_HIDE_LIST));

      $this->add(new atkCreateStampAttribute("created_on", AF_HIDE_LIST)); 

      $this->add(new AtkUpdatedByAttribute("last_modified_by", AF_HIDE_LIST));

      $this->add(new atkUpdateStampAttribute("last_modified_on", AF_HIDE_LIST));


      $this->setOrder("coa_code");

      $db = atkGetDb();
      $existTable = $db->getrows("SHOW TABLES LIKE 'coa_".$user[employer_id]."'");

      if (!empty($existTable)) {
        $tabel = $this->_table."_".$user[employer_id];
      }else{
        $tabel = $this->_table;
      }
      
      $this->setTable($tabel);
    }

    function descriptor_def()
    {
      return "[coa_code] - [coa_name]";
    }

    public function descriptorFields() 
    {
         return array ("coa_code","coa_name");
    }

    function coa_code_validate(&$record, $mode){
      $db   = atkGetDb();
      $user = getUser();
      $code = $record['coa_code'];
      $org  = $record['id_org']['id'];
      $orgcode = $record['atkorgrec']['coa_code'];

      $getprim = $db->getrows("SELECT * FROM coa_".$user[employer_id]." WHERE coa_code = '$code'");
      $coa_code     = $getprim[0]['coa_code'];
      $organization = $getprim[0]['id_org'];

      if($coa_code == $code && $organization == $org && $mode == 'add'){
         atkTriggerError($record, $this->getAttribute('coa_code'), '"COA Exists"');
      }elseif($coa_code == $code && $organization == $org && $orgcode != $code && $mode == 'update' ){
        atkTriggerError($record, $this->getAttribute('coa_code'), '"COA Exists"');
      }
      return true;
    }

    function opening_balance_validate(&$record, $mode){
      $user = getUser();
      $op   = $record['opening_balance'];
      $date = $record['date_ob']['year'];
      $orgcode = $record['atkorgrec']['opening_balance'];

      if($op !== '' && $date == '' && $mode == 'add'){
          atkTriggerError($record, $this->getAttribute('date_ob'), '"Please insert Opening Balance Date"');
      }elseif($op !== '' && $date == '' && $orgcode != $op && $mode == 'update'){
          atkTriggerError($record, $this->getAttribute('date_ob'), '"Please insert Opening Balance Date"');        
      }return true;
    }
    
    /*added by Eros, 11 Oktober 2013*/
    function date_ob_validate(&$record, $mode){
        $db    = atkGetDb();    
        $user  = getUser();
        $id_org= $user['employer_id'];
        $month = $record['date_ob']['month'];
        $year  = $record['date_ob']['year'];
        $date_ob = strtotime($record['date_ob'][year]."-".$record['date_ob'][month]."-".$record['date_ob'][day]);
        
        if ((strlen($month) < 2)){
            $month = "0".$record['date_ob']['month'];
        }        
        
        $res = $db->getrows("SELECT a.status status FROM periode_month a, periode_year b WHERE a.id_year = b.id
                            AND b.year = '" . $year. "' AND b.id_org = ".$id_org." AND a.`month` = '" . $month. "'");
        $status = $res[0]['status'];
        
        $res2 = $db->getrows("SELECT MIN(trans_date) tr_d from journal where id_org = ".$id_org."");
        $tr_d = $res2[0]['tr_d'];
        $trans_date = strtotime($tr_d);
        
        if ($status != 1) {
            atkTriggerError($record, $this->getAttribute('date_ob'), 'Periode for this  opening balance is not yet opened!!');
        }elseif ($date_ob > $trans_date && $tr_d != '') {
            atkTriggerError($record, $this->getAttribute('date_ob'), 'Opening balance date must be smaller than / equal to minimum transaction date!!');
        }
        return true;
    }
    /*end*/

    function initial_values() {
        parent::initial_values();
        $user = getUser();
        $id_org = $user['employer_id'];

        $cur = '0.00';
        
        return array("id_org" => $id_org);
    }

    function AdminHeader(){
        $user = getUser();
        $db = atkGetDb();

        $url2= session_url("dispatch.php?atknodetype=quick_setup.coa_org&atkaction=genCoaStandart", SESSION_NESTED);
        
        $page = &$this->getPage();

        $page->register_scriptcode("function confirm_backCoaStd(value){
          if (confirm('Do you want to generate COA?')) {window.location.href=\"".$url2."\"} else { void('') }
        }");

        $b = "<span><a href='javascript:void(0);' onmouseover='window.status=\"hide link\";return true;' onclick='javascript:confirm_backCoaStd();'>  <input type='button' name='unposting' value='Generate COA'> </a></span> ";

        return $b;

      }


    function action_genCoaStandart(){
        $id_org     = $_REQUEST['idorgan'];
        $coacodes   = $_REQUEST['coacode'];
        $db         = atkGetDb();
        $user       = getUser();

        $created_by = $user[id];
        $created_on = date("Y-m-d H:i:s");

        //------------------------------------------------------------------------------------------------------------------------//
        //------action generate coa ke asal setelah di edit oleh user. (Select, Check Validate balance <> 0, delete, insert)------//
        //------------------------------------------------------------------------------------------------------------------------//

              $existTable = $db->getrows("SHOW TABLES LIKE 'coa_".$user[employer_id]."'");

              if (!empty($existTable)) { //--Check Table COA Organization ada

                $cuco = $db->getrows("SELECT COUNT(opening_balance) as opel FROM coa_".$user[employer_id]." WHERE opening_balance <> '0.00'");
                $open_bal = $cuco[0]['opel'];

                  if($open_bal == 0){ //--Check Opening Balance is value or null

                    $row = $db->getrows("SELECT a.`id_org`, b.`coa` FROM `journal` a, `transaction` b  
                                         WHERE a.`id_journal` = b.`id_journal` AND a.`id_org` = '$user[employer_id]' LIMIT 1");

                          $coa2    = $row[0]['coa'];
                          $id_org2 = $row[0]['id_org'];

                            if($id_org2 == null && $coa2 == null){ //--Check Journal Exists

                                $db->query("DROP TABLE coa_".$user[employer_id]."");

                                $db->query("CREATE TABLE coa_".$user[employer_id]." SELECT * FROM coa_master");

                                $db->query("ALTER TABLE coa_".$user[employer_id]." ADD created_by INT(11), ADD created_on DATETIME, ADD last_modified_by INT(11), ADD last_modified_on DATETIME");

                                $db->query("UPDATE coa_".$user[employer_id]." SET created_by = '$created_by', created_on = '$created_on'");
                                
                                $db->commit();
                                $this->redirect();
                              
                            }else{
                              $alert = "<script>alert('Cannot generate, because COA has been use for transaction');history.go(-1);</script>";
                              echo $alert;
                            }
                  }else{
                    $alert = "<script>alert('Cannot generate, because opening balance already exist for COA');history.go(-1);</script>";
                    echo $alert;
                  }
              }else{

                //---If COA Not Exists
                  
                    $db->query("CREATE TABLE coa_".$user[employer_id]." SELECT * FROM coa_master");

                    $db->query("ALTER TABLE coa_".$user[employer_id]." ADD created_by INT(11), ADD created_on DATETIME, ADD last_modified_by INT(11), ADD last_modified_on DATETIME");

                    $db->query("UPDATE coa_".$user[employer_id]." SET created_by = '$created_by', created_on = '$created_on'");

                  $db->commit();
                $this->redirect();
              }

    }

    function recordActions($rec, &$actions, &$mraactions) {
      $user     = getUser();
      $org      = $user['employer_id'];
      $ob       = $rec['opening_balance'];
      $code     = $rec['coa_code'];

      if(!empty($code)){
        $db       = atkGetDb();
          $getCoa = $db->getrows("SELECT IFNULL(opening_balance,0) as opening_balance FROM coa_".$user[employer_id]." WHERE coa_code = '$code'");
          $opening_balance = $getCoa[0]['opening_balance'];

            if($opening_balance != 0){
              unset($actions['delete']);
            }elseif($opening_balance == ''){
              return true;
            }

          $row = $db->getrows("SELECT a.`id_org`, b.`coa` FROM `journal` a, `transaction` b  
                                    WHERE a.`id_journal` = b.`id_journal` AND b.`coa` = '$code' AND a.`id_org` = '$org' LIMIT 1");
          $coa    = $row[0]['coa'];
          $id_org = $row[0]['id_org'];

            if($id_org == $org && $coa == $code){
             unset($actions['delete']);
            }
      }
    }
}
?>