cmake_minimum_required(VERSION 3.5)
project(Cripto)

set(CMAKE_C_STANDARD 99)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -pthread --std=c99 -pedantic -pedantic-errors -Wall -Wextra -Werror -Wno-unused-parameter -D_POSIX_C_SOURCE=200112L -O0 -fsanitize=address")
#agregar sanidad
#set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -pthread --std=c99 -pedantic -pedantic-errors -Wall -Wextra -Werror -Wno-unused-parameter -D_POSIX_C_SOURCE=200112L -O0")


#####################################################################
#find_package (sqlite3 REQUIRED)
#include_directories(${SQLITE3_INCLUDE_DIRS})

aux_source_directory(src COMMON_SOURCE_FILES)
#aux_source_directory(src/client CLIENT_SOURCE_FILES)
#aux_source_directory(src/server SERVER_SOURCE_FILES)
#aux_source_directory(src/database DB_SOURCE_FILES)


add_executable(cripto  ${COMMON_SOURCE_FILES} src/arguments.c src/general.h src/file_manager.c src/random.h src/utilities.h)
#target_link_libraries(database ${SQLITE3_LIBRARIES})
#####################################################################
