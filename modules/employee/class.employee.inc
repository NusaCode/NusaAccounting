<?php
/**
 * This file is part of the Achievo distribution.
 * Detailed copyright and licensing information can be found
 * in the doc/COPYRIGHT and doc/LICENSE files which should be
 * included in the distribution.
 *
 * @package achievo
 * @subpackage employee
 *
 * @copyright (c)2008 Ibuildings B.V.
 * @license http://www.achievo.org/licensing Achievo Open Source License
 *
 * @version $Revision: 5530 $
 * $Id: class.employee.inc 5530 2009-04-07 19:56:28Z yury $
 */

userelation("atkmanytoonerelation");
userelation("atkonetomanyrelation");
userelation("atkmanyboolrelation");
useattrib("atklistattribute");
useattrib("atkdummyattribute");
useattrib("atkpasswordattribute");
useattrib("atkdateattribute");
useattrib('employee.adminlangselectattribute');

include_once (moduleDir("person")."class.person.inc");
include_once (moduleDir("utils")."class.dateutil.inc");

/**
 * Class for managing employees
 * @package achievo
 * @subpackage employee
 */
class employee extends person
{
  function employee()
  {
    global $ATK_VARS,$g_user;

    $this->person("employee", NF_EDITAFTERADD | NF_LOCK);

    // In employee edit screen, we hide most fields in the add screen.
    foreach (array_keys($this->m_attribList) as $attribname)
    {
      if (!in_array($attribname, array("userid","lastname", "firstname","email")))
      {
        $p_attrib = &$this->getAttribute($attribname);
        $p_attrib->m_flags|=AF_HIDE_ADD;
      }
      elseif($attribname=="userid")
      {
        $p_attrib = &$this->getAttribute($attribname);
        $p_attrib->m_flags|=AF_OBLIGATORY;
      }
    }

    $this->addFilter("person.role='employee'");
    // $this->add(new atkDateAttribute("birthdate","","", 0, date("Ymd"), AF_HIDE_LIST));
    $this->add(new atkDateAttribute("birthdate", "Y M d", "Y M d", 0, 0, AF_HIDE_LIST, 30));   

    $this->add(new atkAttribute("bankaccount", AF_HIDE_LIST|AF_HIDE_ADD), "finance");
    $this->add(new atkAttribute("socialsecuritynumber", AF_HIDE_LIST|AF_HIDE_ADD), "finance");

    $user = getUser();
// var_dump($_SESSION['idOrganization']);
    $employer_id = $this->add(new atkManyToOneRelation("employer_id","organization.organization",AF_HIDE_LIST|AF_OBLIGATORY));
    // if(!empty($_SESSION['idOrganization'])) {
    //   $employer_id->addDestinationFilter("organization.type = 2 AND organization.id = '".$_SESSION['idOrganization']."'");
    // }else{
    //   $employer_id->addDestinationFilter("organization.type = 2 AND organization.id = '".$user[employer_id]."'");
    // }

    $this->add(new atkManyToOneRelation("department","employee.department",AF_HIDE_ADD|AF_HIDE_LIST|AF_RELATION_AUTOLINK));

    // you can't be your own supervisor neither can a nonactive employee be a supervisor
    $preFilter = new atkManyToOneRelation("supervisor","employee.employee",AF_HIDE_ADD|AF_HIDE_LIST|AF_RELATION_AUTOLINK);
    $preFilter->setDestinationFilter("person.userid !='[userid]'");
    $preFilter->setUseFilterForAddLink(false);

    $this->add($preFilter);
      
    $this->add(new atkManyToOneRelation("functionlevel", "employee.functionlevel",AF_HIDE_ADD|AF_HIDE_LIST|AF_RELATION_AUTOLINK));

    //$this->add(new atkManyToOneRelation("entity", "employee.profile",AF_RELATION_AUTOLINK|AF_HIDE_ADD));
    $rel = &$this->add(new atkManyBoolRelation("profiles", "employee.employeerole", "employee.profile", AF_HIDE_LIST|AF_MANYBOOL_AUTOLINK), "account");
    $rel->setLocalKey("employee_id");
    $rel->setRemoteKey("role_id");

    // If we are in employee administration mode, we show all users. Otherwise, we only show active users.
    $this->add(new atkListAttribute("status", array("active","nonactive"), array(), AF_HIDE_LIST|AF_HIDE_ADD|AF_FORCE_LOAD|AF_LIST_NO_NULL_ITEM), "account");

    if ((atkArrayNvl($ATK_VARS, "atknodetype", "") == "employee.employee") && in_array(atkArrayNvl($ATK_VARS, "atkaction", ""), array("admin")))
    {
      // $statusfilter = "nonactive";
      $statusfilter = ($this->getView() == "active") ? "active" : "nonactive";
      $this->addFilter("person.status",$statusfilter);
    }

    if(!empty($_SESSION['idOrganization'])) {
      $this->addFilter("person.employer_id = '".$_SESSION['idOrganization']."'");
    }else{
      $this->addFilter("person.employer_id = '".$user[employer_id]."'");
    }


    $this->add(new atkRadioAttribute("status_login",array("Yes","No"), array("Y", "N"), AF_LIST_NO_NULL_ITEM | AF_HIDE_ADD), "account");
    // $this->add(new adminLangSelectAttribute('lng',AF_HIDE_LIST), "account");

    // $this->add(new atkOneToManyRelation("usercontract","employee.usercontracts","userid",AF_HIDE_LIST|AF_HIDE_ADD));

    //$this->add(new useridAttribute("userid" ,AF_OBLIGATORY|AF_UNIQUE|AF_SEARCHABLE), 1); // first field

    $this->add(new atkdummyattribute("jarak_atas","<br>", AF_HIDE_LIST));

    $this->add(new atkdummyattribute("garis","<hr>", AF_HIDE_LIST));

    $this->add(new atkCreatedByAttribute("created_by", AF_HIDE_LIST|AF_FORCE_LOAD));

    $this->add(new atkCreateStampAttribute("created_on", AF_HIDE_LIST)); 

    $this->add(new AtkUpdatedByAttribute("last_modified_by", AF_HIDE_LIST|AF_FORCE_LOAD));

    $this->add(new atkUpdateStampAttribute("last_modified_on", AF_HIDE_LIST));

    if (in_array("db",explode(",",strtolower(atkconfig('authentication')))))
      $this->addPasswordAttribute();

    $this->add(new atkAttribute("role", AF_OBLIGATORY|AF_READONLY|AF_HIDE, 50)); // discriminator.

    $this->m_securityMap["deactivate"] = "edit"; // If you may edit, you may also deactivate.

    $this->setOrder("lastname");
    $this->setDescriptorTemplate("[lastname], [firstname] ([userid])");

    // Added by Ellyas
    // Oct 24, 2013
    // To make those attributes are editable in list view
    // $this->setEditableListAttributes(array("lastname", "firstname"));
  }

