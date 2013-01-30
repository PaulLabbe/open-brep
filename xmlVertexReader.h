#include <Manifold.h>
#include <xercesc/sax2/SAX2XMLReader.hpp>
#include <xercesc/sax2/XMLReaderFactory.hpp>
#include <xercesc/sax2/DefaultHandler.hpp>
#include <xercesc/util/XMLString.hpp>
#include <xercesc/sax2/DefaultHandler.hpp>

#include <iostream>

using namespace std;
using namespace xercesc;

class VertexSAX2Handler : public DefaultHandler 
{
public:
   VertexSAX2Handler(Geometry& owner)
      : _theGeometry(owner) { };
   void startElement(
                     const   XMLCh* const    uri,
                     const   XMLCh* const    localname,
                     const   XMLCh* const    qname,
                     const   Attributes&     attrs
                     );
   void endElement(const XMLCh *const 	uri,
                      const XMLCh *const 	localname,
                   const XMLCh *const 	qname	 
                   )	
    void fatalError(const SAXParseException&);
private:
   Geometry _theGeometry;
};

void VertexSAX2Handler::startElement(const   XMLCh* const    uri,
                            const   XMLCh* const    localname,
                            const   XMLCh* const    qname,
                            const   Attributes&     attrs)
{
 for (XMLSize_t i = 0; i < atts.getLength(); i++) {
  String Qname = atts.getQName(i);
  String URI = atts.getURI(i)
  String local = atts.GetLocalName(i)
  String type = atts.getType(i);
  String value = atts.getValue(i);

 }
    char* message = XMLString::transcode(localname);
    cout << "I saw element: "<< message << endl;
    XMLString::release(&message);
}

void VertexSAX2Handler::fatalError(const SAXParseException& exception)
{
    char* message = XMLString::transcode(exception.getMessage());
    cout << "Fatal Error: " << message
         << " at line: " << exception.getLineNumber()
         << endl;
    XMLString::release(&message);
}
