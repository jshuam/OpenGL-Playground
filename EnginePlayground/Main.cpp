#include "DisplayManager.h"
#include "Loader.h"
#include "EntityRenderer.h"
#include "StaticShader.h"
#include "ModelTexture.h"
#include "TexturedModel.h"
#include "Entity.h"
#include "OBJLoader.h"
#include "Light.h"
#include "MasterRenderer.h"
#include "Player.h"

#include <random>

void error_callback( int error, const char* description )
{
	throw std::exception( description );
}

int main()
{
	try
	{
		glfwInit();
	}
	catch( std::exception& e )
	{
		std::cout << "\n" << e.what() << std::endl;
	}

	GLFWwindow* window = DisplayManager::createDisplay( 1280, 720 );
	Loader loader;

	/********************************* TEXTURES *********************************/

	TerrainTexture background_texture( loader.loadTexture( "grass" ) );
	TerrainTexture r_texture( loader.loadTexture( "mud" ) );
	TerrainTexture g_texture( loader.loadTexture( "grassFlowers" ) );
	TerrainTexture b_texture( loader.loadTexture( "path" ) );

	TerrainTexturePack texture_pack( background_texture, r_texture, g_texture, b_texture );
	TerrainTexture blend_map( loader.loadTexture( "blendMap" ) );

	/****************************************************************************/

	RawModel tree( OBJLoader::loadObjModel( "lowPolyTree", loader ) );
	RawModel grass( OBJLoader::loadObjModel( "grassModel", loader ) );
	RawModel fern( OBJLoader::loadObjModel( "fern", loader ) );
	RawModel flower( OBJLoader::loadObjModel( "grassModel", loader ) );

	TexturedModel tree_texture( tree, loader.loadTexture( "lowPolyTree" ) );
	tree_texture.getTexture().setNumRows( 4 );
	TexturedModel grass_texture( grass, loader.loadTexture( "grassTexture" ) );
	grass_texture.getTexture().setTransparency( true );
	grass_texture.getTexture().setFakeLighting( true );
	TexturedModel flower_texture( grass, loader.loadTexture( "flower" ) );
	flower_texture.getTexture().setTransparency( true );
	flower_texture.getTexture().setFakeLighting( true );
	TexturedModel fern_texture( fern, loader.loadTexture( "fern" ) );
	fern_texture.getTexture().setNumRows( 2 );
	fern_texture.getTexture().setTransparency( true );

	std::vector<Entity> entities;
	std::uniform_real_distribution<GLfloat> float_dist( 10, 790 );
	std::uniform_int_distribution<GLuint> tree_dist( 0, 15 );
	std::uniform_int_distribution<GLuint> fern_dist( 0, 3 );
	std::random_device rt;
	std::mt19937 mt( rt() );

	Terrain terrain = Terrain( 0, 0, loader, texture_pack, blend_map, "heightMap" );

	/*for( int i = 0; i < 200; i++ )
	{
		GLfloat x = float_dist( mt );
		GLfloat z = float_dist( mt );
		GLfloat y = terrain.getTerrainHeight( x, z );
		entities.emplace_back( flower_texture, glm::vec3( x, y, z ), 0, 0, 0, 1 );
		x = float_dist( mt );
		z = float_dist( mt );
		y = terrain.getTerrainHeight( x, z );
		entities.emplace_back( fern_texture, fern_dist( mt ), glm::vec3( x, y, z ), 0, 0, 0, 1 );
	}
	for( int i = 0; i < 350; i++ )
	{
		GLfloat x = float_dist( mt );
		GLfloat z = float_dist( mt );
		GLfloat y = terrain.getTerrainHeight( x, z );
		entities.emplace_back( grass_texture, glm::vec3( x, y, z ), 0, 0, 0, 1 );
	}*/
	for( int i = 0; i < 200; i++ )
	{
		GLfloat x = float_dist( mt );
		GLfloat z = float_dist( mt );
		GLfloat y = terrain.getTerrainHeight( x, z );
		entities.emplace_back( tree_texture, tree_dist( mt ), glm::vec3( x, y, z ), 0, 0, 0, 1 );
	}

	Light light( glm::vec3( 20000, 40000, 20000 ), glm::vec3( 1, 1, 1 ) );

	MasterRenderer renderer;
	GLfloat old_dt = glfwGetTime(), timer = old_dt;
	GLfloat new_dt = 0;
	GLfloat dt = 0;
	GLuint frames = 0;

	RawModel player_model( OBJLoader::loadObjModel( "player", loader ) );
	TexturedModel player_texture( player_model, ModelTexture( loader.loadTexture( "pink" ) ) );
	player_texture.getTexture().setShineDamper( 1000 );
	player_texture.getTexture().setReflectivity( 100 );
	Player player( player_texture, glm::vec3( 0, 0, 0 ), 0, 0, 0, 0.5 );
	Camera camera( &player );

	while( !glfwWindowShouldClose( window ) )
	{
		new_dt = glfwGetTime();
		dt = new_dt - old_dt;
		old_dt = new_dt;
		for( auto& entity : entities )
		{
			renderer.processEntity( entity );
		}
		renderer.processTerrain( terrain );
		camera.move( dt );
		player.move( dt, terrain );
		renderer.processEntity( player );
		renderer.render( light, camera );
		DisplayManager::updateDisplay();
		frames++;
		if( glfwGetTime() - timer > 1.0 )
		{
			timer++;
			DisplayManager::updateTitle( frames );
			frames = 0;
		}
	}

	renderer.cleanUp();
	loader.cleanUp();
	DisplayManager::closeDisplay();

	glfwTerminate();
}