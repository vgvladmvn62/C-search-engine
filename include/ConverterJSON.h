#ifndef H_CONVERTER_JSON
#define H_CONVERTER_JSON


#include "SearchServer.h"
#include "nlohmann/json.hpp"
#include <vector>
#include <sstream>
#include <fstream>
#include <iostream>


#define CONFIG_FILE "config.json"
#define REQUESTS_FILE "requests.json"
#define ANSWERS_FILE "answers.json"


/**
* Класс для работы с JSON-файлами.
*/
class ConverterJSON 
{
    std::vector<std::string> m_TextDocsFilesList {};
    std::string              m_sRequestsFilename {};
    std::string              m_sAnswersFilename  {};
    std::string              m_sProgramName      {};
    std::string              m_sProgramVersion   {};
    size_t                   m_ResponsesLimit    {5};

public:

    ConverterJSON() = default;

    /**
    *  Метод для сохранения значений параметров из файла конфигурации
    * config.json в переменные класса.
    */
    void SetConfiguration();

    /**
    *  Метод получения имени программы.
    * @return возвращает значение переменной m_sProgramName.
    */
    std::string const &GetName() const;

    /**
    * Метод полчения версии программы.
    * @return возвращает значение переменной m_sProgramVersion...
    */
    std::string const &GetVersion() const;
    
    /**
    *  Метод получения предельного количества ответов на один запрос.
    * @return возвращает значение переменной m_ResponsesLimit.
    */
    size_t const &GetResponsesLimit() const;
    
    /**
    *  Метод получения содержимого файлов.
    * @return Возвращает список с содержимым файлов перечисленных
    * в config.json.
    */
    std::vector<std::string> GetTextDocuments();

    /**
    *  Метод получения запросов из файла requests.json.
    * @return возвращает список запросов из файла requests.json.
    */
    std::vector<std::string> GetRequests();

    /**
    *  Положить в файл answers.json результаты поисковых запросов..
    */
    void PutAnswers(std::vector<std::vector<RelativeIndex>>);
};

#endif