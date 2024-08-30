#ifndef SETTING_H
#define SETTING_H

#define SETTING_FILE_NAME "danmu.setting"

#define KEY_POS_X  "POS_X"
#define KEY_POS_Y  "POS_Y"
#define KEY_WIDTH  "WIDTH"
#define KEY_HEIGHT "HEIGHT"
#define KEY_URL    "URL"
#define KEY_STYLE  "STYLE"

#include <string>
#include <map>

class Setting
{
public:
    Setting();
    const std::string get(const std::string& key);
    void put(const std::string& key, const std::string& value);
    void store();
    bool isEmpty() const;
private:
    std::map<std::string, std::string> keyValues;
};

#endif // SETTING_H
