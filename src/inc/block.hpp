#include <vector>
#include <string>

// An enumeration of all the implemented blocks.

enum block_id
{
	id_air,

	id_bedrock,

	id_water,

	id_stone,

	id_cobblestone,

	id_dirt,

	id_grass,

	id_mycelium,

	id_sand,

	id_sandstone,

	id_gravel,

	id_brick,

	id_bookshelf,

	id_oak_log,

	id_oak_planks,

	id_oak_leaves,

	id_birch_log,

	id_birch_planks,

	id_birch_leaves,

	id_red_mushroom_block,

	id_brown_mushroom_block,

	id_mushroom_stem,

	id_coal_ore,

	id_iron_ore,

	id_gold_ore,

	id_diamond_ore,

	id_emerald_ore,

	id_white_wool,

	id_orange_wool,

	id_magenta_wool,

	id_light_blue_wool,

	id_yellow_wool,

	id_lime_wool,

	id_pink_wool,

	id_gray_wool,

	id_light_gray_wool,

	id_cyan_wool,

	id_purple_wool,

	id_blue_wool,

	id_brown_wool,

	id_green_wool,

	id_red_wool,

	id_black_wool,

	id_glass,

	id_rose,

	id_dandelion,

	id_red_mushroom,

	id_brown_mushroom,

	id_double_stone_slab,

	id_double_sandstone_slab,

	id_double_oak_wood_slab,

	id_double_birch_wood_slab,

	id_double_cobblestone_slab,

	id_double_brick_slab,

	id_stone_slab,

	id_null
};

// Conversion from block_id to std::string.

std::vector<std::string> block_id_to_string =
{
	"air",

	"bedrock",

	"water",

	"stone",

	"cobblestone",

	"dirt",

	"grass",

	"mycelium",

	"sand",

	"sandstone",

	"gravel",

	"brick",

	"bookshelf",

	"oak_log",

	"oak_planks",

	"oak_leaves",

	"birch_log",

	"birch_planks",

	"birch_leaves",

	"red_mushroom_block",

	"brown_mushroom_block",

	"mushroom_stem",

	"coal_ore",

	"iron_ore",

	"gold_ore",

	"diamond_ore",

	"emerald_ore",

	"white_wool",

	"orange_wool",

	"magenta_wool",

	"light_blue_wool",

	"yellow_wool",

	"lime_wool",

	"pink_wool",

	"gray_wool",

	"light_gray_wool",

	"cyan_wool",

	"purple_wool",

	"blue_wool",

	"brown_wool",

	"green_wool",

	"red_wool",

	"black_wool",

	"glass",

	"rose",

	"dandelion",

	"red_mushroom",

	"brown_mushroom",

	"double_stone_slab",

	"double_sandstone_slab",

	"double_oak_wood_slab",

	"double_birch_wood_slab",

	"double_cobblestone_slab",

	"double_brick_slab",

	"stone_slab",

};

// Conversion from block_id to std::string (used for in-game text).

std::vector<std::string> block_id_to_block_name =
{
	"Air",

	"Bedrock",

	"Water",

	"Stone",

	"Cobblestone",

	"Dirt",

	"Grass",

	"Mycelium",

	"Sand",

	"Sandstone",

	"Gravel",

	"Brick",

	"Bookshelf",

	"Oak Log",

	"Oak Planks",

	"Oak Leaves",

	"Birch Log",

	"Birch Planks",

	"Birch Leaves",

	"Red Mushroom Block",

	"Brown Mushroom Block",

	"Mushroom Stem",

	"Coal Ore",

	"Iron Ore",

	"Gold Ore",

	"Diamond Ore",

	"Emerald Ore",

	"White Wool",

	"Orange Wool",

	"Magenta Wool",

	"Light Blue Wool",

	"Yellow Wool",

	"Lime Wool",

	"Pink Wool",

	"Gray Wool",

	"Light Gray Wool",

	"Cyan Wool",

	"Purple Wool",

	"Blue Wool",

	"Brown Wool",

	"Green Wool",

	"Red Wool",

	"Black Wool",

	"Glass",

	"Rose",

	"Dandelion",

	"Red Mushroom",

	"Brown Mushroom",

	"Double Stone Slab",

	"Double Sandstone Slab",

	"Double Oak Wood Slab",

	"Double Birch Wood Slab",

	"Double Cobblestone Slab",

	"Double Brick Slab"
	"Double Brick Slab",

	"Stone Slab",
};

// Returns true if a block is a cross block. Otherwise, returns false.

inline bool is_cross(block_id id)
{
	if 
	(
		id == id_rose ||

		id == id_dandelion ||

		id == id_red_mushroom || 

		id == id_brown_mushroom
	)
	{
		return true;
	}

	return false;
}

// Returns true if the block is not opaque. Otherwise, returns false.

inline bool is_transparent(block_id id)
{
	if 
	(
		id == id_air || 

		id == id_oak_leaves || 

		id == id_birch_leaves || 

		id == id_water ||

		id == id_glass ||

		id == id_null ||

		is_cross(id)
	)
	{
		return true;
	}

	return false;
}

// Returns false if a block is permeable to players. Otherwise, returns true.

inline bool is_not_permeable_mob(block_id id)
{
	if 
	(
		id == id_air ||

		id == id_water ||

		id == id_null ||

		is_cross(id)
	)
	{
		return false;
	}

	return true;
}

// Returns false if a block is permeable to rays. Otherwise, returns true.

inline bool is_not_permeable_ray(block_id id)
{
	if 
	(
		id == id_air ||

		id == id_water ||

		id == id_null
	)
	{
		return false;
	}

	return true;
}

// Returns false if a block is permeable to light. Otherwise, returns true.

inline bool is_not_permeable_light(block_id id)
{
	if 
	(
		id == id_air ||

		id == id_glass ||

		is_cross(id)
	)
	{
		return false;
	}

	return true;
}