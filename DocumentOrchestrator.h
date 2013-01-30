#ifndef DocumentOrchestrator_h_included
#define DocumentOrchestrator_h_included

#include <list>
#include <iostream>

#include <xercesc/sax2/SAX2XMLReader.hpp>
#include "ElementHandler.h"

class DocumentOrchestrator
{
public:
   DocumentOrchestrator(xercesc::SAX2XMLReader& reader)
      : _theReader(reader) { };
   void push( ElementHandler* handler )
   {
      _theStack.push_back( handler );
      _theReader.setContentHandler( handler );
      _theReader.setErrorHandler( handler );
      std::cout << "pushStack(" << _theStack.size();
      for( std::list< ElementHandler* >::iterator it=_theStack.begin();
           it != _theStack.end(); ++it )
      {
         std::cout << "->" << (*it)->getName();
      }
      std::cout << ")\n";
   }
   void pop()
   {
      _theStack.pop_back();
      _theReader.setContentHandler( _theStack.back() );
      _theReader.setErrorHandler(_theStack.back());
      std::cout << "popStack(" << _theStack.size();
      for( std::list< ElementHandler* >::iterator it=_theStack.begin();
           it != _theStack.end(); ++it )
      {
         std::cout << "->" << (*it)->getName();
      }
      std::cout << ")\n";
   }
   ElementHandler* currentHandler(void) { return _theStack.back(); };
private:
   xercesc::SAX2XMLReader& _theReader;
   std::list< ElementHandler* > _theStack;
};

#endif
