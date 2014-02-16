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

	Fl_Slider*			m_BrushSizeSlider;
	//ADDED BY RYAN STARTED
	Fl_Slider*			m_LineWidthSlider;
	Fl_Slider*			m_LineAngleSlider;
	Fl_Slider*			m_AlphaSlider;
	//ADDED BY RYAN ENDED
	Fl_Button*          m_ClearCanvasButton;

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
	void				setAlpha(double Alpha);
	//Added By Ryan ENDED

private:
	ImpressionistDoc*	m_pDoc;		// pointer to document to communicate with the document

	// All attributes here
	int		m_nSize;
	//Added By Ryan Started
	int m_nLine_width;
	int m_nLine_angle;
	double m_nAlpha;
	//Added By Ryan Ended 


	// Static class members
	static Fl_Menu_Item		menuitems[];
	static Fl_Menu_Item		brushTypeMenu[NUM_BRUSH_TYPE+1];

	static ImpressionistUI*	whoami(Fl_Menu_* o);

	// All callbacks here.  Callbacks are declared 
	// static
	static void	cb_load_image(Fl_Menu_* o, void* v);
	static void	cb_save_image(Fl_Menu_* o, void* v);
	static void	cb_brushes(Fl_Menu_* o, void* v);
	static void	cb_clear_canvas(Fl_Menu_* o, void* v);
	static void	cb_exit(Fl_Menu_* o, void* v);
	static void	cb_about(Fl_Menu_* o, void* v);
	static void	cb_brushChoice(Fl_Widget* o, void* v);
	static void	cb_clear_canvas_button(Fl_Widget* o, void* v);

	//Callbacks for Brush Dialog STARTED
	static void	cb_sizeSlides(Fl_Widget* o, void* v);

	//Added By Ryan STARTED

	//Brush Dialog->LineWidthSlider 
	static void cb_line_widthSlides(Fl_Widget* o, void* v);

	//Brush Dialog->LineAngleSlider
	static void cb_line_angleSlides(Fl_Widget* o, void* v);
	
	//Brush Dialog->alpha
	static void cb_alphaSlides(Fl_Widget* o, void* v);

	//Added By Ryan ENDED
	//Callbacks for Brush Dialog ENDED
	
	//Added By Ryan STARTED (File)
	static void	cb_colors(Fl_Menu_* o, void* v);
	static void	cb_paintly(Fl_Menu_* o, void* v);
	static void	cb_load_edge_image(Fl_Menu_* o, void* v);
	static void	cb_load_another_image(Fl_Menu_* o, void* v);

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
