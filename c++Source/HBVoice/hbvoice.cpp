#include "hbvoice.h"
QStringList HBVoice::m_VoiceList;
QMediaPlayer* HBVoice::m_ptrPlayer = nullptr;
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
}

HBVoice::~HBVoice()
{
    m_ptrPlayer->deleteLater();
}

bool HBVoice::PlayVoice(HBVoice::VOICE_EXCEPTION_INDEX index)
{
    m_ptrPlayer->setMedia(QUrl(m_VoiceList.at(index)));
    m_ptrPlayer->play();
}
