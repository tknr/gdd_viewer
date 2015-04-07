<?php

class ReflexiveLoader
{

    /**
     *
     * ディレクトリ格納
     *
     * @var array
     */
    private $dirs = array();

    /**
     * コンストラクタ
     */
    public function __construct()
    {
        spl_autoload_register(array(
            $this,
            'loader'
        ));
    }

    /**
     *
     * ディレクトリを登録
     *
     * @param string $dir            
     */
    public function registerDir($dir)
    {
        $this->dirs[] = $dir;
    }

    /**
     *
     * コールバック
     *
     * @param string $classname            
     */
    public function loader($classname)
    {
        foreach ($this->dirs as $dir) {
            $list = $this->require_list($dir);
            foreach ($list as $path) {
                if (is_readable($path)) {
                    require $path;
                }
            }
        }
    }

    /**
     *
     * @param string $dir            
     * @return multitype:
     */
    private function search($dir)
    {
        $list = glob($dir . '/*');
        foreach ($list as $path) {
            if (is_dir($path)) {
                $list = array_merge($list, $this->search($path));
            }
        }
        return $list;
    }

    /**
     *
     * @param string $dir            
     * @return multitype:
     */
    private function require_list($dir)
    {
        $list = $this->search($dir);
        foreach ($list as $index => $path) {
            $is_match = preg_match("/\.(php|inc)$/", $path);
            if ($is_match === false || $is_match === 0) {
                unset($list[$index]);
            }
        }
        return $list;
    }
}