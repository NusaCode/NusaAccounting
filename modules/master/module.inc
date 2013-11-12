<?php
  class mod_master extends atkModule
  {
    function getNodes()
    {
      // registerNode("master.coa", array("admin", "add", "edit", "delete", "stats", "view_all"));
      // registerNode("master.coa_jenis", array("admin", "view_all"));
      // registerNode("master.journal_type", array("admin", "add", "edit", "delete", "stats", "view_all"));
      registerNode("master.journal_type", array("admin", "add", "edit", "delete","view_all"));
      // registerNode("master.transaction_type_trans", array("admin","add","edit","delete"));
      // registerNode("master.transaction_recur", array("admin","add","edit","delete"));
      registerNode("master.transaction_type", array("admin", "add", "edit", "delete"));
      registerNode("master.department", array("admin", "add", "edit", "delete"));
      // registerNode("master.department", array("admin", "add", "edit", "delete" , "grantall"));
      // registerNode("master.employee_cost_center", array("admin", "view_all"));
      registerNode("master.currency", array("admin","add","edit","delete"));
      registerNode("master.location", array("admin","add","edit","delete"));
      registerNode("master.periode_y", array("admin","add","edit","delete"));
      registerNode("master.periode_m", array("admin","add","edit","delete"));
      // registerNode("master.org_bank", array("admin","add","edit","delete", "Bank"));
      // registerNode("master.cus_bank", array("admin","add","edit","delete"));
      // registerNode("master.ven_bank", array("admin","add","edit","delete"));


    }

    function getMenuItems()
    {
      $user = getUser();
      $id = $user['id'];

      /*
      * Hide menu for admin
      */

      if (!empty($id)) {
        $this->menuitem("master_Data");
        // $this->menuitem("COA", dispatch_url("master.coa", "admin"), "master_Data", array("master.coa", "admin"));

        $this->menuitem("Journal_Type", dispatch_url("master.journal_type", "admin"), "master_Data", array("master.journal_type", "admin"));

        $this->menuitem("Transaction_Type", dispatch_url("master.transaction_type", "admin"), "master_Data", array("master.transaction_type", "admin"));

        // $this->menuitem("Auto_Transaction_Recurring", dispatch_url("master.transaction_recur", "admin"), "master_Data", 
        //                 array("master.transaction_recur", "admin"));

        $this->menuitem("Department", dispatch_url("master.department", "admin"),"master_Data", array("master.department", "admin"));

        // $this->menuitem("Bank", dispatch_url("master.org_bank", "admin"),"master_Data", array("master.org_bank", "admin"));

        // $this->menuitem("Cost_Center / Job", dispatch_url("master.employee_cost_center", "admin"), "master_Data", array("master.employee_cost_center", "admin")); 

        $this->menuitem("Currency", dispatch_url("master.currency", "admin"), "master_Data", array("master.currency", "admin"));

        $this->menuitem("Country", dispatch_url("master.location", "admin"), "master_Data", array("master.location", "admin"));

        $this->menuitem("Periode", dispatch_url("master.periode_y", "admin"), "master_Data", array("master.periode_y", "admin"));

        $this->menuitem("-","","main",true,620);
      }
    }

    function getDependencies($mode)
    {
      return array("Department");
    }
  }
?>
