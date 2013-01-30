#include "StartVertexHandler.h"
#include "IdentificatorHandler.h"
#include <iostream>

static std::string vertexName="StartVertex";
const std::string& StartVertexHandler::getName() const { return vertexName; };
const std::string& StartVertexHandler::getElementName() { return vertexName; };

void StartVertexHandler::startElement(const XMLCh* const    uri,
                                     const XMLCh* const    localname,
                                     const XMLCh* const    qname,
                                     const xercesc::Attributes&     attrs)
{
   char* message = xercesc::XMLString::transcode(localname);
   std::cout << "StartVertex saw element: "<< message << std::endl;
   
   if (IdentificatorHandler::getElementName()==message)
   {
      _theCurrentHandler.reset(new IdentificatorHandler( _theOrchestrator,_theStartVertexId) );
      _theOrchestrator.push(_theCurrentHandler.get());
   }
   xercesc::XMLString::release(&message);
}

void StartVertexHandler::endElement(const XMLCh *const uri,
                                   const XMLCh *const localname,
                                   const XMLCh *const qname)
{
   char* message = xercesc::XMLString::transcode(localname);
   //   std::cout << "StartVertex saw end localname: "<< message << " while id=" << _theIdentificatorHandler->getIdentificator() << std::endl;
   xercesc::XMLString::release(&message);
   _theOrchestrator.pop();
   _theCurrentHandler.reset();
};

void StartVertexHandler::fatalError(const xercesc::SAXParseException& exception)
{
   char* message = xercesc::XMLString::transcode(exception.getMessage());
   std::cout << "Fatal Error: " << message
             << " at line: " << exception.getLineNumber()
             << std::endl;
   xercesc::XMLString::release(&message);
}
