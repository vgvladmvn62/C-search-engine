#ifndef H_INVERTED_INDEX
#define H_INVERTED_INDEX


#include <vector>
#include <map>
#include <set>
#include <string>
#include <sstream>
#include <thread>
#include <mutex>
#include <memory>


struct Entry
{
    size_t docID, count;

    //     Оператор для проведения тестовых сценариев.
    bool operator ==(const Entry& other) const 
    {
        return (docID == other.docID && count == other.count);
    }
};


/**
* Класс для индексации файлов..
*/
class InvertedIndex
{
    std::shared_ptr<std::mutex>               m_mu {std::make_shared<std::mutex>()};
    std::vector<std::string>                  m_vDocs {}; // 

    std::map<std::string, std::vector<Entry>> m_FreqDictionary {}; // 

public:
    
    InvertedIndex() = default;
    /**
    *  Обновить или заполнить базу документов, по которой будем совершать
    * поиск.
    * @param vInputDocs содержимое документов.
    */
    void UpdateDocumentBase(std::vector<std::string> const &vInputDocs);

    /**
    * Метод для заполнения словаря m_FreqDictionary.
    * @param sInputDoc содержимое документа.
    */
    void FillFreqDictionary(std::string const &sInputDoc);

    /**
    *Метод определяет количество вхождений слова word в загруженной базе
    * документов.
    * @param sWord слово, частоту вхождений которого необходимо определить.
    * @return возвращает подготовленный список с частотой слов.
    */
    std::vector<Entry> GetWordCount(std::string const & sWord);

    /**
    * Метод для обращения к m_FreqDictionary.
    * @return возвращает значение поля m_FreqDictionary.
    */
    std::map<std::string, std::vector<Entry>> GetFreqDictionary() const;
};

#endif