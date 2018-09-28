#ifndef __j1MAP_H__
#define __j1MAP_H__

#include "PugiXml/src/pugixml.hpp"
#include "p2List.h"
#include "p2Point.h"
#include "j1Module.h"

typedef unsigned int uint;
// TODO 2: Create a struct to hold information for a TileSet
// Ignore Terrain Types and Tile Types for now, but we want the image!
// ----------------------------------------------------
struct tileset_node
{
	const char* name = nullptr;
	uint firstgid = 0;
	uint tileheight = 0;
	uint tilewidth = 0;
	uint spacing = 0;
	uint margin = 0;

};

// TODO 1: Create a struct needed to hold the information to Map node
enum class map_renderorder {
	left_down,
	right_down,
	left_up,
	right_up,
	error
};

enum class map_orientation {
    orthogonal,
	error
};

struct map_node 
{
	map_orientation orientation = map_orientation::error;
	map_renderorder renderorder = map_renderorder::error;
	uint  width = 0;
	uint height = 0;
	uint tilewidth = 0;
	uint tileheight = 0;

};

// ----------------------------------------------------
class j1Map : public j1Module
{
public:

	j1Map();

	// Destructor
	virtual ~j1Map();

	// Called before render is available
	bool Awake(pugi::xml_node& conf);

	// Called before the first frame
	bool Start();

	// Called each loop iteration
	void Draw();

	// Called before quitting
	bool CleanUp();

	// Load new map
	bool Load(const char* path);

private:

	bool LoadMap();
	bool LoadTileSet();

public:

	// TODO 1: Add your struct for map info as public for now
	map_node *map;
	p2List<tileset_node*> tilesets;
	SDL_Texture* tex;

private:

	pugi::xml_document	map_file;
	p2SString			folder;
	bool				map_loaded;
};

#endif // __j1MAP_H__