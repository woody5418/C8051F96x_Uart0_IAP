# 版本更新，修改，移植说明文档
## 参考资料
	http://www.pudn.com/Download/item/id/1437854.html
	https://wenku.baidu.com/view/b4fd8a5abe23482fb4da4c20.html
	https://wenku.baidu.com/view/6a11e20c76c66137ee0619e0.html
	https://wenku.baidu.com/view/4e14f06aaf1ffc4ffe47ac2b.html

	code range ：0xE000-0X0FBFF  参考C8051F964手册125页

	C8051F964
	FLASH SIZE:			64KB
	LOCK Byte:			0xFFFF
	LOCK Byte Page:		0xFC00~0xFFFE
	FLASH Memory Space:	0x0000~0xFBFF

	Flash 区域划分 宏定义存放在"updata.h"
	Bootloader:存储在 0xE000 - 0xF9FF 需要6K   
	User1     :存储在 0x0000 - 0x6FFF 28k存储用户代码
	User2     :存储在 0x7000 - 0xDFFF 28k存储升级的代码 

	hex 转bin文件查看GSM OTA\bin工具里面的readme.txt说明

	升级功能开始以后先把代码存储到user2 然后再存储到user1
	
### 说明: 

Application 代码bin文件生成方法：
复制文件夹<bin工具>里面的2个文件 放到Keil C51/BIN的路径下"D:\KeilC51\C51\BIN"
修改：
	Hex2Bin.bat文件的"D:\KeilC51\C51\BIN\hex2bin.exe"（修改为你的地址）
修改：
	Option for Target -> Output ->After Make
	勾选Run User Program #1 输入D:\KeilC51\C51\BIN\Hex2Bin.bat（修改为你的地址）
Bootloader代码需要修改存放地址：
	在Flash->Config Flash Tool->BL51 Locate- Code Range 修改"0xE000-0XFA00"	
	
	
如果需要在APP程序中跳转到boot程序可以添加如下代码
void run_Bootloader(void)
{
	void (*Application)( void);  	//跳转程序使用
	Application = 0X0000;  //此地址存放跳转Boot的前三字节
    (*Application)();
}
也可以使用软件复位直接跳转到boot
#define Rst_CPU RSTSRC |= 0x30 			//软件复位
### 版本号 V1.0

	作    者 ：woody
	联系方式 ：QQ 2490006131
	修改时间 ：2020/09/30
	最新样例 ：
	功能说明 ：C8051F964芯片
			   串口接收发送，串口采用查询接收
			   APP跳转地址单独存放
			   系统启动从Boot开始执行，通过AAPP_RUN_ADD确定的跳转地址跳转到APP
			   升级分包传输，512Byte数据+2CRC
			   
			   
			   
































