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

class organization extends atkNode
{

  var $_module  = "quick_setup";
  var $_node    = "organization";
  var $_table   = "organization";
  
  function organization(){

    $this->atkNode($this->_node, NF_ADD_LINK | NF_EDITAFTERADD | NF_LOCK);
    // $session = &atkSessionManager::getSession();
    // var_dump($session);

    $this->add(new atkNumberAttribute("id" ,AF_AUTOKEY));
	
    $this->add(new atkAttribute("organizationcode", AF_SEARCHABLE | AF_OBLIGATORY));
	
    $this->add(new atkAttribute("name",AF_SEARCHABLE|AF_OBLIGATORY, 100));

    $this->add(new atkAttribute("tax_name", AF_SEARCHABLE));

    $this->add(new atkManyToOneRelation("id_currency","master.currency", AF_HIDE_LIST | AF_SEARCHABLE | AF_RELATION_AUTOLINK | AF_HIDE_ADD));
	
    $this->add(new atkListAttribute("type", array("user"), array("2"), AF_HIDE_LIST | AF_READONLY));
	
    $this->add(new atkAttribute("visit_address", AF_SEARCHABLE|AF_HIDE_LIST | AF_HIDE_ADD, 100),"detail.address");
	
    $this->add(new atkAttribute("visit_address2", AF_HIDE_LIST | AF_HIDE_ADD, 100),"detail.address");
	
    $this->add(new atkAttribute("visit_zipcode", AF_HIDE_LIST | AF_HIDE_ADD, 6),"detail.address");
	
    $this->add(new atkAttribute("visit_city", AF_HIDE_LIST | AF_HIDE_ADD, 100),"detail.address");
	
    $this->add(new atkAttribute("visit_state", AF_HIDE_LIST | AF_HIDE_ADD, 100),"detail.address");
	
    $this->add(new atkAttribute("visit_country", AF_HIDE_LIST | AF_HIDE_ADD, 100),"detail.address");

    $this->add(new atkAttribute("tax_address", AF_HIDE_LIST | AF_HIDE_ADD, 100),"detail.tax");

    $this->add(new atkAttribute("tax_country", AF_HIDE_LIST | AF_HIDE_ADD, 100),"detail.tax");

    $this->add(new atkAttribute("tax_city", AF_HIDE_LIST | AF_HIDE_ADD, 100),"detail.tax");

    $this->add(new atkAttribute("tax_state", AF_HIDE_LIST | AF_HIDE_ADD, 100),"detail.tax");

    $this->add(new atkAttribute("tax_zipcode", AF_HIDE_LIST | AF_HIDE_ADD, 100),"detail.tax");

    $this->add(new atkAttribute("invoice_address", AF_SEARCHABLE|AF_HIDE_LIST | AF_HIDE_ADD, 100),"detail.invoice");
  
    $this->add(new atkAttribute("invoice_address2", AF_HIDE_LIST | AF_HIDE_ADD, 100),"detail.invoice");
  
    $this->add(new atkAttribute("invoice_zipcode", AF_HIDE_LIST | AF_HIDE_ADD, 20),"detail.invoice");
  
    $this->add(new atkAttribute("invoice_city", AF_HIDE_LIST | AF_HIDE_ADD, 100),"detail.invoice");
  
    $this->add(new atkAttribute("invoice_state", AF_HIDE_LIST | AF_HIDE_ADD, 100),"detail.invoice");
  
    $this->add(new atkAttribute("invoice_country", AF_HIDE_LIST | AF_HIDE_ADD, 100),"detail.invoice");

    $this->add(new atkAttribute("mail_address", AF_SEARCHABLE|AF_HIDE_LIST | AF_HIDE_ADD, 100),"detail.mail");
	
    $this->add(new atkAttribute("mail_address2", AF_HIDE_LIST | AF_HIDE_ADD, 100),"detail.mail");
	
    $this->add(new atkAttribute("mail_zipcode", AF_HIDE_LIST | AF_HIDE_ADD, 20),"detail.mail");
	
    $this->add(new atkAttribute("mail_city", AF_HIDE_LIST | AF_HIDE_ADD, 100),"detail.mail");
	
    $this->add(new atkAttribute("mail_state", AF_HIDE_LIST | AF_HIDE_ADD, 100),"detail.mail");
	
    $this->add(new atkAttribute("mail_country", AF_HIDE_LIST | AF_HIDE_ADD, 100), "detail.mail");

    $this->add(new atkAttribute("phone",AF_SEARCHABLE, 20));
	
    $this->add(new atkAttribute("fax",AF_SEARCHABLE, 20));
	
    $this->add(new atkEmailAttribute("email", false ,AF_SEARCHABLE | AF_HIDE_LIST | AF_FORCE_LOAD, 50));
	
    $this->add(new atkAttribute("website",AF_HIDE_ADD|AF_HIDE_LIST, 100)); 
	
    $this->add(new atkAttribute("vatnumber", AF_HIDE_LIST, 25));

    $this->add(new atkAttribute("no_pkp", AF_HIDE_LIST, 30));      

    $this->add(new atkDateAttribute("date_pkp", "Y M d", "Y M d", 0, 0, AF_HIDE_LIST, 30));    

    $this->add(new atkAttribute("business_type", AF_HIDE_LIST, 30)); 

    $this->add(new atkAttribute("klu_spt", AF_HIDE_LIST, 30));       
	
    $member = $this->add(new atkManyToOneRelation("member_of","organization.organization", AF_HIDE_LIST | AF_LARGE, 500));
    $member->addDestinationFilter("organization.id <> '[id]'");
    
    $this->add(new atkNumberAttribute("employees",AF_HIDE_LIST,5));

    $this->add(new atkTextAttribute("remark", array("rows"=>1), TEXT_LARGE, AF_HIDE_LIST));

    $this->add(new atkdummyattribute("jarak_atas","<br>", AF_HIDE_LIST));

    $this->add(new atkdummyattribute("garis","<hr>", AF_HIDE_LIST));

    $this->add(new atkCreatedByAttribute("created_by", AF_HIDE_LIST));

    $this->add(new atkCreateStampAttribute("created_on", AF_HIDE_LIST)); 

    $this->add(new AtkUpdatedByAttribute("last_modified_by", AF_HIDE_LIST));

    $this->add(new atkUpdateStampAttribute("last_modified_on", AF_HIDE_LIST));

    $this->add(new atkOneToManyRelation("bank","master.org_bank","id_org", AF_HIDE_LIST, AF_CASCADE_DELETE),"detail.bankAccount")->setLabel("Bank ");

    $user = getUser();
    $this->setOrder($this->name);
// var_dump($user);
    if(!empty($_SESSION['idOrganization'])) {
      $this->addFilter($this->_table.".type = 2 AND organization.id = '".$_SESSION['idOrganization']."' OR organization.member_of = '".$_SESSION['idOrganization']."'");
    }else{
      $this->addFilter($this->_table.".type = 2 AND organization.id = '".$user[employer_id]."' OR organization.member_of = '".$user[employer_id]."'");
    }

    $this->setTable($this->_table);
	  $this->setDescriptorTemplate("[member_of].[organizationcode]");

    $page = &$this->getPage();
        $page->register_scriptcode($this->openWindow());
        $page->register_scriptcode('
                $jq(document).ready(function() { 
                                                                                                  
                    $jq("#filtertitle").click(function(){
                        
                        if (!$jq("#filterform").is(":visible")) {
                          $jq("#filterform").slideDown("slow");                                                  
                        }else{
                          $jq("#filterform").slideUp("slow");
                        }
                    });
                });
        ');
  }
  public function openWindow() {
        return 'function openWindow(url) { window.open(url);  }';
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

  function getView()
  {
    $sessionManager = &atkGetSessionManager();
    $view = $sessionManager->pageVar("view");
    if (!in_array($view, array("all", "customer", "supplier")))
      $view = "all";
    return $view;
  }

    function postAdd(&$record){
      $id   = $record['id'];
      $db   = atkGetDb();
      $user = getUser();

      if (empty($user['id'])) {
      $_SESSION['idOrganization'] = $id;
      }

      $existTable = $db->getrows("SHOW TABLES LIKE 'coa_".$id."'");

      if (!empty($existTable)) {
        // $tabel = $this->_table."_".$user[employer_id];
        return true;
      }else{
        $db->query("CREATE TABLE coa_".$id." 
                (idcoa INT(11) NOT NULL, coa_code CHAR(10) NOT NULL, coa_parent CHAR(10), coa_name VARCHAR(255), coa_jenis CHAR(1), balance TINYINT(1), `desc` TEXT, date_ob DATE, opening_balance DECIMAL(20,2), created_by INT(11), created_on DATETIME, last_modified_by INT(11), last_modified_on DATETIME)");
        $db->commit();
        return true;
      }
    }

  // function recordActions($rec, &$actions, &$mraactions){
  //   $id_organization = $rec['id'];
  //   $db = atkGetDb();
  //   $rows = $db->getrows("SELECT * FROM coa WHERE id_org = '$id_organization'");

    
  //   if($rows[0]['id_org'] == $id_organization){
  //     unset($actions['delete']);
  //   }
  // }
    
   function recordActions($rec, &$actions, &$mraactions){
    $db = atkGetDb();
    $user = getUser();
    
    if(!empty($user[employer_id])){
      $existTable = $db->getrows("SHOW TABLES LIKE 'coa_".$user[employer_id]."'");
        $rows = $db->getrows("SELECT * FROM coa_".$user[employer_id]."");

        if (!empty($rows)) {
          unset($actions['delete']);  
        }
    }
  }

  function action_admin(&$handler)
  {
    $view = $this->getView();
    if ($view != "all")
      $this->addFilter("organization.type='$view'");
    return $handler->action_admin();
  }

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

  function initial_values(){
    return array("type"=>2);
  }
}

?>
