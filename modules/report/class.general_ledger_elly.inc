<?php
/**Author : Dimas Ardi N
*  Created Date : Oct 2013
*/
include_once (atkconfig("atkroot") . "lib/mpdf/mpdf.php");
include_once ("atk.inc");
class general_ledger_elly extends atkNode {

    var $_module = "report";
    var $_node   = "general_ledger_elly";
    var $_table  = "report_journal";


    function general_ledger_elly() {
        $db = atkGetDb();
        $this->atkNode($this->_node, NF_READONLY | NF_NO_EXTENDED_SEARCH);
        $action = array("cetak_general_ledger","getPeriodeMonth");
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
                    $jq(".multiselect").twosidedmultiselect();
                    var selectedOptions = $jq("#coa_code")[0].options;                                                                              
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
                    xmlhttp.open("GET","dispatch.php?atknodetype=report.general_ledger&atkaction=getPeriodeMonth&atklevel=-1&atkprevlevel=0&pyear="+pyear,true);
                    xmlhttp.send();
                }
         ';
        return $content;
    }

    function adminheader() {
        $db = atkGetDb();
        $user = atkGetUser();
        $id_org = $user['employer_id'];

        // $page = &atknew("atk.ui.atkpage");
        // $page->register_script("./javascript/jquery.twosidedmultiselect.js");
        // $page->register_scriptcode('\$jq(".multiselect").twosidedmultiselect();');

        
            if(isset($_REQUEST['show'])){
                $coacode  = $_REQUEST['coa_code'];
                $date1 = $_REQUEST['pyear'];
                $date2 = $_REQUEST['pmonth'];
            }

            //---get coa code
            $coaRecord = $db->getrows("SELECT * FROM coa_".$user[employer_id]." b WHERE NOT EXISTS(SELECT * FROM(SELECT DISTINCT coa_parent FROM coa_".$user[employer_id].")a WHERE b.coa_code=a.coa_parent) ORDER BY coa_code");
            $coa_cd = $coaRecord[0]['coa_code'];
            $option1 = '';
                foreach ($coaRecord as $dataRow) {
                     if(isset($_REQUEST['show'])){                    
                        if(in_array($dataRow['coa_code'], $coacode)){
                            $selected = 'selected';
                        }else{
                            $selected = '';
                        }
                    }
                $option1 .= "<option value='" . $dataRow['coa_code'] . "' ".$selected.">" . $dataRow['coa_code'] . " - " . $dataRow['coa_name'] . "</option>";
                }   

            //---get Year
            $yearRecord = $db->getrows("SELECT a.`year`, a.`id` FROM periode_year a, periode_month b WHERE a.`id` = b.`id_year` AND a.`id_org`='".$user[employer_id]."' GROUP BY a.`year` ORDER BY a.`year` DESC");
            $option2 = '';
                foreach ($yearRecord as $dataRow2) {
                    if($dataRow2['id'] == $date1){
                        $selected2 = 'selected';
                    }else{
                        $selected2 = '';
                    }
                $option2 .= "<option value='" . $dataRow2['id'] . "' ".$selected2.">" . $dataRow2['year'] . "</option>";
            }
            
            //---get Month
            $monthRecord = $db->getrows("SELECT * FROM periode_month WHERE id_year='".$date1."'");
                $monthRec = $monthRecord[0]['month'];
            $option3 = '';
            foreach ($monthRecord as $dataRow3) {
                if($dataRow3['month'] == $date2){
                        $selected3 = 'selected';
                    }else{
                        $selected3 = '';
                    }
                $option3 .= "<option value='" . $dataRow3['month'] . "' ".$selected3.">" . $dataRow3['name'] . "</option>";
            }

            if($_REQUEST['pyearhid'] == ''){
                $hid = $yearRecord[0]['year'];
            }else{
                $hid = $_REQUEST['pyearhid'];
            }

            $url = session_url(dispatch_url('report.general_ledger', 'cetak_general_ledger',array('coa_code' => $coacode, 'coa_name' => $coaname,'pyear' => $date1,'pmonth'=>$date2, 'pyearhid'=>$hid)), SESSION_NESTED);
            
            if (isset($_REQUEST['show'])) {
                $document = '<input type="button" name="button" value="Download PDF" onclick="javascript:openWindow(\'' . $url . '\')">';
                $document = '<a href="javascript:void(0);" onmouseover="window.status=\'hide link\';return true;" onclick="window.location.href=\''.$url.'\'""><input type="button" name="button" value="Download PDF"></a>';
                $pyearhid = $_REQUEST['pyearhid'];
            }

            $content .= "<div id='filter'><h4>+ <a style='text-decoration:underline;cursor:pointer;' id='filtertitle'>Action</a></h4>";
            $content .= "<form method='POST' id='filterform' style='display:yes;'>
                            <input type='hidden' name=atknodetype value=report.general_ledger />
                            <input type='hidden' name=atkaction value=general_ledger />
                            
                <table cellpadding='2' cellspacing='2' align='center' style='margin-top:10px;' border='0'>
                                <tr>
                                    <td valign='top'>COA Code</td>
                                    <td valign='top'>:</td>
                                    <td>
                                    <select name='coa_code[]' id='coa_code' class='multiselect' size='6' multiple> " .$option1. "</select>
                                    </td>
                                </tr>
                                <tr>
                                    <td>Periode Year</td>
                                    <td>:</td>
                                    <td><select name='pyear' id='pyear' onchange='showMonth(this.value)'>" . $option2 ."</select>
                                        <input type='hidden' id='pyearhid' name='pyearhid'>
                                    </td>
                                </tr>
                                <tr>
                                    <td>Periode Month</td><td>:</td><td><select name='pmonth' id='pmonth'>" .$option3. "</select></td>
                                </tr>
                                <tr>    
                                    <td colspan='3'><input type=submit name='show' value='Submit' class='btn_save'>&nbsp;&nbsp;" . $document . "</td>
                                </tr>
                                <tr></tr>
                </table>";
            $page = $content;
            return $page;
    }

    function getGeneralLedger($id_org, $date1, $date2, $coa_code, $yyyymm){
        $db = atkGetDb();
        $year_hid = $_REQUEST['pyearhid'];
        $yyyymm = $year_hid.$date2;
            
        $file = "./lib/query/r_general_ledger.txt";
            $open = fopen($file, 'r+');
            $theData = fread($open, filesize($file));
            fclose($open);

            $read = str_replace('#@id_org#@', $id_org, $theData);
            $read = str_replace('#@coa_code#@', $coa_code, $read);
            $read = str_replace('#@yyyymm#@', $yyyymm, $read);

            $get_general_ledger = $db->getrows($read);
                return $get_general_ledger;
    }

    function getSaldoAE($id_org, $date1, $date2, $coa_code, $yyyymm){ // Saldo Debit
        $db = atkGetDb();
        $year_hid = $_REQUEST['pyearhid'];
        $yyyymm = $year_hid.$date2;
            
        $file = "./lib/query/r_general_ledger_saldo_ae.txt";
            $open = fopen($file, 'r+');
            $theData = fread($open, filesize($file));
            fclose($open);

            $read = str_replace('#@id_org#@', $id_org, $theData);
            $read = str_replace('#@coa_code#@', $coa_code, $read);
            $read = str_replace('#@yyyymm#@', $yyyymm, $read);

            $get_saldo_ae = $db->getrows($read);
                return $get_saldo_ae;
    }

    function getSaldoLOR($id_org, $date1, $date2, $coa_code, $yyyymm){ // Saldo Credit
        $db = atkGetDb();
        $year_hid = $_REQUEST['pyearhid'];
        $yyyymm = $year_hid.$date2;    
        $file = "./lib/query/r_general_ledger_saldo_lor.txt";
            $open = fopen($file, 'r+');
            $theData = fread($open, filesize($file));
            fclose($open);

            $read = str_replace('#@id_org#@', $id_org, $theData);
            $read = str_replace('#@coa_code#@', $coa_code, $read);
            $read = str_replace('#@yyyymm#@', $yyyymm, $read);

            $get_saldo_lor = $db->getrows($read);
                return $get_saldo_lor;
    }

