{if isset($helplink)}<div class="helplink">{$helplink}</div>{/if}

{$formstart}
  {atkmessages}
  {if count($atkmessages)}
  <table border="0" cellspacing="0" cellpadding="0" width="100%">  
    <tr>
      <td valign="top">
        <br>  
        <div class="atkmessages">
          {foreach from=$atkmessages item=message}
            <div class="atkmessages_{$message.type}">{$message.message}</div>
          {/foreach}
        </div>
      </td>
    </tr>        
  </table>
  {/if}  
  
  <table border="0" cellspacing="0" cellpadding="0" width="100%">  
  {if (isset($header) && !empty($header))}
  <tr>
    <td valign="top">{$header}</td>
  </tr>
  {/if}
  <tr>
    <td valign="top">{$content}</td>
  </tr>
  <tr>
    <td valign="top" class="buttons">
      {foreach from=$buttons item=button}
        &nbsp;{$button}&nbsp;
      {/foreach}
	</td>
  </tr>
  </table>
{$formend}
