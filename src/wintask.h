#if !defined(WINTASK_H)
#define WINTASK_H
#include <json.hpp>
using json = nlohmann::json;

class WinTask {
    private:
    json file;

    public:
    WinTask(json main): file(main) {}
    int RunTask(std::string task);
};


#endif // WINTASK_H
