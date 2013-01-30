#include "LoopHandler.h"
#include "IdentificatorHandler.h"
#include "BoundaryEdgeHandler.h"
#include <iostream>

static std::string edgeName="Loop";
const std::string& LoopHandler::getElementName() { return edgeName; };
const std::string& LoopHandler::getName() const { return edgeName; };

void LoopHandler::startElement(const XMLCh* const    uri,
                                     const XMLCh* const    localname,
                                     const XMLCh* const    qname,
                                     const xercesc::Attributes&     attrs)
{
   char* message = xercesc::XMLString::transcode(localname);
   //   std::cout << "Loop saw element: "<< message << std::endl;
   
   if (BoundaryEdgeHandler::getElementName()==message)
   {
      _theCurrentHandler.reset(new BoundaryEdgeHandler( _theOrchestrator,_theLoopIds) );
      _theOrchestrator.push(_theCurrentHandler.get());
   }
   xercesc::XMLString::release(&message);
}

void LoopHandler::endElement(const XMLCh *const uri,
                                   const XMLCh *const localname,
                                   const XMLCh *const qname)
{
   char* message = xercesc::XMLString::transcode(localname);
   std::cout << "Loop saw end localname: "<< message << std::endl;
   if ( LoopHandler::getElementName()==message)
   {
      _theOrchestrator.pop();
      _theCurrentHandler.reset();
   }
   xercesc::XMLString::release(&message);
};

void LoopHandler::fatalError(const xercesc::SAXParseException& exception)
{
   char* message = xercesc::XMLString::transcode(exception.getMessage());
   std::cout << "Fatal Error: " << message
             << " at line: " << exception.getLineNumber()
             << std::endl;
   xercesc::XMLString::release(&message);
}
