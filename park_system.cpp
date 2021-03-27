#include "park_system.h"

time_t Park_system::gettime() {
    return time(NULL);
}

string Park_system::show_time(time_t time) {
    char *s = ctime(&time);
    int len = strlen(s);
    string res = "";
    for(int i=0; i < len-1; i++) res += s[i];    
    return res; 
} 

int Park_system::calculate_money(Car car) {
    int sec = (int)(car.quit_time - car.enter_time);
    return (int)(this->price*sec);
}

string Park_system::to_string(int n) {
    string res = "";
    while(n) {
        res += n%10 + '0';
        n /= 10;
    }
    int len = res.size();
    for(int i=0; i < len/2; i++) {
        char c = res[i];
        res[i] = res[len-1-i];
        res[len-1-i] = c;
    }
    if(res.size() == 0) res = "0";
    return res;
}

Park_system::Park_system(int maxn, double price) {
    this->maxn = maxn;    
    this->price = price;
}

Park_system::~Park_system() {
    
}

void Park_system::setprice(double price) {
    this->price = price;
}

void Park_system::display_park() {
    int num = 5;
    putchar('+');
    for(int i=0; i < num*11 - 1; i++) putchar('-');
    putchar('+'); 
    cout << endl << "| 停车场管理系统";
    for(int i=0; i < 8+11*(num-5); i++) putchar(' ');
    cout << "已停车辆数:" << setw(3) << park.size();
    cout << "  等候车辆数:" << setw(3) << wait.size() << " |" << endl;
    putchar('+');
    for(int i=0; i < num*11 - 1; i++) putchar('-');
    putchar('+');
    cout << endl;
    int vert = maxn/num + (maxn%num?1:0);
    while(!park.empty()) {
        temp.push(park.top());
        park.pop();
    }
    for(int i=0; i < vert; i++) {
        int len = (i+1 == vert && maxn%num != 0? (maxn%num):num)*11;
        for(int j=0; j <= len; j++) {
            if(j%11 == 0) putchar('+');
            else putchar('-');
        } cout << endl;
        for(int j=0; j < len/11; j++) {
            if(!temp.empty()) {
                Car car = temp.top();
                temp.pop();
                park.push(car);
                cout << "| " << car.num << " ";
            }else cout << "|          ";
        } cout << '|' << endl;
        for(int j=0; j <= len; j++) {
            if(j%11 == 0) putchar('+');
            else putchar('-');
        } cout << endl;
    }
    cout << endl;
}

void Park_system::display_wait() {
    cout << "+------------------------------------------------+" << endl;
    cout << "|                等待入库车辆列表                |" << endl;
    cout << "+----------+----------+--------------------------+" << endl;
    cout << "|  车牌号  | 车主姓名 |       开始等待时间       |" << endl;
    cout << "+----------+----------+--------------------------+" << endl;
    int cnt = wait.size();
    if(cnt == 0) {
        cout << "|    无    |    无    |            无            |" << endl;
        cout << "+----------+----------+--------------------------+" << endl;
    }
    while(cnt--) {
        Car car = wait.front(); wait.pop(); wait.push(car);
        string res = "| " + car.num + " |";
        int len = car.master.size();
        for(int i=0; i < (10-len)/2; i++) res += ' ';
        res += car.master;
        for(int i=0;i < (11-len)/2; i++) res += ' ';
        res += "| " + show_time(car.enter_time) + " |";
        cout << res << endl;
        cout << "+----------+----------+--------------------------+" << endl;
    }
    cout << endl;
}

void Park_system::display_car(Car car) {
    cout << "+-----------------------------------------+" << endl;
    cout << "|                车辆信息                 |" << endl;
    cout << "+--------------+--------------------------+" << endl;
    cout << "|     车主     |";
    int len = car.master.size();
    for(int i=0; i < (26-len)/2; i++) putchar(' ');
    cout << car.master;
    for(int i=0; i < (27-len)/2; i++) putchar(' ');
    cout << "|" << endl;
    cout << "+--------------+--------------------------+" << endl;
    cout << "|    车牌号    |";
    len = car.num.size();
    for(int i=0; i < (26-len)/2; i++) putchar(' ');
    cout << car.num;
    for(int i=0; i < (27-len)/2; i++) putchar(' ');
    cout << "|" << endl;
    cout << "+--------------+--------------------------+" << endl;
    cout << "|     状态     |";
    if(car.statu == 1) cout << "          已入库          ";
    else if(car.statu == 0) cout << "       正在等待入库       ";
    else cout << "          已出库          ";
    cout << "|" << endl;
    cout << "+--------------+--------------------------+" << endl;
    string str1,str2;
    if(car.statu == 1) str1 = "   入库时间   ";
    else if(car.statu == 0) str1 = " 开始等待时间 ";
    else str1 = "   出库时间   ";
    if(car.statu == -1) str2 = show_time(car.quit_time);
    else str2 = show_time(car.enter_time);
    cout << "|"+str1+"| "+ str2 +" |" << endl;
    cout << "+--------------+--------------------------+" << endl;
    if(car.statu == -1) {
        cout << "|   缴费金额   |";
        str1 = to_string(car.pay);
        len = str1.size();
        for(int i=0; i < (26-len)/2; i++) putchar(' ');
        cout << str1;
        for(int i=0; i < (27-len)/2; i++) putchar(' ');
        cout << "|" << endl;
        cout << "+--------------+--------------------------+" << endl;
    }
    cout << endl;
}

