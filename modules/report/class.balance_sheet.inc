<?php
include_once (atkconfig("atkroot") . "lib/mpdf/mpdf.php");
include_once ("atk.inc");
/*
 * Author : Dimas Ardi N
 * Created : Oct 2013
 */

class balance_sheet extends atkNode {

    var $_module = "report";
    var $_node = "balance_sheet";
    var $_table = "coa_value";

    function balance_sheet() {
        $this->atkNode($this->_node, NF_READONLY | NF_NO_EXTENDED_SEARCH);
        $action = array("getPeriodeMonth","balance_sheet","cetak_balance_sheet");
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
                    showMonth(pyear);
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
                            xmlhttp.open("GET","dispatch.php?atknodetype=report.balance_sheet&atkaction=getPeriodeMonth&atklevel=-1&atkprevlevel=0&pyear="+pyear,true);
                            xmlhttp.send();
                        }

         ';
        return $content;
    }

    function action_getPeriodeMonth(){

        $db = atkGetDb();
        $pyear = $_REQUEST["pyear"];

        $getRow = $db->getrows("SELECT * FROM periode_month WHERE id_year = '".$pyear."'");
        foreach ($getRow as $key => $value) {
            $select .= "<option value=" . $value['month'] . ">" . $value['name'] . "</option>";
        }
        echo $select;
    }

    function getBalanceSheetAktiva($id_org, $yyyymm, $bs_month){
        $db = atkGetDb();
        $file = "./lib/query/r_balance_sheet_l.txt";
        $open = fopen($file, 'r+');
            $theData = fread($open, filesize($file));
            fclose($open);

        $read = str_replace('#@id_org#@', $id_org, $theData);
        $read = str_replace('#@yyyymm#@', $yyyymm, $read);

            $get_balance_sheet_l = $db->getrows($read);
                return $get_balance_sheet_l;
    }

    function getBalanceSheetHutMod($id_org, $yyyymm, $bs_month){
        $db = atkGetDb();
        $file = "./lib/query/r_balance_sheet_r.txt";
        $open = fopen($file, 'r+');
            $theData = fread($open, filesize($file));
            fclose($open);

        $read = str_replace('#@id_org#@', $id_org, $theData);
        $read = str_replace('#@yyyymm#@', $yyyymm, $read);

            $get_balance_sheet_r = $db->getrows($read);
                return $get_balance_sheet_r;
    }

    public function formSearch($option1, $option2, $option3, $bs_org, $bs_year, $bs_month, $hid){   

        $url = session_url(dispatch_url('report.balance_sheet', 'cetak_balance_sheet',array('org' => $bs_org,'pyear' => $bs_year,'pmonth'=>$bs_month, 'pyearhid'=>$hid)), SESSION_NESTED);
            if (isset($_REQUEST['show'])) {
                $document = '<input type="button" name="button" value="Download PDF" onclick="javascript:openWindow(\'' . $url . '\')">';
                $document = '<a href="javascript:void(0);" onmouseover="window.status=\'hide link\';return true;" onclick="window.location.href=\''.$url.'\'""><input type="button" name="button" value="Download PDF"></a>';
                $pyearhid = $_REQUEST['pyearhid'];
            }
        $content  = "<div id='filter'><h4>+ <a style='text-decoration:underline;cursor:pointer;' id='filtertitle'>Action</a></h4>";
        $content .= "<form method='POST' id='filterform' style='display:yes;'>
                        <input type='hidden' name=atknodetype value=report.balance_sheet />
                        <input type='hidden' name=atkaction value=balance_sheet />
                        
                        <table width='100%' cellpadding='2' cellspacing='2' align='center' style='margin-top:10px;' border='0'>
                                        <tr>
                                            <td>Organization</td>
                                            <td>: <select name='org' id='org'> " .$option1. "</select>
                                            </td>
                                        </tr>
                                        <tr>
                                            <td>Periode Year</td>
                                            <td>: <select name='pyear' id='pyear' onchange='showMonth(this.value)' >" . $option2 ."</select>
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
                $bs_org   = $_REQUEST['org'];
                $bs_year  = $_REQUEST['pyear'];
                $bs_month = $_REQUEST['pmonth'];
                $hid      = $_REQUEST['pyearhid'];
            }
            //---Ambil Organization
            $getOrg = $db->getrows("SELECT * FROM organization WHERE type=2 and id ='".$org."'");
            foreach ($getOrg as $key => $value) {
                if($value['id'] == $bs_org){
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
                    if($dataRow2['id'] == $bs_year){
                        $selected2 = 'selected';
                    }else{
                        $selected2 = '';
                    }
                $option2 .= "<option value='" . $dataRow2['id'] . "' ".$selected2.">" . $dataRow2['year'] . "</option>";
            }
            
            //---Ambil Month
            $monthRecord = $db->getrows("SELECT * FROM periode_month WHERE id_year='".$bs_year."'");
            $monthRec = $monthRecord[0]['month'];
            $option3 = '';
            foreach ($monthRecord as $dataRow3) {
                if($dataRow3['month'] == $bs_month){
                    $selected3 = 'selected';
                }else{
                    $selected3 = '';
                }
            $option3 .= "<option value='" . $dataRow3['month'] . "' ".$selected3.">" . $dataRow3['name'] . "</option>";
            }
            $return .= $this->formSearch($option1, $option2, $option3, $bs_org, $bs_year, $bs_month, $hid);
        }
        return $return;
    }

