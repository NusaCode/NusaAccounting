<?php /* Smarty version 2.6.11, created on 2013-11-08 17:36:09
         compiled from ./atk/themes/elly_nas/templates/list.tpl */ ?>
<?php require_once(SMARTY_CORE_DIR . 'core.load_plugins.php');
smarty_core_load_plugins(array('plugins' => array(array('function', 'atkmessages', './atk/themes/elly_nas/templates/list.tpl', 3, false),)), $this); ?>
<?php if (isset ( $this->_tpl_vars['formstart'] )):  echo $this->_tpl_vars['formstart'];  endif; ?>
<table border="0" cellspacing="0" cellpadding="2" width="100%">
  <?php echo smarty_function_atkmessages(array(), $this);?>

  <?php if (count ( $this->_tpl_vars['atkmessages'] )): ?>
    <tr>
      <td align="center" valign="top">
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
  <?php endif; ?>  
  <?php if (( isset ( $this->_tpl_vars['header'] ) && ! empty ( $this->_tpl_vars['header'] ) )): ?>
  <tr class="list-header">
    <td valign="top" align="left"><?php echo $this->_tpl_vars['header']; ?>
</td>
  </tr>
  <?php endif; ?>
  <?php if (( isset ( $this->_tpl_vars['index'] ) && ! empty ( $this->_tpl_vars['index'] ) )): ?>
  <tr class="list-index">
    <td valign="top" align="left"><?php echo $this->_tpl_vars['index']; ?>
</td>
  </tr>
  <?php endif; ?>
  <?php if (( isset ( $this->_tpl_vars['navbar'] ) && ! empty ( $this->_tpl_vars['navbar'] ) )): ?>
  <tr class="list-navbar">
    <td valign="top" align="left"><?php echo $this->_tpl_vars['navbar']; ?>
</td>
  </tr>
  <?php endif; ?>
  <tr class="list-list">
    <td valign="top" align="left"><?php echo $this->_tpl_vars['list']; ?>
</td>
  </tr>
  <?php if (( isset ( $this->_tpl_vars['navbar'] ) && ! empty ( $this->_tpl_vars['navbar'] ) )): ?>
  <tr class="list-navbar">
    <td valign="top" align="left"><?php echo $this->_tpl_vars['navbar']; ?>
</td>
  </tr>
  <?php endif; ?>
  <?php if (( isset ( $this->_tpl_vars['footer'] ) && ! empty ( $this->_tpl_vars['footer'] ) )): ?>
  <tr class="list-footer">
    <td valign="top" align="left"><?php echo $this->_tpl_vars['footer']; ?>
</td>
  </tr>
  <?php endif; ?>
</table>
<?php if (isset ( $this->_tpl_vars['formstart'] )):  echo $this->_tpl_vars['formend'];  endif; ?>