cmake_minimum_required(VERSION 3.5.0)

if(NOT DEFINED CMAKE_TOOLCHAIN_FILE)
  if(DEFINED ENV{VITASDK})
    set(CMAKE_TOOLCHAIN_FILE "$ENV{VITASDK}/share/vita.toolchain.cmake" CACHE PATH "toolchain file")
  else()
    message(FATAL_ERROR "Please define VITASDK to point to your SDK path!")
  endif()
endif()


set(PROJECT_VERSION "0.0.0")
set(PROJECT_NAME "SDL_Test")
project(${PROJECT_NAME} VERSION ${PROJECT_VERSION} LANGUAGES CXX)

set(VITA_APP_NAME "Bruh moment #3")
set(VITA_TITLEID "BRUH00003")
set(VITA_VERSION "00.00")

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -g")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g -pthread")
add_definitions(-D__VITA)
include("${VITASDK}/share/vita.cmake" REQUIRED)
set(SDL2_DIR "/usr/local/vitasdk/arm-vita-eabi/lib/cmake/SDL2/")
find_package("SDL2" CONFIG REQUIRED)
add_executable(${PROJECT_NAME}
    src/main.cpp
    src/menu.cpp
    src/util.cpp
    src/level.cpp
)

target_link_libraries(${PROJECT_NAME}
  SDL2_ttf
  freetype
  bz2
  SDL2_image
  png
  z
  SDL2::SDL2-static
  SceNet_stub
  SceSysmodule_stub
  SceLibKernel_stub
)

vita_create_self(eboot.bin ${PROJECT_NAME})

vita_create_vpk(${PROJECT_NAME}.vpk ${VITA_TITLEID} eboot.bin
    VERSION ${VITA_VERSION}
    NAME ${VITA_APP_NAME}
    FILE assets/png assets/png
    FILE assets/ttf assets/ttf
    )


set(PSVITAIP "192.168.1.146" CACHE STRING "PSVita IP (for FTP access)")

add_custom_target(send
                  COMMAND echo destroy | nc ${PSVITAIP} 1338
                  COMMAND curl -T eboot.bin ftp://${PSVITAIP}:1337/ux0:/app/${VITA_TITLEID}/
                  COMMAND echo launch ${VITA_TITLEID} | nc ${PSVITAIP} 1338
                  DEPENDS ${PROJECT_NAME}.vpk-vpk
                  )