//
// impressionistUI.h
//
// The user interface part for the program.
//


#include <FL/fl_ask.h>

#include <math.h>

#include "impressionistUI.h"
#include "impressionistDoc.h"

/*
//------------------------------ Widget Examples -------------------------------------------------
Here is some example code for all of the widgets that you may need to add to the 
project.  You can copy and paste these into your code and then change them to 
make them look how you want.  Descriptions for all of the widgets here can be found 
in links on the fltk help session page.

//---------Window/Dialog and Menubar-----------------------------------
	
	//----To install a window--------------------------
	Fl_Window* myWindow = new Fl_Window(600, 300, "MyWindow");
		myWindow->user_data((void*)(this));	// record self to be used by static callback functions
		
		// install menu bar
		myMenubar = new Fl_Menu_Bar(0, 0, 600, 25);
		Fl_Menu_Item ImpressionistUI::myMenuItems[] = {
			{ "&File",		0, 0, 0, FL_SUBMENU },
				{ "&Load...",	FL_ALT + 'l', (Fl_Callback *)ImpressionistUI::cb_load },
				{ "&Save...",	FL_ALT + 's', (Fl_Callback *)ImpressionistUI::cb_save }.
				{ "&Quit",			FL_ALT + 'q', (Fl_Callback *)ImpressionistUI::cb_exit },
				{ 0 },
			{ "&Edit",		0, 0, 0, FL_SUBMENU },
				{ "&Copy",FL_ALT + 'c', (Fl_Callback *)ImpressionistUI::cb_copy, (void *)COPY },
				{ "&Cut",	FL_ALT + 'x', (Fl_Callback *)ImpressionistUI::cb_cut, (void *)CUT },
				{ "&Paste",	FL_ALT + 'v', (Fl_Callback *)ImpressionistUI::cb_paste, (void *)PASTE },
				{ 0 },
			{ "&Help",		0, 0, 0, FL_SUBMENU },
				{ "&About",	FL_ALT + 'a', (Fl_Callback *)ImpressionistUI::cb_about },
				{ 0 },
			{ 0 }
		};
		myMenubar->menu(myMenuItems);
    m_mainWindow->end();

	//----The window callback--------------------------
	// One of the callbacks
	void ImpressionistUI::cb_load(Fl_Menu_* o, void* v) 
	{	
		ImpressionistDoc *pDoc=whoami(o)->getDocument();

		char* newfile = fl_file_chooser("Open File?", "*.bmp", pDoc->getImageName() );
		if (newfile != NULL) {
			pDoc->loadImage(newfile);
		}
	}


//------------Slider---------------------------------------

	//----To install a slider--------------------------
	Fl_Value_Slider * mySlider = new Fl_Value_Slider(10, 80, 300, 20, "My Value");
	mySlider->user_data((void*)(this));	// record self to be used by static callback functions
	mySlider->type(FL_HOR_NICE_SLIDER);
    mySlider->labelfont(FL_COURIER);
    mySlider->labelsize(12);
	mySlider->minimum(1);
	mySlider->maximum(40);
	mySlider->step(1);
	mySlider->value(m_nMyValue);
	mySlider->align(FL_ALIGN_RIGHT);
	mySlider->callback(cb_MyValueSlides);

	//----The slider callback--------------------------
	void ImpressionistUI::cb_MyValueSlides(Fl_Widget* o, void* v)
	{
		((ImpressionistUI*)(o->user_data()))->m_nMyValue=int( ((Fl_Slider *)o)->value() ) ;
	}
	

//------------Choice---------------------------------------
	
	//----To install a choice--------------------------
	Fl_Choice * myChoice = new Fl_Choice(50,10,150,25,"&myChoiceLabel");
	myChoice->user_data((void*)(this));	 // record self to be used by static callback functions
	Fl_Menu_Item ImpressionistUI::myChoiceMenu[3+1] = {
	  {"one",FL_ALT+'p', (Fl_Callback *)ImpressionistUI::cb_myChoice, (void *)ONE},
	  {"two",FL_ALT+'l', (Fl_Callback *)ImpressionistUI::cb_myChoice, (void *)TWO},
	  {"three",FL_ALT+'c', (Fl_Callback *)ImpressionistUI::cb_myChoice, (void *)THREE},
	  {0}
	};
	myChoice->menu(myChoiceMenu);
	myChoice->callback(cb_myChoice);
	
	//-----The choice callback-------------------------
	void ImpressionistUI::cb_myChoice(Fl_Widget* o, void* v)
	{
		ImpressionistUI* pUI=((ImpressionistUI *)(o->user_data()));
		ImpressionistDoc* pDoc=pUI->getDocument();

		int type=(int)v;

		pDoc->setMyType(type);
	}


//------------Button---------------------------------------

	//---To install a button---------------------------
	Fl_Button* myButton = new Fl_Button(330,220,50,20,"&myButtonLabel");
	myButton->user_data((void*)(this));   // record self to be used by static callback functions
	myButton->callback(cb_myButton);

	//---The button callback---------------------------
	void ImpressionistUI::cb_myButton(Fl_Widget* o, void* v)
	{
		ImpressionistUI* pUI=((ImpressionistUI*)(o->user_data()));
		ImpressionistDoc* pDoc = pUI->getDocument();
		pDoc->startPainting();
	}


//---------Light Button------------------------------------
	
	//---To install a light button---------------------
	Fl_Light_Button* myLightButton = new Fl_Light_Button(240,10,150,25,"&myLightButtonLabel");
	myLightButton->user_data((void*)(this));   // record self to be used by static callback functions
	myLightButton->callback(cb_myLightButton);

	//---The light button callback---------------------
	void ImpressionistUI::cb_myLightButton(Fl_Widget* o, void* v)
	{
		ImpressionistUI *pUI=((ImpressionistUI*)(o->user_data()));

		if (pUI->myBool==TRUE) pUI->myBool=FALSE;
		else pUI->myBool=TRUE;
	}

//----------Int Input--------------------------------------

    //---To install an int input-----------------------
	Fl_Int_Input* myInput = new Fl_Int_Input(200, 50, 5, 5, "&My Input");
	myInput->user_data((void*)(this));   // record self to be used by static callback functions
	myInput->callback(cb_myInput);

	//---The int input callback------------------------
	void ImpressionistUI::cb_myInput(Fl_Widget* o, void* v)
	{
		((ImpressionistUI*)(o->user_data()))->m_nMyInputValue=int( ((Fl_Int_Input *)o)->value() );
	}

//------------------------------------------------------------------------------------------------
*/

