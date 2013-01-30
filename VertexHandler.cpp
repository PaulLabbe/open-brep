#include "VertexHandler.h"
#include "IdentificatorHandler.h"
#include <iostream>

static std::string vertexName="Vertex";
const std::string& VertexHandler::getElementName() { return vertexName; };
const std::string& VertexHandler::getName() const { return vertexName; };

void VertexHandler::startElement(const XMLCh* const    uri,
                                     const XMLCh* const    localname,
                                     const XMLCh* const    qname,
                                     const xercesc::Attributes&     attrs)
{
   char* message = xercesc::XMLString::transcode(localname);
   std::cout << "Vertex saw element: "<< message << std::endl;
   
   if (IdentificatorHandler::getElementName()==message)
   {
      _theIdentificatorHandler.reset(new IdentificatorHandler( _theOrchestrator,_theVertexId) );
      _theOrchestrator.push(_theIdentificatorHandler.get());
   }

   xercesc::XMLString::release(&message);
}

void VertexHandler::endElement(const XMLCh *const uri,
                                   const XMLCh *const localname,
                                   const XMLCh *const qname)
{
   char* message = xercesc::XMLString::transcode(localname);
   //   std::cout << "Vertex saw end localname: "<< message << " while id=" << _theIdentificatorHandler->getIdentificator() << std::endl;
   xercesc::XMLString::release(&message);
   _theGeometry.addVertex( _theVertexId );
   _theOrchestrator.pop();
   _theIdentificatorHandler.reset();
};

void VertexHandler::fatalError(const xercesc::SAXParseException& exception)
{
   char* message = xercesc::XMLString::transcode(exception.getMessage());
   std::cout << "Fatal Error: " << message
             << " at line: " << exception.getLineNumber()
             << std::endl;
   xercesc::XMLString::release(&message);
}
