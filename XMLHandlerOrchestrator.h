#ifndef _HEADER_XML_IMPORT_PI_FICH_XML_
#define _HEADER_XML_IMPORT_PI_FICH_XML_

/**
 * @file pificxml.h Definition de la classe PI_FICHIER_IMPORT_XML
 */

#include <stack>
#include <memory>

#include <xercesc/sax2/SAX2XMLReader.hpp>


class XMLHandlerOrchestrator
{
public:
   /// Constructeur par param�tres
   XMLHandlerOrchestrator( const string& nomFichier );

   /// Destructeur
   virtual ~XMLHandlerOrchestrator() {};

   /// Fonction virtuelle lan�ant le parsage du fichier d'import
   virtual int analyser_syntaxe();
 
   /// Empile un gestionnaire SAX2 et l'enregistre au parseur
   void pushHandler(std::shared_ptr<StackableHandler> nouveauHandler);

   /// D�pile le gestionnaire SAX2 sur le haut de la pile
   void popHandler();

   /// Reinitialise le fichier import xml
   void reinitialiser();

private:
   /// Constructeur non implant�s
   XMLHandlerOrchestrator();

   /// Constructeur non implant�s
   XMLHandlerOrchestrator(const XMLHandlerOrchestrator&);
   /// M�thode non implant�s
   const XMLHandlerOrchestrator& operator= (const XMLHandlerOrchestrator&);
   
private:
   /// Pile des gestionnaires SAX2
   std::stack< std::shared_ptr<StackableHandler> > _theStackOfHandlers;

   /// Le parseur xml SAX2
   std::shared_ptr<xercesc::SAX2XMLReader> _theReader;

   //   /// Le gestionnaire d'erreurs SAX2
   // boost::scoped_ptr<PI_SAX2_ERROR_HANDLER> error_
};

#endif
