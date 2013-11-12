<?php

useattrib("atktextattribute");
useattrib("atkdummyattribute");
useattrib("atknumberattribute");
useattrib("atkparserattribute");
useattrib("atkdocumentattribute");
useattrib("atklistattribute");
userelation("atkonetomanyrelation");
userelation("atkmanytoonerelation");
useattrib("atkcreatedbyattribute");
useattrib("atkCreateStampAttribute");
useattrib("atkupdatedbyattribute");
useattrib("atkupdatestampattribute");
useattrib("atktabbedpane");

class vendor extends atkNode
{

  var $_module  = "quick_setup";
  var $_node    = "vendor";
  var $_table   = "organization";
  
  function vendor(){

    $this->atkNode($this->_node, NF_ADD_LINK | NF_EDITAFTERADD | NF_LOCK);

    $this->add(new atkNumberAttribute("id" ,AF_AUTOKEY));
	
    $this->add(new atkAttribute("organizationcode", AF_SEARCHABLE | AF_OBLIGATORY))->setLabel("Vendor Code ");
	
    $this->add(new atkAttribute("name",AF_SEARCHABLE | AF_OBLIGATORY , 100));

    $this->add(new atkAttribute("tax_name", AF_SEARCHABLE | AF_HIDE_ADD | AF_HIDE_LIST));

    $this->add(new atkManyToOneRelation("id_currency","master.currency",  AF_SEARCHABLE | AF_OBLIGATORY | AF_RELATION_AUTOLINK));
	
    $this->add(new atkListAttribute("type", array("customer", "vendor", "user"), array("0","1","2"), AF_HIDE_LIST | AF_READONLY_EDIT | AF_HIDE_ADD));
	
    $this->add(new atkAttribute("visit_address", AF_SEARCHABLE | AF_HIDE_LIST | AF_HIDE_ADD, 100),"detail.address");
	
    $this->add(new atkAttribute("visit_address2", AF_HIDE_LIST | AF_HIDE_ADD, 100),"detail.address");
	
    $this->add(new atkAttribute("visit_zipcode", AF_HIDE_LIST | AF_HIDE_ADD, 6),"detail.address");
	
    $this->add(new atkAttribute("visit_city", AF_HIDE_LIST | AF_HIDE_ADD, 100),"detail.address");
	
    $this->add(new atkAttribute("visit_state", AF_HIDE_LIST | AF_HIDE_ADD, 100),"detail.address");
	
    $this->add(new atkAttribute("visit_country", AF_HIDE_LIST | AF_HIDE_ADD, 100),"detail.address");

    $this->add(new atkAttribute("mail_address", AF_SEARCHABLE|AF_HIDE_LIST | AF_HIDE_ADD, 100),"detail.mail");
	
    $this->add(new atkAttribute("mail_address2", AF_HIDE_LIST | AF_HIDE_ADD, 100),"detail.mail");
	
    $this->add(new atkAttribute("mail_zipcode", AF_HIDE_LIST | AF_HIDE_ADD, 20),"detail.mail");
	
    $this->add(new atkAttribute("mail_city", AF_HIDE_LIST | AF_HIDE_ADD, 100),"detail.mail");
	
    $this->add(new atkAttribute("mail_state", AF_HIDE_LIST | AF_HIDE_ADD, 100),"detail.mail");
	
    $this->add(new atkAttribute("mail_country", AF_HIDE_LIST | AF_HIDE_ADD, 100), "detail.mail");

    $this->add(new atkAttribute("invoice_address", AF_SEARCHABLE|AF_HIDE_LIST | AF_HIDE_ADD, 100),"detail.invoice");
	
    $this->add(new atkAttribute("invoice_address2", AF_HIDE_LIST | AF_HIDE_ADD, 100),"detail.invoice");
	
    $this->add(new atkAttribute("invoice_zipcode", AF_HIDE_LIST | AF_HIDE_ADD, 20),"detail.invoice");
	
    $this->add(new atkAttribute("invoice_city", AF_HIDE_LIST | AF_HIDE_ADD, 100),"detail.invoice");
	
    $this->add(new atkAttribute("invoice_state", AF_HIDE_LIST | AF_HIDE_ADD, 100),"detail.invoice");
	
    $this->add(new atkAttribute("invoice_country", AF_HIDE_LIST | AF_HIDE_ADD, 100),"detail.invoice");
	
    $this->add(new atkAttribute("tax_address", AF_HIDE_LIST | AF_HIDE_ADD | AF_HIDE_ADD, 100),"detail.tax");

    $this->add(new atkAttribute("tax_country", AF_HIDE_LIST | AF_HIDE_ADD, 100),"detail.tax");

    $this->add(new atkAttribute("tax_city", AF_HIDE_LIST | AF_HIDE_ADD, 100),"detail.tax");

    $this->add(new atkAttribute("tax_state", AF_HIDE_LIST | AF_HIDE_ADD, 100),"detail.tax");

    $this->add(new atkAttribute("tax_zipcode", AF_HIDE_LIST | AF_HIDE_ADD, 100),"detail.tax");
	
    $this->add(new atkAttribute("phone",AF_SEARCHABLE | AF_HIDE_ADD | AF_HIDE_LIST, 20));
	
    $this->add(new atkAttribute("fax",AF_SEARCHABLE | AF_HIDE_ADD | AF_HIDE_LIST, 20));
	
    $this->add(new atkAttribute("email",AF_SEARCHABLE | AF_HIDE_ADD | AF_HIDE_LIST, 50));
	
    $this->add(new atkAttribute("website",AF_HIDE_ADD | AF_HIDE_LIST, 100));
	
    // $this->add(new atkAttribute("bankaccount", AF_HIDE_LIST | AF_HIDE_ADD, 30),"detail.bankaccount");
	
    // $this->add(new atkAttribute("bankaccount2", AF_HIDE_LIST | AF_HIDE_ADD, 30),"detail.bankaccount");
	
    // $this->add(new atkAttribute("bankaccount3", AF_HIDE_LIST | AF_HIDE_ADD, 30),"detail.bankaccount");
	
    // $this->add(new atkAttribute("bankaccount4", AF_HIDE_LIST | AF_HIDE_ADD, 30),"detail.bankaccount");

    // $this->add(new atkAttribute("no_faktur_pajak", AF_HIDE_LIST | AF_HIDE_ADD, 30),"detail.bankaccount");    
	
    $this->add(new atkAttribute("vatnumber", AF_HIDE_LIST | AF_HIDE_ADD, 25));

    $this->add(new atkAttribute("no_pkp", AF_HIDE_LIST | AF_HIDE_ADD, 30));      

    $this->add(new atkDateAttribute("date_pkp", "Y M d", "Y M d", 0, 0, AF_HIDE_LIST | AF_HIDE_ADD, 30));    

    $this->add(new atkAttribute("business_type", AF_HIDE_LIST | AF_HIDE_ADD, 30)); 

    $this->add(new atkAttribute("klu_spt", AF_HIDE_LIST | AF_HIDE_ADD, 30))->setlabel("KLU SPT");       
	
    $member_of = $this->add(new atkManyToOneRelation("member_of","quick_setup.vendor",AF_HIDE_LIST|AF_LARGE | AF_HIDE_ADD));
    $member_of ->addDestinationFilter("organization.type = 1 AND organization.id <> '[id]'");

    // $this->add(new atkNumberAttribute("employees",AF_HIDE_LIST | AF_HIDE_ADD,5));
  
    // $this->add(new atkAttribute("revenue",AF_HIDE_LIST | AF_HIDE_ADD,5));

    $this->add(new atkTextAttribute("remark", TEXT_LARGE, AF_HIDE_LIST | AF_HIDE_ADD));

    $this->add(new atkListAttribute("status", array("Active", "Non Active"), array("Y","N"), AF_LIST_NO_NULL_ITEM));

    $this->add(new atkdummyattribute("jarak_atas","<br>", AF_HIDE_LIST | AF_HIDE_ADD));

    $this->add(new atkdummyattribute("garis","<hr>", AF_HIDE_LIST | AF_HIDE_ADD));

    $this->add(new atkCreatedByAttribute("created_by", AF_HIDE_LIST));

    $this->add(new atkCreateStampAttribute("created_on", AF_HIDE_LIST)); 

    $this->add(new AtkUpdatedByAttribute("last_modified_by", AF_HIDE_LIST));

    $this->add(new atkUpdateStampAttribute("last_modified_on", AF_HIDE_LIST));

    $this->add(new atkOneToManyRelation("bank","master.ven_bank","id_org", AF_HIDE_LIST),"detail.bank Account")->setLabel("Bank ");
    $this->add(new atkNumberAttribute("id_org", AF_HIDE));
    $user = getUser();

    $this->setOrder($this->name);
    $this->addFilter($this->_table.".type = 1 AND organization.id_org = '".$user[employer_id]."'");
    // $this->addFilter($this->_table.".type = 1 AND organization.created_by = '".$user[id]."'");
    $this->setTable($this->_table);
    $this->setDescriptorTemplate("[member_of].[organizationcode]");
	
  }
  
