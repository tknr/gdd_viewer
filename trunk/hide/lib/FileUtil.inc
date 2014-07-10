<?php

class FileUtil
{

    /**
     * get file size
     *
     * @param number $filesize            
     * @return string
     */
    public static function getFileSizeString($filesize)
    {
        if ($filesize < 1000) {
            return $filesize . " b";
        }
        $file_kb = round(($filesize / 1024), 2); // bytes to KB
        $file_mb = round(($filesize / 1048576), 2); // bytes to MB
        $file_gb = round(($filesize / 1073741824), 2); // bytes to GB
                                                       // PHP does funny thing for files larger than 2GB
        if ($file_gb > 1) {
            return $file_gb . " Gb";
        }
        if ($file_mb > 1) {
            return $file_mb . " Mb";
        }
        return $file_kb . " Kb";
    }

    /**
     * get extension
     *
     * @param string $filename            
     * @return string
     */
    public static function getExtension($filename)
    {
        $get_ext = explode(".", $filename);
        $type = array_reverse($get_ext);
        return $type[0];
    }
}

/**
 * ファイルやディレクトリの情報を取得
 *
 * @access public
 * @param
 *            string ファイル名
 * @return array
 */
if (! function_exists('get_file_info')) {

    function get_file_info($file = '')
    {
        if (! file_exists($file)) {
            return FALSE;
        }
        // ファイル名を取得
        if (strpos($file, DIRECTORY_SEPARATOR) !== FALSE) {
            $filename = substr(strrchr($file, DIRECTORY_SEPARATOR), 1);
        } else {
            $filename = $file;
        }
        
        return array(
            'name' => $filename, // ファイル名
            'type' => is_dir($file) ? 'dir' : 'file', // ディレクトリ と ファイル の判別
            'path' => $file, // ファイルパス
            'size' => filesize($file), // ファイルサイズ
            'modified' => date('Y-m-d H:i:s', filemtime($file)), // 最終更新日時
            'readable' => is_readable($file), // 読み込み可能か否か
            'writeable' => is_writable($file), // 書き込み可能か否か
            'executable' => is_executable($file), // 実行可能か否か
            'permission' => substr(sprintf('%o', fileperms($file)), - 3) // パーミッション
                );
    }
}
