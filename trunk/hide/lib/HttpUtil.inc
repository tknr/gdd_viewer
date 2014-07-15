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
     * @param string $key
     * @param number $default
     * @return number
     */
    public static function getInt($key, $default = 0)
    {
        return intval(self::get($key, $default));
    }
}