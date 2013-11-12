<?php
include_once (atkconfig("atkroot") . "lib/mpdf/mpdf.php");

/*
 * membuat list coa by: Muhammad Ikhsan Ramadhan
 * modul: report
 * node class: master_list_jurnal_type
 */

class balance_sheet extends atkNode {

    var $_module = "report";
    var $_node = "balance_sheet";
    var $_table = "coa_value";

    function balance_sheet() {
        $this->atkNode($this->_node, NF_READONLY | NF_NO_EXTENDED_SEARCH);

    }

    function action_balance_sheet(){
        $db = atkGetDb();
        $asset_value = "
        SELECT 
            a.coa_code,
            a.coa_name,
            a.current_balance,
            a.debit,
            a.credit,
            ((a.current_balance + a.debit) - a.credit) AS total
        FROM    
            (
             SELECT 
                c.`coa_code`,
                c.`coa_name`,
                IFNULL(ocb.`current_balance`, 0) AS current_balance,
                IFNULL((
                    SELECT SUM(t.debit)
                    FROM `transaction` t,
                        journal j
                    WHERE t.coa = c.`coa_code`
                        AND t.id_journal = j.id_journal
                        AND j.posting = 1
                    GROUP BY c.`coa_code`
                ), 0) AS debit,
                IFNULL((
                    SELECT SUM(t.credit)
                    FROM `transaction` t,
                        journal j
                    WHERE t.coa = c.`coa_code`
                        AND t.id_journal = j.id_journal
                        AND j.posting = 1
                    GROUP BY c.`coa_code`
                ), 0) AS credit
             FROM
                coa c
             LEFT JOIN
                ob_cash_bank ocb
             ON
                c.`coa_code` = ocb.`coa`
             WHERE 
                NOT EXISTS
                    (SELECT * FROM
                    (SELECT DISTINCT coa_parent FROM coa) cp WHERE c.coa_code = cp.coa_parent)
                AND c.`coa_jenis` = 'a'
            ) AS a
        ";

        $liabilities_value = "
SELECT 
    a.coa_code,
    a.coa_name,
    a.current_balance,
    a.debit,
    a.credit,
    ((a.current_balance + a.credit) - a.debit) AS total
FROM    
    (
     SELECT 
        c.`coa_code`,
        c.`coa_name`,
        IFNULL(ocb.`current_balance`, 0) AS current_balance,
        IFNULL((
            SELECT SUM(t.debit)
            FROM `transaction` t,
                journal j
            WHERE t.coa = c.`coa_code`
                AND t.id_journal = j.id_journal
                AND j.posting = 1
            GROUP BY c.`coa_code`
        ), 0) AS debit,
        IFNULL((
            SELECT SUM(t.credit)
            FROM `transaction` t,
                journal j
            WHERE t.coa = c.`coa_code`
                AND t.id_journal = j.id_journal
                AND j.posting = 1
            GROUP BY c.`coa_code`
        ), 0) AS credit
     FROM
        coa c
     LEFT JOIN
        ob_cash_bank ocb
     ON
        c.`coa_code` = ocb.`coa`
     WHERE 
        NOT EXISTS
            (SELECT * FROM
            (SELECT DISTINCT coa_parent FROM coa) cp WHERE c.coa_code = cp.coa_parent)
        AND c.`coa_jenis` = 'l'
    ) AS a
        ";

        $ownerequity_value = "
SELECT 
    a.coa_code,
    a.coa_name,
    a.current_balance,
    a.debit,
    a.credit,
    ((a.current_balance + a.credit) - a.debit) AS total
FROM    
    (
     SELECT 
        c.`coa_code`,
        c.`coa_name`,
        IFNULL(ocb.`current_balance`, 0) AS current_balance,
        IFNULL((
            SELECT SUM(t.debit)
            FROM `transaction` t,
                journal j
            WHERE t.coa = c.`coa_code`
                AND t.id_journal = j.id_journal
                AND j.posting = 1
            GROUP BY c.`coa_code`
        ), 0) AS debit,
        IFNULL((
            SELECT SUM(t.credit)
            FROM `transaction` t,
                journal j
            WHERE t.coa = c.`coa_code`
                AND t.id_journal = j.id_journal
                AND j.posting = 1
            GROUP BY c.`coa_code`
        ), 0) AS credit
     FROM
        coa c
     LEFT JOIN
        ob_cash_bank ocb
     ON
        c.`coa_code` = ocb.`coa`
     WHERE 
        NOT EXISTS
            (SELECT * FROM
            (SELECT DISTINCT coa_parent FROM coa) cp WHERE c.coa_code = cp.coa_parent)
        AND c.`coa_jenis` = 'o'
    ) AS a
        ";
        $getasset_value = $db->getrows($asset_value);
        $getliabilities_value = $db->getrows($liabilities_value);
        $getownerequity_value = $db->getrows($ownerequity_value);

        $total_asset = 0;
        $total_liabilities = 0;
        $total_ownerequity = 0;

        $table = "<table border=0 width='70%'>";
        $table .= "<caption>PT XXX <br> Balance Sheet <br> Dec 2013</caption>";
        $table .= "<tr><td><table border=0 width='100%'>";
        $table .= "<tr><td colspan=3><u>ASSETS</u></td></tr>";
        foreach ($getasset_value as $key => $value) {
            $table .= "<tr>
                        <td>".$value['coa_name']."</td>
                        <td align='right' width='40%'>".number_format($value['total'],2)."</td>
                       </tr>";
            $total_asset = $total_asset + $value['total'];
        }
        $table .= "<tr>
                    <td colspan=2>&nbsp;</td>
                   </tr>";
        $table .= "<tr>
                    <td>Total assets</td>
                    <td align='right' width='40%' style='border-bottom: 1px solid;'>".number_format($total_asset,2)."</td>
                   </tr>";
        $table .= "</table></td><td valign='top' style='padding-left:20px;'><table border=0 width='100%'>";                   
        $table .= "<tr><td colspan=3><u>LIABILITIES</u></td></tr>";
        foreach ($getliabilities_value as $key => $value) {
            $table .= "<tr>
                        <td>".$value['coa_name']."</td>
                        <td align='right'>".number_format($value['total'],2)."</td>
                       </tr>";
            $total_liabilities = $total_liabilities + $value['total'];
        }
        $table .= "<tr>
                    <td colspan=2>&nbsp;</td>
                   </tr>";
        $table .= "<tr>
                    <td>Total liabilities</td>
                    <td align='right' width='40%' style='border-bottom: 1px solid;'>".number_format($total_liabilities,2)."</td>
                   </tr>";
        $table .= "<tr>
                    <td colspan=2>&nbsp;</td>
                   </tr>";
        $table .= "<tr>
                    <td colspan=2>&nbsp;</td>
                   </tr>";
        $table .= "<tr><td colspan=3><u>STOCKHOLDERS EQUITY</u></td></tr>";
        foreach ($getownerequity_value as $key => $value) {
            $table .= "<tr>
                        <td>".$value['coa_name']."</td>
                        <td align='right'>".number_format($value['total'],2)."</td>
                       </tr>";
            $total_ownerequity = $total_ownerequity + $value['total'];
        }
        $table .= "<tr>
                    <td colspan=2>&nbsp;</td>
                   </tr>";
        $table .= "<tr>
                    <td>Total owner equity</td>
                    <td align='right' width='40%' style='border-bottom: 1px solid;'>".number_format($total_ownerequity,2)."</td>
                   </tr>";
        $table .= "</table></td></tr>";
        $table .= " <tr>
                        <td colspan=2>&nbsp;</td>
                    </tr>";
        $table .= "<tr>
                        <td><table border=0 width='100%'><tr><td align='right'>Total Assets:</td><td align='right' width='40%' style='border-bottom: 3px double;'> ".number_format($total_asset,2)."</td></tr></table></td>
                        <td><table border=0 width='100%'><tr><td align='right'>Total Liab. & Owner Equities:</td><td align='right' width='40%' style='border-bottom: 3px double;'> ".number_format(($total_liabilities+$total_ownerequity),2)."</td></tr></table></td>
                   </tr>";
        $table .= "</table>";

        $page = &atknew("atk.ui.atkpage");
        $ui = &atkinstance("atk.ui.atkui");
        $theme = &atkTheme::getInstance();
        $output = &atkOutput::getInstance();
        $page->register_style($theme->stylePath("style.css"));

        $box = $ui->renderBox(array("title"=>atktext("app_shorttitle"),"content" =>$table));

        $page->addContent($box);
        $output->output($page->render(atktext('app_shorttitle'), true));

    }
}
?>