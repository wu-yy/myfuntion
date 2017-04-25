<?
$Patternstr="黄|黑|走私|发票|枪支|东突";
 $Pattern=explode("|",$Patternstr);

 $inputstr="黄色黑色东突枪支弹药走私药品增值发票";
 for($i=0;$i<count($Pattern);$i++)
 {
     if(strpos($inputstr,$Pattern[$i])!==false) //如果找到字符集中的某个字符串
     {
         $outstr=str_replace($Pattern[$i],"",$inputstr); //将该字符串过滤掉
         $inputstr=$outstr;
     }

 }
 echo $outstr."<br>";



?>
