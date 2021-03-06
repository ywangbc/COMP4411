//
// impressionistUI.h
//
// The header file for the UI part
//

#ifndef ImpressionistUI_h
#define ImpressionistUI_h

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/fl_file_chooser.H>		// FLTK file chooser
#include <FL/Fl_Menu_Bar.H>
#include <FL/Fl_Value_Slider.H>
#include <FL/Fl_Choice.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Light_Button.H>
#include <FL/Fl_Color_Chooser.H>
#include <FL/Fl_Float_Input.H>
#include <FL/Fl_Group.H>
#include <cstdlib>

#include "Impressionist.h"
#include "OriginalView.h"
#include "PaintView.h"

#include "ImpBrush.h"

class ImpressionistUI {
public:
	ImpressionistUI();

	// The FLTK widgets
	Fl_Window*			m_mainWindow;
	Fl_Menu_Bar*		m_menubar;
								
	PaintView*			m_paintView;
	OriginalView*		m_origView;

// for brush dialog
	Fl_Window*			m_brushDialog;
	Fl_Choice*			m_BrushTypeChoice;

	Fl_Choice*			m_StrokeDirectionChoice;

	Fl_Slider*			m_BrushSizeSlider;
	//ADDED BY RYAN STARTED
	Fl_Slider*			m_LineWidthSlider;
	Fl_Slider*			m_LineAngleSlider;
	Fl_Slider*			m_AlphaSlider;
	Fl_Slider*			m_ThresholdSlider;
	//ADDED BY RYAN ENDED
	Fl_Button*          m_ClearCanvasButton;

	/* (Tim) Color Dialog [START] */
	Fl_Window*			m_colorDialog;
	Fl_Slider*			m_rColorSlider;
	Fl_Slider*			m_gColorSlider;
	Fl_Slider*			m_bColorSlider;
	Fl_Slider*			m_brightnessColorSlider;
	/* (Tim) Color Dialog [END] */

	/* (Tim) Dissolve An Image Dialog [START] */
	Fl_Window*			m_DissolveDialog;
	Fl_Slider*			m_Dissolve_AlphaSlider;
	Fl_Button*			m_Dissolve_LoadImageButton;
	/* (Tim) Dissolve An Image Dialog [END] */

	Fl_Light_Button *   m_bEdgeClip;

	Fl_Group*			m_bEdgePack;

	Fl_Button*			m_bDo;

	// Member functions
	void				setDocument(ImpressionistDoc* doc);
	ImpressionistDoc*	getDocument();

	void				show();
	void				resize_windows(int w, int h);

	// Interface to get attribute

	int					getSize();
	//Added By Ryan STARTED
	int					getLineWidth();
	int					getLineAngle();
	double				getAlpha();
	//Added By Ryan ENDED

	void				setSize(int size);
	//Added By Ryan STARTED
	void				setLineWidth(int width);
	void				setLineAngle(int angle);

	//Control the threshold of edge pic
	unsigned char		cb_getThreshold();
	void				cb_setThreshold(unsigned char thre);
	static void				cb_do(Fl_Widget* o, void* v);

	//Control activation and deacivation of widgets
	void cb_activation(int type);

	//Added By Ryan ENDED

	/* (Tim) Color Dialog [START] */
	double				getRColor();
	double				getGColor();
	double				getBColor();
	double				getBrightnessColor();
	/* (Tim) Color Dialog [END] */

	/* (Tim) Dissolve An Image Dialog [START] */
	double				get_Dissolve_Alpha();
	/* (Tim) Dissolve An Image Dialog [END] */

private:
	ImpressionistDoc*	m_pDoc;		// pointer to document to communicate with the document

	// All attributes here
	int		m_nSize;
	//Added By Ryan Started
	int m_nLine_width;
	int m_nLine_angle;
	double m_nAlpha;
	//Added By Ryan Ended 

	//To control the treshold of edge image
	unsigned char threshold;

