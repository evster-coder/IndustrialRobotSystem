QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ActivateExecutiveUnit.cpp \
    ControlSystem.cpp \
    DeactivateExecutiveUnit.cpp \
    DecSensorLight.cpp \
    DecSensorRadiation.cpp \
    DecSensorTemperature.cpp \
    DecSensorWet.cpp \
    DecoratorSensorUnit.cpp \
    Detail.cpp \
    EUnitHandCreator.cpp \
    EUnitSprayCreator.cpp \
    ExecutiveUnitHand.cpp \
    ExecutiveUnitSpray.cpp \
    FacadeSystem.cpp \
    MoveMovingUnit.cpp \
    MovingUnit.cpp \
    Robot.cpp \
    RobotSystem.cpp \
    ScanSensorUnit.cpp \
    SensorUnit.cpp \
    SetPressureSensor.cpp \
    dialogaddrobot.cpp \
    main.cpp \
    mainwindowapp.cpp

HEADERS += \
    ActivateExecutiveUnit.h \
    ControlSystem.h \
    DeactivateExecutiveUnit.h \
    DecSensorLight.h \
    DecSensorRadiation.h \
    DecSensorTemperature.h \
    DecSensorWet.h \
    DecoratorSensorUnit.h \
    Detail.h \
    EUnitCreator.h \
    EUnitHandCreator.h \
    EUnitSprayCreator.h \
    ExecutiveUnit.h \
    ExecutiveUnitHand.h \
    ExecutiveUnitSpray.h \
    FacadeSystem.h \
    IRobot.h \
    ISensorUnit.h \
    MoveMovingUnit.h \
    MovingUnit.h \
    ProgramUnit.h \
    Robot.h \
    RobotSystem.h \
    ScanSensorUnit.h \
    SensorUnit.h \
    SetPressureSensor.h \
    dialogaddrobot.h \
    mainwindowapp.h

FORMS += \
    dialogaddrobot.ui \
    mainwindowapp.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
