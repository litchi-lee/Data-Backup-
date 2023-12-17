/**
 * Project 软工实验
 */


#ifndef UNPACK_H
#define UNPACK_H
#include <QDirIterator>
#include <QFileInfo>
#include <QDebug>

// 负责将tar文件解包为文件和目录树。
class Unpack {
  public:
    /*
     * tar压缩包打开失败返回1
     * 写目标文件失败返回2
     * 创建目录失败返回3
     * 正常返回0
     */
    static int unpack(QString tarFilename, QString destination) {
        QFile tar(tarFilename);
        bool success = tar.open(QFile::ReadOnly);
        if (!success) return 1; // 打包文件打开失败
        
        int pathLength;
        int dir;
        int fileLength;
        QString relativePath;
        while (tar.read((char*)&pathLength, sizeof (pathLength))) {
            char* _relativePath = new char[pathLength + 1];
            tar.read(_relativePath, pathLength);
            _relativePath[pathLength] = '\0';
            relativePath = QString::fromStdString(std::string(_relativePath));
            delete[] _relativePath;
            qDebug() << relativePath;
            tar.read((char*)&dir, sizeof (dir));
            tar.read((char*)&fileLength, sizeof (fileLength));
            qDebug() << fileLength;
            if (!dir) {
                QFile data(destination + "/" + relativePath);
                bool success = data.open(QFile::WriteOnly);
                if (!success) return 2;
                if (fileLength) {
                    char* content = new char[fileLength];
                    tar.read(content, fileLength);
                    data.write(content, fileLength);
                    delete[] content;
                } else {
                    data.write("");
                }
                data.close();
            } else {
                QDir dir;
                if (QFileInfo(destination + "/" + relativePath).exists()) continue;
                bool success = dir.mkdir(destination + "/" + relativePath);
                if (!success) return 3;
            }
        }
        return 0;
    }
};

#endif // UNPACK_H