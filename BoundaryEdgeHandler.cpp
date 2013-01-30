#include "XMLStringer.h"
#include "BoundaryEdgeHandler.h"
#include "IdentificatorHandler.h"
#include <iostream>

static std::string edgeName="BoundaryEdge";
const std::string& BoundaryEdgeHandler::getElementName() { return edgeName; };
const std::string& BoundaryEdgeHandler::getName() const { return edgeName; };

void BoundaryEdgeHandler::startElement(const XMLCh* const    uri,
                                     const XMLCh* const    localname,
                                     const XMLCh* const    qname,
                                     const xercesc::Attributes&     attrs)
{
   XMLStringer message(localname);

   //   std::cout << "BoundaryEdge saw element: "<< message << std::endl;
   
   if (IdentificatorHandler::getElementName()==message.getString())
   {
      _theLoopIds.push_back(0);
      _theCurrentHandler.reset(new IdentificatorHandler( _theOrchestrator,_theLoopIds[_theLoopIds.size()-1]) );
      _theOrchestrator.push(_theCurrentHandler.get());
   }
}

void BoundaryEdgeHandler::endElement(const XMLCh *const uri,
                                   const XMLCh *const localname,
                                   const XMLCh *const qname)
{
   char* message = xercesc::XMLString::transcode(localname);
   std::cout << "BoundaryEdge saw end localname: "<< message << std::endl;
   if ( BoundaryEdgeHandler::getElementName()==message)
   {
      _theOrchestrator.pop();
      _theCurrentHandler.reset();
   }
   else throw xercesc::SAXParseException(localname, *_theLocator);
   xercesc::XMLString::release(&message);
};

void BoundaryEdgeHandler::fatalError(const xercesc::SAXParseException& exception)
{
   char* message = xercesc::XMLString::transcode(exception.getMessage());
   std::cout << "Fatal Error: " << message
             << " at line: " << exception.getLineNumber()
             << std::endl;
   xercesc::XMLString::release(&message);
}
