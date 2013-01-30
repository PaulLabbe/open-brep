#ifndef _HEADER_XML_IMPORT_PI_SAX2_BASE_HANDLER_
#define _HEADER_XML_IMPORT_PI_SAX2_BASE_HANDLER_

/**
 * @file pisax2basehandler.h Description de la classe PI_SAX2_BASE_HANDLER
 */

#include <string>
#include <memory>

#include <xercesc/sax2/DefaultHandler.hpp>

#include "pisujet.h"
#include "piobservateur.h"
#include "PI_ERREUR.h"

#include "xmlstr.h"

class PI_FICHIER_IMPORT_XML;

/**
 * @brief Classe de base abstraite poss�dant les caract�ristiques communes au
 * gestionnaire d'�v�nements SAX2 s'occupant du parsage du fichier xml.
 * 
 * L'ensemble des gestionnaires d'�v�nements devraient d�river de cette
 * classe.
 */
class StackableHandler
: public xercesc::DefaultHandler
{
public:
   /// Destructeur
   virtual ~PI_SAX2_BASE_HANDLER();

   /// M�thode h�rit�e de la classe PI_OBSERVATEUR
   virtual void miseAJour(PI_SUJET& s);

   /// M�thode h�rit�e de la classe xercesc::DefaultHandler
   virtual void startElement(
      const XMLCh *const uri,
      const XMLCh *const localname,
      const XMLCh *const qname,
      const xercesc::Attributes& attrs
   );

protected:
   /// Constructeur par param�tres
   PI_SAX2_BASE_HANDLER(PI_FICHIER_IMPORT_XML& fichXml);

private:
   /// Constructeur par d�faut non implant�
   PI_SAX2_BASE_HANDLER();
   /// Constructeur par recopie non implant�
   PI_SAX2_BASE_HANDLER(const PI_SAX2_BASE_HANDLER& c);
   /// M�thode non implant�e
   const PI_SAX2_BASE_HANDLER& operator= (const PI_SAX2_BASE_HANDLER&);

protected:
   /// R�f�rence vers le fichier d'import Xml
   PI_FICHIER_IMPORT_XML& fich_xml;
   /// Nom de l'�lement courant en train de se faire parser
   std::string element_courant;
};

inline PI_SAX2_BASE_HANDLER::~PI_SAX2_BASE_HANDLER()
{
}

/**
 * Par d�faut, un gestionnaire n'a pas besoin d'observer
 */
inline void PI_SAX2_BASE_HANDLER::miseAJour(PI_SUJET& s)
{
}

inline void PI_SAX2_BASE_HANDLER::startElement(
   const XMLCh *const uri,
   const XMLCh *const localname,
   const XMLCh *const qname,
   const xercesc::Attributes& attrs
)
{
   element_courant = XML_TO_STD_STR(localname);
}

inline PI_SAX2_BASE_HANDLER::PI_SAX2_BASE_HANDLER(
   PI_FICHIER_IMPORT_XML& fichXml
)
:  fich_xml(fichXml)
{
}

#endif
