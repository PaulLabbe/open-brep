#include "EndVertexHandler.h"
#include "IdentificatorHandler.h"
#include <iostream>

static std::string vertexName="EndVertex";
const std::string& EndVertexHandler::getElementName() { return vertexName; };
const std::string& EndVertexHandler::getName() const { return vertexName; };

void EndVertexHandler::startElement(const XMLCh* const    uri,
                                    const XMLCh* const    localname,
                                    const XMLCh* const    qname,
                                    const xercesc::Attributes&     attrs)
{
   char* message = xercesc::XMLString::transcode(localname);
   std::cout << "EndVertex saw element: "<< message << std::endl;
   
   if (IdentificatorHandler::getElementName()==message)
   {
      _theCurrentHandler.reset(new IdentificatorHandler( _theOrchestrator, _theEndVertexId) );
      _theOrchestrator.push(_theCurrentHandler.get());
   }
   xercesc::XMLString::release(&message);
}

void EndVertexHandler::endElement(const XMLCh *const uri,
                                  const XMLCh *const localname,
                                  const XMLCh *const qname)
{
   char* message = xercesc::XMLString::transcode(localname);
   std::cout << "EndVertex saw end localname: "<< message << std::endl;
   xercesc::XMLString::release(&message);
   _theOrchestrator.pop();
   _theCurrentHandler.reset();
};

void EndVertexHandler::fatalError(const xercesc::SAXParseException& exception)
{
   char* message = xercesc::XMLString::transcode(exception.getMessage());
   std::cout << "Fatal Error: " << message
             << " at line: " << exception.getLineNumber()
             << std::endl;
   xercesc::XMLString::release(&message);
}
