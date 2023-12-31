LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := MyGame_shared

LOCAL_MODULE_FILENAME := libMyGame

LOCAL_SRC_FILES := $(LOCAL_PATH)/hellocpp/main.cpp \
                   $(LOCAL_PATH)/../../../Classes/AppDelegate.cpp \
                   $(LOCAL_PATH)/../../../Classes/HelloWorldScene.cpp \
                   $(LOCAL_PATH)/../../../Classes/TowerPosition.cpp \
                   $(LOCAL_PATH)/../../../Classes/TowerBase.cpp \
                   $(LOCAL_PATH)/../../../Classes/Tower.cpp \
                   $(LOCAL_PATH)/../../../Classes/Target.cpp \
                   $(LOCAL_PATH)/../../../Classes/ObstacleBase.cpp \
                   $(LOCAL_PATH)/../../../Classes/Obstacle.cpp \
                   $(LOCAL_PATH)/../../../Classes/MonsterBase.cpp \
                   $(LOCAL_PATH)/../../../Classes/Monster.cpp \
                   $(LOCAL_PATH)/../../../Classes/Carrot.cpp \
                   $(LOCAL_PATH)/../../../Classes/UpScene.cpp \
                   $(LOCAL_PATH)/../../../Classes/StartScene.cpp \
                   $(LOCAL_PATH)/../../../Classes/SceneMain.cpp \
                   $(LOCAL_PATH)/../../../Classes/SceneBase.cpp \
                   $(LOCAL_PATH)/../../../Classes/LevelScene.cpp \
                   $(LOCAL_PATH)/../../../Classes/GameScene.cpp \

                   $(LOCAL_PATH)/../../../Classes/AppDelegate.h \
                   $(LOCAL_PATH)/../../../Classes/HelloWorldScene.h \
                   $(LOCAL_PATH)/../../../Classes/TowerPosition.h \
                   $(LOCAL_PATH)/../../../Classes/TowerBase.h \
                   $(LOCAL_PATH)/../../../Classes/Tower.h \
                   $(LOCAL_PATH)/../../../Classes/Target.h \
                   $(LOCAL_PATH)/../../../Classes/ObstacleBase.h \
                   $(LOCAL_PATH)/../../../Classes/Obstacle.h \
                   $(LOCAL_PATH)/../../../Classes/MonsterBase.h \
                   $(LOCAL_PATH)/../../../Classes/Monster.h \
                   $(LOCAL_PATH)/../../../Classes/Carrot.h \
                   $(LOCAL_PATH)/../../../Classes/UpScene.h \
                   $(LOCAL_PATH)/../../../Classes/StartScene.h \
                   $(LOCAL_PATH)/../../../Classes/SceneMain.h \
                   $(LOCAL_PATH)/../../../Classes/SceneBase.h \
                   $(LOCAL_PATH)/../../../Classes/LevelScene.h \
                   $(LOCAL_PATH)/../../../Classes/GameScene.h \


LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../../Classes

# _COCOS_HEADER_ANDROID_BEGIN
# _COCOS_HEADER_ANDROID_END


LOCAL_STATIC_LIBRARIES := cc_static

# _COCOS_LIB_ANDROID_BEGIN
# _COCOS_LIB_ANDROID_END

include $(BUILD_SHARED_LIBRARY)

$(call import-module, cocos)

# _COCOS_LIB_IMPORT_ANDROID_BEGIN
# _COCOS_LIB_IMPORT_ANDROID_END
