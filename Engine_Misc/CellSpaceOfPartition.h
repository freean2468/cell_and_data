#ifndef CELLSPACEPARTITION_H
#define CELLSPACEPARTITION_H
//-----------------------------------------------------------------------------
//
//  Name:   CCellSpacePartition.h
//
//  Author: Mat Buckland (www.ai-junkie.com)
//
//	Modifier : Hoon-il Song (Sider)
//
//  Desc:   class to divide a 2D space into a grid of cells each of which
//          may contain a number of entities. Once created and initialized 
//          with entities, fast proximity querys can be made by calling the
//          CalculateNeighbors method with a position and proximity radius.
//
//          If an entity is capable of moving, and therefore capable of moving
//          between cells, the Update method should be called each update-cycle
//          to sychronize the entity and the cell space it occupies
//
//-----------------------------------------------------------------------------
#pragma warning (disable:4786)

#include "Box3D.h"
#include <list>

//------------------------------------------------------------------------
//
//  defines a cell containing a list of pointers to entities
//------------------------------------------------------------------------
template <class entity>
struct Cell{
  //all the entities inhabiting this cell
  std::list<entity>    Members;

  //the cell's bounding box (it's inverted because the Window's default
  //co-ordinate system has a y axis that increases as it descends)
  CBox3D     BBox;

  Cell(Vector2D topleft, Vector2D botright):BBox(CBox3D(topleft, botright)){}
};

/////////// //////////////////////////////////////////////////////////////////
//  the subdivision class
///////////////////////////////////////////////////////////////////////////////
template <class entity>
class CCellSpacePartition{
private:
  //the required amount of cells in the space
  std::vector<Cell<entity> >               m_Cells;

  //this is used to store any valid neighbors when an agent searches
  //its neighboring space
  std::vector<entity>                      m_Neighbors;

  //this iterator will be used by the methods next and begin to traverse
  //through the above vector of neighbors
  typename std::vector<entity>::iterator   m_curNeighbor;

  //the width and height of the world space the entities inhabit
  double  m_dWorldWidth;
  double  m_dWorldHeight;

  double  m_dCellSizeX;
  double  m_dCellSizeY;

	double	m_iNumCellsX;
	double	m_iNumCellsY;

  //given a position in the game space this method determines the           
  //relevant cell's index
  inline int  PositionToIndex(const Vector2D& pos)const;

public:
  CCellSpacePartition(double width,       //width of the environment
                     double height,       //height ...
                     int   cellsSizeX,    //Size of cell horizontally
                     int   cellsSizeY,    //Size of cell vertically
                     int   MaxEntitys);   //maximum number of entities to add

  //adds entities to the class by allocating them to the appropriate cell
  inline void AddEntity(const entity& ent);

  //update an entity's cell by calling this from your entity's Update method 
  inline void UpdateEntity(const entity& ent, Vector2D OldPos);

  //this method calculates all a _vTarget's neighbors and stores them in
  //the neighbor vector. After you have called this method use the begin, 
  //next and end methods to iterate through the vector.
  inline void CalculateNeighbors(Vector2D TargetPos, double QueryRadius);

  //returns a reference to the entity at the front of the neighbor vector
  inline entity& begin(){m_curNeighbor = m_Neighbors.begin(); return *m_curNeighbor;}

  //this returns the next entity in the neighbor vector
  inline entity& next(){++m_curNeighbor; return *m_curNeighbor;}

  //returns true if the end of the vector is found (a zero value marks the end)
  inline bool   end(){return (m_curNeighbor == m_Neighbors.end()) || (*m_curNeighbor == 0);}   
   
  //empties the cells of entities
  void        EmptyCells();

	//call to Update the cell edges
	inline void UpdateCells();

  //call to render the cell edges
  void RenderCells(ID3DXLine* _pLine)const;

	void RenderCellsCoordinate(ID3DXSprite* p_pSprite, ID3DXFont* _pFont)const;
};

//----------------------------- ctor ---------------------------------------
//--------------------------------------------------------------------------
template<class entity>
CCellSpacePartition<entity>::CCellSpacePartition(double  width,      //width of 2D space
                                               double  height,       //height of 2D space    
																							 int		cellsSizeX,    //Size of cell horizontally
																							 int		cellsSizeY,    //Size of cell vertically
                                               int    MaxEntitys):   //maximum number of entities to partition
																																	m_dWorldWidth(width),
																																	m_dWorldHeight(height),
																																	m_dCellSizeX(cellsSizeX),
																																	m_dCellSizeY(cellsSizeY),
																																	m_Neighbors(MaxEntitys, entity())
{  
	m_iNumCellsX = m_dWorldWidth/m_dCellSizeX;
	m_iNumCellsY = m_dWorldHeight/m_dCellSizeY;

	double left, right, bot, top;

  //create the cells
  for (double y = -m_dWorldHeight/2.0; y < m_dWorldHeight/2.0; y+=m_dCellSizeY){
    for (double x = -m_dWorldWidth/2.0; x < m_dWorldWidth/2.0; x+=m_dCellSizeY){
      left  = x;
      right = left + m_dCellSizeX;
      bot   = y;
			top   = bot + m_dCellSizeY;

      m_Cells.push_back(Cell<entity>(Vector2D(left, top), Vector2D(right, bot)));
    }
  }
}