/* Added By Leontine dF
* 10102013
*/
    function headerModel($ambil_user, $month, $year){
        $isi .='       
                            <div style="padding-top: 20px;" height="100px" align="center">                                                                        
                                <h3 align="center">' . $ambil_user[0]["name"] . '</h3>
                                <strong> Balance Sheet Statement</strong> <br> <br>
                                <strong>' .date("F Y", mktime(0, 0, 0, $month, 3, $year)). '</strong>
                            </div>
                            &nbsp;&nbsp;&nbsp;&nbsp;
                ';
        return $isi;                        
    }

    function headerModelHtml(){
        $isi = '<html>
                        <head>
                        <meta http-equiv="Content-Language" content="en-us">
                        <meta http-equiv="Content-Type" content="text/html; charset=windows-1252">
                        <title>Balance Sheet</title>
                        <style>
                            body{font-size:8pt;}
                            table { border-collapse:collapse; }
                            td {height:25px;}
                            #garis2{border-bottom:double #000000;}
                            #table2{padding:20px}
                        </style>
                        </head>
                        <body>';
        return $isi;                        
    }

/* Added By Leontine dF
* 10102013
*/
    function footerModel(){
        $isi .='    
                        </body>
               </html> 
            ';
        return $isi;
    }
    function getModel($getBalanceSheetAktiva, $getBalanceSheetHutMod, $ambil_user, $pl_year, $pl_month, $year, $month){
        $user = atkGetUser();
        $db   = atkGetDb();

        $page  = &atknew("atk.ui.atkpage");
        $theme = &atkTheme::getInstance();
        $page->register_style($theme->stylePath("style.css"));
        $page->register_style($theme->stylePath("recordlist.css"));

        $isi = '
            <table border="1" width="100%" class="recordListContainer" align="center" cellpadding="50">
                <tr>
                    <td>
                        <table border="0" width="100%" class="recordListContainer" align="center">';
        $no = 0;
        foreach ($getBalanceSheetAktiva as $value) {
            if($value['coa_code'] == 'TOTAL'){
                $isi .='<tr ' . $no . '>
                            <td align="right" class="recordListTd recordListTdLast"><b>' . $value['coa_code'] . '</b></td>
                            <td align="left" class="recordListTd recordListTdLast"><b>' . $value['coa_name'] . '</b></td>                           
                            <td align="right" class="recordListTd recordListTdLast" style="border-top: 2px double #000000; border-bottom: 2px double #000000;"><b>' . $value['balance'] . '</b></td>
                        </tr>';
            }else{
                    $isi .='<tr ' . $no . '>
                                <td align="left"></td>
                                <td align="left" class="recordListTd recordListTdLast">' . $value['coa_name'] . '</td>                           
                                <td align="right" class="table2">' . $value['balance'] . '</td>
                            </tr>';
            }
        }
        
        $isi .= '       </table>
                    </td>
                    <td valign="top">
                        <table border="0" width="100%" class="recordListContainer" align="center">';

        $no2 = 0;
        foreach ($getBalanceSheetHutMod as $value2) {
            if($value2['coa_name'] == 'HUTANG'){
                $isi .='<tr ' . $no2 . '>
                            <td align="left" class="recordListTd recordListTdLast"><b>' . $value2['coa_code'] . '</b></td>
                            <td align="left" class="recordListTd recordListTdLast"><b>' . $value2['coa_name'] . '</b></td>                           
                            <td align="right" class="recordListTd recordListTdLast" style="border-top: 2px double #000000;"><b>' . $value2['balance'] . '</b></td>
                            <tr><td colspan="3" class="recordListTd recordListTdLast"></td>&nbsp;</tr>
                        </tr>';
            }elseif($value2['coa_name'] == 'Profit / Loss'){
                    $isi .='<tr ' . $no2 . '>
                            <td align="right" class="recordListTd recordListTdLast"></td>
                            <td align="left" class="recordListTd recordListTdLast">' . $value2['coa_name'] . '</td>                           
                            <td align="right" class="recordListTd recordListTdLast">' . $value2['balance'] . '</td>
                        </tr>';
            }elseif($value2['coa_name'] == 'EQUITY (MODAL)'){
                    $isi .='<tr ' . $no2 . '>
                            <td align="center" class="recordListTd recordListTdLast"><b>' . $value2['coa_code'] . '</b></td>
                            <td align="left" class="recordListTd recordListTdLast"><b>' . $value2['coa_name'] . '</b></td>                           
                            <td align="right" class="recordListTd recordListTdLast" style="border-top: 2px double #000000;"><b>' . $value2['balance'] . '</b></td>
                            <tr><td colspan="3" class="recordListTd recordListTdLast"></td>&nbsp;</tr>
                        </tr>';
            }elseif($value2['coa_name'] == 'HUTANG & EQUITY (MODAL)'){
                    $isi .='<tr ' . $no2 . '>
                            <td align="right" class="recordListTd recordListTdLast"><b>' . $value2['coa_code'] . '</b></td>
                            <td align="left" class="recordListTd recordListTdLast"><b>' . $value2['coa_name'] . '</b></td>                           
                            <td align="right" class="recordListTd recordListTdLast" style="border-top: 2px double #000000; border-bottom: 2px double #000000;"><b>' . $value2['balance'] . '</b></td>
                            <tr><td colspan="3" class="recordListTd recordListTdLast"></td>&nbsp;</tr>
                        </tr>';
            }else{
                    $isi .='<tr ' . $no2 . '>
                                <td align="left"></td>
                                <td align="left" class="recordListTd recordListTdLast">' . $value2['coa_name'] . '</td>                           
                                <td align="right" class="table2">' . $value2['balance'] . '</td>
                            </tr>';
            }
        }

        $isi .= '       </table>
                    </td>
                </tr>';

        $isi .='</table>';
        return $isi;
    }

    function action_balance_sheet(){
        $db = atkGetDb();
        $content .= $this->adminheader();
        if(isset($_REQUEST['show'])){
            $pl_year  = $_REQUEST['pyear'];
            $pl_month = $_REQUEST['pmonth'];

            $year_hid = $_REQUEST['pyearhid'];
            $yyyymm = $year_hid.$pl_month;

            if (!empty($_REQUEST['org'])) {
                $id_org = $_REQUEST['org'];
            }
                $ambil_user = $db->getrows("SELECT * FROM organization WHERE `type` = '2' AND id = '$id_org'");
                $ambil_m_y  = $db->getrows("SELECT * FROM periode_year a, periode_month b WHERE a.`id` = b.`id_year` AND a.`id_org` = '$id_org' AND b.`month` = '$pl_month' AND b.`id_year` = '$pl_year'");
                    $year = $ambil_m_y[0]['year'];
                    $month = $ambil_m_y[0]['month'];
            $getBalanceSheetAktiva = $this->getBalanceSheetAktiva($id_org, $yyyymm, $bs_month);
            $getBalanceSheetHutMod = $this->getBalanceSheetHutMod($id_org, $yyyymm, $bs_month);
            $getModel = $this->getModel($getBalanceSheetAktiva, $getBalanceSheetHutMod, $ambil_user, $pl_year, $pl_month, $year, $month);
        $content .= $this->headerModel($ambil_user, $month, $year);
        $content .= $getModel;
        }

        $page = $this->getPage();
        $page->register_scriptcode($this->jsSearch());
        $ui = atkinstance("atk.ui.atkui");
        $box = $ui->renderBox(array("title"=>atktext("Balance Sheet"),"content" =>$content));
        $page->addContent($box);
    }

    function action_cetak_balance_sheet() {
        $db = atkGetDb();
        $user = atkGetUser();
        $this->addStyle("style.css");
        $mpdf = new mPDF('', 'A4');

            $pl_year  = $_REQUEST['pyear'];
            $pl_month = $_REQUEST['pmonth'];

            $year_hid = $_REQUEST['pyearhid'];
            $yyyymm = $year_hid.$pl_month;

            if (!empty($_REQUEST['org'])) {
                $id_org = $_REQUEST['org'];
            }           
                $ambil_user = $db->getrows("SELECT * FROM organization WHERE `type` = '2' AND id = '$id_org'");
                $ambil_m_y  = $db->getrows("SELECT * FROM periode_year a, periode_month b WHERE a.`id` = b.`id_year` AND a.`id_org` = '$id_org' AND b.`month` = '$pl_month' AND b.`id_year` = '$pl_year'");
                    $year = $ambil_m_y[0]['year'];
                    $month = $ambil_m_y[0]['month'];
            $getBalanceSheetAktiva = $this->getBalanceSheetAktiva($id_org, $yyyymm, $bs_month);
            $getBalanceSheetHutMod = $this->getBalanceSheetHutMod($id_org, $yyyymm, $bs_month);
            $getModel = $this->getModel($getBalanceSheetAktiva, $getBalanceSheetHutMod, $ambil_user, $pl_year, $pl_month, $year, $month);

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

        $content .= $this->headerModelHtml();
        $content .= $this->headerModel($ambil_user, $month, $year);
        $content .= $getModel;
        $content .= $this->footerModel();
        $mpdf->SetHTMLFooter($footer);
        $mpdf->WriteHTML($content);
        $namepdf = "Balance_Sheet" . ".pdf";
        $mpdf->Output($namepdf, "I");        
        return true;
    }
}
?>