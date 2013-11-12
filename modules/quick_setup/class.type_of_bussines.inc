<?php
userelation("atkmanytoonerelation");
useattrib("atkNumberAttribute");
useattrib("atkTextAttribute");

class type_of_bussines extends atkNode{
  var $_module  = "quick_setup";
  var $_node    = "type_of_bussines";
  var $_table   = "type_of_bussines";

function type_of_bussines(){
    $this->atkNode($this->_node, NF_ADD_LINK | NF_MRA);
  
    $this->add(new atkNumberAttribute("id", AF_AUTOKEY | AF_AUTOINCREMENT));

    $this->add(new atkAttribute("name"));

    $this->add(new atkTextAttribute("desc"));  

    $this->setOrder("id");
    $this->setTable($this->_table);
  }

  function descriptor_def(){
    return "[name]";
  }      
}
?>