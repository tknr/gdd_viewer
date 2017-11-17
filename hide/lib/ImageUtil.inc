<?php

/**
 */
class ImageUtil
{

    /**
     *
     * @var string
     */
    private $src_image;

    private $resource;

    private $resource_org;

    /**
     *
     * @param string $src_image            
     */
    function __construct($src_image)
    {
        $this->src_image = $src_image;
    }

    /**
     *
     * @return string
     */
    public function getType()
    {
        $ext = FileUtil::getExtension($this->src_image);
        if ($ext == 'jpeg') {
            $ext = 'jpg';
        }
        return $ext;
    }

    /**
     *
     * @param number $width            
     * @param number $height            
     * @param number $crop            
     * @return boolean
     * @see http://php.net/manual/ja/function.imagecopyresampled.php#104028
     */
    public function resize($width, $height, $crop = 0)
    {
        if (! list ($w, $h) = getimagesize($this->src_image)) {
            return false;
        }
        
        switch ($this->getType()) {
            case 'bmp':
                {
                    $this->resource_org = imagecreatefromwbmp($this->src_image);
                    break;
                }
            case 'gif':
                {
                    $this->resource_org = imagecreatefromgif($this->src_image);
                    break;
                }
            case 'jpg':
                {
                    $this->resource_org = imagecreatefromjpeg($this->src_image);
                    break;
                }
            case 'png':
                {
                    $this->resource_org = imagecreatefrompng($this->src_image);
                    break;
                }
            default:
                {
                    return false;
                }
        }
        
        // resize
        if ($crop) {
            if ($w < $width or $h < $height) {
                return "Picture is too small!";
            }
            $ratio = max($width / $w, $height / $h);
            $h = $height / $ratio;
            $x = ($w - $width / $ratio) / 2;
            $w = $width / $ratio;
        } else {
            if ($w < $width and $h < $height) {
                return "Picture is too small!";
            }
            $ratio = min($width / $w, $height / $h);
            $width = $w * $ratio;
            $height = $h * $ratio;
            $x = 0;
        }
        
        $this->resource = imagecreatetruecolor($width, $height);
        
        // preserve transparency
        switch ($this->getType()) {
            case 'gif':
            case 'png':
                {
                    imagecolortransparent($this->resource, imagecolorallocatealpha($this->resource, 0, 0, 0, 127));
                    imagealphablending($this->resource, false);
                    imagesavealpha($this->resource, true);
                }
        }
        
        imagecopyresampled($this->resource, $this->resource_org, 0, 0, $x, 0, $width, $height, $w, $h);
        return true;
    }

    /**
     *
     * @return boolean
     */
    public function printOut()
    {
        switch ($this->getType()) {
            case 'bmp':
                {
                    header("content-type: image/x-bmp");
                    self::imagebmp($this->resource);
                    break;
                }
            case 'gif':
                {
                    imagegif($this->resource);
                    break;
                }
            case 'jpg':
                {
                    header("content-type: image/jpeg");
                    imagejpeg($this->resource);
                    break;
                }
            case 'png':
                {
                    header("content-type: image/png");
                    imagepng($this->resource);
                    break;
                }
            default:
                {
                    return false;
                }
        }
        ImageDestroy($this->resource_org);
        ImageDestroy($this->resource);
        return true;
    }

    /**
     *
     * @param unknown $im            
     * @param string $fn            
     * @return boolean
     * @see http://php.net/manual/ja/ref.image.php#63689
     */
    public static function imagebmp($im, $fn = false)
    {
        if (! $im)
            return false;
        
        if ($fn === false)
            $fn = 'php://output';
        $f = fopen($fn, "w");
        if (! $f)
            return false;
            
            // Image dimensions
        $biWidth = imagesx($im);
        $biHeight = imagesy($im);
        $biBPLine = $biWidth * 3;
        $biStride = ($biBPLine + 3) & ~ 3;
        $biSizeImage = $biStride * $biHeight;
        $bfOffBits = 54;
        $bfSize = $bfOffBits + $biSizeImage;
        
        // BITMAPFILEHEADER
        fwrite($f, 'BM', 2);
        fwrite($f, pack('VvvV', $bfSize, 0, 0, $bfOffBits));
        
        // BITMAPINFO (BITMAPINFOHEADER)
        fwrite($f, pack('VVVvvVVVVVV', 40, $biWidth, $biHeight, 1, 24, 0, $biSizeImage, 0, 0, 0, 0));
        
        $numpad = $biStride - $biBPLine;
        for ($y = $biHeight - 1; $y >= 0; -- $y) {
            for ($x = 0; $x < $biWidth; ++ $x) {
                $col = imagecolorat($im, $x, $y);
                fwrite($f, pack('V', $col), 3);
            }
            for ($i = 0; $i < $numpad; ++ $i)
                fwrite($f, pack('C', 0));
        }
        fclose($f);
        return true;
    }
}