<?php
//useattrib("atkNumberAttribute");
//useattrib("atkTextAttribute");
//userelation("atkonetomanyrelation");

class journal extends atkNode
{
  var $_module  = "transaction";
  var $_node    = "journal";
  var $_table   = "journal";
  var $_order   = "trans_date DESC, id_journal ASC";


    function journal()
    {
      $this->atkNode($this->_node, NF_ADD_LINK | NF_MRA | NF_EDITAFTERADD | NF_LOCK | NF_TRACK_CHANGES);
      $action = array("posting_record", "unposting_record","view");
      $db = atkGetDb();
      $user=&atkgetuser();
      
      $this->addAllowedAction($action);
      $this->add(new atkNumberAttribute("id_journal", AF_AUTOKEY | AF_AUTOINCREMENT));

      $this->add(new atkNumberAttribute("v_no", AF_SEARCHABLE | AF_FORCE_LOAD | AF_OBLIGATORY | AF_UNIQUE));      

      $journal_type = $this->add(new atkManyToOneRelation("id_journal_type", "master.journal_type", AF_SEARCHABLE));
      $journal_type->addDependee("id_transaction_type");
      
      $transc_type = $this->add(new atkManyToOneRelation("id_transaction_type", "master.transaction_type", AF_SEARCHABLE | AF_HIDE_LIST))->setLabel("Transaction Type ");
      $transc_type->addDestinationFilter("transaction_type.id_journal_type='[id_journal_type.id]'");
      
      $this->add(new atkDateAttribute("trans_date", "Y M d", "Y M d", 0, 0, AF_SEARCHABLE, 30));
      
      $curr = $this->add(new atkManyToOneRelation("id_currency","master.currency", AF_SEARCHABLE | AF_OBLIGATORY | AF_RELATION_NO_NULL_ITEM));
      $curr->addDependee("rate");
      
//      $que = $db->getrows("SELECT id_currency FROM organization WHERE id = '".$user['employer_id']."'");
//      $res = $que[0]['id_currency'];
      
      $this->add(new atkNumberAttribute("rate", AF_SEARCHABLE | AF_FORCE_LOAD | AF_HIDE_LIST));
      
//      $rate = &$this->add(new atkNumberAttribute("rate", AF_SEARCHABLE | AF_FORCE_LOAD | AF_HIDE_LIST));
//      $rate->addOnChangeHandler("if (newvalue=='".$res."') { $('ar_debit').show(); $('ar_credit').hide(); } else { $('ar_credit').show(); $('ar_debit').hide(); }");
      
      $this->add(new atkListAttribute("status_period", array("Close", "Open", "Close Permanent"), array(0, 1, 99), AF_HIDE_ADD | AF_HIDE_EDIT | AF_SEARCHABLE));      
      
      $this->add(new atkTextAttribute("desc", AF_SEARCHABLE));
      
      $this->add(new atkParserAttribute("totaldebit", null, AF_HIDE_LIST | AF_FORCE_LOAD));
      
      $this->add(new atkParserAttribute("totalcredit", null, AF_HIDE_LIST | AF_FORCE_LOAD));

      $this->add(new atkNumberAttribute("id_org", AF_HIDE));
      
      $this->add(new atkOneToManyRelation("transaction", "transaction.transaction", "id_journal", AF_HIDE_LIST | AF_CASCADE_DELETE));
      
      $this->add(new atkOnetoManyrelation("attachment", "transaction.attachment", "idJournal", AF_HIDE_LIST | AF_CASCADE_DELETE), 'Attachment');
      
      $this->add(new atkListAttribute("posting", array("Not Posted Yet", "Posted", "No Transaction Found", "Not Balanced Yet"), array(0, 1, 2, 3), AF_HIDE_ADD | AF_HIDE_EDIT | AF_HIDE_VIEW | AF_SEARCHABLE));

      $this->add(new atkdummyattribute("jarak_atas","<br>", AF_HIDE_LIST));

      $this->add(new atkdummyattribute("garis","<hr>", AF_HIDE_LIST));

      $this->add(new atkCreatedByAttribute("created_by", AF_HIDE_LIST));

      $this->add(new atkCreateStampAttribute("created_on", AF_HIDE_LIST)); 

      $this->add(new AtkUpdatedByAttribute("last_modified_by", AF_HIDE_LIST));

      $this->add(new atkUpdateStampAttribute("last_modified_on", AF_HIDE_LIST));
      
      if ($user['employer_id'] != '') 
      {
          $this->addFilter($this->_table.".id_org = '".$user['employer_id']."'");
      }
      
      $this->setOrder($this->_order);
      $this->setTable($this->_table);
    }

