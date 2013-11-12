<?php /* Smarty version 2.6.11, created on 2013-11-08 17:14:12
         compiled from ./atk/themes/elly_nas/templates/top.tpl */ ?>
<?php require_once(SMARTY_CORE_DIR . 'core.load_plugins.php');
smarty_core_load_plugins(array('plugins' => array(array('function', 'atkconfig', './atk/themes/elly_nas/templates/top.tpl', 2, false),array('function', 'atkthemeimg', './atk/themes/elly_nas/templates/top.tpl', 6, false),array('function', 'atktext', './atk/themes/elly_nas/templates/top.tpl', 14, false),)), $this); ?>

<?php echo smarty_function_atkconfig(array('var' => 'theme_logo','smartyvar' => 'theme_logo'), $this);?>


<!-- <div id="banner">

	<div id="bannerLogo"><a href="index.php"><img src="<?php if (empty ( $this->_tpl_vars['theme_logo'] )):  echo smarty_function_atkthemeimg(array('0' => "logo.png"), $this); else:  echo $this->_tpl_vars['theme_logo'];  endif; ?>" alt="Logo" /></a></div>
	<div id="bannerCustomImage"></div>

	<div id="topLinks">

		<table id="topLinkTable" cellpadding="0" cellspacing="0">
			<tr valign="top">
				<td><span id="top-center"><?php $_from = $this->_tpl_vars['centerpiece_links']; if (!is_array($_from) && !is_object($_from)) { settype($_from, 'array'); }if (count($_from)):
    foreach ($_from as $this->_tpl_vars['link']):
 echo $this->_tpl_vars['link']; ?>
&nbsp;&nbsp;|&nbsp;&nbsp;<?php endforeach; endif; unset($_from); ?></span></td>
				<td><span id="top-logout"><a href="index.php?atklogout=1" target="<?php echo $this->_tpl_vars['logouttarget']; ?>
"><?php echo smarty_function_atktext(array('0' => 'logout'), $this);?>
 <?php echo $this->_tpl_vars['user']; ?>
</a></span>&nbsp;&nbsp;</td>
				<?php if ($this->_tpl_vars['searchpiece']): ?><td id="topLinkSearch"><span id="top-search"><?php echo $this->_tpl_vars['searchpiece']; ?>
</span></td><?php endif; ?>
			</tr> 
		</table>

	</div>

</div> -->