//------------------------------------- Help Functions --------------------------------------------

//------------------------------------------------------------
// This returns the UI, given the menu item.  It provides a
// link from the menu items to the UI
//------------------------------------------------------------
ImpressionistUI* ImpressionistUI::whoami(Fl_Menu_* o)	
{
	return ( (ImpressionistUI*)(o->parent()->user_data()) );
}


//--------------------------------- Callback Functions --------------------------------------------

//------------------------------------------------------------------
// Brings up a file chooser and then loads the chosen image
// This is called by the UI when the load image menu item is chosen
//------------------------------------------------------------------
void ImpressionistUI::cb_load_image(Fl_Menu_* o, void* v) 
{
	ImpressionistDoc *pDoc=whoami(o)->getDocument();

	char* newfile = fl_file_chooser("Open File?", "*.bmp", pDoc->getImageName() );
	if (newfile != NULL) {
		pDoc->loadImage(newfile);
	}
}


//------------------------------------------------------------------
// Brings up a file chooser and then saves the painted image
// This is called by the UI when the save image menu item is chosen
//------------------------------------------------------------------
void ImpressionistUI::cb_save_image(Fl_Menu_* o, void* v) 
{
	ImpressionistDoc *pDoc=whoami(o)->getDocument();

	char* newfile = fl_file_chooser("Save File?", "*.bmp", "save.bmp" );
	if (newfile != NULL) {
		pDoc->saveImage(newfile);
	}
}

//-------------------------------------------------------------
// Brings up the paint dialog
// This is called by the UI when the brushes menu item
// is chosen
//-------------------------------------------------------------
void ImpressionistUI::cb_brushes(Fl_Menu_* o, void* v) 
{
	whoami(o)->m_brushDialog->show();
}

//------------------------------------------------------------
// Undo the paintview canvas.
// Called by the UI when the undo menu item is chosen
//------------------------------------------------------------
void ImpressionistUI::cb_undo(Fl_Menu_* o, void* v)
{
	ImpressionistDoc* pDoc=whoami(o)->getDocument();

	if (!pDoc->m_ucPainting_Undo.empty()) {
		delete [] pDoc->m_ucPainting;
		pDoc->m_ucPainting = pDoc->m_ucPainting_Undo.top();
		pDoc->m_ucPainting_Undo.pop();

		pDoc->m_pUI->m_paintView->refresh();
	}
}

//------------------------------------------------------------
// Clears the paintview canvas.
// Called by the UI when the clear canvas menu item is chosen
//------------------------------------------------------------
void ImpressionistUI::cb_clear_canvas(Fl_Menu_* o, void* v)
{
	ImpressionistDoc* pDoc=whoami(o)->getDocument();

	pDoc->clearCanvas();
}

//------------------------------------------------------------
// Causes the Impressionist program to exit
// Called by the UI when the quit menu item is chosen
//------------------------------------------------------------
void ImpressionistUI::cb_exit(Fl_Menu_* o, void* v) 
{
	whoami(o)->m_mainWindow->hide();
	whoami(o)->m_brushDialog->hide();
	whoami(o)->m_colorDialog->hide();
	whoami(o)->m_DissolveDialog->hide();
}

//------------------------------------------------------------
// Swaps the paintview canvas.
// Called by the UI when the swap canvas menu item is chosen
//------------------------------------------------------------
void ImpressionistUI::cb_swap_canvas(Fl_Menu_* o, void* v)
{
	ImpressionistDoc* pDoc=whoami(o)->getDocument();

	unsigned char* m_tmp = pDoc->m_ucBitmap;

	pDoc->m_ucBitmap = pDoc->m_ucPainting;
	pDoc->m_ucPainting = m_tmp;

	pDoc->m_pUI->m_origView->refresh();
	pDoc->m_pUI->m_paintView->refresh();
}