    function descriptor_def()
    {
        return "[v_no]";
    }
    
    function totaldebit_edit($record, $mode){
        $db = atkGetDb();
        $res = $db->getrows("SELECT FORMAT(SUM(tr.debit),2) total
                             FROM transaction tr, 
                             journal jr WHERE tr.id_journal=jr.id_journal
                             AND tr.id_journal = '".$record['id_journal']."'");
        $result = $res[0]['total'];
        $total = $result;
        
        return $total;
    }
    
    function totaldebit_add($record, $mode){
        $db = atkGetDb();
        $res = $db->getrows("SELECT FORMAT(SUM(tr.debit),2) total
                             FROM transaction tr, 
                             journal jr WHERE tr.id_journal=jr.id_journal
                             AND tr.id_journal = '".$record['id_journal']."'");
        $result = $res[0]['total'];
        $total = $result;
        
        return $total;
    }    
    
    function totaldebit_display($record, $mode){
        $db = atkGetDb();
        $res = $db->getrows("SELECT FORMAT(SUM(tr.debit),2) total
                             FROM transaction tr, 
                             journal jr WHERE tr.id_journal=jr.id_journal
                             AND tr.id_journal = '".$record['id_journal']."'");
        $result = $res[0]['total'];
        $total = $result;
        
        return $total;
    }    
    
    function totalcredit_edit($record, $mode){
        $db = atkGetDb();
        $res = $db->getrows("SELECT FORMAT(SUM(tr.credit),2) total
                             FROM transaction tr, 
                             journal jr WHERE tr.id_journal=jr.id_journal
                             AND tr.id_journal = '".$record['id_journal']."'");
        $result = $res[0]['total'];
        $total = $result;
        
        return $total;
    }
    
    function totalcredit_add($record, $mode){
        $db = atkGetDb();
        $res = $db->getrows("SELECT FORMAT(SUM(tr.credit),2) total
                             FROM transaction tr, 
                             journal jr WHERE tr.id_journal=jr.id_journal
                             AND tr.id_journal = '".$record['id_journal']."'");
        $result = $res[0]['total'];
        $total = $result;
        
        return $total;
    }    
    
    function totalcredit_display($record, $mode){
        $db = atkGetDb();
        $res = $db->getrows("SELECT FORMAT(SUM(tr.credit),2) total
                             FROM transaction tr, 
                             journal jr WHERE tr.id_journal=jr.id_journal
                             AND tr.id_journal = '".$record['id_journal']."'");
        $result = $res[0]['total'];
        $total = $result;
        
        return $total;
    }    
    
    function posting_display($record, $mode) {
        $db = atkGetDb();
        $res = $db->getrows("SELECT posting FROM journal WHERE id_journal = '" . $record['id_journal']. "'");
        $res2 = $db->getrows("SELECT COUNT(id_transaksi) trans, SUM(debit) tot_debit, SUM(credit) tot_credit FROM transaction WHERE id_journal = '" . $record['id_journal']. "'");
        
        $totdebit = $res2[0]['tot_debit'];
        $totcredit = $res2[0]['tot_credit'];
        $trans = $res2[0]['trans'];
        
        $posting = $res[0]['posting'];
        $status = $record['status_period'];
         
        if($mode == "list") {
            if($posting != 1 && $status == 1 && $trans > 0 && $totdebit == $totcredit) {
                $url = session_url(dispatch_url("transaction.journal", "posting_record", array("id_journal"=>$record['id_journal'])), SESSION_DEFAULT);
                $a = "<a href='javascript:void(0);' onmouseover='window.status=\"hide link\";return true;' onclick='window.location.href=\"".$url."\"'><input type='button' name='posting' value='Posting'></a>";
//                $form="<form method='post'>
//                                    <input type='hidden' name=atknodetype value=transaction.journal/>
//                                    <input type='hidden' name=atkaction value=posting_record />
//                                    <input type='hidden' name='id_journal' value='".$record['id_journal']."'>
//                                    <input type='submit' name='posting' value='Posting'>
//                                    </form>";
//                $form="<a href=".$url."><input type='button' name='posting' value='Posting'></a>";
//               $post .= $form; 
               $post .= $a; 
               return $post;
            }elseif ($posting == 1 && $status == 1 && $trans > 0 && $totdebit == $totcredit){
                $url = session_url(dispatch_url("transaction.journal", "unposting_record", array("id_journal"=>$record['id_journal'])), SESSION_DEFAULT);
                $a = "<a href='javascript:void(0);' onmouseover='window.status=\"hide link\";return true;' onclick='window.location.href=\"".$url."\"'><input type='button' name='unposting' value='Unposting'></a>";
//                $form="<a href=".$url."><input type='button' name='unposting' value='Unposting'></a>";
//               $unpost .= $form;
               $unpost .= $a;
               return $unpost;
            }elseif($posting == 1 && status != 1 && $trans > 0 && $totdebit == $totcredit){
                $post = 'Posted';
                
                return $post;
            }elseif($posting != 1 && status != 1 && $trans > 0 && $totdebit == $totcredit){
                $unpost = 'Not Posted Yet';
                
                return $unpost;
            }elseif($trans < 1){
                $status = 'No Transaction Found';
                
                return $status;
            }elseif (($trans >= 1 && $totdebit == "") || ($trans >= 1 && $totcredit == "") || ($trans >= 1 && $totdebit != $totcredit)){
                $status = 'Not Balanced Yet';
                
                return $status;
            }
        }
           
    }
    
  //   function posting() {	
  //       $db = atkGetDb();
		// if(isset($_POST[posting]) && $_POST[id_journal] != ''){
  //                   $db->query("UPDATE journal set posting='1' where id_journal='".$_POST[id_journal]."'"); 
  //                   $db->commit();
  //               // var_dump($_POST[posting]);
  //       }elseif (isset($_POST[unposting]) && $_POST[id_journal] != ''){
  //                   $db->query("UPDATE journal set posting='0' where id_journal='".$_POST[id_journal]."'"); 
  //                   $db->commit();
  //               }   
		// return true;
  //   }
    
    function initial_values() {
        parent::initial_values();
        $db = atkGetDb();
        $user = atkgetUser();
        $id_org = $user['employer_id'];        
        $vn = $db->getrows("select max(v_no)+1 voucher from journal where id_org = ".$id_org."");
        $v_no = $vn[0]['voucher'];
        
        if($v_no == ''){
            $v_no = 100;
        }
        
        return array("v_no" => $v_no, 
                    "trans_date" => date('Y-m-d'), 
                    "closed_period"=> date('Y-m-d'),
                    "id_org" => $id_org,
                    "posting" => 0
                    );
    }
    
    function rate_edit($record, $mode) {
       $record['rate']=$record['id_currency']['rate'];
		$attr = &$this->getAttribute("rate");
		return $attr->edit($record, $mode);
    }
    
    function postUpdate(&$record){
        $db = atkGetDb();
        $user=&atkgetuser();
        
        $month = $record['trans_date']['month'];
        $year = $record['trans_date']['year'];
        $idor = $user['employer_id'];
        $rate = $record['rate'];
        $orgrate = $record['atkorgrec']['rate'];
        
        if($orgrate != $rate){
            $db->query("UPDATE transaction
                                SET debit = (CASE
                                             WHEN debit > 0 THEN (ori_value*".$rate.")
                                             WHEN debit = 0 THEN 0
                                             END),
                                    credit = (CASE
                                             WHEN credit > 0 THEN (ori_value*".$rate.")
                                             WHEN credit = 0 THEN 0
                                             END)
                        WHERE id_journal = " . $record['id_journal']. "");
            $db->commit();
        }
        
        if ((strlen($month) < 2)){
            $month = "0".$record['trans_date']['month'];
        }         
        
        $res = $db->getrows("SELECT a.status FROM periode_month a, periode_year b WHERE a.id_year = b.id
                            AND b.year = '" . $year. "' AND b.id_org = ".$idor." AND a.`month` = '" . $month. "'");
        $status = $res[0]['status'];
        
        $res3 = $db->getrows("SELECT COUNT(id_transaksi) trans, SUM(debit) tot_debit, SUM(credit) tot_credit FROM transaction WHERE id_journal = '" . $record['id_journal']. "'");
        $totdebit = $res3[0]['tot_debit'];
        $totcredit = $res3[0]['tot_credit'];
        $trans = $res3[0]['trans'];
        
        if (($trans >= 1 && $totdebit == "") || ($trans >= 1 && $totcredit == "") || ($trans >= 1 && $totdebit != $totcredit)){
            $db->query("UPDATE journal SET 
                        status_period = '" . $status . "',
                        rate = '" . $record['rate'] . "',
                        posting = 3    
                        WHERE id_journal = '" . $record['id_journal']. "'");
            $db->commit();
        }elseif($trans >= 2 && $totdebit == $totcredit){
            $db->query("UPDATE journal SET 
                        status_period = '" . $status . "',
                        rate = '" . $record['rate'] . "',
                        posting = 0    
                        WHERE id_journal = '" . $record['id_journal']. "'");
            $db->commit();            
        }elseif($trans < 1){
            $db->query("UPDATE journal SET 
                        status_period = '" . $status . "',
                        rate = '" . $record['rate'] . "',
                        posting = 2    
                        WHERE id_journal = '" . $record['id_journal']. "'");
            $db->commit();            
        }
        
        return true;
    }
        
    function postAdd(&$record) {
        $db = atkGetDb();
        $user=&atkgetuser();
        
        $month = $record['trans_date']['month'];
        $year = $record['trans_date']['year'];
        $idor = $user['employer_id'];
        
        if ((strlen($month) < 2)){
            $month = "0".$record['trans_date']['month'];
        }         
        
        $res = $db->getrows("SELECT a.status FROM periode_month a, periode_year b WHERE a.id_year = b.id
                            AND b.year = '" . $year. "' AND b.id_org = ".$idor." AND a.`month` = '" . $month. "'");
        $status = $res[0]['status'];
        
        
        $db->query("UPDATE journal SET 
                    status_period = '" . $status . "',
                    rate = '" . $record['rate'] . "',
                    posting = 2    
                    WHERE id_journal = '" . $record['id_journal']. "'");
        $db->commit();
        
        $node = atkGetNode('transaction.transaction'); 
        $res2 = $db->getrows("SELECT coa FROM transaction_type_trans WHERE idtransaction_type = '" . $record['id_transaction_type']['id']. "'");
        foreach ($res2 as $k) {
            $record2['id_journal'] = $record['id_journal'];
            $record2['coa'] = $k['coa']; 
//            $record3['desc'] = $k['desc'];
            $node->addDb($record2);        
        }
        
        return true;
    }
    
    function transaction_validate(&$record, $mode){
        $db = atkGetDb();     
        $res = $db->getrows("SELECT COUNT(id_transaksi) jlh, SUM(debit) tot_debit, SUM(credit) tot_credit FROM transaction WHERE id_journal = '" . $record['id_journal']. "'");
        $debit = $res[0]['tot_debit'];
        $credit = $res[0]['tot_credit'];
        $jlh = $res[0]['jlh'];

        if ($jlh > 1) {
            if ($debit != $credit) {
//            atkTriggerError($record, $this->getAttribute('transaction'), 'Credit-Debit not balance yet, please check!!');
                echo '<script>
                    var $quest = confirm("Credit - Debit not balance yet.\nContinue the process?");
                    if($quest == true){
                      window.location="'.dispatch_url("transaction.journal", "admin").'"
                    }else{
                      history.go(-1);
                    }
                </script>';
            }
        }else{
//            atkTriggerError($record, $this->getAttribute('transaction'), 'Transaction record should be more than one!!');
                echo '<script>
                    var $quest = confirm("Transaction record should be more than one.\nContinue the process?");
                    if($quest == true){
                      window.location="'.dispatch_url("transaction.journal", "admin").'"
                    }else{
                      history.go(-1);
                    }
                </script>';            
        }

        return true;
    }
    
        function trans_date_validate(&$record, $mode){
        $db    = atkGetDb();    
        $user  = getUser();
        $id_org= $user['employer_id'];
        $month = $record['trans_date']['month'];
        $year  = $record['trans_date']['year'];
        $trans_date = strtotime($record['trans_date'][year]."-".$record['trans_date'][month]."-".$record['trans_date'][day]);
        
        if ((strlen($month) < 2)){
            $month = "0".$record['trans_date']['month'];
        }        
        
        $res = $db->getrows("SELECT a.status FROM periode_month a, periode_year b WHERE a.id_year = b.id
                            AND b.year = '" . $year. "' AND b.id_org = ".$id_org." AND a.`month` = '" . $month. "'");
        $status = $res[0]['status'];
        
        $res2 = $db->getrows("SELECT DISTINCT(MAX(date_ob)) maximal FROM coa_".$user[employer_id]."");
        $maximal = $res2[0]['maximal'];
        
        $date_ob = strtotime($maximal);
        
        if ($status != 1) {
            atkTriggerError($record, $this->getAttribute('trans_date'), 'Transaction period for this transaction is not yet opened!!');
        }elseif ($trans_date < $date_ob && $maximal != '') {
            atkTriggerError($record, $this->getAttribute('trans_date'), 'Transaction date must be greater than / equal to maximum opening balance date!!');
        }
        return true;
    }
    
    function recordActions($rec, &$actions, &$mraactions) {
//        var_dump($xactions);exit;
        
        $mraactions = array();
        $mraactions['delete'] = 'delete';
        $mraactions['posting'] = "posting_record";
        $mraactions['unposting'] = "unposting_record";
        
        $db = &atkGetDb();
        $user=&atkgetuser();
        $rows = $db->getrows("SELECT posting, status_period from journal where id_journal='" . $rec['id_journal'] . "' AND id_org = ".$user['employer_id']."");

        if ($rows[0]['posting'] == 1) {
            unset($actions['edit']);
            unset($actions['delete']);
            unset($mraactions['delete']);
        }
        elseif ($rows[0]['posting'] != 1 && $rows[0]['status_period'] == 0) {
            unset($actions['edit']);
            unset($actions['delete']);
            unset($mraactions['delete']);
        }
    }
    
    function action_posting_record() {
        if ($this->m_postvars['admin_atkselector']) {
            $id = $this->m_postvars['admin_atkselector'];
            foreach ($id as $pk) {
                $db = &atkGetDb();            
                $db->query("UPDATE journal SET posting = '1' WHERE " . $pk . " AND status_period = 1 AND posting = 0 ");
                $db->commit();
            }
        }else{
            $id = "id_journal = '".$_GET['id_journal']."'";
                $db = &atkGetDb();            
                $db->query("UPDATE journal SET posting = '1' WHERE " . $id . " AND status_period = 1 AND posting = 0 ");
                $db->commit();
        }

	     $this->redirect(session_url(dispatch_url("transaction.journal", "admin", array("atkselector"=>$selector)), SESSION_DEFAULT));
    }

    function action_unposting_record() {
        if ($this->m_postvars['admin_atkselector']) {
            $id = $this->m_postvars['admin_atkselector'];
            foreach ($id as $pk) {
                $db = &atkGetDb();
                $db->query("UPDATE journal SET posting = '0' WHERE " . $pk . " AND status_period = 1 AND posting = 1");
                $db->commit();
            }
        }else{
            $id = "id_journal = '".$_GET['id_journal']."'";
                $db = &atkGetDb();
                $db->query("UPDATE journal SET posting = '0' WHERE " . $id . " AND status_period = 1 AND posting = 1");
                $db->commit();
        }

	     $this->redirect(session_url(dispatch_url("transaction.journal", "admin", array("atkselector"=>$selector)), SESSION_DEFAULT));
    }
    
    function getFormButtons($mode, $record) {
      $db = &atkGetDb();
      $rows = $db->getrows("SELECT posting, status_period FROM journal WHERE  id_journal='" . $record['id_journal'] . "'");
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