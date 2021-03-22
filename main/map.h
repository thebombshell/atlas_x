
#ifndef MAP_H
#define MAP_H

#include "assert.h"
#include "../data_structures.h"
#include "../graphics.h"

typedef struct {
	
	hash_link link;
	unsigned int filepath_length;
	char* filepath;
	int is_loaded;
	texture heightmap;
} heightmap;

int init_heightmap(heightmap* t_heightmap, const char* t_filepath) {
	
	assert(t_heightmap && t_filepath);
	
	t_heightmap->filepath_length = strlen(t_filepath);
	t_heightmap->filepath = malloc(t_heightmap->filepath_length + 1);
	strcpy(t_heightmap->filepath, t_filepath);
	t_heightmap->is_loaded = 0;
	memset(&t_heightmap->heightmap, 0, sizeof(texture));
	
	return 1;
}

void final_heightmap(heightmap* t_heightmap) {
	
	assert(t_heightmap);
	
	free(t_heightmap->filepath);
	if (t_heightmap->is_loaded) {
		
		final_texture(&t_heightmap->heightmap);
	}
}

void heightmap_new(heightmap* t_heightmap) {
	
	assert(t_heightmap && !t_heightmap->is_loaded);
	
	char* data = calloc(1, 1024 * 1024 * 4);
	unsigned int i = 0, j = 0;
	for (; i < 1024; ++i) {
		
		for (j = 0; j < 1024; ++j) {
			
			data[(i * 1024 + j) * 4 + 0] = 255;
			data[(i * 1024 + j) * 4 + 1] = 255;
			data[(i * 1024 + j) * 4 + 2] = 255;
			data[(i * 1024 + j) * 4 + 3] = 0;
		}
	}
	init_texture(&t_heightmap->heightmap, data, 1024, 1024, GL_RGBA, GL_RGBA, GL_UNSIGNED_BYTE);
	t_heightmap->is_loaded = 1;
}

int heightmap_load(heightmap* t_heightmap) {
	
	assert(t_heightmap && !t_heightmap->is_loaded);
	
	if (load_texture(&t_heightmap->heightmap, t_heightmap->filepath)) {
		
		t_heightmap->is_loaded = 1;
		return 1;
	}
	
	return 0;
}

int heightmap_save(heightmap* t_heightmap) {
	
	assert(t_heightmap && t_heightmap->is_loaded);
	
	return load_texture(&t_heightmap->heightmap, t_heightmap->filepath);
}

#define HEIGHTMAP_COUNT_0 (1)
#define HEIGHTMAP_COUNT_1 (HEIGHTMAP_COUNT_0 * 4)
#define HEIGHTMAP_COUNT_2 (HEIGHTMAP_COUNT_1 * 4)
#define HEIGHTMAP_COUNT_3 (HEIGHTMAP_COUNT_2 * 4)
#define HEIGHTMAP_COUNT_4 (HEIGHTMAP_COUNT_3 * 4)
#define HEIGHTMAP_COUNT_5 (HEIGHTMAP_COUNT_4 * 4)
#define HEIGHTMAP_COUNT_6 (HEIGHTMAP_COUNT_5 * 4)
#define HEIGHTMAP_COUNT_7 (HEIGHTMAP_COUNT_6 * 4)
#define HEIGHTMAP_COUNT_8 (HEIGHTMAP_COUNT_7 * 4)
#define HEIGHTMAP_COUNT_9 (HEIGHTMAP_COUNT_8 * 4)
#define HEIGHTMAP_COUNT_10 (HEIGHTMAP_COUNT_9 * 4)

#define HEIGHTMAP_SIZE_0 (HEIGHTMAP_COUNT_0 * 6)
#define HEIGHTMAP_SIZE_1 (HEIGHTMAP_COUNT_1 * 6)
#define HEIGHTMAP_SIZE_2 (HEIGHTMAP_COUNT_2 * 6)
#define HEIGHTMAP_SIZE_3 (HEIGHTMAP_COUNT_3 * 6)
#define HEIGHTMAP_SIZE_4 (HEIGHTMAP_COUNT_4 * 6)
#define HEIGHTMAP_SIZE_5 (HEIGHTMAP_COUNT_5 * 6)
#define HEIGHTMAP_SIZE_6 (HEIGHTMAP_COUNT_6 * 6)
#define HEIGHTMAP_SIZE_7 (HEIGHTMAP_COUNT_7 * 6)
#define HEIGHTMAP_SIZE_8 (HEIGHTMAP_COUNT_8 * 6)
#define HEIGHTMAP_SIZE_9 (HEIGHTMAP_COUNT_9 * 6)
#define HEIGHTMAP_SIZE_10 (HEIGHTMAP_COUNT_10 * 6)

