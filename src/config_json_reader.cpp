#include "../include/util.hpp"
#include "../include/config_json_reader.hpp"

ConfigJsonReader::ConfigJsonReader(StyleManager *styleManager) {
    m_styleManager = styleManager;
}

std::map<std::string, JsonReaderStrategy*> ConfigJsonReader::createOptions() {
    std::map<std::string, JsonReaderStrategy*> options;
    options["selector"] = new JsonStringReaderStrategy(&m_config.selector);
    options["active_selector"] =
        new JsonStringReaderStrategy(&m_config.activeSelector);
    options["prompt"] = new JsonStringReaderStrategy(&m_config.prompt);

    options["prompt_gap"] = (
            new JsonIntReaderStrategy(&m_config.promptGap))->min(0);
    options["history_limit"] = (
            new JsonIntReaderStrategy(&m_config.historyLimit))->min(0);
    options["min_hint_spacing"] = (
            new JsonIntReaderStrategy(&m_config.minHintSpacing))->min(0);
    options["min_hint_width"] = (
            new JsonIntReaderStrategy(&m_config.minHintWidth))->min(0);
    options["max_hint_width"] = (
            new JsonIntReaderStrategy(&m_config.maxHintWidth))->min(0);
    options["show_spinner"] = (
            new JsonBoolReaderStrategy(&m_config.showSpinner));

     options["matcher"] = new JsonEnumReaderStrategy<MatcherType>(
         &m_config.matcher,
         std::map<std::string, MatcherType>{
             {"fuzzy", FUZZY_MATCHER},
             {"regex", REGEX_MATCHER},
             {"exact", REGEX_MATCHER}}
     );
     options["case_mode"] = new JsonEnumReaderStrategy<CaseSensitivity>(
         &m_config.caseSensitivity,
         std::map<std::string, CaseSensitivity>{
            {"sensitive", CASE_SENSITIVE},
            {"insensitive", CASE_INSENSITIVE},
            {"smart", SMART_CASE}}
     );

    std::map<std::string, int*> styles;
    styles["item"] = &m_config.itemStyle;
    styles["active_item"] = &m_config.activeItemStyle;
    styles["hint"] = &m_config.hintStyle;
    styles["active_hint"] = &m_config.activeHintStyle;
    styles["selector"] = &m_config.selectorStyle;
    styles["active_selector"] = &m_config.activeSelectorStyle;
    styles["active_row"] = &m_config.activeRowStyle;
    styles["row"] = &m_config.rowStyle;
    styles["search_prompt"] = &m_config.searchPromptStyle;
    styles["search"] = &m_config.searchStyle;
    styles["search_row"] = &m_config.searchRowStyle;
    styles["background"] = &m_config.backgroundStyle;
    options["style"] = new JsonStylesReaderStrategy(m_styleManager, styles);

    return options;
}

const JsonError ConfigJsonReader::getError() const {
    return m_error;
}

bool ConfigJsonReader::readJsonFile(JsonElement **root, std::ifstream& ifs) {
    if (!ifs.is_open()) {
        root = nullptr;
        m_error.message = "File was not open for reading";
        m_error.line = 0;
        return false;
    }

    std::string json((std::istreambuf_iterator<char>(ifs)),
            (std::istreambuf_iterator<char>()));
    JsonParser jsonParser;
    if (!jsonParser.parse(json)) {
        m_error.message = jsonParser.getError();
        m_error.line = jsonParser.getLine();
        return false;
    }

    *root = jsonParser.getElement();
    return true;
}

bool ConfigJsonReader::read(std::ifstream& ifs) {
    JsonElement *root;

    if (!readJsonFile(&root, ifs)) {
        return false;
    }

    if (root == nullptr) {
        return true;
    }

    std::map<std::string, JsonReaderStrategy*> options = createOptions();

    JsonReader reader(options);
    if (!reader.read(root)) {
        m_error = reader.getError();
        return false;
    }

    return true;
}
