#ifndef ElementHandler_h_included
#define ElementHandler_h_included

#include <string>
#include <xercesc/sax2/DefaultHandler.hpp>

class ElementHandler : public xercesc::DefaultHandler
{
public:
   ElementHandler(void) : _theLocator(NULL) {};
   virtual const std::string& getName(void) const=0;
   virtual void setDocumentLocator (const xercesc::Locator *const locator)
   {
      _theLocator=locator;
   };
protected:
   const xercesc::Locator* _theLocator;
};

#endif
