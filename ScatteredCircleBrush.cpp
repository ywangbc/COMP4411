//
// PointBrush.cpp
//
// The implementation of Point Brush. It is a kind of ImpBrush. All your brush implementations
// will look like the file with the different GL primitive calls.
//

#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "ScatteredCircleBrush.h"

extern float frand();

ScatteredCircleBrush::ScatteredCircleBrush( ImpressionistDoc* pDoc, char* name ) :
	ImpBrush(pDoc,name)
{
}

void ScatteredCircleBrush::BrushBegin( const Point source, const Point target )
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg=pDoc->m_pUI;

	int size = pDoc->getSize();



	glPointSize( (float)size );

	BrushMove( source, target );
}

void ScatteredCircleBrush::BrushMove( const Point source, const Point target )
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg=pDoc->m_pUI;

	if ( pDoc == NULL ) {
		printf( "PointBrush::BrushMove  document is NULL\n" );
		return;
	}

	int length;
	glGetIntegerv(GL_POINT_SIZE ,&length);
	double halfLength=length/2.0;
	double startXS=source.x-halfLength;
	double startYS=source.y-halfLength;
	double startXT=target.x-halfLength;
	double startYT=target.y-halfLength;


	for(int i=0;i<length;i++)
		for(int j=0;j<length;j++)
		{
			Point newS=Point(startXS+i,startYS+j);
			Point newT=Point(startXT+i,startYT+j);
			if(dist(newT,target)>halfLength)
			{
				continue;
			}
			int seed = rand()%50;
			if(seed<1) 
			{
				ImpBrush::c_pBrushes[BRUSH_CIRCLES]->BrushMove(newS, newT);
			}
		}
}

void ScatteredCircleBrush::BrushEnd( const Point source, const Point target )
{
	// do nothing so far
}

