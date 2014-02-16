//
// PointBrush.cpp
//
// The implementation of Point Brush. It is a kind of ImpBrush. All your brush implementations
// will look like the file with the different GL primitive calls.
//


#include "impressionistDoc.h"
#include "impressionistUI.h"
#include <cmath>
#include "LineBrush.h"

const double PI=3.1415927;
extern float frand();

LineBrush::LineBrush( ImpressionistDoc* pDoc, char* name ) :
	ImpBrush(pDoc,name)
{
}

void LineBrush::BrushBegin( const Point source, const Point target )
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg=pDoc->m_pUI;

	int size = pDoc->getSize();



	glPointSize(size);

	BrushMove( source, target );
}

void LineBrush::BrushMove( const Point source, const Point target )
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg=pDoc->m_pUI;

	if ( pDoc == NULL ) {
		printf( "PointBrush::BrushMove  document is NULL\n" );
		return;
	}
	//Processing LineWidth STARTED
	int width=GetDocument()->getLineWidth();
	double halfWidth=width/2.0;   //converted to double in case width is 1
	//Processing LineWIdth ENDED

	//Processsing LineLength STARTED
	int length;
	glGetIntegerv(GL_POINT_SIZE ,&length);
	double halfLength = length/2.0;  //Need to be converted to double. Or nothing will be drawn when length is 1
	//Processing LineLength ENDED
	
	//Processing LineAngle STARTED
	int angle = GetDocument()->getLineAngle();
	double mathAngle=(angle%360)/360.0*2*PI;
	double cosV=cos(mathAngle);
	double sinV=sin(mathAngle);
	//Processing LineAngle ENDED

	glBegin( GL_POLYGON );
		SetColor( source );
		glVertex2d( target.x-halfLength*cosV-halfWidth*sinV, target.y-halfLength*sinV+halfWidth*cosV);
		glVertex2d( target.x-halfLength*cosV+halfWidth*sinV, target.y-halfLength*sinV-halfWidth*cosV);
		glVertex2d( target.x+halfLength*cosV+halfWidth*sinV, target.y+halfLength*sinV-halfWidth*cosV);
		glVertex2d( target.x+halfLength*cosV-halfWidth*sinV, target.y+halfLength*sinV+halfWidth*cosV);
	glEnd();
}

void LineBrush::BrushEnd( const Point source, const Point target )
{
	// do nothing so far
}

