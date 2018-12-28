#ifndef DICTIONARY_H
#define DICTIONARY_H

// 词典Dictionary模板类
template <typename K, typename V> struct Dictionary {
    virtual int size() const = 0;   // 当前词条总数
    virtual bool put(K, V) = 0;     // 插入词条（禁止雷同词条时可能失败）
    virtual V* get(K k) = 0;        // 读取词条
    virtual bool remove(K k) = 0;   // 删除词条
};

#endif // DICTIONARY_H