//Added By Ryan Started ( File)
void ImpressionistUI::cb_colors(Fl_Menu_* o, void* v)
{
	whoami(o)->m_colorDialog->show();
}
void ImpressionistUI::cb_paintly(Fl_Menu_* o, void* v)
{
}
void ImpressionistUI::cb_load_edge_image(Fl_Menu_* o, void* v)
{
}
void ImpressionistUI::cb_load_another_image(Fl_Menu_* o, void* v)
{
}
//Added By Ryan Ended (File)

/* (Tim) Dissolve An Image Dialog [START] */
void ImpressionistUI::cb_Dissolve(Fl_Menu_* o, void* v)
{
	whoami(o)->m_DissolveDialog->show();
}
/* (Tim) Dissolve An Image Dialog [END] */

//Added By Ryan Started (Display)
void ImpressionistUI::cb_original_image(Fl_Menu_* o, void* v)
{
}
void ImpressionistUI::cb_edge_image(Fl_Menu_* o, void* v)
{
}
void ImpressionistUI::cb_another_image(Fl_Menu_* o, void* v)
{
}
//Added By Ryan Ended (Display)

//Added By Ryan Started (Options)
void ImpressionistUI::cb_faster(Fl_Menu_* o, void* v)
{
}
void ImpressionistUI::cb_safer(Fl_Menu_* o, void* v)
{
}
//Added By Ryan Ended (Options)


//-----------------------------------------------------------
// Brings up an about dialog box
// Called by the UI when the about menu item is chosen
//-----------------------------------------------------------
void ImpressionistUI::cb_about(Fl_Menu_* o, void* v) 
{
	fl_message("Impressionist FLTK version for CS341, Spring 2002");
}

//------- UI should keep track of the current for all the controls for answering the query from Doc ---------
//-------------------------------------------------------------
// Sets the type of brush to use to the one chosen in the brush 
// choice.  
// Called by the UI when a brush is chosen in the brush choice
//-------------------------------------------------------------
void ImpressionistUI::cb_brushChoice(Fl_Widget* o, void* v)
{
	ImpressionistUI* pUI=((ImpressionistUI *)(o->user_data()));
	ImpressionistDoc* pDoc=pUI->getDocument();

	int type=(int)v;


	pDoc->setBrushType(type);
}

//Sets the line Stroke_direction  to the one chosen in the stroke 
//direction choice
//Called by the UI when the brush is chosen in the bsush choice
void ImpressionistUI::cb_strokeDirection(Fl_Widget* o, void* v)
{
	ImpressionistUI* pUI=((ImpressionistUI *)(o->user_data()));
	ImpressionistDoc* pDoc=pUI->getDocument();

	int type=(int)v;

	pDoc->setStrokeDirect(type);
}

//------------------------------------------------------------
// Clears the paintview canvas.
// Called by the UI when the clear canvas button is pushed
//------------------------------------------------------------
void ImpressionistUI::cb_clear_canvas_button(Fl_Widget* o, void* v)
{
	ImpressionistDoc * pDoc = ((ImpressionistUI*)(o->user_data()))->getDocument();

	pDoc->clearCanvas();
}


//-----------------------------------------------------------
// Updates the brush size to use from the value of the size
// slider
// Called by the UI when the size slider is moved
//-----------------------------------------------------------
void ImpressionistUI::cb_sizeSlides(Fl_Widget* o, void* v)
{
	((ImpressionistUI*)(o->user_data()))->m_nSize=int( ((Fl_Slider *)o)->value() ) ;
}

//Added By Ryan STARTED
//Update the line width to use
//slider
//Called by the UI when the size of slider is moved
void ImpressionistUI::cb_line_widthSlides(Fl_Widget* o, void* v)
{
	((ImpressionistUI*)(o->user_data()))->m_nLine_width=int( ((Fl_Slider *)o)->value() ) ;
}
//Added By Ryan ENDED

//Added By Ryan STARTED
//Update the line angle to use
//slider
//Called by the UI when the size of slider is moved
void ImpressionistUI::cb_line_angleSlides(Fl_Widget* o, void* v)
{
	((ImpressionistUI*)(o->user_data()))->m_nLine_angle=int( ((Fl_Slider *)o)->value() ) ;
}
//Added By Ryan ENDED

//Added By Ryan STARTED
//Update the alpha to use
//slider
//Called by the UI when the size of slider is moved
void ImpressionistUI::cb_alphaSlides(Fl_Widget* o, void* v)
{
	((ImpressionistUI*)(o->user_data()))->m_nAlpha=double(((Fl_Slider *)o)->value());
}
//Added By Ryan ENDED

