<?php
useattrib("atkNumberAttribute");
useattrib("atkTextAttribute");

class journal_type extends atkNode
{
  var $_module  = "master";
  var $_node    = "journal_type";
  var $_table   = "journal_type";


    function journal_type()
    {
      $user = getUser();
      $this->atkNode($this->_node, NF_ADD_LINK | NF_EDITAFTERADD | NF_LOCK);
  	
      $this->add(new atkNumberAttribute("id", AF_AUTOKEY | AF_AUTOINCREMENT));

      $this->add(new atkAttribute("code", AF_SEARCHABLE | AF_OBLIGATORY));   
  
      $this->add(new atkAttribute("name", AF_SEARCHABLE));  

      $this->add(new atkListAttribute("type",array("Transaction","Adjusment"), array("0","1"), AF_SEARCHABLE | AF_LIST_NO_NULL_ITEM)); 

      $this->add(new atkListAttribute("cash",array("Cash Flow","Non cash"), array("0","1"), AF_SEARCHABLE | AF_LIST_NO_NULL_ITEM))->setLabel("Cash "); 

      $this->add(new atkTextAttribute("desc",array("rows"=>1), AF_SEARCHABLE));  

      $this->add(new atkOneToManyRelation("transaction_type", "master.transaction_type","id_journal_type", AF_SEARCHABLE | AF_HIDE_LIST));

      $this->add(new atkNumberAttribute("id_org", AF_HIDE | AF_FORCE));  

      $this->add(new atkdummyattribute("jarak_atas","<br>", AF_HIDE_LIST));

      $this->add(new atkdummyattribute("garis","<hr>", AF_HIDE_LIST));

      $this->add(new atkCreatedByAttribute("created_by", AF_HIDE_LIST));

      $this->add(new atkCreateStampAttribute("created_on", AF_HIDE_LIST)); 

      $this->add(new AtkUpdatedByAttribute("last_modified_by", AF_HIDE_LIST));

      $this->add(new atkUpdateStampAttribute("last_modified_on", AF_HIDE_LIST));
  	  	
      $this->setOrder($this->_table.".name");
      $this->setTable($this->_table);
      $this->addFilter($this->_table.".id_org= '".$user[employer_id]."'");
      $this->setSecurityAlias("master.transaction_type");
    }

    function descriptor_def()
    {
      $user = getUser();
      return "[code] - [name]";
    }

    function initial_values(){
      $user = getUser();
      $id_org = $user['employer_id'];

      return array("id_org" => $id_org);
    }
}
?>