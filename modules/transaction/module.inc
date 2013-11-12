<?php

class mod_transaction extends atkModule {

    var $moduleName = "transaction";
    var $namaMenu   = "Transaction";

    function getMenuItems() {
      $user = getUser();
      $id = $user['id'];

      /*
      * Hide menu for admin
      */

      if (!empty($id)) {    	
        $this->menuitem($this->namaMenu, "", "main");
        $this->menuitem("Journal", dispatch_url($this->moduleName . ".journal", "admin"), $this->namaMenu, array($this->moduleName . ".journal", "admin")); 
      }
    }

    function getNodes() {
        registerNode($this->moduleName . ".journal", array("admin", "add", "edit", "delete", "select", "search"));
        registerNode($this->moduleName . ".attachment", array("admin", "add", "edit", "delete","document"));
    }

}

?>