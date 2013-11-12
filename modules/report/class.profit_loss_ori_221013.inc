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
        $action = array("getPeriodeMonth","profit_loss", "cetak_profit_loss");
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
		                    xmlhttp.open("GET","dispatch.php?atknodetype=report.profit_loss&atkaction=getPeriodeMonth&atklevel=-1&atkprevlevel=0&pyear="+pyear,true);
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

    function getProfitLoss($id_org, $yyyymm, $pl_month){

        $db = atkGetDb();
        $year_hid = $_REQUEST['pyearhid'];
        $yyyymm = $year_hid.$pl_month;
            
        $file = "./lib/query/r_profit_loss.txt";
            $open = fopen($file, 'r+');
            $theData = fread($open, filesize($file));
            fclose($open);

            $read = str_replace('#@id_org#@', $id_org, $theData);
            $read = str_replace('#@yyyymm#@', $yyyymm, $read);

            $get_profit_loss = $db->getrows($read);
                return $get_profit_loss;
    }

    function getModel($getProfitLoss, $ambil_user, $pl_year, $pl_month, $year, $month){
        $user = atkGetUser();
        $db   = atkGetDb();

        $page  = &atknew("atk.ui.atkpage");
        $theme = &atkTheme::getInstance();
        $page->register_style($theme->stylePath("style.css"));
        $page->register_style($theme->stylePath("recordlist.css"));

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
                            <div style="padding-top: 20px;" height="100px" align="center">                                                                        
                                <h3 align="center">' . $ambil_user[0]["name"] . '</h3>
                                <strong> Profit & Loss Statement</strong> <br> <br>
                                <strong>' .date("F Y", mktime(0, 0, 0, $month, 3, $year)). '</strong>
                            </div>
                            &nbsp;&nbsp;&nbsp;&nbsp;
                            <div style="padding: 20px; border: 1px solid #000000;">
                                <table border="0" width="100%" class="recordListContainer" align="center" cellpadding="2">';

        $no = 0;
        foreach ($getProfitLoss as $value) {
            if($value['coa_code'] == '1. DAFTAR'){
                $isi .='<tr ' . $no . '>
                            <td align="right" class="recordListTd recordListTdLast"><b>' . $value['coa_code'] . '</b></td>
                            <td align="left" class="recordListTd recordListTdLast"><b>' . $value['coa_name'] . '</b></td>
                            <td align="right" class="recordListTd recordListTdLast">' . $value['balance'] . '</td>
                        </tr>'; 
            }elseif($value['coa_code'] == '2. DAFTAR'){
                $isi .='<tr ' . $no . '>
                            <td align="right" class="recordListTd recordListTdLast"><b>' . $value['coa_code'] . '</b></td>
                            <td align="left" class="recordListTd recordListTdLast"><b>' . $value['coa_name'] . '</b></td>
                            <td align="right" class="recordListTd recordListTdLast">' . $value['balance'] . '</td>
                        </tr>';
            }elseif($value['coa_code'] == 'SUB TOTAL'){
                $isi .='<tr ' . $no . '>
                            <td align="left"></td>
                            <td align="left"></td>
                            <td align="right"><b>__________+</b></td>
                        </tr>
                        <tr>
                            <td align="right" class="recordListTd recordListTdLast"><b>' . $value['coa_code'] . '</b></td>
                            <td align="left" class="recordListTd recordListTdLast"><b>' . $value['coa_name'] . '</b></td>                           
                            <td align="right" class="recordListTd recordListTdLast"><b>' . $value['balance'] . '</b></td>
                        </tr><tr><td colspan="3" class="recordListTd recordListTdLast"></td>&nbsp;</tr>';
            }elseif($value['coa_code'] == 'TOTAL'){
                    $isi .='<tr ' . $no . '>
                            <td align="right" class="recordListTd recordListTdLast"><b>' . $value['coa_code'] . '</b></td>
                            <td align="left" class="recordListTd recordListTdLast"><b>' . $value['coa_name'] . '</b></td>                           
                            <td align="right" class="recordListTd recordListTdLast" style="border-top: 2px double #000000; border-bottom: 2px double #000000;"><b>' . $value['balance'] . '</b></td>
                        </tr>';
            }else{
                $isi .='<tr ' . $no . '>
                            <td align="left"></td>
                            <td align="left" class="recordListTd recordListTdLast">' . $value['coa_name'] . '</td>                           
                            <td align="right" class="recordListTd recordListTdLast">' . $value['balance'] . '</td>
                        </tr>';
            }
        }

        $isi .='
                                </table>   
                            </div>                       
                        </body>
               </html> 
            
            ';
        return $isi;
    }


    public function formSearch($option1, $option2, $option3, $pl_org, $pl_year, $pl_month, $hid){	

    	$url = session_url(dispatch_url('report.profit_loss', 'cetak_profit_loss',array('org' => $pl_org,'pyear' => $pl_year,'pmonth'=>$pl_month, 'pyearhid'=>$hid)), SESSION_NESTED);
            if (isset($_REQUEST['show'])) {
                $document = '<input type="button" name="button" value="Download PDF" onclick="javascript:openWindow(\'' . $url . '\')">';
                $document = '<a href="javascript:void(0);" onmouseover="window.status=\'hide link\';return true;" onclick="window.location.href=\''.$url.'\'""><input type="button" name="button" value="Download PDF"></a>';
                $pyearhid = $_REQUEST['pyearhid'];
            }
    	$content  = "<div id='filter'><h4>+ <a style='text-decoration:underline;cursor:pointer;' id='filtertitle'>Action</a></h4>";
        $content .= "<form method='POST' id='filterform' style='display:yes;'>
                        <input type='hidden' name=atknodetype value=report.profit_loss />
                        <input type='hidden' name=atkaction value=profit_loss />
                        
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
	            $org      = $_REQUEST['org'];
	            $date1    = $_REQUEST['pyear'];
	            $date2    = $_REQUEST['pmonth'];
                $pl_org   = $_REQUEST['org'];
                $pl_year  = $_REQUEST['pyear'];
                $pl_month = $_REQUEST['pmonth'];
                $hid      = $_REQUEST['pyearhid'];
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

	        //---Ambil Year
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
    		$return .= $this->formSearch($option1, $option2, $option3, $pl_org, $pl_year, $pl_month, $hid);			
		}
    	return $return;
	}

	function action_profit_loss(){
		$db = atkGetDb();
		$user = getUser();
		$id_org = $user['employer_id'];


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
            	$action = 'profit_loss';
				$getProfitLoss = $this->getProfitLoss($id_org, $yyyymm, $pl_month);
				$getModel = $this->getModel($getProfitLoss, $ambil_user, $pl_year, $pl_month, $year, $month);
				$content .= $getModel;
		}
		/*
		* OUTPUT
		*/

        $page = &atknew("atk.ui.atkpage");
	    $page->register_scriptcode($this->jsSearch());
        $ui = &atkinstance("atk.ui.atkui");
        $theme = &atkTheme::getInstance();
        $output = &atkOutput::getInstance();
        $page->register_style($theme->stylePath("style.css"));

        $box = $ui->renderBox(array("title"=>atktext("Profit & Loss Report"),"content" =>$content));

        $page->addContent($box);
        $output->output($page->render(atktext('Profit & Loss Report'), true));
	}

	function action_cetak_profit_loss() {
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
                $action = 'cetak_profit_loss';
                $getProfitLoss = $this->getProfitLoss($id_org, $yyyymm, $pl_month);
                $getModel = $this->getModel($getProfitLoss, $ambil_user, $pl_year, $pl_month, $year, $month);

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
        $namepdf = "Profit_Loss_List" . ".pdf";
        $mpdf->Output($namepdf, "I");        
        return true;
    }

}
?>