#define HEIGHTMAP_OFFSET_0 (0)
#define HEIGHTMAP_OFFSET_1 (HEIGHTMAP_OFFSET_0 + HEIGHTMAP_COUNT_0)
#define HEIGHTMAP_OFFSET_2 (HEIGHTMAP_OFFSET_1 + HEIGHTMAP_COUNT_1)
#define HEIGHTMAP_OFFSET_3 (HEIGHTMAP_OFFSET_2 + HEIGHTMAP_COUNT_2)
#define HEIGHTMAP_OFFSET_4 (HEIGHTMAP_OFFSET_3 + HEIGHTMAP_COUNT_3)
#define HEIGHTMAP_OFFSET_5 (HEIGHTMAP_OFFSET_4 + HEIGHTMAP_COUNT_4)
#define HEIGHTMAP_OFFSET_6 (HEIGHTMAP_OFFSET_5 + HEIGHTMAP_COUNT_5)
#define HEIGHTMAP_OFFSET_7 (HEIGHTMAP_OFFSET_6 + HEIGHTMAP_COUNT_6)
#define HEIGHTMAP_OFFSET_8 (HEIGHTMAP_OFFSET_7 + HEIGHTMAP_COUNT_7)
#define HEIGHTMAP_OFFSET_9 (HEIGHTMAP_OFFSET_8 + HEIGHTMAP_COUNT_8)
#define HEIGHTMAP_OFFSET_10 (HEIGHTMAP_OFFSET_9 + HEIGHTMAP_COUNT_9)

#define HEIGHTMAP_INDICES_COUNT \
	( HEIGHTMAP_SIZE_0 \
	+ HEIGHTMAP_SIZE_1 \
	+ HEIGHTMAP_SIZE_2 \
	+ HEIGHTMAP_SIZE_3 \
	+ HEIGHTMAP_SIZE_4 \
	+ HEIGHTMAP_SIZE_5 \
	+ HEIGHTMAP_SIZE_6 \
	+ HEIGHTMAP_SIZE_7 \
	+ HEIGHTMAP_SIZE_8 \
	+ HEIGHTMAP_SIZE_9 \
	+ HEIGHTMAP_SIZE_10 )

static mesh g_heightmap_mesh_storage;

static mesh* g_heightmap_mesh = 0;

static const unsigned int g_heightmap_division_count[11] = {
	
	HEIGHTMAP_COUNT_0,
	HEIGHTMAP_COUNT_1,
	HEIGHTMAP_COUNT_2,
	HEIGHTMAP_COUNT_3,
	HEIGHTMAP_COUNT_4,
	HEIGHTMAP_COUNT_5,
	HEIGHTMAP_COUNT_6,
	HEIGHTMAP_COUNT_7,
	HEIGHTMAP_COUNT_8,
	HEIGHTMAP_COUNT_9,
	HEIGHTMAP_COUNT_10
};

static const unsigned int g_heightmap_division_size[11] = {
	
	HEIGHTMAP_SIZE_0,
	HEIGHTMAP_SIZE_1,
	HEIGHTMAP_SIZE_2,
	HEIGHTMAP_SIZE_3,
	HEIGHTMAP_SIZE_4,
	HEIGHTMAP_SIZE_5,
	HEIGHTMAP_SIZE_6,
	HEIGHTMAP_SIZE_7,
	HEIGHTMAP_SIZE_8,
	HEIGHTMAP_SIZE_9,
	HEIGHTMAP_SIZE_10
};

static const unsigned int g_heightmap_division_offset[11] = {
	
	HEIGHTMAP_OFFSET_0,
	HEIGHTMAP_OFFSET_1,
	HEIGHTMAP_OFFSET_2,
	HEIGHTMAP_OFFSET_3,
	HEIGHTMAP_OFFSET_4,
	HEIGHTMAP_OFFSET_5,
	HEIGHTMAP_OFFSET_6,
	HEIGHTMAP_OFFSET_7,
	HEIGHTMAP_OFFSET_8,
	HEIGHTMAP_OFFSET_9,
	HEIGHTMAP_OFFSET_10
};