  function descriptor($rec="")
  {
    if(!empty($rec))
    {
      $tpl = '[name]';
      if($rec['visit_city']!='') $tpl.=', [visit_city]';
      if($rec['organizationcode']!='') $tpl.=' ([organizationcode])';
      $this->setDescriptorTemplate($tpl);
    }
    return parent::descriptor($rec);
  }

  function descriptorFields()
  {
    return array("name", "visit_city", "organizationcode","id", "member_of");
  }

  function initial_values(){
    $user = getUser();
    return array("type"=>'1',
                 "id_org"=>$user['employer_id']);
  }

  function getView()
  {
    $sessionManager = &atkGetSessionManager();
    $view = $sessionManager->pageVar("view");
    if (!in_array($view, array("all", "customer", "supplier")))
      $view = "all";
    return $view;
  }

  function action_admin(&$handler)
  {
    $view = $this->getView();
    if ($view != "all")
      $this->addFilter("organization.type='$view'");
    return $handler->action_admin();
  }
  
  // function adminHeader()
  // {
  //   $result = "<br>" . $this->text("view"). ":";
  //   foreach (array("all", "customer", "supplier") as $filter)
  //     $result .= " " . href(dispatch_url("organization.organization", "admin", array("view"=>$filter)), $this->text($filter));
  //   $result .= "<br><br>";
  //   return $result;
  // }

