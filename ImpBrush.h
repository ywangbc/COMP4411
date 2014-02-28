#ifndef IMPBRUSH_H
#define IMPBRUSH_H

//
// ImpBrush.h
//
// The header file of virtual brush. All the other brushes inherit from it.
//

#include <stdlib.h>
#include <cmath>

// Each brush type has an associated constant.
enum
{
	BRUSH_POINTS = 0,
	BRUSH_LINES,
	BRUSH_CIRCLES,
	BRUSH_SCATTERED_POINTS,
	BRUSH_SCATTERED_LINES,
	BRUSH_SCATTERED_CIRCLES,
	BRUSH_GREYSCALE,				// (Tim) Greyscale Brush
	BRUSH_CONTRAST,					// (Tim) Contrast Brush
	NUM_BRUSH_TYPE					// Make sure this stays at the end!
};

enum
{
	STROKE_SLIDER = 0,
	STROKE_GRAD,
	STROKE_BRUSH,
	NUM_STROKE_DIRECTION
};

const int kernel1[3][3]={{-1,-2,-1},{0,0,0},{1,2,1}};
const int kernel2[3][3]={{1,0,-1},{2,0,-2},{1,0,-1}};


class ImpressionistDoc; // Pre-declaring class

class Point 
{
public:
	Point() {};
	Point(int xx, int yy) { x = xx; y = yy; };

	int x, y;
};

class ImpBrush 
{
protected:
	ImpBrush::ImpBrush( ImpressionistDoc* pDoc = NULL, char* name = NULL );

public:
	// The implementation of your brush should realize these virtual functions
	virtual void BrushBegin( const Point source, const Point target ) = 0;
	virtual void BrushMove( const Point source, const Point target ) = 0;
	virtual void BrushEnd( const Point source, const Point target ) = 0;

	//ADDED BY RYAN
	double dist(Point a, Point b);


	// according to the source image and the position, determine the draw color
	void SetColor( const Point source );

	//ADDED BY RYAN START
	void SetColorAlpha(const Point source);
	//ADDED BY RYAN END

	// get Doc to communicate with it
	ImpressionistDoc* GetDocument( void );

	// Return the name of the brush (not used in this version).
	char* BrushName( void );

	/* (Tim) Save Paint for Undo [START] */
	void savePaintForUndo();
	/* (Tim) Save Paint for Undo [END] */
	
	static int			c_nBrushCount;	// How many brushes we have,
	static ImpBrush**	c_pBrushes;		// and what they are.

private:
	ImpressionistDoc*	m_pDoc;

	// Brush's name (not used in this version).
	char*				m_pBrushName;
};

#endif