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
* ����� ��� ������ � JSON-�������.
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
    *  ����� ��� ���������� �������� ���������� �� ����� ������������
    * config.json � ���������� ������.
    */
    void SetConfiguration();

    /**
    *  ����� ��������� ����� ���������.
    * @return ���������� �������� ���������� m_sProgramName.
    */
    std::string const &GetName() const;

    /**
    * ����� �������� ������ ���������.
    * @return ���������� �������� ���������� m_sProgramVersion...
    */
    std::string const &GetVersion() const;
    
    /**
    *  ����� ��������� ����������� ���������� ������� �� ���� ������.
    * @return ���������� �������� ���������� m_ResponsesLimit.
    */
    size_t const &GetResponsesLimit() const;
    
    /**
    *  ����� ��������� ����������� ������.
    * @return ���������� ������ � ���������� ������ �������������
    * � config.json.
    */
    std::vector<std::string> GetTextDocuments();

    /**
    *  ����� ��������� �������� �� ����� requests.json.
    * @return ���������� ������ �������� �� ����� requests.json.
    */
    std::vector<std::string> GetRequests();

    /**
    *  �������� � ���� answers.json ���������� ��������� ��������..
    */
    void PutAnswers(std::vector<std::vector<RelativeIndex>>);
};

#endif