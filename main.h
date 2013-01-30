#ifndef _HEADER_XML_IMPORT_PI_SAX2_MAIN_HANDLER_
#define _HEADER_XML_IMPORT_PI_SAX2_MAIN_HANDLER_

/**
 * @file pisax2mainhandler.h Description de la classe PI_SAX2_MAIN_HANDLER
 */

#include <memory>
#include <map>
#include <string>

#include <xercesc/util/XMLChar.hpp>

#include "pisax2basehandler.h"

/*
 * @brief Classe principale gerant les evenements pour diriger le parsing
 *
 * Cette classe sert a deleguer le parsing de chaque objet aux classes plus
 * specifiques
 */
class PI_SAX2_MAIN_HANDLER : public PI_SAX2_BASE_HANDLER
{
public:
   /// Constructeur par param�tres
   PI_SAX2_MAIN_HANDLER(PI_FICHIER_IMPORT_XML& fichXml);

   /// Destructeur
   virtual ~PI_SAX2_MAIN_HANDLER(); 

   /// M�thode h�rit�e de la classe xercesc::DefaultHandler
   virtual void startElement(
      const XMLCh *const uri,
      const XMLCh *const localname,
      const XMLCh *const qname,
      const xercesc::Attributes& attrs
   );

   /// M�thode h�rit�e de la classe xercesc::DefaultHandler
   virtual void endElement(
      const XMLCh *const uri,
      const XMLCh *const localname,
      const XMLCh *const qname
   );

private:
   /// Garde pour m�thodes non implant�es
   PI_SAX2_MAIN_HANDLER();
   /// Garde pour m�thodes non implant�es
   PI_SAX2_MAIN_HANDLER(const PI_SAX2_MAIN_HANDLER&);
   /// Garde pour m�thodes non implant�es
   const PI_SAX2_MAIN_HANDLER& operator= (const PI_SAX2_MAIN_HANDLER&);
};

#endif
