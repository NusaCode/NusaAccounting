<?php /* Smarty version 2.6.11, created on 2013-11-08 17:36:09
         compiled from ./atk/themes/elly_nas/templates/recordlist.tpl */ ?>
<?php if (isset ( $this->_tpl_vars['formstart'] )):  echo $this->_tpl_vars['formstart'];  endif; ?>

<?php echo $this->_tpl_vars['searchstart']; ?>


<table cellspacing="0" cellpadding="0" class="recordListContainer">
  <tr>
    <td class="recordListContainerTd">
        <table id="<?php echo $this->_tpl_vars['listid']; ?>
" class="recordList" cellpadding="0" cellspacing="0">
            <!-- header -->
            <tr class="recordListHeader">
              <?php unset($this->_sections['headerloop']);
$this->_sections['headerloop']['name'] = 'headerloop';
$this->_sections['headerloop']['loop'] = is_array($_loop=$this->_tpl_vars['header']) ? count($_loop) : max(0, (int)$_loop); unset($_loop);
$this->_sections['headerloop']['show'] = true;
$this->_sections['headerloop']['max'] = $this->_sections['headerloop']['loop'];
$this->_sections['headerloop']['step'] = 1;
$this->_sections['headerloop']['start'] = $this->_sections['headerloop']['step'] > 0 ? 0 : $this->_sections['headerloop']['loop']-1;
if ($this->_sections['headerloop']['show']) {
    $this->_sections['headerloop']['total'] = $this->_sections['headerloop']['loop'];
    if ($this->_sections['headerloop']['total'] == 0)
        $this->_sections['headerloop']['show'] = false;
} else
    $this->_sections['headerloop']['total'] = 0;
if ($this->_sections['headerloop']['show']):

            for ($this->_sections['headerloop']['index'] = $this->_sections['headerloop']['start'], $this->_sections['headerloop']['iteration'] = 1;
                 $this->_sections['headerloop']['iteration'] <= $this->_sections['headerloop']['total'];
                 $this->_sections['headerloop']['index'] += $this->_sections['headerloop']['step'], $this->_sections['headerloop']['iteration']++):
$this->_sections['headerloop']['rownum'] = $this->_sections['headerloop']['iteration'];
$this->_sections['headerloop']['index_prev'] = $this->_sections['headerloop']['index'] - $this->_sections['headerloop']['step'];
$this->_sections['headerloop']['index_next'] = $this->_sections['headerloop']['index'] + $this->_sections['headerloop']['step'];
$this->_sections['headerloop']['first']      = ($this->_sections['headerloop']['iteration'] == 1);
$this->_sections['headerloop']['last']       = ($this->_sections['headerloop']['iteration'] == $this->_sections['headerloop']['total']);
?>
                <th valign="<?php echo $this->_tpl_vars['vorientation']; ?>
" <?php if (isset ( $this->_tpl_vars['header'][$this->_sections['headerloop']['index']]['htmlattributes'] )):  echo $this->_tpl_vars['header'][$this->_sections['headerloop']['index']]['htmlattributes'];  endif; ?>
                 <?php if ($this->_sections['headerloop']['index'] === 0): ?>class="recordListHeaderTh recordListHeaderThFirst"
                 <?php elseif ($this->_sections['headerloop']['index'] == $this->_sections['headerloop']['last']): ?>class="recordListHeaderTh recordListHeaderThLast"
                 <?php else: ?>class="recordListHeaderTh"<?php endif; ?>>
                 <?php if ($this->_tpl_vars['header'][$this->_sections['headerloop']['index']]['content'] != ""):  echo $this->_tpl_vars['header'][$this->_sections['headerloop']['index']]['content'];  else: ?>&nbsp;<?php endif; ?>
                </th>
              <?php endfor; endif; ?>
            </tr>

			<?php if (count ( $this->_tpl_vars['sort'] )): ?>
			<!-- sort row -->
			<tr>
				<?php echo $this->_tpl_vars['sortstart']; ?>

				<?php $_from = $this->_tpl_vars['sort']; if (!is_array($_from) && !is_object($_from)) { settype($_from, 'array'); }if (count($_from)):
    foreach ($_from as $this->_tpl_vars['col']):
?>
				<th valign="<?php echo $this->_tpl_vars['vorientation']; ?>
" <?php if (isset ( $this->_tpl_vars['col']['htmlattributes'] )):  echo $this->_tpl_vars['col']['htmlattributes'];  endif; ?>>
				<?php if ($this->_tpl_vars['col']['content'] != ""):  echo $this->_tpl_vars['col']['content'];  else: ?>&nbsp;<?php endif; ?>
				</th>
				<?php endforeach; endif; unset($_from); ?>
				<?php echo $this->_tpl_vars['sortend']; ?>

			</tr>
			<?php endif; ?>
			
			<?php if (count ( $this->_tpl_vars['search'] )): ?>
			<!-- search row -->
			<tr class="recordListSearch">
				<?php echo $this->_tpl_vars['searchstart']; ?>

				<?php unset($this->_sections['searchloop']);
