

{atkconfig var="theme_logo" smartyvar="theme_logo"}

<div id="banner">

  <div id="bannerLogo"><a href="index.php"><img src="{if empty($theme_logo)}{atkthemeimg logo.gif}{else}{$theme_logo}{/if}" alt="Logo" /></a></div>
  <div id="bannerCustomImage"></div>
  
  <div id="topLinks">
  
    <table id="topLinkTable" cellpadding="0" cellspacing="0">
      <tr valign="top">
        <td><span id="top-center">{foreach  from=$centerpiece_links item=link}{$link}&nbsp;&nbsp;|&nbsp;&nbsp;{/foreach}</span></td>
      </tr> 
    </table>

  </div>

</div>




<div id="box-menu"> 
 
	<ul id="mainMenu"> 
        <li class="menuItemLevel1">{$title}</li>   
	</ul>
	
</div>




<div class="box">

	<div class="box-title">
	{atktext login_form}
	</div>
		
	<div class="box-content">
		<form action="{$formurl}" method="post">
		{if isset($auth_max_loginattempts_exceeded)}
		{$auth_max_loginattempts_exceeded}
		{else}
		{$atksessionformvars}
		{if isset($auth_mismatch)}<span class="error">{$auth_mismatch}</span><br>{/if}
		{if isset($auth_account_locked)}<span class="error">{$auth_account_locked}</span><br>{/if}
		
		<table cellpadding="0" cellspacing="0" border="0">
			<tr>
				<td class="fieldlabel">{atktext username}:</td>
				<td class="field">{$userfield}</td>
			</tr>
			<tr>
				<td class="fieldlabel">{atktext password}:</td>
				<td class="field"><input class="loginform" type="password" size="15" name="auth_pw" value=""></td>
			</tr>
			<tr>
				<td class="buttons" colspan="2">
					<input name="login" class="button atkdefaultbutton" type="submit" value="{atktext login}">
					{if $auth_enablepasswordmailer}<input name="login" class="button" type="submit" value="{atktext password_forgotten}">{/if}
				</td>
			</tr>
		</table>
		{/if}
		</form>
	</div>
	
</div>
