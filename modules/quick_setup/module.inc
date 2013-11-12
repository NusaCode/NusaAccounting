<?php

class mod_quick_setup extends atkModule {

    var $moduleName = "quick_setup";
    var $namaMenu   = "Quick Setup";

    var $moduleNameOrganization = "organization";
    var $namaMenuOrganization   = "organization";


    function getMenuItems() {
        $this->menuitem($this->namaMenu, "", "main");

        $this->menuitem("Organization", dispatch_url($this->moduleNameOrganization . ".organization", "admin"), 
        $this->namaMenu, array($this->moduleNameOrganization . ".organization", "admin"));

        // $this->menuitem("COA", dispatch_url("master.coa", "admin"), 
        // $this->namaMenu, array("master.coa", "admin"));

        // $this->menuitem("COA_&_Opening_Balance", dispatch_url("master.coa", "admin"), 
        // $this->namaMenu, array("master.coa", "admin"));
      /*
      * Hide menu for admin
      */
      $user = getUser();
      $id = $user['id'];

      if (!empty($id)) {
        $this->menuitem("Vendor", dispatch_url($this->moduleName . ".vendor", "admin"), $this->namaMenu, array($this->moduleName . ".vendor", "admin"));        
        $this->menuitem("Customer", dispatch_url($this->moduleName . ".customer", "admin"), $this->namaMenu, array($this->moduleName . ".customer", "admin"));

        $this->menuitem("COA_&_Opening_Balance", dispatch_url($this->moduleName . ".coa_org", "admin"), $this->namaMenu, array($this->moduleName . ".coa_org", "admin"));
      }

    }

    function getNodes() {
        registerNode($this->moduleNameOrganization  . ".organization", array("admin", "add", "edit", "delete", "select", "search"));
        // registerNode($this->moduleName . ".cash_bank", array("admin", "add", "edit", "delete", "select", "search"));
        // registerNode($this->moduleName . ".hutang", array("admin", "add", "edit", "delete", "select", "search"));
        // registerNode($this->moduleName . ".piutang", array("admin", "add", "edit", "delete", "select", "search"));
        registerNode($this->moduleName . ".vendor", array("admin", "add", "edit", "delete", "select", "search"));
        registerNode($this->moduleName . ".customer", array("admin", "add", "edit", "delete", "select", "search"));
        registerNode($this->moduleName . ".coa_org", array("admin", "add", "edit", "delete", "select", "search"));
    }

}

?>