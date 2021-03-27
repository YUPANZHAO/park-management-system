#include "park_system.h"

int main() {
    ShowWindow(GetForegroundWindow(),SW_MAXIMIZE); //页面全屏
    int n;
    double m;
    cout << endl << "初始化停车场管理系统" << endl;
    cout << endl << "请输入停车场车位数: ";
    cin >> n;
    cout << endl << "请输入停车场每秒收费价格(元，可为小数): ";
    cin >> m;
    Park_system park(n, m);
    park.start();
    return 0;
}