/* Added By Leontine dF
* 10102013
*/
    function headerModel($ambil_user, $date2, $pyearhid){
        $isi = '<html>
                        <head>
                        <meta http-equiv="Content-Language" content="en-us">
                        <meta http-equiv="Content-Type" content="text/html; charset=windows-1252">
                        <title>General Ledger</title>
                        <style>
                            body{font-size:8pt;}
                            table { border-collapse:collapse; }
                            td {height:25px;}
                            #garis2{border-bottom:double #000000;}
                            #headerTH{background: -moz-linear-gradient(center top , #AB8753, #8A622A) repeat scroll 0 0 rgba(0, 0, 0, 0); 
                                border-left: 1px solid #DDDDDD;
                                border-right: 1px solid #DDDDDD;
                                border-top: 1px solid #DDDDDD;
                            }
                        </style>
                        </head>
                        <body>';
        $isi .="       
                    <div style='padding-top: 20px;' height='100px' align='center'>                                                                        
                                    <h3 align='center'>" . $ambil_user[0]['name'] . "</h3>
                                    <strong> General Ledger </strong> <br> <br>
                                    <strong>" .date('F Y', mktime(0, 0, 0, $date2, 3, $pyearhid)). "</strong>
                                </div>
                    </form></div>
                    ";
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

    function getModel($ambil_user, $date1, $date2, $coa_code, $getGeneralLedger, $getSaldoAE, $getSaldoLOR, $action){
        $user = atkGetUser();
        $db   = atkGetDb();
        $nama = $db->getrows("SELECT * FROM coa_".$user[employer_id]." WHERE coa_code = ".$coa_code."");
            $coanama = $nama[0]['coa_name'];

            // get year
        $Getyears = $db->getrows("SELECT * FROM periode_year WHERE id_org = ".$user[employer_id]." AND id = ".$date1."");
            $years = $Getyears[0]['year'];


        $page  = &atknew("atk.ui.atkpage");
        $theme = &atkTheme::getInstance();
        $page->register_style($theme->stylePath("style.css"));
        $page->register_style($theme->stylePath("recordlist.css"));

        $EmptyAE = number_format($getSaldoAE[0]['total'],2);
        $EmptyLOR = number_format($getSaldoLOR[0]['total'],2);
        $isi = '<table style="margin-top:10px;" border="0" width="100%">         
                    <tr>
                        <td><h4>COA Name : '. $coanama .'</h4></td>
                        <td align=right><h4>COA Code : '. $coa_code .'</h4></td>
                    </tr>
                </table>
                <table border="1" class="recordListContainer" width="100%">
                    <tr>
                        <th align="center"  id="headerTH">Date</th>
                        <th align="center"  id="headerTH">Description</th>
                        <th align="center"  id="headerTH">Journal No</th>
                        <th align="center"  id="headerTH">Debit</th>
                        <th align="center"  id="headerTH">Credit</th>
                        <th align="center"  id="headerTH">Saldo</th>
                    </tr>';

            if($getSaldoAE[0]['total'] != '' && $getSaldoLOR[0]['total'] == ''){
                if($date2 != '01' ){
                    $isi .= '<tr class="recordListRecord row">
                                    <td align="left">' . date('M Y',strtotime('-1 month',strtotime('01-'.$date2.'-'.$years))) . '</td>
                                    <td align="left"> Saldo Akhir '. date('F',strtotime('-1 month',strtotime('01-'.$date2.'-'.$years))) . ' </td>
                                    <td align="left"></td>
                                    <td align="right"></td>
                                    <td align="right"></td>
                                    <td align="right" class="recordListTd recordListTdLast">'. number_format($getSaldoAE[0]['total'],2) .'</td>
                    </tr>';
                }else{
                    $isi .= '<tr class="recordListRecord row">
                                    <td align="left"></td>
                                    <td align="left"> Saldo Awal </td>
                                    <td align="left"></td>
                                    <td align="right"></td>
                                    <td align="right"></td>
                                    <td align="right" class="recordListTd recordListTdLast">'. number_format($getSaldoAE[0]['total'],2) .'</td>
                    </tr>';
                }
            }elseif($getSaldoLOR[0]['total'] != '' && $getSaldoAE[0]['total'] == ''){
                if($date2 != '01' ){
                    $isi .= '<tr class="recordListRecord row">
                                    <td align="left">' . date('M Y',strtotime('-1 month',strtotime('01-'.$date2.'-'.$years))) . '</td>
                                    <td align="left"> Saldo Akhir '. date('F',strtotime('-1 month',strtotime('01-'.$date2.'-'.$years))) . ' </td>
                                    <td align="left"></td>
                                    <td align="right"></td>
                                    <td align="right"></td>
                                    <td align="right" class="recordListTd recordListTdLast">'. number_format($getSaldoLOR[0]['total'],2) .'</td>
                    </tr>';
                }else{
                    $isi .= '<tr class="recordListRecord row">
                                    <td align="left"></td>
                                    <td align="left"> Saldo Awal </td>
                                    <td align="left"></td>
                                    <td align="right"></td>
                                    <td align="right"></td>
                                    <td align="right" class="recordListTd recordListTdLast">'. number_format($getSaldoLOR[0]['total'],2) .'</td>
                    </tr>';
                }
            }

        $no = 0;
        $row = 0;
        foreach ($getGeneralLedger as $value) {

            if($row == 0){
                $AmountAwalAE = $getSaldoAE[0]['total'];
                $AmountAwalLOR = $getSaldoLOR[0]['total'];
            }else{
                $AmountAwalAE = $ae;
                $AmountAwalLOR = $lor;
            }

            $ae = ($AmountAwalAE + $value['debit']) - $value['credit'];
            $lor = ($AmountAwalLOR  + $value['credit']) - $value['debit'];

            if($getSaldoAE[0]['total'] == ''){
                $ae = '';
            }

            if($getSaldoLOR[0]['total'] == ''){
                $lor = '';
            }

            $url2= session_url("dispatch.php?atknodetype=transaction.journal&atkaction=view&atkselector=journal.id_journal%3D%27".$value['id_journal']."%27", SESSION_NESTED);
            //Hidden Link on PDF
            if($action == 'gl'){
                $ahref = '<td align="center"><a href="javascript:void(0);" onmouseover="window.status=\'hide link\';" onclick="window.open(\''.$url2.'\')">' . $value['v_no'] . '</a></td>';
            }else{
                $ahref = '<td align="center">' . $value['v_no'] . '</td>';
            }

                $viewAE = $ae == ''? '':number_format($ae,2);
                $viewLOR = $lor == ''? '':number_format($lor,2);

                if($viewAE != ''){
                        $isi .='<tr class="recordListRecord row' . $no . '">
                                <td align="left">' . date('d M Y',strtotime($value['trans_date'])) . '</td>
                                <td align="left">' . $value['desc'] . '</td>
                                '.$ahref.'
                                <td align="right">' . number_format($value['debit'],2) . '</td>
                                <td align="right">' . number_format($value['credit'],2) . '</td>
                                <td align="right" class="recordListTd recordListTdLast">' . $viewAE .'</td>
                                </tr>';
                        $row++;                                                                                                                          
                }elseif($viewLOR != ''){
                        $isi .='<tr class="recordListRecord row' . $no . '">
                                <td align="left">' . date('d M Y',strtotime($value['trans_date'])) . '</td>
                                <td align="left">' . $value['desc'] . '</td>
                                '.$ahref.'
                                <td align="right">' . number_format($value['debit'],2) . '</td>
                                <td align="right">' . number_format($value['credit'],2) . '</td>
                                <td align="right" class="recordListTd recordListTdLast">' . $viewLOR .'</td>
                                </tr>';
                        $row++;
                }else{
                         $isi .='<tr class="recordListRecord row' . $no . '">
                                <td align="left">' . date('d M Y',strtotime($value['trans_date'])) . '</td>
                                <td align="left">' . $value['desc'] . '</td>
                                '.$ahref.'
                                <td align="right">' . number_format($value['debit'],2) . '</td>
                                <td align="right">' . number_format($value['credit'],2) . '</td>
                                <td align="right" class="recordListTd recordListTdLast">0.00</td>
                                </tr>';
                }
        }
        $isi .='</table>';
        return $isi;
    }

    function action_general_ledger(){
        $page = $this->getPage();
        // $page = &atknew("atk.ui.atkpage");
        $page->register_scriptcode($this->openWindow());
        $page->register_script(atkconfig("atkroot") ."javascript/jquerymin.js");
        $page->register_script("./javascript/jquery.twosidedmultiselect.js");
        $page->register_scriptcode($this->jsSearch());
        $content .= $this->adminheader();

        $db = atkGetDb();
        $user = atkGetUser();
        $id_org = $user['employer_id'];

        $action = 'gl';
        if(isset($_REQUEST['show'])){
                $coacode = $_REQUEST['coa_code'];
                $date1 = $_REQUEST['pyear'];
                $date2 = $_REQUEST['pmonth'];
                $pyearhid = $_REQUEST['pyearhid'];
                $ambil_user = $db->getrows("SELECT * FROM organization WHERE `type` = '2' AND `id` = '".$id_org."'");
            foreach ($coacode as $value) {
                $getGeneralLedger = $this->getGeneralLedger($id_org, $date1, $date2, $value, $yyyymm);
                $getSaldoAE = $this->getSaldoAE($id_org, $date1, $date2, $value, $yyyymm);
                $getSaldoLOR = $this->getSaldoLOR($id_org, $date1, $date2, $value, $yyyymm);
                $getModel .= $this->getModel($ambil_user, $date1, $date2, $value, $getGeneralLedger, $getSaldoAE, $getSaldoLOR, $action);
            }

        $content .= $this->headerModel($ambil_user, $date2, $pyearhid);
        $content .= $getModel;
        $content .= $this->footerModel();
        }

        /*
        * OUTPUT
        */

        $ui = $this->getUi();
        // $ui = &atkinstance("atk.ui.atkui");
        // $theme = &atkTheme::getInstance();
        // $output = &atkOutput::getInstance();
        // $page->register_style($theme->stylePath("style.css"));
        // $page->register_style($theme->stylePath("recordlist.css"));
        // $page->unregister_all_scripts();
        // $page->register_script(atkconfig("atkroot") ."javascript/jquery.twosidedmultiselect.js");
        $box = $ui->renderBox(array("title"=>atktext("General Ledger"),"content" =>$content));
        $page->register_stylecode('
        .tsmsselect { width: 40%; float: left; }
        .tsmsselect select { width: 100%; }
        .tsmsoptions { width: 20%; float: left; }
        .tsmsoptions p { margin: 2px; text-align: center; font-size: larger; cursor: pointer; }
        .tsmsoptions p:hover { color: White; background-color: Silver;}
        ');

        $page->addContent($box);
        // $output->output($page->render(atktext('General Ledger'), true));
    }
            
    function action_cetak_general_ledger() {

        $db   = atkGetDb();
        $user = atkGetUser();

        $id_org = $user[employer_id];
        $this->addStyle("style.css");
        $mpdf = new mPDF('', 'A4');

        $ambil_user = $db->getrows("SELECT * FROM organization WHERE `type` = '2' AND id = '$id_org'");

                $coacode = $_REQUEST['coa_code'];
                $date1 = $_REQUEST['pyear'];
                $date2 = $_REQUEST['pmonth'];
                $pyearhid = $_REQUEST['pyearhid'];

            $action = 'cgl';
            foreach ($coacode as $value){
                $getGeneralLedger = $this->getGeneralLedger($id_org, $date1, $date2, $value, $yyyymm);
                $getSaldoAE = $this->getSaldoAE($id_org, $date1, $date2, $value, $yyyymm);
                $getSaldoLOR = $this->getSaldoLOR($id_org, $date1, $date2, $value, $yyyymm);
                $getModel .= $this->getModel($ambil_user, $date1, $date2, $value, $getGeneralLedger, $getSaldoAE, $getSaldoLOR, $action);
            }
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
        $content .= $this->headerModel($ambil_user, $date2, $pyearhid);
        $content .= $getModel;
        $content .= $this->footerModel();
        $mpdf->SetHTMLFooter($footer);
        $mpdf->WriteHTML($content);
        $namepdf = "General Ledger List" . ".pdf";
        $mpdf->Output($namepdf, "I");        
        return true;
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

}
?>