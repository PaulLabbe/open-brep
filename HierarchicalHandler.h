#include <iostream>
#include <xercesc/sax2/SAX2XMLReader.hpp>
#include <xercesc/sax2/XMLReaderFactory.hpp>
#include <xercesc/sax2/DefaultHandler.hpp>
#include <xercesc/util/XMLString.hpp>
#include <xercesc/sax2/DefaultHandler.hpp>
#include <xercesc/sax2/Attributes.hpp>

using namespace std;
using namespace xercesc;
using namespace Geo;

class HierarchicalHandler
{
public:
   HierarchicalHandler(SAX2XMLReader& reader)
      : _theReader(reader) { };
   void startElement(
                     const   XMLCh* const    uri,
                     const   XMLCh* const    localname,
                     const   XMLCh* const    qname,
                     const   Attributes&     attrs);
   void endElement(const XMLCh *const 	uri,
                   const XMLCh *const 	localname,
                   const XMLCh *const 	qname);
    void fatalError(const SAXParseException&);
private:
   SAX2XMLReader& _theReader;
   std::stack< HierarchicalHandler
};

void HierarchicalHandler::startElement(const   XMLCh* const    uri,
                                       const   XMLCh* const    localname,
                                       const   XMLCh* const    qname,
                                       const   Attributes&     atts)
{
   for (XMLSize_t i = 0; i < atts.getLength(); i++) 
   {
      char* Qname = XMLString::transcode(atts.getQName(i));
      char* URI = XMLString::transcode(atts.getURI(i));
      char* type = XMLString::transcode(atts.getType(i));
      char* value = XMLString::transcode(atts.getValue(i));
cerr << "//@HierarchicalHandler;" << " Qname=" << Qname << " URI=" << URI << " type=" << type << " value=" << value << endl;
      XMLString::release(&Qname);
      XMLString::release(&URI);
      XMLString::release(&type);
      XMLString::release(&value);
      
   }
   char* message = XMLString::transcode(localname);
   cout << "I saw localname: "<< message << endl;
   XMLString::release(&message);

   char* messageURI = XMLString::transcode(uri);
   cout << "I saw uri: "<< messageURI << endl;
   XMLString::release(&messageURI);

   char* messageqname = XMLString::transcode(qname);
   cout << "I saw qname: "<< messageqname << endl;
   XMLString::release(&messageqname);

}

void HierarchicalHandler::endElement(const XMLCh *const uri,
                                     const XMLCh *const localname,
                                     const XMLCh *const qname)
{
   char* message = XMLString::transcode(localname);
   cout << "I saw end localname: "<< message << endl;
   XMLString::release(&message);

   char* messageURI = XMLString::transcode(uri);
   cout << "I saw end uri: "<< messageURI << endl;
   XMLString::release(&messageURI);

   char* messageqname = XMLString::transcode(qname);
   cout << "I saw end qname: "<< messageqname << endl;
   XMLString::release(&messageqname);
   
};

void HierarchicalHandler::fatalError(const SAXParseException& exception)
{
    char* message = XMLString::transcode(exception.getMessage());
    cout << "Fatal Error: " << message
         << " at line: " << exception.getLineNumber()
         << endl;
    XMLString::release(&message);
}
