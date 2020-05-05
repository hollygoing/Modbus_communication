#ifndef UTILS_H
#define UTILS_H
#include <QString>
#include <QSettings>
#include <QFile>
#include <QDebug>
#include <QDir>
#include <QFile>
#include <QKeyEvent>
#include <yaml-cpp/yaml.h>
#include <fstream>
#include <QTimer>
#include "mylineedit.h"


class Utils
{
public:
    Utils();
    static QSettings* readIniConf(QString iniFilePath);
    static void saveIniConf(QString iniFilePath, QString valuePath, QString value);
    static QString confPath;
    static void copyConf(QString new_file_name);
    static QList<QString> getConfM1S1();
    static void copyConfBack(QString file_name);

    static YAML::Node getConf(QString confPath);
    static YAML::Node getFullConf();
    static void saveConf(YAML::Node c);
    static void resetConf();

    static void backupConf(QString backup);
    static void restoreConf(QString backup);
    static void deleteBak(QString backup);

    static QString setOutput(QKeyEvent* event, MyLineEdit* s);
    static QString setInput(QKeyEvent* event, MyLineEdit* s);
    static int setLeftRight(QKeyEvent *event, MyLineEdit* s, int current, QList<QString> list);
    static QString setNumber(QKeyEvent* event, MyLineEdit* s, int limit1, int limit2);

};
#endif // UTILS_H
