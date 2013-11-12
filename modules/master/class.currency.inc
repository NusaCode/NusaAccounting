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
      $this->atkNode($this->_node, NF_ADD_LINK | NF_MRA | NF_LOCK);
  	
      $this->add(new atkNumberAttribute("id", AF_AUTOKEY | AF_AUTOINCREMENT));

      $this->add(new atkAttribute("code", AF_SEARCHABLE | AF_OBLIGATORY));   

      $this->add(new atkAttribute("name", AF_SEARCHABLE | AF_OBLIGATORY));   

      $this->add(new atkManyToOneRelation("id_country", "master.location", AF_SEARCHABLE | AF_RELATION_NO_NULL_ITEM | AF_RELATION_AUTOLINK))->setlabel("Country ")   
            ->addDestinationFilter("location.idparent IS NULL");

      $this->add(new atkAttribute("symbol", AF_SEARCHABLE))->setlabel("Symbol ");

      $this->add(new atkNumberAttribute("rate", AF_SEARCHABLE | AF_OBLIGATORY))->setlabel("Rate ");

      $this->add(new atkTextAttribute("desc", AF_SEARCHABLE));   

      $this->add(new atkAttribute("id_org", AF_HIDE | AF_FORCELOAD));

      $this->add(new atkdummyattribute("jarak_atas","<br>", AF_HIDE_LIST));

      $this->add(new atkdummyattribute("garis","<hr>", AF_HIDE_LIST));

      $this->add(new atkCreatedByAttribute("created_by", AF_HIDE_LIST));

      $this->add(new atkCreateStampAttribute("created_on", AF_HIDE_LIST)); 

      $this->add(new AtkUpdatedByAttribute("last_modified_by", AF_HIDE_LIST));

      $this->add(new atkUpdateStampAttribute("last_modified_on", AF_HIDE_LIST));
      // var_dump($_SESSION['idOrganization']);
      $user = getUser();
      if(!empty($_SESSION['idOrganization'])) {
        $this->addFilter($this->_table.".id_org = '".$_SESSION['idOrganization']."'");}
      else{
        $this->addFilter($this->_table.".id_org = '".$user[employer_id]."'");	  	
      }
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

  function intial_values(){
      $user = getUser();
      $id_org = $user['employer_id'];
      return array("id_org"=>$id_org);
    }

  function initial_values(){
      $user = getUser();
      
      if(!empty($_SESSION['idOrganization'])) {
        $id_org = $_SESSION['idOrganization'];}
      else{
        $id_org = $user['employer_id'];
      }

      return array("id_org" => $id_org);
  }
}
?>