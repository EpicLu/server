project(server)

# 配置构建类型
#set(CMAKE_BUILD_TYPE Release)
set(CMAKE_BUILD_TYPE Debug)

# 设置二进制文件目录 默认为当前目录的build -> ./build
# SET(PROJECT_BINARY_DIR ../)
# 设置静态库文件目录
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib)
# 设置动态库文件目录
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib)
# 设置可执行文件目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)
# 设置可执行文件名
set(TARGET server)
# 设置库名
set(PROJECT_LINK_LIBS threadpool event)

# 设置头文件目录
include_directories(include)

# 设置源文件目录 使用GLOB可使用wilecard来获取源文件
file(GLOB THREADPOOL_SOURCES "src/threadpool*.c")
file(GLOB EVENT_SOURCES "src/event*.c")

# 制作动态库
add_library(threadpool SHARED ${THREADPOOL_SOURCES})
SET_TARGET_PROPERTIES(threadpool PROPERTIES VERSION 1.0 SOVERSION 1) # 设置动态库版本
add_library(event SHARED ${EVENT_SOURCES})
SET_TARGET_PROPERTIES(event PROPERTIES VERSION 1.0 SOVERSION 1)

# 制作静态库 如果动态库已经使用过的名字静态库不能在add_library中使用 可用设置版本指令修改名字
add_library(threadpool_static STATIC ${THREADPOOL_SOURCES})
SET_TARGET_PROPERTIES(threadpool_static PROPERTIES OUTPUT_NAME threadpool) # 同下理
add_library(event_static STATIC ${EVENT_SOURCES})
SET_TARGET_PROPERTIES(event_static PROPERTIES OUTPUT_NAME event) # 静态库改名 输出libevent.a

message(${PROJECT_LINK_LIBS})

add_executable(${TARGET} src/main.c src/process.c)	# add_executable用于生成执行文件的地方
 
# 生成可执行文件main，需要把连接库给带上，添加库文件名不需要指定文件路径，cmake会自己找
target_link_libraries(server ${PROJECT_LINK_LIBS}) 

#set the location for library installation --i.e.
#/usr/lib in this case
#not really necessary in this example, use "sudo make install" to apply
#install(TARGETS testStudent DESTINATION /usr/lib)