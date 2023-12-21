#ifndef DECOMPRESSOR_H_INCLUDED
#define DECOMPRESSOR_H_INCLUDED

#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <bitset>
#include <cstring>
#include <queue>
#include <QFileInfo>
#include <QDebug>
#include "md5.h"

#ifndef ull
#define ull unsigned long long
#endif // ull

using namespace std;

// 负责将bak文件使用哈夫曼编码算法解压为tar文件，如果是加密的bak文件需要提供密码解密。

/**
 * 解压缩算法主要思路：
 * 首先从压缩文件种读取字符以及字符频度重构哈弗曼树，然后读取文件长度并记录。
 * 然后一个字节一个字节地遍历压缩文件之后的字符，先进行解密操作；
 * 然后从根节点出发，并且对每个字节的每一位通过位运算遍历：如果是1、移动到右孩子；如果是0、就移动到左孩子。
 * 只要判断移动到了叶子结点，就将叶子节点对应的字符写入到解压缩之后的文件中。
 **/

class Decompressor {
    // 用于记录字符和哈夫曼编码对应关系的map
    map<unsigned char, string> codeMap;

    // 二叉树结点
    struct haffNode {
        ull freq;
        unsigned char uchar;
        string code;
        struct haffNode* left = 0;
        struct haffNode* right = 0;
    };

    struct cmp {
        bool operator ()(const haffNode* a, const haffNode* b) {
            return a->freq > b->freq;
        }
    };

    // 构造哈夫曼树
    void insert_node(haffNode* father, unsigned char uchar, string code) {
        if (code.empty()) {
            father->uchar = uchar;
            return;
        }
        char way = code[0];
        if (way == '0') {
            // 找左孩子
            if (!(father->left)) {
                haffNode* son = new (haffNode);
                father->left = son;
            }
            insert_node(father->left, uchar, code.substr(1));
        } else {
            // 找右孩子
            if (!(father->right)) {
                haffNode* son = new (haffNode);
                father->right = son;
            }
            insert_node(father->right, uchar, code.substr(1));
        }
    }

  public:
    /** 返回值说明：
    0：正常执行
    1：源文件扩展名不是bak
    2：打开源文件失败
    3：打开目标文件失败
    4：文件过短，频率表不完整
    5：文件结尾不完整
    6：密码错误
    7：解码错误
    **/
    int decompress(string sourcePath, string destinationPath, string pw = "") {

        /**
         * 1.打开源文件
        **/
        if (sourcePath.substr(sourcePath.find_last_of(".") + 1) != "bak")
            return 1; // 源文件扩展名不是bak
        ifstream inFile;
        inFile.open(sourcePath, ios::in | ios::binary);
        if (!inFile)
            return 2; // 打开源文件失败

        /**
         * 2.密码校验
        **/
        unsigned char uchar;
        int pw_len = pw.length();
        inFile.read((char*)&uchar, sizeof(char));
        int zeroNum = uchar;
        if (zeroNum >= 8) {
            // 表示该文件加密过
            zeroNum -= 8;
            char crMD5_c[33];
            inFile.get(crMD5_c, 33);
            string crMD5 = string(crMD5_c, 32); // bak文件中保存的加密过的密码
            string pwMD5 = MD5().getMD5(pw); // 输入的密码经过加密后得到的code
            if (crMD5 != pwMD5) {
                inFile.close();
                return 6; // 密码错误
            }
        }

        /**
         * 3.打开目标文件
        **/
        ofstream outFile;
        sourcePath = QFileInfo(QString::fromStdString(sourcePath)).fileName().toStdString();
        string newFileName = destinationPath + sourcePath.substr(0, sourcePath.find_last_of(".")) + ".tar";
        outFile.open(newFileName, ios::out | ios::binary);
        if (!outFile) {
            inFile.close();
            return 3; // 打开目标文件失败
        }

        /**
         * 4.读出频率表
        **/
        ull freq;
        map<unsigned char, ull> freqMap;
        int i = 0;
        for (i = 0; i < 256; i++) {
            inFile.read((char*)&freq, sizeof(freq));
            if (freq) {
                freqMap[i] = freq;
            }
        }
        if (i != 256)
            return 4; // 文件过短，频率表不完整

        /**
         * 5.建立词频小顶堆
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
         * 6.构建哈夫曼树
        **/
        while (freqHeap.size() > 1) {
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
         * 7.读出主体，用哈夫曼树树解码
        **/
        haffNode* decodePointer = root;
        string buf, now;
        inFile.read((char*)&uchar, sizeof(unsigned char));
        int pw_index = 0;
        if (pw_len) {
            uchar ^= pw[pw_index++];
            pw_index %= pw_len;
        }
        bitset<8> bs = uchar;
        // 得到解密后的第一个字节
        buf = bs.to_string();
        while (inFile.read((char*)&uchar, sizeof(unsigned char))) {
            if (pw_len) {
                uchar ^= pw[pw_index++];
                pw_index %= pw_len;
            }
            bitset<8> bs = uchar;
            now = buf;
            buf = bs.to_string();
            // 对每一个字节遍历哈夫曼树进行解压缩
            for (char i = 0; i < 8; i++) {
                if (now[i] == '0') {
                    if (!decodePointer->left)
                        return 7; // 解码错误
                    decodePointer = decodePointer->left;
                } else {
                    if (!decodePointer->right)
                        return 7; // 解码错误
                    decodePointer = decodePointer->right;
                }
                if (!(decodePointer->left || decodePointer->right)) {
                    // 为叶子结点
                    outFile.write((char*) & (decodePointer->uchar), sizeof(decodePointer->uchar));
                    // 指针重新回到根节点
                    decodePointer = root;
                }
            }
        }
        //最后一字节要考虑之前补的0
        now = buf;
        for (char i = 0; i < (8 - zeroNum) % 8; i++) {
            if (now[i] == '0') {
                if (!decodePointer->left)
                    return 7; // 解码错误
                decodePointer = decodePointer->left;
            } else {
                if (!decodePointer->right)
                    return 7; // 解码错误
                decodePointer = decodePointer->right;
            }
            if (!(decodePointer->left || decodePointer->right)) {
                outFile.write((char*) & (decodePointer->uchar), sizeof(unsigned char));
                decodePointer = root;
            }
        }

        inFile.close();
        outFile.close();
        if (decodePointer == root) return 0; // 正常执行
        return 5; // 文件结尾不完整
    }
};
#endif // DECOMPRESSOR_H_INCLUDED
