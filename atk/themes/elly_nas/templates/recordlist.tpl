{if isset($formstart)}{$formstart}{/if}

{$searchstart}

<table cellspacing="0" cellpadding="0" class="recordListContainer">
  <tr>
    <td class="recordListContainerTd">
        <table id="{$listid}" class="recordList" cellpadding="0" cellspacing="0">
            <!-- header -->
            <tr class="recordListHeader">
              {section name=headerloop loop=$header}
                <th valign="{$vorientation}" {if isset($header[headerloop].htmlattributes)}{$header[headerloop].htmlattributes}{/if}
                 {if $smarty.section.headerloop.index===0}class="recordListHeaderTh recordListHeaderThFirst"
                 {elseif $smarty.section.headerloop.index==$smarty.section.headerloop.last}class="recordListHeaderTh recordListHeaderThLast"
                 {else}class="recordListHeaderTh"{/if}>
                 {if $header[headerloop].content != ""}{$header[headerloop].content}{else}&nbsp;{/if}
                </th>
              {/section}
            </tr>

			{if count($sort)}
			<!-- sort row -->
			<tr>
				{$sortstart}
				{foreach from=$sort item=col}
				<th valign="{$vorientation}" {if isset($col.htmlattributes)}{$col.htmlattributes}{/if}>
				{if $col.content != ""}{$col.content}{else}&nbsp;{/if}
				</th>
				{/foreach}
				{$sortend}
			</tr>
			{/if}
			
			{if count($search)}
			<!-- search row -->
			<tr class="recordListSearch">
				{$searchstart}
				{section name=searchloop loop=$search}
				<th valign="{$vorientation}" {if isset($search[searchloop].htmlattributes)}{$search[searchloop].htmlattributes}{/if}
				{if $smarty.section.searchloop.index===0}class="recordListSearchTh recordListSearchThFirst"
				{elseif $smarty.section.searchloop.index==$smarty.section.searchloop.last}class="recordListSearchTh recordListSearchThLast"
				{else}class="recordListSearchTh"{/if}>
				{if $search[searchloop].content != ""}{$search[searchloop].content}{else}&nbsp;{/if}
				</th>
				{/section}
				{$searchend}
			</tr>
			{/if}

            <!-- records -->
            {$liststart}
            {foreach from=$rows item=row}
              <tr id="{$row.id}" class="recordListRecord row{if $row.rownum % 2 == 0 }1{else}2{/if}" {if $row.background!=""}style="background-color:{$row.background}" {/if}
                   onmouseover="highlightrow(this, '#ECF4FC')"
                   onmouseout="resetrow(this)"
                   onclick="selectrow(this, '{$listid}', {$row.rownum}); highlightrow(this, '#ECF4EE');">
               {section name=colloop loop=$row.cols}
               <{if $row.type == "subtotal"}th{else}td{/if}
                 {if $smarty.section.colloop.index===0}class="recordListTd recordListTdFirst"
                 {elseif $smarty.section.colloop.index==$smarty.section.colloop.last}class="recordListTd recordListTdLast"
                 {else}class="recordListTd"{/if}
                 valign="{$vorientation}"  {if isset($row.cols[colloop].htmlattributes)}{$row.cols[colloop].htmlattributes}{/if}
                 {if $row.cols[colloop].type == "data"} onclick="rl_try('{$listid}', event, {$row.rownum}, ['select', 'edit', 'view'], false);"{/if}>
                 {if $row.cols[colloop].content != ""}{$row.cols[colloop].content}{else}&nbsp;{/if}
               </{if $row.type == "subtotal"}th{else}td{/if}>
             {/section}
           </tr>
           {/foreach}

            {if count($total)}
            <!-- totals row -->
            <tr class="recordListTotal">
              {foreach from=$total item=col}
                  <th valign="{$vorientation}" {if $col.content != ""}class="recordListTotalNum"{/if} {if isset($col.htmlattributes)}{$col.htmlattributes}{/if}>
                    {if $col.content != ""}{$col.content}{else}&nbsp;{/if}
                  </th>
              {/foreach}
              </tr>
            {/if}
      </table>
    </td>
  </tr>
  {if $mra!=""}
  <!-- multirecord actions -->
   <tr>
     <td>
       <table border="0" cellspacing="0" cellpadding="0">
         <tr>
           <td valign="top"><img src="{$atkroot}atk/images/arrow.gif" border="0"></td>
           <td class="multirecord-actions-links">
             {$mra} {$listend}
           </td>
         </tr>
       </table>
     </td>
   </tr>
  {/if}
</table>
{if isset($formend)}{$formend}{/if}