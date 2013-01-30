#include "IdentificatorHandler.h"
#include <iostream>
#include <sstream>


static std::string IdName("Id");

const std::string& IdentificatorHandler::getElementName() { return IdName; };
const std::string& IdentificatorHandler::getName() const { return IdName; };

void IdentificatorHandler::startElement(const   XMLCh* const    uri,
                                        const   XMLCh* const    localname,
                                        const   XMLCh* const    qname,
                                        const   xercesc::Attributes&     attrs)
{
   char* message = xercesc::XMLString::transcode(localname);
    std::cout << "Id saw element: "<< message << std::endl;
    xercesc::XMLString::release(&message);
}

void IdentificatorHandler::endElement(const XMLCh *const uri,
                                      const XMLCh *const localname,
                                      const XMLCh *const qname)
{
   char* message = xercesc::XMLString::transcode(localname);
   std::cout << "Id saw end localname: "<< message << std::endl;
   xercesc::XMLString::release(&message);
   _theOrchestrator.pop();
};

void IdentificatorHandler::characters( const XMLCh* const chars, const XMLSize_t length)
{
   char* message = xercesc::XMLString::transcode(chars);
   std::cout << "Id saw string: "<< message << std::endl;
   std::string strVal( message );
   std::istringstream strstream( strVal);
   strstream >> _theIdentificator;
   xercesc::XMLString::release(&message);
}

void IdentificatorHandler::fatalError(const xercesc::SAXParseException& exception)
{
   char* message = xercesc::XMLString::transcode(exception.getMessage());
    std::cout << "Fatal Id Error: " << message
         << " at line: " << exception.getLineNumber()
         << std::endl;
    xercesc::XMLString::release(&message);
}
