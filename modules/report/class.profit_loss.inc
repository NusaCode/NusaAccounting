<?php
/**Author : Dimas Ardi N
*  Created Date : Oct 2013
*/
include_once (atkconfig("atkroot") . "lib/mpdf/mpdf.php");
include_once ("atk.inc");
class profit_loss extends atkNode{
    
    var $_module = "report";
    var $_node   = "profit_loss";
    var $_table  = "report_journal";

    function profit_loss() {
        $this->atkNode($this->_node, NF_READONLY | NF_NO_EXTENDED_SEARCH);
        $action = array("getPeriodeMonth","getPeriodeMonth2","profit_loss", "cetak_profit_loss");
        $this->addAllowedAction($action);    
        $this->setTable($this->_table);
    }

    function descriptor_Def() {
        return "[coa_name]";
    }

    public function openWindow() {
        return 'function openWindow(url) { window.open(url);  }';
    }

    function jsSearch(){
        if(isset($_REQUEST['show'])){
            $pmonth = $_REQUEST['pmonth'];
            $pmonth2 = $_REQUEST['pmonth2'];
        }else{
            $pmonth = null;
            $pmonth2 = null;
        }

        $content = '
                $jq(document).ready(function() { 
                    function showMonth(){
                        var id=$jq("#pyear").val();
                        var dataString = \'pyear=\'+ id + \'&pmonth='.$pmonth.'\';
                        $jq.ajax
                        ({
                            type: "POST",
                            url: "dispatch.php?atknodetype=report.profit_loss&atkaction=getPeriodeMonth&atklevel=-1&atkprevlevel=0&",
                            data: dataString,
                            cache: false,
                            success: function(html)
                            {
                            $jq("#pmonth").html(html);
                            }
                        });                        
                    }

                    function showMonth2(){
                        var id=$jq("#pyear2").val();
                        var dataString = \'pyear=\'+ id + \'&pmonth2='.$pmonth2.'\';
                        
                        $jq.ajax
                        ({
                            type: "POST",
                            url: "dispatch.php?atknodetype=report.profit_loss&atkaction=getPeriodeMonth&atklevel=-1&atkprevlevel=0&",
                            data: dataString,
                            cache: false,
                            success: function(html)
                            {
                            $jq("#pmonth2").html(html);
                            }
                        });                        
                    }

                    showMonth();
                    showMonth2();
                    $jq("#pyear").change(showMonth);
                    $jq("#pyear2").change(showMonth2);
                                                                                                  
                    $jq("#filtertitle").click(function(){
                        
                        if (!$jq("#filterform").is(":visible")) {
                            $jq("#filterform").slideDown("slow");                                                  
                              }else{
                            $jq("#filterform").slideUp("slow");
                              }
                    });
                                      
                });

        
         ';
        return $content;
    }

    function action_getPeriodeMonth(){

        $db = atkGetDb();
        $pyear = $_REQUEST["pyear"];
        $pmonth = $_REQUEST["pmonth"];
        $pmonth2 = $_REQUEST["pmonth2"];

        $getRow = $db->getrows("SELECT * FROM periode_month WHERE id_year = '".$pyear."'");
        foreach ($getRow as $key => $value) {
            if($value['month'] == $pmonth || $value['month'] == $pmonth2){
                $selected = 'selected';
            }else{
                $selected = '';
            }

            $select .= "<option value=" . $value['month'] . " ".$selected.">" . $value['name'] . "</option>";
        }
        echo $select;
    }

    function getProfitLoss($id_org, $yyyy_awal, $yyyy_akhr, $pmonth, $pmonth2){
        $db = atkGetDb();
        $yyyymm_awal  = $yyyy_awal.$pmonth;
        $yyyymm_akhir = $yyyy_akhr.$pmonth2;

        $file = "./lib/query/r_profit_loss.txt";
            $open = fopen($file, 'r+');
            $theData = fread($open, filesize($file));
            fclose($open);

            $read = str_replace('#@id_org#@', $id_org, $theData);
            $read = str_replace('#@yyyymm_awal#@', $yyyymm_awal, $read);
            $read = str_replace('#@yyyymm_akhir#@', $yyyymm_akhir, $read);

            $get_profit_loss = $db->getrows($read);
        return $get_profit_loss;
    }

