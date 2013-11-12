<?php
useattrib("atkNumberAttribute");
useattrib("atkTextAttribute");
userelation("atkOneToManyRelation");

class org_bank extends atkNode{
  var $_module  = "master";
  var $_node    = "org_bank";
  var $_table   = "org_bank";


    function org_bank(){
      $this->atkNode($this->_node, NF_ADD_LINK | NF_MRA);
  	
      $this->add(new atkNumberAttribute("id_bank", AF_AUTOKEY | AF_AUTOINCREMENT));

      $this->add(new atkAttribute("bank_code", AF_SEARCHABLE | AF_OBLIGATORY))->setLabel("Bank Code ");   

      $this->add(new atkAttribute("bank_name", AF_SEARCHABLE | AF_OBLIGATORY ))->setLabel("Bank Name ");   

      $this->add(new atkAttribute("bank_acc", AF_SEARCHABLE | AF_OBLIGATORY))->setLabel("Bank Account ");

      $this->add(new atkTextAttribute("bank_add", AF_SEARCHABLE))->setLabel("Bank Address ");

      $this->add(new atkManyToOneRelation("id_org","organization.organization", AF_HIDE));
  	  	
      $this->setOrder($this->id_bank);
      $this->setTable($this->_table);
    }

    function descriptor_def()
    {
      return "[bank_code] - [bank_name]";
    }
    
    public function descriptorFields() 
	  {
         return array ("bank_code","bank_name","bank_acc", "id_org.id");
    }

    function preAdd(&$record){
      $user = getUser();
      $id_org    = $record['id_org']['id'];
      $bank_code = $record['bank_code'];
      $db = atkGetDb();
      $res = $db->getrows("SELECT bank_code as bank, id_org as org FROM org_bank WHERE id_org = '$id_org' AND bank_code = '$bank_code'");
        $bank = $res[0]['bank'];
        $org  = $res[0]['org'];

      if($bank_code == $bank && $id_org == $org){
        atkTriggerError($record, $this->getAttribute('bank_code'),'Bank Code already exist');
      }
    }

    function postAdd(&$record){
      $id_bank   = $record['id_bank'];
      $bank      = $record['bank_name'];
      $id_org    = $record['id_org']['id'];

      $db = atkGetDb();
      $res = $db->getrows("SELECT COUNT(coa_code) count FROM coa_bank_org WHERE coa_parent = '11120' and id_org = '".$id_org."'");
      $res1 = $res[0]['count'];
      
        if($res1 != 0) {
          $count = $res1 + 1;
          $nextCC = '11120'.$count.'0';
        }else if ($res1 == 0){
          $count = 10;
          $nextCC = '11120'.$count;
        } 
      

      $db->query("INSERT INTO coa_bank_org (coa_code, coa_parent, coa_name, coa_jenis, id_org, id_bank)
                            VALUES ('".$nextCC."', '11120', '".$bank."', 'a', $id_org, $id_bank)");
      $db->commit();                          
    }

    function postDelete(&$record){
      $id_bank   = $record['id_bank'];
      $bank_name = $record['bank_name'];
      $id_org    = $record['id_org']['id'];

      $db = atkGetDb();
        $db->query("DELETE FROM coa_bank_org WHERE id_org = '".$id_org."' AND id_bank = '".$id_bank."' AND coa_name = '".$bank_name."' ");
      $db->commit();
    }

    function postUpdate(&$record){
      $id_bank   = $record['id_bank'];
      $bank_name = $record['bank_name'];
      $id_org    = $record['id_org']['id'];

      $db = atkGetDb();
        $db->query("UPDATE coa_bank_org SET coa_name = '".$bank_name."' WHERE id_org = '".$id_org."' AND id_bank = '".$id_bank."'");

    }

   function recordActions($rec, &$actions, &$mraactions){
    // $db = atkGetDb();

    // $id_bank  = $rec['atkprimkey'];
    // $ex = explode('=', $id_bank);

    // $rows = $db->getrows("SELECT id_org FROM org_bank WHERE id_bank = ".$ex[1]."");
    // $id_org = $rows[0]['id_org'];
   
    // // $que = $db->getrows("SELECT DISTINCT(id_org) as org FROM  coa  WHERE id_org = '".$id_org."'");
    // // $id_org2 = $rows['org'];
    // // var_dump($id_org2);

    //   if($id_org == $id_org2){
    //     unset($actions['delete']);
    //   }
    }
}
?>