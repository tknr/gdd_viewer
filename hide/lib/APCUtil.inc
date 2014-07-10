<?php

class APCUtil
{

    /**
     *
     * @param string $key            
     * @return mixed|boolean
     */
    public static function get($key)
    {
        if (function_exists('apc_fetch')) {
            return apc_fetch($key);
        }
        return false;
    }

    /**
     *
     * @param string $key            
     * @param mixed $value            
     * @return boolean
     */
    public static function put($key, $value)
    {
        if (function_exists('apc_store')) {
            return apc_store($key, $value);
        }
        return false;
    }
}