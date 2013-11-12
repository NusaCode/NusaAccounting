<?php

atkimport("atk.security.atksecuritylistener");

class login_management extends atkSecurityListener 
{
    // This event is thrown just before the user get's authenticated.
    function preLogin($username) 
        {
        atkdebug("$username about to login: preLogin()");
        /*
        * Added by Leontine de fretes
        * 09 Oct 2013
        * Check active time user login, if expired and status_login still 'Y', then update to 'N'
        */

            $inactive = atkconfig("authentication_cookie_expire") * 60;
            $userid = atkconfig("auth_userfield");
            $usertable = atkconfig("auth_usertable");
            $useractivetime = atkconfig("auth_useractivetime");
            $g_db = &atkGetDb();
            $qCheckActiveTime = "select * from $usertable where ".$userid."='".$username."' and status_login='Y'";
            $getCheckActiveTime = $g_db->getrows($qCheckActiveTime);
            $checkActiveTime = $getCheckActiveTime[0][$useractivetime];
            $session_life = time() - $checkActiveTime;
            // var_dump("session_life = ".$session_life." inactive = ".$inactive);exit();
            if($session_life > $inactive)
            {
                $q = "update $usertable set status_login='N' where ".$userid."='".$username."'";
                $g_db->query($q);
                $g_db->commit();
            }else{
                return false;
            }

    }    
    // This event is thrown just after the user is successfully authenticated.
    function postLogin($username) 
    {
    atkdebug("$username already logged in: postLogin()");   
        $db = &atkGetDb();
        $user = &getUser();
        $sqlu = "UPDATE person SET status_login='Y', active_time='".time()."' WHERE id='" . $user['id'] . "'";
        $db->query($sqlu);
        $db->commit();
    }
// end function
    // This event is thrown just before the user get's logged out the system.
    function preLogout($username) 
    {
        $db = &atkGetDb();
        $user = &atkGetUser();
        atkdebug("$username about to logout: preLogout()");
        $sqlu = "UPDATE person SET status_login='N' WHERE id='" . $user['id'] . "'";
        $db->query($sqlu);
        $db->commit();
        // place your custom code below
    }
// end function
    // This event is thrown just after the user is logged out the system.
    function postLogout($username) 
	{
        atkdebug("$username already logged out: postLogout()");
        $db = &atkGetDb();
        $user = &getUser();
        $sqlu = "UPDATE person SET status_login='N' WHERE id='" . $user['id'] . "'";
        $db->query($sqlu);
        $db->commit();
        // place your custom code below
    }
	
	/*function get_ip_address() 
	{
		foreach (array('HTTP_CLIENT_IP', 'HTTP_X_FORWARDED_FOR', 'HTTP_X_FORWARDED', 'HTTP_X_CLUSTER_CLIENT_IP', 'HTTP_FORWARDED_FOR', 'HTTP_FORWARDED', 'REMOTE_ADDR') as $key) 
		{
			if (array_key_exists($key, $_SERVER) === true) 
			{
				foreach (explode(',', $_SERVER[$key]) as $ip) 
				{
					if (filter_var($ip, FILTER_VALIDATE_IP) !== false) 
					{
						return $ip;
					}
				}
			}
		}
	}*/
// end function
}
// end class
?>