    function HeaderModel($ambil_user, $pmonth, $year, $yyyy_akhr, $pmonth2){
         $isi = '<html>
                    <head>
                    <meta http-equiv="Content-Language" content="en-us">
                    <meta http-equiv="Content-Type" content="text/html; charset=windows-1252">
                    <title>Profit & Loss Statement</title>
                    <style>
                        body{font-size:8pt;}
                        table { border-collapse:collapse; }
                        td {height:25px;}
                        #garis2{border-bottom:double #000000;}
                    </style>
                    </head>
                    <body>
                        &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
                            <div style="padding: 35px; display:inline-block;">
                                <h3 align="center">' . $ambil_user[0]["name"] . ' <br> <br>
                                 Profit & Loss Statement</strong> <br> <br>
                                '.date("F Y", mktime(0, 0, 0, $pmonth, 3, $year)).' To '.date("F Y", mktime(0, 0, 0, $pmonth2, 3, $yyyy_akhr)).'
                                </h3>
                        <br><br>';
        
        return $isi;
    }

    function getModel($ambil_user, $year, $month, $model, $paramProfitLoss){
        $user = atkGetUser();
        $db   = atkGetDb();

        $page  = &atknew("atk.ui.atkpage");
        $theme = &atkTheme::getInstance();
        $page->register_style($theme->stylePath("style.css"));
        $page->register_style($theme->stylePath("recordlist.css"));
        $isi .= '<div style="padding: 20px; border: 1px solid #000000; display: inline-block;">';
        $isi .= '<table border="0" class="recordListContainer" align="center" cellpadding="8">';

        // Query dipanggil hanya untuk menampilkan data di 2 kolom pertama (COA_CODE | COA_NAME)
        $getProfitLoss = $this->getProfitLoss($paramProfitLoss['id_org'], $paramProfitLoss['yyyy_awal'], $paramProfitLoss['yyyy_akhr'], $paramProfitLoss['pmonth'], $paramProfitLoss['pmonth2']);

                    if ($model == 2){
                            $isi .='<tr ' . $no . '>
                                        <td align="right" class="recordListTd recordListTdLast" colspan="2">&nbsp;</td>';
                                foreach ($paramProfitLoss['param_year'] as $keyparam_year => $valueparam_year) {
                                        $isi .= '<td align="center" class="recordListTd recordListTdLast" style="border-left: 1px double #000000;  border-right: 1px double #000000; border-bottom: 1px double #000000; border-top: 1px double #000000;">'.date("M Y", mktime(0, 0, 0, $valueparam_year["bulan"], 3, $valueparam_year["year"])).'</td>';
                                }
                            $isi .='</tr>';
                    }
                foreach ($getProfitLoss as $key => $value) {
                    if($value["coa_code"] == '1. DAFTAR'){
                        $isi .='<tr ' . $no . '>
                                    <td align="right" class="recordListTd recordListTdLast"><b>' . $value["coa_code"] . '</b></td>
                                    <td align="left" class="recordListTd recordListTdLast"><b>' . $value["coa_name"] . '</b></td>
                                    '.$this->getModelBalance($paramProfitLoss, $value["coa_code"], $model, $value["coa_name"]).'
                                </tr>';
                    }elseif($value["coa_code"] == '2. DAFTAR'){
                        $isi .='<tr ' . $no . '>
                                    <td align="right" class="recordListTd recordListTdLast"><b>' . $value["coa_code"] . '</b></td>
                                    <td align="left" class="recordListTd recordListTdLast"><b>' . $value["coa_name"] . '</b></td>
                                    '.$this->getModelBalance($paramProfitLoss, $value["coa_code"], $model, $value["coa_name"]).'
                                </tr>';
                    }elseif($value["coa_code"] == 'SUB TOTAL'){
                        $isi .='<tr ' . $no . '>
                                    <td align="left" colspan="12"></td>
                                </tr>
                                <tr>
                                    <td align="right" class="recordListTd recordListTdLast"><b>' . $value["coa_code"] . '</b></td>
                                    <td align="left" class="recordListTd recordListTdLast"><b>' . $value["coa_name"] . '</b></td>    
                                    '.$this->getModelBalance($paramProfitLoss, $value["coa_code"], $model, $value["coa_name"]).'                       
                                </tr><tr><td colspan="12" class="recordListTd recordListTdLast"></td>&nbsp;</tr>';
                    }elseif($value["coa_code"] == 'TOTAL'){
                            $isi .='<tr ' . $no . '>
                                    <td align="right" class="recordListTd recordListTdLast"><b>' . $value["coa_code"] . '</b></td>
                                    <td align="left" class="recordListTd recordListTdLast"><b>' . $value["coa_name"] . '</b></td>
                                    '.$this->getModelBalance($paramProfitLoss, $value["coa_code"], $model, $value["coa_name"]).'                           
                                </tr>';
                    }else{
                        $isi .='<tr ' . $no . '>
                                    <td align="left"></td>
                                    <td align="left" class="recordListTd recordListTdLast">' . $value["coa_name"] . '</td>
                                    '.$this->getModelBalance($paramProfitLoss, $value["coa_code"], $model, $value["coa_name"]).'
                                </tr>';
                    }
                }
            $isi .= "</table>
                        </div>
                            <br>
                            <br>
                                </div>";

            return $isi;
        }
    function footerModel(){
        $isi .='            
                        </body>
               </html> 
            ';
        return $isi;
    }

