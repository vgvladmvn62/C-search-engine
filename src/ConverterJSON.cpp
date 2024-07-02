#include "ConverterJSON.h"


void ConverterJSON::SetConfiguration()
{
    std::ifstream ifsFile {CONFIG_FILE};

    if (!ifsFile.is_open())
        throw std::runtime_error("Config file is missing\n");
        
    if (!nlohmann::json::accept(ifsFile))
        throw std::runtime_error("Config file has invalid JSON format");

    nlohmann::json jsonConfig;

    ifsFile.seekg(0);
    ifsFile >> jsonConfig;

    ifsFile.close();

    if (!jsonConfig.contains("config"))
        throw std::runtime_error("Config file is empty");
    
    if (!jsonConfig.contains("files") || jsonConfig["files"].size() == 0)
        throw std::runtime_error("Config file list is empty");
    
    if (!jsonConfig["config"].contains("name"))
        throw std::runtime_error("Key \"name\" in config file is missing");
    
    if (!jsonConfig["config"].contains("version"))
        throw std::runtime_error("Key \"version\" in config file is missing");

    m_sProgramName = jsonConfig["config"]["name"].get<std::string>();
    m_sProgramVersion = jsonConfig["config"]["version"].get<std::string>();

    if (jsonConfig["config"].contains("max_responses"))
        m_ResponsesLimit = jsonConfig["config"]["max_responses"].get<size_t>();

    if (jsonConfig["config"].contains("answers"))
        m_sAnswersFilename = jsonConfig["config"]["answers"].get<std::string>();

    if (jsonConfig["config"].contains("requests"))
        m_sRequestsFilename = jsonConfig["config"]["requests"].get<std::string>();

    for (size_t i {}, size {jsonConfig["files"].size()}; i < size; ++i)
        m_TextDocsFilesList.push_back(jsonConfig["files"][i].get<std::string>());
}

std::string const &ConverterJSON::GetName() const
{
    return m_sProgramName;
}

std::string const &ConverterJSON::GetVersion() const
{
    return m_sProgramVersion;
}

size_t const &ConverterJSON::GetResponsesLimit() const
{
    return m_ResponsesLimit;
}

std::vector<std::string> ConverterJSON::GetTextDocuments()
{
    std::vector<std::string> vTextDocuments;

    for (auto const &textDocFile : m_TextDocsFilesList)
    {
        try
        {
            std::ifstream ifsFile (textDocFile);
            
            if (!ifsFile.is_open())
            {
                std::string sMessage {"File \"" + textDocFile + "\" from config file list does not exist"};
                throw std::runtime_error(sMessage);
            }
            
            std::string sTextDocument {};
            
            std::getline(ifsFile, sTextDocument, '\0');
            vTextDocuments.push_back(std::move(sTextDocument));

            ifsFile.close();
        }
        catch(std::runtime_error const &event)
        {
            std::cout << event.what() << '\n';
        }
    }

    return std::move(vTextDocuments);
}

std::vector<std::string> ConverterJSON::GetRequests()
{
    std::ifstream ifsFile {(m_sRequestsFilename.size() > 0) 
                            ? m_sRequestsFilename : REQUESTS_FILE};

    if (!ifsFile.is_open())
        throw std::runtime_error("Requests file is missing\n");
    
    if (!nlohmann::json::accept(ifsFile))
        throw std::runtime_error("Requests file has invalid JSON format");

    nlohmann::json jsonRequests;
    
    ifsFile.seekg(0);
    ifsFile >> jsonRequests;

    ifsFile.close();
    
    std::vector<std::string> vRequests;
    
    for (size_t i {}, size {jsonRequests["requests"].size()}; i < size; ++i)
        vRequests.push_back(jsonRequests["requests"][i].get<std::string>());

    return vRequests;
}

void ConverterJSON::PutAnswers(std::vector<std::vector<RelativeIndex>> vAnswers)
{
    nlohmann::json jsonAnswers {{"answers", {}}};

    for (size_t i {}, size {vAnswers.size()}; i < size; ++i)
    {
        std::string sRequestCountKey {};
        std::stringstream ssBuf;
        
        ssBuf << "request" << std::setfill('0') << std::setw(3) << (i + 1);
        ssBuf >> sRequestCountKey;

        if (vAnswers[i].size() == 1)
        {            
            jsonAnswers["answers"][sRequestCountKey]["result"] = true;
            jsonAnswers["answers"][sRequestCountKey]["docid"] = vAnswers[i].at(0).doc_id;
            jsonAnswers["answers"][sRequestCountKey]["rank"] = vAnswers[i].at(0).rank;
        }
        else if (vAnswers[i].size() > 1)
        {            
            jsonAnswers["answers"][sRequestCountKey]["result"] = true;

            for (size_t j {}, size {vAnswers[i].size()}; j < size; j++)
            {
                jsonAnswers["answers"][sRequestCountKey]["relevance"] += {{"docid", vAnswers[i].at(j).doc_id}, 
                                                                    {"rank", vAnswers[i].at(j).rank}};
            }
        }
        else
            jsonAnswers["answers"][sRequestCountKey]["result"] = false;
    }
    
    std::ofstream ofsFile {(m_sAnswersFilename.size() > 0) 
                            ? m_sAnswersFilename : ANSWERS_FILE};

    if (!ofsFile.is_open())
        throw std::runtime_error("Can't open or create output file\n");
    
    ofsFile << jsonAnswers;

    ofsFile.close();
}