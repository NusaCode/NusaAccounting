<?php
  class mod_report extends achievoModule
  {
    var $moduleName = "report";
    var $namaMenu   = "Report";
      
    function getNodes()
    {
      registerNode($this->moduleName . ".master_list_coa", array("admin"));
      registerNode($this->moduleName . ".master_list_jurnal_type", array("admin"));
      registerNode($this->moduleName . ".master_list_departement", array("admin"));
      // registerNode($this->moduleName . ".master_list_cost_center", array("admin", "add", "edit", "delete", "stats", "view_all"));
      registerNode($this->moduleName . ".journal_report", array("journal_report"));
      registerNode($this->moduleName . ".general_ledger", array("general_ledger"));
      registerNode($this->moduleName . ".general_ledger_elly", array("general_ledger"));
      registerNode($this->moduleName . ".balance_sheet", array("balance_sheet"));
      registerNode($this->moduleName . ".profit_loss", array("profit_loss"));
      registerNode($this->moduleName . ".capital_statement", array("capital_statement"));
      // registerNode($this->moduleName . ".baru", array("baru2"));
      
    }

    function getMenuItems()
    {
      $user = getUser();
      $id = $user['id'];

      /*
      * Hide menu for admin
      */

      if (!empty($id)) {
       $this->menuitem($this->namaMenu, "", "main");
       // $this->menuitem("Master_List", "", $this->namaMenu, "");
       $this->menuitem("COA_List", dispatch_url($this->moduleName . ".master_list_coa", "admin"), $this->namaMenu, array($this->moduleName . ".master_list_coa", "admin")); 
       $this->menuitem("Journal_Type_List", dispatch_url($this->moduleName . ".master_list_jurnal_type", "admin"), $this->namaMenu, array($this->moduleName . ".master_list_jurnal_type", "admin")); 
       $this->menuitem("Department_List", dispatch_url($this->moduleName . ".master_list_departement", "admin"), $this->namaMenu, array($this->moduleName . ".master_list_departement", "admin")); 
       // $this->menuitem("Cost_Center_List", dispatch_url($this->moduleName . ".master_list_cost_center", "admin"), $this->namaMenu, array($this->moduleName . ".master_list_cost_center", "admin"));
       
       $this->menuitem("Journal_Report", dispatch_url($this->moduleName . ".journal_report", "journal_report"), $this->namaMenu, array($this->moduleName . ".journal_report", "journal_report"));
       $this->menuitem("General_Ledger", dispatch_url($this->moduleName . ".general_ledger", "general_ledger"), $this->namaMenu, array($this->moduleName . ".general_ledger", "general_ledger"));
       $this->menuitem("balance_sheet", dispatch_url($this->moduleName . ".balance_sheet", "balance_sheet"), $this->namaMenu, array($this->moduleName . ".balance_sheet", "balance_sheet"));
       $this->menuitem("Profit_&_Loss", dispatch_url($this->moduleName . ".profit_loss", "profit_loss"), $this->namaMenu, array($this->moduleName . ".profit_loss", "profit_loss"));
       $this->menuitem("Capital_Statement", dispatch_url($this->moduleName . ".capital_statement", "capital_statement"), $this->namaMenu, array($this->moduleName . ".capital_statement", "capital_statement"));
       // $this->menuitem("coba", dispatch_url($this->moduleName . ".baru", "baru2"), $this->namaMenu, array($this->moduleName . ".baru", "baru2")); 
      }

    }

    }

?>