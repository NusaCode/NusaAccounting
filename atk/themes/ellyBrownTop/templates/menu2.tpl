<body class="easyui-layout">
    <div region="north" border="true">

        <ul id="mainMenu">
            {foreach from=$menuitems item=menuitem}{if !isset($firstmenuitem)}{assign var='firstmenuitem' value=$menuitem.name}{/if}
                {if $menuitem.name!=='-' && $menuitem.enable}
                    <li class="menuItemLevel1{if $atkmenutopname==$menuitem.name} menuItemLevel1-active{/if}" id="mi_{$menuitem.name|replace:' ':'_'}">
                        <a href="{if $menuitem.url!=''}{$menuitem.url}{else}{$menuitem.submenu[0].url}{/if}">
                            <span class="menu-menuitem">{$menuitem.name}</span>
                        </a>
                    </li>
                {/if}
            {/foreach}
        </ul>

        {foreach from=$menuitems item=menuitem}
            {if $atkmenutop!=="main"}{assign var='selectedSubMenu' value=$atkmenutopname}{else}{assign var='selectedSubMenu' value=$firstmenuitem}{/if}
            {if (count($menuitem.submenu)>0) && $menuitem.name == $selectedSubMenu}
                <ul id="smi_{$menuitem.name|replace:' ':'_'}" class="submenuHover">
                    {$menuitem.header}
                    {foreach from=$menuitem.submenu item=submenuitem}
                        {if $submenuitem.enable && $submenuitem.name!=='-'}
                            <li class="menuItemLevel2">
                                <a onclick="addTab('{$submenuitem.name}', '{$submenuitem.url}');">{$submenuitem.name}</a>
                            </li>
                        {/if}
                    {/foreach}
                    <!--<li class="menuItemLevel2"><a>&nbsp</a></li>-->
                </ul>
            {/if}
        {/foreach}

    </div>
    <div region="west" split="true" title="Menu" style="width:220px;padding:10px;overflow:auto;">
        West
    </div>
    <div region="east" split="true" title="News" style="width:200px;padding:10px;">east region</div>
    <div region="south" border="false" style="height:50px;background:#99CBFD;padding:10px;">south region</div>
    <div region="center">
        <div id="tt" class="easyui-tabs" fit="true" border="false"></div>
    </div>
                

{literal}
<script type="text/javascript">
    $(function(){
    //        $('body').layout('collapse','east');

            $('#tt').tabs({
                    fit: true
            });

            $('#tt1').tree('collapseAll');

    });

    function addTab(title, url){
        if ($('#tt').tabs('exists', title)){
            $('#tt').tabs('select', title);
        } else {
            var content = '<iframe scrolling="auto" frameborder="0"  src="'+url+'" style="width:100%;height:100%;"></iframe>';
            $('#tt').tabs('add',{
                title:title,
                content:content,
                closable:true
            });
        }
    }
</script>
{/literal}


