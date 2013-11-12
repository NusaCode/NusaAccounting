<?php
include_once (atkconfig("atkroot") . "lib/mpdf/mpdf.php");
include_once ("atk.inc");
/*
 * Author : Dimas Ardi N
 * Created : Oct 2013
 */

class capital_statement extends atkNode {

    var $_module = "report";
    var $_node = "capital_statement";
    var $_table = "coa_value";

    function capital_statement() {
        $this->atkNode($this->_node, NF_READONLY | NF_NO_EXTENDED_SEARCH);
        $action = array("getPeriodeMonth","capital_statement","cetak_capital_statement");
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
        $content = '
                $jq(document).ready(function() { 
                                                                                                  
                    $jq("#filtertitle").click(function(){
                        
                        if (!$jq("#filterform").is(":visible")) {
                            $jq("#filterform").slideDown("slow");                                                  
                              }else{
                            $jq("#filterform").slideUp("slow");
                              }
                    });
                    function displayVals() {
                        var singleValues = $jq("#pyear :selected").text();
                        $jq("#pyearhid").val(singleValues);
                     }
                    $jq("#pyear").change(displayVals);
                    displayVals();       

                    var pyear = $jq("#pyear").val();
                    showMonth(pyear, "");       
                });

                function showMonth(pyear)
                        {
                            if (pyear=="")
                              {
                              document.getElementById("pmonth").innerHTML="";
                              return;
                              }
                            if (window.XMLHttpRequest)
                              {// code for IE7+, Firefox, Chrome, Opera, Safari
                              xmlhttp=new XMLHttpRequest();
                              }
                            else
                              {// code for IE6, IE5
                              xmlhttp=new ActiveXObject("Microsoft.XMLHTTP");
                              }
                            xmlhttp.onreadystatechange=function()
                              {
                              if (xmlhttp.readyState==4 && xmlhttp.status==200)
                                {
                                document.getElementById("pmonth").innerHTML=xmlhttp.responseText;
                                }
                              }
                            xmlhttp.open("GET","dispatch.php?atknodetype=report.capital_statement&atkaction=getPeriodeMonth&atklevel=-1&atkprevlevel=0&pyear="+pyear,true);
                            xmlhttp.send();
                        }

         ';
        return $content;
    }

    function action_getPeriodeMonth(){
        $db = atkGetDb();
        $pyear = $_REQUEST["pyear"];
        
        if(isset($_REQUEST['show'])){
            $pmonth = $_REQUEST["pmonth"];
        }

        if(isset($_REQUEST['show'])){
            $monthRecord = $db->getrows("SELECT * FROM periode_month WHERE id_year='".$pyear."'");
            $monthRec = $monthRecord[0]['month'];
            $option3 = '';
            foreach ($monthRecord as $dataRow3) {
                if($dataRow3['month'] == $pmonth){
                    $selected3 = 'selected';
                }else{
                    $selected3 = '';
                }
            $option3 .= "<option value='" . $dataRow3['month'] . "' ".$selected3.">" . $dataRow3['name'] . "</option>";
            }
        }else{
            $getRow = $db->getrows("SELECT * FROM periode_month WHERE id_year = '".$pyear."'");
            foreach ($getRow as $key => $value) {
                $select .= "<option value=" . $value['month'] . ">" . $value['name'] . "</option>";
            }
            echo $select;
        }
        
    }

    function getCapitalStatement($id_org, $cs_month, $year_hid, $dd_akhir, $dd_awal, $datetoday, $monthtoday, $yeartoday, $yyyy_akhir, $mm_akhir, $dd_akhir){
        $db = atkGetDb();
        $file = "./lib/query/r_capital_statement.txt";
        $open = fopen($file, 'r+');
            $theData = fread($open, filesize($file));
            fclose($open);


        $yyyymm = $yyyy_akhir.$mm_akhir;
        if($yeartoday.$monthtoday == $yyyy_akhir.$mm_akhir){
            $read = str_replace('#@id_org#@', $id_org, $theData);
            $read = str_replace('#@dd_awal#@', $dd_awal, $read);
            $read = str_replace('#@mm_awal#@', $cs_month, $read);
            $read = str_replace('#@yyyy_awal#@', $year_hid, $read);
            $read = str_replace('#@dd_akhir#@', $datetoday, $read);
            $read = str_replace('#@mm_akhir#@', $monthtoday, $read);
            $read = str_replace('#@yyyy_akhir#@', $yeartoday, $read);
            $read = str_replace('#@yyyymm#@', $yyyymm, $read);
                $get_capital_statement = $db->getrows($read);
                    return $get_capital_statement;
        }else{
            $read = str_replace('#@id_org#@', $id_org, $theData);
            $read = str_replace('#@dd_awal#@', $dd_awal, $read);
            $read = str_replace('#@mm_awal#@', $cs_month, $read);
            $read = str_replace('#@yyyy_awal#@', $year_hid, $read);
            $read = str_replace('#@dd_akhir#@', $dd_akhir, $read);
            $read = str_replace('#@mm_akhir#@', $mm_akhir, $read);
            $read = str_replace('#@yyyy_akhir#@', $yyyy_akhir, $read);
            $read = str_replace('#@yyyymm#@', $yyyymm, $read);
                $get_capital_statement = $db->getrows($read);
                    return $get_capital_statement;
        }
    }

