//
// paintview.h
//
// The header file for painting view of the input images
//

#ifndef PAINTVIEW_H
#define PAINTVIEW_H

#include <FL/Fl.H>
#include <FL/Fl_Gl_Window.H>
#include <FL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>

class ImpressionistDoc;

class PaintView : public Fl_Gl_Window
{
public:
	PaintView(int x, int y, int w, int h, const char* l);
	void draw();
	int handle(int event);

	void refresh();
	
	void resizeWindow(int width, int height);

	void SaveCurrentContent();

	void RestoreContent();

	//ADDED BY RYAN STARTED
	//To access the private members of paint view
	//Will be used in controlling out of border condition
	int GetStartRow();
	int GetEndRow();
	int GetStartCol();
	int GetEndCol();
	int GetDrawHeight();
	//ADDED BY RYAN ENDED
	ImpressionistDoc *m_pDoc;

private:
	GLvoid* m_pPaintBitstart;
	int		m_nDrawWidth,
			m_nDrawHeight,
			m_nStartRow, 
			m_nEndRow,
			m_nStartCol, 
			m_nEndCol,
			m_nWindowWidth, 
			m_nWindowHeight;

	//ADDED BY RYAN START
	Point fixPoint;   //the starting point when left button licked
	//ADDED BY RYAN END

};

#endif