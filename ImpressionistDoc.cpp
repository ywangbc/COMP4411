// 
// impressionistDoc.cpp
//
// It basically maintain the bitmap for answering the color query from the brush.
// It also acts as the bridge between brushes and UI (including views)
//

#include <FL/fl_ask.H>

#include "impressionistDoc.h"
#include "impressionistUI.h"

#include "ImpBrush.h"

// Include individual brush headers here.
#include "PointBrush.h"
#include "LineBrush.h"
#include "CircleBrush.h"
#include "ScatteredPointBrush.h"
#include "ScatteredLineBrush.h"
#include "ScatteredCircleBrush.h"

// Newly implemented brushes
#include "GreyscaleBrush.h"
#include "ContrastBrush.h"


#define DESTROY(p)	{  if ((p)!=NULL) {delete [] p; p=NULL; } }

ImpressionistDoc::ImpressionistDoc() 
{
	// Set NULL image name as init. 
	m_imageName[0]	='\0';	

	m_nWidth		= -1;
	m_ucBitmap		= NULL;
	m_ucPainting	= NULL;
	m_ucBuffer		= NULL;
	m_ucGray		= NULL;
	m_ucBlur		= NULL;
	m_ucAngle		=NULL;
	m_ucTemp1		=NULL;
	m_ucTemp2		=NULL;
	m_ucEdgeHidden	=NULL;
	m_ucEdge100		=NULL;
	lineDirectPattern	=0; 


	// create one instance of each brush
	ImpBrush::c_nBrushCount	= NUM_BRUSH_TYPE;
	ImpBrush::c_pBrushes	= new ImpBrush* [ImpBrush::c_nBrushCount];

	ImpBrush::c_pBrushes[BRUSH_POINTS]	= new PointBrush( this, "Points" );

	// Note: You should implement these 5 brushes.  They are set the same (PointBrush) for now
	ImpBrush::c_pBrushes[BRUSH_LINES]				
		= new LineBrush( this, "Lines" );
	ImpBrush::c_pBrushes[BRUSH_CIRCLES]				
		= new CircleBrush( this, "Circles" );
	ImpBrush::c_pBrushes[BRUSH_SCATTERED_POINTS]	
		= new ScatteredPointBrush( this, "Scattered Points" );
	ImpBrush::c_pBrushes[BRUSH_SCATTERED_LINES]		
		= new ScatteredLineBrush( this, "Scattered Lines" );
	ImpBrush::c_pBrushes[BRUSH_SCATTERED_CIRCLES]	
		= new ScatteredCircleBrush( this, "Scattered Circles" );

	// Newly implemented brushes
	ImpBrush::c_pBrushes[BRUSH_GREYSCALE]	
		= new GreyscaleBrush( this, "Greyscale" );
	ImpBrush::c_pBrushes[BRUSH_CONTRAST]	
		= new ContrastBrush( this, "Contrast" );

	// make one of the brushes current
	m_pCurrentBrush	= ImpBrush::c_pBrushes[0];

}


//---------------------------------------------------------
// Set the current UI 
//---------------------------------------------------------
void ImpressionistDoc::setUI(ImpressionistUI* ui) 
{
	m_pUI	= ui;
}

//---------------------------------------------------------
// Returns the active picture/painting name
//---------------------------------------------------------
char* ImpressionistDoc::getImageName() 
{
	return m_imageName;
}

//---------------------------------------------------------
// Called by the UI when the user changes the brush type.
// type: one of the defined brush types.
//---------------------------------------------------------
void ImpressionistDoc::setBrushType(int type)
{
	m_pCurrentBrush	= ImpBrush::c_pBrushes[type];
	m_pUI->cb_activation(type);
}

//---------------------------------------------------------
// Returns the size of the brush.
//---------------------------------------------------------
int ImpressionistDoc::getSize()
{
	return m_pUI->getSize();
}

//ADDED BY RYAN STARTED
//---------------------------------------------------------
//Return the width of the line
//---------------------------------------------------------
int ImpressionistDoc::getLineWidth()
{
	return m_pUI->getLineWidth();
}

int ImpressionistDoc::getLineAngle()
{
	return m_pUI->getLineAngle();
}

