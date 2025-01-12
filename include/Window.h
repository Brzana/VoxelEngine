#pragma once

#include "../include/OpenGl.h"
#include <string>

class Window {
public:
    Window();
    ~Window();

    bool init(int width, int height, const std::string& title);
    void shutdown();

    void pollEvents();
    void swapBuffers();

    bool shouldClose() const;

    int getWidth() const { return m_width; }
    int getHeight() const { return m_height; }

    GLFWwindow* getNativeWindow() const { return m_window; }

private:
    GLFWwindow* m_window;
    int m_width;
    int m_height;
};