/* (Tim) Color Dialog [START] */
//Update the R channel
void ImpressionistUI::cb_rColorSlides(Fl_Widget* o, void* v)
{
	double brightness = ((ImpressionistUI*)(o->user_data()))->m_nBrightnessColor;

	((ImpressionistUI*)(o->user_data()))->m_nRColor = (double(((Fl_Slider *)o)->value())/brightness)/255.0;
}
//Update the G channel
void ImpressionistUI::cb_gColorSlides(Fl_Widget* o, void* v)
{
	double brightness = ((ImpressionistUI*)(o->user_data()))->m_nBrightnessColor;

	((ImpressionistUI*)(o->user_data()))->m_nGColor = (double(((Fl_Slider *)o)->value())/brightness)/255.0;
}
//Update the B channel
void ImpressionistUI::cb_bColorSlides(Fl_Widget* o, void* v)
{
	double brightness = ((ImpressionistUI*)(o->user_data()))->m_nBrightnessColor;

	((ImpressionistUI*)(o->user_data()))->m_nBColor = (double(((Fl_Slider *)o)->value())/brightness)/255.0;
}
//Update the Brightness
void ImpressionistUI::cb_brightnessColorSlides(Fl_Widget* o, void* v)
{
	double brightness = ((ImpressionistUI*)(o->user_data()))->m_nBrightnessColor = ((Fl_Slider *)o)->value();

	// get the RGB values
	double rColor = ((ImpressionistUI*)(o->user_data()))->m_nRColor;
	double gColor = ((ImpressionistUI*)(o->user_data()))->m_nGColor;
	double bColor = ((ImpressionistUI*)(o->user_data()))->m_nBColor;
	// change RGB sliders' maximums and values
	((ImpressionistUI*)(o->user_data()))->m_rColorSlider->maximum(int(255*brightness));
	((ImpressionistUI*)(o->user_data()))->m_rColorSlider->value(int(255*rColor*brightness));
	((ImpressionistUI*)(o->user_data()))->m_gColorSlider->maximum(int(255*brightness));
	((ImpressionistUI*)(o->user_data()))->m_gColorSlider->value(int(255*gColor*brightness));
	((ImpressionistUI*)(o->user_data()))->m_bColorSlider->maximum(int(255*brightness));
	((ImpressionistUI*)(o->user_data()))->m_bColorSlider->value(int(255*bColor*brightness));
}
/* (Tim) Color Dialog [END] */

/* (Tim) Dissolve An Image Dialog [START] */
// choose alph
void ImpressionistUI::cb_Dissolve_AlphaSlides(Fl_Widget* o, void* v)
{
	((ImpressionistUI*)(o->user_data()))->m_nDissolve_Alpha = ((Fl_Slider *)o)->value();
}

// choose image
void ImpressionistUI::cb_Dissolve_LoadImage(Fl_Widget* o, void* v)
{
	ImpressionistDoc* pDoc = ((ImpressionistUI*)(o->user_data()))->getDocument();

	if (!pDoc->m_ucBitmap) {
		fl_alert("Please load a background image first.");
		return;
	}

	char* newImage = fl_file_chooser("Dissolve Image?", "*.bmp", pDoc->getImageName() );
	if (newImage != NULL) {
		pDoc->load_DissolveImage(newImage);
	}
}
/* (Tim) Dissolve An Image Dialog [END] */

//---------------------------------- per instance functions --------------------------------------

//------------------------------------------------
// Return the ImpressionistDoc used
//------------------------------------------------
ImpressionistDoc* ImpressionistUI::getDocument()
{
	return m_pDoc;
}

//------------------------------------------------
// Draw the main window
//------------------------------------------------
void ImpressionistUI::show() {
	m_mainWindow->show();
	m_paintView->show();
	m_origView->show();
}

//------------------------------------------------
// Change the paint and original window sizes to 
// w by h
//------------------------------------------------
void ImpressionistUI::resize_windows(int w, int h) {
	m_paintView->size(w,h);
	m_origView->size(w,h);
}

//------------------------------------------------ 
// Set the ImpressionistDoc used by the UI to 
// communicate with the brushes 
//------------------------------------------------
void ImpressionistUI::setDocument(ImpressionistDoc* doc)
{
	m_pDoc = doc;

	m_origView->m_pDoc = doc;
	m_paintView->m_pDoc = doc;
}

//------------------------------------------------
// Return the brush size
//------------------------------------------------
int ImpressionistUI::getSize()
{
	return m_nSize;
}
//ADDED BY RYAN STARTED
int ImpressionistUI::getLineWidth()
{
	return m_nLine_width;
}

int ImpressionistUI::getLineAngle()
{
	return m_nLine_angle;
}

double ImpressionistUI::getAlpha()
{
	return m_nAlpha;
}

//ADDED BY RYAN ENDED

/* (Tim) Color Dialog [START] */
double ImpressionistUI::getRColor()
{
	return m_nRColor;
}

double ImpressionistUI::getGColor()
{
	return m_nGColor;
}

double ImpressionistUI::getBColor()
{
	return m_nBColor;
}

double ImpressionistUI::getBrightnessColor()
{
	return m_nBrightnessColor;
}
/* (Tim) Color Dialog [END] */

/* (Tim) Dissolve An Image Dialog [START] */
double ImpressionistUI::get_Dissolve_Alpha() {
	return m_nDissolve_Alpha;
}
/* (Tim) Dissolve An Image Dialog [END] */

