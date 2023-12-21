#ifndef UNPACK_H
#define UNPACK_H
#include <QDirIterator>
#include <QFileInfo>

// 负责将tar文件解包为文件和目录树。
class Unpack {
  public:
    /*
     * tar打开失败返回1
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
        while (tar.read((char*)&pathLength, sizeof (pathLength)))
        {
            char* _relativePath = new char[pathLength + 1];
            tar.read(_relativePath, pathLength); // 读入该文件/目录相对路径
            _relativePath[pathLength] = '\0'; // 结尾补结束符
            relativePath = QString::fromStdString(std::string(_relativePath));
            delete[] _relativePath;

            tar.read((char*)&dir, sizeof (dir)); // 读入dir，判断该路径是文件还是目录
            tar.read((char*)&fileLength, sizeof (fileLength)); // 读入该文件的大小

            if (!dir)
            { // 文件
                QFile data(destination + "/" + relativePath); // 存入的绝对目的路径
                bool success = data.open(QFile::WriteOnly);
                if (!success) return 2; // 文件打开失败
                if (fileLength) {
                    char* content = new char[fileLength];
                    tar.read(content, fileLength);
                    data.write(content, fileLength); // 写入文件内容
                    delete[] content;
                } else { // 文件为空
                    data.write("");
                }
                data.close();
            }
            else
            { // 目录
                QDir dir;
                if (QFileInfo(destination + "/" + relativePath).exists()) continue; // 目录已存在，则无需再次创建
                bool success = dir.mkdir(destination + "/" + relativePath); // 目录创建成功
                if (!success) return 3; // 创建目录失败
            }
        }
        return 0;
    }
};

#endif // UNPACK_H

