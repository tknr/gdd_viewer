<?php

/**
 * 最小テンプレートエンジン
 */
class EZTemplate
{

    /**
     *
     * @var string
     */
    private $template_file_path;

    /**
     *
     * @var array
     */
    private $array_values;

    /**
     *
     * @var array
     */
    private $array_replaces;

    /**
     *
     * @var array
     */
    private $array_headers;

    /**
     *
     * @param string $template_file_path            
     * @param array $array_headers            
     */
    public function __construct($template_file_path, $array_headers = array('Content-type: text/html; charset=utf-8'))
    {
        $this->template_file_path = $template_file_path;
        $this->array_headers = $array_headers;
        $this->array_values = array();
        $this->array_replaces = array();
    }

    /**
     *
     * @param string $key            
     * @param unknown $value            
     */
    public function setValue($key, $value)
    {
        $this->array_values[$key] = $value;
    }

    /**
     *
     * @param string $key            
     * @param string $value            
     */
    public function setReplace($key, $value)
    {
        $this->array_replaces[$key] = $value;
    }

    /**
     *
     * @return boolean
     */
    public function render()
    {
        extract($this->array_values, EXTR_OVERWRITE);
        
        foreach ($this->array_headers as $header) {
            header($header);
        }
        ob_start('mb_output_handler');
        require ($this->template_file_path);
        $output = ob_get_contents();
        foreach ($this->array_replaces as $key => $value) {
            $output = str_replace($key, $value, $output);
        }
        ob_end_clean();
        echo $output;
        return true;
    }
}