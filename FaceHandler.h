#ifndef FaceHandler_h_included
#define FaceHandler_h_included

#include "Manifold.h"
#include "DocumentOrchestrator.h"
#include "IdentificatorHandler.h"
#include "StartVertexHandler.h"
#include "EndVertexHandler.h"

#include <vector>

class FaceHandler : public ElementHandler
{
public:
   typedef std::vector<int> LoopIds;
public:
   FaceHandler(DocumentOrchestrator& orchestrator, Geo::Geometry& geo)
      : _theOrchestrator(orchestrator), _theGeometry(geo), _theFaceId(0) { };
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
   int _theFaceId;
   LoopIds _theLoopIds;
};

#endif
