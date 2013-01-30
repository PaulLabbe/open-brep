#ifndef _Geometry_header
#define _Geometry_header

#include <list>
#include <map>
#include <memory>
#include <cassert>
#include <iostream>

class Manifold;
class Embedding;
class Mapping;
class Domain;
class Image;

namespace Geo
{
   class Vertex;
   class Edge;
   class Face;
   class Volume;
   
   class Loop;
   class Shell;
   
   class BndryVertex;
   class BndryEdge;
   class BndryFace;
   
   class BndryVertex
   {
   public:
      BndryVertex( Vertex* v):_theVertex(v) {};
      BndryVertex( const BndryVertex& other): _theVertex(other._theVertex) {};
      BndryVertex& operator=(const BndryVertex& mdd);
      virtual ~BndryVertex() {};
   private:
      Vertex* _theVertex;
   };
   
   class BndryEdge
   {
   public:
      BndryEdge( Edge* e, int dir): _theEdge(e), _theDirection( dir ) {};
      BndryEdge( const BndryEdge& other ): _theEdge( other._theEdge ), _theDirection( other._theDirection) {};
      virtual ~BndryEdge() {};
   private:
      Edge* _theEdge;
      int _theDirection;
   };

   class BndryFace
   {
      Face* _theFace;
      int direction;
   };
   
   class Loop
   {
   public:
      Loop( const std::list<BndryEdge>& edges ): _theLoop(edges) {};
      ~Loop( ) {};
   private:
      std::list<BndryEdge> _theLoop;
   };
   
   class Shell
   {
      std::list<BndryFace> _theFaces;
   };

   class Vertex
   {
   public:
      Vertex(int id):_id(id) {};
      virtual ~Vertex() {};
      int getId() const { return _id; }
   private:
      Vertex( const Vertex& );
      Vertex& operator=(const Vertex&);
      int _id;
   };

   class Edge
   {
   public:
      Edge(int id,Vertex* startVertex, Vertex* endVertex)
         : _id(id),_startVertex(NULL),_endVertex(NULL) 
      {
         _startVertex.reset(new BndryVertex(startVertex));
         _endVertex.reset(new BndryVertex(endVertex));
      };
      virtual ~Edge() {};
      int getId() const { return _id; }
   private:
      Edge( const Edge& );
      Edge& operator=(const Edge&);
      int _id;
      std::shared_ptr<BndryVertex> _startVertex;
      std::shared_ptr<BndryVertex> _endVertex;
   };
   
   class Face
   {
   public:
      Face(int id):_id(id) {};
      virtual ~Face() {};
      void AddLoop( const Loop& loop ) { _theLoops.push_back( loop ); };
      int getId() const { return _id; }
   private:
      Face( const Face& );
      Face& operator=(const Face&);
      int _id;
      std::list<Loop> _theLoops;
   };
   
   class Volume
   {
   public:
      Volume(int id):_id(id) {};
      virtual ~Volume() {};
      int getId() const { return _id; }
   private:
      Volume( const Volume& );
      Volume& operator=(const Volume&);
      int _id;
      std::list<Shell> _theShells;
   };
   class Geometry
   {
      typedef std::map<int,std::shared_ptr<Vertex>> VertexSet;
      typedef std::map<int,std::shared_ptr<Edge>> EdgeSet;
      typedef std::map<int,std::shared_ptr<Face>> FaceSet;
      typedef std::map<int,std::shared_ptr<Volume>> VolumeSet;

   public:
      Geometry( void ) {};

      virtual Vertex* addVertex( int id )
      {
         assert(_theVertices.find(id)==_theVertices.end());
         std::shared_ptr<Vertex> v(new Vertex(id));
         _theVertices[id]=v;
         return v.get();
      }
      virtual Edge* addEdge( int id, int startVertex, int endVertex )
      {
         assert( _theVertices.find(startVertex)!=_theVertices.end());
         assert( _theVertices.find(endVertex)!=_theVertices.end());
         assert( _theVertices.find(id)==_theVertices.end());
         std::shared_ptr<Edge> v(new Edge(id,_theVertices[startVertex].get(),_theVertices[endVertex].get()));
         _theEdges[id]=v;
         return v.get();
      }
      
      virtual Face* addFace( int id )
      {
         assert(_theFaces.find(id)==_theFaces.end());
         std::shared_ptr<Face> v(new Face(id));
         _theFaces[id]=v;
         return v.get();
      }
      void printVertices(std::ostream& o)
      {
         o<< "Vertices[";
         for( VertexSet::iterator it=_theVertices.begin();
              it != _theVertices.end(); ++it )
         {
            o<< " " << (*it).first;
         }
         o<< std::endl;
      }
      void printFaces(std::ostream& o) 
      {
         o<< "Faces[";
         for( FaceSet::iterator it=_theFaces.begin();
              it != _theFaces.end(); ++it )
         {
            o<< " " << (*it).first;
         }
         o<< std::endl;
      }
   private:
      Geometry( const Geometry& mdd);
      Geometry& operator=( const Geometry& mdd);

      VertexSet _theVertices;
      EdgeSet _theEdges;
      FaceSet _theFaces;
      VolumeSet _theVolumes;
   };
}

#endif
