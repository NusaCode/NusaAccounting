<!--
{atkconfig var="theme_logo" smartyvar="theme_logo"}

<div id="banner">

	<div id="bannerLogo"><a href="index.php"><img src="{if empty($theme_logo)}{atkthemeimg logo.png}{else}{$theme_logo}{/if}" alt="Logo" /></a></div>
	<div id="bannerCustomImage"></div>

	<div id="topLinks">

		<table id="topLinkTable" cellpadding="0" cellspacing="0">
			<tr valign="top">
				<td><span id="top-center">{foreach  from=$centerpiece_links item=link}{$link}&nbsp;&nbsp;|&nbsp;&nbsp;{/foreach}</span></td>
				<td><span id="top-logout"><a href="index.php?atklogout=1" target="{$logouttarget}">{atktext logout} {$user}</a></span>&nbsp;&nbsp;</td>
				{if $searchpiece}<td id="topLinkSearch"><span id="top-search">{$searchpiece}</span></td>{/if}
			</tr> 
		</table>

	</div>

</div>
-->
