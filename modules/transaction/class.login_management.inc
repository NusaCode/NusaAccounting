<?php

atkimport("atk.security.atksecuritylistener");

class login_management extends atkSecurityListener 
{
    // This event is thrown just before the user get's authenticated.
    function preLogin($username) 
        {
        atkdebug("$username about to login: preLogin()");
        $db = &atkGetDb();
        $user = &getUser();        
        $sqlu = "UPDATE person SET status_login='Y' WHERE id='" . $user['id'] . "'";
        $db->query($sqlu);
        $db->commit();        
    }    
    // This event is thrown just after the user is successfully authenticated.
    function postLogin($username) 
	{
	atkdebug("$username already logged in: postLogin()");	
        $db = &atkGetDb();
        $user = &getUser();
        $sqlu = "UPDATE person SET status_login='Y' WHERE id='" . $user['id'] . "'";
        $db->query($sqlu);
        $db->commit();
    }
// end function
    // This event is thrown just before the user get's logged out the system.
    function preLogout($username) 
	{
        atkdebug("$username about to logout: preLogout()");
        $db = &atkGetDb();
        $user = &atkGetUser();
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
		session_destroy();
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