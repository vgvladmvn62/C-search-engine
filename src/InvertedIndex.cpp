#include "InvertedIndex.h"


void InvertedIndex::UpdateDocumentBase(std::vector<std::string> const &vInputDocs)
{
    m_vDocs = {vInputDocs.begin(), vInputDocs.end()};

    std::vector<std::thread *> vThreads;

    for (auto const &sDoc : m_vDocs)
    {
        std::thread *newThread {new std::thread {FillFreqDictionary, this, std::cref(sDoc)}};
        vThreads.push_back(newThread);
    }

    for (auto thread : vThreads)
    {
        thread->join();
        delete thread;
        thread = nullptr;
    }

    m_vDocs.clear();
}

void InvertedIndex::FillFreqDictionary(std::string const &sDoc)
{
    std::set<std::string> setUniqueWords {};
    std::stringstream ssBuf {sDoc};

    while (!ssBuf.eof())
    {
        std::string sWord {};
        ssBuf >> sWord;
        if (m_FreqDictionary.count(sWord) == 0) // ≈сли слово есть в словаре, его можно пропустить.
            setUniqueWords.insert(sWord);
    }
    
    for (auto const &sWord : setUniqueWords)
    {
        std::vector<Entry> vWordCount {GetWordCount(sWord)};
        m_mu->lock();
        m_FreqDictionary.insert({sWord, vWordCount});
        m_mu->unlock();
    }
}

std::vector<Entry> InvertedIndex::GetWordCount(std::string const &sWord)
{
    std::vector<Entry> vEntries {};

    for (size_t docID {}, size {m_vDocs.size()}; docID < size; ++docID)
    {
        std::stringstream ssBuf   {m_vDocs[docID]};
        size_t            count   {};

        while (!ssBuf.eof())
        {
            std::string newWord {};
            ssBuf >> newWord;
            if (newWord == sWord)
                ++count;
        }

        if (count > 0)
        {
            vEntries.push_back({docID, count});
        }
    }

    return vEntries;
}

std::map<std::string, std::vector<Entry>> InvertedIndex::GetFreqDictionary() const
{
    return m_FreqDictionary;
}