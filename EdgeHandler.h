#ifndef EdgeHandler_h_included
#define EdgeHandler_h_included

#include "Manifold.h"
#include "DocumentOrchestrator.h"
#include "IdentificatorHandler.h"
#include "StartVertexHandler.h"
#include "EndVertexHandler.h"

class EdgeHandler : public ElementHandler
{
public:
   EdgeHandler(DocumentOrchestrator& orchestrator, Geo::Geometry& geo)
      : _theOrchestrator(orchestrator), _theGeometry(geo), _theEdgeId(0), _theStartVertexId(0), _theEndVertexId(0) { };
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
   static const std::string& getElementName();
   const std::string& getName() const;
private:
   DocumentOrchestrator& _theOrchestrator;
   Geo::Geometry& _theGeometry;
   std::shared_ptr< ElementHandler > _theCurrentHandler;
   int _theEdgeId;
   int _theStartVertexId;
   int _theEndVertexId;
};

#endif
