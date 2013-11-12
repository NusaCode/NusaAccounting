<?php

include_once (atkconfig("atkroot") . "lib/mpdf/mpdf.php");

/*
 * membuat list coa by: Muhammad Ikhsan Ramadhan
 * modul: report
 * node class: master_list_coa
 */

class master_list_coa extends atkNode {

    var $_module = "report";
    var $_node = "master_list_coa";
    var $_table = "coa";
    var $_order = "coa_code";

    function master_list_coa() {
        
        $this->atkNode($this->_node, NF_READONLY | NF_NO_EXTENDED_SEARCH);

        $this->add(new atkAttribute("coa_code"));

        $this->add(new atkAttribute("coa_name"));
        
        $this->add(new atkListAttribute("coa_jenis", array("Asset", "Liabilities", "Owner Equities", "Revenue", "Expense"), array("a", "l", "o", "r", "e"), 0));

        $this->add(new atkListAttribute("balance", array("Debet", "Kredit"), array(0, 1)));
        
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

        $this->setOrder($this->_order . ".ASC");
        $this->setTable($this->_table);
    }

    function descriptor_def() {
        return "[coa_code]";
    }
    
    public function openWindow() {
        return 'function openWindow(url) { window.open(url);  }';
    }

    function adminheader() {

        $url = session_url(dispatch_url('report.master_list_coa', 'cetak_coa'), SESSION_NESTED);
        $document = '<input type="button" name="button" value="Download Pdf" onclick="javascript:openWindow(\'' . $url . '\')">';

        $content .= "<div id='filter'><h4>+ <a style='text-decoration:underline;cursor:pointer;' id='filtertitle'>Action</a></h4>";
        $content .= "<form method='POST' id='filterform' name='filterform' style='display:none; action=\"$PHP_SELF\">
                        <input type='hidden' name=atknodetype value=report.master_list_coa />
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
    
    function action_cetak_coa(){
        
        $db = atkGetDb();
        $this->addStyle("style.css");
        $mpdf = new mPDF('','A4'); 
             
        $ambil_user = $db->getrows("SELECT * FROM organization WHERE `type` = '2'");
        
        $ambil_coa_list = $db->getrows("SELECT * FROM ".$this->_table);
        
        
        
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
                                <a><strong>Chart of Account Check List</strong></a>
                            </div>
                            
                                                        
                            <table border="1" width="100%">
                                    <tr>
                                        <td width="10px" align="center" id="tebalul">No</td>
                                        <td width="10px" align="center" id="tebalul">COA Code</td>
                                        <td width="10px" align="center" id="tebalul">COA Name</td>
                                        <td width="10px" align="center" id="tebalul">COA Jenis</td>
                                        <td width="10px" align="center" id="tebalul">Balance</td>
                                    </tr> ';
        
        $no = 1;
        foreach($ambil_coa_list as $dataRow){
            
            if($dataRow['balance'] == '0'){      
               
                $data_balance = "Debet";
            }else{
                
                $data_balance = "Kredit";
            }

            switch ($dataRow['coa_jenis']) {
                case 'a':
                   $coa_jenis = "Asset";
                    break;
                case 'l':
                   $coa_jenis = "Liabilities";
                    break;
                case 'o':
                   $coa_jenis = "Owner Equities";
                    break;
                case 'r':
                   $coa_jenis = "Revenue";
                    break;
                case 'e':
                   $coa_jenis = "Expense";
                    break;
            }
            
                     
            $isi .='<tr>
                        <td align="center" id="tebalul">'.$no++.'<td/>
                        <td align="center">'.$dataRow['coa_code'].'<td/>
                        <td align="center">'.$dataRow['coa_name'].'<td/>    
                        <td align="center">'.$coa_jenis.'<td/>     
                        <td align="center">'.$data_balance.'<td/> 
                    </tr>';                     
        }
           $isi .='    
        
                            </table>                          
                        </body>
               </html> 
            
            ';
        
        $footer = "
        <div id='teball'><br>".$ambil_user[0]["name"] ."</div>
        </div>
        ";

        
        $mpdf->WriteHTML($isi);
        $mpdf->SetHTMLFooter($footer);
        $namepdf = "COA List".".pdf";
        $mpdf->Output($namepdf,"I");
    }

}

?>