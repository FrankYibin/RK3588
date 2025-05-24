#ifndef HBVOICE_H
#define HBVOICE_H

#include <QObject>
#include <QStringList>
#include <QMediaPlayer>

class HBVoice : public QObject
{
    Q_OBJECT
private:
    static QStringList m_VoiceList;
    static QMediaPlayer* m_ptrPlayer;
    static HBVoice* m_objVoice;
public:
    enum VOICE_EXCEPTION_INDEX
    {
        WELL_HEAD_EXCEPTION = 0,
        TARGET_CLOSE_EXCEPTION,
        EXCEED_VELOCITY_EXCEPTION,
        LOCKED_EXCEPTION,
        BLOCKED_EXCEPTION,
        TENSION_EXCEPTION,
        SURFACE_CLOSE_EXCEPTION,
        ENCODER_1_EXCEPTION,
        ENCODER_2_EXCEPTION
    };
public:
    explicit HBVoice(QObject *parent = nullptr);
    virtual ~HBVoice();
    static bool PlayVoice(VOICE_EXCEPTION_INDEX index);

signals:
};

#endif // HBVOICE_H
