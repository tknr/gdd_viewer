<?php

class HttpUtil
{

    /**
     *
     * @param string $key            
     * @param string $default            
     * @return unknown
     */
    public static function get($key, $default = '')
    {
        if (! array_key_exists($key, $_GET)) {
            return $default;
        }
        return $_GET[$key];
    }

    /**
     *
     * @param string $key            
     * @param number $default            
     * @return number
     */
    public static function getInt($key, $default = 0)
    {
        return intval(self::get($key, $default));
    }
    
    /**
     *
     * @param string $key            
     * @param string $default            
     * @return unknown
     */
    public static function post($key, $default = '')
    {
        if (! array_key_exists($key, $_POST)) {
            return $default;
        }
        return $_POST[$key];
    }

    /**
     *
     * @param string $key            
     * @param number $default            
     * @return number
     */
    public static function postInt($key, $default = 0)
    {
        return intval(self::post($key, $default));
    }
        
    /**
     *
     * @param string $key            
     * @param string $default            
     * @return unknown
     */
    public static function request($key, $default = '')
    {
        if (! array_key_exists($key, $_REQUEST)) {
            return $default;
        }
        return $_REQUEST[$key];
    }

    /**
     *
     * @param string $key            
     * @param number $default            
     * @return number
     */
    public static function requestInt($key, $default = 0)
    {
        return intval(self::request($key, $default));
    }
}