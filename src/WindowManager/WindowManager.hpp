#ifndef WINDOW_MANAGER_HPP
#define WINDOW_MANAGER_HPP

namespace WindowManager
{
    class WindowManager
    {
    public:
        WindowManager();
        ~WindowManager();

        int showDialogAndAwaitResponse();
    };
}

#endif // WINDOW_MANAGER_HPP