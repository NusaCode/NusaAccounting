<script language="JavaScript" type="text/javascript">
var tabs = new Array();
{section name=i loop=$tabs}
  tabs[tabs.length] = "{$tabs[i].tab}";
{/section}
</script>

<table width="100%" border="0" cellpadding="0" cellspacing="0" valign="top">
	<tr>
		<td width="100%" align="left">
		
			<ul class="tabsTabs" id="mainTabs">
				{section name=i loop=$tabs}
				<li id="tab_{$tabs[i].tab}" class="{if $tabs[i].selected}activetab{else}passivetab{/if}"><a href="javascript:void(0)" onclick="showTab('{$tabs[i].tab}')">{$tabs[i].title}</a></li>
				{/section}
			</ul>

			<table border="0" cellspacing="0" cellpadding="5" width="100%" class="tabsContent">
				<tr>
					<td>
					{$content}
					</td>
				</tr>
			</table>
		</td>
	</tr>
</table>