$this->_sections['searchloop']['name'] = 'searchloop';
$this->_sections['searchloop']['loop'] = is_array($_loop=$this->_tpl_vars['search']) ? count($_loop) : max(0, (int)$_loop); unset($_loop);
$this->_sections['searchloop']['show'] = true;
$this->_sections['searchloop']['max'] = $this->_sections['searchloop']['loop'];
$this->_sections['searchloop']['step'] = 1;
$this->_sections['searchloop']['start'] = $this->_sections['searchloop']['step'] > 0 ? 0 : $this->_sections['searchloop']['loop']-1;
if ($this->_sections['searchloop']['show']) {
    $this->_sections['searchloop']['total'] = $this->_sections['searchloop']['loop'];
    if ($this->_sections['searchloop']['total'] == 0)
        $this->_sections['searchloop']['show'] = false;
} else
    $this->_sections['searchloop']['total'] = 0;
if ($this->_sections['searchloop']['show']):

            for ($this->_sections['searchloop']['index'] = $this->_sections['searchloop']['start'], $this->_sections['searchloop']['iteration'] = 1;
                 $this->_sections['searchloop']['iteration'] <= $this->_sections['searchloop']['total'];
                 $this->_sections['searchloop']['index'] += $this->_sections['searchloop']['step'], $this->_sections['searchloop']['iteration']++):
$this->_sections['searchloop']['rownum'] = $this->_sections['searchloop']['iteration'];
$this->_sections['searchloop']['index_prev'] = $this->_sections['searchloop']['index'] - $this->_sections['searchloop']['step'];
$this->_sections['searchloop']['index_next'] = $this->_sections['searchloop']['index'] + $this->_sections['searchloop']['step'];
$this->_sections['searchloop']['first']      = ($this->_sections['searchloop']['iteration'] == 1);
$this->_sections['searchloop']['last']       = ($this->_sections['searchloop']['iteration'] == $this->_sections['searchloop']['total']);
?>
				<th valign="<?php echo $this->_tpl_vars['vorientation']; ?>
" <?php if (isset ( $this->_tpl_vars['search'][$this->_sections['searchloop']['index']]['htmlattributes'] )):  echo $this->_tpl_vars['search'][$this->_sections['searchloop']['index']]['htmlattributes'];  endif; ?>
				<?php if ($this->_sections['searchloop']['index'] === 0): ?>class="recordListSearchTh recordListSearchThFirst"
				<?php elseif ($this->_sections['searchloop']['index'] == $this->_sections['searchloop']['last']): ?>class="recordListSearchTh recordListSearchThLast"
				<?php else: ?>class="recordListSearchTh"<?php endif; ?>>
				<?php if ($this->_tpl_vars['search'][$this->_sections['searchloop']['index']]['content'] != ""):  echo $this->_tpl_vars['search'][$this->_sections['searchloop']['index']]['content'];  else: ?>&nbsp;<?php endif; ?>
				</th>
				<?php endfor; endif; ?>
				<?php echo $this->_tpl_vars['searchend']; ?>

			</tr>
			<?php endif; ?>

            <!-- records -->
            <?php echo $this->_tpl_vars['liststart']; ?>

            <?php $_from = $this->_tpl_vars['rows']; if (!is_array($_from) && !is_object($_from)) { settype($_from, 'array'); }if (count($_from)):
    foreach ($_from as $this->_tpl_vars['row']):
?>
              <tr id="<?php echo $this->_tpl_vars['row']['id']; ?>
" class="recordListRecord row<?php if ($this->_tpl_vars['row']['rownum'] % 2 == 0): ?>1<?php else: ?>2<?php endif; ?>" <?php if ($this->_tpl_vars['row']['background'] != ""): ?>style="background-color:<?php echo $this->_tpl_vars['row']['background']; ?>
" <?php endif; ?>
                   onmouseover="highlightrow(this, '#ECF4FC')"
                   onmouseout="resetrow(this)"
                   onclick="selectrow(this, '<?php echo $this->_tpl_vars['listid']; ?>
', <?php echo $this->_tpl_vars['row']['rownum']; ?>
); highlightrow(this, '#ECF4EE');">
               <?php unset($this->_sections['colloop']);
$this->_sections['colloop']['name'] = 'colloop';
$this->_sections['colloop']['loop'] = is_array($_loop=$this->_tpl_vars['row']['cols']) ? count($_loop) : max(0, (int)$_loop); unset($_loop);
$this->_sections['colloop']['show'] = true;
$this->_sections['colloop']['max'] = $this->_sections['colloop']['loop'];
$this->_sections['colloop']['step'] = 1;
$this->_sections['colloop']['start'] = $this->_sections['colloop']['step'] > 0 ? 0 : $this->_sections['colloop']['loop']-1;
if ($this->_sections['colloop']['show']) {
    $this->_sections['colloop']['total'] = $this->_sections['colloop']['loop'];
    if ($this->_sections['colloop']['total'] == 0)
        $this->_sections['colloop']['show'] = false;
} else
    $this->_sections['colloop']['total'] = 0;
