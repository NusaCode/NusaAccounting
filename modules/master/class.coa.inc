<?php
atkimport("atk.atktreenode");
userelation("atkManyToOneTreeRelation");

class coa extends atkTreeNode
{
  var $_module  = "master";
  var $_node    = "coa";
  var $_table   = "coa_master";


    function coa()
    {
      $this->atkTreeNode($this->_node, NF_ADD_LINK | NF_MRA |NF_IMPORT | NF_LOCK);
 	
      $this->add(new atkAttribute("coa_code", AF_OBLIGATORY | AF_PRIMARY));
  	
      $this->add(new atkManyToOneTreeRelation("coa_parent", "master.coa", AF_PARENT | AF_CASCADE_DELETE ));
	  
      $this->add(new atkAttribute("coa_name"));

      $this->add(new atkListAttribute("coa_jenis", array("Asset", "Liabilities", "Owner Equities", "Revenue", "Expense"), array("a", "l", "o", "r", "e"),  AF_LIST_NO_NULL_ITEM | AF_HIDE_LIST));

      $this->add(new atkListAttribute("balance",array("Debet","Kredit"), array("0","1"),  AF_LIST_NO_NULL_ITEM | AF_HIDE_LIST));   

      $this->add(new atkNumberAttribute("opening_balance"));      

      $this->add(new atkDateAttribute("date_ob"))->setLabel("Opening Balance Date ");      

      $this->add(new atkTextAttribute("desc", AF_HIDE_LIST));

      // $this->add(new atkManyToOneRelation("id_org","organization.organization", AF_READONLY | AF_RELATION_NO_NULL_ITEM));

      // $this->add(new atkdummyattribute("jarak_atas","<br>", AF_HIDE_LIST));

      // $this->add(new atkdummyattribute("garis","<hr>", AF_HIDE_LIST));

      // $this->add(new atkCreatedByAttribute("created_by", AF_HIDE_LIST));

      // $this->add(new atkCreateStampAttribute("created_on", AF_HIDE_LIST)); 

      // $this->add(new AtkUpdatedByAttribute("last_modified_by", AF_HIDE_LIST));

      // $this->add(new atkUpdateStampAttribute("last_modified_on", AF_HIDE_LIST));


      $this->setTable($this->_table);
    }

    function descriptor_def()
    {
      return "[coa_code] - [coa_name]";
    }


     function preAdd(&$record){
      $user = getUser();
      $op   = $record['opening_balance'];
      $date = $record['date_ob']['year'];


      if($op !== '' && $date == ''){
          atkTriggerError($record, $this->getAttribute('date_ob'), '"Please insert Opening Balance"');
      }
      return true;
    }

    function preUpdate(&$record){
      $user = getUser();
      $op   = $record['opening_balance'];
      $date = $record['date_ob']['year'];


      if($op !== '' && $date == ''){
          atkTriggerError($record, $this->getAttribute('date_ob'), '"Please insert Opening Balance"');
      }
      return true;
    }
}
?>