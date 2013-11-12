<?php

/**
 * This file is part of the Achievo ATK distribution.
 * Detailed copyright and licensing information can be found
 * in the doc/COPYRIGHT and doc/LICENSE files which should be
 * included in the distribution.
 *
 * @package atk
 * @subpackage menu
 *
 * @copyright (c)2007 Ibuildings.nl BV
 * @license http://www.achievo.org/atk/licensing ATK Open Source License
 *
 * @version $Revision: 6320 $
 * $Id: class.atkcookmenu.inc 6354 2009-04-15 02:41:21Z mvdam $
 */
/**
 * Imports
 * @access private
 */
atkimport("atk.menu.atkmodernmenu");

/**
 * The atkBoolAttribute class represents an attribute of a node
 * that can either be true or false.
 *
 * @author Ellyas Jeffry N Sitorus <ellyas@visioinformatika.com>
 * @package atk
 * @subpackage menu
 *
 */
class atkEllyMenu extends atkModernMenu {

    /**
     * Constructor
     *
     * @return atkcookmenu
     */
    function atkEllyMenu() {
        $this->m_height = "22";
    }

    /**
     * Get the menu
     *
     * @return string The menu
     */
    function getMenu() {
        global $g_menu;
        $atkmenutop = "main";

        $menuitems = $this->getMenuItems($g_menu, $atkmenutop);
        $theme = &atkinstance("atk.ui.atktheme");
        $page = $theme->getAttribute('_page', 'atk.ui.atkipage');
        $page = &atkinstance('atk.ui.atkpage');
        $getUser = &atkGetUser();
        $defaultCSS = atkconfig("defaultthemecss");

        if (!file_exists(atkconfig("atkroot") . "atk/javascript/easy-ui/themes/default/" . $defaultCSS)) {
            $defaultCSS = "easyui.css";
        }

        if ($getUser["name"] == "administrator" && $getUser["access_level"] == 9999999) {
            $user = "administrator";
            $uid = "#";
            $linkuid = $uid;
        } else {
            $user = $getUser["userid"];
            $uid = $getUser["id"];
            $linkuid = "dispatch.php?atknodetype=users.editProfile&atkselector=person.id%3D%27" . $uid . "%27&atkaction=edit&atklevel=1&atkprevlevel=0&atkstackid=50767fe1e9061&";
        }

        $page->register_style(atkconfig("atkroot") . "atk/javascript/easy-ui/themes/default/".$defaultCSS);
        $page->register_scriptcode("
            \$jq(function(){
                \$jq('#tt1').tree({
                    onClick:function(node){
                        \$jq(this).tree('toggle', node.target);
                    },
                    onContextMenu: function(e, node){
                        e.preventDefault();
                        \$jq('#tt1').tree('select', node.target);
                        \$jq('#mm').menu('show', {
                            left: e.pageX,
                            top: e.pageY
                        });
                    }
                });
            });
        ");

//        $page->register_scriptcode("
//            var _Hasync= _Hasync|| [];
//            _Hasync.push(['Histats.start', '1,2088699,4,0,0,0,00010000']);
//            _Hasync.push(['Histats.fasi', '1']);
//            _Hasync.push(['Histats.track_hits', '']);
//            (function() {
//            var hs = document.createElement('script'); hs.type = 'text/javascript'; hs.async = true;
//            hs.src = ('http://s10.histats.com/js15_as.js');
//            (document.getElementsByTagName('head')[0] || document.getElementsByTagName('body')[0]).appendChild(hs);
//            })();
//        ");

        $ui = &atkinstance("atk.ui.atkui");
        if (!is_array($g_menu[$atkmenutop]))
            $g_menu[$atkmenutop] = array();
        usort($g_menu[$atkmenutop], array("atkplainmenu", "menu_cmp"));

        $menu_javascript = "";
        $menu = "<ul id=\"tt1\" class=\"easyui-tree\" animate=\"false\" dnd=\"false\">";
        foreach ($g_menu[$atkmenutop] as $menuitem) {
            $menu .= $this->getMenuItem($menuitem, "    ");
        }
//        $menu.="    <li><a href=\"index.php?atklogout=1\">" . atktext('logout') . "</a></li>\n";
        $menu.="</ul>";
        $box = $ui->renderBox(array("menu_javascript" => $menu_javascript, "menu" => $menu, "user" => $user, "linkuid" => $linkuid), "menu");
        return $box;
    }

    function getMenuItem($menuitem, $indentation = "") {
        global $g_menu;
        $enable = $this->isEnabled($menuitem);
        $menu = '';
        if ($enable) {
            if (array_key_exists($menuitem['name'], $g_menu) && $g_menu[$menuitem['name']]) {
                $submenu = $indentation . "<ul>\n";
                foreach ($g_menu[$menuitem['name']] as $submenuitem) {
                    $submenu.=$this->getMenuItem($submenuitem, $indentation . "  ", $submenuname = '', $menuitem['name']);
                }
                $submenu.=$indentation . "</ul>\n";
                $menu.=$indentation . $this->getItemHtml($menuitem, "\n" . $submenu . $indentation);
            } else {
                $menu.=$indentation . $this->getItemHtml($menuitem);
            }
        }
        return $menu;
    }

    /**
     * Get the HTML for a menu item
     *
     * @param string $menuitem
     * @param string $submenu
     * @param string $submenuname
     * @return string The HTML for a menu item
     */
    function getItemHtml($menuitem, $submenu = "", $submenuname = '') {
        $delimiter = atkconfig("menu_delimiter");
        $name = $this->getMenuTranslation($menuitem['name'], $menuitem['module']);

        if ($menuitem['name'] == '-')
//            return "<li class=\"separator\"><div></div></li>\n";
            return "";
        if ($menuitem['url']) {
            $url = str_replace('index', 'dispatch', $menuitem['url']);
            $href = '<a onclick="addTab(\'' . $name . '\',\'' . session_url($url, SESSION_NEW) . '\'); ">' . $name . "</a>";
//            $href = '<a onclick="addTab(\'' . $menuitem['module'] . ' &raquo; ' . $name . '\',\'' . session_url($url, SESSION_NEW) . '\'); ">' . $name . "</a>";
//          href($menuitem['url'],$this->getMenuTranslation($menuitem['name'],$menuitem['module']), SESSION_NEW);
        }
        else
            $href = '<a href="#">' . $name . '</a>';
        return "<li id='{$menuitem['module']}.{$menuitem['name']}' class='$submenuname'><span>" . $href . $delimiter . "</span>" . $submenu . "</li>\n";
    }

}