file(GLOB sources
	"*.h"
	"*.cpp"
)

add_executable(LimitlessEngineCore WIN32 ${sources})

LINK_DIRECTORIES(../_build/LimitlessEngineGraphics)

target_link_libraries(LimitlessEngineCore LimitlessEngineGraphics)

include_directories(../LimitlessEngineGraphics)