//
// PointBrush.cpp
//
// The implementation of Point Brush. It is a kind of ImpBrush. All your brush implementations
// will look like the file with the different GL primitive calls.
//
#include <cmath>
#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "CircleBrush.h"

extern float frand();

const double twoPi=6.2831853;
const int triangles=100;

CircleBrush::CircleBrush( ImpressionistDoc* pDoc, char* name ) :
	ImpBrush(pDoc,name)
{
}

void CircleBrush::BrushBegin( const Point source, const Point target )
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg=pDoc->m_pUI;

	int size = pDoc->getSize();



	glPointSize( (float)size );

	BrushMove( source, target );
}

void CircleBrush::BrushMove( const Point source, const Point target )
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg=pDoc->m_pUI;

	if ( pDoc == NULL ) {
		printf( "PointBrush::BrushMove  document is NULL\n" );
		return;
	}

	//The center of the circle
	double x=target.x;
	double y=target.y;

	//The radius of the circle
	int diam;
	glGetIntegerv(GL_POINT_SIZE ,&diam);
	double radius=diam/2.0;

	glBegin(GL_TRIANGLE_FAN);
		SetColor( source );
		glVertex2f(x, y); // center of circle
		for(int i = 0; i <= triangles;i++) { 
			glVertex2f(
		        x + (radius * cos(i * twoPi / triangles)), 
			    y + (radius * sin(i * twoPi / triangles))
			);
		}
	glEnd();
}

void CircleBrush::BrushEnd( const Point source, const Point target )
{
	// do nothing so far
}

