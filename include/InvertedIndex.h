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

    //     �������� ��� ���������� �������� ���������.
    bool operator ==(const Entry& other) const 
    {
        return (docID == other.docID && count == other.count);
    }
};


/**
* ����� ��� ���������� ������..
*/
class InvertedIndex
{
    std::shared_ptr<std::mutex>               m_mu {std::make_shared<std::mutex>()};
    std::vector<std::string>                  m_vDocs {}; // 

    std::map<std::string, std::vector<Entry>> m_FreqDictionary {}; // 

public:
    
    InvertedIndex() = default;
    /**
    *  �������� ��� ��������� ���� ����������, �� ������� ����� ���������
    * �����.
    * @param vInputDocs ���������� ����������.
    */
    void UpdateDocumentBase(std::vector<std::string> const &vInputDocs);

    /**
    * ����� ��� ���������� ������� m_FreqDictionary.
    * @param sInputDoc ���������� ���������.
    */
    void FillFreqDictionary(std::string const &sInputDoc);

    /**
    *����� ���������� ���������� ��������� ����� word � ����������� ����
    * ����������.
    * @param sWord �����, ������� ��������� �������� ���������� ����������.
    * @return ���������� �������������� ������ � �������� ����.
    */
    std::vector<Entry> GetWordCount(std::string const & sWord);

    /**
    * ����� ��� ��������� � m_FreqDictionary.
    * @return ���������� �������� ���� m_FreqDictionary.
    */
    std::map<std::string, std::vector<Entry>> GetFreqDictionary() const;
};

#endif