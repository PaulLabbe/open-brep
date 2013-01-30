#ifndef GeometryHandler_h_included
#define GeometryHandler_h_included

// #include <xercesc/sax2/SAX2XMLReader.hpp>
// #include <xercesc/util/XMLString.hpp>
// #include <xercesc/sax2/Attributes.hpp>

#include "Manifold.h"
#include "DocumentOrchestrator.h"
#include "ElementHandler.h"

using namespace std;
using namespace xercesc;
using namespace Geo;

class GeometryHandler : public ElementHandler
{
public:
   GeometryHandler(DocumentOrchestrator& orchestrator, Geometry& owner)
      : _theOrchestrator(orchestrator), _theGeometry(owner) {};
   void startElement(
                     const   XMLCh* const    uri,
                     const   XMLCh* const    localname,
                     const   XMLCh* const    qname,
                     const   Attributes&     attrs);
   void endElement(const XMLCh *const 	uri,
                   const XMLCh *const 	localname,
                   const XMLCh *const 	qname);
   void fatalError(const SAXParseException&);
   const std::string& getElementName();
   const std::string& getName() const;
private:
   DocumentOrchestrator& _theOrchestrator;
   Geometry& _theGeometry;
   std::shared_ptr<ElementHandler> _theCurrentHandler;
};

#endif
