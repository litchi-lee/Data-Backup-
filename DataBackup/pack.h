#ifndef PACK_H
#define PACK_H
#include <QDirIterator>
#include <QFileInfo>

// 负责将文件和目录树打包为tar文件。
class Pack {
  public:
    /*
     * destination 打开失败返回1
     * files 中的文件打开失败返回2
     * 正常返回0
     */
    static int pack(QStringList files, QString destination) {
        QFile tar(destination);
        bool success = tar.open(QFile::WriteOnly);
        if (!success) return 1; // 目的路径打开失败

        for (auto& file : files) {

            if (QFileInfo(file).isFile())
            { // 文件
                auto root = QFileInfo(file).path();
                auto relativePath = QString(file).replace(root, ""); // 得到其相对地址
                int pathLength = relativePath.length();
                tar.write((const char*)&pathLength, sizeof (pathLength)); // 写入相对路径的长度
                tar.write(relativePath.toStdString().c_str()); // 写入相对路径
                int fileLength = QFileInfo(file).size();
                int dir = 0;
                tar.write((const char*)&dir, sizeof (dir)); // 不是目录，dir写入0
                tar.write((const char*)&fileLength, sizeof (fileLength)); // 写入文件大小
                QFile data(file);
                bool success = data.open(QFile::ReadOnly);
                if (!success) return 2; // 打开文件失败
                tar.write(data.readAll()); // 写入文件
                data.close();
            }
            else
            { // 非文件
                QDirIterator iter(file, QDirIterator::Subdirectories);
                while (iter.hasNext()) { // 迭代遍历该路径下所有文件及目录
                    iter.next();
                    QFileInfo info = iter.fileInfo();

                    if (info.fileName() == "..") continue;

                    if (info.isDir())
                    { // 为目录
                        auto root = QFileInfo(file).path();
                        auto relativePath = QString(info.absoluteFilePath()).replace(root, ""); // 该目录相对路径
                        int pathLength = relativePath.length(); // 相对路径长度
                        tar.write((const char*)&pathLength, sizeof (pathLength)); // 写入相对路径长度
                        tar.write(relativePath.toStdString().c_str()); // 写入相对路径
                        int fileLength = 0;
                        int dir = 1;
                        tar.write((const char*)&dir, sizeof (dir)); // 是目录，dir写入1
                        tar.write((const char*)&fileLength, sizeof (fileLength)); // 是目录，文件长度直接填0
                    }
                    else
                    { // 文件，同第一步
                        auto root = QFileInfo(file).path();
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

#endif // PACK_H
