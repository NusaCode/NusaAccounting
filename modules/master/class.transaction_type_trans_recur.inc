<?php
useattrib("atkNumberAttribute");
useattrib("atkTextAttribute");

class transaction_type_trans_recur extends atkNode
{
  var $_module  = "master";
  var $_node    = "transaction_type_trans_recur";
  var $_table   = "transaction_type_trans_recur";


    function transaction_type_trans_recur()
    {
      $this->atkNode($this->_node, NF_ADD_LINK | NF_MRA);
    
      $this->add(new atkNumberAttribute("id", AF_AUTOKEY | AF_AUTOINCREMENT));

      $this->add(new atkManyToOneRelation("idtransaction_type", "master.transaction_recur", AF_SEARCHABLE | AF_RELATION_NO_NULL_ITEM | AF_RELATION_AUTOLINK))->setlabel("Trans. Type");

      $this->add(new atkManyToOneRelation("coa","quick_setup.coa_org", AF_SEARCHABLE | AF_OBLIGATORY));   
  
      $this->add(new atkListAttribute("balance",array("Debet","Kredit"), array("0","1"), AF_SEARCHABLE | AF_LIST_NO_NULL_ITEM)); 

      $this->add(new atkNumberAttribute("value"))->setlabel("Value ");      

      $this->add(new atkTextAttribute("desc", AF_SEARCHABLE));
        
      $this->setOrder("id");
      $this->setTable($this->_table);
      $this->setSecurityAlias("master.transaction_type");
    }

    function descriptor_def()
    {
      return "[coa.coa_code] - [coa.coa_name]";
    }

    function coa_validate(&$record, $mode){
      $code = $record['coa']['coa_code'];
      $id = $record['idtransaction_type']['id'];
      $db = atkGetDb();
      $res = $db->getrows("SELECT 1 val FROM transaction_type_trans_recur WHERE coa = '" . $code. "' AND idtransaction_type = '" . $id. "' LIMIT 1");
      $coa = $res[0]['val'];
              
      if($coa == 1)
      {
          atkTriggerError($record, $this->getAttribute('coa'), 'COA already used, please select another COA!!');
      }
      return true;
    }
}
?>