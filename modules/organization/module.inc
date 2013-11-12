<?php

  class mod_organization extends achievoModule
  {
    function getNodes()
    {
      registerNode("organization.organization", array("admin", "add", "edit", "delete", "document"));
    }

    function getMenuItems()
    {
      // $this->menuitem("organizationmanagement",dispatch_url("organization.organization", "admin"),"main",array("organization.organization","admin"),500);
      // $this->menuitem("organization_admin", dispatch_url("organization.organization", "admin"),"organizationmanagement", array("organization.organization","admin"));
    }

    function getDependencies($mode)
    {
      return array("person");
    }

    function search($expression)
    {
      $res = array();
      $custnode = &atkGetNode("organization.organization");
      $recs = $custnode->searchDb($expression);

      $res["organizations"] = $this->recLinks($recs, "organization.organization");

      $contactnode = &atkGetNode("organization.contact");
      $res["contacts"] = $this->recLinks($contactnode->searchDb($expression), "organization.contact");

      $contractnode = &atkGetNode("organization.contracts");
      $res["contracts"] = $this->recLinks($contractnode->searchDb($expression), "organization.contracts");

      return $res;
    }
  }
?>
