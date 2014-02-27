// 
// impressionistDoc.h
//
// header file for Doc 
//

#ifndef ImpressionistDoc_h
#define ImpressionistDoc_h

#include <cstdlib>
#include <cmath>
#include <stack>
#include "impressionist.h"
#include "bitmap.h"

const double PI=3.1415927;

class ImpressionistUI;

class ImpressionistDoc 
{
public:
	ImpressionistDoc();

	void	setUI(ImpressionistUI* ui);		// Assign the UI to use

	int		loadImage(char *iname);			// called by the UI to load image
	int		saveImage(char *iname);			// called by the UI to save image


	int     clearCanvas();                  // called by the UI to clear the drawing canvas
	void	setBrushType(int type);			// called by the UI to set the brushType

	int		getSize();						// get the UI size
	//ADDED BY RYAN STARTED
	int		getLineWidth();
	int		getLineAngle();
	double		getAlpha();
	//ADDED BY RYAN ENDED

	/* (Tim) Color Dialog [START] */
	double	getRColor();
	double	getGColor();
	double	getBColor();
	double	getBrightnessColor();
	/* (Tim) Color Dialog [END] */

	void	setSize(int size);				// set the UI size
	//ADDED BY RYAN STARTED
	void	setStrokeDirect(int type);
	void	setLineWidth(int width);
	void	setLineAngle(int angle);
	//ADDED BY RYAN ENDED
	char*	getImageName();					// get the current image name
	

// Attributes
public:
	// Dimensions of original window.
	int				m_nWidth, 
					m_nHeight;
	// Dimensions of the paint window.
	int				m_nPaintWidth, 
					m_nPaintHeight;	
	// Bitmaps for original image and painting.
	unsigned char*	m_ucBitmap;
	unsigned char*	m_ucPainting;
	std::stack<unsigned char*>	m_ucPainting_Undo;

	// The blurred image which contains intensity only
	unsigned char* m_ucGray;
	// Processed by box filter
	unsigned char* m_ucBlur;
	// Store the line angle of each pixel
	int* m_ucAngle;
	//Store the direction of stroke
	int lineDirectPattern;

	// The current active brush.
	ImpBrush*			m_pCurrentBrush;	
	Point current;


	// Size of the brush.
	int m_nSize;							

	ImpressionistUI*	m_pUI;

// Operations
public:
	// Get the color of the original picture at the specified coord
	GLubyte* GetOriginalPixel( int x, int y );   
	// Get the color of the original picture at the specified point	
	GLubyte* GetOriginalPixel( const Point p );  

	//ADDED BY RYAN START
		//Return RGB and alpha
	//GLubyte* GetOriginalPixelAlpha( int x, int y );
	//GLubyte* GetOriginalPixelAlpha( const Point p );
	//ADDED BY RYAN END

private:
	char			m_imageName[256];

};

extern void MessageBox(char *message);

#endif
