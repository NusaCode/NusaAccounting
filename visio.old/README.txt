Author: Bahtiar
Date: 21 Feb 2013


Since atk650 not supported anymore by Ibuildings
In order To enhance the faetures in this Framework, we maintain our own enhanchement and changes ini this way:

Create New folder in the following structure:

visio - images
      - js
	  - css
	  - patch
	  
All New Addition Javascript file will be put in js folder
All New Addition Stylesheet file will be put in css folder
All New Addition Images file will be put in images folder
All New Classes/Files Patch since atk650 will be put in patch folder

New Features 21/2/2013
FloatingMenu
Desc: Floating Menu In Record Actions
Config in config.inc.php : $config_recordlist_menu="true";

 - Modified Class:
		-atk\ui\class.atkpage.inc
		-atk\datagrid\class.atkdglist.inc