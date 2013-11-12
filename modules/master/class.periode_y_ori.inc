<?php
userelation("atkManyToOneRelation");
useattrib("atkNumberAttribute");
useattrib("atkTextAttribute");

class periode_y extends atkNode{
  var $_module  = "master";
  var $_node    = "periode_y";
  var $_table   = "periode_year";

function periode_y(){
    $this->atkNode($this->_node, NF_ADD_LINK | NF_MRA | NF_EDITAFTERADD);
	
    $this->add(new atkNumberAttribute("id", AF_AUTOINCREMENT | AF_HIDE));

    $this->add(new atkNumberAttribute("year", AF_OBLIGATORY | AF_SEARCHABLE | AF_PRIMARY | AF_UNIQUE))->setLabel("Year");

    $this->add(new atkDummyAttribute("bulan",null,AF_HIDE_ADD | AF_HIDE_LIST));

    $this->add(new atkOneToManyRelation("Periode", "master.periode_m","id_year",  AF_HIDE_LIST))->setLabel("Month");

    $this->add(new atkOneToManyRelation("Flag", "master.periode_m","gen_flag", AF_HIDE_ADD | AF_HIDE | AF_HIDE_LIST));

    $this->add(new atkDummyAttribute("status"));


    $this->setOrder("year");
    $this->setTable($this->_table);     
  }

  function descriptor_def(){
    return "[year]";
  }

  function bulan_edit($record){ 
    $url= session_url("dispatch.php?atknodetype=master.periode_y&atkaction=genmonths&diy=".$record['year'], SESSION_NESTED);
    $a = "<a href='javascript:void(0);' onmouseover='window.status=\"hide link\";return true;' onclick='window.location.href=\"".$url."\"'> Click Here for Generate all Months </a>";
    return $a;
  }

  function action_genmonths() {
    $id_year = $_REQUEST['diy'];
    $db = atkGetDb();
        $node = atkGetNode('master.periode_m'); 

        
        for ($i=1; $i<=13; $i++) {            
            $record2['id_year'] = $id_year;
                if(strlen($i)<>2){
                    $m='0'.$i;
                }else{
                  $m=$i;
                }
            $record2['month'] = $m;
            $record2['name'] =  date('M-y', mktime(0,0,0, $m + 1, 0, $id_year));
            $record2['status'] = 0;
            $record2['gen_flag'] = '1';
            $node->addDb($record2);
        }  
        $this->redirect();
  }

  function status_display($record, $mode){
    $year = $record['year'];
    $db = atkGetDb();
    $res = $db->getrows("SELECT statusx FROM
                      (SELECT a.*,IFNULL(b.status,0) AS statusx FROM periode_month a
                      LEFT JOIN
                      (SELECT * FROM periode_month
                      WHERE `status` <>0) b
                      ON (a.id_year=b.id_year))a
                      WHERE id_year = $year");
    $status = $res[0]['statusx'];    
    // var_dump($status);
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
}
?>