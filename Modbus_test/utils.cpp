#include "utils.h"


using namespace std;
Utils::Utils()
{
}

QSettings* Utils::readIniConf(QString iniFilePath) {
    QSettings* settings = new QSettings(iniFilePath, QSettings::IniFormat);
    return settings;
}


void Utils::saveIniConf(QString iniFilePath, QString valuePath, QString value) {

     QSettings* settings = new QSettings(iniFilePath, QSettings::IniFormat);
     settings -> setValue(valuePath, value);
}

QString Utils::confPath = "./";

void Utils::copyConf(QString new_file_name) {
    qDebug()<<QDir::currentPath();

    QFile conf(Utils::confPath + "config.yaml");

    QFile conf_copy(Utils::confPath + new_file_name);
    conf.open(QIODevice::ReadOnly | QIODevice::Text);
    if (!conf_copy.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "error";
    }

    QString c = conf.readAll();
    conf_copy.write(c.toUtf8(), c.toUtf8().length());

    conf.close();
    conf_copy.close();
}

QList<QString> Utils::getConfM1S1()
{

    QSettings* settings = Utils::readIniConf(Utils::confPath + "conf_mod.ini");


    QString version = settings->value("system_conf/version").toString();
    QString controller_address = settings->value("system_conf/controller_address").toString();
    QString usage = settings->value("system_conf/usage").toBool() ? "工作面" : "皮带";
    QString CS1 = settings->value("system_conf/CS1").toBool() ? "有效" : "无效";
    QString CS1_num = settings->value("system_conf/CS1_num").toString();
    QString CS1_connect = settings->value("system_conf/CS1_connect").toBool() ? "联系" : "不联系";
    QString CS2 = settings->value("system_conf/CS2").toBool() ? "有效" : "无效";
    QString CS2_num = settings->value("system_conf/CS2_num").toString();
    QString CS2_connect = settings->value("system_conf/CS2_connect").toBool() ? "联系" : "不联系";
    QString IO1 = settings->value("system_conf/IO1").toBool() ? "有效" : "无效";
    QString IO2 = settings->value("system_conf/IO2").toBool() ? "有效" : "无效";
    QString IN = settings->value("system_conf/IN").toBool() ? "有效" : "无效";
    QString SP = settings->value("system_conf/SP").toBool() ? "有效" : "无效";
    QString COU = settings->value("system_conf/COU").toBool() ? "有效" : "无效";
    QString COU_connect = settings->value("system_conf/COU_connect").toBool() ? "联系" : "不联系";
    delete settings;
    return {version, usage, controller_address, CS1 , CS1_num, CS1_connect, CS2, CS2_num, CS2_connect, IO1, IO2, IN, SP, COU, COU_connect};
}

void Utils::copyConfBack(QString file_name)
{

    qDebug()<<QDir::currentPath();

    QFile conf_copy(Utils::confPath + "config.yaml");

    QFile conf(Utils::confPath + file_name);
    conf.open(QIODevice::ReadOnly | QIODevice::Text);
    if (!conf_copy.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "error";
    }

    QString c = conf.readAll();
    conf_copy.write(c.toUtf8(), c.toUtf8().length());

    conf.close();
    conf_copy.close();


}

// @brief:
// @param: void
// @ret:
// @birth: created by Lin Ziniu on 20200113
YAML::Node Utils::getConf(QString path)
{
    YAML::Node config = YAML::LoadFile(Utils::confPath.toStdString() + "config_mod.yaml");

    QStringList list = path.split("/");
    for (int i = 0; i < list.size(); i++) {
        config = config[list.at(i).toStdString()];
    }

    return config;
}

YAML::Node Utils::getFullConf()
{
    YAML::Node config = YAML::LoadFile(Utils::confPath.toStdString() + "config_mod.yaml");
    return config;
}

void Utils::saveConf(YAML::Node c)
{

    ofstream fout(Utils::confPath.toStdString() + "config_mod.yaml");
//    qDebug() << c["System"]["IP"]["IP"][3].as<int>();
    fout << c;
    fout.close();
}

void Utils::resetConf()
{
    QFile conf_copy(Utils::confPath + "config.yaml");

    QFile conf(Utils::confPath + "reset.yaml");
    conf.open(QIODevice::ReadOnly | QIODevice::Text);
    if (!conf_copy.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "error";
    }

    QString c = conf.readAll();
    conf_copy.write(c.toUtf8(), c.toUtf8().length());

    conf.close();
    conf_copy.close();
}

void Utils::backupConf(QString backup)
{
    QFile conf(Utils::confPath + "config.yaml");

    QFile conf_copy(Utils::confPath + "backup/" + backup + ".bak");
    conf.open(QIODevice::ReadOnly | QIODevice::Text);
    if (!conf_copy.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "error";
    }

    QString c = conf.readAll();
    conf_copy.write(c.toUtf8(), c.toUtf8().length());

    conf.close();
    conf_copy.close();
}

