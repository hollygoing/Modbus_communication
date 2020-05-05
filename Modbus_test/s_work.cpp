#include <iostream>
#include "mainwindow.h"
#include "yaml-cpp/yaml.h"
#include "utils.h"
#include <QString>

void MainWindow::s_work(){
    unsigned short *p = nullptr;
    int number_pos = 0;

    Utils::confPath = "/home/fuxuan/project/Modbus_test/";//自己添加的路径
    YAML::Node config = Utils::getConf("Work/Detail/Basic"); //读取部分

    unsigned short avaliable[4]; //整型数据可以直接读，读一位填一位然后发送整个数组即可
    for(int no = 0; no < 4; no++){
        avaliable[no] = config["Avaliable"][no].as<unsigned short>();
    }
    QTimer::singleShot(timeSet,mmrtu,[=]{
        mmrtu->Request16(1,address,4,avaliable);
        address = address + 4;//写在里面，防止因为线程不同步而导致的错误
    });//格式 ID 下位机地址 发送的数据个数 发送的数据所在的数组
    timeSet += time_sp;

    unsigned short headGroundInput[4 * 3]; //字符类型数据需要进行转换
    for(int no = 0; no < 4; no++){
        if(config["HeadGroundInput"][no].as<std::string>() == "0"){
            headGroundInput[number_pos] = 0;
            headGroundInput[number_pos + 1] = 0;
            headGroundInput[number_pos + 2] = 0;
            number_pos = number_pos + 3;
        }else{
            p = type_change(config["HeadGroundInput"][no].as<std::string>());
            headGroundInput[number_pos] = p[0];
            headGroundInput[number_pos + 1] = p[1];
            headGroundInput[number_pos + 2] = p[2];
            number_pos = number_pos + 3;
        }
    }
    QTimer::singleShot(timeSet,mmrtu,[=]{
        mmrtu->Request16(1,address,4*3,headGroundInput);
        address = address + 4 * 3;
    });
    number_pos = 0;
    timeSet += time_sp;

    unsigned short tailGroundInput[4 * 3];
    for(int no = 0; no < 4; no++){
        if(config["TailGroundInput"][no].as<std::string>() == "0"){
            tailGroundInput[number_pos] = 0;
            tailGroundInput[number_pos + 1] = 0;
            tailGroundInput[number_pos + 2] = 0;
            number_pos = number_pos + 3;
        }else{
            p = type_change(config["TailGroundInput"][no].as<std::string>());
            tailGroundInput[number_pos] = p[0];
            tailGroundInput[number_pos + 1] = p[1];
            tailGroundInput[number_pos + 2] = p[2];
            number_pos = number_pos + 3;
        }
    }
    QTimer::singleShot(timeSet,mmrtu,[=]{
        mmrtu->Request16(1,address,4*3,tailGroundInput);
        address = address + 4 * 3;
    });
    number_pos = 0;
    timeSet += time_sp;

    unsigned short remoteStartStopInput[4 * 3];
    for(int no = 0; no < 4; no++){
        if(config["RemoteStartStopInput"][no].as<std::string>() == "0"){
            remoteStartStopInput[number_pos] = 0;
            remoteStartStopInput[number_pos + 1] = 0;
            remoteStartStopInput[number_pos + 2] = 0;
            number_pos = number_pos + 3;
        }else{
            p = type_change(config["RemoteStartStopInput"][no].as<std::string>());
            remoteStartStopInput[number_pos] = p[0];
            remoteStartStopInput[number_pos + 1] = p[1];
            remoteStartStopInput[number_pos + 2] = p[2];
            number_pos = number_pos + 3;
        }
    }
    QTimer::singleShot(timeSet,mmrtu,[=]{
        mmrtu->Request16(1,address,4*3,remoteStartStopInput);
        address = address + 4 * 3;
    });
    number_pos = 0;
    timeSet += time_sp;

    unsigned short completeOutput[4 * 10 * 3];
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 10; j++){
            if(config["CompleteOutput"][i][j].as<std::string>() == "0"){
                completeOutput[number_pos] = 0;
                completeOutput[number_pos + 1] = 0;
                completeOutput[number_pos + 2] = 0;
                number_pos = number_pos + 3;
            }else{
                p = type_change(config["CompleteOutput"][i][j].as<std::string>());
                completeOutput[number_pos] = p[0];
                completeOutput[number_pos + 1] = p[1];
                completeOutput[number_pos + 2] = p[2];
                number_pos = number_pos + 3;
            }
        }
    }
    QTimer::singleShot(timeSet,mmrtu,[=]{
        mmrtu->Request16(1,address,4*10*3,completeOutput);
        address = address + 4 * 10 * 3;
    });
    number_pos = 0;
    timeSet += time_sp;

    unsigned short readyInput[4 * 10 * 3];
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 10; j++){
            if(config["ReadyInput"][i][j].as<std::string>() == "0"){
                readyInput[number_pos] = 0;
                readyInput[number_pos + 1] = 0;
                readyInput[number_pos + 2] = 0;
                number_pos = number_pos + 3;
            }else{
                p = type_change(config["ReadyInput"][i][j].as<std::string>());
                readyInput[number_pos] = p[0];
                readyInput[number_pos + 1] = p[1];
                readyInput[number_pos + 2] = p[2];
                number_pos = number_pos + 3;
            }
        }
    }
    QTimer::singleShot(timeSet,mmrtu,[=]{
        mmrtu->Request16(1,address,4*10*3,readyInput);
        address = address + 4 * 10 * 3;
    });
    number_pos = 0;
    timeSet += time_sp;

    unsigned short relateLine[4];
    for(int no = 0; no < 4; no++){
        relateLine[no] = config["RelateLine"][no].as<unsigned short>();
    }
    QTimer::singleShot(timeSet,mmrtu,[=]{
        mmrtu->Request16(1,address,4,relateLine);
        address = address + 4;
    });
    timeSet += time_sp;

    unsigned short relationshipWithStop[4];
    for(int no = 0; no < 4; no++){
        relationshipWithStop[no] = config["RelationshipWithStop"][no].as<unsigned short>();
    }
    QTimer::singleShot(timeSet,mmrtu,[=]{
        mmrtu->Request16(1,address,4,relationshipWithStop);
        address = address + 4;
    });
    timeSet += time_sp;

    unsigned short startWarnNum[4];
    for(int no = 0; no < 4; no++){
        startWarnNum[no] = config["StartWarnNum"][no].as<unsigned short>();
    }
    QTimer::singleShot(timeSet,mmrtu,[=]{
        mmrtu->Request16(1,address,4,startWarnNum);
        address = address + 4;
    });
    timeSet += time_sp;

    unsigned short remoteStopInput[4 * 8 * 3];
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 8; j++){
            if(config["RemoteStopInput"][i][j].as<std::string>() == "0"){
                remoteStopInput[number_pos] = 0;
                remoteStopInput[number_pos + 1] = 0;
                remoteStopInput[number_pos + 2] = 0;
                number_pos = number_pos + 3;
            }else{
                p = type_change(config["RemoteStopInput"][i][j].as<std::string>());
                remoteStopInput[number_pos] = p[0];
                remoteStopInput[number_pos + 1] = p[1];
                remoteStopInput[number_pos + 2] = p[2];
                number_pos = number_pos + 3;
            }
        }
    }
    QTimer::singleShot(timeSet,mmrtu,[=]{
        mmrtu->Request16(1,address,4*8*3,remoteStopInput);
        address = address + 4 * 8 * 3;
    });
    number_pos = 0;
    timeSet += time_sp;

    unsigned short remoteStopOutput[4 * 8 * 3];
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 8; j++){
            if(config["RemoteStopOutput"][i][j].as<std::string>() == "0"){
                remoteStopOutput[number_pos] = 0;
                remoteStopOutput[number_pos + 1] = 0;
                remoteStopOutput[number_pos + 2] = 0;
                number_pos = number_pos + 3;
            }else{
                p = type_change(config["RemoteStopOutput"][i][j].as<std::string>());
                remoteStopOutput[number_pos] = p[0];
                remoteStopOutput[number_pos + 1] = p[1];
                remoteStopOutput[number_pos + 2] = p[2];
                number_pos = number_pos + 3;
            }
        }
    }
    QTimer::singleShot(timeSet,mmrtu,[=]{
        mmrtu->Request16(1,address,4*8*3,remoteStopOutput);
        address = address + 4 * 8 * 3;
    });
    number_pos = 0;
    timeSet += time_sp;

    unsigned short headGroundOutput[4 * 3];
    for(int no = 0; no < 4; no++){
        if(config["HeadGroundOutput"][no].as<std::string>() == "0"){
            headGroundOutput[number_pos] = 0;
            headGroundOutput[number_pos + 1] = 0;
            headGroundOutput[number_pos + 2] = 0;
            number_pos = number_pos + 3;
        }else{
            p = type_change(config["HeadGroundOutput"][no].as<std::string>());
            headGroundOutput[number_pos] = p[0];
            headGroundOutput[number_pos + 1] = p[1];
            headGroundOutput[number_pos + 2] = p[2];
            number_pos = number_pos + 3;
        }
    }
    QTimer::singleShot(timeSet,mmrtu,[=]{
        mmrtu->Request16(1,address,4*3,headGroundOutput);
        address = address + 4 * 3;
    });
    number_pos = 0;
    timeSet += time_sp;

    unsigned short tailGroundOutput[4 * 3];
    for(int no = 0; no < 4; no++){
        if(config["TailGroundOutput"][no].as<std::string>() == "0"){
            tailGroundOutput[number_pos] = 0;
            tailGroundOutput[number_pos + 1] = 0;
            tailGroundOutput[number_pos + 2] = 0;
            number_pos = number_pos + 3;
        }else{
            p = type_change(config["TailGroundOutput"][no].as<std::string>());
            tailGroundOutput[number_pos] = p[0];
            tailGroundOutput[number_pos + 1] = p[1];
            tailGroundOutput[number_pos + 2] = p[2];
            number_pos = number_pos + 3;
        }
    }
    QTimer::singleShot(timeSet,mmrtu,[=]{
        mmrtu->Request16(1,address,4*3,tailGroundOutput);
        address = address + 4 * 3;
    });
    number_pos = 0;
    timeSet += time_sp;

    unsigned short chainDevice[4];
    for(int no = 0; no < 4; no++){
        chainDevice[no] = config["ChainDevice"][no].as<unsigned short>();
    }
    QTimer::singleShot(timeSet,mmrtu,[=]{
        mmrtu->Request16(1,address,4,chainDevice);
        address = address + 4;
    });
    timeSet += time_sp;

    unsigned short remoteStopNum[4];
    for(int no = 0; no < 4; no++){
        remoteStopNum[no] = config["RemoteStopNum"][no].as<unsigned short>();
    }
    QTimer::singleShot(timeSet,mmrtu,[=]{
        mmrtu->Request16(1,address,4,remoteStopNum);
        address = address + 4;
    });
    timeSet += time_sp;

    unsigned short startWarnTime[4];
    for(int no = 0; no < 4; no++){
        startWarnTime[no] = config["StartWarnTime"][no].as<unsigned short>();
    }
    QTimer::singleShot(timeSet,mmrtu,[=]{
        mmrtu->Request16(1,address,4,startWarnTime);
        address = address + 4;
    });
    timeSet += time_sp;

    p = nullptr;
}
