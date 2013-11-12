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
      $this->atkNode($this->_node, NF_ADD_LINK | NF_EDITAFTERADD);
  	
      $this->add(new atkNumberAttribute("id", AF_AUTOKEY | AF_AUTOINCREMENT));

      $this->add(new atkAttribute("code", AF_SEARCHABLE));   
  
      $this->add(new atkAttribute("name", AF_SEARCHABLE));  

      $this->add(new atkListAttribute("type",array("Transaction","Adjusment"), array("0","1"), AF_SEARCHABLE | AF_LIST_NO_NULL_ITEM)); 

      $this->add(new atkListAttribute("cash",array("Cash Flow","Non cash"), array("0","1"), AF_SEARCHABLE | AF_LIST_NO_NULL_ITEM)); 

      $this->add(new atkTextAttribute("desc", AF_SEARCHABLE));  

      $this->add(new atkOneToManyRelation("transaction_type", "master.transaction_type","id_journal_type", AF_SEARCHABLE | AF_HIDE_LIST)); 
  	  	
     $this->setOrder($this->_table.".name");
      $this->setTable($this->_table);
      $this->setSecurityAlias("master.transaction_type");
    }

    function descriptor_def()
    {
      return "[code] - [name]";
    }
}
?>