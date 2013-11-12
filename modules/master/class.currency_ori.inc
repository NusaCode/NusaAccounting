<?php
useattrib("atkNumberAttribute");
useattrib("atkTextAttribute");

class currency extends atkNode
{
  var $_module  = "master";
  var $_node    = "currency";
  var $_table   = "currency";


    function currency()
    {
      $this->atkNode($this->_node, NF_ADD_LINK | NF_MRA);
  	
      $this->add(new atkNumberAttribute("id", AF_AUTOKEY | AF_AUTOINCREMENT));

      $this->add(new atkAttribute("code", AF_SEARCHABLE | AF_OBLIGATORY));   

      $this->add(new atkAttribute("name", AF_SEARCHABLE | AF_OBLIGATORY));   

      $this->add(new atkManyToOneRelation("id_country", "master.location", AF_SEARCHABLE | AF_RELATION_NO_NULL_ITEM | AF_RELATION_AUTOLINK))->setlabel("Country")   
            ->addDestinationFilter("location.idparent IS NULL");

      $this->add(new atkAttribute("symbol", AF_SEARCHABLE));

      $this->add(new atkNumberAttribute("rate", AF_SEARCHABLE | AF_OBLIGATORY));

      $this->add(new atkTextAttribute("desc", AF_SEARCHABLE));   
  	  	
     $this->setOrder($this->Name);
      $this->setTable($this->_table);
    }

    function descriptor_def()
    {
      return "[code] - [name]";
    }
    
    public function descriptorFields() 
	{
        return array ("code","name","rate");
    }     
}
?>