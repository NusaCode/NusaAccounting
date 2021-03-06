<?php

include_once (atkconfig("atkroot") . "lib/mpdf/mpdf.php");

/*
 * Author : Dimas Ardi N
 * Created : Aug 2013
 */

class master_list_departement extends atkNode {

    var $_module = "report";
    var $_node = "master_list_departement";
    var $_table = "master_list_department";
    var $_order = "code";


    function master_list_departement() {
        $user = atkGetUser();
        $this->atkNode($this->_node, NF_READONLY | NF_NO_EXTENDED_SEARCH);
        $action = array("cetak_department");
        $this->addAllowedAction($action);

        $this->add(new atkAttribute("code", AF_SEARCHABLE));

        $this->add(new atkAttribute("name", AF_SEARCHABLE));
        
        $this->add(new atkAttribute("description", AF_SEARCHABLE));
        
        $page = &$this->getPage();
        $page->register_scriptcode($this->openWindow());
        $page->register_scriptcode('
				var $jq = jQuery.noConflict();
				$jq(document).ready(function() { 
				                                                                                  
					$jq("#filtertitle").click(function(){
					    
						if (!$jq("#filterform").is(":visible")) {
							$jq("#filterform").slideDown("slow");                                                  
						      }else{
							$jq("#filterform").slideUp("slow");
						      }
					});
                                        
								
			
				});
         ');
        $this->addFilter($this->_table.".id_org = '".$user[employer_id]."'");
        $this->setOrder($this->_order . ".ASC");
        $this->setTable($this->_table);
    }

    function descriptor_def() {
        return "[code]";
    }

     public function openWindow() {
        return 'function openWindow(url) { window.open(url);  }';
    }

    function adminheader() {

        $url = session_url(dispatch_url('report.master_list_departement', 'cetak_department'), SESSION_NESTED);
        $document = '<input type="button" name="button" value="Download PDF" onclick="javascript:openWindow(\'' . $url . '\')">';

        $content .= "<div id='filter'><h4>+ <a style='text-decoration:underline;cursor:pointer;' id='filtertitle'>Action</a></h4>";
        $content .= "<form method='POST' id='filterform' name='filterform' style='display:none; action=\"$PHP_SELF\">
                        <input type='hidden' name=atknodetype value=report.master_list_departement />
                        <input type='hidden' name=atkaction value=admin />
                        
			<table width='100%' cellpadding='2' cellspacing='2' align='center' style='margin-top:10px;' border='0'>
                            <tr>	
                                <td>" . $document . "</td>
                            </tr>	
			</table>		
                     </form></div>
					
		 ";
        $page = $content;
        return $page;
    }
    
    function action_cetak_department(){
        
        $user = atkGetUser();
        $db = atkGetDb();

        $id_org = $user[employer_id];
        $this->addStyle("style.css");
        $mpdf = new mPDF('','A4'); 
             
        $ambil_user = $db->getrows("SELECT * FROM organization WHERE `type` = '2' AND id = '$id_org'");        
        $ambil_jurnal_departement = $db->getrows("SELECT `code`, `name`, `description` FROM employee_department WHERE id_org = '$id_org'");
                       
        $isi = '<html>
                        <head>
                        <meta http-equiv="Content-Language" content="en-us">
                        <meta http-equiv="Content-Type" content="text/html; charset=windows-1252">
                        <title>Department List Report</title>
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
                                <a><strong>Division/Department Check List</strong></a>
                            </div>
                            
                                                        
                            <table border="1" width="100%" cellpadding="5px">
                                    <tr>
                                        <td align="center" id="tebalul">No</td>
                                        <td align="center" id="tebalul">Code</td>
                                        <td align="center" id="tebalul">Name</td>
                                        <td align="center" id="tebalul">Description</td>                                        
                                    </tr> ';
        
        $no = 1;
        foreach($ambil_jurnal_departement as $dataRow){
                                 
            $isi .='<tr>
                        <td align="center" id="tebalul">'.$no++.'<td/>
                        <td align="left">'.$dataRow['code'].'<td/>
                        <td align="left">'.$dataRow['name'].'<td/>      
                        <td align="left">'.$dataRow['description'].'<td/>  
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
        $namepdf = "Department List".".pdf";
        $mpdf->Output($namepdf,"I");
    }
    
}

?>