double ImpressionistDoc::getAlpha()
{
	return m_pUI->getAlpha();
}

/* (Tim) Color Dialog [START] */
double ImpressionistDoc::getRColor()
{
	return m_pUI->getRColor();
}

double ImpressionistDoc::getGColor()
{
	return m_pUI->getGColor();
}

double ImpressionistDoc::getBColor()
{
	return m_pUI->getBColor();
}

double ImpressionistDoc::getBrightnessColor()
{
	return m_pUI->getBrightnessColor();
}
/* (Tim) Color Dialog [END] */

//Set the attributes of Brushes
void ImpressionistDoc::setSize(int size)
{
	m_pUI->setSize(size);
}

void ImpressionistDoc::setStrokeDirect(int type)
{
	switch(type)
	{
	case STROKE_SLIDER:
	{
		lineDirectPattern = STROKE_SLIDER;
		break;
	}
	case STROKE_GRAD:
	{
		lineDirectPattern = STROKE_GRAD;
		break;
	}
	case STROKE_BRUSH:
	{
		lineDirectPattern = STROKE_BRUSH;
		break;
	}
	default:
		printf("The stroke direction is not identifiable\n");
	}
}
void ImpressionistDoc::setLineWidth(int width)
{
	m_pUI->setLineWidth(width);
}

void ImpressionistDoc::setLineAngle(int angle)
{
	m_pUI->setLineAngle(angle);
}


//ADDED BY RYAN ENDED

