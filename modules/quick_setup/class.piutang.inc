<?php
useattrib("atkNumberAttribute");
useattrib("atkTextAttribute");

class piutang extends atkNode
{
  var $_module  = "quick_setup";
  var $_node    = "piutang";
  var $_table   = "ob_piutang";


    function piutang()
    {
      $this->atkNode($this->_node, NF_ADD_LINK | NF_MRA);
  	
      $this->add(new atkNumberAttribute("id", AF_AUTOKEY | AF_AUTOINCREMENT));

      $this->add(new atkManyToOneRelation("id_org", "quick_setup.customer", AF_HIDE));

      $coa_select = $this->add(new atkManyToOneRelation("coa", "master.coa", AF_SEARCHABLE | AF_RELATION_NO_NULL_ITEM))->setlabel("COA");
      $coa_select->addDestinationFilter("NOT EXISTS 
                                    (SELECT * FROM
                                    (SELECT DISTINCT coa_parent FROM coa)a WHERE coa.coa_code=a.coa_parent) AND coa.coa_jenis = 'a'");

      $this->add(new atkManyToOneRelation("currency", "master.currency", AF_SEARCHABLE | AF_RELATION_NO_NULL_ITEM))->setlabel("Currency");

      $this->add(new atkDateAttribute("date", AF_SEARCHABLE | AF_OBLIGATORY))->setlabel("Date");   

      $this->add(new atkCurrencyAttribute("current_balance", AF_SEARCHABLE | AF_OBLIGATORY))->setlabel("Current Balance");   
  
      $this->add(new atkTextAttribute("desc", AF_SEARCHABLE))->setlabel("Description");   
  	  	
      $this->setOrder($this->Name);
      $this->setTable($this->_table);
      $this->setSecurityAlias("quick_setup.customer");
    }

    function descriptor_def()
    {
      return "[coa]";
    }
}
?>