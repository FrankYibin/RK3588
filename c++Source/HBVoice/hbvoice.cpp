#include "hbvoice.h"
#include <QAudioOutput>
#include <QStandardPaths>
#include <QFile>
QStringList HBVoice::m_VoiceList;
QMediaPlayer* HBVoice::m_ptrPlayer = nullptr;
HBVoice* HBVoice::m_objVoice = nullptr;
HBVoice::HBVoice(QObject *parent)
    : QObject{parent}
{
    m_VoiceList.clear();
    m_VoiceList.append(":/voice/00Well.mp3");
    m_VoiceList.append(":/voice/01Target.mp3");
    m_VoiceList.append(":/voice/02Velocity.mp3");
    m_VoiceList.append(":/voice/03Locked.mp3");
    m_VoiceList.append(":/voice/04Blocked.mp3");
    m_VoiceList.append(":/voice/05Tension.mp3");
    m_VoiceList.append(":/voice/06Surface.mp3");
    m_VoiceList.append(":/voice/07Encoder1.mp3");
    m_VoiceList.append(":/voice/08Encoder2.mp3");
    m_VoiceList.append(":/voice/09Encoder3.mp3");
    m_VoiceList.append(":/voice/10Drowsy.mp3");
    m_VoiceList.append(":/voice/20meter0_0.mp3");
    m_VoiceList.append(":/voice/11meter0_1.mp3");
    m_VoiceList.append(":/voice/12meter0_2.mp3");
    m_VoiceList.append(":/voice/13meter0_3.mp3");
    m_VoiceList.append(":/voice/14meter0_4.mp3");
    m_VoiceList.append(":/voice/15meter0_5.mp3");
    m_VoiceList.append(":/voice/16meter0_6.mp3");
    m_VoiceList.append(":/voice/17meter0_7.mp3");
    m_VoiceList.append(":/voice/18meter0_8.mp3");
    m_VoiceList.append(":/voice/19meter0_9.mp3");
    m_VoiceList.append(":/voice/30meter1_0.mp3");
    m_VoiceList.append(":/voice/21meter1_1.mp3");
    m_VoiceList.append(":/voice/22meter1_2.mp3");
    m_VoiceList.append(":/voice/23meter1_3.mp3");
    m_VoiceList.append(":/voice/24meter1_4.mp3");
    m_VoiceList.append(":/voice/25meter1_5.mp3");
    m_VoiceList.append(":/voice/26meter1_6.mp3");
    m_VoiceList.append(":/voice/27meter1_7.mp3");
    m_VoiceList.append(":/voice/28meter1_8.mp3");
    m_VoiceList.append(":/voice/29meter1_9.mp3");
    m_VoiceList.append(":/voice/31meter2_0.mp3");


    m_ptrPlayer = new QMediaPlayer;
    m_ptrPlayer->setVolume(100);
    m_objVoice = this;
}

HBVoice::~HBVoice()
{
    m_ptrPlayer->deleteLater();
}

HBVoice *HBVoice::GetInstance()
{
    if (m_objVoice == nullptr)
        m_objVoice = new HBVoice();
    return m_objVoice;
}

bool HBVoice::PlayVoice(HBVoice::VOICE_EXCEPTION_INDEX index)
{
    bool bResult = false;
    if(m_objVoice == nullptr)
        return false;
    if(m_VoiceList.size() == 0)
        return false;
    if(m_ptrPlayer->state() == QMediaPlayer::StoppedState)
    {
        QString resourcePath = m_VoiceList.at(index);
        QStringList tmpList = resourcePath.split("/");
        for(int i = 0; i < tmpList.size(); i++)
        {
            qDebug() << "tmp: " << tmpList.at(i);
        }
        QString tempPath = QStandardPaths::writableLocation(QStandardPaths::TempLocation) + + "/" + tmpList.at(2);
        if (!QFile::exists(tempPath)) {
            QFile::copy(resourcePath, tempPath);
        }
        m_ptrPlayer->setMedia(QUrl::fromLocalFile(tempPath));
        m_ptrPlayer->play();
        bResult = true;
    }
    return bResult;
}
