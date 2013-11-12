<?php
userelation("atkManyToOneRelation");
useattrib("atkNumberAttribute");
useattrib("atkTextAttribute");

class periode_y extends atkNode{
  var $_module  = "master";
  var $_node    = "periode_y";
  var $_table   = "periode_year";
  var $_order   = "year DESC";

function periode_y(){
    $action = array("genmonths");
    $this->addAllowedAction($action); 
    $user = getUser();
    $this->atkNode($this->_node, NF_ADD_LINK | NF_EDITAFTERADD | NF_LOCK);
	
    $this->add(new atkNumberAttribute("id", AF_AUTOINCREMENT | AF_HIDE | AF_PRIMARY));

    $this->add(new atkNumberAttribute("year", AF_OBLIGATORY | AF_SEARCHABLE | AF_UNIQUE));

    $this->add(new atkDummyAttribute("bulan",null,AF_HIDE_ADD | AF_HIDE_LIST));

    $this->add(new atkOneToManyRelation("Periode", "master.periode_m","id_year",  AF_HIDE_LIST));

    $this->add(new atkDummyAttribute("status"));

    $this->add(new atkNumberAttribute("id_org", AF_HIDE | AF_FORCELOAD));


    $this->setOrder($this->_order);
    $this->addFilter($this->_table.".id_org = '".$user[employer_id]."'");
    $this->setTable($this->_table);     
  }

  function descriptor_def(){
    return "[year]";
  }

  function bulan_edit($record){ 
    $url= session_url("dispatch.php?atknodetype=master.periode_y&atkaction=genmonths&diy=".$record['year']."&idye=".$record['id']."&idor=".$record['id_org'], SESSION_NESTED);
    $a = "<a href='javascript:void(0);' onmouseover='window.status=\"hide link\";return true;' onclick='window.location.href=\"".$url."\"'><input type='button' name='unposting' value='Generate All Periode'> </a>";
    return $a;
  }

  function initial_values()
  { 
     $user   = getUser();
     $id_org = $user['employer_id'];
     return array("id_org"=> $id_org);
  }

  function action_genmonths() {
    $id_year = $_REQUEST['diy'];
    $id      = $_REQUEST['idye'];
    $id_org  = $_REQUEST['idor'];

    $node    = atkGetNode('master.periode_m'); 
    $db      = atkGetDb();
        
  //   //---Check Exists Periode---//
  //   $periode = $db->getrows("SELECT COUNT(*) AS pin FROM periode_month a, periode_year b WHERE b.`id` = a.`id_year` AND a.`id_year` = '$id' AND b.`id_org` = '$id_org'");
  //     $pin = $periode[0]['pin'];

  //   if(!empty($pin)){
  //     $db->query("DELETE FROM periode_month where id_year = '$id'");

  //       for ($i=1; $i<=13; $i++) {            
  //           $record2['id_year'] = $id;
  //               if(strlen($i)<>2){
  //                   $m='0'.$i;
  //               }else{
  //                 $m=$i;
  //               }
  //           $record2['month'] = $m;
  //           $record2['name'] =  date('M-y', mktime(0,0,0, $m + 1, 0, $id_year));
  //           $record2['status'] = 0;
  //           $node->addDb($record2);
  //       } $this->redirect();
  //   }else{
  //       for ($i=1; $i<=13; $i++) {            
  //           $record2['id_year'] = $id;
  //               if(strlen($i)<>2){
  //                   $m='0'.$i;
  //               }else{
  //                 $m=$i;
  //               }
  //           $record2['month'] = $m;
  //           $record2['name'] =  date('M-y', mktime(0,0,0, $m + 1, 0, $id_year));
  //           $record2['status'] = 0;
  //           $node->addDb($record2);
  //       }  
  //       $this->redirect();
  //   }
  // }

      // ---Check Exists Periode---//

    $periode = $db->getrows("SELECT * FROM list_month WHERE bulan NOT IN(SELECT a.`month` FROM periode_month a WHERE a.`id_year` = '$id')");
      if(!empty($periode)){
        foreach ($periode as $key => $value) {
            $record2['month'] = $value['bulan'];
            $record2['name'] =  date('M-y', mktime(0,0,0, $value['bulan'], 1, $id_year));
            $record2['status'] = 0;
            $record2['id_year'] = $id;
            $node->addDb($record2);
        }
            $node->addDb($record2);  // untuk meng-add lagi record terakhir yg tidak ke add dilooping foreach

        $this->redirect();
      }else{
        $alert = "<script>alert('All Periode Month already generated!');history.go(-1);</script>";
        echo $alert;
      }
    }

  function status_display($record, $mode){
    $year = $record['id'];
    $db = atkGetDb();
    $res = $db->getrows("SELECT statusx FROM
                      (SELECT a.*,IFNULL(b.status,0) AS statusx FROM periode_month a
                      LEFT JOIN
                      (SELECT * FROM periode_month
                      WHERE `status` <>0) b
                      ON (a.id_year=b.id_year))a
                      WHERE id_year = $year");

    $status = $res[0]['statusx'];    
    if($status == '0'){
      $status = "Close";
    }elseif($status == '1'){
       $status = "Open";
    }elseif ($status == '99') {
      $status = "Close Permanen"; 
    }else{
      $status = "-";
    }
    return $status;
  }

  function recordActions($rec, &$actions, &$mraactions) {
    $db     = &atkGetDb();
    $user   = &atkgetuser();

    $id     = $rec['id'];
    $idyear = $rec['id']['id_year'];
    $id_org = $user['employer_id'];

    $get = $db->getrows("SELECT a.`id`, a.`year`, a.`id_org`,
                            b.`id` id_month, b.`month`, b.`id_year`
                            FROM `periode_year` a, `periode_month` b
                            WHERE a.`id` = b.`id_year`
                            AND EXISTS (SELECT * FROM `journal` c
                            WHERE c.`id_org` = a.`id_org`
                            AND SUBSTR(c.`trans_date`,1,4) = a.`year`
                            AND SUBSTR(`trans_date`,6,2) = b.`month`
                            ) AND `id_org` = '$id_org'
                            ORDER BY a.`year`,b.`month`");
    foreach ($get as $getRows) {
      $idy     = $getRows['id_year'];

      if($id == $idy){
          unset($actions['delete']);
      }
    }

  }
}
?>