#include "Oryx.h"
#include "OryxEngine.h"
#include "OryxGameState.h"
#include "GLSubsystem/GLSubsystem.h"
#include "OISSubsystem/OISSubsystem.h"

using namespace Oryx;

class PlayState : public GameState
{
public:

	PlayState() : timer(5.f) {}
	virtual ~PlayState() {}

	virtual void init() 
	{
		OISSubsystem* input = dynamic_cast<OISSubsystem*>(mEngine->getSubsystem("OISSubsystem"));
		GLSubsystem* gl = dynamic_cast<GLSubsystem*>(mEngine->getSubsystem("GLSubsystem"));
		input->initInput(gl->getWindowHandle(), false);
	}

	virtual void update(Real delta)
	{
		timer -= delta;
		if(timer <= 0.f)
			mEngine->shutdown();
	}

	virtual void deinit() {}

	Real timer;
};

int main(int argc, char** argv)
{
	Logger::getPtr();
	TimeManager::getPtr();

	// create subsystems:
	GLSubsystem gl(640,480,false);
	OISSubsystem ois;

	// allocate engine and add subsystems
	Engine* eng = new Engine();
	eng->addSubsystem(&gl);
	eng->addSubsystem(&ois);

	// initialize the engine
	eng->init();

	// add game state
	eng->addState(new PlayState());

	// start up the engine
	eng->start();

	// delete the engine object
	delete eng;
	return 0;
}
