//
// PointBrush.cpp
//
// The implementation of Point Brush. It is a kind of ImpBrush. All your brush implementations
// will look like the file with the different GL primitive calls.
//

#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "ScatteredPointBrush.h"

extern float frand();
ScatteredPointBrush::ScatteredPointBrush( ImpressionistDoc* pDoc, char* name ) :
	ImpBrush(pDoc,name)
{
}

void ScatteredPointBrush::BrushBegin( const Point source, const Point target )
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg=pDoc->m_pUI;

	/* (Tim) Save Paint for Undo [START] */
	savePaintForUndo();
	/* (Tim) Save Paint for Undo [END] */

	int size = pDoc->getSize();



	glPointSize( (float)size );

	BrushMove( source, target );
}

void ScatteredPointBrush::BrushMove( const Point source, const Point target )
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg=pDoc->m_pUI;

	if ( pDoc == NULL ) {
		printf( "PointBrush::BrushMove  document is NULL\n" );
		return;
	}

	int size;
	glGetIntegerv(GL_POINT_SIZE ,&size);
	double halfSize=size/2.0;
	double startXS=source.x-halfSize;
	double startYS=source.y-halfSize;
	double startXT=target.x-halfSize;
	double startYT=target.y-halfSize;


	glPointSize(1);

	for(int i=0;i<size;i++)
		for(int j=0;j<size;j++)
		{
			int seed = rand()%50;
			if(seed<25) 
			{
				Point newS=Point(startXS+i,startYS+j);
				Point newT=Point(startXT+i,startYT+j);
				ImpBrush::c_pBrushes[BRUSH_POINTS]->BrushMove(newS, newT);
			}
		}

	glPointSize(float(size));

}

void ScatteredPointBrush::BrushEnd( const Point source, const Point target )
{
	// do nothing so far
}