        function getModelBalance($paramProfitLoss, $coa_code, $model, $coa_name){
            if ($model == 1) { //summary
                $getProfitLoss2 = $this->getProfitLoss($paramProfitLoss['id_org'], $paramProfitLoss['yyyy_awal'], $paramProfitLoss['yyyy_akhr'], $paramProfitLoss['pmonth'], $paramProfitLoss['pmonth2']);

                return $this->setModelBalance($getProfitLoss2, $coa_code, $coa_name, $model);
            }else{ // permonth
                $content = "";
                foreach ($paramProfitLoss['param_year'] as $key => $value) {
                    $getProfitLoss2 = $this->getProfitLoss($paramProfitLoss['id_org'], $value['year'], $value['year'], $value['bulan'], $value['bulan']);

                    $content .= $this->setModelBalance($getProfitLoss2, $coa_code, $coa_name, $model);
                }
                return $content;
            }
        }

        public function setModelBalance($getProfitLoss2, $coa_code, $coa_name, $model){
                if($model == 1){
                    foreach ($getProfitLoss2 as $key2 => $value2) {
                        if($value2['coa_code'] == '1. DAFTAR' && $value2['coa_code']==$coa_code && $value2['coa_name']==$coa_name){
                            $isi ='
                                        <td align="right" class="recordListTd recordListTdLast">' . $value2['balance'] . '</td>'; 
                        }elseif($value2['coa_code'] == '2. DAFTAR' && $value2['coa_code']==$coa_code && $value2['coa_name']==$coa_name){
                            $isi ='
                                        <td align="right" class="recordListTd recordListTdLast">' . $value2['balance'] . '</td>';
                        }elseif($value2['coa_code'] == 'SUB TOTAL' && $value2['coa_code']==$coa_code && $value2['coa_name']==$coa_name){
                            $isi ='
                                        <td align="right" class="recordListTd recordListTdLast">' . $value2['balance'] . '</td>';
                        }elseif($value2['coa_code'] == 'TOTAL' && $value2['coa_code']==$coa_code && $value2['coa_name']==$coa_name){
                            $isi ='<td align="right" class="recordListTd recordListTdLast">' . $value2['balance'] . '</td>';
                        }elseif($value2['coa_code']==$coa_code && $value2['coa_name']==$coa_name){
                            $isi ='<td align="right" class="recordListTd recordListTdLast">' . $value2['balance'] . '</td>';
                        }
                    }
                }else{
                    foreach ($getProfitLoss2 as $key2 => $value2) {
                        if($value2['coa_code'] == '1. DAFTAR' && $value2['coa_code']==$coa_code && $value2['coa_name']==$coa_name){
                            $isi ='
                                        <td align="right" class="recordListTd recordListTdLast" style="border-left: 1px double #000000;  border-right: 1px double #000000; border-top: 1px double #000000;">' . $value2['balance'] . '</td>'; 
                        }elseif($value2['coa_code'] == '2. DAFTAR' && $value2['coa_code']==$coa_code && $value2['coa_name']==$coa_name){
                            $isi ='
                                        <td align="right" class="recordListTd recordListTdLast" style="border-left: 1px double #000000;  border-right: 1px double #000000; border-top: 1px double #000000;">' . $value2['balance'] . '</td>';
                        }elseif($value2['coa_code'] == 'SUB TOTAL' && $value2['coa_code']==$coa_code && $value2['coa_name']==$coa_name){
                            $isi ='
                                        <td align="right" class="recordListTd recordListTdLast" style="border-left: 1px double #000000;  border-right: 1px double #000000; border-bottom: 1px double #000000; border-top: 1px double #000000;">' . $value2['balance'] . '</td>';
                        }elseif($value2['coa_code'] == 'TOTAL' && $value2['coa_code']==$coa_code && $value2['coa_name']==$coa_name){
                            $isi ='<td align="right" class="recordListTd recordListTdLast" style="border-left: 1px double #000000;  border-right: 1px double #000000; border-bottom: 1px double #000000; border-top: 1px double #000000;">' . $value2['balance'] . '</td>';
                        }elseif($value2['coa_code']==$coa_code && $value2['coa_name']==$coa_name){
                            $isi ='<td align="right" class="recordListTd recordListTdLast" style="border-left: 1px double #000000;  border-right: 1px double #000000; border-bottom: 1px double #000000;">' . $value2['balance'] . '</td>';
                        }
                    }
                }
                return $isi;
        }

