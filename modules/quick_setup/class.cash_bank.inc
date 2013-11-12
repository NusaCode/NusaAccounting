<?php
useattrib("atkNumberAttribute");
useattrib("atkTextAttribute");

class cash_bank extends atkNode
{
  var $_module  = "quick_setup";
  var $_node    = "cash_bank";
  var $_table   = "ob_cash_bank";


    function cash_bank()
    {
      $this->atkNode($this->_node, NF_ADD_LINK | NF_MRA);
  	
      $this->add(new atkNumberAttribute("id", AF_AUTOKEY | AF_AUTOINCREMENT));

      $this->add(new atkManyToOneRelation("id_org", "organization.organization", AF_SEARCHABLE | AF_RELATION_NO_NULL_ITEM | AF_LARGE))->setlabel("Organization");

      $coa_select = $this->add(new atkManyToOneRelation("coa", "master.coa", AF_SEARCHABLE | AF_RELATION_NO_NULL_ITEM))->setlabel("COA");
      $coa_select->addDestinationFilter("NOT EXISTS 
                                    (SELECT * FROM
                                    (SELECT DISTINCT coa_parent FROM coa)a WHERE coa.coa_code=a.coa_parent) AND coa.coa_jenis = 'a'");

      $this->add(new atkManyToOneRelation("currency", "master.currency", AF_SEARCHABLE | AF_RELATION_NO_NULL_ITEM))->setlabel("Currency");

      $this->add(new atkDateAttribute("date", AF_SEARCHABLE))->setlabel("Date");   

      $this->add(new atkCurrencyAttribute("current_balance", AF_SEARCHABLE))->setlabel("Current Balance");   
  
      $this->add(new atkTextAttribute("desc", AF_SEARCHABLE))->setlabel("Description");   
  	  	
     $this->setOrder("id");
      $this->setTable($this->_table);
    }

    function descriptor_def()
    {
      return "[coa]";
    }

    function getUser($record, $mode){
      $db = atkGetDb();
        $user = $db->getrows("SELECT name FROM Organization WHERE type = '0'");
          $attr = &$this->getAttribute("id_org");
          return $attr->edit($record, $mode);
    }
}
?>