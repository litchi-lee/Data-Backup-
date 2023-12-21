#ifndef CONFIGMANAGER_H
#define CONFIGMANAGER_H
#include <QJsonDocument>
#include <QJsonObject>
#include <QFile>
#include <string>
#include <QTextStream>
#include <QDebug>
#include <QFileInfo>
#include <QDir>
#include <QApplication>
using namespace std;

class ConfigManager {
    public:

    static QString getDesPath()
    {
        QFile this_file_ptr(QDir::cleanPath(QCoreApplication::applicationDirPath() + QDir::separator() + QString("/configuration.json")));
        if(false == this_file_ptr.exists())
        {
            return "None";
        }
        if(false == this_file_ptr.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            return "None";
        }
        QString string_value = this_file_ptr.readAll();

        this_file_ptr.close();

        QJsonDocument jsonDoc = QJsonDocument::fromJson(string_value.toUtf8());
        QJsonObject jsonObj = jsonDoc.object();
        return jsonObj["destinationFilePath"].toString();
    }

    static bool updateDesPath(QString path)
    {
        if(!copyDir(getDesPath(), path)) return false;

        QFile file(QDir::cleanPath(QCoreApplication::applicationDirPath() + QDir::separator() + QString("/configuration.json")));
        file.open(QIODevice::ReadOnly | QIODevice::Text);
        QString content = QString(file.readAll());

        QJsonDocument jsonDoc = QJsonDocument::fromJson(content.toUtf8());
        QJsonObject jsonObj = jsonDoc.object();
        file.close(); // 关闭文件
        jsonObj["destinationFilePath"] = path;

        jsonDoc.setObject(jsonObj);
        QFile writeFile(QDir::cleanPath(QCoreApplication::applicationDirPath() + QDir::separator() + QString("/configuration.json")));
        writeFile.open(QIODevice::WriteOnly | QIODevice::Truncate);

        QTextStream wirteStream(&writeFile);
        wirteStream.setCodec("UTF-8");		// 设置读取编码是UTF8
        wirteStream << jsonDoc.toJson();		// 写入文件
        writeFile.close();					// 关闭文件

        return true;
    }

    static bool moveFile(QString sSrcFile, QString sDestFile){
        // 判断目标文件的目录存不存在，不存在则创建
       QFileInfo fileInfo(sDestFile);
       QString sDirPath = fileInfo.absolutePath(); // 取目标文件所在的绝对目录路径

       // 如果文件存在，允许覆盖，则删除目标路径文件
       QFile sTempFile(sDestFile);
       if(sTempFile.exists()) {
        sTempFile.remove();
       }

       // 移动文件
       QFile file(sSrcFile);
       return file.rename(sDestFile);
    }

    static bool copyDir(QString sSrcDir, QString sDestDir)
    {
        // 是否传入了空的路径||源文件夹是否存在
        if (sSrcDir.isEmpty() || sDestDir.isEmpty() || !QDir().exists(sSrcDir))
            return false;

        QDir sourceDir(sSrcDir);
        QDir destDir(sDestDir);

        QFileInfoList fileInfoList = sourceDir.entryInfoList();
        foreach(QFileInfo fileInfo, fileInfoList) {
            if(fileInfo.fileName() == "." || fileInfo.fileName() == "..")
                continue;

            // 当为目录时，递归的进行copy
            if(fileInfo.isDir()) {
                if(!copyDir(fileInfo.filePath(), destDir.filePath(fileInfo.fileName())))
                    return false;
            }
            else {
                // 当允许覆盖操作时，将旧文件进行删除操作
                if(destDir.exists(fileInfo.fileName())){
                    destDir.remove(fileInfo.fileName());
                }

                // 进行文件copy
                if(!QFile::copy(fileInfo.filePath(), destDir.filePath(fileInfo.fileName()))){
                        return false;
                }
            }
        }

        return true;
    }
};
#endif // CONFIGMANAGER_H
