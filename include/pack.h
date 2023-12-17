/**
 * Project 软工实验
 */


#ifndef _PACK_H
#define _PACK_H
#include <QDirIterator>
#include <QFileInfo>
#include <QDebug>

// 负责将文件和目录树打包为tar文件。
class Pack {
  public:
    /*
     * destination(打包文件目的路径) 打开失败返回1
     * files（打包文件列表）中的文件打开失败返回2
     * 正常返回0
     */
    static int pack(QStringList files, QString destination) {
        QFile tar(destination);
        bool success = tar.open(QFile::WriteOnly);
        if (!success) return 1;// 目标路径打开失败

        auto root = QFileInfo(files[0]).path();
        // 遍历需要打包的文件列表中的每一份文件
        for (auto& file : files) {
            if (QFileInfo(file).isFile()) { // 该路径是文件类型
                auto relativePath = QString(file).replace(root, "");
                int pathLength = relativePath.length();
                tar.write((const char*)&pathLength, sizeof (pathLength));
                tar.write(relativePath.toStdString().c_str());
                int fileLength = QFileInfo(file).size();
                int dir = 0;
                tar.write((const char*)&dir, sizeof (dir));
                tar.write((const char*)&fileLength, sizeof (fileLength));
                QFile data(file);
                bool success = data.open(QFile::ReadOnly);
                if (!success) return 2; // 文件打开失败
                tar.write(data.readAll());
                data.close();
            } else {
                QDirIterator iter(file, QDirIterator::Subdirectories);
                while (iter.hasNext()) {
                    iter.next();
                    QFileInfo info = iter.fileInfo();
                    if (info.fileName() == "..") continue;
                    if (info.isDir()) {
                        auto relativePath = QString(info.absoluteFilePath()).replace(root, "");
                        int pathLength = relativePath.length();
                        tar.write((const char*)&pathLength, sizeof (pathLength));
                        tar.write(relativePath.toStdString().c_str());
                        int fileLength = 0;
                        int dir = 1;
                        tar.write((const char*)&dir, sizeof (dir));
                        tar.write((const char*)&fileLength, sizeof (fileLength));
                    } else {
                        auto relativePath = QString(info.absoluteFilePath()).replace(root, "");
                        int pathLength = relativePath.length();
                        tar.write((const char*)&pathLength, sizeof (pathLength));
                        tar.write(relativePath.toStdString().c_str());
                        int fileLength = info.size();
                        int dir = 0;
                        tar.write((const char*)&dir, sizeof (dir));
                        tar.write((const char*)&fileLength, sizeof (fileLength));
                        QFile data(info.absoluteFilePath());
                        bool success = data.open(QFile::ReadOnly);
                        if (!success) return 2;
                        tar.write(data.readAll());
                        data.close();
                    }
                }
            }
        }
        tar.close();
        return 0;
    }
};

#endif //_PACK_H