//---------------------------------------------------------
// Load the specified image
// This is called by the UI when the load image button is 
// pressed.
//---------------------------------------------------------
int ImpressionistDoc::loadImage(char *iname) 
{
	// try to open the image to read
	unsigned char*	data;
	int				width, 
					height;

	if ( (data=readBMP(iname, width, height))==NULL ) 
	{
		fl_alert("Can't load bitmap file");
		return 0;
	}

	// reflect the fact of loading the new image
	m_nWidth		= width;
	m_nPaintWidth	= width;
	m_nHeight		= height;
	m_nPaintHeight	= height;

	// release old storage
	if ( m_ucBitmap ) delete [] m_ucBitmap;
	if ( m_ucPainting ) delete [] m_ucPainting;
	if (m_ucGray) delete [] m_ucGray; 
	if (m_ucBlur) delete [] m_ucBlur;
	if (m_ucAngle) delete [] m_ucAngle;
	if (m_ucTemp1) delete [] m_ucTemp1;
	if (m_ucTemp2) delete [] m_ucTemp2;
	if (m_ucEdgeHidden) delete [] m_ucEdgeHidden;
	if (m_ucEdge100) delete [] m_ucEdge100;
	if (m_ucBuffer)	delete [] m_ucBuffer;

	// empty Undo stack
	while (!m_ucPainting_Undo.empty()) {
		unsigned char* undo = m_ucPainting_Undo.top();
		delete [] undo;
		m_ucPainting_Undo.pop();
	}

	m_ucBitmap		= data;

	// allocate space for draw view
	m_ucPainting	= new unsigned char [width*height*3];
	
	//allocate space for the gray version
	m_ucGray		= new unsigned char [width*height*3];

	//allocate space for the blur version
	m_ucBlur		= new unsigned char [width*height*3];

	//allocate space to store the line anlge of each pixel
	m_ucAngle		= new int [width*height];

	m_ucTemp1		= new double [width*height*sizeof(double)];
	m_ucTemp2		= new double [width*height*sizeof(double)];
	m_ucEdgeHidden	= new unsigned char [width*height*3];
	m_ucEdge100		= new unsigned char [width*height*3];
	m_ucBuffer		= new unsigned char [width*height*3];

	memset(m_ucPainting, 0, width*height*3);
	memset(m_ucGray, 0, width*height*3);
	memset(m_ucBlur, 0, width*height*3);
	memset(m_ucBuffer, 0, width*height*3);
	memset(m_ucAngle, 0, width*height*sizeof(int));

	//Processing to get the Gray version

	for(int i = 0; i < width*height; i++)
	{
		unsigned char r,g,b,lum;
		
		for(int j=0;j<3;j++)
		{
			switch(j)
			{
			case 0:
				r=data[i*3+j];
				break;
			case 1:
				g=data[i*3+j];
				break;
			case 2:
				b=data[i*3+j];
				break;
			}
		}
		lum = (r*0.30) + (g*0.59) + (b*0.11);
		for(int j=0;j<3;j++)
		{
			m_ucGray[i*3+j]=lum;
		}
	}

	//Now we use the gray image to create the blur image
	for(int j=1;j<height-1;j++)
		for(int i=1;i<width-1;i++)
		{
			double sum=0;
			for(int l=0;l<3;l++)
				for(int k=0;k<3;k++)
				{
					int x=i-1+k;
					int y=j-1+l;

					sum+=m_ucGray[(x+y*width)*3];
				}
			unsigned char blurVal=sum/9;
			
			for(int m=0;m<3;m++)
			{
				m_ucBlur[(i+j*width)*3+m]=blurVal;
			}
		}

	//Now we calculate the angle for each pixel
	for(int j=1;j<height-1;j++)
		for(int i=1;i<width-1;i++)
		{
			double xDiff =
				m_ucBlur[(i+j*width)*3]-m_ucBlur[(i-1+j*width)*3];
			double yDiff = 
				m_ucBlur[(i+j*width)*3]-m_ucBlur[(i+(j-1)*width)*3];
			
			int angle = 0;
			if(xDiff==0) angle=90;
			else
			{
				double temp=atan2(yDiff,xDiff);
				angle=temp/(2*PI)*360;
			}

			angle=(angle+90)%360;
			m_ucAngle[i+j*width]=angle;
			
		}
	//Create temp1 using the first filter 
	for(int j=1;j<height-1;j++)
		for(int i=1;i<width-1;i++)
		{
			double sum=0;
			for(int l=0;l<3;l++)
				for(int k=0;k<3;k++)
				{
					int x=i-1+k;
					int y=j-1+l;

					sum+=(m_ucBlur[(x+y*width)*3]*kernel1[l][k]);
				}
			double blurVal=sum/9;
			
			for(int m=0;m<3;m++)
			{
				m_ucTemp1[(i+j*width)*3+m]=blurVal;
			}
		}
	
	//Create temp2 using the first filter 
	for(int j=1;j<height-1;j++)
		for(int i=1;i<width-1;i++)
		{
			double sum=0;
			for(int l=0;l<3;l++)
				for(int k=0;k<3;k++)
				{
					int x=i-1+k;
					int y=j-1+l;

					sum+=(m_ucBlur[(x+y*width)*3]*kernel2[l][k]);
				}
			double blurVal=sum/9;
			
			for(int m=0;m<3;m++)
			{
				m_ucTemp2[(i+j*width)*3+m]=blurVal;
			}
		}


	//Creating the distance image of temp1 and temp2 
	for(int j=1;j<height-1;j++)
		for(int i=1;i<width-1;i++)
		{
			for(int m=0;m<3;m++)
			{
				double val1=m_ucTemp1[(i+j*width)*3+m];
				double val2=m_ucTemp2[(i+j*width)*3+m];
				m_ucEdgeHidden[(i+j*width)*3+m]= sqrt(val1*val1+val2*val2);
			}
		}
	

	


	m_pUI->m_mainWindow->resize(m_pUI->m_mainWindow->x(), 
									m_pUI->m_mainWindow->y(), 
							width*2, 
								height+25);

	// display it on origView
	m_pUI->m_origView->resizeWindow(width, height);	
	m_pUI->m_origView->refresh();

	// refresh paint view as well
	m_pUI->m_paintView->resizeWindow(width, height);	
	m_pUI->m_paintView->refresh();


	return 1;
}


//----------------------------------------------------------------
// Save the specified image
// This is called by the UI when the save image menu button is 
// pressed.
//----------------------------------------------------------------
int ImpressionistDoc::saveImage(char *iname) 
{

	writeBMP(iname, m_nPaintWidth, m_nPaintHeight, m_ucPainting);

	return 1;
}

