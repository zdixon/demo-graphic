#include "DemoVRApp.h"
#include "ds/Dimension.h"
#include "StageController.h"
#include <string>
#include <sstream>
#include <iostream>
#include <ft2build.h>

#include FT_FREETYPE_H
#include FT_GLYPH_H

#define WIDTH   512
#define HEIGHT  512

/* origin is the upper left corner */
unsigned char image[HEIGHT][WIDTH];

void draw_bitmap(FT_Bitmap* bitmap, FT_Int x, FT_Int y) {
	FT_Int i, j, p, q;
	FT_Int x_max = x + bitmap->width;
	FT_Int y_max = y + bitmap->rows;

	for (i = x, p = 0; i < x_max; i++, p++) {
		for (j = y, q = 0; j < y_max; j++, q++) {
			if (i < 0 || j < 0 || i >= WIDTH || j >= HEIGHT)
				continue;

			image[HEIGHT - j][i] |= bitmap->buffer[q * bitmap->width + p];
		}
	}
}

//    init()
//    makeWindow()
//    resizeWindow()
//    ... also most of the processKeys() methods.
//
// The functionality of these methods is assumed by the MinVR apparatus.

DemoVRApp::DemoVRApp(int argc, char** argv) :
		MinVR::VRApp(argc, argv), _scene(bsg::scene()), _shader(new bsg::shaderMgr()), _axesShader(
				new bsg::shaderMgr()), _lights(new bsg::lightList()), _oscillator(0.0f), _testCube(Cube()), _controller(
				StageController()), _stage(-1) {

	_vertexFile = std::string(argv[1]);
	_fragmentFile = std::string(argv[2]);

}

void DemoVRApp::ft_drawString(char * filename, char * text, glm::vec3 color,
	int fontSize, bsg::drawableCube *cube) {
	ft_drawString(filename, text, color, fontSize, 'a', cube);
}

