#ifndef IdentificatorHandler_h_included
#define IdentificatorHandler_h_included

#include <string>
#include <xercesc/sax2/DefaultHandler.hpp>
#include "DocumentOrchestrator.h"

class IdentificatorHandler : public ElementHandler
{
public:
   IdentificatorHandler(DocumentOrchestrator& orchestrator, int& theId )
      : _theOrchestrator(orchestrator), _theIdentificator(theId) { };
   void characters(const XMLCh *const 	chars,
                   const XMLSize_t 	length);	
   void startElement(
                     const   XMLCh* const    uri,
                     const   XMLCh* const    localname,
                     const   XMLCh* const    qname,
                     const   xercesc::Attributes&     attrs
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
   int& _theIdentificator;
};

#endif