  function addPasswordAttribute()
  {
    $this->add(new atkDummyAttribute("passwordexplanation", atktext("password_leaveblankifunchanged"), AF_HIDE_ADD|AF_HIDE_LIST|AF_HIDE_SEARCH|AF_HIDE_VIEW), "account");
    $passwordrestrictions = array(
      "minsize" => atkconfig("password_minsize", 8),
      "minupperchars" => atkconfig("password_minupperchars", 1),
      "minlowerchars" => atkconfig("password_minlowerchars", 1),
      "minalphabeticchars" => atkconfig("password_minalphabeticchars", 1),
      "minnumbers" => atkconfig("password_minnumbers", 1),
      "minspecialchars" => atkconfig("password_minspecialchars", 0)
    );
    $this->add(new atkPasswordAttribute("password", false, AF_HIDE_LIST|AF_PASSWORD_NOVALIDATE, 40, $passwordrestrictions), "account")
         ->getToolTip();
  }

  function initial_values()
  {
    $initial = array();
    $initial["role"] = "employee";
    $initial["status"] = "active";

    return $initial;
  }

  /**
   * Are we in 'active' emps or 'archive' mode?
   */
  function getView()
  {
    global $g_sessionManager;
    $view = $g_sessionManager->stackVar("view");
    if ($view=="")
    {
      $view = "active";
    }
    // var_dump($view);
    return $view;
  }

  function action_admin($handler)
  {

    $view = $this->getView();
    if ($view=="active")
    {
      $this->addFilter("person.status","active");
    }
    return $handler->action_admin();
  }

  function adminFooter()
  {
    $view = $this->getView();

    if ($view=="active")
    {
      return atktext("onlyactiverecordsareshown")." ".href(dispatch_url($this->atknodetype(),$this->m_action,array("view"=>"nonactive")),
                                                           atktext('clicktoviewarchive', $this->m_module, $this->m_type))."<br>";
    }
    else
    {
      return atktext("youareinthearchive")." ".href(dispatch_url($this->atknodetype(),$this->m_action,array("view"=>"active")),
                                                    atktext('clicktoviewactiverecords', $this->m_module, $this->m_type))."<br>";
    }
  }

