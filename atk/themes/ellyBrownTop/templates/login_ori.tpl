{literal}
<style type="text/css">
body {
    {/literal}
    background: url({$themedir}images/bg-login.png) top repeat;
    {literal}
}
</style>
{/literal}
<div class="box" style="background-color:#d0e4fe; border-style:solid; margin:100px auto;height:350px; width:400px;-moz-border-radius: 40px;-webkit-border-radius: 40px;">

	<div class="box-title">
	<img src="{if empty($theme_logo)}{atkthemeimg logo.gif}{else}{$theme_logo}{/if}" alt="Logo" />
	</div>
		
	<div class="box-content" style="height:170px;">
		<form action="{$formurl}" method="post">
		{if isset($auth_max_loginattempts_exceeded)}
		{$auth_max_loginattempts_exceeded}
		{else}
		{$atksessionformvars}
		{if isset($auth_mismatch)}<span class="error">{$auth_mismatch}</span><br>{/if}
		{if isset($auth_account_locked)}<span class="error">{$auth_account_locked}</span><br>{/if}
		
		<table cellpadding="10" cellspacing="0" border="0" style="margin:30px auto;">
			<tr>
				<td>{atktext username}:</td>
				<td>{$userfield}</td>
			</tr>
			<tr>
				<td>{atktext password}:</td>
				<td><input class="loginform" type="password" size="15" name="auth_pw" value=""></td>
			</tr>
			<tr>
				<td colspan="2" align="center">
					<input name="login" class="button atkdefaultbutton" type="submit" value="{atktext login}">
					{if $auth_enablepasswordmailer}<input name="login" class="button" type="submit" value="{atktext password_forgotten}">{/if}
				</td>
			</tr>
		</table>
		{/if}
		</form>
	</div>
	
</div>
