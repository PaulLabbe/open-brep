#ifndef VertexHandler_h_included
#define VertexHandler_h_included

#include "Manifold.h"
#include "DocumentOrchestrator.h"
#include "IdentificatorHandler.h"
#include "ElementHandler.h"


class VertexHandler : public ElementHandler
{
public:
   VertexHandler(DocumentOrchestrator& orchestrator, Geo::Geometry& geo)
      : _theOrchestrator(orchestrator), _theGeometry(geo), _theVertexId(0) { };
   void startElement(
                     const XMLCh* const    uri,
                     const XMLCh* const    localname,
                     const XMLCh* const    qname,
                     const xercesc::Attributes&     attrs
                     );
   void endElement(const XMLCh *const 	uri,
                   const XMLCh *const 	localname,
                   const XMLCh *const 	qname	 
                   );	
   void fatalError(const xercesc::SAXParseException&);
   const std::string& getName() const ;
   static const std::string& getElementName();
private:
   DocumentOrchestrator& _theOrchestrator;
   Geo::Geometry& _theGeometry;
   std::shared_ptr< ElementHandler> _theIdentificatorHandler;
   int _theVertexId;
};

#endif
