<?php

/**
* 
*/
class profit_loss extends atkNode
{
	
    var $_module = "report";
    var $_node = "profit_loss";
    var $_table = "report_journal";

    function profit_loss() {
        $this->atkNode($this->_node, NF_READONLY | NF_NO_EXTENDED_SEARCH);
        $action = array("getPeriodeMonth","profit_loss");
        $this->addAllowedAction($action);    

        $this->add(new atkDateAttribute("trans_date"))->setLabel("Date");

        $this->add(new atkTextAttribute("desc"))->setLabel("Description");

        $this->setTable($this->_table);
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

    public function formSearch($option1, $option2, $option3)
    {
    	$content  = "<div id='filter'><h4>+ <a style='text-decoration:underline;cursor:pointer;' id='filtertitle'>Action</a></h4>";
        $content .= "<form method='GET' id='filterform' style='display:none;'>
                        <input type='hidden' name=atknodetype value=report.profit_loss/>
                        <input type='hidden' name=atkaction value=admin />
                        
			            <table width='100%' cellpadding='2' cellspacing='2' align='center' style='margin-top:10px;' border='0'>
			                            <tr>
			                                <td>Organization</td>
			                                <td>: <select name='org' id='org'> " .$option1. "</select>
			                                </td>
			                            </tr>
			                            <tr>
			                                <td>Periode Year</td>
			                                <td>: <select name='pyear' id='pyear' onchange='showMonth(this.value)'>" . $option2 ."</select>
			                                </td>
			                            </tr>
			                            <tr>
			                                <td>Periode Month</td>
			                                <td>: <select name='pmonth' id='pmonth'>" .$option3. "</select></td>
			                            </tr>
			                            <tr>    
			                                <td colspan=2><input type=submit name='show' value='Submit' class='btn_save'></td>                       
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
    		// $getOrg = $db->getrows("SELECT * FROM organization WHERE id ='".$org."'");
			if(isset($_GET['show'])){
	            $org = $_GET['org'];
	            $date1 = $_GET['pyear'];
	            $date2 = $_GET['pmonth'];
        	}
    		$getOrg = $db->getrows("SELECT * FROM organization WHERE type=2 and id ='".$org."'");
    		foreach ($getOrg as $key => $value) {
	            if($value['id'] == $$org){
	                $selected1 = 'selected';
	            }else{
	                $selected1 = '';
	            }
    			$option1 .= "<option value='".$value['id']."' ".$selected1.">".$value['name']."</option>";
    		}

	        //---Ambil Year
	        $yearRecord = $db->getrows("SELECT * FROM periode_year WHERE id_org = '".$org."' order by year desc");
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
    		$return .= $this->formSearch($option1, $option2, $option3);
			
		}
    	return $return;
	}

	function getRevenue($id_org){
		$db = atkGetDb();
		// $user = getUser();
		// $id_org = $user['employer_id'];
		$q_get = "
			SELECT
			  `c`.`coa_code` AS `coa`,
			  `c`.`coa_name` AS `coa_name`,
			  SUM(`t`.`debit`) AS `debit`,
			  SUM(`t`.`credit`) AS `credit`,
			  (SUM(`t`.`credit`) - SUM(`t`.`debit`)) AS `total`
			FROM ((`transaction` `t`
			    JOIN `coa_".$id_org."` `c`)
			   JOIN `journal` `j`)
			WHERE ((`t`.`coa` = `c`.`coa_code`)
			       AND (`j`.`id_journal` = `t`.`id_journal`)
			       AND (`j`.`posting` = 1)
			       AND (`c`.`coa_jenis` = 'r')
			       AND (j.id_org = ".$id_org."))
			GROUP BY `t`.`coa`
		";

		$get = $db->getrows($q_get);
		foreach ($get as $key => $value) {
			$content .= 
			"<tr>
				<td>".$value['coa_name']."</td>
				<td>&nbsp;</td>
				<td align='right' width='100px'>".number_format($value['total'],2)."</td>
			</tr>";
			$total = $total + $value['total'];
		}

		return array($content,$total);
	}

	function getExpense($id_org){
		$db = atkGetDb();
		// $user = getUser();
		// $id_org = $user['employer_id'];
		$q_get = "
			SELECT
			  `c`.`coa_code` AS `coa`,
			  `c`.`coa_name` AS `coa_name`,
			  SUM(`t`.`debit`) AS `debit`,
			  SUM(`t`.`credit`) AS `credit`,
			  (SUM(`t`.`debit`) - SUM(`t`.`credit`)) AS `total`
			FROM ((`transaction` `t`
			    JOIN `coa_".$id_org."` `c`)
			   JOIN `journal` `j`)
			WHERE ((`t`.`coa` = `c`.`coa_code`)
			       AND (`j`.`id_journal` = `t`.`id_journal`)
			       AND (`j`.`posting` = 1)
			       AND (`c`.`coa_jenis` = 'e')
			       AND (j.id_org = ".$id_org."))
			GROUP BY `t`.`coa`
    		";

		$get = $db->getrows($q_get);
		foreach ($get as $key => $value) {
			$content .= 
			"<tr>
				<td>".$value['coa_name']."</td>
				<td align='right' width='100px'>".number_format($value['total'],2)."</td>
				<td>&nbsp;</td>
			</tr>";
			$total = $total + $value['total'];
		}

		return array($content,$total);
	}

	function action_profit_loss(){
		$user = getUser();
		$id_org = $user['employer_id'];
		if (!empty($_POST['org'])) {
			$id_org = $_POST['org'];
		}

		if(!empty($id_org)){
			
			$content .= $this->adminheader();
			$revenue = $this->getRevenue($id_org);
			$revenueTd = $revenue[0];
			$revenueTotal = $revenue[1];

			$expense = $this->getExpense($id_org);
			$expenseTd = $expense[0];
			$expenseTotal = $expense[1];

			$pl = $revenueTotal - $expenseTotal;

			$content .= "<table border=0>";
			$content .= 
				"<tr style='font-weight:bold;'>
					<td colspan=3>".atktext("pendapatan_usaha")."</td>
				</tr>";
			$content .= $revenueTd;
			$content .= 
				"<tr style='font-weight:bold;'>
					<td>".atktext("jum_pendapatan")."</td>
					<td>&nbsp;</td>
					<td align='right'>".number_format($revenueTotal,2)."</td>
				</tr>";
			$content .= 
				"<tr style='font-weight:bold;'>
					<td colspan=3>".atktext("beban_usaha")."</td>
				</tr>";
			$content .= $expenseTd;
			$content .= 
				"<tr style='font-weight:bold;'>
					<td>".atktext("jum_beban")."</td>
					<td>&nbsp;</td>
					<td align='right'>".number_format($expenseTotal,2)."</td>
				</tr>";
			$content .= 
				"<tr style='font-weight:bold;'>
					<td>".atktext("laba_bersih")."</td>
					<td>&nbsp;</td>
					<td align='right'>".number_format($pl,2)."</td>
				</tr>";

			$content .= "</table>";
		}else{
			$content = atktext("error_node_action_access_denied");
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

}
?>