//-------------------------------------------------
// Set the brush size
//-------------------------------------------------
void ImpressionistUI::setSize( int size )
{
	m_nSize=size;

	if (size<=40&&size>=0) 
		m_BrushSizeSlider->value(m_nSize);
}

//ADDED BY RYAN STARTED
void ImpressionistUI::setLineWidth(int width)
{
	m_nLine_width=width;

	if (width<40&&width>=0)
		m_LineWidthSlider->value(m_nLine_width);
}

void ImpressionistUI::setLineAngle(int angle)
{
	angle=angle%360;
	m_nLine_angle=angle;
	m_LineAngleSlider->value(m_nLine_angle);
}







//ADDED BY RYAN ENDED
// Main menu definition
Fl_Menu_Item ImpressionistUI::menuitems[] = {
	{ "&File",		0, 0, 0, FL_SUBMENU },
		{ "&Load Image...",	FL_ALT + 'l', (Fl_Callback *)ImpressionistUI::cb_load_image },
		{ "&Save Image...",	FL_ALT + 's', (Fl_Callback *)ImpressionistUI::cb_save_image },
		{ "&Brushes...",	FL_ALT + 'b', (Fl_Callback *)ImpressionistUI::cb_brushes }, 
		{ "Undo",	FL_CTRL + 'z', (Fl_Callback *)ImpressionistUI::cb_undo }, 
		{ "S&wap Canvas", FL_ALT + 'w', (Fl_Callback *)ImpressionistUI::cb_swap_canvas },
		{ "&Clear Canvas", FL_ALT + 'c', (Fl_Callback *)ImpressionistUI::cb_clear_canvas, 0, FL_MENU_DIVIDER },

	//Added By Ryan Started (File)
		{ "Colors", FL_ALT+'k',(Fl_Callback *)ImpressionistUI::cb_colors},
		{ "Paintly", FL_ALT+'p',(Fl_Callback *)ImpressionistUI::cb_paintly, 0, FL_MENU_DIVIDER },

		{ "Load Edge Image", FL_ALT+'e',(Fl_Callback *)ImpressionistUI::cb_load_edge_image},
		{ "Load Another Image", FL_ALT+'a',(Fl_Callback *)ImpressionistUI::cb_load_another_image, 0, FL_MENU_DIVIDER},

		{ "Dissol&ve An Image", FL_ALT+'v',(Fl_Callback *)ImpressionistUI::cb_Dissolve, 0, FL_MENU_DIVIDER },
	//Added By Ryan Ended
		
		{ "&Quit",			FL_ALT + 'q', (Fl_Callback *)ImpressionistUI::cb_exit },
		{ 0 },

	//Added By Ryan Started (Display)
	{ "&Display",		0, 0, 0, FL_SUBMENU },
		{ "&Original Image...",	FL_ALT + 'o', (Fl_Callback *)ImpressionistUI::cb_original_image },
		{ "&Edge Image",	FL_ALT + 'e', (Fl_Callback *)ImpressionistUI::cb_edge_image },
		{ "&Another Image",	FL_ALT + 'a', (Fl_Callback *)ImpressionistUI::cb_another_image }, 
		{ 0 },
	//Added By Ryan Ended

	//Added By Ryan Started (Options)
	{ "&Options",		0, 0, 0, FL_SUBMENU },
		{ "&Faster",	FL_ALT + 'f', (Fl_Callback *)ImpressionistUI::cb_faster },
		{ "&Safer",	FL_ALT + 's', (Fl_Callback *)ImpressionistUI::cb_safer },
		{ 0 },
	//Added By Ryan Ended

	{ "&Help",		0, 0, 0, FL_SUBMENU },
		{ "&About",	FL_ALT + 'a', (Fl_Callback *)ImpressionistUI::cb_about },
		{ 0 },

	{ 0 }
};

// Brush choice menu definition
Fl_Menu_Item ImpressionistUI::brushTypeMenu[NUM_BRUSH_TYPE+1] = {
  {"Points",			FL_ALT+'p', (Fl_Callback *)ImpressionistUI::cb_brushChoice, (void *)BRUSH_POINTS},
  {"Lines",				FL_ALT+'l', (Fl_Callback *)ImpressionistUI::cb_brushChoice, (void *)BRUSH_LINES},
  {"Circles",			FL_ALT+'c', (Fl_Callback *)ImpressionistUI::cb_brushChoice, (void *)BRUSH_CIRCLES},
  {"Scattered Points",	FL_ALT+'q', (Fl_Callback *)ImpressionistUI::cb_brushChoice, (void *)BRUSH_SCATTERED_POINTS},
  {"Scattered Lines",	FL_ALT+'m', (Fl_Callback *)ImpressionistUI::cb_brushChoice, (void *)BRUSH_SCATTERED_LINES},
  {"Scattered Circles",	FL_ALT+'d', (Fl_Callback *)ImpressionistUI::cb_brushChoice, (void *)BRUSH_SCATTERED_CIRCLES, FL_MENU_DIVIDER},
  {"&Greyscale",	FL_ALT+'g', (Fl_Callback *)ImpressionistUI::cb_brushChoice, (void *)BRUSH_GREYSCALE},
  {"Con&trast",	FL_ALT+'t', (Fl_Callback *)ImpressionistUI::cb_brushChoice, (void *)BRUSH_CONTRAST},
  {0}
};

