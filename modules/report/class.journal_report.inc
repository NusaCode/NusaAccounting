<?php
include_once (atkconfig("atkroot") . "lib/mpdf/mpdf.php");
include_once ("atk.inc");

/*
 * Author : Dimas Ardi N
 * Created : Sep 2013
 */

class journal_report extends atkNode {

    var $_module = "report";
    var $_node = "journal_report";
    var $_table = "report_journal";
    var $_order = "trans_date DESC, v_no DESC, debit DESC, credit DESC";

    function journal_report() {

        $db = atkGetDb();
        $user=&atkgetuser();
        $this->atkNode($this->_node, NF_READONLY | NF_NO_EXTENDED_SEARCH);
        $action = array("cetak_journal_report","tableJurnalReport");
        $this->addAllowedAction($action);

        $this->setTable($this->_table);
    }

    function descriptor_def() {
        return "[v_no]";
    }

    function openWindow() {
        return 'function openWindow(url) { window.open(url);  }';
    }

    function monthList($sel) {
        for ($j = 1; $j <= 12; $j++) {
            $c .= '<option value="' . $j . '"';
            if ($j == $sel)
                $c .= ' selected=selected';
            $c .= '>' . date("F", mktime(0, 0, 0, $j + 1, 0, 0, 0)) . '</option>';
        }
        return $c;
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
                                        
                                        $jq("select#tgl2").change(function () {
                        var currentTime = new Date();
                        var year = currentTime.getFullYear();
                        if($jq("input#tgl3").val()==""){
                            $jq("input#tgl3").val(year);
                        }
                        if($jq("select#tgl2").val()==""){
                            $jq("input#tgl3").val("");
                        }
                          });
                    
                    $jq("select#tglakhir2").change(function () {
                        var currentTime = new Date();
                        var year = currentTime.getFullYear();
                        if($jq("input#tglakhir3").val()==""){
                            $jq("input#tglakhir3").val(year);
                        }
                        if($jq("select#tglakhir2").val()==""){
                            $jq("input#tglakhir3").val("");
                        }
                          });
            
                });

         ';
        return $content;
    }

    function adminheader() {
        $user = atkGetUser();
        $db   = atkGetDb();
        
        if(isset($_REQUEST['show'])){    

            $month  =   $_REQUEST['tgl2'];
            $month2 =   $_REQUEST['tglakhir2'];
            $year   =   $_REQUEST['tgl3'];
            $year2  =   $_REQUEST['tglakhir3'];
            $posting = $_REQUEST['posting'];
            $trans1  = $_REQUEST['v_no_awal'];
            $trans2  = $_REQUEST['v_no_akhir'];
                        
                        if (strlen($month) == 1) {
                            $tgl2 = '0' . $month;
                        } else {
                            $tgl2 = $month;
                        }

                        if (strlen($month2) == 1) {
                            $tglakhir2 = '0' . $month2;
                        } else {
                            $tglakhir2 = $month2;
                        }
                        
        } else {            
            $month='01';
            $month2=date('m');
            $year=date('Y');    
            $year2=date('Y');               
        }

        if(empty($month) or empty($year)){
                $alert = "<script>alert('Date From cannot NULL');history.go(-1);</script>";
                echo $alert;
            }

        if(empty($month2) or empty($year2)){
                $alert = "<script>alert('Date Through cannot NULL');history.go(-1);</script>";
                echo $alert;
        }


            $ambil_v_no_awal = $db->getrows("SELECT * FROM journal WHERE id_org='".$user[employer_id]."' ORDER BY v_no");
            foreach ($ambil_v_no_awal as $dataRow) {
                if($dataRow['id_journal'] == $trans1){
                        $selected = 'selected';
                    }else{
                        $selected = '';
                    }
                $vno_awal .= "<option value='" . $dataRow['id_journal'] . "' ".$selected.">" . $dataRow['v_no'] . "</option>";
            }

            $ambil_v_no_akhir = $db->getrows("SELECT * FROM journal WHERE id_org='".$user[employer_id]."' ORDER BY v_no");

            foreach ($ambil_v_no_akhir as $dataRow2) {
                if($dataRow2['id_journal'] == $trans2){
                        $selected = 'selected';
                    }else{
                        $selected = '';
                    }            
                $vno_akhir .= "<option value=" . $dataRow2['id_journal'] . " ".$selected.">" . $dataRow2['v_no'] . "</option>";
            }
            
            $getYearAwal = $db->getrows("SELECT a.`year`, a.`id` FROM periode_year a, periode_month b WHERE a.`id` = b.`id_year` AND a.`id_org`='".$user[employer_id]."' GROUP BY a.`year` ORDER BY a.`year` DESC");
            foreach ($getYearAwal as $dataRow3) {
                if($dataRow3['year'] == $year){
                        $selected = 'selected';
                    }else{
                        $selected = '';
                    }            
                $yearGetAwal .= "<option value=" . $dataRow3['year'] . " ".$selected.">" . $dataRow3['year'] . "</option>";
            }

            $getYearAkhir = $db->getrows("SELECT a.`year`, a.`id` FROM periode_year a, periode_month b WHERE a.`id` = b.`id_year` AND a.`id_org`='".$user[employer_id]."' GROUP BY a.`year` ORDER BY a.`year` DESC");
            foreach ($getYearAkhir as $dataRow4) {
                if($dataRow4['year'] == $year2){
                        $selected = 'selected';
                    }else{
                        $selected = '';
                    }            
                $yearGetAkhir .= "<option value=" . $dataRow4['year'] . " ".$selected.">" . $dataRow4['year'] . "</option>";
            }

            for($ix=0;$ix<=4;$ix++) {
                switch ($ix) {
                    case '0':
                        $postingval = 'Not Posted Yet';
                        break;
                    case '1':
                        $postingval = 'Posted';
                        break;
                    case '2':
                        $postingval = 'No Transaction Found';
                        break;
                    case '3':
                        $postingval = 'Not Balance Yet';
                        break;
                    case '4':
                        $postingval = 'All';
                        break;
                }
                if($ix == $posting){
                        $selected = 'selected';
                    }else{
                        $selected = '';
                    }
                $Status .= "<option value='" . $ix . "' ".$selected.">" . $postingval . "</option>";
            }


        $url = dispatch_url('report.journal_report', 'cetak_journal_report',array('month' => $month,'month2'=>$month2,'year'=>$year,'year2'=>$year2, 'v_no_awal'=>$trans1, 'v_no_akhir'=>$trans2, 'posting'=>$posting));
    if(isset($_REQUEST['show'])){            
        $document = '<input type="button" name="button" value="Download PDF" onclick="javascript:openWindow(\'' . $url . '\')">';
        $document = '<a href="javascript:void(0);" onmouseover="window.status=\'hide link\';return true;" onclick="window.location.href=\''.$url.'\'""><input type="button" name="button" value="Download PDF"></a>';
    }
        $content .= "<div id='filter'><h4>+ <a style='text-decoratiotion:underline;cursor:pointer;' id='filtertitle'>Action</a></h4>";
        $content = "<div id='filter'>";
        $content .= "<form method='POST' id='filterform' style='none;'>
                        <input type='hidden' name=atknodetype value=report.journal_report />
                        <input type='hidden' name=atkaction value=journal_report />
                        
            <table width='100%' cellpadding='2' cellspacing='2' align='center' style='margin-top:10px;' border='0'>
                            <tr>
                                <td>From Journal</td>
                                <td>:
                                <select name='v_no_awal' id='v_no_awal'>" .$vno_awal. "</select>
                                </td>
                            <tr>
                            <tr>
                                <td>Through Journal</td>
                                <td>:
                                <select name='v_no_akhir' id='v_no_akhir'>" . $vno_akhir ."</select>
                                </td>
                            <tr>
                            <tr> 
                                <td>Transaction Date From</td>
                                <td>: 
                                    <select name='tgl2' id='tgl2' >" . $this->monthList($_REQUEST['tgl2']) . "</select>
                                    <select name='tgl3' id='tgl3' >" . $yearGetAwal . " </select>
                                </td>
                            </tr>
                            <tr>
                                <td>Transaction Date Through</td>
                                <td>: 
                                    <select name='tglakhir2' id='tglakhir2' >" . $this->monthList($_REQUEST['tglakhir2']) . "</select>
                                    <select name='tglakhir3' id='tglakhir3' >" . $yearGetAkhir . " </select>
                                </td>
                            </tr>
                            <tr>
                                <td>Status Posting</td>
                                <td>:
                                    <select name='posting' id='posting'>
                                        ".$Status."
                                    </select>
                                </td>
                            </tr>
                            <tr>	
				<td><input type=submit name='show' value='Submit' class='btn_save'>&nbsp;&nbsp;" . $document . "</td>					    
                            </tr>
			</table>		
                     </form></div>					
		 ";
        $page = $content;
        return $page;
    }

    function getJournalReport($id_org, $trans1, $trans2, $month, $month2, $year, $year2, $posting, $page=1, $pagelist=10, $action=NULL){
        // if (isset($_REQUEST['panel'])) {
        //     $id_org = $_REQUEST['id_org'];
        //     $trans1 = $_REQUEST['trans1'];
        //     $trans2 = $_REQUEST['trans2'];
        //     $month = $_REQUEST['month'];
        //     $month2 = $_REQUEST['month2'];
        //     $year = $_REQUEST['year'];
        //     $year2 = $_REQUEST['year2'];
        //     $posting = $_REQUEST['posting'];
        // }
        
        $db = atkGetDb();
        $file = "./lib/query/r_journal_report.txt";
            $open = fopen($file, 'r+');
            $theData = fread($open, filesize($file));
            fclose($open);
            if($posting == '4'){
                $posting = '0,1,2,3';
            }
            
            $read = str_replace('#@id_org#@', $id_org, $theData);
            $read = str_replace('#@trans1#@', $trans1, $read);
            $read = str_replace('#@trans2#@', $trans2, $read);
            $read = str_replace('#@month#@', $month, $read);
            $read = str_replace('#@month2#@', $month2, $read);
            $read = str_replace('#@year#@', $year, $read);
            $read = str_replace('#@year2#@', $year2, $read);
            $read = str_replace('#@posting#@', $posting, $read);

            /*
                PAGINATION
            */

            if ($action=='journal_report') {
                $start = ($page-1)*$pagelist;
                $read .= " LIMIT ".$start.",".$pagelist;
            }
            /*
                END OF PAGINATION
            */

            $get_journal_report = $db->getrows($read);
            return $get_journal_report;
    }

