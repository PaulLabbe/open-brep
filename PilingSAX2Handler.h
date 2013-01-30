#include <xercesc/sax2/SAX2XMLReader.hpp>
#include <xercesc/sax2/XMLReaderFactory.hpp>
#include <xercesc/sax2/DefaultHandler.hpp>
#include <xercesc/util/XMLString.hpp>
#include <xercesc/sax2/DefaultHandler.hpp>

#include <iostream>

using namespace std;
using namespace xercesc;

class CompositeSAX2Handler : public DefaultHandler 
{
public:
   CompositeSAX2Handler(Geometry& owner)
      : _theGeometry(owner) { };
   virtual ~CompositeSAX2Handler() {};
   virtual void startElement(
                     const   XMLCh* const    uri,
                     const   XMLCh* const    localname,
                     const   XMLCh* const    qname,
                     const   Attributes&     attrs
                     )=0;
   virtual void endElement(const XMLCh *const 	uri,
                           const XMLCh *const 	localname,
                           const XMLCh *const 	qname	 
                           )=0;	
   void fatalError(const SAXParseException&);
   const std::string& getXMLHandlerName() const;
private:
   std::list<CompositeSAX2Handler> _composedOf;
};

void PilingSAX2Handler::startElement(const   XMLCh* const    uri,
                            const   XMLCh* const    localname,
                            const   XMLCh* const    qname,
                            const   Attributes&     attrs)
{

    char* message = XMLString::transcode(localname);
    cout << "I saw element: "<< message << endl;
    for( std::list<CompositeSAX2Handler>::iterator it=_composedOf.begin();
         it != _composedOf.end(); ++it)
    {
       if ( it->getXMLHandlerName() == message )
       {
          
       }
    }
    XMLString::release(&message);
}

void PilingSAX2Handler::fatalError(const SAXParseException& exception)
{
    char* message = XMLString::transcode(exception.getMessage());
    cout << "Fatal Error: " << message
         << " at line: " << exception.getLineNumber()
         << endl;
    XMLString::release(&message);
}