//Brush direction menu definition
Fl_Menu_Item ImpressionistUI::strokeDirectionMenu[NUM_STROKE_DIRECTION+1] = {
	{"Slider/Right Mouse",	FL_ALT+'s', (Fl_Callback *)ImpressionistUI::cb_strokeDirection, (void* )STROKE_SLIDER},
	{"Gradient",			FL_ALT+'g', (Fl_Callback *)ImpressionistUI::cb_strokeDirection, (void* )STROKE_GRAD},
	{"Brush Direction",		FL_ALT+'b', (Fl_Callback *)ImpressionistUI::cb_strokeDirection, (void* )STROKE_BRUSH},
	{0}
};




//----------------------------------------------------
// Constructor.  Creates all of the widgets.
// Add new widgets here
//----------------------------------------------------
ImpressionistUI::ImpressionistUI() {
	// Create the main window
	m_mainWindow = new Fl_Window(600, 300, "Impressionist");
		m_mainWindow->user_data((void*)(this));	// record self to be used by static callback functions
		// install menu bar
		m_menubar = new Fl_Menu_Bar(0, 0, 600, 25);
		m_menubar->menu(menuitems);

		// Create a group that will hold two sub windows inside the main
		// window
		Fl_Group* group = new Fl_Group(0, 25, 600, 275);

			// install paint view window
			m_paintView = new PaintView(300, 25, 300, 275, "This is the paint view");//0jon
			m_paintView->box(FL_DOWN_FRAME);

			// install original view window
			m_origView = new OriginalView(0, 25, 300, 275, "This is the orig view");//300jon
			m_origView->box(FL_DOWN_FRAME);
			m_origView->deactivate();

		group->end();
		Fl_Group::current()->resizable(group);
    m_mainWindow->end();

	// init values STARTED
	m_nSize = 10;
	m_nLine_width=1;
	m_nLine_angle=0;
	m_nAlpha=1;
	threshold=35;

	//added By Ryan STARTED

	//added By Ryan ENDED

	/* (Tim) Color Dialog [START] */
	m_nRColor = 1.0;
	m_nGColor = 1.0;
	m_nBColor = 1.0;
	m_nBrightnessColor = 1.0;
	/* (Tim) Color Dialog [END] */

	/* (Tim) Dissolve Image Dialog [START] */
	m_nDissolve_Alpha = 0.5;
	/* (Tim) Dissolve Image Dialog [END] */
	// init values ENDED

	// brush dialog definition
	m_brushDialog = new Fl_Window(400, 325, "Brush Dialog");
		// Add a brush type choice to the dialog
		m_BrushTypeChoice = new Fl_Choice(50,10,150,25,"&Brush");
		m_BrushTypeChoice->user_data((void*)(this));	// record self to be used by static callback functions
		m_BrushTypeChoice->menu(brushTypeMenu);
		m_BrushTypeChoice->callback(cb_brushChoice);

		m_ClearCanvasButton = new Fl_Button(240,10,150,25,"&Clear Canvas");
		m_ClearCanvasButton->user_data((void*)(this));
		m_ClearCanvasButton->callback(cb_clear_canvas_button);

		m_StrokeDirectionChoice = new Fl_Choice(110,40,160,25,"&Stroke Direction");
		m_StrokeDirectionChoice->user_data((void*)(this));
		m_StrokeDirectionChoice->menu(strokeDirectionMenu);
		m_StrokeDirectionChoice->callback(cb_strokeDirection);

		// Add line direction function to the software



		// Add brush size slider to the dialog 
		m_BrushSizeSlider = new Fl_Value_Slider(10, 80, 300, 20, "Size");
		m_BrushSizeSlider->user_data((void*)(this));	// record self to be used by static callback functions
		m_BrushSizeSlider->type(FL_HOR_NICE_SLIDER);
        m_BrushSizeSlider->labelfont(FL_COURIER);
        m_BrushSizeSlider->labelsize(12);
		m_BrushSizeSlider->minimum(1);
		m_BrushSizeSlider->maximum(40);
		m_BrushSizeSlider->step(1);
		m_BrushSizeSlider->value(m_nSize);
		m_BrushSizeSlider->align(FL_ALIGN_RIGHT);
		m_BrushSizeSlider->callback(cb_sizeSlides);

		// Added By Ryan STARTED
		//line width slider to the dialog STARTED
		m_LineWidthSlider = new Fl_Value_Slider(10, 110, 300, 20, "Line Width");
		m_LineWidthSlider->user_data((void*)(this));	// record self to be used by static callback functions
		m_LineWidthSlider->type(FL_HOR_NICE_SLIDER);
        m_LineWidthSlider->labelfont(FL_COURIER);
        m_LineWidthSlider->labelsize(12);
		m_LineWidthSlider->minimum(1);
		m_LineWidthSlider->maximum(40);
		m_LineWidthSlider->step(1);
		m_LineWidthSlider->value(m_nLine_width);
		m_LineWidthSlider->align(FL_ALIGN_RIGHT);
		m_LineWidthSlider->callback(cb_line_widthSlides);
		//line width slider to the dialog ENDED
		// Added By Ryan ENDED

		// Added By Ryan STARTED
		//line angle slider to the dialog STARTED
		m_LineAngleSlider = new Fl_Value_Slider(10, 140, 300, 20, "Line Angle");
		m_LineAngleSlider->user_data((void*)(this));	// record self to be used by static callback functions
		m_LineAngleSlider->type(FL_HOR_NICE_SLIDER);
        m_LineAngleSlider->labelfont(FL_COURIER);
        m_LineAngleSlider->labelsize(12);
		m_LineAngleSlider->minimum(0);
		m_LineAngleSlider->maximum(359);
		m_LineAngleSlider->step(1);
		m_LineAngleSlider->value(m_nLine_angle);
		m_LineAngleSlider->align(FL_ALIGN_RIGHT);
		m_LineAngleSlider->callback(cb_line_angleSlides);
		//line width slider to the dialog ENDED
		// Added By Ryan ENDED

		// Added By Ryan STARTED
		//Alpha slider to the dialog STARTED
		m_AlphaSlider = new Fl_Value_Slider(10, 170, 300, 20, "Alpha");
		m_AlphaSlider->user_data((void*)(this));	// record self to be used by static callback functions
		m_AlphaSlider->type(FL_HOR_NICE_SLIDER);
        m_AlphaSlider->labelfont(FL_COURIER);
        m_AlphaSlider->labelsize(12);
		m_AlphaSlider->minimum(0.00);
		m_AlphaSlider->maximum(1);
		m_AlphaSlider->step(0.01);
		m_AlphaSlider->value(m_nAlpha);
		m_AlphaSlider->align(FL_ALIGN_RIGHT);
		m_AlphaSlider->callback(cb_alphaSlides);
		//Alpha slider to the dialog ENDED
		//Added By Ryan ENDED

		//Control the activation of edge clip
		m_bEdgeClip = new Fl_Light_Button(10,210,150,25,"&Edge Clipping");
		m_bEdgeClip->user_data((void*)(this));
		m_bEdgeClip->callback(edgeClipControl);

		//The pack control the threshold of edge image
		m_bEdgePack = new Fl_Group(10, 240, 400, 30);

			//Edge slider to the dialog STARTED
			m_ThresholdSlider = new Fl_Value_Slider(10, 245, 150, 20, "Edge Threshold");
			m_ThresholdSlider->user_data((void*)(this));	// record self to be used by static callback functions
			m_ThresholdSlider->type(FL_HOR_NICE_SLIDER);
			m_ThresholdSlider->labelfont(FL_COURIER);
			m_ThresholdSlider->labelsize(12);
			m_ThresholdSlider->minimum(0);
			m_ThresholdSlider->maximum(500);
			m_ThresholdSlider->step(1);
			m_ThresholdSlider->value(threshold);
			m_ThresholdSlider->align(FL_ALIGN_RIGHT);
			m_ThresholdSlider->callback(cb_thresholdSlides);
			

			m_bDo = new Fl_Button(200,245,80,20,"Do it!");
			m_bDo->user_data((void*)(this));   // record self to be used by static callback functions
			m_bDo->callback(cb_do);


		m_bEdgePack->end();

    m_brushDialog->end();

	/* (Tim) Color Dialog [START] */
	m_colorDialog = new Fl_Window(412, 130, "Color Dialog");
		m_rColorSlider = new Fl_Value_Slider(10, 10, 300, 20, "Red Channel");
		m_rColorSlider->user_data((void*)(this));	// record self to be used by static callback functions
		m_rColorSlider->type(FL_HOR_NICE_SLIDER);
        m_rColorSlider->labelfont(FL_COURIER);
        m_rColorSlider->labelsize(12);
		m_rColorSlider->minimum(0);
		m_rColorSlider->maximum(int(255*m_nBrightnessColor));
		m_rColorSlider->step(1);
		m_rColorSlider->value(int(255*m_nRColor*m_nBrightnessColor));
		m_rColorSlider->align(FL_ALIGN_RIGHT);
		m_rColorSlider->callback(cb_rColorSlides);

		m_gColorSlider = new Fl_Value_Slider(10, 40, 300, 20, "Green Channel");
		m_gColorSlider->user_data((void*)(this));	// record self to be used by static callback functions
		m_gColorSlider->type(FL_HOR_NICE_SLIDER);
        m_gColorSlider->labelfont(FL_COURIER);
        m_gColorSlider->labelsize(12);
		m_gColorSlider->minimum(0);
		m_gColorSlider->maximum(int(255*m_nBrightnessColor));
		m_gColorSlider->step(1);
		m_gColorSlider->value(int(255*m_nGColor*m_nBrightnessColor));
		m_gColorSlider->align(FL_ALIGN_RIGHT);
		m_gColorSlider->callback(cb_gColorSlides);

		m_bColorSlider = new Fl_Value_Slider(10, 70, 300, 20, "Blue Channel");
		m_bColorSlider->user_data((void*)(this));	// record self to be used by static callback functions
		m_bColorSlider->type(FL_HOR_NICE_SLIDER);
        m_bColorSlider->labelfont(FL_COURIER);
        m_bColorSlider->labelsize(12);
		m_bColorSlider->minimum(0);
		m_bColorSlider->maximum(int(255*m_nBrightnessColor));
		m_bColorSlider->step(1);
		m_bColorSlider->value(int(255*m_nBColor*m_nBrightnessColor));
		m_bColorSlider->align(FL_ALIGN_RIGHT);
		m_bColorSlider->callback(cb_bColorSlides);

		m_brightnessColorSlider = new Fl_Value_Slider(10, 100, 300, 20, "Brightness");
		m_brightnessColorSlider->user_data((void*)(this));	// record self to be used by static callback functions
		m_brightnessColorSlider->type(FL_HOR_NICE_SLIDER);
        m_brightnessColorSlider->labelfont(FL_COURIER);
        m_brightnessColorSlider->labelsize(12);
		m_brightnessColorSlider->minimum(0.00);
		m_brightnessColorSlider->maximum(1.00);
		m_brightnessColorSlider->step(0.01);
		m_brightnessColorSlider->value(m_nBrightnessColor);
		m_brightnessColorSlider->align(FL_ALIGN_RIGHT);
		m_brightnessColorSlider->callback(cb_brightnessColorSlides);
	m_colorDialog->end();
	/* (Tim) Color Dialog [END] */

	/* (Tim) Dissolve An Image Dialog [START] */
	m_DissolveDialog = new Fl_Window(360, 75, "Dissolve An Image Dialog");
		m_Dissolve_AlphaSlider = new Fl_Value_Slider(10, 10, 300, 20, "Alpha");
		m_Dissolve_AlphaSlider->user_data((void*)(this));	// record self to be used by static callback functions
		m_Dissolve_AlphaSlider->type(FL_HOR_NICE_SLIDER);
        m_Dissolve_AlphaSlider->labelfont(FL_COURIER);
        m_Dissolve_AlphaSlider->labelsize(12);
		m_Dissolve_AlphaSlider->minimum(0);
		m_Dissolve_AlphaSlider->maximum(1.00);
		m_Dissolve_AlphaSlider->step(0.01);
		m_Dissolve_AlphaSlider->value(m_nDissolve_Alpha);
		m_Dissolve_AlphaSlider->align(FL_ALIGN_RIGHT);
		m_Dissolve_AlphaSlider->callback(cb_Dissolve_AlphaSlides);
		
		m_Dissolve_LoadImageButton = new Fl_Button(105,40,150,25,"Choose Image");
		m_Dissolve_LoadImageButton->user_data((void*)(this));
		m_Dissolve_LoadImageButton->callback(cb_Dissolve_LoadImage);
	m_DissolveDialog->end();
	/* (Tim) Dissolve An Image Dialog [END] */

		this->m_StrokeDirectionChoice->deactivate();
		this->m_LineWidthSlider->deactivate();
		this->m_LineAngleSlider->deactivate();
}

