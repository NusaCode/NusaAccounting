{atkconfig var="theme_login_logo" smartyvar="login_logo"}
{if !$login_logo}{atkconfig var="theme_logo" smartyvar="login_logo"}{/if}
{if !$login_logo}{capture assign="login_logo"}{atkthemeimg login_logo.jpg}{/capture}{/if}
{if !$login_logo}{capture assign="login_logo"}{atkthemeimg logo.jpg}{/capture}{/if}
{literal}
<style type="text/css">
/*html{background-color:#fff;}*/
*{font-size: inherit;}
/*body,div,p{margin:0;padding:0;background-color:#fff;}*/
.lofb_wrap {
    font:20px arial;
    color:#000;
    /*width:800px;*/
    /*width:550px;*/
    /*margin:130px auto 0;*/
    font-family:Gotham,verdana,sans-serif !important;
    line-height:1.5em;
}
.lofb {
    /*padding-right:280px;*/
    /*margin-left:20px;*/
    margin-right:20px;
}
.lofb h2{font-size:3.1em;font-weight:bold;color:#7B0099;margin:10px 0;line-height:1em;}
.lofb h3{margin-left:5px;font-size:1.05em;color:#000;font-weight:bold;margin:10px 5px;}
.lofb p {margin-left:5px;font-size: 20px !important; text-align: justify;}

#mainBox {
    background-color: rgba(0, 0, 0, 0);
    /*height: 960px;*/
    /*margin: 0 auto;*/
    /*margin: 130px auto;*/
    /*min-height: 680px;*/
    /*position: relative;*/
    text-align: left;
    /*top: 11px;*/
    /*top: 130px;*/
    /*bottom: 130px;*/
    /*width: 100%;*/
    margin-top: 100px;
}

#loginHolder {
    height: 100%;
    /*margin: 0 auto;*/
    /*max-width: 840px;*/
    /*min-width: 262px;*/
    min-width: 902px;
    /*position: relative;*/
    min-height: 400px;
    background: none repeat scroll 0 0 #FFFFFF;
    box-shadow: 0px 0px 10px rgba(0, 0, 0, 0.2);
    opacity: .7;
}

#loginHolder-container {
    margin: 0px auto; 
    padding: 30px 30px 30px 0px; 
    width: 830px;
}

#leftContent {
    /*left: 0;*/
    /*position: absolute;*/
    /*float: left;*/
    /*margin-left: 255px;*/
    display: inline-flex;
    width: 550px;
}

#loginBox {
    /*height: 600px;*/
    /*float: right;*/
    /*margin-right: 20px;*/
    /*margin-right: 270px;*/
    /*margin-top: 10px;*/
    /*margin-top: 60px;*/
    display: inline-flex;
    width: 262px !important;
    margin-left: 10px;
    box-shadow: 1px 1px 4px rgba(153, 153, 153, 0.75); 
    margin-top: 20px;
    position: absolute;
}

#yreglg {
    /*width: 262px !important;*/
}

#yreglg {
    /*float: right;*/
    /*margin: 0 0 20px;*/
    /*width: 240px;*/
}

.mm-lgbx {
    background-color: #FFFFFF;
    /*border: 2px solid rgba(153, 153, 153, 0.75);*/
    border-radius: 2px 2px 2px 2px;
    font-family: "Helvetica Neue",Helvetica,Arial,sans-serif;
    font-size: 13px !important;
    z-index: 3;
}

.top {
    position: relative;
    /*top: 100px;*/
    /*top: 130px;*/
}

.mm-lgbx .lgbx {
    /*padding: 20px;*/
}

.lgbx-ltr {
    direction: ltr;
}

#fsLogin {
    position: relative;
}
#fsLogin {
    padding-top: 0;
}
.clear {
    clear: both;
}
img, fieldset {
    border: 0 none;
}

#inputs {
    padding: 0;
}

#inputs input {
    border: 1px solid #BABABA;
    border-radius: 3px 3px 3px 3px;
    font-size: 107% !important;
    /*height: 23px;*/
    height: 30px;
    margin-bottom: 15px;
    padding: 5px;
    /*width: 208px;*/
    width: 95%;
}

#submit {
    padding-bottom: 5px;
}
#submit {
    font-family: arial;
    padding-bottom: 20px;
}

