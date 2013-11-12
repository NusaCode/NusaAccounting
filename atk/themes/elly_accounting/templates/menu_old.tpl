<ul id="nav">
{foreach from=$menuitems item=menuitem}
	{if !isset($firstmenuitem)}{assign var='firstmenuitem' value=$menuitem.name}{/if}
	{if $menuitem.name!=='-' && $menuitem.enable}
		<li id="mi_{$menuitem.name}">
			<a href="{$menuitem.url}">{$menuitem.name}</a>
			{if (array_key_exists('submenu',$menuitem) && count($menuitem.submenu)>0)}
				<ul id="smi_{$menuitem.name}" class="child">
					{$menuitem.header}
					{foreach from=$menuitem.submenu item=submenuitem}
						{if $submenuitem.enable && $submenuitem.name!=='-'}
							<li>
								<a href="{$submenuitem.url}">{$submenuitem.name}</a>
							</li>
						{/if}
					{/foreach}
				</ul>
			{/if}
		</li>
	{/if}
{/foreach}
</ul>
