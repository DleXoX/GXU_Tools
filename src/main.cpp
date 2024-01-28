
#include<iostream>
#include<requests.h>
#include "icmp.h"
#include "hlog.h"
//
//int mai1n() {
//	hlog_disable();
//
//	HWND hwnd = GetForegroundWindow();	//获取程序启动时的窗口
//	if (hwnd) {
//		ShowWindow(hwnd, SW_HIDE);				//设置指定窗口的显示状态
//	}
//	while (true) {
//		if (!isConnected()) {
//			//requests::get("http://172.17.0.2:801/eportal/?c=ACSetting&a=login&DDDDD=2007310429@unicom&upass=252476&xxwlanacname=ME60-1&wlanacip=172.17.0.2");
//			requests::get("http://172.17.0.2:801/eportal/?c=ACSetting&a=login&DDDDD=2007310436@cmcc&upass=242315&wlanacname=ME60-1&wlanacip=172.17.0.2");
//		}
//		else { 
//			hv_sleep(60); }
//		hv_sleep(10);
//	}
//		return 0;
//}

//auto res = requests::get("http://172.17.0.2:801/eportal/?c=ACSetting&a=Login&loginMethod=1&protocol=http%3A&hostname=172.17.0.2&port=&iTermType=1&wlanuserip=10.128.96.148&wlanacip=210.36.18.65&wlanacname=ME60-1&redirect=null&session=null&vlanid=0&mac=00-00-00-00-00-00&ip=10.128.96.148&enAdvert=0&jsVersion=2.4.3&DDDDD=%2C0%2C2007310429%40unicom&upass=252476&R1=0&R2=0&R3=0&R6=0&para=00&0MKKey=123456&buttonClicked=&redirect_url=&err_flag=&username=&password=&user=&cmd=&Login=");
//auto res = requests::get("http://172.17.0.2:801/eportal/?c=ACSetting&a=Login&loginMethod=1&protocol=http%3A&hostname=172.17.0.2&port=&iTermType=1&wlanuserip=10.128.96.148&wlanacip=210.36.18.65&wlanacname=ME60-1&redirect=null&session=null&vlanid=0&mac=00-00-00-00-00-00&ip=10.128.96.148&enAdvert=0&jsVersion=2.4.3&DDDDD=%2C0%2C2007310415%40cmcc&upass=08527022&R1=0&R2=0&R3=0&R6=0&para=00&0MKKey=123456&buttonClicked=&redirect_url=&err_flag=&username=&password=&user=&cmd=&Login=");
