<?php
class baru extends atkNode {

    var $_module = "report";
    var $_node   = "baru";
    var $_table  = "report_journal";


    function baru() {
        
        $this->atkNode($this->_node, NF_READONLY | NF_NO_EXTENDED_SEARCH);
        $action = array("baru2");
        $this->addAllowedAction($action);
        $this->add(new atkDateAttribute("trans_date"))->setLabel("Date");

        $this->add(new atkTextAttribute("desc"))->setLabel("Description");


        $this->setTable($this->_table);    
    }

    function action_baru2()
    {
        $content = '<h2>Constrain Draggable</h2>
<div class="demo-info">
<div class="demo-tip icon-tip"></div>
<div>The draggable object can only be moved within its parent container.</div>
</div>
<div style="margin:10px 0;"></div>
<div style="position:relative;overflow:hidden;border:1px solid #ccc;width:500px;height:300px">
<div class="easyui-draggable" data-options="handle:\'#title\',onDrag:onDrag" style="width:200px;height:150px;background:#fafafa;border:1px solid #ccc;margin-top:10px">
<div id="title" style="padding:5px;background:#ccc;color:#fff">Title</div>
<table border=1 width=100%>
<tr>
    <td>test</td>
    <td>test</td>
    <td>test</td>
</tr>
<tr>
    <td>test</td>
    <td>test</td>
    <td>test</td>
</tr>
<tr>
    <td>test</td>
    <td>test</td>
    <td>test</td>
</tr>
</table>
</div>
</div>';
        $page = &atknew("atk.ui.atkpage");
        $page->register_scriptcode("
 function onDrag(e){
var d = e.data;
if (d.left < 0){d.left = 0}
if (d.top < 0){d.top = 0}
if (d.left + \$jq(d.target).outerWidth() > \$jq(d.parent).width()){
d.left = \$jq(d.parent).width() - \$jq(d.target).outerWidth();
}
if (d.top + \$jq(d.target).outerHeight() > \$jq(d.parent).height()){
d.top = \$jq(d.parent).height() - \$jq(d.target).outerHeight();
}
}       ");

        /*
        * OUTPUT
        */

        $ui = &atkinstance("atk.ui.atkui");
        $theme = &atkTheme::getInstance();
        $output = &atkOutput::getInstance();
        $page->register_style($theme->stylePath("style.css"));

        $box = $ui->renderBox(array("title"=>atktext("test"),"content" =>$content));

        $page->addContent($box);
        $output->output($page->render(atktext('test'), true));
    
    }

}
?>