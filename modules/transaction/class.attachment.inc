<?php
userelation("atkonetomanyrelation");
userelation("atkmanytoonerelation");

class attachment extends atkNode {
        
	var $namaModul = 'transaction';
	var $namaNode  = 'attachment';
	var $namaTabel = 'attachment';


    function attachment() {
	
	$this->log = atknew("atk.utils.atkeventlog");  // log object for atkeventlog listener. Leontine 01 Aug 2012
        $this->addListener($this->log);
	
	
        $this->atkNode($this->namaNode, NF_EXPORT | NF_ADD_LINK | NF_NO_SEARCH);
        
        $this->add(new atkAttribute("idAttachment",AF_AUTOKEY | AF_HIDE_LIST));       
        
	$this->add(new atkmanytoonerelation("idJournal","transaction.journal", AF_OBLIGATORY | AF_SEARCHABLE | AF_HIDE));
	
	$this->add(new atkFileAttribute("filename", moduleDir("transaction")."attachment",  AF_OBLIGATORY|AF_FILE_NO_SELECT | AF_FILE_PHYSICAL_DELETE | AF_FILE_POPUP));
        
	$this->add(new atkAttribute("module_node",AF_HIDE));
	
        $this->add(new atkAttribute("id_org",AF_HIDE));
        
        $this->add(new atkdummyattribute("jarak_atas","<br>", AF_HIDE_LIST));

        $this->add(new atkdummyattribute("garis","<hr>", AF_HIDE_LIST));

        $this->add(new atkCreatedByAttribute("created_by", AF_HIDE_LIST));

        $this->add(new atkCreateStampAttribute("created_on", AF_HIDE_LIST)); 

        $this->add(new AtkUpdatedByAttribute("last_modified_by", AF_HIDE_LIST));

        $this->add(new atkUpdateStampAttribute("last_modified_on", AF_HIDE_LIST));        
        
        $this->setOrder("idAttachment");
        $this->setTable($this->namaTabel);
    }

    function descriptor_def() {
        return "[file_name]";
    }

    function postAdd(&$record) {

        $data = "id = \'" . $record['idAttachment'] . "\', Nama File = \'" . $record['filename'] . "\'";
        $this->log->actionPerformed('Add', $data);
        return true;
    }

    function postUpdate(&$record) {

        $data = "id = \'" . $record['idAttachment'] . "\', Nama File = \'" . $record['filename'] . "\'";
        $this->log->actionPerformed('Edit', $data);

        return true;
    }

    function postDelete($record) {

        $data = "id = \'" . $record['idAttachment'] . "\', Nama File = \'" . $record['filename'] . "\'";
        $this->log->actionPerformed('Delete', $data);

        return true;
    }	

    function initial_values() {
        parent::initial_values();
        $user = atkgetUser();
        $id_org = $user['employer_id'];        

        
        return array("module_node" =>  $_GET['atknodetype'],
                     "id_org" => $id_org
                    );
    }    
}

?>