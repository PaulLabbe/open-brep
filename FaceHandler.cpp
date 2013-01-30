#include "FaceHandler.h"
#include "IdentificatorHandler.h"
#include "LoopHandler.h"
#include <iostream>

static std::string edgeName="Face";
const std::string& FaceHandler::getElementName() { return edgeName; };
const std::string& FaceHandler::getName() const { return edgeName; };

void FaceHandler::startElement(const XMLCh* const    uri,
                                     const XMLCh* const    localname,
                                     const XMLCh* const    qname,
                                     const xercesc::Attributes&     attrs)
{
   char* message = xercesc::XMLString::transcode(localname);
   //   std::cout << "Face saw element: "<< message << std::endl;
   
   if (IdentificatorHandler::getElementName()==message)
   {
      _theCurrentHandler.reset(new IdentificatorHandler( _theOrchestrator,_theFaceId) );
      _theOrchestrator.push(_theCurrentHandler.get());
   }
   else if  (LoopHandler::getElementName()==message)
   {
      _theCurrentHandler.reset(new LoopHandler( _theOrchestrator,_theLoopIds) );
      _theOrchestrator.push(_theCurrentHandler.get());
   }
   xercesc::XMLString::release(&message);
}

void FaceHandler::endElement(const XMLCh *const uri,
                                   const XMLCh *const localname,
                                   const XMLCh *const qname)
{
   char* message = xercesc::XMLString::transcode(localname);
   std::cout << "Face saw end localname: "<< message << std::endl;
   if ( FaceHandler::getElementName()==message)
   {
      _theGeometry.addFace(_theFaceId);
      _theOrchestrator.pop();
      _theCurrentHandler.reset();
   }
   xercesc::XMLString::release(&message);
};

void FaceHandler::fatalError(const xercesc::SAXParseException& exception)
{
   char* message = xercesc::XMLString::transcode(exception.getMessage());
   std::cout << "Fatal Error: " << message
             << " at line: " << exception.getLineNumber()
             << std::endl;
   xercesc::XMLString::release(&message);
}