//----------------------------------------------------------------
// Clear the drawing canvas
// This is called by the UI when the clear canvas menu item is 
// chosen
//-----------------------------------------------------------------
int ImpressionistDoc::clearCanvas() 
{

	// Release old storage
	if ( m_ucPainting ) 
	{
		delete [] m_ucPainting;

		// allocate space for draw view
		m_ucPainting	= new unsigned char [m_nPaintWidth*m_nPaintHeight*3];
		memset(m_ucPainting, 0, m_nPaintWidth*m_nPaintHeight*3);

		// refresh paint view as well	
		m_pUI->m_paintView->refresh();
	}
	
	return 0;
}

/* (Tim) Dissolve An Image into The Original Image [START] */
//---------------------------------------------------------
// Load the specified image
// This is called by the UI when the load image button is 
// pressed.
//---------------------------------------------------------
int ImpressionistDoc::load_DissolveImage(char *iname) 
{
	// try to open the image to read
	unsigned char*	loaded;
	int				width,
					height;

	if ( (loaded=readBMP(iname, width, height))==NULL ) 
	{
		fl_alert("Cannot load bitmap file.");
		return 0;
	}

	// alert for loading an image which has a dimension bigger than the background
	if ( width > m_nWidth || height > m_nHeight) {
		fl_alert("The dimension of the loading image is bigger than the dimension of the background image.");
		return 0;
	}

	// release old storage
	if ( m_ucPainting ) delete [] m_ucPainting;
	if (m_ucGray) delete [] m_ucGray; 
	if (m_ucBlur) delete [] m_ucBlur;
	if (m_ucAngle) delete [] m_ucAngle;

	// empty Undo stack
	while (!m_ucPainting_Undo.empty()) {
		unsigned char* undo = m_ucPainting_Undo.top();
		delete [] undo;
		m_ucPainting_Undo.pop();
	}

	// dissolve the images
	double alpha = m_pUI->get_Dissolve_Alpha();
	for (int row = 0; row < height; ++row) {
		for (int col = 0; col < width; ++col) {
			for (int color = 0; color < 3; ++color) {
				int byte_Original = (row*m_nWidth + col)*3 + color;
				int byte_Loaded = (row*width + col)*3 + color;
				m_ucBitmap[byte_Original] = char(m_ucBitmap[byte_Original]*(1 - alpha) + loaded[byte_Loaded]*(alpha));
			}
		}
	}

	// allocate space for draw view
	m_ucPainting	= new unsigned char [m_nWidth*m_nHeight*3];
	
	//allocate space for the gray version
	m_ucGray		= new unsigned char [m_nWidth*m_nHeight*3];

	//allocate space for the blur version
	m_ucBlur		= new unsigned char [m_nWidth*m_nHeight*3];

	//allocate space to store the line anlge of each pixel
	m_ucAngle		= new int [m_nWidth*m_nHeight];

	memset(m_ucPainting, 0, m_nWidth*m_nHeight*3);
	memset(m_ucGray, 0, m_nWidth*m_nHeight*3);
	memset(m_ucBlur, 0, m_nWidth*m_nHeight*3);
	memset(m_ucAngle, 0, m_nWidth*m_nHeight*sizeof(int));

	//Processing to get the Gray version

	for(int i = 0; i < m_nWidth*m_nHeight; i++)
	{
		unsigned char r,g,b,lum;
		
		for(int j=0;j<3;j++)
		{
			switch(j)
			{
			case 0:
				r=m_ucBitmap[i*3+j];
				break;
			case 1:
				g=m_ucBitmap[i*3+j];
				break;
			case 2:
				b=m_ucBitmap[i*3+j];
				break;
			}
		}
		lum = (r*0.30) + (g*0.59) + (b*0.11);
		for(int j=0;j<3;j++)
		{
			m_ucGray[i*3+j]=lum;
		}
	}

	//Now we use the gray image to create the blur image
	for(int j=1;j<m_nHeight-1;j++)
		for(int i=1;i<m_nWidth-1;i++)
		{
			double sum=0;
			for(int l=0;l<3;l++)
				for(int k=0;k<3;k++)
				{
					int x=i-1+k;
					int y=j-1+l;

					sum+=m_ucGray[(x+y*m_nWidth)*3];
				}
			unsigned char blurVal=sum/9;
			
			for(int m=0;m<3;m++)
			{
				m_ucBlur[(i+j*m_nWidth)*3+m]=blurVal;
			}
		}

	//Now we calculate the angle for each pixel
	for(int j=1;j<m_nHeight-1;j++)
		for(int i=1;i<m_nWidth-1;i++)
		{
			double xDiff =
				m_ucBlur[(i+j*m_nWidth)*3]-m_ucBlur[(i-1+j*m_nWidth)*3];
			double yDiff = 
				m_ucBlur[(i+j*m_nWidth)*3]-m_ucBlur[(i+(j-1)*m_nWidth)*3];
			
			int angle = 0;
			if(xDiff==0) angle=90;
			else
			{
				double temp=atan2(yDiff,xDiff);
				angle=temp/(2*PI)*360;
			}

			angle=(angle+90)%360;
			m_ucAngle[i+j*m_nWidth]=angle;
			
		}

	



	m_pUI->m_mainWindow->resize(m_pUI->m_mainWindow->x(), 
									m_pUI->m_mainWindow->y(), 
							m_nWidth*2, 
								m_nHeight+25);

	// display it on origView
	m_pUI->m_origView->resizeWindow(m_nWidth, m_nHeight);	
	m_pUI->m_origView->refresh();

	// refresh paint view as well
	m_pUI->m_paintView->resizeWindow(m_nWidth, m_nHeight);	
	m_pUI->m_paintView->refresh();


	return 1;
}
/* (Tim) Dissolve An Image into The Original Image [END] */