    function formSearch($option1, $option2, $option3, $option4, $option5, $org, $pyear, $pmonth, $pyear2, $pmonth2, $model){   

        $url = session_url(dispatch_url('report.profit_loss', 'cetak_profit_loss',array('org' => $org,'pyear' => $pyear,'pyear2' => $pyear2,'pmonth'=>$pmonth,'pmonth2'=>$pmonth2, 'model'=>$model)), SESSION_NESTED);
            if (isset($_REQUEST['show'])) {
                $document = '<input type="button" name="button" value="Download PDF" onclick="javascript:openWindow(\'' . $url . '\')">';
                $document = '<a href="javascript:void(0);" onmouseover="window.status=\'hide link\';return true;" onclick="window.location.href=\''.$url.'\'""><input type="button" name="button" value="Download PDF"></a>';
            }
        $content  = "<div id='filter'><h4>+ <a style='text-decoration:underline;cursor:pointer;' id='filtertitle'>Action</a></h4>";
        $content .= "<form method='POST' id='filterform' style='display:yes;'>
                        <input type='hidden' name=atknodetype value=report.profit_loss />
                        <input type='hidden' name=atkaction value=profit_loss />
                        
                        <table cellpadding='2' cellspacing='2' align='center' style='margin-top:10px;' border='0'>
                                        <tr>
                                            <td>Organization</td>
                                            <td>: <select name='org' id='org'> " .$option1. "</select>
                                            </td>
                                        </tr>
                                        <tr>
                                            <td>Periode From</td>
                                            <td>: <select name='pyear' id='pyear'>" . $option2 ."</select>
                                            <select name='pmonth' id='pmonth'>" .$option3. "</select>
                                            </td>
                                        </tr>
                                        <tr>
                                            <td>Periode To</td>
                                            <td>: <select name='pyear2' id='pyear2'>" . $option4 ."</select>
                                            <select name='pmonth2' id='pmonth2'>" .$option5. "</select>
                                            </td>
                                        </tr>
                                        <tr>
                                            <td>Model Type</td>
                                            <td>: <input type='radio' name='model' id='model' value='1' checked> Summary
                                                  <input type='radio' name='model' id='model' value='2'> Per-Month
                                            </td>
                                        </tr>
                                        <tr>    
                                            <td colspan='3'><input type=submit name='show' value='Submit' class='btn_save'>&nbsp;&nbsp;" . $document . "</td>
                                        </tr>
                        </table>        
                     </form>
                     </div>       
         ";
         return $content;
    }