int init_heightmap_mesh() {
	
	assert(!g_heightmap_mesh);
	
	SYS("initializing heightmap mesh");
	
	SYS("heightmap counts:\n\t\t%i,\n\t\t%i,\n\t\t%i,\n\t\t%i,\n\t\t%i,\n\t\t%i,\n\t\t%i,\n\t\t%i,\n\t\t%i,\n\t\t%i,\n\t\t%i"
		, HEIGHTMAP_COUNT_0
		, HEIGHTMAP_COUNT_1
		, HEIGHTMAP_COUNT_2
		, HEIGHTMAP_COUNT_3
		, HEIGHTMAP_COUNT_4
		, HEIGHTMAP_COUNT_5
		, HEIGHTMAP_COUNT_6
		, HEIGHTMAP_COUNT_7
		, HEIGHTMAP_COUNT_8
		, HEIGHTMAP_COUNT_9
		, HEIGHTMAP_COUNT_10);
	
	SYS("heightmap size:\n\t\t%i,\n\t\t%i,\n\t\t%i,\n\t\t%i,\n\t\t%i,\n\t\t%i,\n\t\t%i,\n\t\t%i,\n\t\t%i,\n\t\t%i,\n\t\t%i"
		, HEIGHTMAP_SIZE_0
		, HEIGHTMAP_SIZE_1
		, HEIGHTMAP_SIZE_2
		, HEIGHTMAP_SIZE_3
		, HEIGHTMAP_SIZE_4
		, HEIGHTMAP_SIZE_5
		, HEIGHTMAP_SIZE_6
		, HEIGHTMAP_SIZE_7
		, HEIGHTMAP_SIZE_8
		, HEIGHTMAP_SIZE_9
		, HEIGHTMAP_SIZE_10);
	
	SYS("heightmap offset:\n\t\t%i,\n\t\t%i,\n\t\t%i,\n\t\t%i,\n\t\t%i,\n\t\t%i,\n\t\t%i,\n\t\t%i,\n\t\t%i,\n\t\t%i,\n\t\t%i"
		, HEIGHTMAP_OFFSET_0
		, HEIGHTMAP_OFFSET_1
		, HEIGHTMAP_OFFSET_2
		, HEIGHTMAP_OFFSET_3
		, HEIGHTMAP_OFFSET_4
		, HEIGHTMAP_OFFSET_5
		, HEIGHTMAP_OFFSET_6
		, HEIGHTMAP_OFFSET_7
		, HEIGHTMAP_OFFSET_8
		, HEIGHTMAP_OFFSET_9
		, HEIGHTMAP_OFFSET_10);
	
	static float attrib_pos[1025 * 1025 * 2];
	
	float x = 0.0f, y = 0.0f;
	unsigned int offset = 0;
	for (; y < 1025.0f; y += 1.0f) {
		
		for (x = 0.0f; x < 1025.0f; x += 1.0f) {
			
			attrib_pos[offset + 0] = x;
			attrib_pos[offset + 1] = y;
			offset += 2;
		}
	}
	
	static unsigned int index_data[HEIGHTMAP_INDICES_COUNT];
	unsigned int i = 0, j = 0, k = 0, vertex_stride = 0, tl = 0, tr = 0, bl = 0, br = 0;
	
	for (; i < 11; ++i) {
		
		vertex_stride = (1 << (10 - i));
		for (j = 0; j < (1024 / vertex_stride); ++j) {
			
			for (k = 0; k < (1024 / vertex_stride); ++k) {
				
				offset = g_heightmap_division_offset[i] + j * (1024 / vertex_stride) + k;
				
				tl = (j + 0) * (vertex_stride) * 1025 + (k + 0) * (vertex_stride);
				tr = (j + 0) * (vertex_stride) * 1025 + (k + 1) * (vertex_stride);
				bl = (j + 1) * (vertex_stride) * 1025 + (k + 0) * (vertex_stride);
				br = (j + 1) * (vertex_stride) * 1025 + (k + 1) * (vertex_stride);
				
				index_data[offset * 6 + 0] = tl;
				index_data[offset * 6 + 1] = bl;
				index_data[offset * 6 + 2] = br;
				index_data[offset * 6 + 3] = tl;
				index_data[offset * 6 + 4] = br;
				index_data[offset * 6 + 5] = tr;
			}
		}
	}
	
	
	static vertex_attribute attribs = {
		
		attrib_pos,
		1025 * 1025 * sizeof(float) * 2,
		2,
		GL_FLOAT,
		sizeof(float) * 2
	};
	
	static index_buffer indices = {
		
		index_data,
		HEIGHTMAP_INDICES_COUNT * sizeof(unsigned int),
		GL_UNSIGNED_INT
	};
	
	if (init_mesh(&g_heightmap_mesh_storage, 1, &attribs, GL_STATIC_DRAW, &indices, GL_STATIC_DRAW)) {
		
		g_heightmap_mesh = &g_heightmap_mesh_storage;
		SYS("initialized heightmap mesh");
		return 1;
	}
	
	ERR("failed initializing heightmap mesh");
	
	return 0;
}

void heightmap_render(heightmap* t_heightmap, unsigned int t_division, unsigned int t_heightmap_index) {
	
	assert(t_heightmap && t_heightmap->is_loaded && t_division < 11);
	
	if (!g_heightmap_mesh) {
		
		if (!init_heightmap_mesh()) {
			
			return;
		}
	}
	
	texture_bind(&t_heightmap->heightmap, t_heightmap_index);
	mesh_render_part(g_heightmap_mesh, g_heightmap_division_offset[t_division] * 6 * sizeof(unsigned int), g_heightmap_division_size[t_division]);
}


#endif