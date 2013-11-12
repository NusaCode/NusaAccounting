<?php
useattrib("atkNumberAttribute");
useattrib("atkTextAttribute");

class transaction_recur extends atkNode
{
  var $_module  = "master";
  var $_node    = "transaction_recur";
  var $_table   = "transaction_type";


    function transaction_recur()
    {
      $this->atkNode($this->_node, NF_ADD_LINK | NF_EDITAFTERADD | NF_LOCK);
    
      $this->add(new atkNumberAttribute("id", AF_AUTOKEY | AF_AUTOINCREMENT));

      $this->add(new atkManyToOneRelation("id_journal_type","master.journal_type", AF_SEARCHABLE))->setLabel("Journal Type ");

      $this->add(new atkAttribute("name", AF_SEARCHABLE | AF_OBLIGATORY));   
  
      $this->add(new atkTextAttribute("desc", AF_SEARCHABLE)); 

      $this->add(new atkListAttribute("recur", array("Yes", "No"), array("0","1"), AF_HIDE_LIST | AF_READONLY_EDIT | AF_HIDE_ADD))->setLabel("Recurring ");

      $this->add(new atkOneToManyRelation("transaction_type_trans_recur", "master.transaction_type_trans_recur","idtransaction_type", AF_SEARCHABLE | AF_HIDE_LIST))->setLabel("Transaction Type Trans Recurring "); 
       
      $this->add(new atkdummyattribute("jarak_atas","<br>", AF_HIDE_LIST));

      $this->add(new atkdummyattribute("garis","<hr>", AF_HIDE_LIST));

      $this->add(new atkCreatedByAttribute("created_by", AF_HIDE_LIST));

      $this->add(new atkCreateStampAttribute("created_on", AF_HIDE_LIST)); 

      $this->add(new AtkUpdatedByAttribute("last_modified_by", AF_HIDE_LIST));

      $this->add(new atkUpdateStampAttribute("last_modified_on", AF_HIDE_LIST));
        
      $this->setOrder($this->_table.".name");
      $this->setTable($this->_table);
      $this->addFilter($this->_table.".recur = 1");
      $this->setSecurityAlias("master.journal_type");
    }

    function descriptor_def()
    {
      return "[id_journal_type.code]";
    }

    function transaction_type_trans_validate(&$record, $mode){
        $db = atkGetDb();
        $page = $this->getPage();        
        $que = $db->getrows("SELECT COUNT(id) trns FROM transaction_type_trans WHERE idtransaction_type = '" . $record['id']. "'");
        $val = $que[0]['trns'];
        if ($val <= 1) {
            atkTriggerError($record, $this->getAttribute('transaction_type_trans'), 'Transaction record should be more than one!!');
        }
        return true;
    }

    function initial_values(){
      return array("recur"=>1);
    }
}
?>