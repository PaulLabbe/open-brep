#ifndef StartVertexHandler_h_included
#define StartVertexHandler_h_included

#include "Manifold.h"
#include "DocumentOrchestrator.h"
#include "IdentificatorHandler.h"


class StartVertexHandler : public xercesc::DefaultHandler 
{
public:
   StartVertexHandler(DocumentOrchestrator& orchestrator, Geo::Geometry& owner)
      : _theOrchestrator(orchestrator), _theGeometry(owner) { };
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
   static const std::string& getName();
private:
   DocumentOrchestrator& _theOrchestrator;
   Geo::Geometry _theGeometry;
   std::shared_ptr< IdentificatorHandler> _theIdentificatorHandler;
};

#endif
