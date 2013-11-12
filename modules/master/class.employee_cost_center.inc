<?php
useattrib("atkNumberAttribute");
useattrib("atkTextAttribute");

class employee_cost_center extends atkNode
{
  var $_module  = "master";
  var $_node    = "employee_cost_center";
  var $_table   = "employee_cost_center";


    function employee_cost_center()
    {
      $this->atkNode($this->_node, NF_ADD_LINK | NF_MRA);
  	
      $this->add(new atkNumberAttribute("id", AF_AUTOKEY | AF_AUTOINCREMENT));

     $this->add(new atkmanytoonerelation("id_organization", "organization.organization", AF_SEARCHABLE | AF_RELATION_AUTOLINK | AF_LARGE));

      $this->add(new atkAttribute("code", AF_SEARCHABLE));   

      $this->add(new atkAttribute("name", AF_SEARCHABLE));   
  
      $this->add(new atkTextAttribute("description", AF_SEARCHABLE));   
  	  	
     $this->setOrder($this->Name);
      $this->setTable($this->_table);
    }

    function descriptor_def()
    {
      return "[name]";
    }
}
?>