	<div id="nav-container" class="nas-grid-box">
		<div id="nav">

			<!-- User login Section -->
			<div id="user-section-container">
				<div id="user-container">
					<span class="nas-valign-container" dir="ltr" id="user-displayname">
						{$u_name}
					</span>

					<button role="button" data-orientation="vertical" type="button" class="nas-user-icon nas-uix-button">
					    <img width="27" height="27" alt="Thumbnail" src="{$u_img_27}">
					</button>
				</div>


				<div class="nas_container">
					<div class="nas_o">
						<!-- <div align="right" id="cl_gbc">X</div> -->
						<!-- User with DEFAULT role -->
						<div class="nas_K">
							<a href="javascript:void(0);" class="nas_L nas_gb">
								<img alt="{$u_name}" src="{$u_img_96}" width="96" height="96" class="nas_N">
							</a>
							<div class="nas_M">
								<div class="nas_P">{$u_name}</div>
								{if (count($u_org)>0)}
								<div class="nas_Q">{$u_org.organizationcode}</div>
								<!-- <div class="nas_J">
									<a href="https://www.google.com/settings?ref=home&amp;authuser=0">Account</a>&ndash;<a href="http://www.google.com/intl/en/policies/">Privacy</a>
								</div> -->
								<a href="javascript:void(0);" class="nas_ab gbp1 nas_x">View profile</a>
								{/if}
							</div>
						</div>

						<!-- Same user with another roles -->
						{if (count($u_role)>0)}
						<div class="nas_U">
							<!-- <a class="nas_V" href="javascript:void(0);"> -->
							<div class="nas_V">
								<!-- <img class="nas_Z" src="{$u_img_48}" width="48" height="48" alt="{$u_name}"> -->
								<div class="nas_0">
									<!-- <div class="nas_1">{$u_name}</div> -->
									<!-- <div class="nas_2">{$roles.name} - <span class="nas_3">{$roles.organizationcode}</span></div>		 -->
									<!-- <div> -->
										Switch Role:
										<select id="switch_role">
											{foreach from=$u_role item=roles}
											<option value="{$roles.id}">
												<span class="nas_2">{$roles.name} - <span class="nas_3">{$roles.organizationcode}</span></span>
											</option>					
											{/foreach}
										</select>
									<!-- </div> -->
								</div>
							</div>
							<!-- </a> -->
						</div>
						{/if}

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
				{foreach from=$menuitems item=menuitem}
				{if $menuitem.name!=='-' && $menuitem.enable}
					<li>
						<a href="{if $menuitem.url!=''}{$menuitem.url}{else}{$menuitem.submenu[0].url}{/if}">
							<img src="{$menuitem.icons}" title="{$menuitem.name}">{$menuitem.name}
						</a>
						{if (count($menuitem.submenu)>0)}
							<ul>
								{$menuitem.header}
						{foreach from=$menuitem.submenu item=submenuitem}
						{if $submenuitem.enable && $submenuitem.name!=='-'}
								<li>
									<a href="{$submenuitem.url}"><img src="{$submenuitem.icons_sub}" title="{$submenuitem.name}">{$submenuitem.name}</a>
								</li>
						{/if}
						{/foreach}
							</ul>
						{/if}
					</li>
				{/if}
				{/foreach}
				</ul>
			</div>

			<a id="logo-container" href="./" title="Nusa Accounting System Home">
				<img alt="Nusa Accounting System" src="{$logo}" id="logo">
			</a>

		</div>
	</div>

