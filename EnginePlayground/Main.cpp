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
#include "GuiTexture.h"
#include "GuiRenderer.h"
#include "MousePicker.h"

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
	RawModel diffuse( OBJLoader::loadObjModel( "grassModel", loader ) );
	RawModel fern( OBJLoader::loadObjModel( "fern", loader ) );
	RawModel lamp( OBJLoader::loadObjModel( "lamp", loader ) );

	TexturedModel tree_texture( tree, loader.loadTexture( "lowPolyTree" ) );
	tree_texture.getTexture().setNumRows( 2 );
	TexturedModel diffuse_texture( diffuse, loader.loadTexture( "diffuse" ) );
	diffuse_texture.getTexture().setNumRows( 3 );
	diffuse_texture.getTexture().setTransparency( true );
	diffuse_texture.getTexture().setFakeLighting( true );
	TexturedModel fern_texture( fern, loader.loadTexture( "fern" ) );
	fern_texture.getTexture().setNumRows( 2 );
	fern_texture.getTexture().setTransparency( true );
	TexturedModel lamp_texture( lamp, loader.loadTexture( "lamp" ) );
	lamp_texture.getTexture().setFakeLighting( true );

	std::vector<std::shared_ptr<Entity>> entities;
	std::vector<std::shared_ptr<Light>> lights;
	std::vector<Terrain> terrains;
	std::uniform_real_distribution<GLfloat> float_dist( 10, 790 );
	std::uniform_int_distribution<GLuint> tree_dist( 0, 15 );
	std::uniform_int_distribution<GLuint> fern_dist( 0, 3 );
	std::uniform_int_distribution<GLuint> diffuse_dist( 0, 8 );
	std::random_device rt;
	std::mt19937 mt( rt() );

	terrains.emplace_back( 0, 0, loader, texture_pack, blend_map, "heightmapPerlin" );

	for( int i = 0; i < 200; i++ )
	{
		GLfloat x = float_dist( mt );
		GLfloat z = float_dist( mt );
		GLfloat y = terrains[0].getTerrainHeight( x, z );
		entities.emplace_back( std::make_shared<Entity>( fern_texture, fern_dist( mt ), glm::vec3( x, y, z ), 0, 0, 0, 1 ) );
	}
	for( int i = 0; i < 350; i++ )
	{
		GLfloat x = float_dist( mt );
		GLfloat z = float_dist( mt );
		GLfloat y = terrains[0].getTerrainHeight( x, z );
		entities.emplace_back( std::make_shared<Entity>( diffuse_texture, diffuse_dist( mt ), glm::vec3( x, y, z ), 0, 0, 0, 3 ) );
	}
	for( int i = 0; i < 200; i++ )
	{
		GLfloat x = float_dist( mt );
		GLfloat z = float_dist( mt );
		GLfloat y = terrains[0].getTerrainHeight( x, z );
		entities.emplace_back( std::make_shared<Entity>( tree_texture, tree_dist( mt ), glm::vec3( x, y, z ), 0, 0, 0, 1 ) );
	}

	lights.emplace_back( std::make_shared<Light>( glm::vec3( 0, 1000, 7000 ), glm::vec3( 0.4f, 0.4, 0.4f ) ) );
	lights.emplace_back( std::make_shared<Light>( glm::vec3( 185, terrains[0].getTerrainHeight( 185, 293 ) + 13, 293 ), glm::vec3( 3, 0, 0 ), glm::vec3( 1, 0.01f, 0.002f ) ) );
	lights.emplace_back( std::make_shared<Light>( glm::vec3( 370, terrains[0].getTerrainHeight( 370, 300 ) + 13, 300 ), glm::vec3( 0, 3, 3 ), glm::vec3( 1, 0.01f, 0.002f ) ) );
	lights.emplace_back( std::make_shared<Light>( glm::vec3( 293, terrains[0].getTerrainHeight( 293, 305 ) + 13, 305 ), glm::vec3( 3, 3, 0 ), glm::vec3( 1, 0.01f, 0.002f ) ) );

	entities.emplace_back( std::make_shared<Entity>( lamp_texture, glm::vec3( 185, terrains[0].getTerrainHeight( 185, 293 ), 293 ), 0, 0, 0, 1 ) );
	entities.emplace_back( std::make_shared<Entity>( lamp_texture, glm::vec3( 370, terrains[0].getTerrainHeight( 370, 300 ), 300 ), 0, 0, 0, 1 ) );
	entities.emplace_back( std::make_shared<Entity>( lamp_texture, glm::vec3( 293, terrains[0].getTerrainHeight( 293, 305 ), 305 ), 0, 0, 0, 1 ) );

	GLuint frames = 0;
	GLfloat timer = glfwGetTime();

	RawModel player_model( OBJLoader::loadObjModel( "player", loader ) );
	TexturedModel player_texture( player_model, ModelTexture( loader.loadTexture( "pink" ) ) );
	player_texture.getTexture().setShineDamper( 1000 );
	player_texture.getTexture().setReflectivity( 100 );
	std::shared_ptr<Player> player = std::make_shared<Player>( player_texture, glm::vec3( 0, 0, 0 ), 0, 0, 0, 0.5 );
	Camera camera( player );
	entities.push_back( player );
	std::shared_ptr<Entity> lamp_entity = std::make_shared<Entity>( lamp_texture, glm::vec3( 5, terrains[0].getTerrainHeight( 5, 5 ) + 13, 5 ), 0, 0, 0, 1 );
	entities.push_back( lamp_entity );
	std::shared_ptr<Light> light = std::make_shared<Light>( glm::vec3( 185, terrains[0].getTerrainHeight( 185, 293 ) + 13, 293 ), glm::vec3( 3, 0, 1 ), glm::vec3( 1, 0.01f, 0.002f ) );
	lights.push_back( light );
	MasterRenderer renderer( loader, lights.size() );

	MousePicker picker( camera, renderer.getProjectionMatrix(), &terrains[0] );

	while( !glfwWindowShouldClose( window ) )
	{
		DisplayManager::calculateDeltaTime();
		camera.move( DisplayManager::getDeltaTime() );
		player->move( DisplayManager::getDeltaTime(), terrains[0] );

		picker.update();
		if( picker.currentTerrainPointFound() )
		{
			glm::vec3 point = picker.getCurrentTerrainPoint();
			lamp_entity->setPosition( point );
			light->setPosition( point.x, terrains[0].getTerrainHeight( point.x, point.z ) + 13, point.z );
		}

		renderer.renderScene( entities, terrains, lights, camera );
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