	/* (Tim) Color Dialog [START] */
	double m_nRColor;
	double m_nGColor;
	double m_nBColor;
	double m_nBrightnessColor;
	/* (Tim) Color Dialog [START] */

	/* (Tim) Dissolve An Image Dialog [START] */
	double m_nDissolve_Alpha;
	/* (Tim) Dissolve An Image Dialog [END] */


	// Static class members
	static Fl_Menu_Item		menuitems[];
	static Fl_Menu_Item		brushTypeMenu[NUM_BRUSH_TYPE+1];
	static Fl_Menu_Item		strokeDirectionMenu[NUM_STROKE_DIRECTION+1];

	static ImpressionistUI*	whoami(Fl_Menu_* o);

	// All callbacks here.  Callbacks are declared 
	// static
	static void	cb_load_image(Fl_Menu_* o, void* v);
	static void	cb_save_image(Fl_Menu_* o, void* v);
	static void	cb_brushes(Fl_Menu_* o, void* v);
	static void	cb_clear_canvas(Fl_Menu_* o, void* v);
	static void	cb_undo(Fl_Menu_* o, void* v);
	static void	cb_exit(Fl_Menu_* o, void* v);
	static void	cb_about(Fl_Menu_* o, void* v);
	static void	cb_brushChoice(Fl_Widget* o, void* v);
	static void	cb_clear_canvas_button(Fl_Widget* o, void* v);
	static void edgeClipControl(Fl_Widget* o, void* v);
	

		//Added By Ryan ENDED
	

	// (Tim) Swap the Canvas
	static void	cb_swap_canvas(Fl_Menu_* o, void* v);

	// (Tim) Dissolve an image into the original image
	static void cb_Dissolve_AlphaSlides(Fl_Widget* o, void* v);
	static void cb_Dissolve_LoadImage(Fl_Widget* o, void* v);

	//change the line Stroke_direction
	static void cb_strokeDirection(Fl_Widget* o, void* v);

	//Callbacks for Brush Dialog STARTED
	static void	cb_sizeSlides(Fl_Widget* o, void* v);

	//Callback to control the threshold
	static void cb_thresholdSlides(Fl_Widget* o, void* v);

	//Added By Ryan STARTED

	//Brush Dialog->LineWidthSlider 
	static void cb_line_widthSlides(Fl_Widget* o, void* v);

	//Brush Dialog->LineAngleSlider
	static void cb_line_angleSlides(Fl_Widget* o, void* v);
	
	//Brush Dialog->alpha
	static void cb_alphaSlides(Fl_Widget* o, void* v);

	//Added By Ryan ENDED
	//Callbacks for Brush Dialog ENDED

	/* (Tim) Color Dialog [START] */
	static void cb_rColorSlides(Fl_Widget* o, void* v);
	static void cb_gColorSlides(Fl_Widget* o, void* v);
	static void cb_bColorSlides(Fl_Widget* o, void* v);
	static void cb_brightnessColorSlides(Fl_Widget* o, void* v);
	/* (Tim) Color Dialog [END] */
	
	//Added By Ryan STARTED (File)
	static void	cb_colors(Fl_Menu_* o, void* v);
	static void	cb_paintly(Fl_Menu_* o, void* v);
	static void	cb_load_edge_image(Fl_Menu_* o, void* v);
	static void	cb_load_another_image(Fl_Menu_* o, void* v);
	static void	cb_Dissolve(Fl_Menu_* o, void* v);

	//Added By Ryan ENDED (File)

	//Added By Ryan STARTED (Display)
	static void cb_original_image(Fl_Menu_* o, void* v);
	static void cb_edge_image(Fl_Menu_* o, void* v);
	static void cb_another_image(Fl_Menu_* o, void* v);
	//Added By Ryan ENDED (Display)

	//Added By Ryan STARTED (Options)
	static void cb_faster(Fl_Menu_* o, void* v);
	static void cb_safer(Fl_Menu_* o, void* v);
	//Added By Ryan ENDED (Options)

};

#endif
