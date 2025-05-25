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
    m_ptrPlayer = new QMediaPlayer;
    m_ptrPlayer->setVolume(100);
    m_objVoice = this;
}

HBVoice::~HBVoice()
{
    m_ptrPlayer->deleteLater();
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