/* edited by Leontine de Fretes
    2 Oct 2013
*/
    function action_tableJurnalReport($getJournalReport2=NULL){
        $id_org = $_REQUEST['id_org'];
        $month = $_REQUEST['month'];
        $month2 = $_REQUEST['month2'];

        $year = $_REQUEST['year'];
        $year2 = $_REQUEST['year2'];
        $trans1 = $_REQUEST['trans1'];
        $trans2 = $_REQUEST['trans2'];
        $posting = $_REQUEST['posting'];
        $page = $_REQUEST['page'];
        $pagelist = $_REQUEST['pagelist'];
        if (empty($pagelist)) {
            $pagelist = 10;
        }
        $action = $_REQUEST['action'];
        if (!is_object($getJournalReport2)) {
            $getJournalReport = $getJournalReport2;
        }else{
            $getJournalReport = $this->getJournalReport($id_org, $trans1, $trans2, $month, $month2, $year, $year2, $posting, $page, $pagelist, $action);
        }
        $isi = '
                                <table border="1" width="100%" class="recordListContainer">
                                    <tr class="recordListHeader">
                                        <th width="10px" class="recordListHeaderTh" align="center">Journal No</th>
                                        <th width="10px" class="recordListHeaderTh" align="center">Journal Type</th>
                                        <th width="10px" class="recordListHeaderTh" align="center">Transaction Date</th>
                                        <th width="10px" class="recordListHeaderTh" align="center">COA</th>
                                        <th width="10px" class="recordListHeaderTh" align="center">Debit</th>
                                        <th width="10px" class="recordListHeaderTh" align="center">Credit</th>
                                        <th width="10px" class="recordListHeaderTh" align="center">Description</th>
                                        <th width="10px" class="recordListHeaderTh" align="center">Status Posting</th>
                                    </tr> ';

        $no = 0;
        //Membuat baris hasil menjadi hiden saat transaksi sama
        foreach ($getJournalReport as $value) {
            if($v_no == $value['v_no']){
                if ($no%2==1) {
                    $angka = '1';
                }else{
                    $angka = '2';
                }
                $isi .='<tr class="recordListRecord row' . $angka . '">
                        <td align="left">' . $value['coa'] . '</td>
                        <td align="right">'. $value['debit'] . '</td>
                        <td align="right">'. $value['credit'] . '</td>
                        <td align="left">' . $value['desc'] . '</td>
                        <td class="recordListTd recordListTdLast" align="left">'. $value['posting_desc'] . '</td>
                        </tr>';
            }else{
                $v_no = $value['v_no'];
                $totV_no = 0;
                foreach ($getJournalReport as $value2) {
                    if($v_no == $value2['v_no']){
                        $totV_no++;
                    }
                }
                $no++;
                if ($no%2==1) {
                    $angka = '1';
                }else{
                    $angka = '2';
                }

                    $isi .='<tr class="recordListRecord row' . $angka . '">
                                <td align="left" rowspan = "'.$totV_no.'" valign="top">' . $value['v_no'] . '</td>
                                <td align="left" rowspan = "'.$totV_no.'" valign="top">' . $value['journal_type'] . '</td>
                                <td align="left" rowspan = "'.$totV_no.'" valign="top">' . $value['trans_date'] . '</td>
                                <td align="left">' . $value['coa'] . '</td>
                                <td align="right">'. $value['debit'] . '</td>
                                <td align="right">'. $value['credit'] . '</td>
                                <td align="left">' . $value['desc'] . '</td>
                                <td class="recordListTd recordListTdLast" align="left">'. $value['posting_desc'] . '</td>
                            </tr>';
                }
        }
        $isi .='    
        
                            </table>   
                            ';
        /*
        * OUTPUT
        */
        if (!is_object($getJournalReport2)) { //SEND this output if not paging
            return $isi;
        }else{ //SEND this output if paging
            $page = $this->getPage();
            $ui = $this->getUI();
            // $output = &atkOutput::getInstance();

            $page->addContent($isi);
            // $output->output($page->render(atktext('Journal Report'), true));
            // $haha = $ui->renderBox(array("title"=>"My Hello World Page",
                                              // "content"=>$isi));
            // return $haha;
            // $page->addContent($this->renderActionPage("showhelloworld", $output));
        }
    }

