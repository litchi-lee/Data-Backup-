#ifndef COMPRESSOR_H_INCLUDED
#define COMPRESSOR_H_INCLUDED

#include <iostream>
#include <fstream>
#include <map>
#include <queue>
#include <vector>
#include <bitset>
#include <QFileInfo>
#include <QDebug>
#include "md5.h"

#ifndef ull
#define ull unsigned long long
#endif

using namespace std;

// 负责将tar文件使用哈夫曼编码算法压缩为bak文件，同时使用md5算法进行加密。

/**
 * 哈夫曼编码构建主要思路：
 * 给定一个字符集合，统计字符出现的频率，并按照频率从小到大排序。
 * 取出频率最小的两个字符，将它们作为叶子节点构建一棵二叉树（可以使用任意一种二叉树表示方式，比如孩子兄弟表示法）。
 * 以该二叉树为基础，再次取出频率最小的两个字符，将它们添加到这棵二叉树中（作为兄弟或者作为父节点的左右孩子），得到一棵较大的二叉树。
 * 重复上述步骤，直到所有字符都被添加到二叉树中。
 * 此时，生成的二叉树即为哈夫曼树。
 * 根据哈夫曼树的构建规则，左子树代表频率较小的字符，右子树代表频率较大的字符。
 * 对于每一个叶子节点，记录其路径所代表的二进制编码即为该字符的哈夫曼编码。
 *
**/

/**
 * 压缩算法实现主要思路：
 * 首先一个字符一个字符的读取待压缩文件，统计字符的种数以及字符出现的频度。
 * 为了解压缩时重构哈夫曼树，所以此时要将字符的出现的字符种数、字符以及相应的频度写入待压缩文件。
 * 然后根据字符以及字符频度创建哈夫曼树，进行哈夫曼编码。
 * 然后以二进制的方式一个一个字节地遍历待压缩文件，匹配每个字节对应的哈夫曼编码。
 * 每8位进行一次异或加密。
 */

class Compressor {
    // 用于记录字符和哈夫曼编码对应关系的map
    map<unsigned char, string> codeMap;

    // 二叉树结点
    struct haffNode {
        ull freq; // 频率
        unsigned char uchar; // 原字符
        string code; // 编码
        struct haffNode* left = 0; // 左子树
        struct haffNode* right = 0; // 右子树
    };

    struct cmp {
        bool operator ()(const haffNode* a, const haffNode* b) {
            return a->freq > b->freq;
        }
    };

    // 根据当前结点及当前编码递归构建哈夫曼树
    void encode(haffNode* pn, string code) {
        pn->code = code;
        if (pn->left) encode(pn->left, code + "0");
        if (pn->right) encode(pn->right, code + "1");
        if (!pn->left && !pn->right) {
            // 叶节点加入codeMap
            codeMap[pn->uchar] = code;
        }
    }

