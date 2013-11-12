<?php /* Smarty version 2.6.11, created on 2013-11-08 17:14:12
         compiled from ./atk/themes/elly_nas/templates/menu.tpl */ ?>
	<div id="nav-container" class="nas-grid-box">
		<div id="nav">

			<!-- User login Section -->
			<div id="user-section-container">
				<div id="user-container">
					<span class="nas-valign-container" dir="ltr" id="user-displayname">
						<?php echo $this->_tpl_vars['u_name']; ?>

					</span>

					<button role="button" data-orientation="vertical" type="button" class="nas-user-icon nas-uix-button">
					    <img width="27" height="27" alt="Thumbnail" src="<?php echo $this->_tpl_vars['u_img_27']; ?>
">
					</button>
				</div>


				<div class="nas_container">
					<div class="nas_o">
						<!-- <div align="right" id="cl_gbc">X</div> -->
						<!-- User with DEFAULT role -->
						<div class="nas_K">
							<a href="javascript:void(0);" class="nas_L nas_gb">
								<img alt="<?php echo $this->_tpl_vars['u_name']; ?>
" src="<?php echo $this->_tpl_vars['u_img_96']; ?>
" width="96" height="96" class="nas_N">
							</a>
							<div class="nas_M">
								<div class="nas_P"><?php echo $this->_tpl_vars['u_name']; ?>
</div>
								<?php if (( count ( $this->_tpl_vars['u_org'] ) > 0 )): ?>
								<div class="nas_Q"><?php echo $this->_tpl_vars['u_org']['organizationcode']; ?>
</div>
								<!-- <div class="nas_J">
									<a href="https://www.google.com/settings?ref=home&amp;authuser=0">Account</a>&ndash;<a href="http://www.google.com/intl/en/policies/">Privacy</a>
								</div> -->
								<a href="javascript:void(0);" class="nas_ab gbp1 nas_x">View profile</a>
								<?php endif; ?>
							</div>
						</div>

						<!-- Same user with another roles -->
						<?php if (( count ( $this->_tpl_vars['u_role'] ) > 0 )): ?>
						<div class="nas_U">
							<!-- <a class="nas_V" href="javascript:void(0);"> -->
							<div class="nas_V">
								<!-- <img class="nas_Z" src="<?php echo $this->_tpl_vars['u_img_48']; ?>
" width="48" height="48" alt="<?php echo $this->_tpl_vars['u_name']; ?>
"> -->
								<div class="nas_0">
									<!-- <div class="nas_1"><?php echo $this->_tpl_vars['u_name']; ?>
</div> -->
									<!-- <div class="nas_2"><?php echo $this->_tpl_vars['roles']['name']; ?>
 - <span class="nas_3"><?php echo $this->_tpl_vars['roles']['organizationcode']; ?>
</span></div>		 -->
									<!-- <div> -->
										Switch Role:
										<select id="switch_role">
											<?php $_from = $this->_tpl_vars['u_role']; if (!is_array($_from) && !is_object($_from)) { settype($_from, 'array'); }if (count($_from)):
    foreach ($_from as $this->_tpl_vars['roles']):
?>
											<option value="<?php echo $this->_tpl_vars['roles']['id']; ?>
">
												<span class="nas_2"><?php echo $this->_tpl_vars['roles']['name']; ?>
 - <span class="nas_3"><?php echo $this->_tpl_vars['roles']['organizationcode']; ?>
</span></span>
											</option>					
											<?php endforeach; endif; unset($_from); ?>
										</select>
									<!-- </div> -->
								</div>
							</div>
							<!-- </a> -->
						</div>
						<?php endif; ?>

						<!-- Log out section -->
						<div class="nas_R">
							<div>
								<a target="_top" id="nas_71" class="nas_bb nas_jb nas_x">Sign out</a>
							</div>
						</div>
					</div>
				</div>
			</div>

			<!-- Navigation Section -->
			<div id="menu">
				<ul class="sf-menu" id="nas_menu">
				<?php $_from = $this->_tpl_vars['menuitems']; if (!is_array($_from) && !is_object($_from)) { settype($_from, 'array'); }if (count($_from)):
    foreach ($_from as $this->_tpl_vars['menuitem']):
?>
				<?php if ($this->_tpl_vars['menuitem']['name'] !== '-' && $this->_tpl_vars['menuitem']['enable']): ?>
					<li>
						<a href="<?php if ($this->_tpl_vars['menuitem']['url'] != ''):  echo $this->_tpl_vars['menuitem']['url'];  else:  echo $this->_tpl_vars['menuitem']['submenu'][0]['url'];  endif; ?>">
							<img src="<?php echo $this->_tpl_vars['menuitem']['icons']; ?>
" title="<?php echo $this->_tpl_vars['menuitem']['name']; ?>
"><?php echo $this->_tpl_vars['menuitem']['name']; ?>

						</a>
						<?php if (( count ( $this->_tpl_vars['menuitem']['submenu'] ) > 0 )): ?>
							<ul>
								<?php echo $this->_tpl_vars['menuitem']['header']; ?>

						<?php $_from = $this->_tpl_vars['menuitem']['submenu']; if (!is_array($_from) && !is_object($_from)) { settype($_from, 'array'); }if (count($_from)):
    foreach ($_from as $this->_tpl_vars['submenuitem']):
?>
						<?php if ($this->_tpl_vars['submenuitem']['enable'] && $this->_tpl_vars['submenuitem']['name'] !== '-'): ?>
								<li>
									<a href="<?php echo $this->_tpl_vars['submenuitem']['url']; ?>
"><img src="<?php echo $this->_tpl_vars['submenuitem']['icons_sub']; ?>
" title="<?php echo $this->_tpl_vars['submenuitem']['name']; ?>
"><?php echo $this->_tpl_vars['submenuitem']['name']; ?>
</a>
								</li>
						<?php endif; ?>
						<?php endforeach; endif; unset($_from); ?>
							</ul>
						<?php endif; ?>
					</li>
				<?php endif; ?>
				<?php endforeach; endif; unset($_from); ?>
				</ul>
			</div>

			<a id="logo-container" href="./" title="Nusa Accounting System Home">
				<img alt="Nusa Accounting System" src="<?php echo $this->_tpl_vars['logo']; ?>
" id="logo">
			</a>

		</div>
	</div>
