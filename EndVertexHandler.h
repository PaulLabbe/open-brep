#ifndef EndVertexHandler_h_included
#define EndVertexHandler_h_included

#include "Manifold.h"
#include "DocumentOrchestrator.h"
#include "IdentificatorHandler.h"


class EndVertexHandler : public ElementHandler
{
public:
   EndVertexHandler(DocumentOrchestrator& orchestrator, int& endVId)
      : _theOrchestrator(orchestrator), _theEndVertexId(endVId) { };
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
   std::shared_ptr< ElementHandler> _theCurrentHandler;
   int& _theEndVertexId;
};

#endif
