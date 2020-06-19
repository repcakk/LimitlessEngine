file(GLOB sources
	"*.h"
	"*.cpp"
	"*.hlsl"
)

add_library(LimitlessEngineGraphics STATIC ${sources})

# Set shader types, models and entry point
set_source_files_properties(PixelShader.hlsl PROPERTIES VS_SHADER_TYPE Pixel VS_SHADER_MODEL 5.0 VS_SHADER_ENTRYPOINT main)
set_source_files_properties(VertexShader.hlsl PROPERTIES VS_SHADER_TYPE Vertex VS_SHADER_MODEL 5.0 VS_SHADER_ENTRYPOINT main)