  function getExportAttributeGroup($attributename)
  {
    if (strpos($attributename, "visit_") === 0) return "organization_visitaddress";
    if (strpos($attributename, "mail_") === 0) return "organization_mailaddress";
    if (strpos($attributename, "invoice_") === 0) return "organization_invoiceaddress";
  }

  function action_export(&$handler)
  {
    foreach(array("contactperson", "contracts", 'archivedcontracts', "projects", "archivedprojects", "vcard", "document") as $attrname)
    {
      $attr = &$this->getAttribute($attrname);
      $attr->addFlag(AF_HIDE);
    }
    return $handler->action_export();
  }

  function email_display($record, $mode)
  {
    $email = $record["email"];
    if (!in_array($mode, array("csv", "plain")) && $email!='')
      $email = sprintf('<a href="mailto:%1$s">%1$s</a>', $email);
    return $email;
  }

   function website_display($record, $mode)
  {
    $website = $record["website"];
    if (!in_array($mode, array("csv", "plain")) && $website!='')
      $website = '<a href="http://'.$website.'" target="_blank">'.$website.'</a>';
    return $website;
  }

  function website_edit($record, $mode)
  {
     $attr = &$this->getAttribute("website");
     $org = $attr->edit($record, $mode);
     return "http://".$org;
  }

  function archivedprojects_edit($record)
  {
    return $this->showProjects($record,"relation","archived");
  }

  function archivedprojects_display($record)
  {
    return $this->showProjects($record,"view","archived");
  }

  function showProjects($record, $mode,$status="active")
  {
    $projectnode = &atkGetNode("project.project");
    $projectnode->m_fuzzyFilters=array("project.status='$status'");
    $recs = $projectnode->selectDb("customer = ".$record["id"], "", "", $projectnode->m_listExcludes);
    if (count($recs)>0)
    {
      $rl = &atknew("atk.recordlist.atkrecordlist");
      return $rl->render($projectnode, $recs, $projectnode->defaultActions($mode), RL_NO_SEARCH|RL_NO_SORT);
    }
    return atktext("none");
  }

  function postDelete($record)
  {
    $eventlog = &atkGetNode("crm.eventlog");
    $eventlog->delete_event_history($this->atknodetype(),$record["atkprimkey"]);
    return true;
  }


}

?>