void ImpressionistUI::cb_activation(int type)
{
	switch(type)
	{
	case BRUSH_POINTS:
	case BRUSH_CIRCLES:
	case BRUSH_SCATTERED_POINTS:
	case BRUSH_SCATTERED_CIRCLES:
		this->m_StrokeDirectionChoice->deactivate();
		this->m_LineWidthSlider->deactivate();
		this->m_LineAngleSlider->deactivate();
		break;
	case BRUSH_GREYSCALE:
	case BRUSH_CONTRAST:
		this->m_StrokeDirectionChoice->deactivate();
		this->m_LineWidthSlider->deactivate();
		this->m_LineAngleSlider->deactivate();
		this->m_AlphaSlider->deactivate();
	break;

	case BRUSH_LINES:
	case BRUSH_SCATTERED_LINES:
		this->m_StrokeDirectionChoice->activate();
		this->m_LineWidthSlider->activate();
		this->m_LineAngleSlider->activate();
	break;

	}
}

unsigned char ImpressionistUI::cb_getThreshold()
{
	return threshold;
}
void ImpressionistUI::cb_setThreshold(unsigned char thre)
{
	threshold=thre;
}

void ImpressionistUI::edgeClipControl(Fl_Widget* o, void* v)
{

}

void ImpressionistUI::cb_thresholdSlides(Fl_Widget* o, void* v)
{
	((ImpressionistUI*)(o->user_data()))->threshold=int( ((Fl_Slider *)o)->value() / 7.0) ;
}

void ImpressionistUI::cb_do(Fl_Widget* o, void* v)
{

	ImpressionistDoc * pDoc = ((ImpressionistUI*)(o->user_data()))->getDocument();
	pDoc->getThresholdImage();
			//Create the threshold image using distance image

}
