<body class="easyui-layout">
    <div border="0" id="north" region="north" scrolling="no" split="false" style="overflow:hidden; height:110px;border-bottom: 5px solid #8A622A;">
        <div id="top-layout">
            <div id="top-layout-left">
                <img src="{$themedir}/images/login-logo.png" height="56" width="130" alt="{atktext app_title}" title="{atktext app_title}" />{atktext app_shorttitle}
            </div>
            <div id="top-layout-right">
                Welcome, <span id="user-info">{$user}</span>
                <img id="user" src="{$themedir}/images/icon-user.png" height="32" width="32" alt="{$user}" title="{$user}" /> 
                <a href="index.php?atklogout=1" target="{$logouttarget}">
                    <img id="logout" src="{$themedir}/images/icon-logout.png" height="32" width="32" alt="{atktext logout}" title="{atktext logout}" /> 
                </a>
            </div>
        </div>
        {$menu}
    </div>

    <div region="south" split="false" style="height:30px;">
        <div id="bottom-layout">Nusa Code &copy; 2013</div>
    </div>

    <div region="center" style="overflow:hidden;">
        <div id="tt" class="easyui-tabs" fit="true" border="false" style="overflow:hidden;">
            <div title="Welcome" icon="icon-reload" closable="true" >
                <iframe name="main" scrolling="auto" frameborder="0" src="welcome.php" style="width:100%;height:99.6%;overflow:hidden;"></iframe>
            </div>
        </div>
    </div>


    {literal}
        <script type="text/javascript">
            $jq(function(){
        //            $jq('body').layout('collapse','east');
        //            $jq('body').layout('collapse','west');

                    $jq('#tt').tabs({
                       fit: true
                    });

                    $jq('#tt1').tree('collapseAll');
            });

            function addTab(title, url){
                if ($jq('#tt').tabs('exists', title)){
                    $jq('#tt').tabs('select', title);
                } else {
                    var content = '<iframe scrolling="auto" frameborder="0"  src="'+url+'" style="width:100%;height:100%;"></iframe>';
                    $jq('#tt').tabs('add',{
                        title:title,
                        content:content,
                        closable:true
                    });
                }
            }
        </script>
    {/literal}


