<script type="text/javascript" src="{$themedir}js/jquery.js"></script>
<script type="text/javascript" src="{$themedir}js/navigation.js"></script>
<script type="text/javascript" src="{$themedir}js/navigationT.js"></script>

<link rel="stylesheet" type="text/css" href="{$themedir}styles/navigation.css">
<link rel="stylesheet" type="text/css" href="{$themedir}styles/navigationT.css">
<link rel="stylesheet" type="text/css" href="{$themedir}styles/style.css">
	
<script type="text/javascript">
{literal}
	var col
	function ChangeCol() {
		colors = new Array('#4D3D98', '#0C8B44', '#88288F', '#D24827', '#00A0B1'); /* Colors of the Menu Items */
		body_color = "#1C1651"; /* Background Color of the whole Navigation */
		hover_color = "#352869"; /* Color of the border of the menu items for HOVER*/
		scroll_color = "#5A4B80"; /* Default background color for the scroll arrow */
		scroll_hover = "#FFFFFF"; /* Hover background color for the scroll arrow */
		scroll_click = "#282828"; /* background color for the scroll arrow when clicked */
		$("div.metro_nav").show();
		$("div.metro_na").hide();

		setColors();
	}
{/literal}
</script>

<script type="text/javascript">
{literal}
	$jq(document).ready(function(){
		$jq(".hideMenu").click(function(){
			$jq(".metro_nav").slideUp();
			$jq(".hideMenu").css("display", "none");
			$jq(".showMenu").css("display", "block");
		});

		$jq(".showMenu").click(function(){
			$jq(".metro_nav").slideDown();
			$jq(".hideMenu").css("display", "block");
			$jq(".showMenu").css("display", "none");
		});
	});
{/literal}
</script>

<style>
{literal}
	div.metro_na {display : none;}
	body {margin : 0;}
	img {border : none;}
{/literal}
</style>

<link href="{$themedir}styles/light.css" type="text/css" rel="stylesheet"></head>

<div class="showMenu"></div>
<div class="hideMenu"></div>

<div style="background-color: rgb(28, 22, 81);" class="metro_nav">
	<div class="nav_title">Navigation</div>
	<ul>
	{foreach from=$menuitems item=menuitem}
		{if !isset($firstmenuitem)}{assign var='firstmenuitem' value=$menuitem.name}{/if}
		{if $menuitem.name!=='-' && $menuitem.enable}
			<li id="mi_{$menuitem.name}">
				<a href="{$menuitem.url}"><img src="{$menuitem.icons}" title="{$menuitem.name}"><span>{$menuitem.name}</span></a>
				{if (array_key_exists('submenu',$menuitem) && count($menuitem.submenu)>0)}
					<ul id="smi_{$menuitem.name}">
						{$menuitem.header}
						{foreach from=$menuitem.submenu item=submenuitem}
							{if $submenuitem.enable && $submenuitem.name!=='-'}
								<li>
									<a href="{$submenuitem.url}"><img src="{$submenuitem.icons_sub}" title="{$submenuitem.name}"><span>{$submenuitem.name}</span></a>
								</li>
							{/if}
						{/foreach}
					</ul>
				{/if}
			</li>
		{/if}
	{/foreach}
	</ul>
</div>

