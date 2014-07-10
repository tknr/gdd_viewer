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
}