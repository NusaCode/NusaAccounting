<?php
useattrib("atkNumberAttribute");
useattrib("atkTextAttribute");

class coa_jenis extends atkNode
{
  var $_module  = "master";
  var $_node    = "coa_jenis";
  var $_table   = "coa_jenis";


    function coa_jenis()
    {
      $this->atkNode($this->_node, NF_NO_ADD| NF_NO_EDIT | NF_NO_DELETE | NF_MRA);
  	
      $this->add(new atkNumberAttribute("id", AF_AUTOKEY | AF_AUTOINCREMENT));

      $this->add(new atkAttribute("Name", AF_SEARCHABLE));   
  
      $this->add(new atkTextAttribute("desc", AF_SEARCHABLE));   
  	  	
     $this->setOrder($this->Name);
      $this->setTable($this->_table);
    }

    function descriptor_def()
    {
      return "[Name]";
    }
}
?>