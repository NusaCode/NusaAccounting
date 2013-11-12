<?php
useattrib("atkNumberAttribute");
useattrib("atkTextAttribute");
include_once (moduleDir("master")."class.coa.inc");

class opening_balance extends atkNode
{
  var $_module  = "quick_setup";
  var $_node    = "opening_balance";
  var $_table   = "coa";


    function opening_balance()
    {
      $this->atkNode($this->_node, NF_ADD_LINK | NF_MRA );
	
      $this->add(new atkAttribute("coa_code", AF_OBLIGATORY | AF_PRIMARY | AF_HIDE_LIST));
  	
      $this->add(new atkManyToOneTreeRelation("coa_parent", "master.coa", AF_PARENT | AF_CASCADE_DELETE | AF_HIDE_LIST));
	  
      $this->add(new atkAttribute("coa_name"));

      $this->add(new atkListAttribute("coa_jenis", array("Asset", "Liabilities", "Owner Equities", "Revenue", "Expense"), array("a", "l", "o", "r", "e"),  AF_LIST_NO_NULL_ITEM | AF_HIDE_LIST));

      $this->add(new atkListAttribute("balance",array("Debet","Kredit"), array("0","1"),  AF_LIST_NO_NULL_ITEM | AF_HIDE_LIST));   

      $this->add(new atkNumberAttribute("opening_balance"));      

      $this->add(new atkTextAttribute("desc", AF_HIDE_LIST));

      $this->setOrder("coa_code");
      $this->setTable($this->_table);
    }
  }
?>