<?php
useattrib("atkNumberAttribute");
useattrib("atkTextAttribute");
userelation("atkOneToManyRelation");
include_once (moduleDir("master")."class.org_bank.inc");

class ven_bank extends org_bank{
	  var $_module  = "quick_setup";
	  var $_node    = "ven_bank";
	  var $_table   = "org_bank";

    function ven_bank(){
      $this->org_bank($this->_node, NF_ADD_LINK | NF_MRA);
      $this->add(new atkManyToOneRelation("id_org","quick_setup.vendor", AF_HIDE));

    } 
}
?>