void Utils::restoreConf(QString backup)
{
    QFile conf(Utils::confPath + "backup/" + backup + ".bak");

    QFile conf_copy(Utils::confPath + "config.yaml");
    conf.open(QIODevice::ReadOnly | QIODevice::Text);
    if (!conf_copy.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "error";
    }

    QString c = conf.readAll();
    conf_copy.write(c.toUtf8(), c.toUtf8().length());

    conf.close();
    conf_copy.close();
}

void Utils::deleteBak(QString backup)
{
    QFile::remove(Utils::confPath + "backup/" + backup + ".bak");
}

QString Utils::setOutput(QKeyEvent *event, MyLineEdit* s)
{
    QString nums = "1234567890";
    QString temp_1= "";
    int temp;
    QList<QString> list;
    QString inputs = "1234567";
    QString outputs = "1234";
    if (event->text().compare("") != 0)
    {
        if (s->isClear)
        {
            s->setText("");
            s->isClear = false;
        }
        list = {"CS1", "CS2", "IO1", "IO2"};

        if (s->text().compare("") == 0)
        {
            if (outputs.contains(event->text()))
            {
                qDebug() << event->text().toInt();
                s->setText(list.at(event->text().toInt() - 1));
            }
        }
        else
        {
            if (event->key() == Qt::Key_Period)
            {
                if (s->text().split(".").length() == 3)
                {
                    return "";
                }
                s->setText(s->text() + ".");
            }
            else
            {
                if (nums.contains(event->text()))
                {
                    temp_1 = s->text().split(".").at(s->text().split(".").length() - 1) + event->text();
                    if (temp_1.toInt() > 0 && temp_1.toInt() < 50)
                    {
                        s->setText(s->text() + event->text());
                    }
                }
            }
        }
        return s->text();
    }
    return "";
}

QString Utils::setInput(QKeyEvent *event, MyLineEdit *s)
{

    QString nums = "1234567890";
    QString temp_1= "";
    int temp;
    QList<QString> list;
    QString inputs = "1234567";
    QString outputs = "1234";
    if (event->text().compare("") != 0)
    {
        if (s->isClear)
        {
            s->setText("");
            s->isClear = false;
        }
        list = {"CS1", "CS2", "IO1", "IO2", "IN", "COM1", "COM2"};

        if (s->text().compare("") == 0)
        {
            if (inputs.contains(event->text()))
            {
                qDebug() << event->text().toInt();
                s->setText(list.at(event->text().toInt() - 1));
            }
        }
        else
        {
            if (event->key() == Qt::Key_Period)
            {
                if (s->text().split(".").length() == 3)
                {
                    return "";
                }
                s->setText(s->text() + ".");
            }
            else
            {
                if (nums.contains(event->text()))
                {
                    temp_1 = s->text().split(".").at(s->text().split(".").length() - 1) + event->text();
                    if (temp_1.toInt() > 0 && temp_1.toInt() < 50)
                    {
                        s->setText(s->text() + event->text());
                    }
                }
            }
        }
        return s->text();
    }
    return "";
}

int Utils::setLeftRight(QKeyEvent *event,  MyLineEdit* s, int current, QList<QString> list)
{
//    list = {"无效", "1#皮带", "2#皮带", "3#皮带", "4#皮带", "破碎机", "转载机", "前部运输机", "后部运输机", "下控制器"};
//    temp = config["Work"]["Detail"]["Basic"]["ChainDevice"][no].as<int>();

    if (event->key() == Qt::Key_Left) {
        current = (current + list.length() - 1) % list.length();
    }

    if (event->key() == Qt::Key_Right) {
        current = (current + 1) % list.length();
    }
//        qDebug() << temp;

    s -> setText(list.at(current));
    return current;
}

QString Utils::setNumber(QKeyEvent *event, MyLineEdit *s, int limit1, int limit2)
{
    QString nums = "1234567890";
    QString temp_1= "";
    if (nums.contains(event->text()) && event->text().compare("") != 0) {
        if (s->isClear) {
            s->setText("");
            s->isClear = false;
        }
        temp_1 = s->text() + event->text();
        if (temp_1.toInt() >= limit1 && temp_1.toInt() <= limit2) {
            s->setText(temp_1);
//            if (!(QString::fromStdString(this->config["Work"]["Detail"]["Advance"]["CoalDepth"][no].as<string>()).compare(s->text()) == 0)) {
//                this->config["Work"]["Detail"]["Advance"]["CoalDepth"][no] = s->text().toStdString();
//            }
        }
    }
    return s->text();
}
