
<div id="box-menu">

	<ul id="mainMenu">
{foreach from=$menuitems item=menuitem}{if !isset($firstmenuitem)}{assign var='firstmenuitem' value=$menuitem.name}{/if}
{if $menuitem.name!=='-' && $menuitem.enable}
		<li class="menuItemLevel1{if $atkmenutopname==$menuitem.name} menuItemLevel1-active{/if}" id="mi_{$menuitem.name|replace:' ':'_'}">
			<a href="{if $menuitem.url!=''}{$menuitem.url}{else}{$menuitem.submenu[0].url}{/if}"><span class="menu-menuitem">{$menuitem.name}</span></a></li>
{/if}
{/foreach}
	</ul>
	
{foreach from=$menuitems item=menuitem}
{if $atkmenutop!=="main"}{assign var='selectedSubMenu' value=$atkmenutopname}{else}{assign var='selectedSubMenu' value=$firstmenuitem}{/if}
{if (count($menuitem.submenu)>0) && $menuitem.name == $selectedSubMenu}
	<ul id="smi_{$menuitem.name|replace:' ':'_'}" class="submenuHover">
		{$menuitem.header}
{foreach from=$menuitem.submenu item=submenuitem}
{if $submenuitem.enable && $submenuitem.name!=='-'}
		<li class="menuItemLevel2"><a href="{$submenuitem.url}">{$submenuitem.name}</a></li>
{/if}
{/foreach}
		<li class="menuItemLevel2"><a>&nbsp</a></li>
	</ul>
{/if}
{/foreach}

</div>
