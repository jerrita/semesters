<?php
$conn = new mysqli("172.17.0.1", "root", "pa5sw0rd");
if ($conn)
	echo "数据库连接成功！可以申请老师检查！";
else echo "连接失败！继续按指导书修改";
?>