void DemoVRApp::ft_drawString(char * filename, char * text, glm::vec3 color,
		int fontSize, char side, bsg::drawableCube *cube) {
	FT_Library library;
	FT_Face face;

	FT_GlyphSlot slot;
	FT_Matrix matrix; /* transformation matrix */
	FT_Vector pen; /* untransformed origin  */
	FT_Error error;

	double angle;
	int target_height;
	int n, num_chars;

	target_height = HEIGHT;

	num_chars = strlen(text);
	angle = 0.0; // (25.0 / 360) * 3.14159 * 2;      /* use 25 degrees     */

	error = FT_Init_FreeType(&library); /* initialize library */
	/* error handling omitted */

	error = FT_New_Face(library, filename, 0, &face);/* create face object */
	/* error handling omitted */

	/* use 50pt at 100dpi */
	error = FT_Set_Char_Size(face, fontSize * 64, 0, 100, 0); /* set character size */
	/* error handling omitted */

	slot = face->glyph;

	/* set up matrix */
	matrix.xx = (FT_Fixed)(cos(angle) * 0x10000L);
	matrix.xy = (FT_Fixed)(-sin(angle) * 0x10000L);
	matrix.yx = (FT_Fixed)(sin(angle) * 0x10000L);
	matrix.yy = (FT_Fixed)(cos(angle) * 0x10000L);

	/* the pen position in 26.6 cartesian space coordinates; */
	// start at (300,200) relative to the upper left corner
	pen.x = 0 * 64;
	pen.y = (target_height - fontSize) * 64;

	for (n = 0; n < num_chars; n++) {
		/* set transformation */
		FT_Set_Transform(face, &matrix, &pen);

		/* load glyph image into the slot (erase previous one) */
		error = FT_Load_Char(face, text[n], FT_LOAD_RENDER);
		if (error)
			continue; /* ignore errors */

		/* now, draw to our target surface (convert position) */
		draw_bitmap(&slot->bitmap, slot->bitmap_left, target_height - slot->bitmap_top);

		/* increment pen position */
		pen.x += slot->advance.x;
		pen.y += slot->advance.y;
	}

	//show_image();

	FT_Done_Face(face);
	FT_Done_FreeType(library);

	glUniform3f(glGetUniformLocation(_shader->getProgram(), "textColor"), color.x, color.y, color.z);

	cube->setTexture(WIDTH, HEIGHT, (unsigned char *) &image, side);
	memset(image, 0, sizeof image);

	//glGenTextures(1, &texture);
	//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, slot->bitmap.width, slot->bitmap.rows, 0,
	//	GL_ALPHA, GL_UNSIGNED_BYTE, slot->bitmap.buffer);
	//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, WIDTH, HEIGHT,
	//	0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, WIDTH, HEIGHT, 0,
	//	GL_ALPHA, GL_UNSIGNED_BYTE, image);
	//glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	//glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
}
void DemoVRApp::setExamples(vector<Dimension<string> > & dims, Array3D & arr) {
	dims = vector<Dimension<string> >();
	Dimension<string> x = Dimension<string>("Time");
	x.addNonRepValue("2010");
	x.addNonRepValue("2011");
	x.addNonRepValue("2012");
	Dimension<string> y = Dimension<string>("Location");
	y.addNonRepValue("MA");
	y.addNonRepValue("RI");
	y.addNonRepValue("NY");
	Dimension<string> z = Dimension<string>("Type");
	z.addNonRepValue("New");
	z.addNonRepValue("Old");
	z.addNonRepValue("Current");
	dims.push_back(x);
	dims.push_back(y);
	dims.push_back(z);

	int X = x.getSize();
	int Y = y.getSize();
	int Z = z.getSize();

	arr.resize(boost::extents[X][Y][Z]);

	for(int xi = 0; xi < X; xi++){
		for(int yi = 0; yi < Y; yi++){
			for(int zi = 0; zi < Z; zi++){
				arr[xi][yi][zi] = std::rand() / 10000.0;
				std::cout << arr[xi][yi][zi] << " " << std::endl;
			}
		}
	}
//	 int values = 0;
//	  for(arrIndex i = 0; i != 3; ++i)
//	    for(arrIndex j = 0; j != 4; ++j)
//	      for(arrIndex k = 0; k != 2; ++k)
//	        arr[i][j][k] = values++;
}
void DemoVRApp::updateStage() {
	vector<Dimension<string> > dims;
	Array3D arr;
	setExamples(dims, arr);
	_controller.setUpDimsArr(dims, arr, _stage);
	dataToCubes(dims, arr);
}

void DemoVRApp::processKeys(unsigned char key) {

	// Each press of a key changes a dimension by this amount. If you
	// want things to go faster, increase this step.
	float step = 0.5f;

	std::cout << "Key: " << key << std::endl;
	_showCameraPosition();

	// This function processes only the 'normal' keys.  The arrow keys
	// don't appear here, nor mouse events.
	switch (key) {
	case 27:
		exit(0);

		// These next few are for steering the position of the viewer.
	case 'a':
		_scene.addToCameraPosition(glm::vec3(-step, 0.0f, 0.0f));
		break;
	case 'q':
		_scene.addToCameraPosition(glm::vec3(step, 0.0f, 0.0f));
		break;
	case 's':
		_scene.addToCameraPosition(glm::vec3(0.0f, -step, 0.0f));
		break;
	case 'w':
		_scene.addToCameraPosition(glm::vec3(0.0f, step, 0.0f));
		break;
	case 'd':
		_scene.addToCameraPosition(glm::vec3(0.0f, 0.0f, -step));
		break;
	case 'e':
		_scene.addToCameraPosition(glm::vec3(0.0f, 0.0f, step));
		break;

		// These next are for steering the position of where you're looking.
	case 'j':
		_scene.addToLookAtPosition(glm::vec3(-step, 0.0f, 0.0f));
		break;
	case 'u':
		_scene.addToLookAtPosition(glm::vec3(step, 0.0f, 0.0f));
		break;
	case 'k':
		_scene.addToLookAtPosition(glm::vec3(0.0f, -step, 0.0f));
		break;
	case 'i':
		_scene.addToLookAtPosition(glm::vec3(0.0f, step, 0.0f));
		break;
	case 'l':
		_scene.addToLookAtPosition(glm::vec3(0.0f, 0.0f, -step));
		break;
	case 'o':
		_scene.addToLookAtPosition(glm::vec3(0.0f, 0.0f, step));
		break;
	}
}


