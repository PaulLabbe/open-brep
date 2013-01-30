#include "Manifold.h"
#include <xercesc/sax2/SAX2XMLReader.hpp>
#include <xercesc/sax2/XMLReaderFactory.hpp>
#include <xercesc/sax2/DefaultHandler.hpp>
#include <xercesc/util/XMLString.hpp>

#include <iostream>

using namespace std;
using namespace xercesc;

#include "GeometryHandler.h"
#include "DocumentOrchestrator.h"


int main (int argc, char* args[]) 
{
cerr << "//@xmlReader;" << " argc=" << argc << endl;
   try 
   {
      XMLPlatformUtils::Initialize();
   }
   catch (const XMLException& toCatch) 
   {

      char* message = XMLString::transcode(toCatch.getMessage());
      cout << "Error during initialization! :\n";
      cout << "Exception message is: \n"
           << message << "\n";
      XMLString::release(&message);
      return 1;
   }
   
   const char* xmlFile = (argc==2)?args[1]:"x1.xml";
   std::shared_ptr< SAX2XMLReader> parser (XMLReaderFactory::createXMLReader());
   parser->setFeature(XMLUni::fgSAX2CoreValidation, true);
   parser->setFeature(XMLUni::fgSAX2CoreNameSpaces, true);   // optional

   DocumentOrchestrator orchestrator( *parser );
   
   Geo::Geometry theGeo;
   std::shared_ptr<GeometryHandler> geoHandler(new GeometryHandler(orchestrator,theGeo));
   orchestrator.push( geoHandler.get() );
   try 
   {
      parser->parse(xmlFile);
   }
   catch (const XMLException& toCatch) 
   {
      char* message = XMLString::transcode(toCatch.getMessage());
      cout << "Exception message is: \n"
           << message << "\n";
      XMLString::release(&message);
      return -1;
   }
   catch (const SAXParseException& toCatch) 
   {
      char* message = XMLString::transcode(toCatch.getMessage());
      cout << "Exception message is: \n"
           << message << "\n";
      XMLString::release(&message);
      return -1;
   }
   catch (...) 
   {
      cout << "Unexpected Exception \n" ;
      return -1;
   }
   
   return 0;
}
