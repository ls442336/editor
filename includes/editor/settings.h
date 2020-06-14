#ifndef __SETTINGS__H__
#define __SETTINGS__H__

class Settings {
private:
public:
    int width;
    int height;

    int fontSize;

    void updateWindowSize(int width, int height);
};

#endif  //!__SETTINGS__H__