#include <iostream>
#include "mainwindow.h"

unsigned short * MainWindow::type_change(std::string s){
    static unsigned short result[3];
    if(s[0] == 'C' && s[1] == 'S'){
        int pos_1,pos_2;

        pos_1 = s.find(".");//第一次出现"."的位置
        pos_2 = s.rfind(".");//最后一次出现"."的位置
        result[0] = 1*100 + atoi(s.substr(2,pos_1-2).c_str());
        result[1] = atoi(s.substr(pos_1 + 1 , pos_2 - pos_1 - 1).c_str());
        result[2] = atoi(s.substr(pos_2 + 1).c_str());
        return result;
    }
    else if(s[0] == 'I' && s[1] == 'O'){
        int pos_1,pos_2;

        pos_1 = s.find(".");//第一次出现"."的位置
        pos_2 = s.rfind(".");//最后一次出现"."的位置
        result[0] = 2*100 + atoi(s.substr(2,pos_1-2).c_str());
        result[1] = atoi(s.substr(pos_1 + 1 , pos_2 - pos_1 - 1).c_str());
        result[2] = atoi(s.substr(pos_2 + 1).c_str());
        return result;
    }
    else if(s[0] == 'I' && s[1] == 'N'){
        int pos_1,pos_2;

        pos_1 = s.find(".");//第一次出现"."的位置
        pos_2 = s.rfind(".");//最后一次出现"."的位置
        result[0] = 300;
        result[1] = atoi(s.substr(pos_1 + 1 , pos_2 - pos_1 - 1).c_str());
        result[2] = atoi(s.substr(pos_2 + 1).c_str());
        return result;
    }
    else if(s[0] == 'C' && s[1] == 'O' && s[2] == 'M'){
        int pos_1,pos_2;

        pos_1 = s.find(".");//第一次出现"."的位置
        pos_2 = s.rfind(".");//最后一次出现"."的位置
        result[0] = 4*100 + atoi(s.substr(3,pos_1-3).c_str());
        result[1] = atoi(s.substr(pos_1 + 1 , pos_2 - pos_1 - 1).c_str());
        result[2] = atoi(s.substr(pos_2 + 1).c_str());
        return result;
    }else
        return nullptr;
}
