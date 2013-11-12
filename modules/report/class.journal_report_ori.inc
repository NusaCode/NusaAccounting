<?php
include_once (atkconfig("atkroot") . "lib/mpdf/mpdf.php");

/*
 * membuat list coa by: Muhammad Ikhsan Ramadhan
 * modul: report
 * node class: master_list_jurnal_type
 */

class journal_report extends atkNode {

    var $_module = "report";
    var $_node = "journal_report";
    var $_table = "report_journal";

    function journal_report() {

        $this->atkNode($this->_node, NF_READONLY | NF_NO_EXTENDED_SEARCH);

        $this->add(new atkAttribute("v_no"));

        $this->add(new atkAttribute("journal_type"));

        $this->add(new atkDateAttribute("trans_date"));

        $this->add(new atkAttribute("coa"));

        $this->add(new atkAttribute("debit"));

        $this->add(new atkAttribute("credit"));

        $this->add(new atkTextAttribute("desc"));

        if (isset($_GET['show'])) {

            if (strlen($_GET['tgl2']) == 1) {
                $tgl2 = '0' . $_GET['tgl2'];
            } else {
                $tgl2 = $_GET['tgl2'];
            }

            if (strlen($_GET['tglakhir2']) == 1) {
                $tglakhir2 = '0' . $_GET['tglakhir2'];
            } else {
                $tglakhir2 = $_GET['tglakhir2'];
            }

            $trans1 = $_GET['type_jurnal'];
            $trans2 = $_GET['type_jurnal_akhir'];
            $date1 = $_GET['tgl2'] . $_GET['tgl3'];
            $date2 = $_GET['tglakhir2'] . $_GET['tglakhir3'];

            $where = "";

            if ($date1 != '') {
                $where.="DATE_FORMAT(report_journal.trans_date,'%Y-%m') >=  '" . $_GET['tgl3'] . "-" . $tgl2 . "' ";
            } else {
                $where.="report_journal.trans_date like '%%'";
            }

            if ($date2 != '') {
                $where.="AND DATE_FORMAT(report_journal.trans_date,'%Y-%m') <=  '" . $_GET['tglakhir3'] . "-" . $tglakhir2 . "' ";
            } else {
                $where.="AND report_journal.trans_date like '%%'";
            }

//            if ($trans1 != '') {
//                $where.="AND report_journal.journal_type BETWEEN '" . $trans1 . "' ";
//            } else {
//                $where.="";
//            }
//
//            if ($trans2 != '') {
//                $where.="AND report_journal.journal_type BETWEEN '" . $trans2 . "'";
//            } else {
//                $where.="";
//            }
            
            if(!empty($trans1) && empty($trans2)) {
                $where .= "AND report_journal.journal_type BETWEEN '" . $trans1 . "' AND '" . $trans1 . "' ";
            } elseif (!empty($trans1) && !empty($trans2)) {
                $where .= "AND report_journal.journal_type BETWEEN '" . $trans1 . "' AND '" . $trans2 . "' ";
            } else {
                $where.="";
            }

            $this->addFilter($where);
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
         ');

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

    function adminheader() {

        $db = atkGetDb();
        $ambil_jurnal_type = $db->getrows("SELECT `code` FROM journal_type");

        $tipe_jurnal = '';
        foreach ($ambil_jurnal_type as $dataRow) {
            $tipe_jurnal .= "<option value=" . $dataRow['code'] . ">" . $dataRow['code'] . "</option>";
        }
        
        if(isset($_GET['show'])){		    
			$month=$_GET['tgl2'];
			$month2=$_GET['tglakhir2'];
			$year=$_GET['tgl3'];
			$year2=$_GET['tglakhir3'];
                        
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
                
        
        $url = session_url(dispatch_url('report.journal_report', 'cetak_journal_report', array('month' => $tgl2,'month2'=>$tglakhir2,'year'=>$year,'year2'=>$year2)), SESSION_NESTED);
        $document = '<input type="button" name="button" value="Download Pdf" onclick="javascript:openWindow(\'' . $url . '\')">';
        $content = "<div id='filter'><h4>+ <a style='text-decoration:underline;cursor:pointer;' id='filtertitle'>Action</a></h4>";
        $content .= "<form method='GET' id='filterform' style='display:none;'>
                        <input type='hidden' name=atknodetype value=report.journal_report />
                        <input type='hidden' name=atkaction value=admin />
                        
			<table width='100%' cellpadding='2' cellspacing='2' align='center' style='margin-top:10px;' border='0'>
                            <tr>
                                <td>From Journal</td>
                                <td>:
                                <select name='type_jurnal' id='type_jurnal'> <option value=''></option>" . $tipe_jurnal . $_GET['type_jurnal'] . "</select>
                                </td>
                            <tr>
                            <tr>
                                <td>Through Journal</td>
                                <td>:
                                <select name='type_jurnal_akhir' id='type_jurnal_akhir'> <option value=''></option>" . $tipe_jurnal . $_GET['type_jurnal_akhir'] . "</select>
                                </td>
                            <tr>
                            <tr> 
                                <td>Trans date</td><td>: <select name=tgl2 id=tgl2 ><option value=''></option>" . $this->monthList($_GET['tgl2']) . "</select><input size=5 type=text name=tgl3 id=tgl3 value=" . $_GET['tgl3'] . " ></td>
                            </tr>
                            <tr>
                                <td>Trough</td><td>: <select name=tglakhir2 id=tglakhir2 ><option value=''></option>" . $this->monthList($_GET['tglakhir2']) . "</select><input size=5 type=text name=tglakhir3 id=tglakhir3 value=" . $_GET['tglakhir3'] . " ></td>
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

    function action_cetak_journal_report() {

        $db = atkGetDb();
        $this->addStyle("style.css");
        $mpdf = new mPDF('', 'A4');
        
        $month = $_GET['month'];
	$year = $_GET['year'];
	$month2 = $_GET['month2'];
	$year2 = $_GET['year2'];
         
        $date_awal=$year.'-'.$month.'-01';
	$date_akhir=$year2.'-'.$month2.'-31';
      
        $ambil_user = $db->getrows("SELECT * FROM organization WHERE `type` = '2'");
        $ambil_jurnal_report = $db->getrows("SELECT
                                            `j`.`v_no`       AS `v_no`,
                                            `jt`.`code`      AS `journal_type`,
                                            `j`.`trans_date` AS `trans_date`,
                                            `t`.`coa`        AS `coa`,
                                            `t`.`desc`       AS `desc`,
                                            `t`.`debit`      AS `debit`,
                                            `t`.`credit`     AS `credit`
                                          FROM (((`journal` `j`
                                                LEFT JOIN `transaction` `t`
                                                    ON ((`j`.`id_journal` = `t`.`id_journal`)))
                                                LEFT JOIN `journal_type` `jt`
                                                    ON ((`jt`.`id` = `j`.`id_journal_type`)))
                                                LEFT JOIN `coa` `c`
                                                    ON ((`c`.`coa_code` = `t`.`coa`)))
                                          WHERE j.`trans_date` >= '".$date_awal."' AND j.`trans_date`<= '".$date_akhir."'
                                          ORDER BY `j`.`v_no`,`j`.`trans_date`");

        $isi = '<html>
                        <head>
                        <meta http-equiv="Content-Language" content="en-us">
                        <meta http-equiv="Content-Type" content="text/html; charset=windows-1252">
                        <title>Manajemen Building Apartemen Cer</title>
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
                        
                            <div style="padding-top: 20px;" height="100px">                                                                        
                                <h3>' . $ambil_user[0]["name"] . '</h3>
                                <a><strong>Journal Report</strong></a>
                            </div>
                            
                                                        
                            <table border="1" width="100%">
                                    <tr>
                                        <td width="10px" align="center" id="tebalul">No</td>
                                        <td width="10px" align="center" id="tebalul">V no</td>
                                        <td width="10px" align="center" id="tebalul">Journal Type</td>
                                        <td width="10px" align="center" id="tebalul">Trans Date</td>
                                        <td width="10px" align="center" id="tebalul">Coa</td>
                                        <td width="10px" align="center" id="tebalul">Debit</td>
                                        <td width="10px" align="center" id="tebalul">Credit</td>
                                        <td width="10px" align="center" id="tebalul">Description</td>
                                    </tr> ';

        $no = 1;
        foreach ($ambil_jurnal_report as $dataRow) {
            $isi .='<tr>
                        <td align="center" id="tebalul">' . $no++ . '<td/>
                        <td align="center">' . $dataRow['v_no'] . '<td/>
                        <td align="center">' . $dataRow['journal_type'] . '<td/>      
                        <td align="center">' . $dataRow['trans_date'] . '<td/>  
                        <td align="center">' . $dataRow['coa'] . '<td/> 
                        <td align="center">' . $dataRow['debit'] . '<td/>   
                        <td align="center">' . $dataRow['credit'] . '<td/>   
                        <td align="center">' . $dataRow['desc'] . '<td/>   
                    </tr>';
        }
        $isi .='    
        
                            </table>                          
                        </body>
               </html> 
            
            ';

        $footer = "
        <div id='teball'><br>" . $ambil_user[0]["name"] . "</div>
        </div>
        ";

        $mpdf->WriteHTML($isi);
        $mpdf->SetHTMLFooter($footer);
        $namepdf = "Jurnal Report List" . ".pdf";
        $mpdf->Output($namepdf, "I");
        
        return true;
    }
    

}
?>