#submit button {
    font-size: 13px;
}
.mm-lgbx .purple-bg {
    /*background-color: #6E329D;*/
    /*background-image: -moz-linear-gradient(center center , #6E329D 0%, #6E329D 100%);*/
    border: 1px solid #522675;
    border-radius: 2px 2px 2px 2px;

    background:#6E329D;

    /* Safari 4-5, Chrome 1-9 */
    background: -webkit-gradient(linear, 0% 0%, 0% 100%, from(#6E329D), to(#6E329D));

    /* Safari 5.1, Chrome 10+ */
    background: -webkit-linear-gradient(top, #6E329D, #6E329D);

    /* Firefox 3.6+ */
    background: -moz-linear-gradient(top, #6E329D, #6E329D);

    /* IE > 8 */
    filter: progid:DXImageTransform.Microsoft.gradient(startColorstr='#6E329D', endColorstr='#6E329D');

    /* IE 10 */
    background: -ms-linear-gradient(top, #6E329D, #6E329D);

    /* Opera 11.10+ */
    background: -o-linear-gradient(top, #6E329D, #6E329D);

    opacity: 0.95;
    cursor: pointer;
}

.mm-lgbx .purple-bg:hover {
    opacity: 1;
}

.mm-lgbx .lgbx-btn {
    border: 0 none;
    color: #FFFFFF;
    cursor: pointer;
    font-weight: bold;
    height: 35px;
    text-align: center;
    width: 100%;
}

.lgbx {
    /*padding: 20px;*/
}

.lgbx-logo {
    background-position: 0 -4px;
    height: 30px;
    /*margin: 10px 10px 27px 20px;*/
    margin: 20px;
    position: relative;
    text-align: center;
    /*width: 138px;*/
}

.yregertxt {
    background-image: url("https://s.yimg.com/lq/i/reg/login/loginsprite_2_18_2010.png");
    background-position: left -197px;
    background-repeat: no-repeat;
    color: #E10707;
    margin-bottom: 10px;
    margin-top: 4px;
    padding-left: 24px;
}

#nas-img-login {
    /*border-radius: 50% 50% 50% 50%; */
    border: 3px solid #FFFFFF;
    box-shadow: 2px 4px 4px rgba(0, 0, 0, 0.2);
    margin-right: 20px;
    width: 200px;
    height: 150px;
}
</style>

{/literal}


<div id="mainBox">
      <div id="loginHolder">
        <div id="loginHolder-container">
            <div id="leftContent">
              <!-- <div id="static" style="display: block;"> -->
              <div id="static">
                <div class="lofb_wrap">
                <div class="lofb">                    
                    <h3>What is Nusa Accounting?</h3>
                    <p>
                        <img id="nas-img-login" src="./images/nas-accounting.png" width="200" height="150" align="left" hspace="0" vspace="5" />
                        NusaAccounting is a web based system of collection, storage and processing of financial and accounting data that is used by decision makers. NusaAccounting is a web based solution for tracking accounting activity in conjunction with information technology resources. The resulting statistical reports can be used internally by management or externally by other interested parties including investors, creditors and tax authorities.
                    </p>
                </div>
                </div>
              </div>
            </div>
            <div id="loginBox">
              <div id="yreglg">
                <div class="top mm-lgbx">
                  <div class="lgbx lisu">    
                    <div class="lgbx-ltr">
                      <div class="lgbx-logo ">
                        <img src="{$login_logo}" alt="Logo">
                      </div>
                    </div>
                    <fieldset class="clear" id="fsLogin">
                    {if isset($auth_max_loginattempts_exceeded)}
                      {$auth_max_loginattempts_exceeded}
                    {else}
                      {$atksessionformvars}
                      {if isset($auth_mismatch)}<div class="yregertxt">{$auth_mismatch}</div><br>{/if}
                      {if isset($auth_account_locked)}<div class="yregertxt">{$auth_account_locked}</div><br>{/if}
                      <form id="login_form" name="login_form" autocomplete="" action="{$formurl}" method="post">
                        <div id="inputs" class="yui-skin-sam">
                                <input type="text" value="" autocomplete="off" autocorrect="off" placeholder="Username" required="true" tabindex="1" maxlength="96" id="username" name="auth_user">
                                <input type="password" value="" autocomplete="off" autocorrect="off" placeholder="Password" required="true" tabindex="2" maxlength="64" id="passwd" name="auth_pw">
                        </div>
                        <div id="submit">
                          <input tabindex="4" class="lgbx-btn purple-bg" name=".save" id=".save" type="submit" value="{atktext sign_in}">
                          {if $auth_enablepasswordmailer}<input name="login" class="button" type="submit" value="{atktext password_forgotten}">{/if}
                        </div>
                      </form>
                      {/if}
                    </fieldset>
                  </div>
                </div>
              </div>
            </div>
        </div>
      </div><!-- end loginHolder -->
</div>