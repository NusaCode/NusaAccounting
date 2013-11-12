<?php
include_once (atkconfig("atkroot") . "lib/mpdf/mpdf.php");
class general_ledger extends atkNode {

    var $_module = "report";
    var $_node   = "general_ledger";
    var $_table  = "report_journal";


    function general_ledger() {
        
        $this->atkNode($this->_node, NF_READONLY | NF_NO_EXTENDED_SEARCH);
        $action = array("cetak_general_ledger","getPeriodeMonth");
        $this->addAllowedAction($action);

        $this->add(new atkDateAttribute("trans_date"))->setLabel("Date");

        $this->add(new atkTextAttribute("desc"))->setLabel("Description");

        $this->add(new atkAttribute("v_no"))->setLabel("Reff");

        $this->add(new atkAttribute("journal_type"));
        
        $this->add(new atkAttribute("debit"));

        $this->add(new atkAttribute("credit"));

        $this->add(new atkAttribute("coa"));

        $this->add(new atkDummyAttribute("saldo_debit"))->setLabel("Saldo Debit");

        $this->add(new atkDummyAttribute("saldo_credit"))->setLabel("Saldo Credit");

        if (isset($_GET['show'])) {
            $db = atkGetDb();
            $user = atkGetUser();
            $id_org = $user['employer_id'];
            $coa_code    = $_GET['coa_code'];
            $date_year   = $_GET['pyear'];
            $date_month  = $_GET['pmonth'];

            // $where.="coa = '$coa_code' and periode_year = '$date_year' and periode_month = '$date_month'";
            // $this->addFilter($where);

            $file = "./lib/query/r_general_ledger.txt";
            $open = fopen($file, 'r+');
            $theData = fread($open, filesize($file));
            fclose($open);
            $read = str_replace('#@id_org#@', $id_org, $TheData);
                echo $read;

        }else{
            $this->addFilter($this->_table.".trans_date = 0");
        }

        $page = &$this->getPage();
        $page->register_scriptcode($this->openWindow());
        $page->register_scriptcode('
                $jq(document).ready(function() { 
                                                                                                  
                    $jq("#filtertitle").click(function(){
                        
                        if (!$jq("#filterform").is(":visible")) {
                            $jq("#filterform").slideDown("slow");                                                  
                              }else{
                            $jq("#filterform").slideUp("slow");
                              }
                    });
                                        
                 // function displayVals() {
                 //                var singleValues = $jq(\'#coa_code\').val();
                 //                $jq(\'#coa_name\').text(singleValues);
                 //                }
                 //                $jq(\'select\').change(displayVals);    

                
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
         ');

        $this->setTable($this->_table);    
    }

    function descriptor_Def() {
        return "[v_no]";
    }

    public function openWindow() {
        return 'function openWindow(url) { window.open(url);  }';
    }
            
    function adminheader() {
    $db = atkGetDb();
    $user = atkGetUser();
    $id_org = $user['employer_id'];
    
        if(isset($_GET['show'])){
            $coacode  = $_GET['coa_code'];
            $coaname = $_GET['coa_name'];
            $date1 = $_GET['pyear'];
            $date2 = $_GET['pmonth'];

        $coaNameRecord = $db->getrows("SELECT * FROM coa_".$user[employer_id]." WHERE coa_code = $coacode");
        $nameofcoa = $coaNameRecord[0]['coa_name'];
        }

        //---Ambil coa Code
        $coaRecord = $db->getrows("SELECT * FROM coa_".$user[employer_id]." b WHERE NOT EXISTS(SELECT * FROM(SELECT DISTINCT coa_parent FROM coa_".$user[employer_id].")a WHERE b.coa_code=a.coa_parent) ORDER BY coa_code");
        $coa_cd = $coaRecord[0]['coa_code'];
        $option1 = '';
            foreach ($coaRecord as $dataRow) {
                if($dataRow['coa_code'] == $coacode){
                    $selected = 'selected';
                }else{
                    $selected = '';
                }
                $option1 .= "<option value='" . $dataRow['coa_code'] . "' ".$selected.">" . $dataRow['coa_code'] . " - " . $dataRow['coa_name'] . "</option>";
            }   

        //---Ambil Year
        $yearRecord = $db->getrows("SELECT * FROM periode_year WHERE id_org = '$id_org' ORDER BY year DESC");
        $option2 = '';
            foreach ($yearRecord as $dataRow2) {
                if($dataRow2['id'] == $date1){
                    $selected2 = 'selected';
                }else{
                    $selected2 = '';
                }
            $option2 .= "<option value='" . $dataRow2['id'] . "' ".$selected2.">" . $dataRow2['year'] . "</option>";
        }
        
        //---Ambil Month
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

        $url = session_url(dispatch_url('report.general_ledger', 'cetak_general_ledger', array('coa_code' => $coacode, 'coa_name' => $coaname,'pyear' => $date1,'pmonth'=>$date2)), SESSION_NESTED);
    if (isset($_GET['show'])) {
        $document = '<input type="button" name="button" value="Download PDF" onclick="javascript:openWindow(\'' . $url . '\')">';
    }
        $content .= "<div id='filter'><h4>+ <a style='text-decoration:underline;cursor:pointer;' id='filtertitle'>Action</a></h4>";
        $content  = "<div id='filter'>";
        $content .= "<form method='GET' id='filterform' style='none;'>
                        <input type='hidden' name=atknodetype value=report.general_ledger />
                        <input type='hidden' name=atkaction value=admin />
                        
            <table width='100%' cellpadding='2' cellspacing='2' align='center' style='margin-top:10px;' border='0'>
                            <tr>
                                <td>COA Code</td>
                                <td>:
                                <select name='coa_code' id='coa_code'> " .$option1. "</select>
                                </td>
                            </tr>
                            <tr>
                                <td>Periode Year</td>
                                <td>: <select name='pyear' id='pyear' onchange='showMonth(this.value)'>" . $option2 ."</select>
                                </td>
                            </tr>
                            <tr>
                                <td>Periode Month</td><td>: <select name='pmonth' id='pmonth'>" .$option3. "</select></td>
                            </tr>
                            <tr>    
                                <td><input type=submit name='show' value='Submit' class='btn_save'>&nbsp;&nbsp;" . $document . "</td>                       
                            </tr>
                            <tr></tr>
            </table>        
                     </form></div>
           <table width='77%' style='margin-top:10px;' border='0'>         
            <tr>
                <td><h4>COA Name : ". $nameofcoa."</h4></td>
		       <td align=left><h4>COA Code : ". $coacode."</h4></td>
            </tr>
            </table>         
         ";
        $page = $content;
        return $page;
    }


    function saldo_debit_display($record, $mode){
        $ref = $record['v_no'];
        $coa = $record['coa'];
        $db = atkGetDb();
        if(!empty($coa)){

        $que     = $db->getrows("SELECT balance, MONTH(date_ob) AS `month`, YEAR(date_ob) AS `year`, opening_balance FROM coa WHERE  coa_code = $coa");
        $balance = $que[0]['balance'];
        $month_ob = $que[0]['month'];
        $year_ob = $que[0]['year'];
        $opening_balance = $que[0]['opening_balance'];

        // if($record!=0){
        //     $digit = number_format($record, 2, '.', ',');
        // }else{
        //     $digit = 0;
        // }

        if($balance == '0'){
            $res = $db->getrows("SELECT * FROM report_journal WHERE v_no = $ref and coa = '".$coa."'");
            $debit = $res[0]['debit'];  
            $credit = $res[0]['credit'];

            if($res[0]['periode_year'] == $year_ob && $res[0]['periode_month'] == $month_ob){
                $saldo = $opening_balance + $debit - $credit;
            }
            
            return $opening_balance." + ".$debit." - ".$credit." = ".number_format($saldo,2);
        }
        }
    }

     function saldo_credit_display($record, $mode){
        $ref = $record['v_no'];
        $coa = $record['coa'];
        $db = atkGetDb();

        if (!empty($coa)) {
            $que     = $db->getrows("SELECT * FROM coa WHERE  coa_code = $coa");
            $balance = $que[0]['balance'];

            $i = 1;
            if($balance == '1'){
                $res = $db->getrows("SELECT * FROM report_journal WHERE v_no = $ref");
                $credit = $res[0]['credit'];
                $debit = $res[0]['debit'];

                $cre_bal = $balance_credit.$i = ($balance.$i+$credit-$debit-1);

                return $cre_bal;    
            }
        }
     }

     function v_no_display($record, $mode){
        $ref = $record['v_no'];
        $url= session_url("dispatch.php?atknodetype=transaction.journal&atkaction=view&v_no=".$record['v_no'], SESSION_NESTED);
        $a = "<a href='javascript:void(0);' onmouseover='window.status=\"hide link\";return true;' onclick='window.open(\"".$url."\")'> $ref </a>";
        return $a;
     }

    function action_getPeriodeMonth(){
        $db = atkGetDb();
        $pyear = $_REQUEST["pyear"];

        $getRow = $db->getrows("SELECT * FROM periode_month WHERE id_year = '".$pyear."'");
        var_dump("SELECT * FROM periode_month WHERE id_year = '".$pyear."'");
        foreach ($getRow as $key => $value) {
            $select .= "<option value=" . $value['month'] . ">" . $value['name'] . "</option>";
        }
        echo $select;
    }

    function action_cetak_general_ledger() {

        $db   = atkGetDb();
        $user = atkGetUser();

        $id_org = $user[employer_id];
        $this->addStyle("style.css");
        $mpdf = new mPDF('', 'A4');
        $coa      = $_GET['coa_code'];
        $year       = $_GET['pyear'];
        $month      = $_GET['pmonth'];

        $coaNameRecord  = $db->getrows("SELECT * FROM coa_".$user[employer_id]." WHERE coa_code = $coa");
        $ambil_user     = $db->getrows("SELECT * FROM organization WHERE `type` = '2' AND `id` = '".$id_org."'");
        $ambil_general_report = $db->getrows("SELECT 
                                            `trans_date` AS `Date`,
                                            `desc` AS `Description`,
                                            `v_no` AS `Reff`,
                                            `journal_type` AS `Journal_Type`,
                                            `coa` AS `COA`,
                                            `debit` AS `Debit`,
                                            `credit` AS `Credit`
                                             FROM `report_journal`
                                             WHERE `coa` = '".$coa."'
                                             AND `periode_year` = '".$year."'
                                             AND `periode_month` = '".$month."'");
        $ambil_periode = $db->getrows("SELECT CASE b.`month` WHEN '01' THEN 'January' WHEN '02' THEN 'February'
                                        WHEN '03' THEN 'March' WHEN '04' THEN 'April'
                                        WHEN '05' THEN 'May' WHEN '06' THEN 'June'
                                        WHEN '07' THEN 'July' WHEN '08' THEN 'August'
                                        WHEN '09' THEN 'September' WHEN '10' THEN 'October'
                                        WHEN '11' THEN 'November' WHEN '12' THEN 'December' END AS month_name, 
                                        b.*, a.* 
                                        FROM periode_year a, periode_month b WHERE a.`id` = b.`id_year` AND a.`id` = '".$year."' AND b.`month` = '".$month."'");
            $nama_bulan = $ambil_periode[0]['month_name'];
            $nama_tahun = $ambil_periode[0]['year'];
        $isi = '<html>
                        <head>
                        <meta http-equiv="Content-Language" content="en-us">
                        <meta http-equiv="Content-Type" content="text/html; charset=windows-1252">
                        <title>General Ledger</title>
                        <style>
                            body{font-size:8pt;}
                            #teball{text-align:left;font-weight:bold;}
                            #tebalc{text-align:center;font-weight:bold;}
                            #tebalr{text-align:right;font-weight:bold;}
                            #tebalul{text-align:center;font-weight:bold;}
                            #tebalulr{text-align:right;font-weight:bold;text-decoration:underline;}
                            #tebalcjudul{text-align:center;font-weight:bold;font-size:14pt;}
                            #tebalcsubjudul{text-align:center;font-weight:bold;font-size:11pt;}
                            #squarebig{border:1px solid black;width:40px;height:20px;}
                            #squaresmall{border:1px solid black;width:20px;height:10px;}
                            #garis2{border-bottom:double #000000;}
                            table { border-collapse:collapse; }
                            td {height:25px;}
                        </style>
                        </head>

                        <body>
                        
                            <div style="padding-top: 20px;" height="100px" align="center">                                                                        
                                <h3 align="center">' . $ambil_user[0]["name"] . '</h3>
                                <a><strong>General Ledger Report</strong></a> <br> <br>
                                <a><strong>'.$nama_bulan.' '.$nama_tahun.'</strong></a>
                            </div>
                            <table border="1" width="100%">
                                    <tr>
                                        <td colspan="10">
                                        <table border="1" width="100%">
                                            <tr>
                                                <td align="left" width="100%" colspan="5">A</td>
                                                <td align="right" width="100%" colspan="5">B</td>
                                            </tr>
                                        </table>
                                        </td>
                                    </tr>
                                    <tr>    
                                        <td width="10px" align="center" id="tebalul">No</td>
                                        <td width="10px" align="center" id="tebalul">Date</td>
                                        <td width="10px" align="center" id="tebalul">Description</td>
                                        <td width="10px" align="center" id="tebalul">Reff</td>
                                        <td width="10px" align="center" id="tebalul">Journal Type</td>
                                        <td width="10px" align="center" id="tebalul">COA</td>
                                        <td width="10px" align="center" id="tebalul">Debit</td>
                                        <td width="10px" align="center" id="tebalul">Credit</td>
                                        <td width="10px" align="center" id="tebalul">Saldo Debit</td>
                                        <td width="10px" align="center" id="tebalul">Saldo Credit</td>
                                    </tr> 
                            </table>
                                ';

        $no = 1;
        foreach ($ambil_general_report as $dataRow) {
            $isi .='<tr>
                        <td align="center" id="tebalul">' . $no++ . '<td/>
                        <td align="center">' .$dataRow['Date']. '<td/>
                        <td align="center">' .$dataRow['Description']. '<td/>   
                        <td align="center">' .$dataRow['Reff']. '<td/>
                        <td align="center">' .$dataRow['Journal_Type']. '<td/>      
                        <td align="center">' .$dataRow['COA']. '<td/> 
                        <td align="right">' .$dataRow['Debit']. '<td/>   
                        <td align="right">' .$dataRow['Credit']. '<td/>   
                    </tr>';
        }
        $isi .='    
        
                            </table>                          
                        </body>
               </html> 
            
            ';

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
        $mpdf->WriteHTML($isi);
        $namepdf = "General Ledger List" . ".pdf";
        $mpdf->Output($namepdf, "I");        
        return true;
    }

}
?>