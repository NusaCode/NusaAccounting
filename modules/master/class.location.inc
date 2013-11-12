<?php

class location extends atkNode{

    var $_module  = "master";
    var $_node    = "location";
    var $_table   = "location";

    function location(){
        $this->atkNode($this->_node, NF_NO_EXTENDED_SEARCH | NF_ADD_LINK);

    	  //-- ID & ROWCOUNTER --------------------------------------------------------------------
        $this->add(new atkAttribute("id", AF_AUTOKEY | AF_AUTOINCREMENT));
        $this->add(new atkRowCounter("no", null, 1));
        //-- ID & ROWCOUNTER --------------------------------------------------------------------

        // $this->add(new atkManyToOneTreeRelation("idparent", "master.location", AF_PARENT));
        $this->add(new atkAttribute("name", AF_SEARCHABLE | AF_OBLIGATORY));    
    	  	

       $this->setTable($this->_table);
       $this->setOrder("name");    
   }

    function descriptor_def(){
      return "[name]";
    }
}
?>