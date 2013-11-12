{if isset($formstart)}{$formstart}{/if}
<table border="0" cellspacing="0" cellpadding="2" width="100%">
  {atkmessages}
  {if count($atkmessages)}
    <tr>
      <td align="center" valign="top">
        <div class="atkmessages">
          {foreach from=$atkmessages item=message}
            <div class="atkmessages_{$message.type}">{$message.message}</div>
          {/foreach}
        </div>
      </td>
    </tr>        
  {/if}  
  {if (isset($header) && !empty($header))}
  <tr class="list-header">
    <td valign="top" align="left">{$header}</td>
  </tr>
  {/if}
  {if (isset($index) && !empty($index))}
  <tr class="list-index">
    <td valign="top" align="left">{$index}</td>
  </tr>
  {/if}
  {if (isset($navbar) && !empty($navbar))}
  <tr class="list-navbar">
    <td valign="top" align="left">{$navbar}</td>
  </tr>
  {/if}
  <tr class="list-list">
    <td valign="top" align="left">{$list}</td>
  </tr>
  {if (isset($navbar) && !empty($navbar))}
  <tr class="list-navbar">
    <td valign="top" align="left">{$navbar}</td>
  </tr>
  {/if}
  {if (isset($footer) && !empty($footer))}
  <tr class="list-footer">
    <td valign="top" align="left">{$footer}</td>
  </tr>
  {/if}
</table>
{if isset($formstart)}{$formend}{/if}