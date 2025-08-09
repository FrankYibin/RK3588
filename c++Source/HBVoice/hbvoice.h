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
        ENCODER_2_EXCEPTION,
        ENCODER_3_EXCEPTION,
        DROWSY_DRIVING,
        METER_0_0,
        METER_0_1,
        METER_0_2,
        METER_0_3,
        METER_0_4,
        METER_0_5,
        METER_0_6,
        METER_0_7,
        METER_0_8,
        METER_0_9,
        METER_1_0,
        METER_1_1,
        METER_1_2,
        METER_1_3,
        METER_1_4,
        METER_1_5,
        METER_1_6,
        METER_1_7,
        METER_1_8,
        METER_1_9,
        METER_2_0
    };
public:
    static HBVoice* GetInstance();
    static bool PlayVoice(VOICE_EXCEPTION_INDEX index);

private:
    explicit HBVoice(QObject *parent = nullptr);
    virtual ~HBVoice();

signals:
};

#endif // HBVOICE_H