/* Added By Leontine dF
* 10102013
*/

    function headerModelHtml(){
        $isi = '<html>
                        <head>
                        <meta http-equiv="Content-Language" content="en-us">
                        <meta http-equiv="Content-Type" content="text/html; charset=windows-1252">
                        <title>Journal Report</title>
                        <style>
                            body{font-size:8pt;}
                            table { border-collapse:collapse; }
                            #garis2{border-bottom:double #000000;}
                            td {height:25px;}
                            #garis2{border-bottom:double #000000;}
                        </style>
                        </head>
                        <body>';
        return $isi;                        
    }

    function headerModel($ambil_user, $month, $month2, $year, $year2){
        $isi .='       
                            <div style="padding-top: 20px;" height="100px" align="center">
                                <h3 align="center">' . $ambil_user[0]["name"] . '</h3>
                                <strong> Journal Report </strong> <br> <br>
                                <strong>' .date("F Y", mktime(0, 0, 0, $month, 3, $year)). ' To ' .date("F Y", mktime(0, 0, 0, $month2, 3, $year2)). '</strong>
                            </div>';
                    
        return $isi;                        
    }

    function footerModel(){
        $isi .='    
                        </body>
               </html> 
            ';
        return $isi;
    }
    function getModel($ambil_user, $month, $month2, $year, $year2, $getJournalReport, $posting, $id_org, $trans1, $trans2, $action){
        $user = atkGetUser();
        $db   = atkGetDb();
        
        $page = $this->getPage();
        // $theme = &atkTheme::getInstance();
        // $page->register_style($theme->stylePath("style.css"));
        // $page->register_style($theme->stylePath("recordlist.css"));
        $totalHal = count($getJournalReport);
        // $url = dispatch_url('report.journal_report', 'tableJurnalReport',array('id_org'=>$id_org, 'trans1'=>$trans1, 'trans2'=>$trans2, 'month'=>$month, 'month2'=>$month2, 'year'=>$year, 'year2'=>$year2, 'posting'=>$posting, 'action'=> $action));
        $url = "dispatch.php?atknodetype=report.journal_report&atkaction=tableJurnalReport&id_org=".$id_org."&trans1=".$trans1."&trans2=".$trans2."&month=".$month."&month2=".$month2."&year=".$year."&year2=".$year2."&posting=".$posting."&action=".$action;

            /*
                PAGINATION
            */
            if ($action=='journal_report') {
            $isi .= '
                            <div class="easyui-pagination" 
                                 data-options="total:'.$totalHal.', 
                                               onSelectPage: function(pageNumber, pageSize){$jq(\'#contentJur\').panel(\'refresh\', \''.$url.'&page=\'+pageNumber+\'&pagelist=\'+pageSize);},
                                               pageList: [5,10,15,20,25,30,40,50,100]"
                                 style="border:1px solid #ddd;">
                            </div>';
                            
            $isi .= '
                            <div id="contentJur" class="easyui-panel" data-options="href:\''.$url.'&page=1\'"></div>            
            ';
            /*
                END OF PAGINATION
            */            
            }else{ // NOT PAGINATION (PDF)
                $isi .= $this->action_tableJurnalReport($getJournalReport);
            }
            
        return $isi;
    }

    function action_journal_report(){
        $db = atkGetDb();
        $user = atkGetUser();
        $id_org = $user[employer_id];
        $content .= $this->adminheader();

        if(isset($_REQUEST['show'])){
            
            $month = $_REQUEST['tgl2'];
            $month2 = $_REQUEST['tglakhir2'];

            $year = $_REQUEST['tgl3'];
            $year2 = $_REQUEST['tglakhir3'];

            $trans1 = $_REQUEST['v_no_awal'];
            $trans2 = $_REQUEST['v_no_akhir'];
             
            $posting = $_REQUEST['posting'];
          
            $ambil_user = $db->getrows("SELECT * FROM organization WHERE `type` = '2' AND id = '$id_org'");
            $action = 'journal_report';
                $getJournalReport = $this->getJournalReport($id_org, $trans1, $trans2, $month, $month2, $year, $year2, $posting, $action);

                $getModel = $this->getModel($ambil_user,  $month, $month2, $year, $year2, $getJournalReport, $posting, $id_org, $trans1, $trans2, $action);

            $content .= $this->headerModel($ambil_user, $month, $month2, $year, $year2);
            $content .= $getModel; //(.=) menambahkan isi variabel $getModel ke $content
        }
        /*
        * OUTPUT
        */
        $page = $this->getPage();
        $page->register_scriptcode($this->jsSearch());
        $ui = atkinstance("atk.ui.atkui");

        $box = $ui->renderBox(array("title"=>atktext("Journal Report"),"content" =>$content));

        $page->addContent($box);
    }

    function action_cetak_journal_report() {

        $user = atkGetUser();
        $db = atkGetDb();

        $id_org = $user[employer_id];
        $this->addStyle("style.css");
        $mpdf = new mPDF('', 'A4');
        
        $month = $_REQUEST['month'];
    	$year = $_REQUEST['year'];

    	$month2 = $_REQUEST['month2'];
    	$year2 = $_REQUEST['year2'];

        $trans1 = $_REQUEST['v_no_awal'];
        $trans2 = $_REQUEST['v_no_akhir'];

        $posting = $_REQUEST['posting'];
         
        $ambil_user = $db->getrows("SELECT * FROM organization WHERE `type` = '2' AND id = '$id_org'");
        $action = 'cetak_journal_report';
            $getJournalReport = $this->getJournalReport($id_org, $trans1, $trans2, $month, $month2, $year, $year2, $posting, $action);
            $getModel .= $this->getModel($ambil_user,  $month, $month2, $year, $year2, $getJournalReport, $posting, $id_org, $trans1, $trans2, $action);

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
        $content .= $this->headerModel($ambil_user, $month, $month2, $year, $year2);
        $content .= $getModel;
        $content .= $this->footerModel();

        $mpdf->SetHTMLFooter($footer);
        $mpdf->WriteHTML($content);
        $namepdf = "Jurnal Report List" . ".pdf";
        $mpdf->Output($namepdf, "I");
        
        return true;
    }
}
?>