if ($this->_sections['colloop']['show']):

            for ($this->_sections['colloop']['index'] = $this->_sections['colloop']['start'], $this->_sections['colloop']['iteration'] = 1;
                 $this->_sections['colloop']['iteration'] <= $this->_sections['colloop']['total'];
                 $this->_sections['colloop']['index'] += $this->_sections['colloop']['step'], $this->_sections['colloop']['iteration']++):
$this->_sections['colloop']['rownum'] = $this->_sections['colloop']['iteration'];
$this->_sections['colloop']['index_prev'] = $this->_sections['colloop']['index'] - $this->_sections['colloop']['step'];
$this->_sections['colloop']['index_next'] = $this->_sections['colloop']['index'] + $this->_sections['colloop']['step'];
$this->_sections['colloop']['first']      = ($this->_sections['colloop']['iteration'] == 1);
$this->_sections['colloop']['last']       = ($this->_sections['colloop']['iteration'] == $this->_sections['colloop']['total']);
?>
               <<?php if ($this->_tpl_vars['row']['type'] == 'subtotal'): ?>th<?php else: ?>td<?php endif; ?>
                 <?php if ($this->_sections['colloop']['index'] === 0): ?>class="recordListTd recordListTdFirst"
                 <?php elseif ($this->_sections['colloop']['index'] == $this->_sections['colloop']['last']): ?>class="recordListTd recordListTdLast"
                 <?php else: ?>class="recordListTd"<?php endif; ?>
                 valign="<?php echo $this->_tpl_vars['vorientation']; ?>
"  <?php if (isset ( $this->_tpl_vars['row']['cols'][$this->_sections['colloop']['index']]['htmlattributes'] )):  echo $this->_tpl_vars['row']['cols'][$this->_sections['colloop']['index']]['htmlattributes'];  endif; ?>
                 <?php if ($this->_tpl_vars['row']['cols'][$this->_sections['colloop']['index']]['type'] == 'data'): ?> onclick="rl_try('<?php echo $this->_tpl_vars['listid']; ?>
', event, <?php echo $this->_tpl_vars['row']['rownum']; ?>
, ['select', 'edit', 'view'], false);"<?php endif; ?>>
                 <?php if ($this->_tpl_vars['row']['cols'][$this->_sections['colloop']['index']]['content'] != ""):  echo $this->_tpl_vars['row']['cols'][$this->_sections['colloop']['index']]['content'];  else: ?>&nbsp;<?php endif; ?>
               </<?php if ($this->_tpl_vars['row']['type'] == 'subtotal'): ?>th<?php else: ?>td<?php endif; ?>>
             <?php endfor; endif; ?>
           </tr>
           <?php endforeach; endif; unset($_from); ?>

            <?php if (count ( $this->_tpl_vars['total'] )): ?>
            <!-- totals row -->
            <tr class="recordListTotal">
              <?php $_from = $this->_tpl_vars['total']; if (!is_array($_from) && !is_object($_from)) { settype($_from, 'array'); }if (count($_from)):
    foreach ($_from as $this->_tpl_vars['col']):
?>
                  <th valign="<?php echo $this->_tpl_vars['vorientation']; ?>
" <?php if ($this->_tpl_vars['col']['content'] != ""): ?>class="recordListTotalNum"<?php endif; ?> <?php if (isset ( $this->_tpl_vars['col']['htmlattributes'] )):  echo $this->_tpl_vars['col']['htmlattributes'];  endif; ?>>
                    <?php if ($this->_tpl_vars['col']['content'] != ""):  echo $this->_tpl_vars['col']['content'];  else: ?>&nbsp;<?php endif; ?>
                  </th>
              <?php endforeach; endif; unset($_from); ?>
              </tr>
            <?php endif; ?>
      </table>
    </td>
  </tr>
  <?php if ($this->_tpl_vars['mra'] != ""): ?>
  <!-- multirecord actions -->
   <tr>
     <td>
       <table border="0" cellspacing="0" cellpadding="0">
         <tr>
           <td valign="top"><img src="<?php echo $this->_tpl_vars['atkroot']; ?>
atk/images/arrow.gif" border="0"></td>
           <td class="multirecord-actions-links">
             <?php echo $this->_tpl_vars['mra']; ?>
 <?php echo $this->_tpl_vars['listend']; ?>

           </td>
         </tr>
       </table>
     </td>
   </tr>
  <?php endif; ?>
</table>
<?php if (isset ( $this->_tpl_vars['formend'] )):  echo $this->_tpl_vars['formend'];  endif; ?>