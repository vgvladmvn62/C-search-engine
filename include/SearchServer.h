#ifndef H_SEARCH_SERVER
#define H_SEARCH_SERVER


#include "InvertedIndex.h"
#include <unordered_map>
#include <algorithm>


struct RelativeIndex
{
    size_t doc_id {};
    float  rank   {};
    
    //Оператор для проведения тестовых сценариев.
    bool operator ==(RelativeIndex const &other) const 
    {
        return (doc_id == other.doc_id && rank == other.rank);
    }
};


/*
* Класс для обработки поисковых запросов.
*/
class SearchServer
{
    std::map<std::string, std::vector<Entry>> const m_FreqDictionary {};
    
public:

    /**
    *  @param idx в конструктор класса передаётся ссылка на класс InvertedIndex,
    * чтобы SearchServer мог узнать частоту слов, встречаемых в запросе.
    */
    SearchServer(InvertedIndex const &idx);

    /**
    * Метод обработки поисковых запросов.
    * @param queries_input поисковые запросы взятые из файла requests.json.
    * @return возвращает отсортированный список релевантных ответов для заданных запросов.
    */
    std::vector<std::vector<RelativeIndex>> Search(std::vector<std::string> const &vQueriesInput, 
                                                   size_t const &nResponsesLimit);
};

#endif
