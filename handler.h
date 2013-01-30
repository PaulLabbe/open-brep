#ifndef _HEADER_XML_IMPORT_PI_FICH_XML_
#define _HEADER_XML_IMPORT_PI_FICH_XML_

/**
 * @file pificxml.h Definition de la classe PI_FICHIER_IMPORT_XML
 */

#include <stack>
#include <memory>

#include <xercesc/sax2/SAX2XMLReader.hpp>

#include <boost/smart_ptr.hpp>

#include "pirate.h"
#include "pifich.h"
#include "p_vectid.h"
#include "pichrefa.h"

#include "pisax2errorhandler.h"
#include "pisax2basehandler.h"

/**
 * @brief Gestionnaire qui peut lire des fichiers en format natif de pirate 
 * sous forme xml.
 *
 * Tout ce qui peut se trouver dans un fichier de pirate. Le
 * PI_FICHIER_IMPORT_XML est un gestionnaire qui est capable de lire un fichier
 * pirate sous forme xml.
 */
class PI_FICHIER_IMPORT_XML : public PI_FICHIER_IMPORT
{
public:
   /// Constructeur par param�tres
   PI_FICHIER_IMPORT_XML( const string& nomFichier );
   /// Destructeur
   virtual ~PI_FICHIER_IMPORT_XML() {};

   /// Fonction virtuelle lan�ant le parsage du fichier d'import
   virtual int analyser_syntaxe();
 
   /// Empile un gestionnaire SAX2 et l'enregistre au parseur
   void empilerHandler(std::auto_ptr<PI_SAX2_BASE_HANDLER> nouveauHandler);
   /// D�pile le gestionnaire SAX2 sur le haut de la pile
   void depilerHandler();

   /// Reinitialise le fichier import xml
   void reinitialiser();

private:
   /// Constructeur non implant�s
   PI_FICHIER_IMPORT_XML();
   /// Constructeur non implant�s
   PI_FICHIER_IMPORT_XML(const PI_FICHIER_IMPORT_XML&);
   /// M�thode non implant�s
   const PI_FICHIER_IMPORT_XML& operator= (const PI_FICHIER_IMPORT_XML&);
   
private:
   /// Variable indiquant si la librairie Xerces a �t� initialis�e ou non
   static bool s_lib_xerces_initialisees;

   /// Pile des gestionnaires SAX2
   std::stack< boost::shared_ptr<PI_SAX2_BASE_HANDLER> > handler_stack;
   /// Le parseur xml SAX2
   boost::scoped_ptr<xercesc::SAX2XMLReader> parseur;
   /// Le gestionnaire d'erreurs SAX2
   boost::scoped_ptr<PI_SAX2_ERROR_HANDLER> error_handler;

   /// References en amont
   P_TMPL_VECT_ID<PI_CHREF_AMONT> references_amonts;
};

#endif
