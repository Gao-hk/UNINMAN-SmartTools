//SecurityHouse
const char bAPDU_SecurityHouse[][65] = {
/*-----------------------------------------------------
卡片的文件结构如下：
		output("—MF═╗                              ┏ 主控密钥");
		output("      ‖                              ┃ 应用维护密钥");
		output("      ‖                              ┃ 外部认证密钥");
		output("      ‖═══════KEY文件（FID=0000）————┃ 内部认证密钥");
		output("      ‖                              ┃ PIN密钥");
		output("      ‖                              ┗ PIN重装密钥");
		output("      ‖");
		output("      ‖");
		output("      ‖");
		output("      ‖══ADF═╗   （FID=0xADF1，名称=“SecurityHouse”）");
		output("                 ‖");
		output("                 ‖                              ┏ 主控密钥");
		output("                 ‖                              ┃ 应用维护密钥");
		output("                 ‖                              ┃ 外部认证密钥");
		output("                 ‖═══════KEY文件（FID=0000）————┃ 内部认证密钥");
		output("                 ‖                              ┃ PIN密钥");
		output("                 ‖                              ┗ PIN重装密钥");
		output("                 ‖");
		output("                 ‖═══════自己SM2公钥文件0201");
		output("                 ‖═══════自己SM2私钥文件0202");
		output("                 ‖");
		output("                 ‖═══════对方SM2公钥文件0403");
		output("                 ‖═══════鉴权SM2私钥文件0502");
-----------------------------------------------------*/
//创建ADF1目录以及KEY文件，在创建ADF1前，请先计算好需要用到的空间大小，尽量预留空间大一些。
//创建ADF   FID=ADF_FID，空间=0x002000，建立权限=F2，擦除权限=F2，名称=ADF_NAMEE
{"98E0ADF11B18002000F2F2FFFFFFFFFFFFFFFF5365637572697479486F757365"},
//创建KEY文件
{"98E00000081F10FFF0F2FFFFFF"},
//========装载KEY 初次个人化时可以明文装KEY；但是装载完成后如果要更新需按照KEY文件的权限和线路保护方式进行
//SM4版密钥
//1、明文装载MK  
{"B8D4000115F0F20401FF436F7265536869656C644D5478303031"},
//2、明文装载DAMK   版本（索引）=01，算法=04（SM4），重试次数10
{"B8D4010115F0F204FFAA4144463144414D4B4144463144414D4B"},
//3、明文装载ITK   版本（索引）=01，算法=04（SM4）
{"B8D4030115F0F204FFFF414446312D49544B414446312D49544B"},
//4、明文装载ETK   版本（索引）=01，算法=04（SM4），后续状态02，重试次数10
{"B8D4020115F0F20402AA414446312D45544B414446312D45544B"},
//5、明文装载PIN   PIN=010101010101，后续状态01，重试次数3
{"B8D40A0115F0F1FF0133010101010101FFFFFFFFFFFFFFFFFFFF"},
//6、明文装载RPK   版本（索引）=01，算法=04（SM4），重试次数10
{"B8D4080115F0F204FFAA414446312D52504B414446312D52504B"},
//========装载KEY 结束

//一、ADF下SM2公私钥文件的建立	
//自己公钥： 0x0201;
//自己私钥： 0x0202;
//对方公钥： 0x0403;
//鉴权私钥： 0x0502;
//创建SM2公钥文件FID=0201
{"98E00201081AFFFFF0F1FFFFFF"},
//创建SM2私钥文件FID=0202
{"98E00202081BFFFFF0F1FFFFFF"},
//创建SM2公钥文件FID=0403
{"98E00403081AFFFFF0F1FFFFFF"},
//创建SM2私钥文件FID=0502
{"98E00502081BFFFFF0F1FFFFFF"},
//生成SM2公私钥对,公钥文件FID=0201,私钥文件FID=0202
{"9840000108C0020201C2020202"},

};