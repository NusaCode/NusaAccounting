<?php /* Smarty version 2.6.11, created on 2013-11-08 17:36:18
         compiled from ./atk/themes/elly_nas/templates/action.tpl */ ?>
<?php require_once(SMARTY_CORE_DIR . 'core.load_plugins.php');
smarty_core_load_plugins(array('plugins' => array(array('function', 'atkmessages', './atk/themes/elly_nas/templates/action.tpl', 4, false),)), $this); ?>
<?php if (isset ( $this->_tpl_vars['helplink'] )): ?><div class="helplink"><?php echo $this->_tpl_vars['helplink']; ?>
</div><?php endif; ?>

<?php echo $this->_tpl_vars['formstart']; ?>

  <?php echo smarty_function_atkmessages(array(), $this);?>

  <?php if (count ( $this->_tpl_vars['atkmessages'] )): ?>
  <table border="0" cellspacing="0" cellpadding="0" width="100%">  
    <tr>
      <td valign="top">
        <br>  
        <div class="atkmessages">
          <?php $_from = $this->_tpl_vars['atkmessages']; if (!is_array($_from) && !is_object($_from)) { settype($_from, 'array'); }if (count($_from)):
    foreach ($_from as $this->_tpl_vars['message']):
?>
            <div class="atkmessages_<?php echo $this->_tpl_vars['message']['type']; ?>
"><?php echo $this->_tpl_vars['message']['message']; ?>
</div>
          <?php endforeach; endif; unset($_from); ?>
        </div>
      </td>
    </tr>        
  </table>
  <?php endif; ?>  
  
  <table border="0" cellspacing="0" cellpadding="0" width="100%">  
  <?php if (( isset ( $this->_tpl_vars['header'] ) && ! empty ( $this->_tpl_vars['header'] ) )): ?>
  <tr>
    <td valign="top"><?php echo $this->_tpl_vars['header']; ?>
</td>
  </tr>
  <?php endif; ?>
  <tr>
    <td valign="top"><?php echo $this->_tpl_vars['content']; ?>
</td>
  </tr>
  <tr>
    <td valign="top" class="buttons">
      <?php $_from = $this->_tpl_vars['buttons']; if (!is_array($_from) && !is_object($_from)) { settype($_from, 'array'); }if (count($_from)):
    foreach ($_from as $this->_tpl_vars['button']):
?>
        &nbsp;<?php echo $this->_tpl_vars['button']; ?>
&nbsp;
      <?php endforeach; endif; unset($_from); ?>
	</td>
  </tr>
  </table>
<?php echo $this->_tpl_vars['formend']; ?>
