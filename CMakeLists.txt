cmake_minimum_required(VERSION 3.19)
project(lmc LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets)

qt_standard_project_setup()

set(SOURCES src/main.cpp src/mainwindow.cpp src/lmc.cpp src/utils.cpp src/consoleio.cpp src/settingswindow.cpp src/aboutwindow.cpp)
set(HEADERS include/mainwindow.h include/lmc.h include/utils.h include/abstractio.h include/settingswindow.h include/aboutwindow.h)

qt_add_executable(lmc
    WIN32 MACOSX_BUNDLE
    ${SOURCES}
    ${HEADERS}
)

target_link_libraries(lmc
    PRIVATE
        Qt::Core
        Qt::Widgets
)

target_include_directories(${PROJECT_NAME} PUBLIC include)

include(GNUInstallDirs)

install(TARGETS lmc
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET lmc
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