//----------------------- CalculateNeighbors ----------------------------
//
//  This must be called to create the vector of neighbors.This method 
//  examines each cell within range of the _vTarget, If the 
//  cells contain entities then they are tested to see if they are situated
//  within the _vTarget's neighborhood region. If they are they are added to
//  neighbor list
//------------------------------------------------------------------------
template<class entity>
void CCellSpacePartition<entity>::CalculateNeighbors(Vector2D TargetPos,
                                                    double   QueryRadius)
{
  //create an iterator and set it to the beginning of the neighbor vector
  std::vector<entity>::iterator curNbor = m_Neighbors.begin();
  
  //create the query box that is the bounding box of the _vTarget's query
  //area
  CBox3D QueryBox(TargetPos - Vector2D(QueryRadius, QueryRadius),
                            TargetPos + Vector2D(QueryRadius, QueryRadius));

  //iterate through each cell and test to see if its bounding box overlaps
  //with the query box. If it does and it also contains entities then
  //make further proximity tests.
  std::vector<Cell<entity> >::iterator curCell;

  for (curCell=m_Cells.begin(); curCell!=m_Cells.end(); ++curCell){
    //test to see if this cell contains members and if it overlaps the query box
    if (curCell->BBox.isOverlappedWith(QueryBox) && !curCell->Members.empty()){
      //add any entities found within query radius to the neighbor list
      std::list<entity>::iterator it = curCell->Members.begin();

      for (it; it!=curCell->Members.end(); ++it){     
        if (Vec2DDistanceSq((*it)->GetPos2D(), TargetPos) < QueryRadius*QueryRadius){
          *curNbor++ = *it;
        }
      }    
    }
  }//next cell

  //mark the end of the list with a zero.
  *curNbor = 0;
}

//--------------------------- Empty --------------------------------------
//
//  clears the cells of all entities
//------------------------------------------------------------------------
template<class entity>
void CCellSpacePartition<entity>::EmptyCells(){
  std::vector<Cell<entity> >::iterator it = m_Cells.begin();

  for (it; it!=m_Cells.end(); ++it){
    it->Members.clear();
  }
}

//--------------------- PositionToIndex ----------------------------------
//
//  Given a 2D vector representing a position within the game world, this
//  method calculates an index into its appropriate cell
//------------------------------------------------------------------------
template<class entity>
inline int CCellSpacePartition<entity>::PositionToIndex(const Vector2D& pos)const{
  int idx = static_cast<int>(m_iNumCellsX * pos.x / m_dWorldWidth) + 
            static_cast<int>(((m_iNumCellsY) * pos.y / m_dWorldHeight) * m_iNumCellsX);

  //if the entity's position is equal to Vector2D(m_dWorldWidth, m_dWorldHeight)
  //then the index will overshoot. We need to check for this and adjust
  if (idx > (int)(m_Cells.size()-1)) idx = m_Cells.size()-1;

  return idx;
}

//----------------------- AddEntity --------------------------------------
//
//  Used to add the entitys to the data structure
//------------------------------------------------------------------------
template<class entity>
inline void CCellSpacePartition<entity>::AddEntity(const entity& ent){ 
  assert (ent);

  int sz = m_Cells.size();
  int idx = PositionToIndex(ent->GetPos2D());
  
  m_Cells[idx].Members.push_back(ent);
}

//----------------------- UpdateEntity -----------------------------------
//
//  Checks to see if an entity has moved cells. If so the data structure
//  is updated accordingly
//------------------------------------------------------------------------
template<class entity>
inline void CCellSpacePartition<entity>::UpdateEntity(const entity& ent, Vector2D OldPos){
  //if the index for the old pos and the new pos are not equal then
  //the entity has moved to another cell.
  int OldIdx = PositionToIndex(OldPos);
  int NewIdx = PositionToIndex(ent->GetPos2D());

  if (NewIdx == OldIdx) return;

  //the entity has moved into another cell so delete from current cell
  //and add to new one
  m_Cells[OldIdx].Members.remove(ent);
  m_Cells[NewIdx].Members.push_back(ent);
}

//-------------------------- UpdateCells -----------------------------------
//--------------------------------------------------------------------------
template<class entity>
inline void CCellSpacePartition<entity>::UpdateCells(){
  std::vector<Cell<entity> >::iterator curCell;

  for (curCell=m_Cells.begin(); curCell!=m_Cells.end(); ++curCell){
		curCell->BBox.Update();
  }
}

//-------------------------- RenderCells -----------------------------------
//--------------------------------------------------------------------------
template<class entity>
void CCellSpacePartition<entity>::RenderCells(ID3DXLine* _pLine)const{
  std::vector<Cell<entity> >::const_iterator curCell;

  for (curCell=m_Cells.begin(); curCell!=m_Cells.end(); ++curCell){
		_pLine->SetWidth(curCell->BBox.GetLineWeight());
		_pLine->Begin();
		curCell->BBox.Render(_pLine, &D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f), false);
  }
}

//-------------------------- RenderCellsCoordinate -------------------------
//--------------------------------------------------------------------------
template<class entity>
void CCellSpacePartition<entity>::RenderCellsCoordinate(ID3DXSprite* p_pSprite, ID3DXFont* _pFont)const{
  std::vector<Cell<entity> >::const_iterator curCell;
  for (curCell=m_Cells.begin(); curCell!=m_Cells.end(); ++curCell){
		curCell->BBox.RenderCoordinateXY(&Vector2D(curCell->BBox.Left(), curCell->BBox.Bottom()));
  }
	//curCell->BBox.RenderCoordinateXY(&Vector2D(curCell->BBox.Left(), curCell->BBox.Top()));

	D3DXMATRIXA16 mtMatrix;

	// 월드 좌표를 원점으로 되돌린다.
	D3DXMatrixIdentity(&mtMatrix);
	p_pSprite->SetTransform(&mtMatrix);
}

#endif