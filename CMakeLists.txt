cmake_minimum_required(VERSION 3.16.3)
project(concordo)
include_directories(src)

add_executable(concordo src/main.cpp src/channel.cpp src/message.cpp src/server.cpp src/sistema.cpp src/textChannel.cpp src/user.cpp src/voiceChannel.cpp )
