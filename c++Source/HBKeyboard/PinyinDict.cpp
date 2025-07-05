#include "PinyinDict.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>

PinyinDict::PinyinDict(QObject *parent) : QObject(parent) {
    // 默认加载 ChinesePinyin 文件
    loadFromFile(":/ChinesePinyin");
}

bool PinyinDict::loadFromFile(const QString &filePath) {
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "No available Pinyin library";
        return false;
    }
    QTextStream in(&file);
    m_dict.clear();
    while (!in.atEnd()) {
        QString line = in.readLine().trimmed();
        if (line.isEmpty() || line.startsWith("#"))
            continue;
        // 找到第一个字母的位置
        int firstAlpha = -1;
        for (int i = 0; i < line.size(); ++i) {
            QChar ch = line[i];
            if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z')) {
                firstAlpha = i;
                break;
            }
        }
        if (firstAlpha > 0) {
            QString hanzi = line.left(firstAlpha);
            QString pinyin = line.mid(firstAlpha);
            QStringList hanziList;
            for (const QChar &c : hanzi)
                hanziList << QString(c);
            if (m_dict.contains(pinyin))
                m_dict[pinyin].append(hanziList);
            else
                m_dict.insert(pinyin, hanziList);
        }
    }
    return true;
}

QStringList PinyinDict::getCandidates(const QString &pinyin) const
{
    // qDebug() << "Size: " << m_dict.size();
    // QHash<QString, QStringList>::const_iterator iter = m_dict.constBegin();
    // while(iter != m_dict.constEnd())
    // {
    //     qDebug() << "pinyin: " << iter.key() << "hanzi: " << iter.value();
    //     iter++;
    // }
    return m_dict.value(pinyin);
}
