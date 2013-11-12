<?php
useattrib("atkNumberAttribute");
useattrib("atkTextAttribute");

class department extends atkNode
{
  var $_module  = "master";
  var $_node    = "department";
  var $_table   = "employee_department";


    function department()
    {
      $this->atkNode($this->_node, NF_ADD_LINK);
  	
      $this->add(new atkNumberAttribute("id",AF_AUTOKEY | AF_AUTOINCREMENT));
  	
      $this->add(new atkAttribute("name",AF_OBLIGATORY | AF_SEARCHABLE));
	  
      $this->add(new atkTextAttribute("description", AF_SEARCHABLE));

      $this->add(new atkNumberAttribute("id_org", AF_HIDE | AF_FORCELOAD));      
  	  	
      $user = getUser();
      $this->addFilter($this->_table.".id_org = '".$user['employer_id']."'");
      $this->setOrder($this->Name);
      $this->setTable($this->_table);
    }

    function descriptor_def()
    {
      return "[name]";
    }

    function intial_values(){
      $user = getUser();
      $id_org = $user['employer_id'];
      return array("id_org"=>$id_org);
    }

    function initial_values(){
      $user = getUser();
      $id_org = $user['employer_id'];

      return array("id_org" => $id_org);
    }
}
?>