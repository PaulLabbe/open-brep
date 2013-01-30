#ifndef StartVertexHandler_h_included
#define StartVertexHandler_h_included

#include "Manifold.h"
#include "DocumentOrchestrator.h"
#include "IdentificatorHandler.h"

class StartVertexHandler : public ElementHandler
{
public:
   StartVertexHandler(DocumentOrchestrator& orchestrator, int& vertexId )
      : _theOrchestrator(orchestrator), _theStartVertexId(vertexId) { };
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
   const std::string& getName()const;
private:
   DocumentOrchestrator& _theOrchestrator;
   std::shared_ptr< ElementHandler> _theCurrentHandler;
   int& _theStartVertexId;
};

#endif
