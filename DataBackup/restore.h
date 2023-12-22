#ifndef RESTORE_H
#define RESTORE_H
#include <unpack.h>
#include <Decompressor.h>

class Restore {
    public:

    /**
     * @brief restore
     * @param srcPath .bak文件路径
     * @param desPath 恢复目标路径
     * @param isEncoded 是否加密
     * @param pw 秘钥
     * @return 错误码
     * 0：正常执行
     * 1：源文件扩展名不是bak
     * 2：打开.bak源文件失败
     * 3：打开目标路径失败
     * 4：.bak文件过短，频率表不完整，解压失败
     * 5：.bak文件结尾不完整，解压失败
     * 6：密码错误
     * 7：解码错误
     * 8：.tar文件打开失败
     * 9：打开目标路径失败
     * 10：创建目录失败
     */
    static int restore(QString srcPath, QString desPath, bool isEncoded, QString pw){
        Decompressor decompressor;
        int errorCode = decompressor.decompress(srcPath.toStdString(), desPath.toStdString() + "\\", isEncoded ? pw.toStdString() : "");
        if (errorCode) {
            return errorCode;
        }

        QString tempFilename = desPath + "/" + QFileInfo(srcPath).fileName();
        tempFilename = tempFilename.left(tempFilename.length() - 3) + "tar";
        errorCode = Unpack::unpack(tempFilename, desPath);
        if (errorCode) {
            return errorCode;
        }

        QFile tarFile(tempFilename);
        tarFile.remove();

        return errorCode;
    }
};

#endif // RESTORE_H
