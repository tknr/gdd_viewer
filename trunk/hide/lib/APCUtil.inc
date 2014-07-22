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

    /**
     *
     * @param string $key            
     * @param array $arr            
     * @param boolean $case_sensitive            
     * @return boolean
     */
    public static function define_array($key, $arr, $case_sensitive = true)
    {
        if (function_exists('apc_load_constants')) {
            
            if (! apc_load_constants($key, $case_sensitive)) {
                return apc_define_constants($key, $arr, $case_sensitive);
            }
        } else {
            
            foreach ($arr as $name => $value) {
                define($name, $value, $case_sensitive);
            }
            return true;
        }
    }
}