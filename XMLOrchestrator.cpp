#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/sax2/XMLReaderFactory.hpp>


using namespace xercesc;
using namespace boost;

int PI_FICHIER_IMPORT_XML::analyser_syntaxe()
{
   try 
   {
      // Guarde afin de reinitialiser le gestionnaire
      ON_BLOCK_EXIT_OBJ(*this, &PI_FICHIER_IMPORT_XML::reinitialiser);

      // Instanciation et initialisation du parseur
      parseur.reset( XMLReaderFactory::createXMLReader() );
      
      parseur->setFeature(XMLUni::fgSAX2CoreValidation, true);
      parseur->setFeature(XMLUni::fgXercesDynamic, true);
      parseur->setFeature(XMLUni::fgSAX2CoreNameSpaces, true);
      parseur->setFeature(XMLUni::fgXercesSchema, true);
      parseur->setFeature(XMLUni::fgXercesSchemaFullChecking, true);
      parseur->setFeature(XMLUni::fgSAX2CoreNameSpacePrefixes, true);

      error_handler.reset( new PI_SAX2_ERROR_HANDLER );
      parseur->setErrorHandler( error_handler.get() );
      
      // On parse une 1re fois pour detecter les erreurs de validation
      // a l'aide des fichiers schemas 
      parseur->parse( get_nomDeLIdentificateur().c_str() );

      // Verification du succes de l'operation de validation des fichiers
      // schemas
      if (parseur->getErrorCount() > 0)
      {
         ostringstream msgErreur;
         msgErreur << "Erreur lors de la validation du fichiers d'entrees"
            " selon le XML Schema specifie"
            "\nNombres d'erreurs : " << parseur->getErrorCount() << endl;

         throw PI_ERREUR( msgErreur.str().c_str() );
      }

      cerr << "Validation du fichier d'entrees reussite. On procede "
         "a l'instanciation" << endl;

      // La validation est reussie, alors on procede au second parsage qui
      // cette fois ci, instanciera les objets PIR
      auto_ptr<PI_SAX2_BASE_HANDLER> mainHandler(
         new PI_SAX2_MAIN_HANDLER(*this)
      );
      empilerHandler( mainHandler );

      parseur->parse(get_nomDeLIdentificateur().c_str());

      // Verification du succes de l'operation de l'instanciation des objets
      // PIE specifies dans le fichier xml
      if (parseur->getErrorCount() > 0)
      {
         ostringstream msgErreur;
         msgErreur << "Erreur lors de l'instanciation des objets Pir specifies"
            " dans le fichier XML\n"
            "Nombres d'erreurs : " << parseur->getErrorCount() << endl;
         throw PI_ERREUR( msgErreur.str().c_str() );
      }

      return 0;
   }
   catch (const XMLException& ex)
   {
      ostringstream nouveauMsg;
      nouveauMsg << "pifichxml.cpp - XMLException message : \n"
         << XML_TO_STD_STR(ex.getMessage()) << "\n" << endl;

      throw PI_ERREUR( nouveauMsg.str().c_str() ); 
   }
}

/**
 * Cette fonction permet d'empiler une gestionnaire SAX2
 *
 * @param nouveauHandler Le gestionnaire a empiler
 *
 * @throw PI_ERREUR si le parseur n'existe pas
 *
 * @remark Le gestionnaire est automatique assign� au parseur courant
 */
void PI_FICHIER_IMPORT_XML::empilerHandler(
   std::auto_ptr<PI_SAX2_BASE_HANDLER> nouveauHandler
)
{
   // Verifie l'existence du parseur
   if (parseur == 0)
   {
      throw PI_ERREUR( "Pour empiler un gestionnaire, un parseur doit etre construit" );
   }

   // Prend en charge le nouveau handler et l'enregistre aupres du parseur
   handler_stack.push( 
      shared_ptr<PI_SAX2_BASE_HANDLER>(
         nouveauHandler.release()
      )
   );
   parseur->setContentHandler( handler_stack.top().get() );
}

/**
 * Cette fonction depile le gestionnaire courant assigne au parseur
 */
void PI_FICHIER_IMPORT_XML::depilerHandler()
{
   // On d�truit le gestionnaire sur le haut de la pile
   handler_stack.pop();

   // Si un parseur existe, on reassigne le handler du haut de la pile au
   // gestionnaire
   if (parseur != 0)
   {
      // Il n'y plus rien sur la pile, le parseur est sans gestionnaire
      if (handler_stack.empty())
      {
         parseur->setContentHandler(0);
      }
      else 
      { 
         parseur->setContentHandler( handler_stack.top().get() );
      }
   }
}

void PI_FICHIER_IMPORT_XML::reinitialiser()
{
   parseur.reset();
   error_handler.reset();

   // On vide la pile
   while ( !handler_stack.empty() )
   {
      handler_stack.pop();
   }
}
