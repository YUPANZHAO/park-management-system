#ifndef _PARK_H_
#define _PARK_H_

#include"stack.cpp"
#include"queue.cpp"
#include<vector>
#include<cstring>
#include<ctime>
#include<iostream>
#include<iomanip>
#include<windows.h>
using namespace std;

struct Car {
    string master; //车主姓名
    string num; //车牌号
    time_t enter_time; //入库时间或开始等待时间
    time_t quit_time; //出库时间
    int statu; //当前状态 1代表已入库 0代表正在等待入库 -1代表已出库
    int pay; //缴费金额
    Car() {}
    Car(string s):num(s) {}
    Car(string master, string num, time_t e, time_t q, int s, int pay) {
        this->master = master;
        this->num = num;
        this->enter_time = e;
        this->quit_time = q;
        this->statu = s;
        this->pay = pay;
    }
};

class Park_system {
    private:
        stack<Car> park; //停车场
        queue<Car> wait; //等候区
        stack<Car> temp; //辅助栈
        vector<Car> history; //历史记录
        int maxn; //停车场车位数
        double price; //每秒钟停车价格
        time_t gettime(); //返回一个time_t类型的数据，记录的是当前时间
        string show_time(time_t time); //将time_t类型的数据转换成字符串
        int calculate_money(Car car); //计算该车辆应缴费金额
        string to_string(int n);
    public:
        Park_system(int maxn, double price); //构造函数
        ~Park_system(); //析构函数
        void setprice(double price); //设置价格
        bool enter(string master, string num); //该车入库，若车库已满则置于等候区等待
        bool quit(string num); //该车出库
        void display_park(); //显示当前停车场状况
        void display_wait(); //显示当前等候区状况
        void display_car(Car car); //输出车辆信息
        void display_history(); //显示历史记录
        bool select(string num); //查找车辆 若该车在车库或停车场中输出该车信息
                                 //若该车不在车库或停车场，而在历史记录中则输出时间最近的历史记录
                                 //若在车库、停车场、历史记录中都找不到，输出"未找到该车辆"
        void start(); //启动停车场管理系统
};

#endif