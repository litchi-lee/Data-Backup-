#ifndef BACKUP_H
#define BACKUP_H
#include <pack.h>
#include <compressor.h>
#include <QMessageBox>
#include <configManager.h>

class BackUp
{
    public:

    /**
     * @brief backup
     * @param files 待备份的文件列表
     * @param desTar .tar文件路径
     * @param isEncoded 是否加密
     * @param pw 用户输入的密码
     * @return 错误码
     * 0 备份成功
     * 1 tar文件的目标文件打开失败
     * 2 打开源文件失败
     * 3 源文件扩展名不是bak
     * 4 打开tar源文件失败
     * 5 打开目标文件失败
     */
    static int backup(QStringList files, QString desTar, bool isEncoded, string pw){
        // 打包
        int errorCode = Pack::pack(files, desTar);
        if (errorCode) {
            return errorCode;
        }

        // 加密并压缩
        Compressor compressor;
        errorCode = compressor.compress(desTar.toStdString(), ConfigManager::getDesPath().toStdString() + "\\", isEncoded ? pw : "");
        qDebug() << (ConfigManager::getDesPath() + "\\");
        if (errorCode) {
            return errorCode;
        }

        QFile tarFile(desTar);
        tarFile.remove();
        return errorCode;
    }
};

#endif // BACKUP_H
