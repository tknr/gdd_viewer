<?php

/**
 */
class UserAgent
{

    /**
     *
     * @var string
     */
    private $user_agent;

    /**
     *
     * @param string $user_agent            
     */
    function __construct($user_agent)
    {
        $this->user_agent = $user_agent;
    }

    /**
     * get if smart phone or not
     * 
     * @return boolean
     */
    function is_smart_phone()
    {
        return ((strpos($this->user_agent, 'iPhone') !== false) || (strpos($this->user_agent, 'iPod') !== false) || (strpos($this->user_agent, 'Android') !== false));
    }

    /**
     * get if feature phone or not
     * 
     * @return boolean
     */
    function is_feature_phone()
    {
        return ((strpos($this->user_agent, 'DoCoMo') !== false) || (strpos($this->user_agent, 'UP.Browser') !== false) || (strpos($this->user_agent, 'J-PHONE') !== false) || (strpos($this->user_agent, 'J-Vodafone') !== false) || (strpos($this->user_agent, 'SoftBank') !== false) || (strpos($this->user_agent, 'WILLCOM') !== false));
    }

    /**
     *
     * @return string
     */
    public function getUserAgent()
    {
        return $this->user_agent;
    }
}