    function adminheader() {
        $page = &atknew("atk.ui.atkpage");
        $page->register_scriptcode($this->jsSearch());

        $db = atkGetDb();
        $user = getUser();
        if(!empty($user["id"])){
            $org = $user['employer_id'];
            if(isset($_REQUEST['show'])){
                $org      = $_REQUEST['org'];
                $pyear    = $_REQUEST['pyear'];
                $pmonth   = $_REQUEST['pmonth'];
                $pyear2   = $_REQUEST['pyear2'];
                $pmonth2  = $_REQUEST['pmonth2'];
                $model    = $_REQUEST['model'];
            }

            //---Ambil Organization
            $getOrg = $db->getrows("SELECT * FROM organization WHERE type=2 and id ='".$org."'");
            foreach ($getOrg as $key => $value) {
                if($value['id'] == $org){
                    $selected1 = 'selected';
                }else{
                    $selected1 = '';
                }
                $option1 .= "<option value='".$value['id']."' ".$selected1.">".$value['name']."</option>";
            }

            //---Ambil Year From
            $yearRecord = $db->getrows("SELECT a.`year`, a.`id` FROM periode_year a, periode_month b WHERE a.`id` = b.`id_year` AND a.`id_org`='".$user[employer_id]."' GROUP BY a.`year` ORDER BY a.`year` DESC");
                foreach ($yearRecord as $dataRow2) {
                    if($dataRow2['id'] == $pyear){
                        $selected2 = 'selected';
                    }else{
                        $selected2 = '';
                    }
                $option2 .= "<option value='" . $dataRow2['id'] . "' ".$selected2.">" . $dataRow2['year'] . "</option>";
            }
            
            //---Ambil Month From
            $monthRecord = $db->getrows("SELECT * FROM periode_month WHERE id_year='".$pyear."'");
                foreach ($monthRecord as $dataRow3) {
                    if($dataRow3['month'] == $pmonth){
                        $selected3 = 'selected';
                    }else{
                        $selected3 = '';
                    }
                $option3 .= "<option value='" . $dataRow3['month'] . "' ".$selected3.">" . $dataRow3['name'] . "</option>";
            }

            //---Ambil Year To
            $yearRecordTo = $db->getrows("SELECT a.`year`, a.`id` FROM periode_year a, periode_month b WHERE a.`id` = b.`id_year` AND a.`id_org`='".$user[employer_id]."' GROUP BY a.`year` ORDER BY a.`year` DESC");
                foreach ($yearRecordTo as $dataRow4) {
                    if($dataRow4['id'] == $pyear2){
                        $selected4 = 'selected';
                    }else{
                        $selected4 = '';
                    }
                $option4 .= "<option value='" . $dataRow4['id'] . "' ".$selected4.">" . $dataRow4['year'] . "</option>";
            }

            //---Ambil Month To
            $monthRecordTo = $db->getrows("SELECT * FROM periode_month WHERE id_year='".$pyear2."'");
                foreach ($monthRecordTo as $dataRow5) {
                    if($dataRow5['month'] == $pmonth2){
                        $selected5 = 'selected';
                    }else{
                        $selected5 = '';
                    }
                $option5 .= "<option value='" . $dataRow5['month'] . "' ".$selected5.">" . $dataRow5['name'] . "</option>";
            }

            $return .= $this->formSearch($option1, $option2, $option3, $option4, $option5, $org, $pyear, $pmonth, $pyear2, $pmonth2, $model);
        }
        return $return;
    }

