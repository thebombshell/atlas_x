
#ifndef SHADERS_H
#define SHADERS_H

typedef struct {
	
	float world[16];
	float view[16];
	float proj[16];
} uniform_wvp;

typedef struct {
	
	unsigned int sampler;
	unsigned int texture;
} uniform_texture_type;

#define SHADER_POSITION_VS_HEAD \
	"layout(location = 0)in vec3 attribute_position;\n" \
	"layout(std430, binding = 0)buffer uniform_wvp { mat4 uniform_world; mat4 uniform_view; mat4 uniform_proj; };\n"

#define SHADER_COLOR_VS_HEAD \
	"layout(location = 2)in vec4 attribute_colour;\n" \
	"out vec4 varying_colour;\n"

#define SHADER_TEXCOORD_VS_HEAD \
	"layout(location = 3)in vec2 attribute_texcoord;\n" \
	"out vec2 varying_texcoord;\n"

#define SHADER_POSITION_VS_BODY \
	"	gl_Position = uniform_proj * uniform_view * uniform_world *  vec4(attribute_position, 1.);\n"

#define SHADER_COLOR_VS_BODY \
	"	varying_colour = attribute_colour;\n"

#define SHADER_TEXCOORD_VS_BODY \
	"	varying_texcoord = attribute_texcoord;\n"

const char* vs_position_shader = 
	"#version 460\n"
	SHADER_POSITION_VS_HEAD
	"void main() {\n"
	SHADER_POSITION_VS_BODY
	"}\n";

const char* vs_position_color_shader =
	"#version 460\n"
	SHADER_POSITION_VS_HEAD
	SHADER_COLOR_VS_HEAD
	"void main() {\n"
	SHADER_POSITION_VS_BODY
	SHADER_COLOR_VS_BODY
	"}\n";

const char* vs_position_texcoord_shader = 
	"#version 460\n"
	SHADER_POSITION_VS_HEAD
	SHADER_TEXCOORD_VS_HEAD
	"void main() {\n"
	SHADER_POSITION_VS_BODY
	SHADER_TEXCOORD_VS_BODY
	"}\n";

const char* vs_position_color_texcoord_shader =
	"#version 460\n"
	SHADER_POSITION_VS_HEAD
	SHADER_COLOR_VS_HEAD
	SHADER_TEXCOORD_VS_HEAD
	"layout(std430, binding = 0)buffer uniform_wvp { mat4 uniform_world; mat4 uniform_view; mat4 uniform_proj; };"
	"void main() {\n"
	SHADER_POSITION_VS_BODY
	SHADER_COLOR_VS_BODY
	SHADER_TEXCOORD_VS_BODY
	"}\n";

const char* fs_color_shader =
	"#version 460\n"
	"out vec4 output_colour;"
	"void main() {\n"
	"	output_colour = varying_colour;"
	"}\n";

const char* fs_texcoord_shader =
	"#version 460\n"
	"in vec2 varying_texcoord;"
	"out vec4 output_colour;"
	"layout(binding = 2)uniform sampler2D uniform_texture;"
	"void main() {\n"
	"	output_colour = texture2D(uniform_texture, varying_texcoord);"
	"}\n";

const char* fs_color_texcoord_shader =
	"#version 460\n"
	"in vec4 varying_colour;"
	"in vec2 varying_texcoord;"
	"out vec4 output_colour;"
	"layout(binding = 2)uniform sampler2D uniform_texture;"
	"void main() {\n"
	"	output_colour = texture2D(uniform_texture, varying_texcoord) * varying_colour;"
	"}\n";

#endif