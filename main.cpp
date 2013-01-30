/**
 * @file pisax2mainhandler.cpp Fichier contenant l'implantation des m�thodes
 * de la classe PI_SAX2_MAIN_HANDLER.
 */
#include "pisax2mainhandler.h"

#include <iostream>
#include <memory>

#include <xercesc/sax2/Attributes.hpp>

#include "xmlstr.h"
#include "pifichxml.h"
#include "pisax2champhandler.h"
#include "pisax2geohandler.h"

using namespace std;
using namespace xercesc;

/**
 * @param fichXml Gestionnaire d'import xml
 */
PI_SAX2_MAIN_HANDLER::PI_SAX2_MAIN_HANDLER(
   PI_FICHIER_IMPORT_XML& fichXml
)
:  PI_SAX2_BASE_HANDLER(fichXml)
{
}

PI_SAX2_MAIN_HANDLER::~PI_SAX2_MAIN_HANDLER()
{
}

/*
 * Dans cette fonction, le gestionnaire principale s'occupe d'aiguiller
 * les sous-gestionnaires d'elements plus specifiques, selon l'element
 * rencontre
 * 
 * @param uri : voir classe xercesc::DefaultHandler
 * @param localname : voir classe xercesc::DefaultHandler
 * @param qname : voir classe xercesc::DefaultHandler
 * @param attrs : voir classe xercesc::DefaultHandler
 */
void PI_SAX2_MAIN_HANDLER::startElement(
   const XMLCh*const uri,
   const XMLCh*const localname,
   const XMLCh*const qname,
   const Attributes& attrs
)
{
   PI_SAX2_BASE_HANDLER::startElement(uri, localname, qname, attrs);

   // Selon le nom du start element, on instancie et empile le gestionnaire
   // appropri�
   if (element_courant == "version")
   {
      cout << "Version du fichier :"
         "\nmajor: "
         << XML_TO_STD_STR( attrs.getValue(0, STD_TO_XML_STR("major")) )
         << "\nminor: " 
         << XML_TO_STD_STR( attrs.getValue(0, STD_TO_XML_STR("minor")) )
         << "\nrevision: "
         << XML_TO_STD_STR( attrs.getValue(0, STD_TO_XML_STR("revision")) )
         << endl;
   }
   else if ( element_courant == "champ" )
   {
      auto_ptr<PI_SAX2_BASE_HANDLER> nouvGest(
         new PI_SAX2_CHAMP_HANDLER(fich_xml, attrs)
      );

      fich_xml.empilerHandler(nouvGest);
   }
   else if ( element_courant == "geometrie" )
   {
      auto_ptr<PI_SAX2_BASE_HANDLER> nouvGest(
         new PI_SAX2_GEO_HANDLER(fich_xml, attrs)
      );

      fich_xml.empilerHandler(nouvGest);
   }
   else 
   { 
      cout << "L'element : " << element_courant << " a �t� trouv�" << endl;
   }
}

void PI_SAX2_MAIN_HANDLER::endElement(
      const XMLCh *const uri,
      const XMLCh *const localname,
      const XMLCh *const qname
)
{
   const string qname_str = XML_TO_STD_STR(qname);

   if ( qname_str == "pie" )
   {
      fich_xml.depilerHandler();
   }
}
