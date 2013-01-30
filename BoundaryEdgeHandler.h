#ifndef BoundaryEdgeHandler_h_included
#define BoundaryEdgeHandler_h_included

#include "Manifold.h"
#include "DocumentOrchestrator.h"
#include "FaceHandler.h"

class BoundaryEdgeHandler : public ElementHandler
{
   typedef std::vector<int> LoopIds;
public:
   BoundaryEdgeHandler(DocumentOrchestrator& orchestrator, FaceHandler::LoopIds& loop)
      : _theOrchestrator(orchestrator), _theLoopIds(loop) { };
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
   std::shared_ptr< ElementHandler > _theCurrentHandler;
   LoopIds& _theLoopIds;
};

#endif