void DemoVRApp::dataToCubes(vector<Dimension<string> >& dims, Array3D& arr) {
	std::cout << "dataToCubes" << std::endl;
	int numDims = dims.size();
	switch (numDims)
	{
	case 1:
		break;
	case 2:
		break;
	default:
		int xSize = dims[0].getSize();
		int ySize = dims[1].getSize();
		int zSize = dims[2].getSize();

		std::cout << "xSize" << xSize << "ySize" << ySize << "zSize" << zSize << std::endl;

		int maxSize = std::max(std::max(xSize, ySize), zSize);
		float cubeScale = 5.0 / maxSize;
		float xPos = 0.0;
		float yPos = 0.0;
		float zPos = 0.0;
		float step = cubeScale * 1.1;
		for (int x = 0; x < xSize; x++) {
			for (int y = 0; y < ySize; y++) {
				for (int z = 0; z < zSize; z++) {
					std::cout << "Adding Cube" << std::endl;
					bsg::drawableCube *cube = new bsg::drawableCube(_shader, 10,
						glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
					std::string dbl = boost::lexical_cast<std::string>(arr[x][y][z]);
					std::cout << dbl << std::endl;
					std::vector<char> char_array(dbl.begin(), dbl.end());
					char_array.push_back(0);

					ft_drawString("../fonts/times.ttf", &char_array[0],
						glm::vec3(1.0, 1.0, 1.0), 100, cube);
					cube->setScale(cubeScale);
					cube->setPosition(glm::vec3(xPos + (x * step), yPos - (y * step), zPos + (z * step)));
					std::cout << "x: " << x << "/" << xSize << ", y: " << y << "/" << ySize << ", z: " << z << "/" << zSize << std::endl;
					//std::cout << xPos + ((float) x * step) << ", " << yPos - ((float) y * step) << ", " << zPos + ((float) z * step) << std::endl;
					cubes.insert(cube);

					std::cout << "Added cube" << std::endl;
				}
			}
		}
		std::cout << "After added cube..." << std::endl;
		_scene = bsg::scene();
		_shader = new bsg::shaderMgr();
		_axesShader = new bsg::shaderMgr();
		_lights = new bsg::lightList();
		_oscillator = 0.0f;
		_initializeScene();
		// exit(0);
		_scene.prepare();
		break;
	}
}

// This contains a bunch of sanity checks from the graphics
// initialization of demo2.cpp.  They are still useful with MinVR.
void DemoVRApp::_checkContext() {
// There is one more graphics library used here, called GLEW.  This
// library sorts through the various OpenGL updates and changes and
// allows a user to pretend that it's all a consistent and simple
// system.  The 'core profile' refers to some modern OpenGL
// enhancements that are not so modern as of 2017.  Set this to true
// to get those enhancements.
	glewExperimental = true; // Needed for core profile
	if (glewInit() != GLEW_OK) {
		throw std::runtime_error("Failed to initialize GLEW");
	}

// Now that we have a graphics context, let's look at what's inside.
	std::cout << "Hardware check: " << glGetString(GL_RENDERER) // e.g. Intel 3000 OpenGL Engine
			<< " / " << glGetString(GL_VERSION)    // e.g. 3.2 INTEL-8.0.61
			<< std::endl;

	if (glewIsSupported("GL_VERSION_2_1")) {
		std::cout << "Software check: Ready for OpenGL 2.1." << std::endl;
	} else {
		throw std::runtime_error("Software check: OpenGL 2.1 not supported.");
	}

// This is the background color of the viewport.
	glClearColor(1.0, 1.0, 1.0, 0.0);

// Now we're ready to start issuing OpenGL calls.  Start by enabling
// the modes we want.  The DEPTH_TEST is how you get hidden faces.
	glEnable(GL_DEPTH_TEST);

	if (glIsEnabled(GL_DEPTH_TEST)) {
		std::cout << "Depth test enabled" << std::endl;
	} else {
		std::cout << "No depth test enabled" << std::endl;
	}

// This is just a performance enhancement that allows OpenGL to
// ignore faces that are facing away from the camera.
	glEnable(GL_CULL_FACE);
	glLineWidth(1);
	glEnable(GL_LINE_SMOOTH);

}

// Just a little debug function so that a user can see what's going on
// in a non-graphical sense.
void DemoVRApp::_showCameraPosition() {

	std::cout << "Camera is at (" << _scene.getCameraPosition().x << ", " << _scene.getCameraPosition().y << ", "
			<< _scene.getCameraPosition().z << ")... ";
	std::cout << "looking at (" << _scene.getLookAtPosition().x << ", " << _scene.getLookAtPosition().y << ", "
			<< _scene.getLookAtPosition().z << ")." << std::endl;
}

void DemoVRApp::_initializeScene() {

// Create a list of lights.  If the shader you're using doesn't use
// lighting, and the shapes don't have textures, this is irrelevant.
	_lights->addLight(glm::vec4(0.0f, 0.0f, 3.0f, 1.0f), glm::vec4(1.0f, 1.0f, 0.0f, 0.0f));

// Create a shader manager and load the light list.
	_shader->addLights(_lights);

// Add the shaders to the manager, first the vertex shader...

	_shader->addShader(bsg::GLSHADER_VERTEX, _vertexFile);
	_shader->addShader(bsg::GLSHADER_FRAGMENT, _fragmentFile);

// The shaders are loaded, now compile them.
	_shader->compileShaders();

	_cube = new bsg::drawableCube(_shader, 10, glm::vec4(1.0f, 1.0f, 1.0f, 0.0f));
	_cube->setScale(2.0f);

	_rectangle = new bsg::drawableRectangle(_shader, 9.0f, 9.0f, 2);

	// Now add our rectangle to the scene.
	//_scene.addObject(_rectangle);
	//_scene.addObject(_cube);

	_axesShader->addShader(bsg::GLSHADER_VERTEX, "../shaders/shader2.vp");
	_axesShader->addShader(bsg::GLSHADER_FRAGMENT, "../shaders/shader.fp");
	_axesShader->compileShaders();

	_axesSet = new bsg::drawableAxes(_axesShader, 100.0f);

	// Now add the axes.
	_scene.addObject(_axesSet);
	std::cout << "cubes: " << cubes.size() << std::endl;
	if (cubes.size()) {
		for each (bsg::drawableCube *cb in cubes)
		{
			std::cout << "added cube" << std::endl;
			_scene.addObject(cb);
		}
		cubes.clear();
	}


	// Some fonts cause segfaults for no good reason on some platforms (Mac). For example, '2', '3', and '5' in 
	// Arial causes the crash, but other characters/fonts do not. Just use times.

	/*ft_drawString("../fonts/times.ttf", "Lorem ipsum dolor",
			glm::vec3(1.0, 1.0, 1.0), 20, 'f', _cube);
	ft_drawString("../fonts/times.ttf", "1", glm::vec3(0.0, 1.0, 1.0), 100,
			'b', _cube);
	ft_drawString("../fonts/times.ttf", "2", glm::vec3(0.0, 0.0, 1.0), 100,
			'u', _cube);
	ft_drawString("../fonts/times.ttf", "0123456789", glm::vec3(0.0, 1.0, 0.0),
			100, 'd', _cube);
	ft_drawString("../fonts/times.ttf", "times", glm::vec3(1.0, 1.0, 0.0), 100,
			'l', _cube);
	ft_drawString("../fonts/times.ttf", "value", glm::vec3(1.0, 1.0, 1.0), 100,
			'r', _cube);*/
//	FTDrawString("../fonts/times.ttf", "Lorem ipsum dolor", glm::vec3(1.0, 1.0, 1.0), 20, 'f');
//	FTDrawString("../fonts/times.ttf", "1", glm::vec3(0.0, 1.0, 1.0), 100, 'b');
//	FTDrawString("../fonts/times.ttf", "2", glm::vec3(0.0, 0.0, 1.0), 100, 'u');
//	FTDrawString("../fonts/times.ttf", "0123456789", glm::vec3(0.0, 1.0, 0.0), 100, 'd');
//	FTDrawString("../fonts/times.ttf", "times", glm::vec3(1.0, 1.0, 0.0), 100, 'l');
//	FTDrawString("../fonts/times.ttf", "value", glm::vec3(1.0, 1.0, 1.0), 100, 'r');
// so far so good
}

/// The MinVR apparatus invokes this method whenever there is a new
/// event to process.
void DemoVRApp::onVREvent(const MinVR::VREvent &event) {

	float step = 0.5f;
	float stepAngle = 5.0f / 360.0f;

// Quit if the escape button is pressed

	if (event.getName() == "KbdEsc_Down") {
		shutdown();
	} else if (event.getName() == "FrameStart") {
		_oscillator = event.getDataAsFloat("ElapsedSeconds");
	} else if (event.getName() == "KbdLeft_Down" || event.getName() == "KbdDown_Down") { // && event.getDataAsCharArray("EventString")[0] == 'D'
		if (_stage > 0)
			_stage--;
		updateStage();
	} else if (event.getName() == "KbdRight_Down" || event.getName() == "KbdUp_Down") { // && event.getDataAsCharArray("EventString")[0] == 'D'
		_stage++;
		updateStage();
	}
	else if (event.getName().length() > 4 && event.getName().substr(0, 3) == "Kbd") {
		std::cout << event.getName() << std::endl;
		processKeys(event.getName().at(3));
	}
}

/// brief Set the render context.
///
/// The onVRRender methods are the heart of the MinVR rendering
/// apparatus.  Some render calls are shared among multiple views,
/// for example a stereo view has two renders, with the same render
/// context.
void DemoVRApp::onVRRenderGraphicsContext(const MinVR::VRGraphicsState &renderState) {

// Check if this is the first call.  If so, do some initialization.
	if (renderState.isInitialRenderCall()) {
		_checkContext();
		_initializeScene();
		// exit(0);
		_scene.prepare();
	}

}

/// brief Draw the image.
///
/// This is the heart of any graphics program, the render function.
/// It is called each time through the main graphics loop, and
/// re-draws the scene according to whatever has changed since the
/// last time it was drawn.
void DemoVRApp::onVRRenderGraphics(const MinVR::VRGraphicsState &renderState) {
// Only draw if the application is still running.
	if (isRunning()) {
		// If you want to adjust the positions of the various objects in
		// your scene, you can do that here.
		glm::vec3 pos = glm::vec3(0, 0, 0);      //_rectangle->getPosition();
		pos.x = 2.0f * sin(_oscillator);
		pos.y = 2.0f * cos(_oscillator);
		pos.z = -4.0f;
		_rectangle->setPosition(pos);

		// Move the cube forward and have it circle counterclockwise
		pos.z = 0.0f;
		float temp = pos.x;
		pos.x = pos.y;
		pos.y = temp;
		_cube->setPosition(pos);
		_cube->setScale(1.0);

		_cube->setRotation(glm::vec3(cos(_oscillator), cos(_oscillator) * M_PI, 0.0f));
		// Now the preliminaries are done, on to the actual drawing.

		// First clear the display.
		glClear(
		GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

		// Second the load() step.  We let MinVR give us the projection
		// matrix from the render state argument to this method.
		const float* pm = renderState.getProjectionMatrix();
		glm::mat4 projMatrix = glm::mat4(pm[0], pm[1], pm[2], pm[3], pm[4], pm[5], pm[6], pm[7], pm[8], pm[9], pm[10],
				pm[11], pm[12], pm[13], pm[14], pm[15]);
		_scene.load();



		// The draw step.  We let MinVR give us the view matrix.
		const float* vm = renderState.getViewMatrix();
		glm::mat4 viewMatrix = glm::mat4(vm[0], vm[1], vm[2], vm[3], vm[4], vm[5], vm[6], vm[7], vm[8], vm[9], vm[10],
				vm[11], vm[12], vm[13], vm[14], vm[15]);

		_scene.draw(_scene.getViewMatrix(), _scene.getProjMatrix());

		//bsg::bsgUtils::printMat("view", viewMatrix);
		//bsg::bsgUtils::printMat("proj", projMatrix);

	}

}

