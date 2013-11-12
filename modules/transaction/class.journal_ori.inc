`<?php
//useattrib("atkNumberAttribute");
//useattrib("atkTextAttribute");
//userelation("atkonetomanyrelation");

class journal extends atkNode
{
  var $_module  = "transaction";
  var $_node    = "journal";
  var $_table   = "journal";
  var $_order   = "trans_date, id_journal ASC";


    function journal()
    {
      $this->atkNode($this->_node, NF_ADD_LINK | NF_MRA | NF_EDITAFTERADD | NF_LOCK);
  	
      $this->add(new atkNumberAttribute("id_journal", AF_AUTOKEY | AF_AUTOINCREMENT));

      $this->add(new atkNumberAttribute("v_no", AF_SEARCHABLE | AF_FORCE_LOAD | AF_OBLIGATORY | AF_UNIQUE))
      ->setLabel("J No");      

      $journal_type = $this->add(new atkManyToOneRelation("id_journal_type", "master.journal_type", AF_SEARCHABLE | AF_RELATION_NO_NULL_ITEM | AF_OBLIGATORY));
      $journal_type->addDependee("id_transaction_type");
      
      $transc_type = $this->add(new atkManyToOneRelation("id_transaction_type", "master.transaction_type", AF_SEARCHABLE | AF_RELATION_NO_NULL_ITEM | AF_HIDE_LIST));
      $transc_type->addDestinationFilter("transaction_type.id_journal_type='[id_journal_type.id]'");
      
      $this->add(new atkDateAttribute("trans_date", AF_SEARCHABLE));
      
      $curr = $this->add(new atkManyToOneRelation("id_currency","master.currency", AF_SEARCHABLE | AF_OBLIGATORY | AF_RELATION_NO_NULL_ITEM));
      $curr->addDependee("rate");
      
      $this->add(new atkNumberAttribute("rate", AF_SEARCHABLE | AF_FORCE_LOAD));
      
      $this->add(new atkListAttribute("status_period", array("Close", "Open","Close"), array(0, 1, 99), AF_HIDE_ADD | AF_HIDE_EDIT | AF_SEARCHABLE));      
      
      $this->add(new atkTextAttribute("desc", AF_SEARCHABLE));
      
      $this->add(new atkExpressionAttribute("Total_Debit", "SELECT SUM(debit) 
                                                            FROM transaction tr 
                                                            LEFT JOIN journal jr ON tr.id_journal=jr.id_journal
                                                            WHERE tr.id_journal = [table].id_journal", AF_HIDE_LIST));

      $this->add(new atkExpressionAttribute("Total_Credit", "SELECT SUM(credit) 
                                                         FROM transaction tr 
                                                         LEFT JOIN journal jr ON tr.id_journal=jr.id_journal
                                                         WHERE tr.id_journal = [table].id_journal", AF_HIDE_LIST));

      $this->add(new atkNumberAttribute("id_org", AF_HIDE));
      
      $this->add(new atkOneToManyRelation("transaction", "transaction.transaction", "id_journal", AF_HIDE_LIST | AF_CASCADE_DELETE));


      
      $this->add(new atkDummyAttribute("post", NULL, AF_HIDE_ADD | AF_HIDE_EDIT | AF_NO_LABEL));
      $this->post();
      
      $user=&atkgetuser();
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
    
    
    function post_display($record, $mode) {
        $db = atkGetDb();
        $res = $db->getrows("SELECT posting FROM journal WHERE id_journal = '" . $record['id_journal']. "'");
        $posting = $res[0]['posting'];
        
        $month = $record['trans_date']['month'];
        $year = $record['trans_date']['year'];
        
        if ((strlen($month) < 2)){
            $month = "0".$record['trans_date']['month'];
        }         
        
        $res2 = $db->getrows("SELECT status FROM periode_month WHERE id_year = '" . $year. "' AND month = '" . $month. "'");
        $status = $res2[0]['status'];
        
        if ($mode == "list") {
            if ($posting != 1 && $status == 1) {
                $form="<form method='post' action=''>
                                    <input type='hidden' name='id_journal' value='".$record['id_journal']."'>
                                    <input type='submit' name='posting' value='posting'>
                                    </form>";

               $post .= $form;
               
               return $post;
            }elseif ($posting == 1 && $status == 1){
                $form="<form method='post' action=''>
                    <input type='hidden' name='id_journal' value='".$record['id_journal']."'>
                    <input type='submit' name='unposting' value='unposting'>
                    </form>";

               $unpost .= $form;
               return $unpost;
            }elseif($posting == 1 && status != 1){
                $post = 'POSTED';
                
                return $post;
            }elseif($posting != 1 && status != 1){
                $unpost = 'Not Posted Yet';
                
                return $unpost;
            }
        }
           
    }
    
    function post() {	
        $db = atkGetDb();
		if(isset($_POST[posting]) && $_POST[id_journal] != ''){
			
                    $db->query("UPDATE journal set posting='1' where id_journal='".$_POST[id_journal]."'"); 
                    $db->commit();
			
		}elseif (isset($_POST[unposting]) && $_POST[id_journal] != ''){
                    $db->query("UPDATE journal set posting='0' where id_journal='".$_POST[id_journal]."'"); 
                    $db->commit();
                }	
		return true;
    }
    
    function initial_values() {
        parent::initial_values();
        $db = atkGetDb();
        $user = atkgetUser();
        $id_org = $user['employer_id'];        
        $vn = $db->getrows("select max(v_no)+1 voucher from journal");
        $v_no = $vn[0]['voucher'];
        
        if ($v_no == "") {
            $v_no = 100;
        }
        
        return array("v_no" => $v_no, 
                    "trans_date" => date('Y-m-d'), 
                    "closed_period"=> date('Y-m-t'),
                    "id_org" => $id_org
                    );
    }
    
    function rate_edit($record, $mode) {
       $record['rate']=$record['id_currency']['rate'];
		$attr = &$this->getAttribute("rate");
		return $attr->edit($record, $mode);
    }
    
    function postUpdate($record){
        $db = atkGetDb();
        
        $month = $record['trans_date']['month'];
        $year = $record['trans_date']['year'];
        
        if ((strlen($month) < 2)){
            $month = "0".$record['trans_date']['month'];
        }         
        
        $res = $db->getrows("SELECT status FROM periode_month WHERE id_year = '" . $year. "' AND month = '" . $month. "'");
        $status = $res[0]['status'];
        
        $db->query("UPDATE journal SET status_period = '" . $status . "' WHERE id_journal = '" . $record['id_journal']. "'");
        $db->commit();
        
        $db->query("UPDATE journal SET rate = '" . $record['rate'] . "' WHERE id_journal = '" . $record['id_journal']. "'");
        $db->commit();
        return true;
    }
    
    function postAdd(&$record) {
        $db = atkGetDb();
        
        $month = $record['trans_date']['month'];
        $year = $record['trans_date']['year'];
        
        if ((strlen($month) < 2)){
            $month = "0".$record['trans_date']['month'];
        }         
        
        $res = $db->getrows("SELECT status FROM periode_month WHERE id_year = '" . $year. "' AND month = '" . $month. "'");
        $status = $res[0]['status'];
        
        $db->query("UPDATE journal SET status_period = '" . $status . "' WHERE id_journal = '" . $record['id_journal']. "'");
        $db->commit();

        $db->query("UPDATE journal SET rate = '" . $record['rate'] . "' WHERE id_journal = '" . $record['id_journal']. "'");
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
        $page = $this->getPage();        
        $res = $db->getrows("SELECT COUNT(id_transaksi) jlh, SUM(debit) tot_debit, SUM(credit) tot_credit FROM transaction WHERE id_journal = '" . $record['id_journal']. "'");
        $debit = $res[0]['tot_debit'];
        $credit = $res[0]['tot_credit'];
        $jlh = $res[0]['jlh'];
        
        if ($jlh > 1) {
            if ($debit != $credit) {
            atkTriggerError($record, $this->getAttribute('transaction'), 'Credit-Debit not balance yet, please check!!');
            }
        }else{
            atkTriggerError($record, $this->getAttribute('transaction'), 'Transaction record should be more than one!!');
        }

        return true;
    }
    
        function trans_date_validate(&$record, $mode){
        $db = atkGetDb();    
        $month = $record['trans_date']['month'];
        $year = $record['trans_date']['year'];
        
        if ((strlen($month) < 2)){
            $month = "0".$record['trans_date']['month'];
        }        
        
        $res = $db->getrows("SELECT status FROM     periode_month WHERE id_year = '" . $year. "' AND month = '" . $month. "'");
        $status = $res[0]['status'];
        
        if ($status != 1) {
            atkTriggerError($record, $this->getAttribute('transaction'), 'Transaction period for this transaction is not yet opened!!');
            }
        return true;
    }
    
    function recordActions($rec, &$actions, &$mraactions) {
        
//        var_dump($rec);
        $db = &atkGetDb();
        $rows = $db->getrows("SELECT posting, status_period from journal where id_journal='" . $rec['id_journal'] . "'");

        $mraactions = array();
        $mraactions['delete']     = 'delete';
        $mraactions['posting']     = 'posting_record';
        $mraactions['unposting']     = 'unposting_record';

        if ($rows[0]['posting'] == 1) {
            unset($actions['edit']);
            unset($actions['delete']);
        }elseif ($rows[0]['posting'] != 1 && $rows[0]['status_period'] == 0) {
            unset($actions['edit']);
            unset($actions['delete']);
        }
    }
    
    function action_posting_record() {
        $id = $this->m_postvars['admin_atkselector'];

        foreach ($id as $pk) {
            $db = &atkGetDb();
            $db->query("UPDATE journal SET posting = '1' WHERE " . $pk . " AND status_period = 1");
            $db->commit();
        }
	$this->redirect();        
    }

    function action_unposting_record() {
        $id = $this->m_postvars['admin_atkselector'];

        foreach ($id as $pk) {
            $db = &atkGetDb();
            $db->query("UPDATE journal SET posting = '0' WHERE " . $pk . " AND status_period = 1");
            $db->commit();
        }
	$this->redirect();        
    }
    
    function getFormButtons($mode, $record) {
      $db = &atkGetDb();
      $rows = $db->getrows("SELECT posting FROM journal WHERE  id_journal='" . $record['id_journal'] . "'");
      $res = $rows[0]['posting'];
      
      $buttons = parent::getFormButtons($mode, $record);  // returns an array of buttons
      if ( $mode == 'view' && $res == '1' ) {
           $buttons[1] = '';    // remove the 1st button (which is usually save & close)
      }
      return $buttons; 
    }
}
?>