    public function formSearch($option1, $option2, $option3, $cs_org, $cs_year, $cs_month, $pyearhid){   

        $url = session_url(dispatch_url('report.capital_statement', 'cetak_capital_statement',array('org' => $cs_org,'pyear' => $cs_year,'pmonth'=>$cs_month, 'pyearhid'=>$pyearhid)), SESSION_NESTED);
            if (isset($_REQUEST['show'])) {
                $document = '<input type="button" name="button" value="Download PDF" onclick="javascript:openWindow(\'' . $url . '\')">';
                $document = '<a href="javascript:void(0);" onmouseover="window.status=\'hide link\';return true;" onclick="window.location.href=\''.$url.'\'""><input type="button" name="button" value="Download PDF"></a>';
                $pyearhid = $_REQUEST['pyearhid'];
            }
        $content  = "<div id='filter'><h4>+ <a style='text-decoration:underline;cursor:pointer;' id='filtertitle'>Action</a></h4>";
        $content .= "<form method='POST' id='filterform' style='display:yes;'>
                        <input type='hidden' name=atknodetype value=report.capital_statement />
                        <input type='hidden' name=atkaction value=capital_statement />
                        <table width='100%' cellpadding='2' cellspacing='2' align='center' style='margin-top:10px;' border='0'>
                                        <tr>
                                            <td>Organization</td>
                                            <td>: <select name='org' id='org'> " .$option1. "</select>
                                            </td>
                                        </tr>
                                        <tr>
                                            <td>Periode Year</td>
                                            <td>: <select name='pyear' id='pyear' onchange='showMonth(this.value)'>" . $option2 ."</select>
                                            <input type='hidden' id='pyearhid' name='pyearhid'>
                                            </td>
                                        </tr>
                                        <tr>
                                            <td>Periode Month</td>
                                            <td>: <select name='pmonth' id='pmonth'>" .$option3. "</select></td>
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
                $cs_org     = $_REQUEST['org'];
                $cs_year    = $_REQUEST['pyear'];
                $cs_month   = $_REQUEST['pmonth'];
                $pyearhid   = $_REQUEST['pyearhid'];
                $ambil_user = $db->getrows("SELECT * FROM organization WHERE `type` = '2' AND id = '$id_org'");
                $yyyy_akhir = $_REQUEST['pyear'];
                $mm_akhir   = $_REQUEST['pmonth'];

            }
            //---Ambil Organization
            $getOrg = $db->getrows("SELECT * FROM organization WHERE type=2 and id ='".$org."'");
            foreach ($getOrg as $key => $value) {
                if($value['id'] == $cs_org){
                    $selected1 = 'selected';
                }else{
                    $selected1 = '';
                }
                $option1 .= "<option value='".$value['id']."' ".$selected1.">".$value['name']."</option>";
            }

            //---Ambil Year
            $yearRecord = $db->getrows("SELECT a.`year`, a.`id` FROM periode_year a, periode_month b WHERE a.`id` = b.`id_year` AND a.`id_org`='".$user[employer_id]."' GROUP BY a.`year` ORDER BY a.`year` DESC");
            $option2 = '';
                foreach ($yearRecord as $dataRow2) {
                    if($dataRow2['id'] == $cs_year){
                        $selected2 = 'selected';
                    }else{
                        $selected2 = '';
                    }
                $option2 .= "<option value='" . $dataRow2['id'] . "' ".$selected2.">" . $dataRow2['year'] . "</option>";
            }
            
