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

# 其他的等待明天补充....... (就是累死了)#