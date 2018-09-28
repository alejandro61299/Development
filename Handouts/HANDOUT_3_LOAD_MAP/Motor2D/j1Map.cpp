#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1Textures.h"
#include "j1Map.h"
#include <math.h>

j1Map::j1Map() : j1Module(), map_loaded(false)
{
	name.create("map");
	map = new map_node;
	tex = nullptr;
}

// Destructor
j1Map::~j1Map()
{}

bool j1Map::Start()
{
	LOG("Map start");
	tex = App->tex->Load("maps/tmw_desert_spacing.png");
	// back background
	
	return true;
}

// Called before render is available
bool j1Map::Awake(pugi::xml_node& config)
{
	LOG("Loading Map Parser");
	bool ret = true;

	folder.create(config.child("folder").child_value());

	return ret;
}

void j1Map::Draw()
{
	if(map_loaded == false)
		return;
	SDL_Rect r = { 0, 0, tilesets.start->data->tilewidth, tilesets.start->data->tileheight };

	
	// TODO 6: Iterate all tilesets and draw all their 
	// images in 0,0 (you should have only one tileset for now)
	App->render->Blit(tex, 0, 0, &r);

}

// Called before quitting
bool j1Map::CleanUp()
{
	LOG("Unloading map");

	// TODO 2: Make sure you clean up any memory allocated
	// from tilesets / map
	tilesets.clear();
	delete map;
	map = nullptr;
	map_file.reset();

	return true;
}

// Load new map
bool j1Map::Load(const char* file_name)
{
	bool ret = true;
	p2SString tmp("%s%s", folder.GetString(), file_name);

	pugi::xml_parse_result result = map_file.load_file(tmp.GetString());

	if(result == NULL)
	{
		LOG("Could not load map xml file %s. pugi error: %s", file_name, result.description());
		ret = false;
	}

	if(ret == true)
	{
		// TODO 3: Create and call a private function to load and fill
		// all your map data
		ret = LoadMap();
	}

	
	if (ret == true)
	{
		// TODO 4: Create and call a private function to load a tileset
		// remember to support more any number of tilesets!
		ret = LoadTileSet();
	}
	

	if(ret == true)
	{
		LOG("Successfully parsed map XML file: %s", file_name);
		LOG("with:       %i  height:       %i", map->width, map->height);
		LOG("tile_width: %i  tile_height:  %i", map->tilewidth, map->tileheight);

		p2List_item<tileset_node*>* item;
		item = tilesets.start;
		/*for (item = tilesets.start; item != NULL; item = item->next)
		{*/
		while (item != NULL) {
			LOG("Tileset =========================");
			LOG("name:         %s", item->data->name);
			LOG("tile width:   %i", item->data->tilewidth);
			LOG("tile height:  %i", item->data->tileheight);
			LOG("spacing:      %i", item->data->spacing);
			LOG("margin:       %i", item->data->margin);
			item = item->next;
		}

		// TODO 5: LOG all the data loaded
		// iterate all tilesets and LOG everything
	}
	
	map_loaded = ret;

	return ret;
}

bool j1Map::LoadMap()
{
	const char* orientation_str = map_file.child("map").attribute("orientation").as_string();
	const char* renderorder_str = map_file.child("map").attribute("renderorder").as_string();

	if (orientation_str == "orthogonal")
		map->orientation = map_orientation::orthogonal;
	if (renderorder_str == "right-down")
		map->renderorder = map_renderorder::right_down;

	map->width = map_file.child("map").attribute("width").as_int();
	map->height = map_file.child("map").attribute("height").as_int();
	map->tilewidth = map_file.child("map").attribute("tilewidth").as_int();
	map->tileheight = map_file.child("map").attribute("tileheight").as_int();

	return true;
}

bool j1Map::LoadTileSet()
{

	for (pugi::xml_node tileset = map_file.child("map").child("tileset"); tileset; tileset = tileset.next_sibling("tileset"))
	{
		if (tileset == NULL) break;

		tileset_node *item = new tileset_node;
		
		item->name = tileset.attribute("name").as_string();
		item->firstgid = tileset.attribute("firstgid").as_int();
		item->tileheight = tileset.attribute("tileheight").as_int();
		item->tilewidth = tileset.attribute("tilewidth").as_int();
		item->spacing = tileset.attribute("spacing").as_int();
		item->margin = tileset.attribute("margin").as_int();
		tilesets.add(item);

		delete item;
	}
	return true;
}

