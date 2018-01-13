// VoiceMail interface

#include <string>

class VoiceMail
{
public:
    void record(std::string msg);
    void erase();
    void playback() const;
private:
    std::string m_message;
};
