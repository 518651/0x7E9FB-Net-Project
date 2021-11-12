#include "Un-main.h"



//http://oh6kf0af4o.great-site.net/download/Config_download/Config.WaotoCry


int downnload(string usl)
{
    string download_usl = usl;
    size_t len = download_usl.length();//获取字符串长度
    int nmlen = MultiByteToWideChar(CP_ACP, 0, download_usl.c_str(), len + 1, NULL, 0);
    wchar_t* buffer = new wchar_t[nmlen];
    MultiByteToWideChar(CP_ACP, 0, download_usl.c_str(), len + 1, buffer, nmlen);
    HRESULT hr = URLDownloadToFile(NULL, buffer, _T("I:\\Project\\C++\\C++_\\0x7E9FB\\Debug\\Config.WaotoCry"), 0, NULL);
    if (hr == S_OK)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}