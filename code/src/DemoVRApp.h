#include "bsg/bsg.h"
#include "bsg/bsgMenagerie.h"
#include "bsg/bsgObjModel.h"
#include "db/DBHandler.h"
#include "ds/Dimension.h"

#include <api/MinVR.h>

class DemoVRApp: public MinVR::VRApp {

	// private members of the VRApp.
private:

	DBHandler _dbhandler;
	Dimension<string> _d;

	// The scene and the objects in it must be available from the main()
	// function where it is created and the renderScene() function where
	// it is drawn.  The scene object contains all the drawable objects
	// that make up the scene.
	bsg::scene _scene;

	// These are the shapes that make up the scene.  They are out here in
	// the global variables so they can be available in both the main()
	// function and the renderScene() function.
	bsg::drawableCompound* _axesSet;
	bsg::drawableCollection* _modelGroup;
	bsg::drawableObjModel* _model;
	bsg::drawableObjModel* _orbiter;

	// These are part of the animation stuff, and again are out here with
	// the big boy global variables so they can be available to both the
	// interrupt handler and the render function.
	float _oscillator;

	// These variables were not global before, but their scope has been
	// divided into several functions here, so they are class-wide
	// private data objects.
	bsg::bsgPtr<bsg::shaderMgr> _shader;
	bsg::bsgPtr<bsg::shaderMgr> _axesShader;
	bsg::bsgPtr<bsg::lightList> _lights;

	// Here are the drawable objects that make up the compound object
	// that make up the scene.
	bsg::drawableObj _axes;
	bsg::drawableObj _topShape;
	bsg::drawableObj _bottomShape;

	std::string _vertexFile;
	std::string _fragmentFile;

	// These functions from demo2.cpp are not needed here:
	//
	//    init()
	//    makeWindow()
	//    resizeWindow()
	//    ... also most of the processKeys() methods.
	//
	// The functionality of these methods is assumed by the MinVR apparatus.

	// This contains a bunch of sanity checks from the graphics
	// initialization of demo2.cpp.  They are still useful with MinVR.
	void _checkContext();

	// Just a little debug function so that a user can see what's going on
	// in a non-graphical sense.
	void _showCameraPosition();

	void _initializeScene();

public:
	DemoVRApp(int argc, char** argv);

	/// The MinVR apparatus invokes this method whenever there is a new
	/// event to process.
	void onVREvent(const MinVR::VREvent &event);

	/// brief Set the render context.
	///
	/// The onVRRender methods are the heart of the MinVR rendering
	/// apparatus.  Some render calls are shared among multiple views,
	/// for example a stereo view has two renders, with the same render
	/// context.
	void onVRRenderGraphicsContext(const MinVR::VRGraphicsState &renderState);

	/// brief draw the image.
	///
	/// This is the heart of any graphics program, the render function.
	/// It is called each time through the main graphics loop, and
	/// re-draws the scene according to whatever has changed since the
	/// last time it was drawn.
	void onVRRenderGraphics(const MinVR::VRGraphicsState &renderState);
};

