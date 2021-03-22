
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

const char* vs_basic_shader =
	"#version 460\n"
	"layout(location = 0)in vec3 attribute_position;"
	"layout(location = 2)in vec4 attribute_colour;"
	"out vec4 varying_colour;"
	"layout(std430, binding = 0)buffer uniform_wvp { mat4 uniform_world; mat4 uniform_view; mat4 uniform_proj; };"
	"void main() {\n"
	"	gl_Position = uniform_proj * uniform_view * uniform_world *  vec4(attribute_position, 1.);"
	"	varying_colour = attribute_colour;"
	"}\n";

const char* fs_basic_shader =
	"#version 460\n"
	"in vec4 varying_colour;"
	"out vec4 output_colour;"
	"void main() {\n"
	"	output_colour = varying_colour;"
	"}\n";

const char* vs_sprite_shader =
	"#version 460\n"
	"layout(location = 0)in vec3 attribute_position;"
	"layout(location = 2)in vec4 attribute_colour;"
	"layout(location = 3)in vec2 attribute_texcoord;"
	"out vec4 varying_colour;"
	"out vec2 varying_texcoord;"
	"layout(std430, binding = 0)buffer uniform_wvp { mat4 uniform_world; mat4 uniform_view; mat4 uniform_proj; };"
	"void main() {\n"
	"	gl_Position = uniform_proj * uniform_view * uniform_world *  vec4(attribute_position, 1.);"
	"	varying_colour = attribute_colour;"
	"	varying_texcoord = attribute_texcoord;"
	"}\n";

const char* fs_sprite_shader =
	"#version 460\n"
	"in vec4 varying_colour;"
	"in vec2 varying_texcoord;"
	"out vec4 output_colour;"
	"layout(binding = 2)uniform sampler2D uniform_texture;"
	"void main() {\n"
	"	output_colour = texture2D(uniform_texture, varying_texcoord) * varying_colour;"
	"}\n";

const char* vs_heightmap_shader =
	"#version 460\n"
	"layout(location = 0)in vec2 attribute_position;"
	"out vec4 varying_colour;"
	"out vec2 varying_texcoord;"
	"layout(std430, binding = 0)buffer uniform_wvp { mat4 uniform_world; mat4 uniform_view; mat4 uniform_proj; };"
	"layout(binding = 1)uniform sampler2D uniform_heightmap;"
	"void main() {\n"
	"	vec4 heightmap_sample = texture2D(uniform_heightmap, attribute_position / 1024.);"
	"	gl_Position = uniform_proj * uniform_view * uniform_world * vec4(attribute_position, heightmap_sample.a, 1.);"
	"	varying_colour = vec4(heightmap_sample.rgb, 1.);"
	"	varying_texcoord = attribute_position / 1024.;"
	"}\n";

#endif