#include "includes.h"

class GJHttpResult :  public cocos2d::CCNode {

public:
    bool success;
    std::string response;
    std::string tag;
    GJHttpType httptype;


    static GJHttpResult* create(bool success, std::string response, std::string tag, GJHttpType httptype);
    bool init(bool success, std::string response, std::string tag, GJHttpType httptype);
};

