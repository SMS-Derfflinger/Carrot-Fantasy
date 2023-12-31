#include "AppDelegate.h"
#include "SceneMain.h"
#include "StartScene.h"

// #define USE_AUDIO_ENGINE 1
// #define USE_SIMPLE_AUDIO_ENGINE 1

#if USE_AUDIO_ENGINE && USE_SIMPLE_AUDIO_ENGINE
#error "Don't use AudioEngine and SimpleAudioEngine at the same time. Please just select one in your game!"
#endif

#if USE_AUDIO_ENGINE
#include "audio/include/AudioEngine.h"
using namespace cocos2d::experimental;
#elif USE_SIMPLE_AUDIO_ENGINE
#include "audio/include/SimpleAudioEngine.h"
using namespace CocosDenshion;
#endif

USING_NS_CC;

static cocos2d::Size designResolutionSize = cocos2d::Size(1300, 800);  // 设计分辨率大小为1300x800像素。

AppDelegate::AppDelegate()
{
}

// 根据不同的音频引擎选择，执行相应的资源释放操作
AppDelegate::~AppDelegate()
{
#if USE_AUDIO_ENGINE
    AudioEngine::end();
#elif USE_SIMPLE_AUDIO_ENGINE
    SimpleAudioEngine::end();
#endif
}

// 用于初始化OpenGL上下文属性
// if you want a different context, modify the value of glContextAttrs
// it will affect all platforms
void AppDelegate::initGLContextAttrs()
{
    // set OpenGL context attributes: red,green,blue,alpha,depth,stencil,multisamplesCount
    GLContextAttrs glContextAttrs = { 8, 8, 8, 8, 24, 8, 0 };

    GLView::setGLContextAttrs(glContextAttrs);
}

// 用于注册所有的扩展包
// if you want to use the package manager to install more packages,  
// don't modify or remove this function
static int register_all_packages()
{
    return 0; //flag for packages manager
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance(); //获取全局唯一的 Director 对象实例
    auto glview = director->getOpenGLView(); //获取 OpenGL 视图对象
    // 检查 OpenGL 视图对象是否存在
    // 如果不存在，则根据不同的平台创建一个新的 OpenGL 视图
    // 并将其设置为 Director 的 OpenGL 视图
    if (!glview) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
        glview = GLViewImpl::createWithRect("Scene1", cocos2d::Rect(0, 0, designResolutionSize.width, designResolutionSize.height));
#else
        glview = GLViewImpl::create("Scene1");
#endif
        director->setOpenGLView(glview);
    }

    // 设置游戏运行时的帧率为 60 帧每秒
    director->setAnimationInterval(1.0f / 60);

    // 以固定高度为基准，自动计算宽度进行适配，可能会裁剪宽度上的部分内容。
    glview->setDesignResolutionSize(1300, 800, ResolutionPolicy::SHOW_ALL);

    // 注册所有支持的扩展包
    register_all_packages();

    // 创建一个场景对象，并将其设置为自动释放
    //auto scene = Scene1::createScene();

    auto startScene = StartScene::create();

    // run
    director->runWithScene(startScene);

    return true;
}

// This function will be called when the app is inactive. Note, when receiving a phone call it is invoked.
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation(); // 停止游戏的动画渲染

    // 选择相应的音频引擎来暂停音频播放
#if USE_AUDIO_ENGINE
    AudioEngine::pauseAll();
#elif USE_SIMPLE_AUDIO_ENGINE
    SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
    SimpleAudioEngine::getInstance()->pauseAllEffects();
#endif
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation(); // 开启游戏的动画渲染

    // 选择相应的音频引擎来恢复音频播放
#if USE_AUDIO_ENGINE
    AudioEngine::resumeAll();
#elif USE_SIMPLE_AUDIO_ENGINE
    SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
    SimpleAudioEngine::getInstance()->resumeAllEffects();
#endif
}
