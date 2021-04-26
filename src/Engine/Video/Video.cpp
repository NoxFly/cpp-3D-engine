#include "Video.h"

#include <iostream>
#include <GL/glew.h>

#include "Video_driver.h"
#include "Console.h"

Video::Video():
    m_window(nullptr),
    m_clear_color{0, 0, 0, 1},
    m_tick(SDL_GetTicks())
{

}

Video::Video(unsigned int x, unsigned int y, unsigned int width, unsigned int height, std::string title, Uint32 flags):
    Video()
{
    createWindow(x, y, width, height, title, flags);
}

Video::Video(Window_props& properties, Uint32 flags):
    Video(properties.x, properties.y, properties.width, properties.height, properties.title, flags)
{
    
}

Video::~Video() {
    destroyWindow(true);
}

SDL_Window* Video::createWindow(unsigned int x, unsigned int y, unsigned int width, unsigned int height, std::string title, Uint32 flags) {
    if(m_window != nullptr) {
        Console::warn("Video::createWindow", "Window already created");
        return nullptr;
    }

    if(initSDL() < 0) {
        return nullptr;
    }

    flags |= VIDEO_OPENGL;

    m_window = SDL_CreateWindow(
        title.c_str(),
        (int)x,     (int)y,
        (int)width, (int)height,
        flags
    );

    if(m_window == nullptr) {
        Console::error("Video::createWindow", "SDL Window Creation (" + (std::string)SDL_GetError() + ")");
		SDL_Quit();
		return nullptr;
    }

    if(initGL() < 0) {
        return nullptr;
    }

    // disabled : can cause some troubles for some people
    //SDL_SetWindowInputFocus(m_window);

    return m_window;
}

int Video::initSDL() {
    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
		Console::error("Video::initSDL", "SDL Init (" + (std::string)SDL_GetError() + ")");
		SDL_Quit();
		return -1;
	}

    // OpenGL version
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, Video_driver::opengl_major_version);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, Video_driver::opengl_minor_version);

    // Double Buffer
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    return 0;
}

int Video::initGL() {
    m_oglContext = SDL_GL_CreateContext(m_window);

	if(m_oglContext == nullptr) {
		Console::error("Video::initGL", "OpenGL Context Creation (" + (std::string)SDL_GetError() + ")");
		destroyWindow(false);
		return -3;
	}

    glewExperimental = GL_TRUE;
    GLenum glew_init = glewInit();

    if(glew_init != GLEW_OK) {
        Console::error("Video::initGL", "Glew Init (" + (std::string)(char*)glewGetErrorString(glew_init) + ")");
        destroyWindow(true);
        return -4;
    }

    if(Video_driver::is_initialized && Video_driver::opengl_major_version < 2) {
        if(!GLEW_ARB_shader_objects) {
            Console::warn("Video::iniGL", "GLEW_ARB_shader_objects not available");
        }

        if(!GLEW_ARB_vertex_shader) {
            Console::warn(" Video::iniGL", "GLEW_ARB_vertex_shader not available");
        }

        if(!GLEW_ARB_fragment_shader) {
            Console::warn("Video::iniGL", "GLEW_ARB_fragment_shader not available");
        }
    }

	// Depth Buffer activation
	glEnable(GL_DEPTH_TEST);

    return 0;
}

void Video::close() {
    destroyWindow(true);
}

void Video::destroyWindow(bool destroyContext=false) {
    if(destroyContext && m_oglContext != nullptr) {
        SDL_GL_DeleteContext(m_oglContext);
    }

    if(m_window != nullptr) {
        SDL_DestroyWindow(m_window);
        SDL_Quit();
    }
}


Uint32 Video::id() const {
    return SDL_GetWindowID(m_window);
}

bool Video::hasWindow() const {
    return m_window != nullptr;
}

Window_props Video::getWindowProps() const {
    if(!hasWindow()) {
        return (Window_props){ 0, 0, 0, 0, "" };
    }

    int x, y, w, h;

    SDL_GetWindowSize(m_window, &w, &h);
    SDL_GetWindowPosition(m_window, &x, &y);
    const char* title = SDL_GetWindowTitle(m_window);

    return (Window_props){ x, y, w, h, title };
}

void Video::clear() {
    glClearColor(m_clear_color.r, m_clear_color.g, m_clear_color.b, m_clear_color.a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Video::display() {
    SDL_GL_SwapWindow(m_window);
}

void Video::updateTick(Uint32 fps) {
    Uint32 now = SDL_GetTicks();
    Uint32 delta = now - m_tick;

    if(delta < fps) {
        SDL_Delay(fps - delta);
    }

    m_tick = now - (delta % fps);
}