<?php
useattrib("atkNumberAttribute");
useattrib("atkTextAttribute");

class transaction_type_trans extends atkNode
{
  var $_module  = "master";
  var $_node    = "transaction_type_trans";
  var $_table   = "transaction_type_trans";


    function transaction_type_trans()
    {
      $user = &atkGetUser();
  	  $employer_id = $user['employer_id'];

      $this->atkNode($this->_node, NF_ADD_LINK | NF_MRA);
      $action = array("admin","add","edit","delete");
        $this->addAllowedAction($action);

      $this->add(new atkNumberAttribute("id", AF_AUTOKEY | AF_AUTOINCREMENT));

      $this->add(new atkmanytoonerelation("idtransaction_type", "master.transaction_type", AF_SEARCHABLE | AF_RELATION_NO_NULL_ITEM | AF_RELATION_AUTOLINK))->setlabel("Trans. Type");

      $coa = $this->add(new atkManyToOneRelation("coa","quick_setup.coa_org", AF_SEARCHABLE | AF_OBLIGATORY | AF_MANYTOONE_LAZY));   
      $coa->addDestinationFilter("NOT EXISTS 
                                    (SELECT * FROM
                                    (SELECT DISTINCT coa_parent FROM coa_".$employer_id.")a WHERE coa_".$employer_id.".coa_code=a.coa_parent)");
  
      $this->add(new atkListAttribute("balance",array("Debet","Kredit"), array("0","1"), AF_SEARCHABLE | AF_LIST_NO_NULL_ITEM)); 

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
      $res = $db->getrows("SELECT 1 val FROM transaction_type_trans WHERE coa = '" . $code. "' AND idtransaction_type = '" . $id. "' LIMIT 1");
      $coa = $res[0]['val'];
              
      if($coa == 1)
      {
          atkTriggerError($record, $this->getAttribute('coa'), 'COA already used, please select another COA!!');
      }
      return true;
    }
}
?>