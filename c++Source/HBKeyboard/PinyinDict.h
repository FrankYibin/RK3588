#ifndef PINYINDICT_H
#define PINYINDICT_H

#include <QObject>
#include <QHash>
#include <QStringList>

class PinyinDict : public QObject
{
    Q_OBJECT
public:
    explicit PinyinDict(QObject *parent = nullptr);
    Q_INVOKABLE QStringList getCandidates(const QString &pinyin) const;
    bool loadFromFile(const QString &filePath);
private:
    QHash<QString, QStringList> m_dict;
};

#endif // PINYINDICT_H
