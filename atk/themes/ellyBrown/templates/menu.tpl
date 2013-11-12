<body class="easyui-layout">
    <div border="0" id="north" region="north" scrolling="no"  split="true" style="border:0px;overflow: hidden;height:70px;">
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
    </div>

    <div id="menu" region="west" border="false"  split="false" title="<i>Menu Category</i>" style="width:250px;padding:0px;">
        <!--        <div class="easyui-accordion" fit="true" border="false">
                    <div title="Menu Utama" style="overflow:auto;width:250px;padding:5px;" selected="true"> -->
        {$menu}
        <!--            </div>
                    <div title="User Info"  >
                        <iframe name="main" scrolling="no" frameborder="0"  src="userInfo.php" style="width:100%;height:100%;" ></iframe>
                    </div>
                </div>-->
    </div>

    <div region="south" split="false" style="height:30px;">
        <div id="bottom-layout">Nusa Code &copy; 2012</div>
    </div>

    <div region="center" style="overflow:hidden;border-left: 4px solid #8A622A;">
        <div id="tt" class="easyui-tabs" fit="true" border="false">
            <div title="Welcome" icon="icon-reload" closable="true" >
                <iframe name="main" scrolling="auto" frameborder="0" src="welcome.php" style="width:100%;height:99.6%;" ></iframe>
            </div>
        </div>
    </div>


    {literal}
        <script type="text/javascript">
            $jq(function(){
            //        $jq('body').layout('collapse','east');

                    $jq('#tt').tabs({
                            fit: true
                    });

                    $jq('#tt1').tree('collapseAll');

            });

            var index = 0;
            function addTab(title, url){
                if ($jq('#tt').tabs('exists', title)){
                    $jq('#tt').tabs('select', title);
                } else {
                    var content = '<iframe scrolling="auto" frameborder="0"  src="'+url+'" style="width:100%;height:99.6%;"></iframe>';
                    $jq('#tt').tabs('add',{
                        title:title,
                        content:content,
                        closable:true
                    });
                }
            }
        </script>
    {/literal}