  public:
    /** 返回值说明：
    0：正常执行
    3：源文件扩展名不是tar
    4：打开源文件失败
    5：打开目标文件失败
    **/
    int compress(string sourcePath, string destinationPath, string pw = "") {
        codeMap.clear();
        if (sourcePath.substr(sourcePath.find_last_of(".") + 1) != "tar")
            return 3; // 源文件扩展名不是tar

        ifstream inFile;
        // 以二进制以及读模式打开sourcePath
        inFile.open(sourcePath, ios::in | ios::binary);
        if (!inFile)
            return 4; // 打开源文件失败

        ofstream outFile;
        sourcePath = QFileInfo(QString::fromStdString(sourcePath)).fileName().toStdString();
        string newFileName = destinationPath + sourcePath.substr(0, sourcePath.find_last_of(".")) + ".bak";
        // 以二进制以及写模式打开newFileName
        outFile.open(newFileName, ios::out | ios::binary);
        if (!outFile) {
            inFile.close();
            return 5; // 打开目标文件失败
        }

        /**
         * 1.统计词频
        **/
        unsigned char uchar;
        map<unsigned char, ull> freqMap;
        while (inFile.read((char*)&uchar, sizeof(char))) {
            freqMap[uchar]++;
        }

        /**
         * 2.建立词频小顶堆
        **/
        priority_queue<haffNode*, vector<haffNode*>, cmp> freqHeap;
        map<unsigned char, ull>::reverse_iterator it;
        for (it = freqMap.rbegin(); it != freqMap.rend(); it++) {
            haffNode* pn = new (haffNode);
            pn->freq = it->second;
            pn->uchar = it->first;
            pn->left = pn->right = 0;
            freqHeap.push(pn);
        }

        /**
         * 3.构建哈夫曼树
        **/
        while (freqHeap.size() > 1) {
            // 得到最小频率的两个结点
            haffNode* pn1 = freqHeap.top();
            freqHeap.pop();
            haffNode* pn2 = freqHeap.top();
            freqHeap.pop();

            haffNode* pn = new (haffNode);
            pn->freq = pn1->freq + pn2->freq;
            pn->left = pn1;
            pn->right = pn2;
            freqHeap.push(pn);
        }
        haffNode* root = freqHeap.top();
        codeMap.clear();

        /**
         * 4.用哈夫曼树编码
        **/
        encode(root, "");

        /**
         * 5.写入压缩文件头部：补零数+密码标志（暂时留空）
        **/
        const unsigned char zeroUC = 0;
        outFile.write((char*)&zeroUC, sizeof(zeroUC));

        /**
         * 6.写入压缩文件头部：密码
        **/
        int pw_len = pw.length();
        if (pw_len) {
            string pwMD5 = MD5().getMD5(pw).c_str();
            outFile << pwMD5;
        }

        /**
         * 7.写入压缩文件头部：频率表
        **/
        const ull zeroULL = 0;
        for (int i = 0; i < 256; i++) {
            if (freqMap.count(i) == 0) {
                // 没有i这个字符
                outFile.write((char*)&zeroULL, sizeof(zeroULL));
            } else {
                ull freq = freqMap[i];
                outFile.write((char*)&freq, sizeof(freq));
            }
        }

        /**
         * 8.写入压缩文件主体（加密），最后补上补零数+密码标志字段
        **/
        {
            int pw_index = 0;
            inFile.clear();
            inFile.seekg(0);
            string buf;
            unsigned char uchar;
            while (inFile.read((char*)&uchar, sizeof(uchar))) {
                // 根据codeMap将原tar文件内容压缩
                buf += codeMap[uchar];
                // 每到8位就加密一次
                while (buf.length() >= 8) {
                    bitset<8> bs(buf.substr(0, 8));
                    uchar = bs.to_ulong();
                    // 加密
                    if (pw_len) {
                        uchar ^= pw[pw_index++];
                        pw_index %= pw_len;
                    }
                    outFile.write((char*)&uchar, sizeof(uchar));
                    buf = buf.substr(8);
                }
            }
            // 末尾处理
            int zeroNum = (8 - buf.length()) % 8;
            if (zeroNum) {
                for (int i = 0; i < zeroNum; i++) {
                    buf += "0";
                }
                bitset<8> bs(buf.substr(0, 8));
                uchar = bs.to_ulong();
                if (pw_len) {
                    uchar ^= pw[pw_index++];
                    pw_index %= pw_len;
                }
                outFile.write((char*)&uchar, sizeof(uchar));
            }

            /**
             * 9.写入头部预留的补零数+密码标志字段
            **/
            outFile.clear();
            outFile.seekp(0);
            if (pw_len) {
                zeroNum += 8;
            }
            uchar = zeroNum;
            outFile.write((char*)&uchar, sizeof(uchar));
        }

        inFile.close();
        outFile.close();
        return 0; // 正常执行
    }
};
#endif // COMPRESSOR_H_INCLUDED

