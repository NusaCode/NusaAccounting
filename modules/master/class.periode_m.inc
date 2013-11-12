<?php
userelation("atkmanytoonerelation");
useattrib("atkNumberAttribute");
useattrib("atkTextAttribute");

class periode_m extends atkNode{
  var $_module  = "master";
  var $_node    = "periode_m";
  var $_table   = "periode_month";

function periode_m(){
    $this->atkNode($this->_node, NF_ADD_LINK | NF_MRA | NF_TRACK_CHANGES);
  
    $this->add(new atkNumberAttribute("id", AF_AUTOKEY));

    $this->add(new atkAttribute("name"));

    $this->add(new atkManyToOneRelation("id_year", "master.periode_y", AF_HIDE_LIST|AF_FORCE_LOAD| AF_READONLY));

    $this->add(new atkListAttribute("month", array("January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"), array("01","02","03","04","05","06","07","08","09","10","11","12"),AF_LIST_NO_NULL_ITEM | AF_READONLY_EDIT));

    $this->add(new atkListAttribute("status", array("Close","Open","Close_Permanent"), array("0","1","99"),AF_LIST_NO_NULL_ITEM));

    $this->add(new atkdummyattribute("jarak_atas","<br>", AF_HIDE_LIST));

    $this->add(new atkdummyattribute("garis","<hr>", AF_HIDE_LIST));

    $this->add(new atkCreatedByAttribute("created_by", AF_HIDE_LIST));

    $this->add(new atkCreateStampAttribute("created_on", AF_HIDE_LIST)); 

    $this->add(new AtkUpdatedByAttribute("last_modified_by", AF_HIDE_LIST));

    $this->add(new atkUpdateStampAttribute("last_modified_on", AF_HIDE_LIST));   

    $this->setOrder("month");
    $this->setTable($this->_table);
  }

  function descriptor_def(){
    return "[name]";
  }

    function descriptorFields()
  {
    return array("id", "name", "id_year");
  }
  
  function postUpdate($record){
      $user=&atkgetuser();
      $idor = $user['employer_id'];
      $status = $record['status'];
      $year   = $record['id_year']['year'];
      $month  = $record ['month'];
      
      
        if ((strlen($month) < 2)){
            $month = "0".$record['trans_date']['month'];
        }       
      
      $db   = atkGetDb();
      
      $db->query("UPDATE journal SET status_period = '" . $status . "' WHERE DATE_FORMAT(trans_date, '%Y') = '".$record[id_year][year]."'
            AND DATE_FORMAT(trans_date, '%m') = '".$record[month]."' AND id_org = '".$idor."'");
      $db->commit;
  }

  function recordActions($rec, &$actions, &$mraactions) {
    $id_x   = $rec['id'];
    $year_x = $rec['id_year']['year'];
    $idyear_x = $rec['id_year']['id'];


    $db = &atkGetDb();
    $user=&atkgetuser();
    $id_org = $user['employer_id'];

    $rows = $db->getrows("SELECT * FROM periode_month where id='" . $rec['id'] . "'");
     $mraactions = array();
     $mraactions['delete']               = 'delete';
     $mraactions['close_permanent']      = 'close_permanent';

     //Action saat status '99' (Close_Permanent), maka akan hanya bisa view saja.
     if ($rows[0]['status'] == '99') {
        unset($actions['edit']);
        unset($actions['delete']);
     }

    $get = $db->getrows("SELECT a.id, a.year, a.`id_org`,
                            b.id id_month, b.month, b.id_year
                            FROM periode_year a, periode_month b
                            WHERE a.id = b.`id_year`
                            AND EXISTS (SELECT * FROM journal c
                            WHERE c.id_org = a.`id_org`
                            AND SUBSTR(c.trans_date,1,4) = a.`year`
                            AND SUBSTR(trans_date,6,2) = b.`month`
                            ) AND id_org = '$id_org'
                            ORDER BY a.year,b.month");
    foreach ($get as $getrows) {
      $id      = $getrows['id'];
      $year    = $getrows['year'];
      $org     = $getrows['id_org'];
      $idm     = $getrows['id_month'];
      $mon     = $getrows['month'];
      $idy     = $getrows['id_year'];

    //Action saat periode sudah ada transaction, maka tidak bisa di delete.
     if( ($id_x == $idm) && ($idyear_x == $idy)){
        unset($actions['delete']);
        unset($mraactions['delete']);
     }
    }
  }


  function action_close_permanent() {
        $id = $this->m_postvars['atkselector'];

        foreach ($id as $pk) {
            $db = &atkGetDb();
            $db->query("UPDATE periode_month SET status = '99' WHERE " . $pk);
            $db->commit();
        }
  $this->redirect();        
    }

  function month_validate(&$record, $mode){
     $db   = &atkGetDb();
     $user = &atkgetuser();

    $employer_id = $user['employer_id'];
    $year        = $record['id_year']['id'];
    $month_input = $record['month'];
    $orgcode     = $record['atkorgrec']['month'];

     $que  = $db->getrows("SELECT * FROM periode_month a, periode_year b WHERE a.`id_year` = b.`id` AND b.`id` = '$year' AND b.`id_org` = '$employer_id' AND a.`month` = '$month_input'");
     // var_dump("SELECT * FROM periode_month a, periode_year b WHERE a.`id_year` = b.`id` AND b.`id` = '$year' AND b.`id_org` = '$employer_id'");exit;
      $month    = $que[0]['month'];
      $year_id  = $que[0]['year'];

     if($mode == 'add' && (!empty($que))){
        atkTriggerError($record, $this->getAttribute('month'), 'This month already exists in '.$year_id.'');
     }elseif($mode == 'update' && $orgcode <> $month_input){
        atkTriggerError($record, $this->getAttribute('month'), 'This month already exists in '.$year_id.'');
     }
  }
 

  function status_validate(&$record, $mode){
     $db   = &atkGetDb();
     $user = &atkgetuser();

     $id       = $record['id'];
     $code     = $record['status'];
     $orgcode  = $record['atkorgrec']['status'];
     $year     = $record['id_year']['id'];
     $employer_id = $user['employer_id'];


     $que  = $db->getrows("SELECT a.`status`, a.`id` FROM periode_month a, periode_year b WHERE a.`id_year` = b.`id` AND a.`status` = 1 AND b.`id_org` = '$employer_id'");
     $status   = $que[0]['status'];

        if($status == 1 && $code == 1){ //--Cek Periode Sudah di Open atau Belum
           atkTriggerError($record, $this->getAttribute('status'), 'There is Periode already "Open", Please "Close" before edit');
        }

          if($code == 0 && $orgcode <> $code){
            $id_year  = $record['id_year'];
            $id_month = $record['month'];
            $db       = atkGetDb();
            $que3     = $db->getrows("SELECT COUNT(posting) as posting FROM journal WHERE posting = 0 
              AND DATE_FORMAT(trans_date, '%Y') = '".$record[id_year][id]."'
              AND DATE_FORMAT(trans_date, '%m') = '".$record[month]."'");
            $posting = $que3[0]['posting'];

              if($posting > 0){
                echo '<script>
                    var $quest = confirm("Ada ' . $posting . ' Journal not yet Posted.\nLanjutkan Proses?");
                    if($quest == true){
                      history.go(-2);
                    }else{
                      history.go(-1);
                    }
                </script>';
              }          
          }        
        return true;
  }      
}
?>