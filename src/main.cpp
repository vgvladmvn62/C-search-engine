#include "ConverterJSON.h"

#include "InvertedIndex.h"

#include "SearchServer.h"




int main()

{
    
ConverterJSON newConverterJSON;
    
newConverterJSON.SetConfiguration();
    
   
 InvertedIndex newInvertedIndex;
    
newInvertedIndex.UpdateDocumentBase(newConverterJSON.GetTextDocuments());
    
    
SearchServer newSearchServer {newInvertedIndex};
    
    
newConverterJSON.PutAnswers(newSearchServer.Search(newConverterJSON.GetRequests(), 
                                                     newConverterJSON.GetResponsesLimit()));
    
  
  std::cout << newConverterJSON.GetName() << " version " 
<< newConverterJSON.GetVersion() << " execution completed";

}