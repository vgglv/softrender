cmake_minimum_required(VERSION 3.24)
project(softrender)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

#TODO: move this to if (APPLE) or some shit
add_executable(${PROJECT_NAME} src/platform/osx/main.mm)

file(GLOB_RECURSE SOURCES 
	"src/common/*.*"
	"src/core/*.*"
	"src/render/*.*"
	"src/state/*.*"
)

target_sources(${PROJECT_NAME} PRIVATE ${SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE "src/")

target_link_libraries(${PROJECT_NAME}
	PUBLIC
		"-ObjC"
		"-framework Cocoa"
		"-framework AppKit"

#		"-framework CoreGraphics"
#		"-framework Foundation"
#		"-framework OpenGL"
#		"-framework AVFoundation"
#		"-framework StoreKit"
#		"-framework QuartzCore"
#		"-framework SystemConfiguration"
#		"-framework OpenAL"
#		"-framework WebKit"
#		"-framework IOKit"
#		"-framework CoreMedia"
#		"-framework AudioUnit"
#		"-framework CoreAudio"
#		"-framework CoreFoundation"
#		"-framework ApplicationServices"
#		"-framework CFNetwork"
#		"-framework GameKit"
#		"-framework AudioToolbox"
#		"-framework Foundation"
#		"-framework Security"
#		"-framework CoreVideo"
#		"-framework VideoDecodeAcceleration"
#		"-framework VideoToolBox"
	)
