#include "GeometryHandler.h"
#include "VertexHandler.h"
#include "EdgeHandler.h"
#include "FaceHandler.h"
#include <iostream>

static std::string name("Geometry");
const std::string& GeometryHandler::getElementName() { return name;};
const std::string& GeometryHandler::getName() const { return name;};

void GeometryHandler::startElement(const   XMLCh* const    uri,
                                       const   XMLCh* const    localname,
                                       const   XMLCh* const    qname,
                                       const   Attributes&     atts)
{
   char* message = XMLString::transcode(localname);

   if (VertexHandler::getElementName()==message)
   {
      _theCurrentHandler.reset(new VertexHandler( _theOrchestrator,_theGeometry));
      _theOrchestrator.push(_theCurrentHandler.get());
   }
   else if (EdgeHandler::getElementName()==message)
   {
      _theCurrentHandler.reset(new EdgeHandler( _theOrchestrator,_theGeometry ));
      _theOrchestrator.push(_theCurrentHandler.get());
   }
   else if (FaceHandler::getElementName()==message)
   {
      _theCurrentHandler.reset(new FaceHandler( _theOrchestrator,_theGeometry ));
      _theOrchestrator.push(_theCurrentHandler.get());
   }

   XMLString::release(&message);
}

void GeometryHandler::endElement(const XMLCh *const uri,
                                     const XMLCh *const localname,
                                     const XMLCh *const qname)
{
   char* message = XMLString::transcode(localname);
   std::cout << "Geo saw end localname: "<< message << std::endl;
   XMLString::release(&message);
};

void GeometryHandler::fatalError(const SAXParseException& exception)
{
    char* message = XMLString::transcode(exception.getMessage());
    std::cout << "Fatal Geo Error: " << message
              << " at line: " << exception.getLineNumber()
              << std::endl;
    XMLString::release(&message);
}