void Park_system::display_history() {
    cout << "+----------------------------------------------------------------------------------------+" << endl;
    cout << "|                                       历史记录                                         |" << endl;
    cout << "+----------+----------+--------------------------+--------------------------+------------+" << endl;
    cout << "|  车牌号  |   车主   |         入库时间         |         出库时间         |  缴费金额  |" << endl;
    cout << "+----------+----------+--------------------------+--------------------------+------------+" << endl;
    int cnt = history.size();
    if(cnt == 0) {
        cout << "|    无    |    无    |            无            |            无            |     无     |" << endl;
        cout << "+----------+----------+--------------------------+--------------------------+------------+" << endl;
    }
    for(int i=0; i < cnt; i++) {
        Car car = history[i];
        string res = "| " + car.num + " |";
        int len = car.master.size();
        for(int i=0; i < (10-len)/2; i++) res += ' ';
        res += car.master;
        for(int i=0;i < (11-len)/2; i++) res += ' ';
        res += "| " + show_time(car.enter_time) + " |";
        res += " " + show_time(car.quit_time) + " |";
        string tim = to_string(car.pay);
        len = tim.size();
        for(int i=0; i < (12-len)/2; i++) res += ' ';
        res += tim;
        for(int i=0; i < (13-len)/2; i++) res += ' ';
        res += '|';
        cout << res << endl;
        cout << "+----------+----------+--------------------------+--------------------------+------------+" << endl;
    }
    cout << endl;
}

void Park_system::start() {
    system("cls");
    cout << endl; display_park(); display_wait();
    cout << "================" << endl;
    cout << "1/ 进入车辆\n2/ 退出车辆\n3/ 设置收费价格" << endl;
    cout << "4/ 查看历史记录\n5/ 查找车辆\n6/ 退出系统\n请输入操作序号: ";
    while(true) {
        int oper;
        cin.clear();
        string str;
        cin >> str;
        if(str.size() != 1 || !isdigit(str[0])) oper = -1;
        else oper = str[0] - '0';
        string master, num;
        double price;
        bool flag;
        switch(oper) {
            case 1:
                cout << "请输入车主姓名(汉字2~4个): ";
                cin >> master;
                cout << "请输入车牌号(一个汉字以及6个数字或字母,例:粤A88888): ";
                cin >> num;
                flag = enter(master, num);
                system("cls");
                cout << endl; display_park(); display_wait();
                if(flag) select(num);
                else cout << endl << "输入格式错误" << endl << endl;
                break;
            case 2:
                cout << "请输入车牌号: ";
                cin >> num;
                flag = quit(num);
                system("cls");
                cout << endl; display_park(); display_wait();
                if(flag) select(num);
                else cout << endl << "未在停车场中找到该车辆" << endl << endl;
                break;
            case 3:
                cout << "请输入新收费价格(元/秒): ";
                cin >> price;
                setprice(price);
                system("cls");
                cout << endl; display_park(); display_wait();
                cout << "收费价格已修改为: " << this->price << "元/秒" << endl << endl;
                break;
            case 4:
                system("cls");
                cout << endl; display_park(); display_wait();
                display_history();
                break;
            case 5:
                cout << "请输入车牌号: ";
                cin >> num;
                system("cls");
                cout << endl; display_park(); display_wait();
                flag = select(num);
                if(!flag) cout << "未找到该车辆信息" << endl << endl;
                break;
            case 6: return ;
            default: system("cls");
                     cout << endl; display_park();
                     display_wait();
                     cout << endl << "无法执行此操作" << endl << endl;
        }
        cout << "================" << endl;
        cout << "1/ 进入车辆\n2/ 退出车辆\n3/ 设置收费价格" << endl;
        cout << "4/ 查看历史记录\n5/ 查找车辆\n6/ 退出系统\n请输入操作序号: ";
    }
}

bool Park_system::enter(string master, string num) {
    if(master.size() > 8 || num.size() != 8) return false; 
    if(park.size() < maxn) park.push(Car(master,num,gettime(),gettime(),1,0));
    else wait.push(Car(master,num,gettime(),gettime(),0,0));
    return true;
}

bool Park_system::quit(string num) {
    Car car;
    while(!park.empty() && park.top().num != num) {
        temp.push(park.top());
        park.pop();
    }
    if(park.empty()) {
        while(!temp.empty()) {
            park.push(temp.top());
            temp.pop();
        }
        return false;
    }
    car = park.top();
    park.pop();
    car.quit_time = gettime();
    car.statu = -1;
    car.pay = calculate_money(car);
    history.push_back(car);
    while(!temp.empty()) {
        park.push(temp.top());
        temp.pop();
    }
    if(!wait.empty()) {
    	Car car = wait.front();
		wait.pop();
		car.enter_time = gettime();
		park.push(car);
    }
    return true;
}

bool Park_system::select(string num) {
    bool flag = false;
    Car car, tmp;
    while(!park.empty() && park.top().num != num) {
        temp.push(park.top());
        park.pop();
    }
    if(!park.empty()) {
        car = park.top();
        flag = true;
    }
    while(!temp.empty()) {
        park.push(temp.top());
        temp.pop();
    }
    if(flag) {
        display_car(car);
        return true;
    }
    int cnt = wait.size();
    while(cnt--) {
        tmp = wait.front(); wait.pop();
        if(!flag && tmp.num == num) {
            flag = true;
            car = tmp;    
        }
        wait.push(tmp);
    } 
    if(flag) {
        display_car(car);
        return true;
    }
    cnt = history.size();
    for(int i=cnt-1; i >= 0; i--) {
        tmp = history[i];
        if(tmp.num == num) {
            car = tmp;
            flag = true;
            break;
        } 
    }
    if(flag) {
        display_car(car);
        return true;
    }
    return false;
}