  function recordActions($rec, &$actions, &$mraactions)
  {
    // Get the userid of the user currently logged in
    $user = getUser();
    $userid = atkArrayNvl($user, "id", -1);

    // Actve users may be deactivated, but not the logged in user.
    if ($rec["status"] == "active" && $rec["id"]!=$userid)
    {
      $actions["deactivate"] = session_url(dispatch_url($this->atkNodeType(),"deactivate",array("atkselector"=>"[pk]")), SESSION_NESTED);
    }

    // Prevent users from deleting themselves when they are logged in.
    if($rec["id"] == $userid)
    {
      unset($actions["delete"]);
    }
  }

  function action_deactivate(&$handler)
  {
    $select = $this->m_postvars["atkselector"];
    $query = "UPDATE person SET status='nonactive' WHERE $select";

    // Verify that the selector or id were not tampered with before passing on to the db
    if(preg_match("/person\.id='\d+'/i", $select) === 1)
    {
      $db = &atkGetDb();
      $db->query($query);
    }
    else
    {
      // TODO: give the name of the module, the logged userid and the IP address
      // of the offending user in the debug entry so it gets logged properly
      atkdebug("SQL injection attack detected in 'action_deactivate', not executed. The selector was '$select' and the resulting query would have been '$query'", true);
    }

    $this->redirect();
  }


  // function rowColor($record)
  // {
  //   if ($record["status"]=="active")
  //   {
  //     $contractnode = &atkGetNode("employee.usercontracts");

  //     $endlesscontracts = $contractnode->countDb("usercontract.enddate IS NULL AND usercontract.userid='{$record["id"]}'");

  //     if ($endlesscontracts == 0)
  //     {
  //       $contract = $contractnode->getMostRecentContract($record["id"]);

  //       $enddate = isset($contract["enddate"]) ? (dateutil::arr2str($contract["enddate"])) : "";

  //       if (!count($contract)||($enddate!=""&&$enddate<date("Ymd")))
  //       {
  //         return array(COLOR_ERROR, COLOR_HIGHLIGHT_ERROR);
  //       }
  //       else if ($enddate!=""&&dateutil::date_diff(date("Ymd"), $enddate)<14)
  //       {
  //         return array(COLOR_WARNING, COLOR_HIGHLIGHT_WARNING);
  //       }
  //     }
  //   }
  // }

  function postAdd($record)
  {
    // $pimitems = &atkGetNode("pim.userpimitems");
    // $pimitems->addDefaultPimItemsForUser($record['id']);
    $this->removeBirthdaysCache();
    // Create scheduler userprefs
    // $userprefs = &atkGetNode("scheduler.scheduler_userpreferences");
    // $userprefs->createUserPreferences($record['id']);
    return true;
  }

  function postUpdate($record)
  {
    $this->removeBirthdaysCache();
    return true;
  }
  // function preUpdate($record)
  // {
  //   var_dump($record);
  //   return true;
  // }

  function postDel($record)
  {
    $this->removeBirthdaysCache();
    // Remove scheduler userprefs
    // $userprefs = &atkGetNode("scheduler.scheduler_userpreferences");
    // $userprefs->deleteDb("userid='".$record['id']."'");
    return true;
  }

  /**
   * Remove birthdays cache file
   */
  function removeBirthdaysCache()
  {
    atkimport("atk.utils.atktmpfile");
    $file = new atkTmpFile("employee_birthdays.inc");
    if($file->exists())
      $file->remove();
  }

  /**
   * Get birthdays from all employees
   *
   * @return array Array with all employees birthdays
   */
  function getBirthdates()
  {
    atkimport("atk.utils.atktmpfile");
    $file = new atkTmpFile("employee_birthdays.inc");
    if(!$file->exists())
    {
      $birthday_recs = $this->selectDb("birthdate IS NOT NULL AND status='active'","month(birthdate), dayofmonth(birthdate)","","",array("firstname","lastname","birthdate"));
      $items = array();
      foreach($birthday_recs as $birthday)
      {

        $day = intval($birthday["birthdate"]["day"]);
        $month = intval($birthday["birthdate"]["month"]);
        $name = $birthday["firstname"]." ".$birthday["lastname"];
        atkdebug("$day - $month - $name");
        $items[$month][$day][] = array("name"=>$name,"birthday"=>$birthday["birthdate"]);
      }

      $file->writeAsPhp("birthdays",$items);
    }
    else
    {
      include $file->getPath();
    }

    return $birthdays;
  }


}

?>