    function action_profit_loss(){
        $db = atkGetDb();
        $user = getUser();
        $id_org = $user['employer_id'];

        $content .= $this->adminheader();
        if(isset($_REQUEST['show'])){
            $org      = $_REQUEST['org'];
            $pyear    = $_REQUEST['pyear'];
            $pmonth   = $_REQUEST['pmonth'];
            $pyear2   = $_REQUEST['pyear2'];
            $pmonth2  = $_REQUEST['pmonth2'];
            $model    = $_REQUEST['model'];

            if (!empty($_REQUEST['org'])) {
                $id_org = $_REQUEST['org'];
            }
                $ambil_user = $db->getrows("SELECT * FROM organization WHERE `type` = '2' AND id = '$id_org'");
                $ambil_m_y  = $db->getrows("SELECT * FROM periode_year a, periode_month b WHERE a.`id` = b.`id_year` AND a.`id_org` = '$id_org' AND b.`month` = '$pmonth' AND b.`id_year` = '$pyear'");
                    $year = $ambil_m_y[0]['year'];
                    $month = $ambil_m_y[0]['month'];

                $action = 'profit_loss';
                $ambil_y_awal    = $db->getrows("SELECT * FROM periode_year WHERE `id` = '$pyear'");
                    $yyyy_awal   = $ambil_y_awal[0]['year'];

                $ambil_y_akhr    = $db->getrows("SELECT * FROM periode_year WHERE `id` = '$pyear2'");
                    $yyyy_akhr   = $ambil_y_akhr[0]['year'];

                $thn_awal        = $yyyy_awal.$pmonth;
                $thn_akhr        = $yyyy_akhr.$pmonth2;

                $param_year_count      = $db->getrows("SELECT COUNT(CONCAT(a.`year`, b.`bulan`)) total
                                                FROM periode_year a, list_month b
                                                WHERE a.`id_org` = '$org'
                                                AND CONCAT(`year`,bulan) >= '$thn_awal'
                                                AND CONCAT(`year`,bulan) <= '$thn_akhr'
                                                ORDER BY CONCAT(a.`year`, b.`bulan`) DESC");
                $rec_limit = 6;
                $param_year_count = ceil($param_year_count[0]['total']/$rec_limit);
                $content .= $this->HeaderModel($ambil_user, $pmonth, $year, $yyyy_akhr, $pmonth2);

                if($model == 2){
                    for ($z=0; $z < $param_year_count; $z++) { 
                        $offset = $rec_limit * $z ;
                        $param_year      = $db->getrows("SELECT CONCAT(a.`year`, b.`bulan`) yyyymm, a.`year`, b.`bulan`
                                                        FROM periode_year a, list_month b
                                                        WHERE a.`id_org` = '$org'
                                                        AND CONCAT(`year`,bulan) >= '$thn_awal'
                                                        AND CONCAT(`year`,bulan) <= '$thn_akhr'
                                                        ORDER BY CONCAT(a.`year`, b.`bulan`) DESC LIMIT ".$offset.",".$rec_limit);

                        $paramProfitLoss = array('id_org' => $id_org, 
                                                 'yyyy_awal' => $yyyy_awal, 
                                                 'yyyy_akhr' => $yyyy_akhr, 
                                                 'pmonth' => $pmonth, 
                                                 'pmonth2' => $pmonth2,
                                                 'thn_awal' => $thn_awal,
                                                 'thn_akhr' => $thn_akhr,
                                                 'param_year' => $param_year);
                        $getModel .= $this->getModel($ambil_user, $year, $month, $model, $paramProfitLoss);
                    }
                }else{
                    $param_year      = $db->getrows("SELECT CONCAT(a.`year`, b.`bulan`) yyyymm
                                                FROM periode_year a, list_month b
                                                WHERE a.`id_org` = '$org'
                                                AND CONCAT(`year`,bulan) >= '$thn_awal'
                                                AND CONCAT(`year`,bulan) <= '$thn_akhr'
                                                ORDER BY CONCAT(a.`year`, b.`bulan`) DESC");
                    $paramProfitLoss = array('id_org' => $id_org, 
                                             'yyyy_awal' => $yyyy_awal, 
                                             'yyyy_akhr' => $yyyy_akhr, 
                                             'pmonth' => $pmonth, 
                                             'pmonth2' => $pmonth2,
                                             'thn_awal' => $thn_awal,
                                             'thn_akhr' => $thn_akhr,
                                             'param_year' => $param_year);

                    $getModel = $this->getModel($ambil_user, $year, $month, $model, $paramProfitLoss);

                }
                    $content .= $getModel;
                    $content .= $this->footerModel();
        }
        /*
        * OUTPUT
        */
        $page = $this->getPage();
        $page->register_scriptcode($this->jsSearch());
        $ui = atkinstance("atk.ui.atkui");

        $box = $ui->renderBox(array("title"=>atktext("Profit & Loss Report"),"content" =>$content));

        $page->addContent($box);
    }

    function action_cetak_profit_loss() {
        $db = atkGetDb();
        $user = atkGetUser();
        $this->addStyle("style.css");
        $mpdf = new mPDF('', 'A4');

            $org      = $_REQUEST['org'];
            $pyear    = $_REQUEST['pyear'];
            $pmonth   = $_REQUEST['pmonth'];
            $pyear2   = $_REQUEST['pyear2'];
            $pmonth2  = $_REQUEST['pmonth2'];
            $model    = $_REQUEST['model'];


            if (!empty($_REQUEST['org'])) {
                $id_org = $_REQUEST['org'];
            }           
                $ambil_user = $db->getrows("SELECT * FROM organization WHERE `type` = '2' AND id = '$id_org'");
                $ambil_m_y  = $db->getrows("SELECT * FROM periode_year a, periode_month b WHERE a.`id` = b.`id_year` AND a.`id_org` = '$id_org' AND b.`month` = '$pmonth' AND b.`id_year` = '$pyear'");
                    $year = $ambil_m_y[0]['year'];
                    $month = $ambil_m_y[0]['month'];

                $action = 'profit_loss';
                $ambil_y_awal    = $db->getrows("SELECT * FROM periode_year WHERE `id` = '$pyear'");
                    $yyyy_awal   = $ambil_y_awal[0]['year'];

                $ambil_y_akhr    = $db->getrows("SELECT * FROM periode_year WHERE `id` = '$pyear2'");
                    $yyyy_akhr   = $ambil_y_akhr[0]['year'];

                $thn_awal        = $yyyy_awal.$pmonth;
                $thn_akhr        = $yyyy_akhr.$pmonth2;

                $param_year_count      = $db->getrows("SELECT COUNT(CONCAT(a.`year`, b.`bulan`)) total
                                                FROM periode_year a, list_month b
                                                WHERE a.`id_org` = '$org'
                                                AND CONCAT(`year`,bulan) >= '$thn_awal'
                                                AND CONCAT(`year`,bulan) <= '$thn_akhr'
                                                ORDER BY CONCAT(a.`year`, b.`bulan`) DESC");
                $rec_limit = 6;
                $param_year_count = ceil($param_year_count[0]['total']/$rec_limit);
                $content .= $this->HeaderModel($ambil_user, $pmonth, $year, $yyyy_akhr, $pmonth2);

                if($model == 2){
                    for ($z=0; $z < $param_year_count; $z++) { 
                        $offset = $rec_limit * $z ;
                        $param_year      = $db->getrows("SELECT CONCAT(a.`year`, b.`bulan`) yyyymm, a.`year`, b.`bulan`
                                                        FROM periode_year a, list_month b
                                                        WHERE a.`id_org` = '$org'
                                                        AND CONCAT(`year`,bulan) >= '$thn_awal'
                                                        AND CONCAT(`year`,bulan) <= '$thn_akhr'
                                                        ORDER BY CONCAT(a.`year`, b.`bulan`) DESC LIMIT ".$offset.",".$rec_limit);

                        $paramProfitLoss = array('id_org' => $id_org, 
                                                 'yyyy_awal' => $yyyy_awal, 
                                                 'yyyy_akhr' => $yyyy_akhr, 
                                                 'pmonth' => $pmonth, 
                                                 'pmonth2' => $pmonth2,
                                                 'thn_awal' => $thn_awal,
                                                 'thn_akhr' => $thn_akhr,
                                                 'param_year' => $param_year);
                        $getModel .= $this->getModel($ambil_user, $year, $month, $model, $paramProfitLoss);
                    }
                }else{
                    $param_year      = $db->getrows("SELECT CONCAT(a.`year`, b.`bulan`) yyyymm
                                                FROM periode_year a, list_month b
                                                WHERE a.`id_org` = '$org'
                                                AND CONCAT(`year`,bulan) >= '$thn_awal'
                                                AND CONCAT(`year`,bulan) <= '$thn_akhr'
                                                ORDER BY CONCAT(a.`year`, b.`bulan`) DESC");
                    
                    $paramProfitLoss = array('id_org' => $id_org, 
                                             'yyyy_awal' => $yyyy_awal, 
                                             'yyyy_akhr' => $yyyy_akhr, 
                                             'pmonth' => $pmonth, 
                                             'pmonth2' => $pmonth2,
                                             'thn_awal' => $thn_awal,
                                             'thn_akhr' => $thn_akhr,
                                             'param_year' => $param_year);

                    $getModel = $this->getModel($ambil_user, $year, $month, $model, $paramProfitLoss);
                    // var_dump($getModel);exit();
                }
                    $content .= $getModel;
                    $content .= $this->footerModel();

        $footer = "
        <table width='100%'>
            <br>
            <br>
            <tr>
                <td colspan='2' id='garis2'></td>
            </tr>
            <tr>
                <td align='left'>
                    Print By : ".$user[firstname]." ".$user[lastname].", ".date('d M Y H:i:s')."
                </td>
                <td align='right'>
                    {PAGENO}
                </td>
            </tr>

        </table>
        ";

        $mpdf->SetHTMLFooter($footer);
        $mpdf->WriteHTML($content);
        $namepdf = "Profit_Loss_List" . ".pdf";
        $mpdf->Output($namepdf, "I");        
        // return true;
    }

}
?>