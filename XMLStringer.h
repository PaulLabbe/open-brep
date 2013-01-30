#ifndef XMLStringer_h_included
#define XMLStringer_h_included

#include <xercesc/util/XMLString.hpp>

class XMLStringer
{
public:
   XMLStringer( const XMLCh* message ) 
      : charEquivalence(xercesc::XMLString::transcode(message)) {};
   ~XMLStringer() { xercesc::XMLString::release( &charEquivalence );};
   const char* getString(void) const { return charEquivalence; };
   operator const char* () const { return charEquivalence; };
private:
   char* charEquivalence;
};

#endif
