<?php
useattrib("atkNumberAttribute");
useattrib("atkTextAttribute");
userelation("atkOneToManyRelation");
include_once (moduleDir("master")."class.org_bank.inc");

class cus_bank extends org_bank{
	  var $_module  = "quick_setup";
	  var $_node    = "cus_bank";
	  var $_table   = "org_bank";
	
    function cus_bank(){
      $this->org_bank($this->_node, NF_ADD_LINK | NF_MRA);
      $this->add(new atkManyToOneRelation("id_org","quick_setup.customer", AF_HIDE));

    } 
}
?>