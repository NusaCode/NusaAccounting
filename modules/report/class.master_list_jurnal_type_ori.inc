<?php
include_once (atkconfig("atkroot") . "lib/mpdf/mpdf.php");

/*
 * membuat list coa by: Muhammad Ikhsan Ramadhan
 * modul: report
 * node class: master_list_jurnal_type
 */

class master_list_jurnal_type extends atkNode {

    var $_module = "report";
    var $_node = "master_list_jurnal_type";
    var $_table = "master_list_journal_type";
    var $_order = "code";

    function master_list_jurnal_type() {

        $this->atkNode($this->_node, NF_READONLY | NF_NO_EXTENDED_SEARCH);

        $this->add(new atkAttribute("code", AF_SEARCHABLE));

        $this->add(new atkAttribute("name", AF_SEARCHABLE));

        $this->add(new atkListAttribute("type", array("Transaction", "Adjustment"), array(0, 1)));

        $this->add(new atkListAttribute("cash", array("Cash Flow", "Non Cash"), array(0, 1)));

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
        return "[code]";
    }
    
    public function openWindow() {
        return 'function openWindow(url) { window.open(url);  }';
    }

    function adminheader() {

        $url = session_url(dispatch_url('report.master_list_jurnal_type', 'cetak_jurnal_type'), SESSION_NESTED);
        $document = '<input type="button" name="button" value="Download Pdf" onclick="javascript:openWindow(\'' . $url . '\')">';

        $content .= "<div id='filter'><h4>+ <a style='text-decoration:underline;cursor:pointer;' id='filtertitle'>Action</a></h4>";
        $content .= "<form method='POST' id='filterform' name='filterform' style='display:none; action=\"$PHP_SELF\">
                        <input type='hidden' name=atknodetype value=report.master_list_jurnal_type />
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
    
    function action_cetak_jurnal_type(){
        
        $db = atkGetDb();
        $this->addStyle("style.css");
        $mpdf = new mPDF('','A4'); 
             
        $ambil_user = $db->getrows("SELECT * FROM organization WHERE `type` = '2'");        
        $ambil_jurnal_type = $db->getrows("SELECT `code`, `name`, `type`, `cash` FROM journal_type");
                       
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
                                <a><strong>Journal Check List</strong></a>
                            </div>
                            
                                                        
                            <table border="1" width="100%">
                                    <tr>
                                        <td width="10px" align="center" id="tebalul">No</td>
                                        <td width="10px" align="center" id="tebalul">Code</td>
                                        <td width="10px" align="center" id="tebalul">Name</td>
                                        <td width="10px" align="center" id="tebalul">Type</td>
                                        <td width="10px" align="center" id="tebalul">Cash</td>
                                    </tr> ';
        
        $no = 1;
		
        foreach($ambil_jurnal_type as $dataRow)
		{
            if($dataRow['type']== '0')
			{      
                $data_type = "Transaction";
            }
			else
			{
                $data_type = "Adjustment";
            }
            if($dataRow['cash'] == '0')
			{      
                $data_cash = "Cash Flow";
            }
			else
			{
                $data_cash = "Non Cash";
            }
                     
            $isi .='<tr>
                        <td align="center" id="tebalul">'.$no++.'<td/>
                        <td align="center">'.$dataRow['code'].'<td/>
                        <td align="center">'.$dataRow['name'].'<td/>      
                        <td align="center">'.$data_type.'<td/>  
                        <td align="center">'.$data_cash.'<td/> 
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
        $namepdf = "Jurnal Type List".".pdf";
        $mpdf->Output($namepdf,"I");
    }

}

?>