            //---Ambil Month
            $monthRecord = $db->getrows("SELECT * FROM periode_month WHERE id_year='".$cs_year."'");
            $monthRec = $monthRecord[0]['month'];
            $option3 = '';
            foreach ($monthRecord as $dataRow3) {
                if($dataRow3['month'] == $cs_month){
                    $selected3 = 'selected';
                }else{
                    $selected3 = '';
                }
            $option3 .= "<option value='" . $dataRow3['month'] . "' ".$selected3.">" . $dataRow3['name'] . "</option>";
            }
            $return .= $this->formSearch($option1, $option2, $option3, $cs_org, $cs_year, $cs_month, $pyearhid);
        }
        return $return;
    }

    function getModel($getCapitalStatement, $ambil_user, $yyyy_akhir, $mm_akhir){
        $user = atkGetUser();
        $db   = atkGetDb();

        $page  = &atknew("atk.ui.atkpage");
        $theme = &atkTheme::getInstance();
        $page->register_style($theme->stylePath("style.css"));
        $page->register_style($theme->stylePath("recordlist.css"));

        $isi .= '<html>
                        <head>
                        <meta http-equiv="Content-Language" content="en-us">
                        <meta http-equiv="Content-Type" content="text/html; charset=windows-1252">
                        <title>Capital Statement</title>
                        <style>
                            body{font-size:8pt;}
                            table { border-collapse:collapse; }
                            td {height:25px;}
                            #garis2{border-bottom:double #000000;}
                            #table2{padding:20px}
                        </style>
                        </head>
                        <body>
                            &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
                            <div style="padding-top: 20px; display:inline-block;" height="100px" align="center">
                                <h3 align="center">' . $ambil_user[0]["name"] . '</h3>
                                <strong> Capital Statement</strong> <br> <br>
                                <strong>' .date("F Y", mktime(0, 0, 0, $mm_akhir, 3, $yyyy_akhir)). '</strong>
                            </div><BR><BR>
                            <div style="padding: 25px; border: 1px solid #000000; display:inline-block;">
            <table border="0" width="100%" class="recordListContainer" align="center" cellpadding="6px">';

        $no2 = 0;
        foreach ($getCapitalStatement as $value2) {
            if($value2['coa_code'] == 'Modal Awal'){
                $isi .='<tr ' . $no2 . '>
                            <td align="right" class="recordListTd recordListTdLast"><b>' . $value2['coa_code'] . '</b></td>
                            <td align="left"><b>' . $value2['coa_name'] . '</b></td>                           
                            <td></td>
                            <td align="right" class="recordListTd recordListTdLast" style="border-bottom: 2px solid #000000;"><b>' . $value2['balance'] . '</b></td>
                            <tr><td colspan="4" class="recordListTd recordListTdLast"></td>&nbsp;</tr>
                        </tr>';
            }elseif ($value2['coa_code'] == 'Total') {
                 $isi .='<tr ' . $no2 . '>
                            <td align="right" class="recordListTd recordListTdLast"><b>' . $value2['coa_code'] . '</b></td>
                            <td align="left"><b>' . $value2['coa_name'] . '</b></td>                           
                            <td align="right" class="recordListTd recordListTdLast"><b>' . $value2['balance'] . '</b></td>
                            <td></td>
                            <tr><td colspan="4" class="recordListTd recordListTdLast"></td>&nbsp;</tr>
                        </tr>';
            }elseif ($value2['coa_code'] == 'Perubahan') {
                 $isi .='<tr ' . $no2 . '>
                            <td align="right" class="recordListTd recordListTdLast"><b>' . $value2['coa_code'] . '</b></td>
                            <td align="left"><b>' . $value2['coa_name'] . '</b></td>                           
                            <td></td>
                            <td align="right" class="recordListTd recordListTdLast" style="border-bottom: 2px solid #000000;"><b>' . $value2['balance'] . '</b>  </td>
                            <tr><td colspan="4" class="recordListTd recordListTdLast"></td>&nbsp;</tr>
                        </tr>';
            }elseif ($value2['coa_code'] == 'Modal Akhir') {
                 $isi .='<tr ' . $no2 . '>
                            <td align="right" class="recordListTd recordListTdLast"><b>' . $value2['coa_code'] . '</b></td>
                            <td align="left"><b>' . $value2['coa_name'] . '</b></td>                           
                            <td></td>
                            <td align="right" class="recordListTd recordListTdLast" style="border-top: 2px solid #000000; border-bottom: 2px solid #000000;"><b>' . $value2['balance'] . '</b>  </td>
                            <tr><td colspan="4" class="recordListTd recordListTdLast"></td>&nbsp;</tr>
                        </tr>';
            }else{
                $isi .='<tr ' . $no2 . '>
                    <td align="right" class="recordListTd recordListTdLast"></td>
                    <td align="left"><b>' . $value2['coa_name'] . '</b></td>                           
                    <td align="right" class="recordListTd recordListTdLast"><b>' . $value2['balance'] . '</b></td>
                    <td></td>
                    <tr><td colspan="4" class="recordListTd recordListTdLast"></td>&nbsp;</tr>
                </tr>';
            }
        }

        $isi .='
                        </table>     
                        </div>                     
                    </body>
               </html>';
        return $isi;
    }

    function action_capital_statement(){
        $db = atkGetDb();
        $content .= $this->adminheader();

        $datetoday  = date('d');
        $monthtoday = date('m');
        $yeartoday  = date('Y');

        if(isset($_REQUEST['show'])){
            $cs_month = $_REQUEST['pmonth']; //bulan yang di pilih (12)d
            $year_hid = $_REQUEST['pyearhid']; //tahun yang di pilih (2013)
            $date_begin     = cal_days_in_month(CAL_GREGORIAN, $cs_month, $year_hid); //yang dipilih (31)

            $yyyy_akhir = $_REQUEST['pyearhid'];
            $mm_akhir   = $_REQUEST['pmonth'];
            $dd_akhir   = cal_days_in_month(CAL_GREGORIAN, $mm_akhir, $yyyy_akhir);

            if($cs_month == '01'){
                $cs_month = '12';
                    if($cs_month == '12'){
                        $dd_awal   = cal_days_in_month(CAL_GREGORIAN, $cs_month, $year_hid);
                        $year_hid = $year_hid -1;
                    }else{
                        $dd_awal   = cal_days_in_month(CAL_GREGORIAN, $cs_month -1, $year_hid);
                    }
            }else{
                $cs_month   = $cs_month -1;
                $dd_awal = cal_days_in_month(CAL_GREGORIAN, $cs_month, $year_hid);
            }
            
            if(strlen($cs_month) < 2){
                $cs_month = '0'.$cs_month;
            }

            if (!empty($_REQUEST['org'])) {
                $id_org = $_REQUEST['org'];
            }
                $ambil_user = $db->getrows("SELECT * FROM organization WHERE `type` = '2' AND id = '$id_org'");

            $getCapitalStatement = $this->getCapitalStatement($id_org, $cs_month, $year_hid, $dd_akhir, $dd_awal, $datetoday, $monthtoday, $yeartoday, $yyyy_akhir, $mm_akhir, $dd_akhir);
            $getModel = $this->getModel($getCapitalStatement, $ambil_user, $yyyy_akhir, $mm_akhir);
            $content .= $getModel;
        }

        $page = $this->getPage();
        $page->register_scriptcode($this->jsSearch());
        $ui = atkinstance("atk.ui.atkui");

        $box = $ui->renderBox(array("title"=>atktext("Capital Statement"),"content" =>$content));

        $page->addContent($box);
    }

    function action_cetak_capital_statement() {
        $db = atkGetDb();
        $user = atkGetUser();
        $this->addStyle("style.css");
        $mpdf = new mPDF('', 'A4');

            $datetoday  = date('d');
            $monthtoday = date('m');
            $yeartoday  = date('Y');

            $cs_month = $_REQUEST['pmonth']; //bulan yang di pilih (12)d
            $year_hid = $_REQUEST['pyearhid']; //tahun yang di pilih (2013)
            $date_begin     = cal_days_in_month(CAL_GREGORIAN, $cs_month, $year_hid); //yang dipilih (31)

            $yyyy_akhir = $_REQUEST['pyearhid'];
            $mm_akhir   = $_REQUEST['pmonth'];
            $dd_akhir   = cal_days_in_month(CAL_GREGORIAN, $mm_akhir, $yyyy_akhir);

            if($cs_month == '01'){
                $cs_month = '12';
                    if($cs_month == '12'){
                        $dd_awal   = cal_days_in_month(CAL_GREGORIAN, $cs_month, $year_hid);
                        $year_hid = $year_hid -1;
                    }else{
                        $dd_awal   = cal_days_in_month(CAL_GREGORIAN, $cs_month -1, $year_hid);
                    }
            }else{
                $cs_month   = $cs_month -1;
                $dd_awal = cal_days_in_month(CAL_GREGORIAN, $cs_month, $year_hid);
            }
            
            if(strlen($cs_month) < 2){
                $cs_month = '0'.$cs_month;
            }

            if (!empty($_REQUEST['org'])) {
                $id_org = $_REQUEST['org'];
            }
                $ambil_user = $db->getrows("SELECT * FROM organization WHERE `type` = '2' AND id = '$id_org'");

            $getCapitalStatement = $this->getCapitalStatement($id_org, $cs_month, $year_hid, $dd_akhir, $dd_awal, $datetoday, $monthtoday, $yeartoday, $yyyy_akhir, $mm_akhir, $dd_akhir);
            $getModel = $this->getModel($getCapitalStatement, $ambil_user, $yyyy_akhir, $mm_akhir);
            $content .= $getModel;

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
        $mpdf->WriteHTML($getModel);
        $namepdf = "capital_statement" . ".pdf";
        $mpdf->Output($namepdf, "I");        
        return true;
    }
}
?>