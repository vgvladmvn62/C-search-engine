#include "SearchServer.h"


SearchServer::SearchServer(InvertedIndex const &idx) 
                           : m_FreqDictionary {idx.GetFreqDictionary()} {}

std::vector<std::vector<RelativeIndex>> SearchServer::Search(std::vector<std::string> const &vQueriesInput, 
                                                             size_t const &nResponsesLimit)
{
    std::vector<std::vector<RelativeIndex>> vResults {};

    for (auto const &query : vQueriesInput)
    {
        std::stringstream ssBuf {query};
        std::set<std::string> setUniqueQueries {};
        std::unordered_map<size_t, size_t> umapCounter {};
        std::vector<RelativeIndex> vQueryResult {};

        while (!ssBuf.eof())
        {
            std::string sWord {};
            ssBuf >> sWord;
            setUniqueQueries.insert(sWord);
        }

        for (auto const &sWord : setUniqueQueries)
        {
            if (m_FreqDictionary.count(sWord) > 0)
            {
                for (auto const &entry : m_FreqDictionary.at(sWord))
                {
                    if (!umapCounter.insert(std::pair<size_t, size_t>(entry.docID, entry.count)).second)
                        umapCounter.at(entry.docID) += entry.count; //  Если этот док уже встречался, его релевантность выше.
                }
            }
        }
        
        {
            std::vector<std::pair<size_t, size_t>> vSorting {umapCounter.begin(), 
                                                             umapCounter.end()};
            
            std::sort(vSorting.begin(), vSorting.end(), 
                      [](auto const &a, auto const &b)
                      {return a.second > b.second;});

            std::sort(vSorting.begin(), vSorting.end(), 
                      [](auto const &a, auto const &b)
                      {return ((a.second == b.second && a.first < b.first) || (a.second > b.second));});
            
            for (size_t i {}, size {vSorting.size()}; 
                 (i < nResponsesLimit) && (i < size); 
                 ++i)
            {
                RelativeIndex newRelativeIndex {vSorting[i].first, 
                                                (static_cast<float>(vSorting[i].second) 
                                                / (setUniqueQueries.size()))};
                
                vQueryResult.push_back(newRelativeIndex);
            }
        }

        vResults.push_back(vQueryResult);
    }

    return vResults;
}