//------------------------------------------------------------------
// Get the color of the pixel in the original image at coord x and y
//------------------------------------------------------------------
GLubyte* ImpressionistDoc::GetOriginalPixel( int x, int y )
{
	if ( x < 0 ) 
		x = 0;
	else if ( x >= m_nWidth ) 
		x = m_nWidth-1;

	if ( y < 0 ) 
		y = 0;
	else if ( y >= m_nHeight ) 
		y = m_nHeight-1;

	return (GLubyte*)(m_ucBitmap + 3 * (y*m_nWidth + x));
}


//----------------------------------------------------------------
// Get the color of the pixel in the original image at point p
//----------------------------------------------------------------
GLubyte* ImpressionistDoc::GetOriginalPixel( const Point p )
{
	return GetOriginalPixel( p.x, p.y );
}
/*
GLubyte* ImpressionistDoc::GetOriginalPixelAlpha( int x, int y )
{
	if ( x < 0 ) 
		x = 0;
	else if ( x >= m_nWidth ) 
		x = m_nWidth-1;

	if ( y < 0 ) 
		y = 0;
	else if ( y >= m_nHeight ) 
		y = m_nHeight-1;

	return (GLubyte*)(m_ucBitmap + 4 * (y*m_nWidth + x));
}


GLubyte* ImpressionistDoc::GetOriginalPixelAlpha(const Point p)
{
	return GetOriginalPixelAlpha(p.x,p.y);
}
*/
unsigned char ImpressionistDoc::getThreshold()
{
	return m_pUI->cb_getThreshold();
}
void ImpressionistDoc::setThreshold(unsigned char thre)
{
	m_pUI->cb_setThreshold(thre);
}

void ImpressionistDoc::getThresholdImage()
{
	for(int j=1;j<m_nHeight-1;j++)
		for(int i=1;i<m_nWidth-1;i++)
		{
			for(int m=0;m<3;m++)
			{
				unsigned char val=m_ucEdgeHidden[(i+j*m_nWidth)*3+m];
				if(val>=getThreshold()) 
				{
					m_ucEdge100[(i+j*m_nWidth)*3+m]=255;
				}
				else
				{
					m_ucEdge100[(i+j*m_nWidth)*3+m]=0;
				}
			}
		}

	memcpy(m_ucBuffer,m_ucEdge100,3*m_nWidth*m_nHeight);
	unsigned char* temp=m_ucBitmap;
	m_ucBitmap = m_ucBuffer;
	m_ucBuffer = temp;

	m_pUI->m_origView->refresh();
}
