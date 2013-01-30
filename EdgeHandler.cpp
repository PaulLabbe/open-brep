#include "EdgeHandler.h"
#include "IdentificatorHandler.h"
#include "StartVertexHandler.h"
#include "EndVertexHandler.h"
#include <iostream>

static std::string edgeName="Edge";
const std::string& EdgeHandler::getElementName() { return edgeName; };
const std::string& EdgeHandler::getName() const { return edgeName; };

void EdgeHandler::startElement(const XMLCh* const    uri,
                                     const XMLCh* const    localname,
                                     const XMLCh* const    qname,
                                     const xercesc::Attributes&     attrs)
{
   char* message = xercesc::XMLString::transcode(localname);
   //   std::cout << "Edge saw element: "<< message << std::endl;
   
   if (IdentificatorHandler::getElementName()==message)
   {
      _theCurrentHandler.reset(new IdentificatorHandler( _theOrchestrator,_theEdgeId) );
      _theOrchestrator.push(_theCurrentHandler.get());
   }
   else if  (StartVertexHandler::getElementName()==message)
   {
      _theCurrentHandler.reset(new StartVertexHandler( _theOrchestrator,_theStartVertexId) );
      _theOrchestrator.push(_theCurrentHandler.get());
   }
   else if  (EndVertexHandler::getElementName()==message)
   {
      _theCurrentHandler.reset(new EndVertexHandler( _theOrchestrator,_theEndVertexId) );
      _theOrchestrator.push(_theCurrentHandler.get());
   }
   xercesc::XMLString::release(&message);
}

void EdgeHandler::endElement(const XMLCh *const uri,
                                   const XMLCh *const localname,
                                   const XMLCh *const qname)
{
   char* message = xercesc::XMLString::transcode(localname);
   std::cout << "Edge saw end localname: "<< message << std::endl;
   if ( EdgeHandler::getElementName()==message)
   {
      _theGeometry.addEdge(_theEdgeId, _theStartVertexId, _theEndVertexId);
      _theOrchestrator.pop();
      _theCurrentHandler.reset();
   }
   xercesc::XMLString::release(&message);
};

void EdgeHandler::fatalError(const xercesc::SAXParseException& exception)
{
   char* message = xercesc::XMLString::transcode(exception.getMessage());
   std::cout << "Fatal Error: " << message
             << " at line: " << exception.getLineNumber()
             << std::endl;
   xercesc::XMLString::release(&message);
}
