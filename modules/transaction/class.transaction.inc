<?php
useattrib("atkNumberAttribute");
useattrib("atkTextAttribute");
userelation("atkmanytoonerelation");

class transaction extends atkNode
{
  var $_module  = "transaction";
  var $_node    = "transaction";
  var $_table   = "transaction";
  var $_order   = "debit DESC,credit DESC";


    function transaction()
    {
      $user = &atkGetUser();
      $employer_id = $user['employer_id'];
      $this->atkNode($this->_node, NF_ADD_LINK | NF_MRA | NF_TRACK_CHANGES);
    
      $this->add(new atkNumberAttribute("id_transaksi", AF_AUTOKEY | AF_AUTOINCREMENT));
      
      $this->add(new atkManyToOneRelation("id_journal", "transaction.journal"));
      
      $coa = $this->add(new atkManyToOneRelation("coa", "quick_setup.coa_org", AF_SEARCHABLE | AF_LIST_NO_NULL_ITEM | AF_OBLIGATORY | AF_RELATION_AUTOLINK |AF_MANYTOONE_LAZY));
      $coa->addDestinationFilter("NOT EXISTS 
                                    (SELECT * FROM
                                    (SELECT DISTINCT coa_parent FROM coa_".$employer_id.")a WHERE coa_".$employer_id.".coa_code=a.coa_parent)");
      
      // $this->add(new atkManyToOneRelation("id_department", "master.department", AF_SEARCHABLE | AF_LIST_NO_NULL_ITEM));
      
      // $this->add(new atkManyToOneRelation("id_cost_center", "master.employee_cost_center", AF_SEARCHABLE));
      
      $balance = &$this->add(new atkListAttribute("balancing", array("Debit", "Credit"), array(1, 2), AF_HIDE_LIST |  AF_LIST_NO_NULL_ITEM));
      $balance->addOnChangeHandler("if (newvalue=='1') { $('ar_debit').show(); $('ar_credit').hide(); } else { $('ar_credit').show(); $('ar_debit').hide(); }");

      $this->add(new atkCurrencyAttribute("debit"));
      
      $this->add(new atkCurrencyAttribute("credit"));
      
      $this->add(new atkTextAttribute("desc", AF_SEARCHABLE));

      $this->add(new atkdummyattribute("jarak_atas","<br>", AF_HIDE_LIST));

      $this->add(new atkdummyattribute("garis","<hr>", AF_HIDE_LIST));

      $this->add(new atkCreatedByAttribute("created_by", AF_HIDE_LIST));

      $this->add(new atkCreateStampAttribute("created_on", AF_HIDE_LIST)); 

      $this->add(new AtkUpdatedByAttribute("last_modified_by", AF_HIDE_LIST));

      $this->add(new atkUpdateStampAttribute("last_modified_on", AF_HIDE_LIST));
      
      $page = $this->getPage();
     
      if($_GET['atknodetype'] == 'transaction.transaction' && ($_GET['atkaction'] == 'add' || $_GET['atkaction'] == 'edit')){
      $page->register_scriptcode('  

        function debit_onload(){

                        var balancing = document.getElementById(\'balancing\');
                        var debit = document.getElementById("ar_debit");
                        var credit = document.getElementById("ar_credit");
                       
                        if(balancing.value == 2){
                                debit.style.display = \'none\';
                                credit.style.display = \'\';

                        } else if(balancing.value == 1){
                            debit.style.display = \'\';
                            credit.style.display = \'none\';
                        }

                }

               window.onload = debit_onload;		
          
	');
  	
      }
      $this->setOrder($this->_order);
      $this->setSecurityAlias("transaction.journal");
      $this->setTable($this->_table);
    }
          
    function postAdd(&$record){
        $db = &atkGetDb();
        $bal = $record['balancing'];
        $debit = $record['debit'];
        $credit = $record['credit'];
        
        $res = $db->getrows("SELECT rate FROM journal WHERE id_journal = '" . $record['id_journal']['id_journal']. "'");
        $rate = $res[0]['rate'];
        $res3 = $db->getrows("SELECT SUM(debit) tot_debit, SUM(credit) tot_credit FROM transaction WHERE id_journal = '" . $record['id_journal']['id_journal']. "'");
        $totdebit = $res3[0]['tot_debit'];
        $totcredit = $res3[0]['tot_credit'];
        
        if($bal == 1){
            $newdeb = $debit * $rate;
            $db->query("UPDATE transaction SET debit = '".$newdeb."', ori_value = '".$debit."' WHERE id_transaksi = '" . $record['id_transaksi']. "'");
            $db->commit();
        }else{
            $newcre = $credit * $rate;
            $db->query("UPDATE transaction SET credit = '".$newcre."', ori_value = '".$credit."' WHERE id_transaksi = '" . $record['id_transaksi']. "'");
            $db->commit();            
        }
 
        if ($totdebit != $totcredit){
            $db->query("UPDATE journal SET posting = 3 WHERE id_journal = '" . $record['id_journal']['id_journal']. "'");
            $db->commit();
        }else{
            $db->query("UPDATE journal SET posting = 0 WHERE id_journal = '" . $record['id_journal']['id_journal']. "'");
            $db->commit();            
        }        
        return true;
    }
    
    function postUpdate(&$record){
        $db = &atkGetDb();
        $idj = $record['id_journal']['id_journal'];
        $bal = $record['balancing'];
        $orgdebit = $record['atkorgrec']['debit'];
        $orgcredit = $record['atkorgrec']['credit'];
        $id = $record['id_transaksi'];        
        $debit = $record['debit'];
        $credit = $record['credit'];
        
        $res = $db->getrows("SELECT rate FROM journal WHERE id_journal = '" . $idj. "'");
        $rate = $res[0]['rate'];
        $res3 = $db->getrows("SELECT SUM(debit) tot_debit, SUM(credit) tot_credit FROM transaction WHERE id_journal = '" . $idj. "'");
        $totdebit = $res3[0]['tot_debit'];
        $totcredit = $res3[0]['tot_credit'];
        
        if($bal == 1 && $debit != '' && $orgdebit != $debit){
            $newdeb = $debit * $rate;
            $db->query("UPDATE transaction SET credit = 'NULL', debit = '".$newdeb."', ori_value = '".$debit."' WHERE id_transaksi= '".$id."'");
            $db->commit;
        }elseif ($bal == 2 && $credit != '' && $orgcredit != $credit) {
            $newcre = $credit * $rate;
            $db->query("UPDATE transaction SET debit = 'NULL', credit = '".$newcre."', ori_value = '".$credit."' WHERE id_transaksi= '".$id."'");
            $db->commit;
        }        
        
        if ($totdebit != $totcredit){
            $db->query("UPDATE journal SET posting = 3 WHERE id_journal = '" . $record['id_journal']['id_journal']. "'");
            $db->commit();
        }else{
            $db->query("UPDATE journal SET posting = 0 WHERE id_journal = '" . $record['id_journal']['id_journal']. "'");
            $db->commit();            
        }
        
        return true;
    }

    function postDelete($record){
       $db = &atkGetDb();
        $res3 = $db->getrows("SELECT SUM(debit) tot_debit, SUM(credit) tot_credit FROM transaction WHERE id_journal = '" . $record['journal']['id_journal']. "'");
        $totdebit = $res3[0]['tot_debit'];
        $totcredit = $res3[0]['tot_credit'];
        if ($totdebit != $totcredit){
            $db->query("UPDATE journal SET posting = 3 WHERE id_journal = '" . $record['id_journal']['id_journal']. "'");
            $db->commit();
        }else{
            $db->query("UPDATE journal SET posting = 0 WHERE id_journal = '" . $record['id_journal']['id_journal']. "'");
            $db->commit();            
        }
        
        return true;
    }
    
    function coa_validate(&$record, $mode){
        $code = $record['coa']['coa_code'];
        $orgcode = $record['atkorgrec']['coa']['coa_code'];
        $id = $record['id_journal']['id_journal'];
        $db = atkGetDb();
        $res = $db->getrows("SELECT 1 val FROM transaction WHERE coa = '" . $code. "' AND id_journal = '" . $id. "' LIMIT 1");
        $coa = $res[0]['val'];
                
        if($coa == 1 && $mode == 'add')
        {
            atkTriggerError($record, $this->getAttribute('coa'), 'COA already used, please select another COA!!');
        }else if($coa == 1 && $mode == 'update' && $orgcode != $code) {
            atkTriggerError($record, $this->getAttribute('coa'), 'COA already used, please select another COA!!');
        }
        return true;
    }
    
    function initial_values() {
        parent::initial_values();
        
        $d = 0.00;
        $c = 0.00;
        
        return array("debit" => $d, 
                    "credit" => $c
                    );
    }       

    function getFormButtons($mode, $record) {
      $db = &atkGetDb();
      $id = $record['id_transaksi'];
      
      $rows = $db->getrows("SELECT a.posting, a.status_period FROM journal a, transaction b WHERE  a.id_journal = b.id_journal AND b.id_transaksi='" . $id . "'");
      $res = $rows[0]['posting'];
      $res2 = $rows[0]['status_period'];
        
      $buttons = parent::getFormButtons($mode, $record);  // returns an array of buttons
      if ( ($mode == 'view' && $res == '1') || ($mode == 'view' && $res != '1' && $res2 != '1') ) {
           $buttons[1] = '';    // remove the 1st button (which is usually save & close)
      }
      return $buttons; 
    }
}
?>